// SpaceSearchSet.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "SpaceSearchSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CSpaceSearchSet dialog


CSpaceSearchSet::CSpaceSearchSet(CWnd* pParent /*=NULL*/)
	: CDialog(CSpaceSearchSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpaceSearchSet)
	m_shizxLength = 5;
	m_shuzxHeight =20;
	//}}AFX_DATA_INIT
}


void CSpaceSearchSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpaceSearchSet)
	DDX_Control(pDX, IDC_COMBOL_WIDTH, m_combolWidth);
	DDX_Text(pDX, IDC_EDIT_SHIZXLENGTH, m_shizxLength);
	DDX_Text(pDX, IDC_EDIT_SHUZXHEIGHT, m_shuzxHeight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpaceSearchSet, CDialog)
	//{{AFX_MSG_MAP(CSpaceSearchSet)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, OnButtonColor)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CSpaceSearchSet message handlers

// ��ɫ��ť��Ӧ����
void CSpaceSearchSet::OnButtonColor() 
{
	CColorDialog colorDlg;//������ɫ�Ի������
	if(colorDlg.DoModal()==IDOK)//�����ɫ�Ի���򿪳ɹ�
	{
		long m_color=colorDlg.GetColor();//�õ���ѡ�����ɫ
		pbrush.DeleteObject ();//ɾ��pbrush��ˢ����
		pbrush.CreateSolidBrush (m_color);//������ѡ�����ɫ���´�����ˢ
		CButton *pbutton=(CButton*)GetDlgItem(IDC_BUTTON_COLOR);
		CRect rect;
		pbutton->GetClientRect(rect);
		pbutton->InvalidateRect(rect,TRUE);//ˢ����ɫ��ť��,
		
		m_QueryColorR=GetRValue(m_color);//�õ���ѡ�����ɫ�ĺ�ɫ
		m_QueryColorG=GetGValue(m_color);//�õ���ѡ�����ɫ����ɫ
		m_QueryColorB=GetBValue(m_color);//�õ���ѡ�����ɫ����ɫ
	
	}		
}

//������ɫ��ťѡ�����ɫ����䱳��
HBRUSH CSpaceSearchSet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(pWnd->GetDlgCtrlID()== IDC_BUTTON_COLOR)//����ؼ�ID=IDC_BUTTON_COLOR,��pbrush��ˢ�ť����
		return pbrush;
	else //����,����Ĭ�ϻ�ˢ
		return hbr;
	
}

//��Ϣ��ʼ��
BOOL CSpaceSearchSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	myedit[0].SubclassDlgItem(IDC_EDIT_SHIZXLENGTH,this);
//	myedit[1].SubclassDlgItem(IDC_EDIT_SHUZXHEIGHT,this);
		
	m_combolWidth.ResetContent();//�洢��־�߿�ȵ����������
	for(int i=1;i<=20;i++)//�߿������Ϊ20
	{
		CString tt;
		tt.Format("%d",i);
		m_combolWidth.AddString(tt);
	}

	//����������ĵ�ǰѡ����
	if(m_QueryLineWidth>0)
		m_combolWidth.SetCurSel(m_QueryLineWidth-1);
	else
		m_combolWidth.SetCurSel(0);

	this->UpdateData(FALSE);//���ݱ�������
	
	//���ݱ�־����ɫ������ˢ
	pbrush.CreateSolidBrush(RGB(m_QueryColorR,m_QueryColorG,m_QueryColorB));
	
	return TRUE;  
}

BOOL CSpaceSearchSet::PreTranslateMessage(MSG* pMsg) 
{
 
	if(pMsg->wParam == VK_RETURN)//�����ť�ǻس���
	{
		CDialog *pWnd=(CDialog*)GetParent();
		pWnd->NextDlgCtrl ();
		return FALSE;
	}	
	else
		return CDialog::PreTranslateMessage(pMsg);
}


//ȷ��ɨť��Ӧ����
void CSpaceSearchSet::OnOK() 
{
	this->UpdateData();//��������
	CString tt;
	m_combolWidth.GetLBText(m_combolWidth.GetCurSel(),tt);//�õ�
	m_QueryLineWidth=m_combolWidth.GetCurSel();//�õ���־�߿��
	CDialog::OnOK();//��IDOKģʽ�ر��˳��Ի���
}
