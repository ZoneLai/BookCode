// TextureBP.cpp : implementation file
 

#include "stdafx.h"
#include "T3DSystem.h"
#include "TextureBP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

 
// CTextureBP dialog


CTextureBP::CTextureBP(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureBP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextureBP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTextureBP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextureBP)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextureBP, CDialog)
	//{{AFX_MSG_MAP(CTextureBP)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

 
// CTextureBP message handlers

//��ʼ����Ϣ
BOOL CTextureBP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitTexture();//��ʼ���������ƣ�����д���б��ؼ��� 
	return TRUE; 
}

//��ʼ���������ƣ�����д���б��ؼ��� 
void CTextureBP::InitTexture()
{
	CString tt;
	m_list.ResetContent(); //���
	for(int i=1;i<=6;i++)  //�����ļ�����(�ɸ���ʵ�ʵ����������и���)
	{
		tt.Format("���λ���%d.bmp",i); //�����ļ�����(�ɸ���ʵ�ʵ������ļ����ƽ��и���)
		m_list.AddString(tt);	//�����б��ؼ���
	}
	for(i=1;i<=6;i++)  
	{
		tt.Format("���λ���%d.bmp",i);//�����ļ�����(�ɸ���ʵ�ʵ������ļ����ƽ��и���)
		m_list.AddString(tt);		//�����б��ؼ���
	}
	m_list.AddString("���ιǼ�.bmp");//�����б��ؼ���
	m_list.AddString("ƽ�λ���.bmp");//�����б��ؼ���

	m_list.SetCurSel(0);//Ĭ��ѡ����Ϊ��1������
	OnSelchangeList(); //��Ӧ����ѡ��ı�ʱ����Ϣ
}

//��Ӧ����ѡ��ı�ʱ����Ϣ
void CTextureBP::OnSelchangeList() 
{
	m_list.GetText(m_list.GetCurSel(),m_BPtextureName);//�õ������ļ���
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect); //�õ�IDC_STATIC_BMP�ؼ��Ŀͻ�����С
	this->ScreenToClient(rect); //����Ļ����ת�����û�����
	CString BitmapFilePath;
	
	BitmapFilePath="./����\\���·���\\"+m_BPtextureName;//�����ļ�ȫ·������
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect); //��ѡ�е�����Ӱ����IDC_STATIC_BMP�ϻ���
}
