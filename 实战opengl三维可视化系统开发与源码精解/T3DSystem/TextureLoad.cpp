// TextureLoad.cpp : implementation file
 

#include "stdafx.h"
 
#include "TextureLoad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CTextureLoad dialog

#define   BUFFERLEN   102400

CTextureLoad::CTextureLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureLoad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureLoad)
	//}}AFX_DATA_INIT
}


void CTextureLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureLoad)
	DDX_Control(pDX, IDC_LIST_FILES, m_listfiles);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureLoad, CDialog)
	//{{AFX_MSG_MAP(CTextureLoad)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CTextureLoad message handlers


//����ⲿ�����ļ�
void CTextureLoad::OnButtonBrowse() 
{
	CString  strFile,strFilter="Tif files(*.Tif)|*.Tif|\
							 BMP files(*.BMP)|*.BMP|\
							 Jpeg files(*.JPG)|*.JPG|\
							 GIF files(*.GIF)|*.GIF|\
							 PCX files(*.PCX)|*.PCX|\
							 Targa files(*.TGA)|*.TGA||";

	//���ƴ��ļ��Ի���ʹ֧�ֶ���ѡ��(OFN_ALLOWMULTISELECT)
	CFileDialog   fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT,strFilter);     

	char  *pBuf= new  char[BUFFERLEN];//���뻺����
	
	fdlg.m_ofn.lpstrFile=pBuf;    //��pBuf����CFileDialog������	
	fdlg.m_ofn.lpstrFile[0]='\0';     
	fdlg.m_ofn.nMaxFile=BUFFERLEN; 


	int nCount=0;//��ʼѡ����ļ���Ϊ0
	
	//����ɹ�����ȡ�Ի������ѡ����ļ�����������ӵ��б����
	if(fdlg.DoModal()==IDOK)     
	{     
        //GetStartPosition():����ָʾ����ӳ����ʼλ�õ�POSITIONλ�ã����ӳ��Ϊ�գ��򷵻�NULL
		POSITION  pos=fdlg.GetStartPosition();  
		m_listfiles.ResetContent();//����б��
	
		while(pos)   //���ӳ�䲻Ϊ��
		{   
			nCount++; 
			strFile=fdlg.GetNextPathName(pos);  //�õ��ļ���
			m_listfiles.AddString(strFile);//���ļ������뵽�б��
		}     
	}  
	
	delete[]  pBuf;   //���ջ�����
}

//��ʼ���Ի���
BOOL CTextureLoad::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	myOci.Init_OCI();	//��ʼ��OCI
	return TRUE;  
}

//�Ը�������Ӱ������ֿ鴦��,��д��oracle���ݿ���
void CTextureLoad::OnOK() 
{

	CString mfilename,stt,tt;

	BeginWaitCursor();

	CString tempDirctory="c:\\tempRailwayBmp";//�������Ӱ���ӿ����ʱ�ļ���
	DWORD  dwAttr=GetFileAttributes(tempDirctory);   //��ȡ�ļ�������
	if(dwAttr==0xFFFFFFFF)  //������ļ��в����ھʹ���һ��   
        CreateDirectory(tempDirctory,NULL);  //������ʱ�ļ���

	m_listfiles.SetCurSel(0);
	m_listfiles.GetText(m_listfiles.GetCurSel(),mfilename);
	if(GetTextureRange(mfilename)==FALSE)
		return;
	
	//�Ը�������Ӱ������ֿ鴦��,��д��oracle���ݿ���
	for(int i=0;i<m_listfiles.GetCount();i++)
	{
		m_listfiles.SetCurSel(i); //�����б��ǰ����
		m_listfiles.GetText(m_listfiles.GetCurSel(),mfilename);//�õ���ǰ����ȫ·����Ӱ���ļ���
		int nPos=mfilename.ReverseFind('\\');
		tt=mfilename.Mid(nPos+1,mfilename.GetLength()-nPos);//�õ�Ӱ���ļ���
		
		stt.Format("���ڴ���%s",tt);
		this->SetWindowText(stt);	//���öԻ������
		SeperateImage(mfilename,i,tempDirctory);//��Ӱ��������зֿ鴦��,��д��oracle���ݿ���	
	}	

	//��Ӱ������������Ϣд��Ӱ����Ϣ����
	tt.Format("INSERT INTO IMAGERECT_INFO VALUES(%.3f,%.3f,%.3f,%.3f,%d,\
		%.2f,%.2f,%.2f,%.2f,%.2f)",theApp.m_TexturLeftDown_x,theApp.m_TexturLeftDown_y,\
		theApp.m_TexturRightUp_x,theApp.m_TexturRightUp_y,m_listfiles.GetCount(),\
		theApp.m_ImageResolution[1],theApp.m_ImageResolution[2],theApp.m_ImageResolution[3],\
		theApp.m_ImageResolution[4],theApp.m_ImageResolution[5]);
	theApp.m_pConnection->Execute (_bstr_t(tt),NULL,adCmdText);//ִ��SQL���
	
	EndWaitCursor(); //������л�ΪĬ�Ϲ��,�����ȴ�
	m_progress.ShowWindow(SW_HIDE);//���ؽ�����
	m_progress.SetPos(0);//�ָ���ʼλ��0ֵ
	MessageBox("Ӱ�������ļ�д�����!","Ӱ���������",MB_OK);
	RemoveDirectory(tempDirctory); //ɾ����ʱ�ļ���
	theApp.bLoadImage=TRUE;//����Ӱ��ɹ�
		
	CDialog::OnOK();
}

//������Ӱ����зֿ鴦��,��д��oracle���ݿ���
void CTextureLoad::SeperateImage(CString mfilename, int m_phramidLayer,CString tempDirctory)
{
	
		CString stt,strfile;
        m_pImageObject=new CImageObject;
		
		m_pImageObject->Load(mfilename,NULL,-1,-1);//����Ӱ������
		long m_height=m_pImageObject->GetHeight();//�õ�����߶�
		long m_width=m_pImageObject->GetWidth();//�õ�������

		//��ǰLOD���������ֱ���
		theApp.m_ImageResolution[m_phramidLayer]=(theApp.m_TexturRightUp_x-theApp.m_TexturLeftDown_x)/m_width;
	

		//����Ӱ���ӿ�Ŀ��
		int m_fg_width=theApp.m_Dem_BlockWidth/theApp.m_ImageResolution[m_phramidLayer]; 
		//����Ӱ���ӿ�ĸ߶�
		int m_fg_height=theApp.m_Dem_BlockWidth/theApp.m_ImageResolution[m_phramidLayer];

		//���㵱ǰLOD��������Ӱ��ֿ��������
		if(m_height%m_fg_height==0)
			m_totalRows=m_height/m_fg_height;
		else
		{
			m_totalRows=m_height/m_fg_height+1;
			
		}
		
		//���㵱ǰLOD��������Ӱ��ֿ��������
		if(m_width%m_fg_width==0)
			m_totalCols=m_width/m_fg_width;
		else
		{
			m_totalCols=m_width/m_fg_width+1;
			
		}		
		
		int nPos=mfilename.ReverseFind('\\');
		strfile=mfilename.Mid(nPos+1,mfilename.GetLength()-nPos-5);

		for(int i=0;i<m_totalRows;i++)
		{
			for(int j=0;j<m_totalCols;j++)
			{
			
			//���ý�����ֵ
			m_progress.SetPos((i*m_totalCols+j+1)*100.0/(m_totalRows*m_totalCols));
			int mleftx=(j-0)*m_fg_width;	    //Ӱ���ӿ����½�x����
			int mlefty=(m_totalRows-i-1)*m_fg_height;	//Ӱ���ӿ����½�y����
			int mrightx=mleftx+m_fg_width-1;	//Ӱ���ӿ����Ͻ�x����
			int mrigty=mlefty+m_fg_height-1;	//Ӱ���ӿ����Ͻ�y����
			m_pImageObject->Crop( mleftx, mlefty, mrightx, mrigty);	//��ȡ��mleftx��mlefty��mrightx��mrigty��ȷ����Ӱ���ӿ�
			stt.Format("%s\\%s@%d_%d.bmp",tempDirctory,strfile,i,j);
			m_pImageObject->Save( stt, 1);//����ȡ��Ӱ���ӿ�洢����ʱ�ļ���
			int m_subImageWidth=m_pImageObject->GetWidth();//�õ�Ӱ���ӿ�Ŀ��
			int m_subImageHeight=m_pImageObject->GetHeight();//�õ�Ӱ���ӿ�ĸ߶�
		    //��Ӱ���ӿ���BLOB��������д��oracle���ݿ���
			WriteImageToDB(stt,i+1,j+1,m_subImageHeight,m_subImageWidth,m_phramidLayer,m_fg_width,m_fg_height);
			DeleteFile(stt);
			m_pImageObject->Load(mfilename,NULL,-1,-1);//���¼���ԭʼӰ��
			}
		}
}

//��Ӱ���ӿ���BLOB��������д��oracle���ݿ���
BOOL CTextureLoad::WriteImageToDB(CString strFile, int m_RowIndex, int m_ColIndex, int m_height, int m_width, int m_phramidLayer,int m_fg_width,int m_fg_height)
{
	
	CString tt;
	
	double m_leftdownx,m_leftdowny,m_rightUpx,m_rightUpy;

	//���㽫Ӱ���ӿ�����º����Ͻ�x,y�������
	m_leftdownx=(m_ColIndex-1)*m_fg_width*theApp.m_ImageResolution[m_phramidLayer]+theApp.m_TexturLeftDown_x;
	m_leftdowny=(m_RowIndex-1)*m_fg_height*theApp.m_ImageResolution[m_phramidLayer]+theApp.m_TexturLeftDown_y;
	m_rightUpx=m_leftdownx+m_width*theApp.m_ImageResolution[m_phramidLayer];
	m_rightUpy=m_leftdowny+m_height*theApp.m_ImageResolution[m_phramidLayer];

	int m_ID=(m_RowIndex-1)*m_totalCols+m_ColIndex;//Ӱ���ӿ��ID��

	tt.Format("INSERT INTO texture VALUES(%d,%d,%d,%d,%d,EMPTY_BLOB(),\
		%ld,%.3f,%.3f,%.3f,%.3f)",\
		m_RowIndex,m_ColIndex,m_height,m_width,m_phramidLayer,m_ID,\
		m_leftdownx,m_leftdowny,m_rightUpx,m_rightUpy);
	
	//����OCI�������AddNormalDataToDB�������������������͵�����д��oracle���ݿ���
	myOci.AddNormalDataToDB(tt);

	//����OCI�������AddBOLBDataToDB��������BLOB���͵�����д��oracle���ݿ���
	tt.Format("SELECT �������� FROM texture WHERE �к�=%d AND �к�=%d AND ������������=%d AND ���= :%d FOR UPDATE",m_RowIndex,m_ColIndex,m_phramidLayer,m_ID)  ;
	myOci.AddBOLBDataToDB(strFile,tt,m_ID);
	
	return TRUE;
}

//���ٶԻ���
void CTextureLoad::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_pImageObject=NULL;
	delete m_pImageObject;
	
}

 
//�����һ������Ӱ�񲻽��зֿ�ֱ��д�����ݿ���,������Ϊ����ͼ����
BOOL CTextureLoad::WriteLittleLodImageToDB(CString strFile)
{
	
	CString tt;
	int m_ID=1;
	
	tt.Format("INSERT INTO texture_LitLOD VALUES(EMPTY_BLOB(),%d)",m_ID);
	//����OCI�������AddNormalDataToDB�������������������͵�����д��oracle���ݿ���
	myOci.AddNormalDataToDB(tt);
	
	tt.Format("SELECT �������� FROM texture_LitLOD WHERE  ���= :%d FOR UPDATE",m_ID)  ;
	//����OCI�������AddBOLBDataToDB��������BLOB���͵�����д��oracle���ݿ���
	myOci.AddBOLBDataToDB(strFile,tt,m_ID);
	return TRUE;
}


//�õ�Ӱ����������º����Ͻ� x,y����
BOOL CTextureLoad::GetTextureRange(CString tcrPathname)
{
	/*
	
	Ӱ�����������ļ�������Ŀ����ͬ���ģ���չ��Ϊ".tod"���ļ��д洢�ģ����ʽΪ��
	lb: 781395.000	1869975.000
	rt: 797995.000	1876275.000
	����	��һ�е�lb:��ʾӰ����������½�x,y����
			�ڶ��е�rt:��ʾӰ����������Ͻ�x,y����
	*/
	CString tt,strpath;
	int	pos=tcrPathname.ReverseFind('\\');
	strpath=tcrPathname.Left(pos);
	pos=strpath.ReverseFind('\\');
	tt=strpath.Right(strpath.GetLength()-pos-1);
    FILE *fp;
	tt=strpath+"\\"+tt+".tod";//�õ�Ӱ��Χ�ļ���
	
	if((fp=fopen(tt,"r"))==NULL)//����ļ���ʧ��
    {
		MessageBox("Ӱ��Χ�ļ�"+tt+"������!","��ȡӰ��Χ�ļ�",MB_ICONINFORMATION+MB_OK);
		fclose(fp);	//�ر��ļ�
		return FALSE;//����FALSE
	}
	else
	{
		fscanf(fp,"%s",tt);//�õ�lb:�ַ���
		fscanf(fp,"%s",tt);theApp.m_TexturLeftDown_x=atof(tt);//��������½�x����
		fscanf(fp,"%s\n",tt);theApp.m_TexturLeftDown_y=atof(tt);//�������x,y����
		fscanf(fp,"%s",tt);//�õ�rt:�ַ���
		fscanf(fp,"%s",tt);theApp.m_TexturRightUp_x=atof(tt);//��������Ͻ�x����
		fscanf(fp,"%s\n",tt);theApp.m_TexturRightUp_y=atof(tt);//��������Ͻ�y����
		fclose(fp);//�ر��ļ�
		return TRUE;//����TRUE
		
	}
	
}
