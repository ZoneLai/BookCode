// DemLoad.cpp : implementation file
 

#include "stdafx.h"
 
#include "DemLoad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 
// CDemLoad dialog

CDemLoad::CDemLoad(CWnd* pParent /*=NULL*/)
	: CDialog(CDemLoad::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemLoad)
	m_DemFileName = _T("");
	m_strblockinfo = _T("");
	m_strsubblockinfo = _T("");
	//}}AFX_DATA_INIT
}


void CDemLoad::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemLoad)
	DDX_Control(pDX, IDC_COMBO_SUBBLOCKSIZE, m_subCombolblockSize);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	DDX_Text(pDX, IDC_EDIT_DEMFILE, m_DemFileName);
	DDX_Text(pDX, IDC_EDIT_BLOCKINFOR, m_strblockinfo);
	DDX_Text(pDX, IDC_EDIT_SUBBLOCKINFOR, m_strsubblockinfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDemLoad, CDialog)
	//{{AFX_MSG_MAP(CDemLoad)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_SEPERATE, OnButtonSeperate)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBBLOCKSIZE, OnSelchangeComboSubblocksize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CDemLoad message handlers

//��DEM�ӿ�����д�����ݿ���
void CDemLoad::AddDemBlockDataToDB(int RowIndex, int ColIndex, CString strfilenaem, long ID)
{
	CString tt;
	double centerx,centery;

	//DEM�ӿ����������
	centerx=theApp.m_DemLeftDown_x+((ColIndex-1)+1.0/2)*theApp.m_Dem_BlockWidth;
	centery=theApp.m_DemLeftDown_y+((RowIndex-1)+1.0/2)*theApp.m_Dem_BlockWidth;

	tt.Format("INSERT INTO dem_block VALUES(%d,%d,EMPTY_BLOB(),%ld,%.3f,%.3f)",\
		RowIndex,ColIndex,ID,centerx,centery);

	myOci.AddNormalDataToDB(tt);//��������������д��oralce���ݿ���

	tt.Format("SELECT DEM���� FROM dem_block WHERE �к�=%d AND �к�=%d AND ���= :%d FOR UPDATE",RowIndex,ColIndex,ID)  ;
	myOci.AddBOLBDataToDB(strfilenaem,tt,ID);//��DEM�ֿ��ļ���ΪBLOB������������д��oralce���ݿ���
	
}


//��ʼ��DEM�ֿ��С
void CDemLoad::Init_BlockSize()
{
	long mvalue=1;
	int m;
	CString tt;
	m_subCombolblockSize.ResetContent ();
	for(int i=1;i<=9;i++)
	{
		m=1;
		for(int j=1;j<=i;j++)
			m=m*2;
		mvalue=m*16+1;
		tt.Format("%d",mvalue);
		tt=tt+"��"+tt;
		m_subCombolblockSize.AddString (tt);
	}
	m_subCombolblockSize.SetCurSel (0);
	OnSelchangeComboSubblocksize();
}

 
void CDemLoad::OnButtonBrowse() 
{


	CString tt,stt;
	FILE *fp;

	CFileDialog FileDialog(TRUE,"DEM�����ļ�",NULL,OFN_HIDEREADONLY \
		| OFN_OVERWRITEPROMPT,\
		"DEM�����ļ�(*.dem)|*.dem|\
		�ı���ʽ(*.txt)|*.txt||",NULL);
	
	FileDialog.m_ofn.lpstrTitle="��DEM�����ļ�";	


	if(FileDialog.DoModal() == IDOK)
		m_DemFileName = FileDialog.GetPathName();
	else
		return;	
	this->UpdateData(FALSE);
	

	
    if((fp=fopen(m_DemFileName,"r"))==NULL)
		
    {
		MessageBox("����ģ���ļ�������!","��ʼ������ģ��",MB_ICONINFORMATION+MB_OK);
		exit(-1);
	}

}

 
void CDemLoad::OnButtonSeperate() 
{
	CString stt;
	
	BeginWaitCursor();
    m_progress.ShowWindow(SW_SHOW);

	DWORD   dw1=GetTickCount();   
	tempDemDirctory="c:\\tempRailwayDem";
	DWORD  dwAttr=GetFileAttributes(tempDemDirctory);   
	if(dwAttr==0xFFFFFFFF)     
        CreateDirectory(tempDemDirctory,NULL);  //������ʱ�ļ���
	
	SeperateDem(m_DemFileName,m_subBlockSize);//�ֿ鴦��

	DWORD   dw2=GetTickCount();   
	DWORD   dw3=dw2-dw1; 
	stt.Format("%.3f��!",dw3/1000.0);
	EndWaitCursor(); //������л�ΪĬ�Ϲ��,�����ȴ�
	RemoveDirectory(tempDemDirctory);//ɾ����ʱ�ļ���
	
	SetWindowText("��ģ��ȡ��ֿ鴦��");	
	m_progress.ShowWindow(SW_HIDE);//���ؽ�����
	m_progress.SetPos(0);
	MessageBox("��ģ��ȡ��ֿ鴦����ɣ�����ʱ"+stt,"��ģ��ȡ��ֿ鴦��",MB_ICONINFORMATION|MB_OK);
	EndDialog(IDOK);//��IDOKģʽ�رնԻ���
	
}

//��ʼ����Ϣ
BOOL CDemLoad::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_progress.SetRange(0,100);//���ý������ؼ���Χ
	
	Init_BlockSize();//��ʼ��DEM�ֿ��С
	
	myOci.Init_OCI();//��ʼ��OCI

	return TRUE;  
}


//�ֿ�ѡ��ı�ʱ,����DEM�ӿ�ֿ��С
void CDemLoad::OnSelchangeComboSubblocksize() 
{
	int mIndex=	m_subCombolblockSize.GetCurSel();
	CString tt;
	m_subCombolblockSize.GetLBText(mIndex,tt);
	int mPos=tt.Find("��",1);
	tt=tt.Left(mPos);
	m_subBlockSize=atoi(tt);	
}

 
//���������õķֿ��С����DEM�ļ����зֿ鲢д��Oralce���ݿ���
void CDemLoad::SeperateDem(CString strfilename, int BlockSize)
{
	long i,j;
	GLint m_DEM_X_neednumber,m_DEM_Y_neednumber;
	CString *strfiles;
	CStdioFile *Sfiles;
	
	float hh;	
	CString tt,stt;
	CString m_TerrainFileName;

	FILE *fp=fopen(strfilename,"r");//��DEM�ļ�

	fscanf(fp,"%s",tt);theApp.m_DemLeftDown_x=atof(tt);//�õ�DEM���ݵ����½Ǵ��x����
    fscanf(fp,"%s",tt);theApp.m_DemLeftDown_y=atof(tt);//�õ�DEM���ݵ����½Ǵ��y����
    fscanf(fp,"%s",tt);theApp.m_Cell_xwidth=atoi(tt);//�õ�DEM������x���������ݵ���
    fscanf(fp,"%s",tt);theApp.m_Cell_ywidth=atoi(tt);//�õ�DEM������y���������ݵ���
    fscanf(fp,"%s",tt);theApp.m_Dem_cols=atoi(tt);//�õ�DEM����������
    fscanf(fp,"%s",tt);theApp.m_Dem_Rows=atoi(tt);//�õ�DEM����������
    fscanf(fp,"%s\n",tt);theApp.m_DEM_IvalidValue=atoi(tt);//�õ�DEM������Ч����ֵ
    
    theApp.m_Dem_BlockSize=m_subBlockSize;//DEM�ֿ��С
	theApp.m_DemRightUp_x=theApp.m_DemLeftDown_x+theApp.m_Cell_xwidth*(theApp.m_Dem_cols-1);//DEM���Ͻ�x����
	theApp.m_DemRightUp_y=theApp.m_DemLeftDown_y+theApp.m_Cell_ywidth*(theApp.m_Dem_Rows-1);//DEM���Ͻ�y����
	theApp.m_Dem_BlockWidth=theApp.m_Cell_xwidth*(theApp.m_Dem_BlockSize-1);//DEM�ӿ��ܿ��

	
	SetWindowText("���ڽ�����ģ�ֿ鴦��....");	

	if(theApp.m_Dem_Rows<=BlockSize)//���DEM������С�������õķֿ��С,��DEM�ӿ�������=1
	{
		theApp.m_BlockRows=1;
		m_DEM_Y_neednumber=BlockSize-theApp.m_Dem_Rows;//��Y����(��)��Ҫ�����Ч���ݵ�����
	}
	else  //���DEM���������������õķֿ��С,����DEM�ӿ�������
	{
		if((theApp.m_Dem_Rows-BlockSize) % (BlockSize-1)==0)//���DEM�������Ƿֿ��С��������
		{
			theApp.m_BlockRows=(theApp.m_Dem_Rows-BlockSize) /(BlockSize-1)+1;
			m_DEM_Y_neednumber=0;//��Y�����ϲ���Ҫ�����Ч����
		}
		else
		{
			theApp.m_BlockRows=(theApp.m_Dem_Rows-BlockSize) /(BlockSize-1)+2;//�ֿ�������
			m_DEM_Y_neednumber=theApp.m_BlockRows*(BlockSize-1)+1-theApp.m_Dem_Rows;//��Y����(��)��Ҫ�����Ч���ݵ�����
		}
	}
		
	if(theApp.m_Dem_cols<=BlockSize)//���DEM������С�������õķֿ��С,��DEM�ӿ�������=1
	{
		theApp.m_BlockCols=1;//��DEM�ӿ�������=1
		m_DEM_X_neednumber=BlockSize-theApp.m_Dem_cols;//��Ҫ��x����(��)�����Ч���ݵ�����
	}
	else //���DEM���������������õķֿ��С,����DEM�ӿ�������
	{
		if((theApp.m_Dem_cols-BlockSize) % (BlockSize-1)==0)//���DEM�������Ƿֿ��С��������
		{
			theApp.m_BlockCols=(theApp.m_Dem_cols-BlockSize) /(BlockSize-1)+1;
			m_DEM_X_neednumber=0;//��X�����ϲ���Ҫ�����Ч����
		}
		else
		{
			theApp.m_BlockCols=(theApp.m_Dem_cols-BlockSize) /(BlockSize-1)+2;//�ֿ�������
			m_DEM_X_neednumber=theApp.m_BlockCols*(BlockSize-1)+1-theApp.m_Dem_cols;//��X����(��)��Ҫ�����Ч���ݵ�����
		}
	}
	
	
        //���¶���m_pHeight�����С
		m_pHeight= new float[BlockSize*BlockSize];

		//���ݷֿ�������������������¶���strfiles��Sfiles��С,�����洢ÿ���ӿ����ݵ��ļ���
		strfiles =new CString [theApp.m_BlockRows*theApp.m_BlockCols];		
		Sfiles =new CStdioFile [theApp.m_BlockRows*theApp.m_BlockCols];
		
		//���ݷֿ����������������,������ʱ�ļ�,�����洢�ӿ�����
		for ( i=0;i<theApp.m_BlockRows;i++)
		{
			for ( j=0;j<theApp.m_BlockCols;j++)
			{
				//����ļ���
				tt.Format("%d.txt",j+i*theApp.m_BlockCols+1);
				strfiles[j+i*theApp.m_BlockCols]=tempDemDirctory+"\\block_"+tt;
				//�����ļ�
				Sfiles[j+i*theApp.m_BlockCols].Open (strfiles[j+i*theApp.m_BlockCols],CFile::modeCreate | CFile::modeWrite);
				Sfiles[j+i*theApp.m_BlockCols].Close();//�ر��ļ�
			}
		}
	

	long mto=theApp.m_Dem_Rows*theApp.m_Dem_cols;
	
	int mColsdatanum=0;
	int mCurrentRow,mCurrentCol;
	int m_oldcurrentRow=-1;

	CString *strSaveUpText;
	strSaveUpText= new CString [theApp.m_BlockCols];

	//
	theApp.m_DemHeight= new float[theApp.m_Dem_Rows*theApp.m_Dem_cols];
	
	//���ݷֿ����������������\�ͷֿ��С,��DEM���ݽ����˷ֿ鴦��,������д���Ӧ��DEM�ӿ������ļ���
	for (i=1;i<=theApp.m_Dem_Rows;i++)
	{	
		m_progress.SetPos (i*(100.0/theApp.m_Dem_Rows));		
		if(i<=BlockSize)
			mCurrentRow=1;
		else
		{
			if((i-1)%(BlockSize-1)==0)
				mCurrentRow=(i-1)/(BlockSize-1);
            else
				mCurrentRow=(i-1)/(BlockSize-1)+1;
		}

        if(m_oldcurrentRow!=mCurrentRow)
		{
			if(m_oldcurrentRow>0)
			{
				for ( int k=0;k<theApp.m_BlockCols;k++)
				{
					Sfiles[k+(m_oldcurrentRow-1)*theApp.m_BlockCols].Close();
				}
			}

			for (  int k=0;k<theApp.m_BlockCols;k++)
			{
				Sfiles[k+(mCurrentRow-1)*theApp.m_BlockCols].Open (strfiles[k+(mCurrentRow-1)*theApp.m_BlockCols],CFile::modeCreate |CFile::modeWrite);
			}
		}
	
		stt="";	

		mColsdatanum=0;
		for (j=1;j<=theApp.m_Dem_cols;j++)
		{
			if(j<=BlockSize)
				mCurrentCol=1;
			else
			{
				if((j-1)%(BlockSize-1)==0)
					mCurrentCol=(j-1)/(BlockSize-1);
				else
					mCurrentCol=(j-1)/(BlockSize-1)+1;
			}

			fscanf(fp,"%f ",&hh);  //��ȡ�߳�
			tt.Format("%.3f	",hh);//�߳̾���ȡС�����3λ
			theApp.m_DemHeight[(i-1)*theApp.m_Dem_cols+(j-1)]=hh;
			stt=stt+tt;
			mColsdatanum++;
			if(mColsdatanum % BlockSize==0 || j==theApp.m_Dem_cols )
				{
				if(j==theApp.m_Dem_cols)
				{
				
					//���ڲ���ֿ��С���ӿ�����,����Ч���ݲ���
					int pos=BlockSize-mColsdatanum;
					for(int k=1;k<=pos;k++)
					{
					
						tt.Format("%d",theApp.m_DEM_IvalidValue);
						stt=stt+tt;
					}
				}
				stt=stt+"\n";
			    if(mCurrentRow>1 && m_oldcurrentRow!=mCurrentRow)
				{
					
					Sfiles[(mCurrentRow-1)*theApp.m_BlockCols+mCurrentCol-1].WriteString(strSaveUpText[mCurrentCol-1]);

				}
				Sfiles[(mCurrentRow-1)*theApp.m_BlockCols+mCurrentCol-1].WriteString (stt);
		
                if((i-1)% (BlockSize-1)==0 && (i>1 && i<theApp.m_Dem_Rows)) 
				{
					int ms=(i-1)/(BlockSize-1)*theApp.m_BlockCols+mCurrentCol-1;
					Sfiles[ms].Open(strfiles[ms],CFile::modeCreate |CFile::modeWrite);
				
					Sfiles[ms].WriteString (stt);//������д���ļ�
					Sfiles[ms].Close();
					strSaveUpText[mCurrentCol-1]=stt;
				}
			
				if(mColsdatanum % BlockSize==0) 
				{
					stt=tt;
					mColsdatanum=1;
				}
				else
				{
					stt="";
					if(j<theApp.m_Dem_cols) mColsdatanum=0;
				}
				if(i>=theApp.m_Dem_Rows && j>=theApp.m_Dem_cols)
				{
				
					int pos=m_DEM_Y_neednumber;
					for(int p=1;p<=theApp.m_BlockCols;p++)
					{
						for(int k=1;k<=pos;k++)
						{
							stt="";
							//���ڲ���ֿ��С���ӿ�����,����Ч���ݲ���
							for(int m=1;m<=BlockSize+1;m++)
							{
							
								tt.Format("	%d",theApp.m_DEM_IvalidValue);
								stt=stt+tt;
							}
							stt=stt+"\n";
							Sfiles[theApp.m_BlockCols*theApp.m_BlockRows-(theApp.m_BlockCols-p+1)].WriteString (stt);
						}
					}
					
				}
							
			}
			
		}
		fscanf(fp,"\n");  
		m_oldcurrentRow=mCurrentRow;
	
	}

	//�ر����򿪵���ʱ�ļ�
	for ( int k=0;k<theApp.m_BlockCols;k++)
	{
		Sfiles[k+(theApp.m_BlockRows-1)*theApp.m_BlockCols].Close();
	}

	//д�����ݿ�֮ǰ,��ɾ��dem_block(DEM���ݱ��е�ԭ����������)
	//��Ϊ�˷�ֹ��ͬһ�����ļ����д�����ݿ��е��ظ�д�����
	CString strSql;
	strSql="DELETE FROM dem_block";
	HRESULT hr=theApp.m_pConnection->Execute (_bstr_t(strSql),NULL,adCmdText);
	if(!SUCCEEDED(hr))
	{
		MessageBox("ɾ��ʧ��!","д��DEM���ݵ����ݿ�",MB_ICONSTOP);
		return;
	}
	//���ν��ֿ鲶��DEM�ӿ������ļ�д��oracle���ݿ���
    SetWindowText("����ģ�ֿ�����д�����ݿ�...");	
	for ( i=0;i<theApp.m_BlockRows;i++)
	{
			for ( j=0;j<theApp.m_BlockCols;j++)
			{
				m_progress.SetPos ((i*theApp.m_BlockCols+j+1)*(100.0/(theApp.m_BlockRows*theApp.m_BlockCols)));
				AddDemBlockDataToDB(i+1,j+1,strfiles[i*theApp.m_BlockCols+j],i*theApp.m_BlockCols+j+1);
			}
	}
	
	fclose(fp);  //�ر��ļ�
	
	WriteTotalDemToBlob(strfilename);//��DEM����д��oralce���ݿ���

}



//�õ��ֿ��С
int CDemLoad::GetBlcokSize(int currentSel)
{
	int m=1;
	for(int i=0;i<currentSel;i++)
		m=m*2;
	return m*32+1;
}

//��DEM�ֿ��ļ��ж�ȡ���� 
void CDemLoad::ReadDemDataFromFiles(CString strfiles, int Index)
{
	float hh; 
	int i,j;
    int mCount=theApp.m_Dem_BlockSize;
    FILE *fp=fopen(strfiles,"r");//���ļ�
	
	for( i=0;i<mCount;i++) //�ȱ���DEM�ӿ���С�����������ͬ��(��33��33,65��65�ȵ�)
	{
		for( j=0;j<mCount;j++)
		{
			fscanf(fp,"%f ",&hh);  
			
			m_pHeight[i*mCount+j]=hh;
			
		}
	}
	fclose(fp);//�ر��ļ�
	DeleteFile(strfiles);//ɾ����ʱ�ֿ��ļ�
}

 
//�����С�������ֵ�����ӦDEM���ݵ�ĸ߳�
float CDemLoad::HH(int mRows, int mCols)
{
	return m_pHeight[mRows*theApp.m_Dem_BlockSize+mCols];
}


//��DEM����д��oralce���ݿ���
void CDemLoad::WriteTotalDemToBlob(CString strfile)
{
	CString tt;

	
	tt.Format("INSERT INTO DEM_INFO VALUES(%.3f,%.3f,%d,%d,%d,%d,%d,%d,%d,EMPTY_BLOB(),%d,%d)",\
		theApp.m_DemLeftDown_x,theApp.m_DemLeftDown_y,theApp.m_Cell_xwidth,\
		theApp.m_Cell_ywidth,theApp.m_Dem_BlockSize,theApp.m_BlockRows,\
		theApp.m_BlockCols,theApp.m_Dem_Rows,theApp.m_Dem_cols,1,theApp.m_DEM_IvalidValue);

	myOci.AddNormalDataToDB(tt);//��������������д��oralce���ݿ���
	
	tt.Format("SELECT DEM���� FROM DEM_INFO WHERE ���= :%d FOR UPDATE",1)  ;
	myOci.AddBOLBDataToDB(strfile,tt,1);//��DEM�ֿ��ļ���ΪBLOB������������д��oralce���ݿ���

	
}





















