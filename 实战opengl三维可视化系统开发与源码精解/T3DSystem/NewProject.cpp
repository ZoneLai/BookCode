// NewProject.cpp : implementation file
 

#include "stdafx.h"
 
#include "NewProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CNewProject dialog




CNewProject::CNewProject(CWnd* pParent /*=NULL*/)
	: CDialog(CNewProject::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewProject)
	m_systemname = _T("");
	m_systempassword = _T("");
	m_projectname = _T("");
	m_servername = _T("");
	//}}AFX_DATA_INIT
}


void CNewProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewProject)
	DDX_Text(pDX, IDC_SYSTEM_NAME, m_systemname);
	DDX_Text(pDX, IDC_SYSTEM_PASSWORD, m_systempassword);
	DDX_Text(pDX, IDC_EDIT_PROJECTNAME, m_projectname);
	DDX_Text(pDX, IDC_SYSTEM_SERVERNAME, m_servername);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewProject, CDialog)
	//{{AFX_MSG_MAP(CNewProject)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CNewProject message handlers

BOOL CNewProject::CreateNewProject()
{
	_bstr_t Sql;

	CString strtable[200];//��Ŀ�����ɴ���������

	CString strsql;//���ڴ洢SQL�ַ���
	CString m_username,m_userpassword;	//�洢�´������û���������

	this->UpdateData();//��������

	if(m_projectname.IsEmpty()) //��Ŀ���Ʋ���Ϊ��
	{
		MessageBox("��Ŀ���Ʋ���Ϊ��!","�½���Ŀ",MB_ICONINFORMATION);
		return FALSE; //����
	}
	
	m_username=m_projectname;//�´�����Oracle�û���

	//�´�����Oracle�û�����,�������趨,����ֱ�Ӹ�һ��Ĭ��ֵ,����Ϊ����,
	//������Ŀʱ,�Ͳ���Ҫ������Ŀ������Ϳ���ֱ�Ӵ���Ŀ)
	m_userpassword="a"; //�´�����Oracle�û�����

	theApp.m_username=m_username;//Oracle���ݿ�ϵͳ����Ա�û���
	theApp.m_userpassword=m_userpassword;//Oracle���ݿ�ϵͳ����Ա����
	theApp.m_servername=m_servername;//Oracle���ݿ�ϵͳ����Ա��������
	
	if(FAILED(CoInitialize (NULL)))   //��ʼ��ADO
	{
		MessageBox ("ADO��ʼ��ʧ��!","��¼���ݿ�",MB_ICONERROR);
		return FALSE;
	}
		
	//����m_pConnectionʵ�����
	HRESULT hr = theApp.m_pConnection.CreateInstance("ADODB.Connection");	
	
	if(theApp.m_pConnection->State) //������ݿ��Ѵ�
		theApp.m_pConnection->Close(); //�ر�����
	
	//����SQL�ַ���
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_systemname+";Password="+m_systempassword+";";
	try
	{
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//��Oracleϵͳ����Ա�û�
		if(!SUCCEEDED(hr)) //��ʧ��
		{
			MessageBox("ϵͳ����Ա���ݿ�����ʧ��!","��¼���ݿ�",MB_ICONINFORMATION);
			return FALSE;	//����
		}
	}
	catch(_com_error& e)	//������
	{
		CString errormessage;
		errormessage.Format("������Ϣ:%s",e.ErrorMessage());
		errormessage="ϵͳ����Ա�û���������������������!";
		MessageBox(errormessage,"��¼���ݿ�",MB_ICONINFORMATION);//�������������Ϣ
		return FALSE;	//����
	} 
 
    //����һ�����û��� ���ڴ洢��������Ŀ����
	CString tname,tpass;
	tname="RW3D";	//�趨���û�����(�������û���)
	tpass="aaa";	//�趨���û�����(����������)
	strsql.Format("SELECT * FROM dba_users WHERE  username='%s'",tname);
	theApp.m_pRecordset.CreateInstance(_uuidof(Recordset));

	//��Oracle��dba_users����ѡȡ�Ƿ������趨���û�
	theApp.m_pRecordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	if(theApp.m_pRecordset->adoEOF) //���û�и��û�,�򴴽�
	{
		theApp.m_pRecordset->Close();//�رձ�
		strsql = "CREATE USER  " + tname + "  IDENTIFIED BY   " + tpass;
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//�����趨���û�
		
		strsql = "GRANT CREATE SESSION,CREATE TABLE ,UNLIMITED TABLESPACE ,DBA to " + tname;
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//���䴴�����Ȩ��
		theApp.m_pConnection->Close();//�ر����ݿ�����
		
		strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+tname+";Password="+tpass+";";
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//�����´������û�
		strsql= "CREATE TABLE Project(��Ŀ���� VARCHAR2(50),����ʱ�� VARCHAR2(20))";
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//���´������û��´�����Project
		theApp.m_pConnection->Close();//�ر����ݿ�����
	
		//��������Oracleϵͳ����Ա�û�
		strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_systemname+";Password="+m_systempassword+";";
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);
	}
	else //����洢��Ŀ���Ƶ��û��Ѿ�����,�Ͳ�����Ҫ������(��ֻ�ǵ�һ���½���Ŀʱ,�ᴴ���洢��Ŀ���Ƶ��û������ݱ�)
		theApp.m_pRecordset->Close(); //�رռ�¼��

	
   //������Ŀ(������Ŀ���ƴ���Oracle���û�)
	strsql = "CREATE USER  " + m_username + "  IDENTIFIED BY   " + m_userpassword;
	try
	{
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//����Oracle���û�
		if(!SUCCEEDED(hr)) //�������ʧ��
		{
			MessageBox("��Ŀ����ʧ��!","��������Ŀ",MB_ICONINFORMATION);
			return FALSE;	//����
		}

		//Ϊ������Ŀ�����û����䴴������(CREATE SESSION,),������(CREATE TABLE),
		//�����Ʊ�ռ�(UNLIMITED TABLESPACE)��Ȩ��
		strsql = "GRANT CREATE SESSION,CREATE TABLE ,UNLIMITED TABLESPACE to " + m_username;
		hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);
		if(!SUCCEEDED(hr))//���Ȩ�޸�ֵʧ��
		{
			MessageBox("Ȩ�޸�ֵʧ��!","��������Ŀ",MB_ICONINFORMATION);
			return FALSE;//����
		}
		theApp.m_pConnection->Close();//�رռ�¼��
	} 		

	catch(_com_error& e)	//������
	{
		CString errormessage;
		
		if(e.WCode()==3092) //�����Ŀ�Ѿ�����
		{
			errormessage="��Ŀ "+m_username+" �Ѿ�����,�Ƿ�ɾ��?";	
			int nanswer=MessageBox(errormessage,"��������Ŀ",MB_ICONINFORMATION|MB_YESNO);
			if(nanswer==6)	//ɾ��������Ŀ
			{
				strsql="Drop user "+m_username+"  cascade";
				hr =theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//ɾ��������Ŀ
				if(!SUCCEEDED(hr))	//���ɾ����Ŀʧ��
					MessageBox("ɾ����Ŀʧ��","ɾ����Ŀ",MB_ICONINFORMATION);
				else
					MessageBox("ɾ����Ŀ���","ɾ����Ŀ",MB_ICONINFORMATION);
				
			}
		}
		
		else	//����������Ϣ
		{
			errormessage.Format("������Ϣ:%s",e.ErrorMessage());
			MessageBox(errormessage,"��������Ŀ",MB_ICONINFORMATION);
		}
		return FALSE;	//����
	} 

	//���Ӹ�����Ŀ���ƴ��������û�
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_username+";Password="+m_userpassword+";";
	try
	{
		hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//���Ӹ�����Ŀ���ƴ��������û�
		if(!SUCCEEDED(hr))//����������û�ʧ��
		{
			MessageBox("���ݿ�����ʧ��!","��������Ŀ",MB_ICONINFORMATION);
			return FALSE;	//����
		}
	    	
	}
	catch(_com_error& e)	//������
	{
		CString errormessage;
		WORD nWcode=e.WCode(); 
		if(e.WCode()==0) //��Ŀ��������
		{	errormessage="��Ŀ��������!";
			MessageBox(errormessage,"��������Ŀ",MB_ICONINFORMATION);
			return FALSE;	//����
		}
		else	//����������Ϣ
		{	
			errormessage.Format("������Ϣ:%s",e.ErrorMessage());
			MessageBox(errormessage,"��������Ŀ",MB_ICONINFORMATION);
			return FALSE; 	//����
		}
	} 

	//�������Ϊ�ڸ�����Ŀ���ƴ��������û��´������ݱ���DEM���ݱ�,Ӱ�����ݱ��
	int index=-1;

	//1.DEM������Ϣ��
	index++;
	strtable[index]= "CREATE TABLE DEM_INFO(DEM�������X NUMBER(10,3),\
		DEM�������Y NUMBER(10,3),�������X NUMBER(3),\
		�������Y NUMBER(3),DEM�ֿ��С NUMBER(3),\
		DEM�ֿ����� NUMBER(6),DEM�ֿ����� NUMBER(6),\
		ԭʼDEM���� NUMBER(10),ԭʼDEM���� NUMBER(10),\
		DEM���� BLOB,��� NUMBER(2),��ЧDEMֵ NUMBER(10))";	
	

	//2.DEM�����ӿ����ݱ�
	index++;
	strtable[index]= "CREATE TABLE dem_block(�к� NUMBER(6),\
			�к� NUMBER(6),DEM���� BLOB,��� NUMBER(6),\
			��������X NUMBER(10,3),��������Y NUMBER(10,3))";	

	//3.DEM�����ӿ���Ϣ��
	index++;
	strtable[index]= "CREATE TABLE dem_subblock(�к� NUMBER(6),\
		�к� NUMBER(6),DEM���� BLOB,������� NUMBER(6),��� NUMBER(6))";	
			
	//4.Ӱ�������
	index++;
	strtable[index]= "CREATE TABLE texture(�к� NUMBER(6),\
		  �к� NUMBER(6),���� NUMBER(6),��� NUMBER(6),\
		  ������������ NUMBER(6),�������� BLOB,��� NUMBER(6),\
		  ���½�����X NUMBER(10,3),���½�����Y NUMBER(10,3),\
		  ���Ͻ�����X NUMBER(10,3),���Ͻ�����Y NUMBER(10,3))";	
				
	//5.Ӱ��LOD��Ϣ��
	index++;
	strtable[index]= "CREATE TABLE IMAGERECT_INFO(���½�����X NUMBER(10,3),\
		 ���½�����Y NUMBER(10,3),���Ͻ�����X NUMBER(10,3),\
		 ���Ͻ�����Y NUMBER(10,3),Ӱ����������� NUMBER(2),\
		 һ��Ӱ��ֱ��� NUMBER(6,2),����Ӱ��ֱ��� NUMBER(6,2),\
		 ����Ӱ��ֱ��� NUMBER(6,2),\
		 �ļ�Ӱ��ֱ��� NUMBER(6,2),�弶Ӱ��ֱ��� NUMBER(6,2))";

	index++;
	
	//6.��Ŀ�������ݱ�
	strtable[index]= "CREATE TABLE Scheme (\
		 �������� VARCHAR2(100), ��Ƶȼ� VARCHAR2(20),\
		 ǣ������ VARCHAR2(10),�������� VARCHAR2(50),������ʽ VARCHAR2(50),\
		 ���εر� VARCHAR2(12), �������� VARCHAR2(20),����ٶ� NUMBER(6),\
		 ��С���߰뾶 NUMBER(6),��������Ч���� NUMBER(6),\
		 ��С�³� NUMBER(6,2),����¶� NUMBER(6,2),����¶Ȳ� NUMBER(6,2),\
		 ������ NUMBER(20,3),�յ���� NUMBER(20,3))";
	
	index++;
	strtable[index]= "CREATE TABLE T3DLineZxCorrdinate (\
		  �������� VARCHAR2(100),��� NUMBER(10), x���� NUMBER(20,3),\
		  y���� NUMBER(20,3),z���� NUMBER(20,3),�������� VARCHAR2(30),\
		  ����߳� NUMBER(20,3),���ڸ� NUMBER(20,3),��� NUMBER(20,3))";
	

	index++;
	strtable[index]= "CREATE TABLE Scheme_plane_CureveData (\
		  �������� VARCHAR2(100),������ VARCHAR2(50),\
		  ת�� NUMBER(10,3),��λ��1 NUMBER(10,3),��λ��2 NUMBER(10,3),\
		  ת�� NUMBER(2),�������߳�  NUMBER(6),\
		  ���߳� NUMBER(15,3),���߳� NUMBER(15,3),\
		  Բ���߳� NUMBER(15,3),ֱ������� NUMBER(20,3),\
		  ��Բ����� NUMBER(20,3),Բ������� NUMBER(20,3),\
		  ��ֱ����� NUMBER(20,3),��ʸ�� NUMBER(10,3),\
		  ���ƾ� NUMBER(10,3),���߰뾶 NUMBER(10),\
		  ������� NUMBER(20,3),����x���� NUMBER(20,3),\
		  ����y���� NUMBER(20,3),����z���� NUMBER(20,3),\
		  ������� NUMBER(10))";
	
	index++;
	strtable[index]= "CREATE TABLE Scheme_plane_CureveData_XY (\
		 �������� VARCHAR2(100),������ VARCHAR2(50),\
		 Բ��x���� NUMBER(20,3),Բ��y���� NUMBER(20,3),\
		 ֱ��x���� NUMBER(20,3),ֱ��y���� NUMBER(20,3),\
		 ��Բx���� NUMBER(20,3),��Բy���� NUMBER(20,3),\
		 Բ��x���� NUMBER(20,3),Բ��y���� NUMBER(20,3),\
		 ��ֱx���� NUMBER(20,3),��ֱy���� NUMBER(20,3),\
		 ������� NUMBER(10))";
	

	index++;
	strtable[index]= "CREATE TABLE PriorityRadius (\
		�г��ٶ� NUMBER(4), ���߰뾶��Сֵ NUMBER(6),\
		���߰뾶���ֵ NUMBER(6))";
	
	index++;
	strtable[index]= "CREATE TABLE MinRadius (\
		�г��ٶ� NUMBER(4), һ��ض� NUMBER(6),\
		���ѵض� NUMBER(6))";
	
	index++;
	strtable[index]= "CREATE TABLE T3DLineZxCorrdinateZDM (\
		 �������� VARCHAR2(100),��� NUMBER(10), x���� NUMBER(20,3),\
		 y���� NUMBER(20,3),z���� NUMBER(20,3),�������� VARCHAR2(30),\
		 ����߳� NUMBER(20,3),���ڸ� NUMBER(20,3),���\
		 NUMBER(20,3),������� NUMBER(20,3))";
	
	
	index++;
	strtable[index]= "CREATE TABLE ZDmJDCurve (\
		 �������� VARCHAR2(100), �³� NUMBER(20,3),\
		 ���� NUMBER(20,3),���µ�׮�� NUMBER(20,3),��� VARCHAR2(30),\
		 �����߰뾶 NUMBER(20,3),��ʸ�� NUMBER(20,3),���߳� NUMBER(20,3),\
		 �¶ȴ����� NUMBER(20,3),��� NUMBER(10),ת������ NUMBER(2),\
		 ֱ������� NUMBER(20,3),ֱ������ NUMBER(20,3),\
		 ��ֱ����� NUMBER(20,3),��ֱ���� NUMBER(20,3))";
	index++;
	strtable[index]= "CREATE TABLE zdmSegmentGeoFeature (\
		   �ֶ���ʼ��� NUMBER(10,3),�ֶ��յ���� NUMBER(10,3),\
		   ���̵������� VARCHAR2(2000),�������� VARCHAR2(100))";
	
	index++;
	strtable[index]= "CREATE TABLE Tunnel (\
			 ������� VARCHAR2(400),��������� NUMBER(20,3),\
			 ����յ���� NUMBER(20,3), ������� NUMBER(20,3),�������� VARCHAR2(200))";

	index++;
	strtable[index]= "CREATE TABLE Bridge (\
		 �������� VARCHAR2(400),���������� NUMBER(20,3),\
		 �����յ���� NUMBER(20,3), �������� NUMBER(20,3),\
		 �������� VARCHAR2(200))";

	index++;
	strtable[index]= "CREATE TABLE StationTable (\
		��վ���� VARCHAR2(200),��վ���� VARCHAR2(50),\
		��� NUMBER(20,3), �������� VARCHAR2(200))";

	/*
		�����Լ�����������Ҫ�����ݱ�
	*/

	//�����������ݱ�
	for(int i=0;i<=index;i++)
	{

		HRESULT hr=theApp.m_pConnection->Execute (_bstr_t(strtable[i]),NULL,adCmdText);//������
		if(!SUCCEEDED(hr)) //�������ʧ��,��ɾ��������Ŀ�����´������û�
		{
			MessageBox("����ʧ��!","��¼���ݿ�",MB_ICONINFORMATION);
			strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_systemname+";Password="+m_systempassword+";";
			hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//��������Oracleϵͳ����Ա�û�
			strsql = "DROP USER  " + m_username + "  CASCADE   " ;
			hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//ɾ���´������û�			
			return FALSE;

		}
	}
	theApp.m_pConnection->Close();//�ر����ݿ�����

	
	
	//�����ڴ洢��������Ŀ���Ƶ��û�
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+tname+";Password="+tpass+";";
	hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);
	if(!SUCCEEDED(hr))//��ʧ��
	{
		MessageBox("���ݿ�򿪴���!");
	}
	//����õ���Ŀ���������ں�ʱ����Ϣ
	CString stt;
	CTime time = CTime::GetCurrentTime();   
	int m_nYear = time.GetYear();     
	int m_nMonth = time.GetMonth();     
	int m_nDay = time.GetDay();     
	int m_nHour = time.GetHour();     
	int m_nMinute = time.GetMinute();   
	int m_nSecond = time.GetSecond();   
	stt.Format("%4d-%2d-%2d",m_nYear,m_nMonth,m_nDay);
	strsql.Format("INSERT INTO Project VALUES('%s','%s')",m_username,stt);
	hr=theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);//����Ŀ���������ں�ʱ����Ϣд��Project����
	theApp.m_pConnection->Close();//�ر����ݿ�����
	
	//�������Ӹ�����Ŀ���ƴ��������û�
	strsql="Provider=OraOLEDB.Oracle;Data Source="+m_servername+";User Id="+m_username+";Password="+m_userpassword+";";
	hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);	//�������ݿ�
	theApp.bLoginSucceed=TRUE; //���ݿ��¼�ɹ�
	MessageBox("��Ŀ�����ɹ�!","��������Ŀ",MB_ICONINFORMATION);
	
	return TRUE;
}

BOOL CNewProject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_servername="test";
	m_systemname="system";
	m_systempassword="manager";
	this->UpdateData(FALSE);
	
	return TRUE;  
}

//ȷ��
void CNewProject::OnOK() 
{
	BeginWaitCursor();//������л�Ϊ�ȴ����
	if(CreateNewProject()==TRUE) //��������Ŀ
	{
		EndWaitCursor();//������л�ΪĬ�Ϲ��,�����ȴ�
		CDialog::OnOK();//����
	}
	else
	{
		EndWaitCursor();//������л�ΪĬ�Ϲ��,�����ȴ�
	}
	
}
