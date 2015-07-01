// TextureTunnel.cpp : implementation file
//

#include "stdafx.h"
#include "T3DSystem.h"
#include "TextureTunnel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextureTunnel dialog


CTextureTunnel::CTextureTunnel(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureTunnel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureTunnel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTextureTunnel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureTunnel)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureTunnel, CDialog)
	//{{AFX_MSG_MAP(CTextureTunnel)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextureTunnel message handlers

void CTextureTunnel::InitTexture()
{
	CString tt;
	m_list.ResetContent();//���
	for(int i=1;i<=5;i++)  //�����ļ�����(�ɸ���ʵ�ʵ����������и���)
	{
		tt.Format("%d.bmp",i);
		m_list.AddString(tt);	//�����б��ؼ���	
	}
	
	m_list.SetCurSel(0);//Ĭ��ѡ����Ϊ��1������
	OnSelchangeList(); //��Ӧ����ѡ��ı�ʱ����Ϣ
}

BOOL CTextureTunnel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitTexture();//��ʼ���������ƣ�����д���б��ؼ��� 
	return TRUE;  
}

//��Ӧ����ѡ��ı�ʱ����Ϣ
void CTextureTunnel::OnSelchangeList() 
{
	m_list.GetText(m_list.GetCurSel(),m_TunneltextureName);//�õ������ļ���
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect);//�õ�IDC_STATIC_BMP�ؼ��Ŀͻ�����С
	this->ScreenToClient(rect);//����Ļ����ת�����û�����
	CString BitmapFilePath;
	BitmapFilePath="./����\\�����ǽ\\"+m_TunneltextureName;//�����ļ�ȫ·������
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect);//��ѡ�е�����Ӱ����IDC_STATIC_BMP�ϻ���

}
