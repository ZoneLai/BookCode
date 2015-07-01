// TextureLJ.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "TextureLJ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CTextureLJ dialog


CTextureLJ::CTextureLJ(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureLJ::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureLJ)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTextureLJ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureLJ)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureLJ, CDialog)
	//{{AFX_MSG_MAP(CTextureLJ)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CTextureLJ message handlers

BOOL CTextureLJ::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitTexture();//��ʼ���������ƣ�����д���б��ؼ��� 
	
	return TRUE; 
}


void CTextureLJ::InitTexture()
{
	CString tt;
	m_list.ResetContent();//���
	for(int i=1;i<=12;i++)  //�����ļ�����(�ɸ���ʵ�ʵ����������и���)
	{
		tt.Format("%d.bmp",i);
		m_list.AddString(tt);		//�����б��ؼ���
	}

	m_list.SetCurSel(0);//Ĭ��ѡ����Ϊ��1������
	OnSelchangeList(); //��Ӧ����ѡ��ı�ʱ����Ϣ
}

//��Ӧ����ѡ��ı�ʱ����Ϣ
void CTextureLJ::OnSelchangeList() 
{
	m_list.GetText(m_list.GetCurSel(),m_LJtextureName);//�õ������ļ���
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect);//�õ�IDC_STATIC_BMP�ؼ��Ŀͻ�����С
	this->ScreenToClient(rect); //����Ļ����ת�����û�����
	CString BitmapFilePath;
	BitmapFilePath="./����\\·��\\"+m_LJtextureName;//�����ļ�ȫ·������
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect);	//��ѡ�е�����Ӱ����IDC_STATIC_BMP�ϻ���
}
