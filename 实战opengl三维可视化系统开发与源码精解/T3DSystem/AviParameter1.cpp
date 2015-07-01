// AviParameter1.cpp : implementation file
//

#include "stdafx.h"
#include "T3DSystem.h"
#include "AviParameter1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAviParameter dialog


CAviParameter::CAviParameter(CWnd* pParent /*=NULL*/)
	: CDialog(CAviParameter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAviParameter)
	m_AviFilename = _T("");
	m_AVIFrame = 0;
	m_AVIHeight = 0;
	m_AVIWidth = 0;
	//}}AFX_DATA_INIT
}


void CAviParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAviParameter)
	DDX_Control(pDX, IDC_SLIDER_MOVIE_WIDTH, m_Slider_AVIWidth);
	DDX_Control(pDX, IDC_SLIDER_MOVIE_HEIGHT, m_Slider_AVIHeight);
	DDX_Control(pDX, IDC_SLIDER_FRAME, m_slider_frame);
	DDX_Text(pDX, IDC_EDIT_FILENAME, m_AviFilename);
	DDX_Text(pDX, IDC_EDIT_FRAME, m_AVIFrame);
	DDX_Text(pDX, IDC_EDIT_MOVIE_HEIGHT, m_AVIHeight);
	DDX_Text(pDX, IDC_EDIT_MOVIE_WIDTH, m_AVIWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAviParameter, CDialog)
	//{{AFX_MSG_MAP(CAviParameter)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnButtonBrowse)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAviParameter message handlers

//����AVI�ļ�
void CAviParameter::OnButtonBrowse() 
{
	CString s;
	s="Microsoft AVI (*.avi)|*.avi||";
	CFileDialog fd(FALSE,"avi",0,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,s);
	if(fd.DoModal ()==IDOK) //����ļ��Ի���򿪳ɹ�
	{
		m_AviFilename=fd.GetPathName();  //�õ������ļ���
		this->UpdateData (FALSE); //���ݸ���
		if(m_AviFilename.IsEmpty ()) //��������ļ���Ϊ��
		{
			this->MessageBox ("�ļ�������Ϊ��!","�����ļ�����",MB_OK|MB_ICONERROR);
			return; //����
		}
	}
}

//��ӦIDOK��ť��Ϣ
void CAviParameter::OnOK() 
{
	if(this->UpdateData ()==TRUE )
	{
		if(m_AviFilename.IsEmpty ()) //�����Ƶ�����ļ���Ϊ�գ�����
			return;
		this->EndDialog (IDOK); 
	}		
	
	CDialog::OnOK();
}

//��ʼ����Ϣ
BOOL CAviParameter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_slider_frame.SetRange (1,30); //���ò�׽֡�ʷ�Χ
	m_slider_frame.SetPos (m_AVIFrame); //���ò�׽֡�ʳ�ʼֵ
	
	m_Slider_AVIWidth.SetRange (1,m_MoviemaxWidth);//���ò�׽�����ȷ�Χ
	m_Slider_AVIHeight.SetRange (1,m_MoviemaxHeight);//���ò�׽�����ȳ�ʼֵ
	
	m_Slider_AVIWidth.SetPos (m_MovieWidth);//���ò�׽����߶ȷ�Χ
	m_Slider_AVIHeight.SetPos (m_MovieHeight);//���ò�׽����߶ȳ�ʼֵ
	
	m_AVIHeight=m_MovieWidth; //�����߶�
	m_AVIWidth=m_MovieHeight;//�������
	
    this->UpdateData (FALSE); //���¿ؼ�����

	return TRUE;  
}

//��Ӧˮƽ��������Ϣ
void CAviParameter::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	this->UpdateData(TRUE); //���±�������
	
	switch(pScrollBar->GetDlgCtrlID())
	{
	case  IDC_SLIDER_FRAME: //����ǲ�׽֡��
		m_AVIFrame=m_slider_frame.GetPos (); //�õ���׽֡��
		break;
	case  IDC_SLIDER_MOVIE_WIDTH://����ǲ�׽������
		m_AVIWidth=m_Slider_AVIWidth.GetPos (); //�õ�AVI�Ŀ��
		m_MovieWidth=m_AVIWidth;
		break;
	case  IDC_SLIDER_MOVIE_HEIGHT://����ǲ�׽����߶�
		m_AVIHeight=m_Slider_AVIHeight.GetPos (); //�õ�AVI�ĸ߶�
		m_MovieHeight=m_AVIHeight;
		break;
	}
	
    this->UpdateData(FALSE);//���¿ؼ�����
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
