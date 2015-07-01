// TextureTunnelDm.cpp : implementation file
//

#include "stdafx.h"
#include "T3DSystem.h"
#include "TextureTunnelDm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureTunnelDm dialog


CTextureTunnelDm::CTextureTunnelDm(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureTunnelDm::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureTunnelDm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTextureTunnelDm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureTunnelDm)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureTunnelDm, CDialog)
	//{{AFX_MSG_MAP(CTextureTunnelDm)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureTunnelDm message handlers

void CTextureTunnelDm::InitTexture()
{
	CString tt;
	m_list.ResetContent();//���
	for(int i=1;i<=4;i++)  //�����ļ�����(�ɸ���ʵ�ʵ����������и���)
	{
		tt.Format("%d.bmp",i);
		m_list.AddString(tt);		//�����б��ؼ���		
	}
	
	m_list.SetCurSel(0);//Ĭ��ѡ����Ϊ��1������
	OnSelchangeList(); //��Ӧ����ѡ��ı�ʱ����Ϣ
}

BOOL CTextureTunnelDm::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitTexture();//��ʼ���������ƣ�����д���б��ؼ��� 
	return TRUE;  
}

//��Ӧ����ѡ��ı�ʱ����Ϣ
void CTextureTunnelDm::OnSelchangeList() 
{
	m_TextureIndex=m_list.GetCurSel()+1;
	m_list.GetText(m_list.GetCurSel(),m_TunnelDmtextureName);//�õ������ļ���
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect);//�õ�IDC_STATIC_BMP�ؼ��Ŀͻ�����С
	this->ScreenToClient(rect);
	CString BitmapFilePath;//����Ļ����ת�����û�����
	BitmapFilePath="./����\\�������\\"+m_TunnelDmtextureName;//�����ļ�ȫ·������
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect);//��ѡ�е�����Ӱ����IDC_STATIC_BMP�ϻ���
	
}
