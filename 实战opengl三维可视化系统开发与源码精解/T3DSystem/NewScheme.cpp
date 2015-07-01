// NewScheme.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "NewScheme.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CNewScheme dialog


CNewScheme::CNewScheme(CWnd* pParent /*=NULL*/)
	: CDialog(CNewScheme::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewScheme)
	m_minRadius = 0;
	m_criterionMinR = 0;
	m_startLC = 0.0;
	m_maxSlopePd = 0.0f;
	m_maxSlopePddsc = 0.0f;
	m_minSLopePc = 0.0f;
	m_criterionminSlopePc = 0;
	m_criterionmaxSlopePD = 0.0f;
	m_criterionmaxSlopePddsc = 0.0f;
	m_endLC = 0.0;
	//}}AFX_DATA_INIT
}


void CNewScheme::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewScheme)
	DDX_Control(pDX, IDC_COMBO_BSSTYLE, m_CBbsStyle);
	DDX_Control(pDX, IDC_COMBO_LOCOMOTIVE, m_CBlocomotiveStyle);
	DDX_Control(pDX, IDC_COMBO_DFXEFFICIENTLENGTH, m_CBdfxefficientLength);
	DDX_Control(pDX, IDC_COMBO_TERRAINSTYLE, m_CBterrainStyle);
	DDX_Control(pDX, IDC_COMBO_ENGINEERINGCONDITION, m_CBengineeringCondition);
	DDX_Control(pDX, IDC_COMBO_DESIGNSPEED, m_CBdesignSpeed);
	DDX_Control(pDX, IDC_COMBO_SCHEMENAME, m_CBschemeName);
	DDX_Control(pDX, IDC_COMBO_GRADE, m_CBrailwayGrade);
	DDX_Control(pDX, IDC_COMBO_DRAUGHTSTYLE, m_CBdraughtStyle);
	DDX_Text(pDX, IDC_EDIT_MINRADIUS, m_minRadius);
	DDX_Text(pDX, IDC_EDIT_CRITERIONMINR, m_criterionMinR);
	DDX_Text(pDX, IDC_EDIT_STARTLC, m_startLC);
	DDX_Text(pDX, IDC_EDIT_MAXSLOPEPD, m_maxSlopePd);
	DDX_Text(pDX, IDC_EDIT_MAXSLOPEPDDSC, m_maxSlopePddsc);
	DDX_Text(pDX, IDC_EDIT_MINPC, m_minSLopePc);
	DDX_Text(pDX, IDC_EDIT_CRITERIONMINPC, m_criterionminSlopePc);
	DDX_Text(pDX, IDC_EDIT_CRITERIONMAXSLOPEPD, m_criterionmaxSlopePD);
	DDX_Text(pDX, IDC_EDIT_CRITERIONMAXSLOPEPDDSC, m_criterionmaxSlopePddsc);
	DDX_Text(pDX, IDC_EDIT_ENDLC, m_endLC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewScheme, CDialog)
	//{{AFX_MSG_MAP(CNewScheme)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_CBN_SELCHANGE(IDC_COMBO_SCHEMENAME, OnSelchangeComboSchemename)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_CBN_SELCHANGE(IDC_COMBO_GRADE, OnSelchangeComboGrade)
	ON_CBN_SELCHANGE(IDC_COMBO_DESIGNSPEED, OnSelchangeComboDesignspeed)
	ON_CBN_SELCHANGE(IDC_COMBO_ENGINEERINGCONDITION, OnSelchangeComboEngineeringcondition)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_COMBO_DRAUGHTSTYLE, OnSelchangeComboDraughtstyle)
	ON_CBN_SELCHANGE(IDC_COMBO_DFXEFFICIENTLENGTH, OnSelchangeComboDfxefficientlength)
	ON_CBN_SELCHANGE(IDC_COMBO_TERRAINSTYLE, OnSelchangeComboTerrainstyle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CNewScheme message handlers

//��ʼ������
void CNewScheme::InitData()
{
	m_pRecordset.CreateInstance("ADODB.Recordset");   
	
	//��·�ȼ�
	m_CBrailwayGrade.ResetContent();
	m_CBrailwayGrade.AddString("����·");
	m_CBrailwayGrade.AddString("����·");
	m_CBrailwayGrade.AddString("����·");
	m_CBrailwayGrade.SetCurSel(0); //����ѡ����
	OnSelchangeComboGrade();//��·�ȼ��仯ʱ

	//ǣ������
	m_CBdraughtStyle.ResetContent();
	m_CBdraughtStyle.AddString("����");
	m_CBdraughtStyle.AddString("��ȼ");
	m_CBdraughtStyle.SetCurSel(0); //����ѡ����
	OnSelchangeComboDraughtstyle();//ǣ�����ͱ仯ʱ
		
	//��������
	m_CBengineeringCondition.ResetContent();
	m_CBengineeringCondition.AddString("һ��ض�");
	m_CBengineeringCondition.AddString("���ѵض�");
	m_CBengineeringCondition.SetCurSel(0); //����ѡ����
	OnSelchangeComboEngineeringcondition(); //���������仯ʱ

	//���η���
	m_CBterrainStyle.ResetContent();
	m_CBterrainStyle.AddString("ƽԭ");
	m_CBterrainStyle.AddString("����");
	m_CBterrainStyle.AddString("ɽ��");
	m_CBterrainStyle.SetCurSel(0); //����ѡ����

	//��������Ч����
	m_CBdfxefficientLength.ResetContent();
	m_CBdfxefficientLength.AddString("1050");
	m_CBdfxefficientLength.AddString("850");
	m_CBdfxefficientLength.AddString("750");
	m_CBdfxefficientLength.AddString("650");
	m_CBdfxefficientLength.AddString("550");
	m_CBdfxefficientLength.SetCurSel(0); //����ѡ����
	OnSelchangeComboDfxefficientlength();//�����߳��������仯ʱ
	
	//������ʽ
	m_CBbsStyle.ResetContent();
	m_CBbsStyle.AddString("���Զ�����");
	m_CBbsStyle.AddString("�Զ�����");
	m_CBbsStyle.AddString("�п�һ�廯CTC");
	m_CBbsStyle.SetCurSel(0); //����ѡ����
	
	

	
/*
	if(!m_tooltip.Create(this))
	{
		TRACE("���ܴ���������ʾ����!");
	}
	else
	{
		CEdit *pedit=(CEdit*)GetDlgItem(IDC_EDIT_MINPC);
		m_tooltip.AddTool(pedit,IDS_RAILWAYGRADE);
		
		m_tooltip.Activate(TRUE);
	}*/


	
}

//��ʼ����Ϣ	
BOOL CNewScheme::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitData();//��ʼ������
	LoadSchemeNmae("");	//������Ŀ���ƴ����ݿ��м��ط�������
	GetMaxSlopePdRules(); //�ӹ淶�л�ȡ������¶�ֵ
	GetMaxPddscRules(); //�ӹ淶�л�ȡ������¶ȴ�����
	return TRUE; 
}

//����Ŀ������Ϣ���м��
BOOL CNewScheme::CheckData(BOOL bAdd)
{
	CString tt,strtilte;
	if(bAdd==TRUE)
	{
		strtilte="���ӷ���";
	}
	else
	{
		strtilte="�޸ķ���";
	}
	int nsel=m_CBschemeName.GetCurSel();
	if(nsel<0)
	{
		m_CBschemeName.GetWindowText(m_schemename);
	}
	else
	{
		m_CBschemeName.GetLBText(nsel,m_schemename);
	}

	if(bAdd==TRUE)
	{
		for(int i=0;i<m_CBschemeName.GetCount();i++)
		{
			m_CBschemeName.GetLBText(i,tt);
			if(strcmp(tt,m_schemename)==0)
			{
				tt.Format("����[%s]�Ѵ���!",m_schemename);
				MessageBox(tt,strtilte,MB_ICONSTOP);
				return FALSE;
			}
		}
	}
	else if(bAdd==FALSE)
	{
		for(int i=0;i<m_CBschemeName.GetCount();i++)
		{
			m_CBschemeName.GetLBText(i,tt);
			if(strcmp(tt,m_schemename)==0 &&strcmp(tt,m_oldschemename)!=0) 
			{
				tt.Format("����[%s]�Ѵ���!",m_schemename);
				MessageBox(tt,strtilte,MB_ICONSTOP);
				return FALSE;
			}
		}
	}


	if(m_minRadius<m_criterionMinR)
	{
		int m_answer=MessageBox("��С���߰뾶С�ڹ淶ֵ,ȷ�����ô˰뾶ֵ��?","��С���߰뾶���",MB_ICONQUESTION||MB_YESNO);
		if(m_answer!=1) 
	
	
		{
			CEdit *pedit=(CEdit*)GetDlgItem(IDC_EDIT_MINRADIUS);
			pedit->SetSel(0,-1);
			pedit->SetFocus();
			return FALSE;
		}
	}		
	

	if(m_maxSlopePd>m_criterionmaxSlopePD)
	{
		MessageBox("����¶Ȳ��ܴ��ڹ淶ֵ",strtilte,MB_ICONSTOP);
		return FALSE;
	}

	if(m_maxSlopePddsc>m_criterionmaxSlopePddsc)
	{
		MessageBox("����¶Ȳ�ܴ��ڹ淶ֵ",strtilte,MB_ICONSTOP);
		return FALSE;
	}
	
	if(m_minSLopePc<m_criterionminSlopePc)
	{
		MessageBox("��С�³�����С�ڹ淶ֵ",strtilte,MB_ICONSTOP);
		return FALSE;
	}


	return TRUE;

}

//���淽�� 
void CNewScheme::OnButtonSave() 
{
	Add_Edit_Data(TRUE);//���Ӻ󱣴淽����Ϣ�����ݿ��� 
	
}


//�������Ʊ仯ʱ
void CNewScheme::OnSelchangeComboSchemename() 
{
	CString tt;
	if(m_CBschemeName.GetCount()>0)
	{
		m_CBschemeName.GetLBText(m_CBschemeName.GetCurSel(),m_oldschemename);
		LoadData(m_oldschemename);//���ݷ�������,�����ݿ��м�����Ŀ����
		GetMinRfromCriterion();//�õ��淶����С���߰뾶 
//		m_CBdesignSpeed.GetLBText(m_CBdesignSpeed.GetCurSel(),tt);
//		int mspeed=atoi(tt);
//		
//		m_criterionMinR=myDesingScheme.GetMinRfromCriterion(mspeed, m_CBengineeringCondition.GetCurSel());
		this->UpdateData(FALSE);
	}

}

//�޸ķ��� 
void CNewScheme::OnButtonEdit() 
{
	this->UpdateData();
	CString strSql;
	strSql.Format("DELETE  from  Scheme WHERE ��������='%s'",m_oldschemename);  
	try
	{
		hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 
		if(!SUCCEEDED(hr))
		{
			MessageBox("ɾ��ʧ��!","ɾ������",MB_ICONINFORMATION);
			return;
		}
	}
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("������Ϣ:%s",e.ErrorMessage());
		MessageBox("ɾ��ʧ��!","ɾ������",MB_ICONINFORMATION);
	} 	

	Add_Edit_Data(FALSE);//�޸ĺ󱣴淽����Ϣ�����ݿ��� 
	
}

//������Ŀ���ƴ����ݿ��м��ط�������
void CNewScheme::LoadSchemeNmae(CString mstrschemename)
{
	CString strSql="Select *   from  Scheme ORDER BY �������� ASC";  
	try
	{
		m_pRecordset->Open((_bstr_t)strSql,(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("�򿪱�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"�����ݱ�",MB_ICONSTOP);
		return;
	} 
	
	
	CString tt;
	m_CBschemeName.ResetContent(); //���
	while(!m_pRecordset->adoEOF)
	{
		Thevalue = m_pRecordset->GetCollect("��������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			m_CBschemeName.AddString(tt);
		}
		m_pRecordset->MoveNext();
	}
	m_pRecordset->Close();
	if(m_CBschemeName.GetCount()>0)
	{
		if(mstrschemename.IsEmpty())
			m_CBschemeName.SetCurSel(0);
		else
		{
			for(int i=0;i<m_CBschemeName.GetCount();i++)
			{
				CString tt2;
				m_CBschemeName.GetLBText(i,tt2);
				if(strcmp(tt2,mstrschemename)==0)
				{
					m_CBschemeName.SetCurSel(i);
					break;
				}
			}
		}
		OnSelchangeComboSchemename();//�������Ʊ仯ʱ		
	}
}

//���ݷ�������,�����ݿ��м�����Ŀ����
void CNewScheme::LoadData(CString strschemeName)
{
	CString strSql;
	strSql.Format("Select *   from  Scheme WHERE �������� ='%s'",strschemeName);  
	try
	{
		m_pRecordset->Open((_bstr_t)strSql,(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("�򿪱�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"�����ݱ�",MB_ICONSTOP);
		return;
	} 

	
	CString tt,tt2;
	int i;
	
	if(!m_pRecordset->adoEOF)
	{
		Thevalue = m_pRecordset->GetCollect("��Ƶȼ�"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			for(i=0;i<m_CBrailwayGrade.GetCount();i++)
			{
				m_CBrailwayGrade.GetLBText(i,tt2);
				if(strcmp(tt,tt2)==0)
				{
					m_CBrailwayGrade.SetCurSel(i);
					break;
				}
			}
		}
	
		Thevalue = m_pRecordset->GetCollect("ǣ������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			for(i=0;i<m_CBdraughtStyle.GetCount();i++)
			{
				m_CBdraughtStyle.GetLBText(i,tt2);
				if(strcmp(tt,tt2)==0)
				{
					m_CBdraughtStyle.SetCurSel(i);
					break;
				}
			}
		}

		Thevalue = m_pRecordset->GetCollect("��������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			for(i=0;i<m_CBlocomotiveStyle.GetCount();i++)
			{
				m_CBlocomotiveStyle.GetLBText(i,tt2);
				if(strcmp(tt,tt2)==0)
				{
					m_CBlocomotiveStyle.SetCurSel(i);
					break;
				}
			}
		}
		
		Thevalue = m_pRecordset->GetCollect("������ʽ"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			for(i=0;i<m_CBbsStyle.GetCount();i++)
			{
				m_CBbsStyle.GetLBText(i,tt2);
				if(strcmp(tt,tt2)==0)
				{
					m_CBbsStyle.SetCurSel(i);
					break;
				}
			}
		}


		Thevalue = m_pRecordset->GetCollect("���εر�"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			for(i=0;i<m_CBterrainStyle.GetCount();i++)
			{
				m_CBterrainStyle.GetLBText(i,tt2);
				if(strcmp(tt,tt2)==0)
				{
					m_CBterrainStyle.SetCurSel(i);
					break;
				}
			}
		}
	
		Thevalue = m_pRecordset->GetCollect("��������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			for(i=0;i<m_CBengineeringCondition.GetCount();i++)
			{
				m_CBengineeringCondition.GetLBText(i,tt2);
				if(strcmp(tt,tt2)==0)
				{
					m_CBengineeringCondition.SetCurSel(i);
					break;
				}
			}
		}

		
		Thevalue = m_pRecordset->GetCollect("����ٶ�"); 
		int mspeed=(short)Thevalue;
		for(i=0;i<m_CBdesignSpeed.GetCount();i++)
		{
			m_CBdesignSpeed.GetLBText(i,tt);
			if(atoi(tt)==mspeed)
			{
				m_CBdesignSpeed.SetCurSel(i);
				break;
			}
		}

		Thevalue = m_pRecordset->GetCollect("��С���߰뾶"); 
		m_minRadius=(long)Thevalue;
	
		Thevalue = m_pRecordset->GetCollect("��������Ч����"); 
		int mdfxLength=(short)Thevalue;
		for(i=0;i<m_CBdfxefficientLength.GetCount();i++)
		{
			m_CBdfxefficientLength.GetLBText(i,tt);
			if(atoi(tt)==mdfxLength)
			{
				m_CBdfxefficientLength.SetCurSel(i);
				break;
			}
		}

		Thevalue = m_pRecordset->GetCollect("��С�³�"); 
		m_minSLopePc=(double)Thevalue;	
		
		Thevalue = m_pRecordset->GetCollect("����¶�"); 
		m_maxSlopePd=(double)Thevalue;	

		Thevalue = m_pRecordset->GetCollect("����¶Ȳ�"); 
		m_maxSlopePddsc=(double)Thevalue;	

		Thevalue = m_pRecordset->GetCollect("������"); 
		m_startLC=(double)Thevalue;		
		
		Thevalue = m_pRecordset->GetCollect("�յ����"); 
		m_endLC=(double)Thevalue;		
		
	}
	m_pRecordset->Close(); //�رռ�¼��
 
}

//����
void CNewScheme::OnButtonExit() 
{
	EndDialog(IDCANCEL);
	
}

//��·�ȼ��仯ʱ
void CNewScheme::OnSelchangeComboGrade() 
{
	switch(m_CBrailwayGrade.GetCurSel())
	{
	case 0:
		m_CBdesignSpeed.ResetContent();
		m_CBdesignSpeed.AddString("160 km/h");
		m_CBdesignSpeed.AddString("140 km/h");
		m_CBdesignSpeed.AddString("120 km/h");
		m_CBdesignSpeed.SetCurSel(0);
		break;
	case 1:
		m_CBdesignSpeed.ResetContent();
		m_CBdesignSpeed.AddString("120 km/h");
		m_CBdesignSpeed.AddString("100 km/h");
		m_CBdesignSpeed.AddString("80 km/h");
		m_CBdesignSpeed.SetCurSel(0);
		break;
	case 2:
		
		
		m_CBdesignSpeed.ResetContent();
		m_CBdesignSpeed.AddString("60 km/h");
		m_CBdesignSpeed.AddString("50 km/h");
		m_CBdesignSpeed.AddString("40 km/h");
		m_CBdesignSpeed.SetCurSel(0);
		break;
	case 3:
		
		
		m_CBdesignSpeed.ResetContent();
		m_CBdesignSpeed.AddString("50 km/h");
		m_CBdesignSpeed.AddString("40 km/h");
		m_CBdesignSpeed.AddString("30 km/h");
		m_CBdesignSpeed.SetCurSel(0);
		break;
	}
	
	GetMaxSlopePdRules(); //�ӹ淶�л�ȡ������¶�ֵ
	GetMaxPddscRules(); //�ӹ淶�л�ȡ������¶ȴ�����

}

//����ٶȱ仯ʱ
void CNewScheme::OnSelchangeComboDesignspeed() 
{
	this->UpdateData();
	m_criterionMinR=GetMinRfromCriterion();
	this->UpdateData(FALSE);
	
}

//�õ��淶����С���߰뾶 
int CNewScheme::GetMinRfromCriterion()
{
	
	CString tt;
	m_CBdesignSpeed.GetLBText(m_CBdesignSpeed.GetCurSel(),tt);
	int mspeed=atoi(tt);

	
    switch(mspeed)
	{
	case 160:
		if(m_CBengineeringCondition.GetCurSel()==0) 
			m_criterionMinR=2000;	
		else
			m_criterionMinR=1600;	
		break;
	case 140:
		if(m_CBengineeringCondition.GetCurSel()==0) 
			m_criterionMinR=1600;	
		else
			m_criterionMinR=1200;	
		break;
	case 120:
		if(m_CBengineeringCondition.GetCurSel()==0) 
			m_criterionMinR=1200;	
		else
			m_criterionMinR=800;	
		break;
	case 100:
		if(m_CBengineeringCondition.GetCurSel()==0) 
			m_criterionMinR=800;	
		else
			m_criterionMinR=600;	
		break;
		
	case 80:
		if(m_CBengineeringCondition.GetCurSel()==0) 
			m_criterionMinR=600;	
		else
			m_criterionMinR=500;	
		break;
	}

	this->UpdateData(FALSE);
	
	return m_criterionMinR;

}

//���������仯ʱ
void CNewScheme::OnSelchangeComboEngineeringcondition() 
{
	
	this->UpdateData();
	m_criterionMinR=GetMinRfromCriterion();//�õ��淶����С���߰뾶 
	this->UpdateData(FALSE);
	GetMaxPddscRules();//�õ��淶��Ĭ��ֵ (����¶ȴ�����)
}

//���ӻ��޸ĺ󱣴淽����Ϣ�����ݿ��� 
void CNewScheme::Add_Edit_Data(BOOL bAddorEdit)
{
	this->UpdateData();
	if(CheckData(bAddorEdit)==FALSE)//����Ŀ������Ϣ���м��,���ʧ��,����
		return;
	BeginWaitCursor();
	
	CString tt;
	CString strdesigngrade,strdraughtstyle,strCBbsStyle,strBlocomotiveStyle;
	CString strterrainstyle,strengineeringcondition;
	
	m_CBrailwayGrade.GetLBText(m_CBrailwayGrade.GetCurSel(),strdesigngrade);	//��·�ȼ�
	m_CBdraughtStyle.GetLBText(m_CBdraughtStyle.GetCurSel(),strdraughtstyle);	//ǣ������	
 
	m_CBlocomotiveStyle.GetLBText(m_CBlocomotiveStyle.GetCurSel(),strBlocomotiveStyle);	//��������
	m_CBbsStyle.GetLBText(m_CBbsStyle.GetCurSel(),strCBbsStyle); //������ʽ
	m_CBterrainStyle.GetLBText(m_CBterrainStyle.GetCurSel(),strterrainstyle);	//��������
	m_CBengineeringCondition.GetLBText(m_CBengineeringCondition.GetCurSel(),strengineeringcondition); //��������
	
	
	int mdesignspeed;
	m_CBdesignSpeed.GetLBText(m_CBdesignSpeed.GetCurSel(),tt); //����ٶ�
	mdesignspeed=atoi(tt);
    

	int mdxflength;
	m_CBdfxefficientLength.GetLBText(m_CBdfxefficientLength.GetCurSel(),tt);//��������Ч��
	mdxflength=atoi(tt);
	
	tt.Format("INSERT INTO Scheme VALUES(\
	   '%s','%s','%s','%s','%s','%s','%s',\
	   %d,%d,%d,%.3f,%.3f,%.3f,%.3f,%.3f)",\
	   m_schemename,
	   strdesigngrade,
	   strdraughtstyle,
	   strBlocomotiveStyle,
	   strCBbsStyle,
	   strterrainstyle,
	   strengineeringcondition,
	   mdesignspeed,
	   m_minRadius,
	   mdxflength,
	   m_minSLopePc,
	   m_maxSlopePd,
	   m_maxSlopePddsc,
	   m_startLC,
	   0);
	try
	{
		hr=theApp.m_pConnection->Execute((_bstr_t)tt,&RecordsAffected,adCmdText); 
		if(!SUCCEEDED(hr))
		{
			if(bAddorEdit==TRUE)
			{
				MessageBox("��������ʧ��!","�����·���",MB_ICONINFORMATION);
				return;
			}
			else
			{
				MessageBox("�����޸�ʧ��!","�޸ķ���",MB_ICONINFORMATION);
				return;
			}
		}
	}
	catch(_com_error& e)	//����׽ 
	{
		CString errormessage;
		errormessage.Format("������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"�޸ķ���",MB_ICONINFORMATION);
		return;
	} 
	if(bAddorEdit==TRUE) //���ӷ���
	{
		MessageBox("��������ɹ�!","�����·���",MB_ICONINFORMATION);
		LoadSchemeNmae(m_schemename);	//������Ŀ���ƴ����ݿ��м��ط�������
	}
	else   //�޸ķ���
	{
		MessageBox("�����޸ĳɹ�!","�޸ķ���",MB_ICONINFORMATION);
	}
}

//ɾ������
void CNewScheme::OnButtonDelete() 
{
	this->UpdateData();

	int manwer=MessageBox("�Ƿ�ɾ������?","ɾ������",MB_ICONINFORMATION|MB_YESNO);
	if(manwer==6)
		DeleteSchemeTableData();//ɾ��������ɾ��������Ӧ�����ݱ�������

	LoadSchemeNmae("");//������Ŀ���ƴ����ݿ��м��ط�������
	
}

//ɾ����Ŀ��Ӧ�����ݱ��е�����
void CNewScheme::DeleteSchemeTableData()
{
	CString strSql;
	strSql.Format("DELETE  from  Scheme WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 

	strSql.Format("DELETE  from  Scheme_plane_CureveData WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 
	
	strSql.Format("DELETE  from  Scheme_plane_CureveData_XY WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 

	strSql.Format("DELETE  from  T3DLineZxCorrdinate WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 

	strSql.Format("DELETE  from  T3DLineZxCorrdinateZDM WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 
	
	strSql.Format("DELETE  from  ZDmJDCurve WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 
	
	strSql.Format("DELETE  from  zdmSegmentGeoFeature WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 

	strSql.Format("DELETE  from  Tunnel WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 

	strSql.Format("DELETE  from  Bridge WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 

	strSql.Format("DELETE  from  StationTable WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 

	strSql.Format("DELETE  from  SchemeDesignResult WHERE ��������='%s'",m_oldschemename);  
	hr=theApp.m_pConnection->Execute((_bstr_t)strSql,&RecordsAffected,adCmdText); 

	//�������
	myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_RailwayBP3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.TunnelInfor[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.BridgeInfor[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_RailwayZhenMu[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_RailwayTieGui[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].RemoveAll();
	
	
	if(SUCCEEDED(hr))
	{
		MessageBox("����ɾ���ɹ�!","ɾ������",MB_ICONINFORMATION);
		theApp.b_haveDeletScheme=TRUE;//��ʶ�Ƿ�ɾ������,���ɾ��,��Ҫ����ͼ���»���
	}
	else
		MessageBox("����ɾ��ʧ��!","ɾ������",MB_ICONINFORMATION);
		
}


BOOL CNewScheme::PreTranslateMessage(MSG* pMsg) 
{
//	m_tooltip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void CNewScheme::OnMouseMove(UINT nFlags, CPoint point) 
{
	CString strText;
	switch(m_CBrailwayGrade.GetCurSel())
	{
	case 0:
		strText="����·,��·������Ǹ����õ���·,�������ͻ��������ڻ����20Mt";
		break;
	case 1:
		strText="����·,��·���������硢�������õ���·,�������ͻ�����С��20Mt�Ҵ���10Mt";
		break;
	case 2:
		strText="����·,Ϊĳһ��������ҵ�������·,�������ͻ�����С��10Mt�Ҵ���5Mt";
		break;
	case 3:
		strText="������·,Ϊĳһ��������ҵ�������·,�������ͻ�����С��5Mt";
		break;
	}
/*
	CComboBox *pComboBox=(CComboBox*)GetDlgItem(IDC_COMBO_GRADE);
	CRect rect;
	pComboBox->GetWindowRect(&rect);   
	this->SetCapture();
	ScreenToClient(&rect);   
	if(point.x>=rect.left-1 && point.x<=rect.right+1 && point.y<=rect.bottom+1 && point.y>=rect.top-1)
	{   
		m_tooltip.AddTool(pComboBox,strText);
		
	}   
	ReleaseCapture();
*/

	
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CNewScheme::DestroyWindow() 
{
	_RecordsetPtr   m_Recordset;
	_variant_t Thevalue;  
	variant_t RecordsAffected;
	m_Recordset.CreateInstance("ADODB.Recordset");   
	CString strsql;
	
	strsql.Format("select * from Scheme ORDER BY �������� ASC");
	if(m_Recordset->State)
		m_Recordset->Close();
	try
	{
		m_Recordset->Open(_bstr_t(strsql),(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);    
	}
	
	catch(_com_error& e)	
	{
		CString errormessage;
		errormessage.Format("�����ݿ��ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		MessageBox(errormessage,"�����ݿ��",MB_ICONINFORMATION);
		m_Recordset->Close();
		return 0 ;
	} 
	
	m_SchemeNames.RemoveAll();
	while(!m_Recordset->adoEOF)
	{
		Thevalue = m_Recordset->GetCollect("��������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			CString tt=Thevalue.bstrVal;
			m_SchemeNames.Add(tt);
		}
		m_Recordset->MoveNext();
	}
	m_Recordset->Close();
	
	if(m_SchemeNames.GetSize()>0)
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		pMainFrame->AddSchemeName();
	}

	return CDialog::DestroyWindow();
}


//ǣ�����ͱ仯ʱ 
void CNewScheme::OnSelchangeComboDraughtstyle() 
{
	
	m_CBlocomotiveStyle.ResetContent();
	switch(m_CBdraughtStyle.GetCurSel())
	{
	case 0: 
		m_CBlocomotiveStyle.AddString("SS1");
		m_CBlocomotiveStyle.AddString("SS3");
		m_CBlocomotiveStyle.AddString("SS4");
		m_CBlocomotiveStyle.AddString("SS4B");
		m_CBlocomotiveStyle.AddString("SS6B");
		m_CBlocomotiveStyle.AddString("SS7");
		m_CBlocomotiveStyle.AddString("SS8");
		break;
	case 1:	
		m_CBlocomotiveStyle.AddString("DF4");
		m_CBlocomotiveStyle.AddString("DF4B");
		m_CBlocomotiveStyle.AddString("DF4E");
		m_CBlocomotiveStyle.AddString("DF6");
		m_CBlocomotiveStyle.AddString("DF8");
		m_CBlocomotiveStyle.AddString("DF10D");
		m_CBlocomotiveStyle.AddString("DF11");
		break;
		
	}
	m_CBlocomotiveStyle.SetCurSel(0);

	GetMaxSlopePdRules(); //�ӹ淶�л�ȡ������¶�ֵ
	
	  
}


//�����߳��������仯ʱ
void CNewScheme::OnSelchangeComboDfxefficientlength() 
{

	int index=m_CBdfxefficientLength.GetCurSel();
	switch(index)
	{
		case 0:
			m_criterionminSlopePc=400;
			break;
		case 1:
			m_criterionminSlopePc=350;
			break;
		case 2:
			m_criterionminSlopePc=300;
			break;
		case 3:
			m_criterionminSlopePc=250;
			break;
		default:
			m_criterionminSlopePc=200;
			break;
	}

	this->UpdateData(FALSE);
	GetMaxPddscRules(); //�ӹ淶�л�ȡ������¶ȴ�����
	
	
}

//������������仯ʱ
void CNewScheme::OnSelchangeComboTerrainstyle() 
{
	GetMaxSlopePdRules(); //�ӹ淶�л�ȡ������¶�ֵ
	GetMaxPddscRules(); //�ӹ淶�л�ȡ������¶ȴ�����
	
}


//�ӹ淶�л�ȡ������¶ȴ�����
void CNewScheme::GetMaxPddscRules()
{
	int m_grade=m_CBrailwayGrade.GetCurSel(); 
	
	
	int  CBdfxefficientLength=m_CBdfxefficientLength.GetCurSel();
	
	int m_engineeringCondition=m_CBengineeringCondition.GetCurSel();

	
	switch(m_grade)
	{
	case  0:  
	case 1:
		switch(CBdfxefficientLength) 
		{
		case 0:
			if(m_engineeringCondition==0)
				m_criterionmaxSlopePddsc=8;
			else
				m_criterionmaxSlopePddsc=10;
			break;
		case 1:
			if(m_engineeringCondition==0)
				m_criterionmaxSlopePddsc=10;
			else
				m_criterionmaxSlopePddsc=12;
			break;
		case 2:
			if(m_engineeringCondition==0)
				m_criterionmaxSlopePddsc=12;
			else
				m_criterionmaxSlopePddsc=15;
			break;
		case 3:
			if(m_engineeringCondition==0)
				m_criterionmaxSlopePddsc=15;
			else
				m_criterionmaxSlopePddsc=18;
			break;
		}
		break;
		case 2:
			switch(CBdfxefficientLength) 
			{
			case 0:
				if(m_engineeringCondition==0)
					m_criterionmaxSlopePddsc=10;
				else
					m_criterionmaxSlopePddsc=12;
				break;
			case 1:
				if(m_engineeringCondition==0)
					m_criterionmaxSlopePddsc=12;
				else
					m_criterionmaxSlopePddsc=15;
				break;
			case 2:
				if(m_engineeringCondition==0)
					m_criterionmaxSlopePddsc=15;
				else
					m_criterionmaxSlopePddsc=18;
				break;
			case 3:
				if(m_engineeringCondition==0)
					m_criterionmaxSlopePddsc=18;
				else
					m_criterionmaxSlopePddsc=20;
			case 4:
				if(m_engineeringCondition==0)
					m_criterionmaxSlopePddsc=20;
				else
					m_criterionmaxSlopePddsc=25;
				break;
			}
			break;
	}
	this->UpdateData(FALSE);

}


 //�ӹ淶�л�ȡ������¶�ֵ
void CNewScheme::GetMaxSlopePdRules()
{
	int m_grade=m_CBrailwayGrade.GetCurSel(); 
 

	int m_terrainstyle=m_CBterrainStyle.GetCurSel(); 
 
	int m_draughtStyle=m_CBdraughtStyle.GetCurSel();
 

	float MaxSlopePdRules;

	switch(m_grade)
	{
	case  0:  
		switch(m_terrainstyle)//���εر�
		{
		case 0: 
			MaxSlopePdRules=6.0;
			break;
		case 1:
			if(m_draughtStyle==0) 
				MaxSlopePdRules=12.0;
			else
				MaxSlopePdRules=9.0;
			break;
		case 2:
			if(m_draughtStyle==0) 
				MaxSlopePdRules=15.0;
			else
				MaxSlopePdRules=12.0;
			break;
		}
		break;
	case  1:  
			switch(m_terrainstyle)
			{
			case 0: 
				MaxSlopePdRules=6.0;
				break;
			case 1:
				if(m_draughtStyle==0) 
					MaxSlopePdRules=15.0;
				else
					MaxSlopePdRules=9.0;
				break;
			case 2:
				if(m_draughtStyle==0) 
					MaxSlopePdRules=20.0;
				else
					MaxSlopePdRules=15.0;
				break;
			}
			break;
		case  2:  
				switch(m_terrainstyle)
				{
				case 0: 
					if(m_draughtStyle==0) 
						MaxSlopePdRules=9.0;
					else
						MaxSlopePdRules=8.0;
					break;					break;
				case 1:
					if(m_draughtStyle==0) 
						MaxSlopePdRules=18.0;
					else
						MaxSlopePdRules=12.0;
					break;
				case 2:
					if(m_draughtStyle==0) 
						MaxSlopePdRules=25.0;
					else
						MaxSlopePdRules=18.0;
					break;
				}
				break;
	}

	m_criterionmaxSlopePD=MaxSlopePdRules;
	this->UpdateData(FALSE);
	
}


