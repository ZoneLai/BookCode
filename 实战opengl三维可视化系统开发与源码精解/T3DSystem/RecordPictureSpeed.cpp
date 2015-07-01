// RecordPictureSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "T3DSystem.h"
#include "RecordPictureSpeed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordPictureSpeed dialog


CRecordPictureSpeed::CRecordPictureSpeed(CWnd* pParent /*=NULL*/)
	: CDialog(CRecordPictureSpeed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRecordPictureSpeed)
	m_recordPictSpeed = 0;
	//}}AFX_DATA_INIT
}


void CRecordPictureSpeed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRecordPictureSpeed)
	DDX_Control(pDX, IDC_SLIDER_RECORDPICTURE_SPEED, m_slider_recordpictSpeed);
	DDX_Text(pDX, IDC_EDIT_RECORDPICTURESPEED, m_recordPictSpeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRecordPictureSpeed, CDialog)
	//{{AFX_MSG_MAP(CRecordPictureSpeed)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRecordPictureSpeed message handlers

//��ʼ����Ϣ
BOOL CRecordPictureSpeed::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_slider_recordpictSpeed.SetRange (1,2000); //���òɼ�ͼ���Ƶ�ʷ�Χ����ÿ�����ٺ���¼��һ��ͼ��
	m_slider_recordpictSpeed.SetPos (m_recordPictSpeed); //���õ�ǰ�ɼ�ͼ���Ƶ��
    this->UpdateData (FALSE); //���ݸ���
	
	
	return TRUE;  
}

//��Ӧˮƽ��������Ϣ
void CRecordPictureSpeed::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	this->UpdateData(TRUE); //���±�������
	
	//�����IDC_SLIDER_RECORDPICTURE_SPEED�ؼ�
	if(pScrollBar->GetDlgCtrlID() ==IDC_SLIDER_RECORDPICTURE_SPEED)
	{
		m_recordPictSpeed=m_slider_recordpictSpeed.GetPos (); //�õ������õĲɼ�ͼ��Ƶ��
		this->UpdateData(FALSE);//���ݸ���
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
