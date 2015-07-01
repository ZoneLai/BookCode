// PLaneRL0.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "PLaneRL0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CPLaneRL0 dialog


CPLaneRL0::CPLaneRL0(CWnd* pParent /*=NULL*/)
	: CDialog(CPLaneRL0::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPLaneRL0)
	m_L0 = 0;
	m_minR = 0;
	m_minL0 = 0;
	m_strrangR = _T("");
	m_ID = _T("");
	//}}AFX_DATA_INIT
}


void CPLaneRL0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPLaneRL0)
	DDX_Control(pDX, IDC_COMBO_R, m_CBRadius);
	DDX_Text(pDX, IDC_EDIT_L0, m_L0);
	DDX_Text(pDX, IDC_EDIT_MINR, m_minR);
	DDX_Text(pDX, IDC_EDIT_MINl0, m_minL0);
	DDX_Text(pDX, IDC_EDIT_RANGER, m_strrangR);
	DDX_Text(pDX, IDC_EDIT_ID, m_ID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPLaneRL0, CDialog)
	//{{AFX_MSG_MAP(CPLaneRL0)
	ON_CBN_SELCHANGE(IDC_COMBO_R, OnSelchangeComboR)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CPLaneRL0 message handlers


//��ʼ����Ϣ	
BOOL CPLaneRL0::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//������Ŀ������ٶȣ��������ѡ������߰뾶�����߰뾶��Χ
	switch(	myDesingScheme.SchemeDatass[m_currentSchemeIndexs].designspeed)
	{
	case 160: //����ٶ�Ϊ160Km/h
		m_strrangR="2500��5000";//���߰뾶��Χ
		m_CBRadius.ResetContent();
		m_CBRadius.AddString("1600");
		m_CBRadius.AddString("1800");
		m_CBRadius.AddString("2000");
		m_CBRadius.AddString("2500");
		m_CBRadius.AddString("2800");
		m_CBRadius.AddString("3000");
		m_CBRadius.AddString("3500");
		m_CBRadius.AddString("4000");
		m_CBRadius.AddString("4500");
		m_CBRadius.AddString("5000");
		m_CBRadius.AddString("6000");
		m_CBRadius.AddString("7000");
		m_CBRadius.AddString("8000");
		m_CBRadius.AddString("10000");
		m_CBRadius.AddString("12000");
		m_CBRadius.SetCurSel(0); //��������
		break;
	case 140:  //����ٶ�Ϊ140Km/h
		m_strrangR="2000��4000";
		m_CBRadius.ResetContent();
		m_CBRadius.AddString("1200");
		m_CBRadius.AddString("1400");
		m_CBRadius.AddString("1600");
		m_CBRadius.AddString("1800");
		m_CBRadius.AddString("2000");
		m_CBRadius.AddString("2500");
		m_CBRadius.AddString("2800");
		m_CBRadius.AddString("3000");
		m_CBRadius.AddString("3500");
		m_CBRadius.AddString("4000");
		m_CBRadius.AddString("4500");
		m_CBRadius.AddString("5000");
		m_CBRadius.AddString("6000");
		m_CBRadius.AddString("7000");
		m_CBRadius.AddString("8000");
		m_CBRadius.AddString("10000");
		m_CBRadius.AddString("12000");
		m_CBRadius.SetCurSel(0);
		break;
	case 120: //����ٶ�Ϊ120Km/h
		m_strrangR="1600��3000";
		m_CBRadius.ResetContent();
		m_CBRadius.AddString("800");
		m_CBRadius.AddString("1000");
		m_CBRadius.AddString("1200");
		m_CBRadius.AddString("1400");
		m_CBRadius.AddString("1600");
		m_CBRadius.AddString("1800");
		m_CBRadius.AddString("2000");
		m_CBRadius.AddString("2500");
		m_CBRadius.AddString("2800");
		m_CBRadius.AddString("3000");
		m_CBRadius.AddString("3500");
		m_CBRadius.AddString("4000");
		m_CBRadius.AddString("4500");
		m_CBRadius.AddString("5000");
		m_CBRadius.AddString("6000");
		m_CBRadius.AddString("7000");
		m_CBRadius.AddString("8000");
		m_CBRadius.AddString("10000");
		m_CBRadius.AddString("12000");
		m_CBRadius.SetCurSel(0);	
		break;
	case 100: //����ٶ�Ϊ100Km/h
		m_strrangR="1200��2500";
		m_CBRadius.ResetContent();
		m_CBRadius.AddString("600");
		m_CBRadius.AddString("700");
		m_CBRadius.AddString("800");
		m_CBRadius.AddString("1000");
		m_CBRadius.AddString("1200");
		m_CBRadius.AddString("1400");
		m_CBRadius.AddString("1600");
		m_CBRadius.AddString("1800");
		m_CBRadius.AddString("2000");
		m_CBRadius.AddString("2500");
		m_CBRadius.AddString("2800");
		m_CBRadius.AddString("3000");
		m_CBRadius.AddString("3500");
		m_CBRadius.AddString("4000");
		m_CBRadius.AddString("4500");
		m_CBRadius.AddString("5000");
		m_CBRadius.AddString("6000");
		m_CBRadius.AddString("7000");
		m_CBRadius.AddString("8000");
		m_CBRadius.AddString("10000");
		m_CBRadius.AddString("12000");
		break;
	case 80:  //����ٶ�Ϊ80Km/h
		m_strrangR="800��2000";
		m_CBRadius.ResetContent();
		m_CBRadius.AddString("550");
		m_CBRadius.AddString("600");
		m_CBRadius.AddString("700");
		m_CBRadius.AddString("800");
		m_CBRadius.AddString("1000");
		m_CBRadius.AddString("1200");
		m_CBRadius.AddString("1400");
		m_CBRadius.AddString("1600");
		m_CBRadius.AddString("1800");
		m_CBRadius.AddString("2000");
		m_CBRadius.AddString("2500");
		m_CBRadius.AddString("2800");
		m_CBRadius.AddString("3000");
		m_CBRadius.AddString("3500");
		m_CBRadius.AddString("4000");
		m_CBRadius.AddString("4500");
		m_CBRadius.AddString("5000");
		m_CBRadius.AddString("6000");
		m_CBRadius.AddString("7000");
		m_CBRadius.AddString("8000");
		m_CBRadius.AddString("10000");
		m_CBRadius.AddString("12000");
		break;
	}
 
	//����ѡ������߰뾶,��������
	CString tt;
	m_minR=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].minRadius;
	for(int i=0;i<m_CBRadius.GetCount();i++)
	{
		m_CBRadius.GetLBText(i,tt);
		float mR=atof(tt);
		if(mR==m_minR)
		{
			m_CBRadius.SetCurSel(i);
			break; //�˳�
		}
	}

	m_L0=m_minL0;
	this->UpdateData(FALSE); //���ݸ���
	OnSelchangeComboR(); //���ı����߰뾶ʱ,���㻺�����߳�
	
	
	return TRUE;  
}

//���ı����߰뾶ʱ,���㻺�����߳�
void CPLaneRL0::OnSelchangeComboR() 
{
	this->UpdateData();

	CString tt;

	switch(	myDesingScheme.SchemeDatass[m_currentSchemeIndexs].designspeed)
	{
		case 160: //����ٶ�Ϊ160Km/h
			m_L0=myDesingScheme.m_minPriorityR160_L0[14-m_CBRadius.GetCurSel()];
			break;
		case 140: //����ٶ�Ϊ140Km/h
			m_L0=myDesingScheme.m_minPriorityR140_L0[16-m_CBRadius.GetCurSel()];
			break;
		case 120:  //����ٶ�Ϊ120Km/h
			m_L0=myDesingScheme.m_minPriorityR120_L0[18-m_CBRadius.GetCurSel()];
			break;
	}

	m_minL0=myDesingScheme.GetMinL0(m_CBRadius.GetCurSel()); //��С�������߳�
	this->UpdateData(FALSE); //���ݸ���
}


//ȷ��
void CPLaneRL0::OnOK() 
{
	this->UpdateData(); //��������
	CString tt;
	
	if(m_ID.IsEmpty()) //�������IDΪ��
	{
		MessageBox("�����Ų���Ϊ��!","�����ż��",MB_ICONSTOP);
		return;
	}

	m_CBRadius.GetLBText(m_CBRadius.GetCurSel(),tt); //���߰뾶
	R=atoi(tt);
	if(R<m_minR) //������߰뾶С����С���߰뾶
	{
		MessageBox("���߰뾶С����С���߰뾶!","���߰뾶���",MB_ICONSTOP);
		return;
	}
	if(m_L0<m_minL0)
	{
		MessageBox("�������߳���С����С�������߳���!","�������߳��ȼ��",MB_ICONSTOP);
		return;
	}

	CDialog::OnOK();
}





















