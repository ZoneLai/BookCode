// OpenProject.cpp : implementation file
 

#include "stdafx.h"
#include "MainFrm.h"
#include "OpenProject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// COpenProject dialog




COpenProject::COpenProject(CWnd* pParent /*=NULL*/)
	: CDialog(COpenProject::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenProject)
	//}}AFX_DATA_INIT
}


void COpenProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenProject)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenProject, CDialog)
	//{{AFX_MSG_MAP(COpenProject)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, OnButtonOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// COpenProject message handlers

BOOL COpenProject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitListCtrl();//��ʼ�� ListCtrl�ؼ�
	
	LoadData();//�����ݿ���м�����Ŀ����
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//�����ݿ���м�����Ŀ����
void COpenProject::LoadData()
{
	CString strsql;

	//�Ӵ洢��Ŀ���ơ��������ڵ�Oralce�û�RW3D�ж�ȡ������Ŀ��Ϣ
	strsql="Provider=OraOLEDB.Oracle;User Id=RW3D;Password=aaa;";	//����SQL�ַ���	
	try
	{
		HRESULT hr =m_Connection->Open(_bstr_t(strsql),"","",-1);//�����ݿ�
		if(!SUCCEEDED(hr)) //�����ʧ��
		{
			MessageBox("���ݿ�����ʧ��!","����Ŀ",MB_ICONINFORMATION);
			return ;//����
		}
	}
	catch(_com_error& e)	//������
	{
		CString errormessage;
		errormessage.Format("������Ϣ:%s",e.ErrorMessage());
		MessageBox("���ݿ�����ʧ��!","����Ŀ�ļ�",MB_ICONINFORMATION|MB_OK);
		return ;//����
	} 
	
	//����Ŀ��������Ϊ�����Project�ж�ȡ������Ŀ��Ϣ
	strsql="select  *   from  Project ORDER BY ����ʱ��  ASC";  //����SQL�ַ���	
	try
	{
		//�����ݱ�
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(m_Connection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//������
	{
		CString errormessage;
		errormessage.Format("�����ݿ��ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"װ������",MB_ICONSTOP);
		return;
	} 
	
	//ɾ����������
	m_list.DeleteAllItems();
	mtotalProjects=0;//����Ŀ����ʼֵ=0
	
    CString tt[3];
	while(!m_Recordset->adoEOF)//���û�е���¼��β
	{    
		Thevalue = m_Recordset->GetCollect("��Ŀ����"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt[1]=Thevalue.bstrVal;//��Ŀ����
		}
	
		Thevalue = m_Recordset->GetCollect("����ʱ��"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt[2]=Thevalue.bstrVal;//����ʱ��
		}

		tt[0].Format("%d",mtotalProjects+1);//���

		//����Ŀ����,����ʱ����Ϣд��ListCtrl�ؼ���
		m_list.InsertItem(mtotalProjects,tt[0]);      //���
		m_list.SetItemText(mtotalProjects,1,tt[1]);   //��Ŀ����
		m_list.SetItemText(mtotalProjects,2,tt[2]);	//��Ŀ����ʱ��
		
		mtotalProjects++;//����Ŀ��+1

		m_Recordset->MoveNext();//��¼��ָ������
	}  

	m_Recordset->Close();  //�رռ�¼��
	m_Connection->Close();//�ر����ݿ�
	
	
}

//����ListCtrl�ؼ���Ӧ����,�����õ�ѡ�����Ŀ����
void COpenProject::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	NMLISTVIEW    *pNMListView = (NMLISTVIEW    *)pNMHDR;
	
	if(pNMListView->iItem >= 0) //���ѡ��
    {
        m_nCurrentItem = pNMListView->iItem;//������Ŀ������
        m_nCurrentSubItem = pNMListView->iSubItem;
		m_strProjectname=m_list.GetItemText(m_nCurrentItem,1);//�õ�ѡ�����Ŀ����
    }
	*pResult = 0;
}


//����Ŀ
void COpenProject::OnButtonOpen() 
{
	CString strsql;

	if(mtotalProjects<=0)	
	{
		MessageBox("û����Ŀ��","����Ŀ",MB_ICONINFORMATION|MB_OK);
		return;
	}
	
	if(m_nCurrentItem<0)	
	{
		MessageBox("��ѡ��Ҫ�򿪵���Ŀ��","����Ŀ",MB_ICONINFORMATION|MB_OK);
		return;
	}
	
	if(	m_strProjectname.IsEmpty())
		return;
	
	BeginWaitCursor();

	
	theApp.m_username=m_strProjectname;
	theApp.m_userpassword="a";
	m_currentSchemeNames=m_strProjectname;
	
	if(theApp.m_pConnection->State) //������ݿ��Ѵ�
		theApp.m_pConnection->Close(); //�ر�����
	
	strsql="Provider=OraOLEDB.Oracle;User Id="+theApp.m_username+";Password="+theApp.m_userpassword+";";
	try
	{
		HRESULT hr =theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);
		if(!SUCCEEDED(hr))
		{
			MessageBox("���ݿ�����ʧ��!","����Ŀ",MB_ICONINFORMATION);
			theApp.m_pConnection->Close();//�ر����ݿ�����
			return ;
		}
	}
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"����Ŀ",MB_ICONINFORMATION);
		theApp.m_pConnection->Close();//�ر����ݿ�����
		return ;
	} 

	
	//����SQL�ַ���
	strsql="select *  from DEM_INFO ";  
	if(m_Recordset->State)	//���m_Recordset�Ѵ򿪣��ȹر�
		m_Recordset->Close();
	
	try
	{
		//�� DEM_INFO���ݱ�,��ȡDEM�����Ϣ
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//������
	{
		CString errormessage;
		errormessage.Format("�����ݿ��ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"װ������",MB_ICONSTOP);
		m_Recordset->Close();
		return ;
	} 
 
    if(!m_Recordset->adoEOF)//���û�е���¼��ĩβ,��ʾ�м�¼
	{
		Thevalue = m_Recordset->GetCollect("DEM�������X"); 
		theApp.m_DemLeftDown_x=(double)Thevalue;//DEM���½�x����

		Thevalue = m_Recordset->GetCollect("DEM�������Y"); 
		theApp.m_DemLeftDown_y=(double)Thevalue;//DEM���½�y����

	
		Thevalue = m_Recordset->GetCollect("�������X"); 	
		theApp.m_Cell_xwidth=(long)Thevalue ;//DEM��x�����ϸ�������

		Thevalue = m_Recordset->GetCollect("�������Y"); 
		theApp.m_Cell_ywidth=(long)Thevalue;//DEM��y�����ϸ�������
		
		Thevalue = m_Recordset->GetCollect("DEM�ֿ��С"); 
		theApp.m_Dem_BlockSize=(long)Thevalue;//DEM�ֿ��С,��һ�������ӿ�Ĵ�С

		Thevalue = m_Recordset->GetCollect("DEM�ֿ�����"); 
		theApp.m_BlockRows=(long)Thevalue;//DEM�ֿ��������

		Thevalue = m_Recordset->GetCollect("DEM�ֿ�����"); 
		theApp.m_BlockCols=(long)Thevalue;//DEM�ֿ��������
		
		Thevalue = m_Recordset->GetCollect("ԭʼDEM����"); 
		theApp.m_Dem_Rows=(long)Thevalue;//DEM���ݺ�������
 
		Thevalue = m_Recordset->GetCollect("ԭʼDEM����"); 
		theApp.m_Dem_cols=(long)Thevalue;//DEM���ݺ�������
		
		Thevalue = m_Recordset->GetCollect("��ЧDEMֵ"); 
		theApp.m_DEM_IvalidValue=(long)Thevalue;//��ЧDEM���ݵ�߳�ֵ
		
		//DEM�����ӿ�Ŀ��(��һ�����ο��ʾ���ٿռ����,���ֿ��С=33,
		//DEM��x�����ϸ�������=20,��DEM�����ӿ���=20*32=640��)
		theApp.m_Dem_BlockWidth=theApp.m_Cell_xwidth*(theApp.m_Dem_BlockSize-1);
		
		m_Recordset->Close();//�رռ�¼��
	
		//DEM���Ͻ�x����
		theApp.m_DemRightUp_x=theApp.m_DemLeftDown_x+theApp.m_Cell_xwidth*(theApp.m_Dem_cols-1);
		//DEM���Ͻ�y����
		theApp.m_DemRightUp_y=theApp.m_DemLeftDown_y+theApp.m_Cell_ywidth*(theApp.m_Dem_Rows-1);

	}
	else
	{
		m_Recordset->Close();//�رռ�¼��
		MessageBox("��Ŀû����ģ����!","����Ŀ",MB_ICONINFORMATION);
		return ;	//����
	}


	//����SQL�ַ���
	strsql="select *  from IMAGERECT_INFO ";  
	try
	{
		//�� IMAGERECT_INFO���ݱ�,��ȡӰ�����������Ϣ
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//������
	{
		CString errormessage;
		errormessage.Format("�����ݿ��ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"װ������",MB_ICONSTOP);
		m_Recordset->Close();//�رռ�¼��
		return ;	//����
	} 
	
	
	if(!m_Recordset->adoEOF)	//���û�е���¼��ĩβ,��ʾ�м�¼
	{
		Thevalue = m_Recordset->GetCollect("���½�����X"); 
		theApp.m_TexturLeftDown_x=(double)Thevalue;//�������½�x����
		
		Thevalue = m_Recordset->GetCollect("���½�����Y"); 
		theApp.m_TexturLeftDown_y=(double)Thevalue;//�������½�y����
		
		Thevalue = m_Recordset->GetCollect("���Ͻ�����X"); 
		theApp.m_TexturRightUp_x=(double)Thevalue ;//�������Ͻ�x����
		
		Thevalue = m_Recordset->GetCollect("���Ͻ�����Y"); 
		theApp.m_TexturRightUp_y=(double)Thevalue;//�������Ͻ�y����
		
		Thevalue = m_Recordset->GetCollect("Ӱ�����������"); 
		theApp.m_ImagePyramidCount=(long)Thevalue;//����Ӱ�����������,������LOD����
	
		Thevalue = m_Recordset->GetCollect("һ��Ӱ��ֱ���"); 
		theApp.m_ImageResolution[1]=(float)Thevalue;//����Ӱ��һ��Ӱ��ֱ���

		Thevalue = m_Recordset->GetCollect("����Ӱ��ֱ���"); 
		theApp.m_ImageResolution[2]=(float)Thevalue;//����Ӱ�����Ӱ��ֱ���

		Thevalue = m_Recordset->GetCollect("����Ӱ��ֱ���"); 
		theApp.m_ImageResolution[3]=(float)Thevalue;//����Ӱ������Ӱ��ֱ���
	
		Thevalue = m_Recordset->GetCollect("�ļ�Ӱ��ֱ���"); 
		theApp.m_ImageResolution[4]=(float)Thevalue;//����Ӱ���ļ�Ӱ��ֱ���
	
		Thevalue = m_Recordset->GetCollect("�弶Ӱ��ֱ���"); 
		theApp.m_ImageResolution[5]=(float)Thevalue;//����Ӱ���弶Ӱ��ֱ���

		m_Recordset->Close();//�رռ�¼��
		
	}
	else
	{
		m_Recordset->Close();//�رռ�¼��
	}
   
  	
	
	theApp.bLoginSucceed=TRUE;//���ݼ��سɹ�
	myOci.Init_OCI();//��ʼ��OCI
	
	//����SQL�ַ���	
	strsql.Format("select * from Scheme ORDER BY �������� ASC");
	if(m_Recordset->State)
		m_Recordset->Close();
	try
	{
		//�� Scheme���ݱ�,��ȡ�򿪷����������Ϣ
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)		//������
	{
		CString errormessage;
		errormessage.Format("�����ݿ��ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"�����ݿ��",MB_ICONINFORMATION);
		m_Recordset->Close();//�رռ�¼��
		return  ;//����
	} 	
	
	//GetCollect():Ado��ȡ���ݿ��ֶ�ֵ����
	m_SchemeNames.RemoveAll(); //��գ��洢�������Ƶ�ȫ������
	int index=0; //��ȡ������Ϣ
	while(!m_Recordset->adoEOF)
	{
	
		Thevalue = m_Recordset->GetCollect("��������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].Schemename=Thevalue.bstrVal;//��������
			m_SchemeNames.Add(myDesingScheme.SchemeDatass[index].Schemename);//�洢�������Ƶ�ȫ������
		}

		Thevalue = m_Recordset->GetCollect("��Ƶȼ�");
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDesigngrade=Thevalue.bstrVal;//��Ƶȼ�
			
		}
		
		Thevalue = m_Recordset->GetCollect("ǣ������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDraughtstyle=Thevalue.bstrVal;//ǣ������
		}
		

		Thevalue = m_Recordset->GetCollect("��������"); //��������
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strBlocomotiveStyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("������ʽ"); //������ʽ
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strCBbsStyle=Thevalue.bstrVal;
		}

		Thevalue = m_Recordset->GetCollect("���εر�");  //���εر�
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strTerrainstyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("��������"); //��������
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strEngineeringcondition=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("����ٶ�"); //����ٶ�
		myDesingScheme.SchemeDatass[index].designspeed=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("��С���߰뾶"); //��С���߰뾶
		myDesingScheme.SchemeDatass[index].minRadius=(long)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("��������Ч����"); //��������Ч����
		myDesingScheme.SchemeDatass[index].dxfLength=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("��С�³�"); //��С�³�
		myDesingScheme.SchemeDatass[index].minSlopeLength=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("����¶�"); //����¶�
		myDesingScheme.SchemeDatass[index].maxSlope=(double)Thevalue;		
	
		Thevalue = m_Recordset->GetCollect("����¶Ȳ�"); //����¶Ȳ�
		myDesingScheme.SchemeDatass[index].maxSlopePddsc=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("������"); //������
		myDesingScheme.SchemeDatass[index].StartLC=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("�յ����"); //�յ����
		myDesingScheme.SchemeDatass[index].EndLC=(double)Thevalue;		
		
		index++;	
		m_Recordset->MoveNext();//��¼��ָ������

	}
	m_Recordset->Close();//�رռ�¼��
	if(m_SchemeNames.GetSize()>0)
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrame->AddSchemeName();
	}
	MessageBox("����Ŀ�ɹ�!","����Ŀ",MB_ICONINFORMATION);
    EndWaitCursor();//������л�ΪĬ�Ϲ��,�����ȴ�
	EndDialog(IDOK);
}


//ɾ����Ŀ
void COpenProject::OnButtonDelete() 
{
	HRESULT hr;
	CString trsql;
	
	
	if(mtotalProjects<=0)	//�����Ŀ������<=0����ʾ��û�н�����Ŀ������ɾ�� 
	{
		MessageBox("û����Ŀ��","ɾ����Ŀ",MB_ICONINFORMATION|MB_OK);
		return;
	}

	if(m_nCurrentItem<0)	//���û��ѡ��ListCtrl�ؼ�����Ŀ������
	{
		MessageBox("��ѡ��Ҫɾ������Ŀ��","ɾ����Ŀ",MB_ICONINFORMATION|MB_OK);
		return;
	}

	//��ǰ����Ŀ����ɾ��
	if(strcmp(theApp.m_username,m_strProjectname)==0)
	{
		MessageBox("��ǰ����ĿΪ"+m_strProjectname+",����ɾ��!","ɾ����Ŀ",MB_ICONSTOP|MB_OK);
		return;
	}

	//���m_Connection�Ѵ�������״̬���ȹرգ������ٴ�����ʱ������
	if(m_Connection->State)
		m_Connection->Close();
	
	BeginWaitCursor();//���ñ�������ʾɳ©���,�����û�ϵͳæ
	
	//����SQL�ַ���
	CString strsql="Provider=OraOLEDB.Oracle;User Id=RW3D;Password=aaa;";
	try
	{
		hr =m_Connection->Open(_bstr_t(strsql),"","",-1);//���Ӵ洢��Ŀ���ơ��������ڵ�Oralce�û�RW3D
		
		if(!SUCCEEDED(hr))//������ݿ�����ʧ��
		{
			MessageBox("���ݿ�����ʧ��!","ɾ����Ŀ",MB_ICONINFORMATION);
			m_Connection->Close();//�ر�����
			EndWaitCursor();//����ɳ©���,���ָ���ǰ�Ĺ��
			return ;//����
		}
	}
	catch(_com_error& e)	//������
	{
		CString errormessage;
		errormessage.Format("������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"ɾ����Ŀ",MB_ICONINFORMATION);
		m_Connection->Close();//�ر�����
		EndWaitCursor();//����ɳ©���,���ָ���ǰ�Ĺ��
		return ;//����
	} 
 
	int manwer=MessageBox("�Ƿ�ɾ����Ŀ?","ɾ����Ŀ",MB_ICONINFORMATION|MB_YESNO);
	if(manwer==7)//�����ɾ����Ŀ������
		return ;

//	drop tablespace XXXX INCLUDING CONTENTS; 
//	drop user XXXX cascade;
//	Oracle��drop user��drop user cascade������
//		drop user �� ������ɾ���û���
//		drop user ����  cascade ����ɾ�����û����µ����б����ͼ���Ӳ�������Ϊ��ɾ������û��µ����ж���! 

	//����SQL�ַ���
//	strsql="Provider=OraOLEDB.Oracle;Data Source="+theApp.m_servername+";User Id="+theApp.m_systemname+";Password="+theApp.m_userpassword+";";
//	theApp.m_pConnection->Open(_bstr_t(strsql),"","",-1);//��Oracleϵͳ����Ա�û�
//	strsql="Drop user "+m_strProjectname+"  cascade";
//	theApp.m_pConnection->Execute (_bstr_t(strsql),NULL,adCmdText);

	
	//����SQL�ַ���,(ɾ���û�)
	//ɾ����Ŀ�û��ʹ��û����µ����б����ͼ(���� cascade����Ϊ��ɾ������û��µ����ж���!)
	strsql="Drop user "+m_strProjectname+"  cascade";
	try
	{
		hr =m_Connection->Execute (_bstr_t(strsql),NULL,adCmdText);//ɾ����Ŀ
		if(!SUCCEEDED(hr))
		{
			MessageBox("ɾ����Ŀʧ��!","ɾ����Ŀ",MB_ICONINFORMATION);
			m_Connection->Close();//�ر�����
			EndWaitCursor();//����ɳ©���,���ָ���ǰ�Ĺ��
			return ;//����
		}
	}
	catch(_com_error& e)	//������
	{
		CString errormessage;
		errormessage.Format("������Ϣ:%s",e.ErrorMessage());
		m_Connection->Close();//�ر�����
		MessageBox(errormessage,"ɾ����Ŀ",MB_ICONINFORMATION);
		EndWaitCursor();//����ɳ©���,���ָ���ǰ�Ĺ��
		return ;//����
	} 

	strsql.Format("Delete  from Project WHERE ��Ŀ����='%s'",m_strProjectname);
	hr =m_Connection->Execute (_bstr_t(strsql),NULL,adCmdText);
	m_Connection->Close();//�ر�����
	
	MessageBox("��Ŀɾ���ɹ�!","ɾ����Ŀ",MB_ICONINFORMATION);

	m_nCurrentItem=-1; //�ָ�Ϊѡ��״̬
	LoadData(); //���¼�����Ŀ����
	EndWaitCursor();//����ɳ©���,���ָ���ǰ�Ĺ��
	
}



//����Ŀ
BOOL  COpenProject::OpenProjects(int NewOrOpen)
{
	CString strsql;

	
	BeginWaitCursor();
	
	//����SQL�ַ���
	strsql="select *  from DEM_INFO ";  
	if(m_Recordset->State)	//���m_Recordset�Ѵ򿪣��ȹر�
		m_Recordset->Close();
	
	try
	{
		//�� DEM_INFO���ݱ�,��ȡDEM�����Ϣ
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//������
	{
		CString errormessage;
		errormessage.Format("�����ݿ��ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"װ������",MB_ICONSTOP);
		return FALSE;
	} 
 
    if(!m_Recordset->adoEOF)//���û�е���¼��ĩβ,��ʾ�м�¼
	{
		Thevalue = m_Recordset->GetCollect("DEM�������X"); 
		theApp.m_DemLeftDown_x=(double)Thevalue;//DEM���½�x����

		Thevalue = m_Recordset->GetCollect("DEM�������Y"); 
		theApp.m_DemLeftDown_y=(double)Thevalue;//DEM���½�y����

	
		Thevalue = m_Recordset->GetCollect("�������X"); 	
		theApp.m_Cell_xwidth=(long)Thevalue ;//DEM��x�����ϸ�������

		Thevalue = m_Recordset->GetCollect("�������Y"); 
		theApp.m_Cell_ywidth=(long)Thevalue;//DEM��y�����ϸ�������
		
		Thevalue = m_Recordset->GetCollect("DEM�ֿ��С"); 
		theApp.m_Dem_BlockSize=(long)Thevalue;//DEM�ֿ��С,��һ�������ӿ�Ĵ�С

		Thevalue = m_Recordset->GetCollect("DEM�ֿ�����"); 
		theApp.m_BlockRows=(long)Thevalue;//DEM�ֿ��������

		Thevalue = m_Recordset->GetCollect("DEM�ֿ�����"); 
		theApp.m_BlockCols=(long)Thevalue;//DEM�ֿ��������
		
		Thevalue = m_Recordset->GetCollect("ԭʼDEM����"); 
		theApp.m_Dem_Rows=(long)Thevalue;//DEM���ݺ�������
 
		Thevalue = m_Recordset->GetCollect("ԭʼDEM����"); 
		theApp.m_Dem_cols=(long)Thevalue;//DEM���ݺ�������
		
		Thevalue = m_Recordset->GetCollect("��ЧDEMֵ"); 
		theApp.m_DEM_IvalidValue=(long)Thevalue;//��ЧDEM���ݵ�߳�ֵ
		
		//DEM�����ӿ�Ŀ��(��һ�����ο��ʾ���ٿռ����,���ֿ��С=33,
		//DEM��x�����ϸ�������=20,��DEM�����ӿ���=20*32=640��)
		theApp.m_Dem_BlockWidth=theApp.m_Cell_xwidth*(theApp.m_Dem_BlockSize-1);
		
		m_Recordset->Close();//�رռ�¼��
	
		//DEM���Ͻ�x����
		theApp.m_DemRightUp_x=theApp.m_DemLeftDown_x+theApp.m_Cell_xwidth*(theApp.m_Dem_cols-1);
		//DEM���Ͻ�y����
		theApp.m_DemRightUp_y=theApp.m_DemLeftDown_y+theApp.m_Cell_ywidth*(theApp.m_Dem_Rows-1);

	}
	else
	{
		m_Recordset->Close();//�رռ�¼��
		MessageBox("��Ŀû����ģ����!","����Ŀ",MB_ICONINFORMATION);
		return FALSE;	//����
	}


	//����SQL�ַ���
	strsql="select *  from IMAGERECT_INFO ";  
	try
	{
		//�� IMAGERECT_INFO���ݱ�,��ȡӰ�����������Ϣ
		HRESULT	hr =m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	//������
	{
		CString errormessage;
		errormessage.Format("�����ݿ��ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"װ������",MB_ICONSTOP);
		m_Recordset->Close();//�رռ�¼��
		return FALSE;	//����
	} 
	
	
	if(!m_Recordset->adoEOF)	//���û�е���¼��ĩβ,��ʾ�м�¼
	{
		Thevalue = m_Recordset->GetCollect("���½�����X"); 
		theApp.m_TexturLeftDown_x=(double)Thevalue;//�������½�x����
		
		Thevalue = m_Recordset->GetCollect("���½�����Y"); 
		theApp.m_TexturLeftDown_y=(double)Thevalue;//�������½�y����
		
		Thevalue = m_Recordset->GetCollect("���Ͻ�����X"); 
		theApp.m_TexturRightUp_x=(double)Thevalue ;//�������Ͻ�x����
		
		Thevalue = m_Recordset->GetCollect("���Ͻ�����Y"); 
		theApp.m_TexturRightUp_y=(double)Thevalue;//�������Ͻ�y����
		
		Thevalue = m_Recordset->GetCollect("Ӱ�����������"); 
		theApp.m_ImagePyramidCount=(long)Thevalue;//����Ӱ�����������,������LOD����
	
		Thevalue = m_Recordset->GetCollect("һ��Ӱ��ֱ���"); 
		theApp.m_ImageResolution[1]=(float)Thevalue;//����Ӱ��һ��Ӱ��ֱ���

		Thevalue = m_Recordset->GetCollect("����Ӱ��ֱ���"); 
		theApp.m_ImageResolution[2]=(float)Thevalue;//����Ӱ�����Ӱ��ֱ���

		Thevalue = m_Recordset->GetCollect("����Ӱ��ֱ���"); 
		theApp.m_ImageResolution[3]=(float)Thevalue;//����Ӱ������Ӱ��ֱ���
	
		Thevalue = m_Recordset->GetCollect("�ļ�Ӱ��ֱ���"); 
		theApp.m_ImageResolution[4]=(float)Thevalue;//����Ӱ���ļ�Ӱ��ֱ���
	
		Thevalue = m_Recordset->GetCollect("�弶Ӱ��ֱ���"); 
		theApp.m_ImageResolution[5]=(float)Thevalue;//����Ӱ���弶Ӱ��ֱ���

		m_Recordset->Close();//�رռ�¼��
		
	}
	else
	{
		m_Recordset->Close();//�رռ�¼��
	}
   
  	
	
	theApp.bLoginSucceed=TRUE;//���ݼ��سɹ�
	myOci.Init_OCI();//��ʼ��OCI
	
	//����SQL�ַ���	
	strsql.Format("select * from Scheme ORDER BY �������� ASC");
	if(m_Recordset->State)
		m_Recordset->Close();
	try
	{
		//�� Scheme���ݱ�,��ȡ�򿪷����������Ϣ
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)		//������
	{
		CString errormessage;
		errormessage.Format("�����ݿ��ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"�����ݿ��",MB_ICONINFORMATION);
		m_Recordset->Close();//�رռ�¼��
		return  FALSE;//����
	} 	
	
	m_SchemeNames.RemoveAll();	
	//GetCollect():Ado��ȡ���ݿ��ֶ�ֵ����
	int index=0; //��ȡ������Ϣ
	while(!m_Recordset->adoEOF)
	{
	
		Thevalue = m_Recordset->GetCollect("��������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].Schemename=Thevalue.bstrVal;//��������
			m_SchemeNames.Add(myDesingScheme.SchemeDatass[index].Schemename);
			
		}

		Thevalue = m_Recordset->GetCollect("��Ƶȼ�");
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDesigngrade=Thevalue.bstrVal;//��Ƶȼ�
			
		}
		
		Thevalue = m_Recordset->GetCollect("ǣ������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strDraughtstyle=Thevalue.bstrVal;//ǣ������
		}
		

		Thevalue = m_Recordset->GetCollect("��������"); //��������
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strBlocomotiveStyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("������ʽ"); //������ʽ
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strCBbsStyle=Thevalue.bstrVal;
		}

		Thevalue = m_Recordset->GetCollect("���εر�");  //���εر�
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strTerrainstyle=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("��������"); //��������
		if(Thevalue.vt!=VT_NULL) 
		{
			myDesingScheme.SchemeDatass[index].strEngineeringcondition=Thevalue.bstrVal;
		}
		
		Thevalue = m_Recordset->GetCollect("����ٶ�"); //����ٶ�
		myDesingScheme.SchemeDatass[index].designspeed=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("��С���߰뾶"); //��С���߰뾶
		myDesingScheme.SchemeDatass[index].minRadius=(long)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("��������Ч����"); //��������Ч����
		myDesingScheme.SchemeDatass[index].dxfLength=(short)Thevalue;
		
		Thevalue = m_Recordset->GetCollect("��С�³�"); //��С�³�
		myDesingScheme.SchemeDatass[index].minSlopeLength=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("����¶�"); //����¶�
		myDesingScheme.SchemeDatass[index].maxSlope=(double)Thevalue;		
	
		Thevalue = m_Recordset->GetCollect("����¶Ȳ�"); //����¶Ȳ�
		myDesingScheme.SchemeDatass[index].maxSlopePddsc=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("������"); //������
		myDesingScheme.SchemeDatass[index].StartLC=(double)Thevalue;		
		
		Thevalue = m_Recordset->GetCollect("�յ����"); //�յ����
		myDesingScheme.SchemeDatass[index].EndLC=(double)Thevalue;		
		
		index++;	
		m_Recordset->MoveNext();//��¼��ָ������

	}
	m_Recordset->Close();//�رռ�¼��
	
	if(m_SchemeNames.GetSize()>0)
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrame->AddSchemeName();
	}

//	if(NewOrOpen==1) //	1:����Ŀ  -1:�½���Ŀ
	MessageBox("����Ŀ�ɹ�!","����Ŀ",MB_ICONINFORMATION);
    
    EndWaitCursor();//������л�ΪĬ�Ϲ��,�����ȴ�

	return TRUE; //����
	
}

//��ʼ�� ListCtrl�ؼ�
void COpenProject::InitListCtrl()
{
	// 	1.�¼�ListControl �ؼ��������е�style����ҳ�µ�Viewѡ��Report��
	m_list.InsertColumn(0,"���");          //������
	m_list.InsertColumn(1,"��Ŀ����");
	m_list.InsertColumn(2,"��Ŀ��������");

	CRect rect;
	m_list.GetClientRect(rect);    //��õ�ǰ�ͻ�����Ϣ                 
	m_list.SetColumnWidth(0,rect.Width()/5);   //�����еĿ��     
	m_list.SetColumnWidth(1,rect.Width()/3);
	m_list.SetColumnWidth(2,rect.Width()/3);
	
	//����ListControl �ؼ����Ϊ���������ѡ��ģʽ
	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_GRIDLINES|   LVS_EX_FULLROWSELECT);
}

