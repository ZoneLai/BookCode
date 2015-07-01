// ModelMangerQD.cpp : implementation file
//

#include "stdafx.h"
#include "T3DSystem.h"
#include "ModelMangerQD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModelMangerQD dialog


CModelMangerQD::CModelMangerQD(CWnd* pParent /*=NULL*/)
	: CDialog(CModelMangerQD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModelMangerQD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModelMangerQD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModelMangerQD)
	DDX_Control(pDX, IDC_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModelMangerQD, CDialog)
	//{{AFX_MSG_MAP(CModelMangerQD)
	ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModelMangerQD message handlers

void CModelMangerQD::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}


//��ʼ����Ϣ
BOOL CModelMangerQD::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitData(); //��ʼ���Ŷ�ģ��
	
	return TRUE;  
}

//��ʼ���Ŷ�ģ��
void CModelMangerQD::InitData()
{
	m_list.ResetContent(); //���
	m_list.AddString("��ʽ���Զ�");
	m_list.AddString("����ʽ�Ŷ�");
	m_list.AddString("�ռ�ʽ���Զ�");
	m_list.AddString("���˫��ʽ�Ŷ�");
	m_list.AddString("�ż�׮���Զ�");
	m_list.AddString("�����¸ն�");
	m_list.AddString("˫��ʽ�Ŷ�");
	m_list.AddString("����ʽ�Ŷ�");
	m_list.AddString("����ʽ�����Ŷ�");
	m_list.AddString("����ʽԲ�����Ŷ�");
	m_list.AddString("����ʽԲ���Ŷ�");
	m_list.AddString("���ʽƴװ�Ŷ�");
	m_list.SetCurSel(0); //Ĭ��ѡ����Ϊ��1��ģ��
	
}

//��Ӧģ��ѡ��ı�ʱ����Ϣ
void CModelMangerQD::OnSelchangeList() 
{
	CString BitmapFilePath,strFilename,tt;
	
	int index=m_list.GetCurSel(); //�õ��б�ռ���ǰ����
	if(index<0) //�����ǰ����<0������
		return;
	
	m_list.GetText(index,tt); //�õ�ģ���ļ���
	
	strFilename.Format("%s\\%s.bmp",tt,tt);
	CDC *pdc=GetDC();
	CRect rect;
	GetDlgItem(IDC_STATIC_BMP)->GetWindowRect(rect);//�õ�IDC_STATIC_BMP�ؼ��Ŀͻ�����С
	this->ScreenToClient(rect);//����Ļ����ת�����û�����
	
	BitmapFilePath=".\\ģ��\\������̨\\"+strFilename;
	m_3DSfilename_QD.Format(".\\ģ��\\������̨\\%s\\ģ���ļ�.3ds",tt);//�õ�ģ�Ͱ�������·�����ļ���

	//��ѡ�е�ģ��Ӱ����IDC_STATIC_BMP�ϻ���
	myDesingScheme.drawBitmapFormFile(BitmapFilePath,pdc,rect);	
	
	
}
