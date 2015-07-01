// T3DSystemView.cpp : implementation of the CT3DSystemView class
//

#include "stdafx.h"
#include "T3DSystem.h"

#include "T3DSystemDoc.h"
#include "T3DSystemView.h"
#include "MainFrm.h"
#include "OpenProject.h"
#include "SpaceSearchSet.h"
#include "PLaneRL0.h"
#include "TunncelPropertySet.h"
#include "BridgeSet.h"
#include "TextureBP.h"
#include "TextureLJ.h"
#include "TextureQLHpm.h"
#include "TextureTunnel.h"
#include "TextureTunnelDm.h"
#include "ModelMangerQD.h"
#include "DXF.h"
#include "AviParameter.h"
#include "RecordPictureSpeed.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PAI 3.1415926       //����г���
#define HDANGLE  52.706     //����1���ȵ��ڶ��ٶ�(1����=180/PAI)
#define PAI_D180  PAI/180   //����1�ȵ��ڶ��ٻ���(1��=PAI/180����)

char g_sMediaPath[512];
UINT g_Texture[100] = {0};

GLfloat LightAmbient  [] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse  [] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition [] = { 0.0f, 0.0f, 2.0f, 1.0f };

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView

IMPLEMENT_DYNCREATE(CT3DSystemView ,  CView)

BEGIN_MESSAGE_MAP(CT3DSystemView ,  CView)
	//{{AFX_MSG_MAP(CT3DSystemView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MENU_OPENPROJECT ,  OnMenuOpenproject)
	ON_COMMAND(ID_DRAWMODE_LINE ,  OnDrawmodeLine)
	ON_COMMAND(ID_DRAWMODE_RENDER ,  OnDrawmodeRender)
	ON_COMMAND(ID_DRAWMODE_TEXTURE ,  OnDrawmodeTexture)
	ON_COMMAND(ID_SPACEQUERY_SET ,  OnSpacequerySet)
	ON_COMMAND(ID_QUERY_COORDINATE ,  OnQueryCoordinate)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_QUERY_DISTENCE ,  OnQueryDistence)
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENU_STEREO, OnMenuStereo)
	ON_UPDATE_COMMAND_UI(ID_MENU_STEREO, OnUpdateMenuStereo)
	ON_COMMAND(ID_MENU_PROJECTTIONORTHO, OnMenuProjecttionortho)
	ON_UPDATE_COMMAND_UI(ID_MENU_PROJECTTIONORTHO, OnUpdateMenuProjecttionortho)
	ON_COMMAND(ID_ORTHO_ZOOMIN, OnOrthoZoomIn)
	ON_UPDATE_COMMAND_UI(ID_ORTHO_ZOOMIN, OnUpdateOnOrthoZoomIn)
	ON_COMMAND(ID_ORTHO_ZOOMOUT, OnOrthoZoomOut)
	ON_UPDATE_COMMAND_UI(ID_ORTHO_ZOOMOUT, OnUpdateOnOrthoZoomOut)
	ON_COMMAND(ID_ORTHO_PAN, OnOrthoPan)
	ON_UPDATE_COMMAND_UI(ID_ORTHO_PAN, OnUpdateOnOrthoPan)
	ON_COMMAND(ID_ORTHO_ZOOMORIGIN, OnOrthoZoomOrigin)
	ON_UPDATE_COMMAND_UI(ID_ORTHO_ZOOMORIGIN, OnUpdateOnOrthoZoomOrigin)
	ON_COMMAND(ID_ORTHO_ZOOWINDOW, OnOrthoZoomWindow)
	ON_UPDATE_COMMAND_UI(ID_ORTHO_ZOOWINDOW, OnUpdateOnOrthoZoomWindow)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_MENU_LINEDESIGN, OnMenuLinedesign)
	ON_UPDATE_COMMAND_UI(ID_MENU_LINEDESIGN, OnUpdateMenuLinedesign)
	ON_UPDATE_COMMAND_UI(ID_QUERY_COORDINATE, OnUpdateQueryCoordinate)
	ON_UPDATE_COMMAND_UI(ID_QUERY_DISTENCE, OnUpdateQueryDistence)
	ON_COMMAND(ID_MENU_LINESAVESCHEME, OnMenuLinesavescheme)
	ON_UPDATE_COMMAND_UI(ID_MENU_PERSPECTIVE, OnUpdateMenuPerspective)
	ON_COMMAND(ID_MENU_PERSPECTIVE, OnMenuPerspective)
	ON_COMMAND(ID_MENU_BUILD3DLINEMODLE, OnMenuBuild3dlinemodle)
	ON_COMMAND(ID_FLY_ROUTINSCHEMELINE, OnFlyRoutinschemeline)
	ON_WM_TIMER()
	ON_COMMAND(ID_FLY_STOP, OnFlyStop)
	ON_COMMAND(ID_MENU_TUNNELSET, OnMenuTunnelset)
	ON_COMMAND(ID_MENU_BRIDGESET, OnMenuBridgeset)
	ON_COMMAND(ID_MENU_TEXTUREBP, OnMenuTexturebp)
	ON_COMMAND(ID_MENU_TEXTURELJ, OnMenuTexturelj)
	ON_COMMAND(ID_MENU_TEXTUREQLHPM, OnMenuTextureqlhpm)
	ON_COMMAND(ID_MENU_TEXTURETUNNEL, OnMenuTexturetunnel)
	ON_COMMAND(ID_MENU_TEXTURETUNNEL_DM, OnMenuTexturetunnelDm)
	ON_COMMAND(ID_PATH_MANUINPUT, OnPathManuinput)
	ON_COMMAND(ID_FLYPATH_SAVE, OnFlypathSave)
	ON_COMMAND(ID_FLPPATH_INTERPOLATION, OnFlppathInterpolation)
	ON_COMMAND(ID_FLY_OPENPATH, OnFlyOpenpath)
	ON_COMMAND(ID_FLY_ONOFFPATH, OnFlyOnoffpath)
	ON_UPDATE_COMMAND_UI(ID_FLY_ONOFFPATH, OnUpdateFlyOnoffpath)
	ON_COMMAND(ID_FLY_STATICHEIGHT, OnFlyStaticheight)
	ON_UPDATE_COMMAND_UI(ID_FLY_STATICHEIGHT, OnUpdateFlyStaticheight)
	ON_COMMAND(ID_FLY_ROUTINEHEIGHT, OnFlyRoutineheight)
	ON_UPDATE_COMMAND_UI(ID_FLY_ROUTINEHEIGHT, OnUpdateFlyRoutineheight)
	ON_COMMAND(ID_FLY_PLAYPAUSE, OnFlyPlaypause)
	ON_UPDATE_COMMAND_UI(ID_FLY_PLAYPAUSE, OnUpdateFlyPlaypause)
	ON_COMMAND(ID_FLY_ONESTEP, OnFlyOnestep)
	ON_COMMAND(ID_FLY_VIEW_ENLARGE, OnFlyViewEnlarge)
	ON_COMMAND(ID_FLY_VIEW_SMALL, OnFlyViewSmall)
	ON_COMMAND(ID_FLY_HEIGHT_UP, OnFlyHeightUp)
	ON_COMMAND(ID_FLY_HEIGHT_DOWN, OnFlyHeightDown)
	ON_COMMAND(ID_FLY_VIEW_DOWN, OnFlyViewDown)
	ON_COMMAND(ID_FLY_VIEW_UP, OnFlyViewUp)
	ON_COMMAND(ID_FLY_SPEED_UP, OnFlySpeedUp)
	ON_COMMAND(ID_FLY_SPEED_DOWN, OnFlySpeedDown)
	ON_COMMAND(ID_MENU_MODLEQD, OnMenuModleqd)
	ON_COMMAND(ID_MENU_OUPTCAD3DLINEMODEL, OnMenuOuptcad3dlinemodel)
	ON_COMMAND(ID_AVI_PARAMETER, OnAviParameter)
	ON_COMMAND(ID_AVI_START, OnAviStart)
	ON_COMMAND(ID_AVI_PAUSE, OnAviPause)
	ON_COMMAND(ID_AVI_END, OnAviEnd)
	ON_COMMAND(ID_SAVEPICTURE_SPEED, OnSavepictureSpeed)
	ON_COMMAND(ID_SAVEPICTURE_CONTINUE, OnSavepictureContinue)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_SAVEPICTURE_STOP, OnSavepictureStop)
	ON_COMMAND(ID_MENU_SAVESCREENTOBMP, OnMenuSavescreentobmp)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT ,  CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT ,  CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW ,  CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView construction/destruction

PBlockTriInfos tempBlockTriInfos;

class GetBlockTriangles
{
public:
	GetBlockTriangles(long blockIndex) : MyblockIndex(blockIndex){}
	void operator()(const triangle& tri) const
	{
		
		const vertex * v0 = tri.GetVertex(0);
		const vertex * v1 = tri.GetVertex(1);
		const vertex * v2 = tri.GetVertex(2);
		
		
		PTriPt tempptript=new TriPt;
		tempptript->Pt1.x=v0->GetX(); tempptript->Pt1.y=v0->GetY();	tempptript->Pt1.z=v0->GetZ();
		tempptript->Pt2.x=v1->GetX(); tempptript->Pt2.y=v1->GetY();	tempptript->Pt2.z=v1->GetZ();
		tempptript->Pt3.x=v2->GetX(); tempptript->Pt3.y=v2->GetY();	tempptript->Pt3.z=v2->GetZ();
		tempBlockTriInfos->TriPts.Add(tempptript);
		
		
		
		
	}
protected:
	long MyblockIndex;
};


CT3DSystemView::CT3DSystemView()
{
	Init_data() ; // ��ʼ����ر���
	m_lpThread  = NULL;
	
}

CT3DSystemView::~CT3DSystemView()
{
}

BOOL CT3DSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	//���ô�������
	cs.style|=WS_CLIPCHILDREN|WS_CLIPSIBLINGS;
	return CView::PreCreateWindow(cs);
	
}

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView drawing

//������ά����
void CT3DSystemView::OnDraw(CDC* pDC)
{
	CT3DSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
//	m_snows.DrawSnow ();
//	return;

	if (pDC->IsPrinting()) 
	{
		CRect rcDIB;
		GetClientRect(&rcDIB);
		
		m_rcPrintRect=rcDIB;
		
		pDC->DPtoLP(&rcDIB);
		
		rcDIB.right = rcDIB.Width();
		rcDIB.bottom = rcDIB.Height();
		
		// ��ô�ӡ��ҳ��ߴ�(����)
		int cxPage = pDC->GetDeviceCaps(HORZRES);
		int cyPage = pDC->GetDeviceCaps(VERTRES);
		// ��ô�ӡ��ÿӢ���ϵ����ظ���
		int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
		int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);
		
		CRect rcDest;
		rcDest.top = rcDest.left = 0;
		rcDest.bottom = (int)(((double)rcDIB.Height() * cxPage * cyInch)
			/ ((double)rcDIB.Width() * cxInch));
		rcDest.right = cxPage;
		CapturedImage.OnDraw(pDC->m_hDC, &rcDest, &rcDIB);
	}
	else 
	{
		wglMakeCurrent( pDC->m_hDC, m_hRC );// ʹ RC �뵱ǰ DC �����
		DrawScene() ; // ��������
		if (m_movieCapture != NULL && m_Recording)
		{
			m_movieCapture->captureFrame();
		}
		glFlush();	
		::SwapBuffers(m_pDC->GetSafeHdc());	//����������	 
	}
	

}

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView printing

BOOL CT3DSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CT3DSystemView::OnBeginPrinting(CDC* /*pDC*/ ,  CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CT3DSystemView::OnEndPrinting(CDC* /*pDC*/ ,  CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView diagnostics

#ifdef _DEBUG
void CT3DSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CT3DSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CT3DSystemDoc* CT3DSystemView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CT3DSystemDoc)));
	return (CT3DSystemDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CT3DSystemView message handlers

int CT3DSystemView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//��ȡ�ͻ������豸������
	m_pDC=new CClientDC(this); 

	//��ʼ��OpenGL
	InitializeOpenGL(m_pDC); 
	InitList() ; // ��ʼ����ʾ�б�	
	
	return 0; 

}

BOOL CT3DSystemView::InitializeOpenGL(CDC *pDC)
{
	//����opengl�ĳ�ʼ������
	m_pDC=pDC; 
	//���Ȱ�DC�����ظ�ʽ����Ϊָ���ĸ�ʽ���Ա�����DC��ʹ��
	SetupPixelFormat(); 
	//����DC������RC
	m_hRC=::wglCreateContext(m_pDC->GetSafeHdc()); 
	//���õ�ǰ��RC���Ժ�Ļ�ͼ����������m_pDCָ���DC��
	::wglMakeCurrent(m_pDC->GetSafeHdc() , m_hRC); 
	

	//�жϵ�ǰϵͳ��OpenGL�汾�Ƿ�֧�ֶ���������չ  �ж��Կ��Ƿ�֧�ָ���չ
	glActiveTextureARB		= (PFNGLACTIVETEXTUREARBPROC)		wglGetProcAddress("glActiveTextureARB");
	glMultiTexCoord2fARB	= (PFNGLMULTITEXCOORD2FARBPROC)		wglGetProcAddress("glMultiTexCoord2fARB");
	
	if(!glActiveTextureARB || !glMultiTexCoord2fARB)
	{
		MessageBox("��ǰOpenGL�汾�ϵͣ���֧�ֶ�������\n��չ���ܣ������ذ�װ�µİ汾��" ,  "����������չ����" ,  MB_ICONSTOP);
		return FALSE;
	}

	m_cTxtSky.LoadGLTextures("Sky.bmp");	//���ر�����յ�����Ӱ��

	m_cTxtureBP.LoadGLTextures("����\\���·���\\���λ���1.bmp");
	m_cTxtureLJ.LoadGLTextures("����\\·��\\1.bmp");
	m_cTxtureGdToLJ.LoadGLTextures("����\\·��\\10.bmp");
	m_cTxtureSuigou.LoadGLTextures("����\\ˮ��\\ˮ��1.bmp");
	m_cTxturePT.LoadGLTextures("����\\����ƽ̨\\����ƽ̨1.bmp");
	m_cTxtureRailway.LoadGLTextures("����\\��·\\��·1.bmp");
	m_cBridgeHpm.LoadGLTextures("����\\���·�������\\1.bmp");//��ͷ�·�����������
	m_cTunnel.LoadGLTextures("����\\�����ǽ\\1.bmp"); //�����ǽ����
	m_cTunnel_dm.LoadGLTextures("����\\�������\\2.bmp");//�����������
	m_cTunnel_dmwcBp.LoadGLTextures("����\\�������������\\2.bmp");//�������������*/

	
	return TRUE;

	

}

BOOL CT3DSystemView::SetupPixelFormat()
{
	//��ʼ�����ظ�ʽ�Լ�ѡȡ���ʵĸ�ʽ������RC
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR) ,  // pfd�ṹ�Ĵ�С 
			1 ,  // �汾��
			PFD_DRAW_TO_WINDOW | // ֧���ڴ����л�ͼ 
			PFD_SUPPORT_OPENGL | // ֧�� OpenGL 
			PFD_DOUBLEBUFFER| // ˫����ģʽ
			PFD_STEREO |  //֧������ģʽ
			PFD_TYPE_RGBA ,  // RGBA ��ɫģʽ 
			24 ,  // 24 λ��ɫ���
			0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  // ������ɫλ 
			0 ,  // û�з�͸���Ȼ��� 
			0 ,  // ������λλ 
			0 ,  // ���ۼӻ��� 
			0 ,  0 ,  0 ,  0 ,  // �����ۼ�λ 
			32 ,  // 32 λ��Ȼ��� 
			0 ,  // ��ģ�建�� 
			0 ,  // �޸������� 
			PFD_MAIN_PLANE ,  // ���� 
			0 ,  // ���� 
			0 ,  0 ,  0 // ���Բ� , �ɼ��Ժ������ģ 
	}; 
	//��DC��ѡ����ʵ����ظ�ʽ������������
	int pixelformat;
	pixelformat=::ChoosePixelFormat(m_pDC->GetSafeHdc() , &pfd);
	if (pixelformat==0)
	{
		MessageBox("ѡ�����ظ�ʽʧ��!" , "�������ظ�ʽ" , MB_ICONERROR);
		return FALSE;
	}
	//����ָ�����ظ�ʽ
	if (::SetPixelFormat(m_pDC->GetSafeHdc() , pixelformat , &pfd)==FALSE)
	{
		MessageBox("�������ظ�ʽʧ��!" , "�������ظ�ʽ" , MB_ICONERROR);
		return FALSE;
	}

	

	//���Ե�ǰ���ú�Ӳ���Կ��Ƿ�֧������ģʽ
	unsigned char ucTest;
    glGetBooleanv (GL_STEREO ,  &ucTest);  
    if (!ucTest) 
	{
		return 1;
	}
	
	
	if((pfd.dwFlags & PFD_STEREO)==0)
		bStereoAvailable=FALSE ; // �Կ���֧������ģʽ
	else
		bStereoAvailable=TRUE;
	
	CString stt[5];
	if(bStereoAvailable==FALSE) //����Կ���֧������ģʽ���������ܵĴ���ԭ��
	{
		stt[0]="��.ͼ�ο���֧�����建��;\n";
		stt[1]="��.ͼ�ο���������֧�����建��;\n";
		stt[2]="��.ֻ�����ض��Ľ����Ȼ�ˢ���������� , �ſ���֧�����建��;\n";
		stt[3]="��.���建����Ҫ�ض������������Լ���;";
		stt[4].Format("����ģʽδ������.����������ԭ��:\n%s%s%s%s" , stt[0] , stt[1] , stt[2] , stt[3]);
		MessageBox(stt[4] , "����ģʽ����" , MB_ICONINFORMATION);
	}
	
	
}

void CT3DSystemView::OnSize(UINT nType ,  int cx ,  int cy) 
{
	CView::OnSize(nType ,  cx ,  cy);


	if(cy>0)
	{
		WinViewX = cx ; // �ӿڿ��
		WinViewY = cy ; // �ӿڸ߶�
		glViewport(0 , 0 , cx , cy); //�����ӿڴ�С
        m_aspectRatio = (float)cx/(float)cy ; // �ӿڵĺ��ݱ���
		glMatrixMode(GL_PROJECTION); //����ǰ��������ΪͶӰ����,ָ����ǰ����ΪGL_PROJECTION 
		glLoadIdentity();    //����ǰ�����û�Ϊ��λ��        
		gluPerspective(50.0 + m_ViewWideNarrow , m_aspectRatio , m_near , m_far);		//:fovy=50.0 + m_ViewWideNarrow , ����Ұ�Ƕ�
		m_FrustumAngle=2*asin(0.5*m_aspectRatio*tan((50.0 + m_ViewWideNarrow)*PAI_D180))*HDANGLE;
		m_es=m_SCREEN_HEIGHT*cos(m_viewdegree*PAI_D180)/(2*tan(m_FrustumAngle/2.0*PAI_D180));
		glMatrixMode(GL_MODELVIEW);	//����ǰ��������Ϊģ�;���		
		glLoadIdentity();	//����ǰ�����û�Ϊ��λ�� 
	}			
}

//�������
BOOL CT3DSystemView::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	
}

//��ʼ����ر���
void CT3DSystemView::Init_data()
{
	m_ViewWideNarrow = 0.0f;	//��ʼ�����ӿڿ�խ����
	CWindowDC dc=NULL;
	m_SCREEN_WIDTH = ::GetDeviceCaps(dc , HORZRES);	//��Ļ���
	m_SCREEN_HEIGHT = ::GetDeviceCaps(dc , VERTRES);	//��Ļ�߶�
	m_near=1;	//�۲����������ƽ��ľ���
	m_far=5000 ; // �۲����Զ�����ƽ��ľ���

	m_currebtPhramid=0 ; // ��ǰӰ�������LOD����
	mTimeElaps=0 ; // ���ڼ���֡�ʵ�ʱ��ֵ
	
	m_stereo=FALSE; //�ر�����ģʽ
	m_Drawmode=3 ; // ����ģʽ(1://�߿�ģʽ  2://����ģʽ	3://����ģʽ)
	
	
	m_bCamraInit=FALSE ; // ���δ��ʼ��
    m_bLoadInitDemData=FALSE ; // ���κ�Ӱ������δ���� 
	m_LodDemblockNumber=0 ; // ���ص��ο�������ʼΪ0
	m_RenderDemblockNumber=0 ; // ��Ⱦ���ο�������ʼΪ0
	
	//�����������ʸ��
	m_vUpVector.x=0; 
	m_vUpVector.y=1;
	m_vUpVector.z=0;
	
	
	m_viewdegree=0 ; // ��ʼ�ӽ����� 
	m_viewHeight=m_oldviewHeight=10 ; // �����ʼ�߶�
	m_camraDistence=80 ; // ˫Ŀ����ģʽ�µ����������ʼ���
	m_heighScale=1.0 ; // �߳�����ϵ��

	m_Radius=50000 ; // ��Χ��뾶
	m_R=5500 ; // 
	m_r=3500 ; // 

	m_BhasInitOCI=FALSE;	//��ʼOCIδ��ʼ��
	mTimeElaps=0 ; // ���ڼ���֡�ʵ�ʱ��ֵ
	
	m_maxHeight=-9999 ; // ��ʼ���߳�
	m_minHeight=9999 ; // ��ʼ��С�߳�

	//DE�������̺߳���С�̶߳�Ӧ����ɫ��ʼֵ
	minZ_color_R=0;minZ_color_G=1;minZ_color_B=0 ; // ��ɫ
	maxZ_color_R=1;maxZ_color_G=0;maxZ_color_B=0 ; // ��ɫ
	
// 	m_bShowbreviary=TRUE ; // �Ƿ���ʾ����ͼ

	m_shizxLength=20 ; // ��ѯ��־ʮ���߳���
	m_shuzxHeight=45 ; // ��ѯ��־��ֱ�߸߶�
	m_QueryLineWidth=1 ; // ��ѯ��־�ߵĿ��
	m_QueryColorR=255 ; // ��ѯ��־�ߵ���ɫ(��)
	m_QueryColorG=255 ; // ��ѯ��־�ߵ���ɫ(��)
	m_QueryColorB=0 ; // ��ѯ��־�ߵ���ɫ(��)
	m_bSearchDistencePtNums=0;

	Derx=0;	//�����X�����ϵĳ�ʼ�仯��
	Derz=0;	//�����Z�����ϵĳ�ʼ�仯��
	m_Step_X=5.0;	//�����X�����ƶ��Ĳ�����ʼֵ(������)
	m_Step_Z=5.0;	//�����Z�����ƶ��Ĳ�����ʼֵ(������)
	m_xTrans=0;	//��X�������ƶ��Ĳ���(���̿���)
	m_zTrans=0;	//��Z�������ƶ��Ĳ���(���̿���)

	m_OrthoViewSize=0.3;//����ͶӰģʽ���Ӿ����С
	m_OrthotranslateX=m_OrthotranslateY=0;//����ͶӰX�᷽���Y�᷽���ƶ��ľ����ֵ

	m_ViewType=GIS_VIEW_PERSPECTIVE;

	b_haveMadeRail3DwayList=FALSE; //�Ƿ��Ѿ�����ά��·��ʾ�б�(͸��ͶӰģʽ��)
	b_haveMadeRail3DwayList_Ortho=FALSE;//�Ƿ��Ѿ�����ά��·��ʾ�б�(����ͶӰģʽ��)
	b_haveTerrainZoomroadList=FALSE; //��·��ά��ģ���Ƿ����˵���TINģ�͵���ʾ�б�

	//��ʼ���й̶��߶ȱ���
	m_StaticHeight = 80.0f;
	
	//��ʼ�����ӿ����������
	m_ViewUpDown = 0.0f;
	
	//��ʼ�����ӿڿ�խ����
	m_ViewWideNarrow = 0.0f;
	
	m_flyspeed=10;//�����ٶ�
	
	
	m_PreZooomLC=m_CurZooomLC=0;//����ʱǰһ��̺͵�ǰ���

	b_haveGetRegion=FALSE;//��ʶ�Ƿ�����·�������
	
	
	m_bridgeColorR=0; //����������ɫ
	m_bridgeColorG=0;//����������
	m_bridgeColorB=255;//����������
	m_Bridge.m_Bridge_HLHeight=2.0; //�������˸�
	m_Bridge.m_Bridge_HLSpace=10;//�������˼��
	m_Bridge.m_Bridge_HLWidth=3.0;//�������˿��
    m_Bridge.m_Bridge_QDSpace=40;//�Ŷռ��
	m_Bridge.m_Bridge_HPangle=45;//��ͷ�������
	m_3DSfilename_QD=".\\ģ��\\������̨\\�ռ�ʽ���Զ�\\ģ���ļ�.3DS";
	
	
	m_Railway.m_Railway_width=2.5;//·�������ܿ��
	m_Railway.m_Lj_width=0.8;//·����
	m_Railway.m_GuiMianToLujianWidth=0.6;//�������ŵĸ߶�
	m_Railway.m_Lj_Dh=m_Railway.m_GuiMianToLujianWidth*(1/1.75);//���쵽���ľ���
	m_Railway.m_TieGui_width=1.435;//������
	
	m_Tunnel.height=6.55; //����ܸ߶�
	m_Tunnel.Archeight=2;//���Բ���߶�
	m_Tunnel.WallHeight=m_Tunnel.height-m_Tunnel.Archeight;////�����ǽ�߶�
	m_Tunnel.ArcSegmentNumber=20;//���Բ���ֶ���
	m_Tunnel.H=1.5;//���Բ�����������ϵĸ߶�(m_Tunnel.height+m_Tunnel.H=��������ܸ߶�)
	m_Tunnel.L=4.0;//������Ŷ���������������Ŀ�� 
	m_Tunnel.width=m_Railway.m_Railway_width+2*(m_Railway.m_Lj_width+m_Railway.m_GuiMianToLujianWidth);
	
	
	m_shizxLength=20;
	m_shuzxHeight=45;

	m_NorthPtangle=90;//ָ�����ʼָ��Ƕ�(90��,����ʾ��������,����ά�ռ�����ָ��ZԱ������,��ָ����Ļ����)
	
	m_bShowbreviary=TRUE;//��ʾ������ͼ

	m_PathFlag=FALSE;//�Ƿ�ɹ��򿪷���·��
	m_FlyPause=FALSE;//��ʶ�Ƿ���ͣ����
	
	
	m_3DSfilename_QD=".\\ģ��\\������̨\\�ռ�ʽ���Զ�\\ģ���ļ�.3DS";
	
	
	DeleteFile("c:\\TEMP.AVI"); //ɾ��c:\\TEMP.AVI�ļ�
    m_AviFilename="c:\\TEMP.AVI"; //AVI������ʼ�ļ���
	m_AVIFrame=15; //AVIƵ��
	m_Recording=false; //��ʶ�Ƿ����ڲ�׽��Ƶ����
	
	m_RecordPicture=FALSE;     //¼��ͼ�����еı�־	
    m_recordPictSpeed=100;	//¼��ͼ���֡��
	m_PictureNumbers=0; //¼��ͼ������
	
}

//�����ӿ��Ӱ���ӿ�ĵ���
BOOL CT3DSystemView::LoadInitDemData()
{
	if(theApp.bLoadImage==FALSE)//���Ӱ�����ʧ�� , ���� 
        return FALSE;

	if(theApp.bLoginSucceed==FALSE) //������ݿ�����ʧ�� , ����
		return FALSE;
	if(m_bLoadInitDemData==TRUE)	//�����ʼ���κ�Ӱ���ӿ��ѵ���ɹ� , ����
		return TRUE;

	if(theApp.m_BlockCols<=0 || theApp.m_BlockRows<=0) //������ο����������������<=0 , ����
		return FALSE;
	else  //���¶����ά����m_DemLod_My�Ĵ�С , ��Ϊ������ڴ�
		m_AllocUnAlloc2D3D.Alloc2D_int(m_DemLod_My , theApp.m_BlockCols*theApp.m_BlockRows+1 , 3);
	
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	
	//������ͶӰģʽ�µ��ε�x , y���������x , y����ı���
	m_ortho_CordinateOriginX=0.5;
	m_ortho_CordinateXYScale=(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);
	m_ortho_CordinateOriginY=m_ortho_CordinateOriginX*m_ortho_CordinateXYScale;
	
	double m_Sphere_x , m_Sphere_y;
	m_Sphere_x=(theApp.m_DemRightUp_x+theApp.m_DemLeftDown_x)/2.0 ; // ��Χ������x����
	m_Sphere_y=(theApp.m_DemRightUp_y+theApp.m_DemLeftDown_y)/2.0 ; // ��Χ������y����
	
	
	CString strsql;
	int mRowId , mColID;

	//�����ݿ��dem_block
	strsql="select *  from  dem_block order by �к� , �к�";
	if(m_Recordset->State)	//���m_Recordset�Ѵ�
		m_Recordset->Close() ; // �ر�
	try
	{
		m_Recordset->Open(_bstr_t(strsql) , (IDispatch*)(theApp.m_pConnection) , adOpenDynamic , adLockOptimistic , adCmdText);    
	}
	catch(_com_error& e)	//������		
	{
		CString errormessage;
		errormessage.Format("�����ݿ��ʧ��!\r\n������Ϣ:%s" , e.ErrorMessage());
		AfxMessageBox(errormessage , MB_ICONSTOP , 0);
		m_Recordset->Close() ; // �رռ�¼��
		return FALSE ; // ����
	} 
	
	long mcount;
    m_LodDemblockNumber=0 ; // ���ص��ο�����
	
	while(!m_Recordset->adoEOF)//���û�е����ݿ�β
	{
		
		Thevalue = m_Recordset->GetCollect("��������X"); 
		double m_demblock_centerx=(double)Thevalue ;	//�õ�DEM�ӿ�����x����
		
		Thevalue = m_Recordset->GetCollect("��������Y"); 
		double m_demblock_centery=(double)Thevalue;	//�õ�DEM�ӿ�����y����
		
		//����DEM�ӿ��������Χ�����ľ���
		double distence=sqrt((m_Sphere_x-m_demblock_centerx)*(m_Sphere_x-m_demblock_centerx)+
			(m_Sphere_y-m_demblock_centery)*(m_Sphere_y-m_demblock_centery));

		if(distence<m_Radius)//���DEM�ӿ��������Χ�����ľ���<���õİ�Χ��뾶 , ����ظõ����ӿ�
		{
			Thevalue = m_Recordset->GetCollect("�к�"); 
			mRowId=(long)Thevalue;
			
			Thevalue = m_Recordset->GetCollect("�к�"); 
			mColID=(long)Thevalue;
			//�洢�����صĵ��ο����Ĵ��x , y����
			m_DemBlockCenterCoord[m_LodDemblockNumber][0]=m_demblock_centerx-theApp.m_DemLeftDown_x;
			m_DemBlockCenterCoord[m_LodDemblockNumber][1]=-(m_demblock_centery-theApp.m_DemLeftDown_y);
			
			m_lodDemBlock[m_LodDemblockNumber][0]=mRowId ; // ����ĵ��ο���к�
			m_lodDemBlock[m_LodDemblockNumber][1]=mColID ; // ����ĵ��ο���к�
			m_lodDemBlock[m_LodDemblockNumber][2]=m_LodDemblockNumber ; // ����ĵ��ο�����
			
			mcount=(mRowId-1)*theApp.m_BlockCols+mColID ; // �������ĵ��ο�������DEM���ݿ��е�����
			m_DemLodIndex[m_LodDemblockNumber]=mcount ; // ��¼����ĵ�m_LodDemblockNumber�����ӿ������ 
			m_DemLod_My[mcount][0]=mRowId;	//����ĵ��ο���к�
			m_DemLod_My[mcount][1]=mColID;	//����ĵ��ο���к�
			m_DemLod_My[mcount][2]=m_LodDemblockNumber;	//����ĵ��ο�����
			m_pbm_DemLod[mcount]=true;
			if(m_LodDemblockNumber==0)//����ǵ�һ�ε���
			{
				m_loddem_StartRow=mRowId ; // �洢����ĵ��ο����ʼ�к�
				m_loddem_StartCol=mColID ; // �洢����ĵ��ο����ʼ�к�
			}
			m_LodDemblockNumber++; //������ο�����+1
		}

		if(mRowId>(theApp.m_BlockRows/2.0+m_Radius/theApp.m_Dem_BlockWidth) && mColID>(theApp.m_BlockCols/2.0+m_Radius/theApp.m_Dem_BlockWidth) && distence>m_Radius)
			break;
			m_Recordset->MoveNext() ; // 
	}
	m_Recordset->Close() ; // �ر����ݿ��

	m_loddem_EndRow=mRowId ; // �洢����ĵ��ο�Ľ����к�
	m_loddem_EndCol=mColID ; // �洢����ĵ��ο�Ľ����к�

    if(m_LodDemblockNumber<=0) //������ص��ο�����<=0 , ��ʾ����ʧ�� , ����
		return FALSE ; // ����
	

    m_tempDemLodIndex=new int[m_LodDemblockNumber];
	//���¶���bsign�����С(��ֵΪ1,��ʾ����ĵ����ӿ�������,=0,��ʾδ�������,���޳�����)
	m_bsign=new int[m_LodDemblockNumber];
	
	CString strtempfile="c:\\tempdem.txt" ; // ��ʱASCII�ļ� , ���ڴ洢�����ݿ��ж�ȡ��DEM�ӿ�����
	ExporttotalDemToFIle(strtempfile);//�����ݿ��ж�ȡ���и߳����ݵ�������,��Ϊ�������ڲ�߳�ʱ�õ�	
	ReadHdata(strtempfile);//��ȡDEM���и��ֵ㵽ȫ������theApp.m_DemHeight[]��

	float iPer=100.0/m_LodDemblockNumber;
	for( int i=0;i<m_LodDemblockNumber;i++)
	{
		//����m_lodDemBlock[i][0]�к͵�m_lodDemBlock[i][1]�еĴ������(BLOB)
		//DEM���ݴ����ݿ��ж�ȡ��д����ʱASCII�ļ���
		ExportBlobDemToFIle(strtempfile , m_lodDemBlock[i][0] , m_lodDemBlock[i][1]);
		ReadDataFromFiles(strtempfile , i) ; // ����ʱ��ASCII�ļ���ȡDEM���ݵ㵽�߳�
	 	getDemBlockTexture(m_lodDemBlock[i][0] , m_lodDemBlock[i][1] , i) ; // ��ȡ�����ض�ӦDEM�����ӿ��Ӱ������
		strsql.Format("���ڼ��ص�����Ӱ���������� , ���Ժ�... , �����%.2f%s" , (i+1)*iPer , "%");
		pMainFrame->Set_BarText(4 , strsql , 0); 
	}
	pMainFrame->Set_BarText(4 , "���ص�����Ӱ�������������!" , 0); 
	pMainFrame->Set_BarText(5 , " " , 60) ; // ������ɣ���ս�����Ϣ�������ؽ������ؼ�
	m_bLoadInitDemData=TRUE ; // ���ݼ��سɹ�

	double	mCx=(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x)/2.0 ; // ��ʼ����ӵ�X����(λ�ڵ��ε�����)
	double	mCz=-800 ; // ��ʼ����ӵ�Z����

	if(m_bCamraInit==FALSE)//������û�г�ʼ��
	{
		m_bCamraInit=TRUE ; // ��ʶ�����ʼ��
		float mDis=100 ; // �ӵ���۲���ʼ����

		//��ʼ����� , ����¼�������
		PositionCamera(
			mCx , 
			m_viewHeight+m_maxHeight*m_heighScale*1.0 , 
			mCz , 
			mCx , 
			m_viewHeight+m_maxHeight*m_heighScale*1.0-mDis*tan(m_viewdegree*PAI_D180) , 
			mCz-mDis , 
			0 , 1 , 0);
		
		//�����ʼ�ӵ�����
		m_originPosition=CVector3(mCx ,  m_viewHeight+m_maxHeight*m_heighScale*1.0 ,  mCz);
		//�����ʼ�۲������
		m_originView=CVector3(mCx , m_viewHeight+m_maxHeight*m_heighScale*1.0-mDis*tan(m_viewdegree*PAI_D180) , mCz-mDis);
			
	}
	
	return TRUE;
}

//��ȡDEM���и��ֵ㵽ȫ������theApp.m_DemHeight[]��
void CT3DSystemView::ReadHdata(CString strfilename)
{
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	long i,j;
	CString tt;
	float hh;	
	FILE *fp=fopen(strfilename,"r");//��DEM�ļ�

	//��ȡDEM�ļ�ͷ��Ϣ
	fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s",tt);
    fscanf(fp,"%s\n",tt);

	//���¶���ȫ������theApp.m_DemHeight[]�Ĵ�С,�������ڴ�
	theApp.m_DemHeight= new float[theApp.m_Dem_Rows*theApp.m_Dem_cols];
	float mPer=100.0/(theApp.m_Dem_Rows*theApp.m_Dem_cols);
	
	for (i=0;i<theApp.m_Dem_Rows;i++)
	{
		for (j=0;j<theApp.m_Dem_cols;j++)
		{
			fscanf(fp,"%f ",&hh);  //��ȡ�߳�
			theApp.m_DemHeight[i*theApp.m_Dem_cols+j]=hh;
		}
		fscanf(fp,"\n");  
	}
	
	fclose(fp); //�ر��ļ�
	DeleteFile(strfilename); //ɾ����ʱ�ļ�
}

//�����ݿ��ж�ȡ���и߳����ݵ�������,��Ϊ�������ڲ�߳�ʱ�õ�
void CT3DSystemView::ExporttotalDemToFIle(CString strFilename)
{
	CString tt;
	int idcol=1;	
	tt.Format("SELECT DEM���� FROM DEM_INFO WHERE ���= :%d FOR UPDATE",1);
	myOci.ReadBOLBDataFromDB(strFilename,tt,1);//�����ݿ��ж�ȡDEM����
}

//��ʼ����� , ����¼�������
void CT3DSystemView::PositionCamera(double positionX ,  double positionY ,  double positionZ ,  double viewX ,  double viewY ,  double viewZ ,  double upVectorX ,  double upVectorY ,  double upVectorZ)
{
	CVector3 vPosition	= CVector3(positionX ,  positionY ,  positionZ);
	CVector3 vView		= CVector3(viewX ,  viewY ,  viewZ);
	CVector3 vUpVector	= CVector3(upVectorX ,  upVectorY ,  upVectorZ);
	
	
	m_vPosition = vPosition;	//�ӵ�����				
	m_vView     = vView;		//�۲������		
	m_vUpVector = vUpVector;	//����ʸ������			
	m_oldvPosition=m_vPosition; //���浱ǰ�ӵ�����
}

//��DEM���ݱ��ж�ȡ��BLOB�����Ƶ�DEM���ݣ���д����ʱASCII��ʽ���ļ��У�ʵ��DEM���ݶ�ȡ
void CT3DSystemView::ExportBlobDemToFIle(CString strFilename ,  int RowIndex ,  int ColIndex)
{
	CString tt;
	int idcol=(RowIndex-1)*theApp.m_BlockCols+ColIndex;	
	tt.Format("SELECT DEM���� FROM dem_block WHERE �к�=%d AND �к�=%d AND ���= :%d FOR UPDATE" , RowIndex , ColIndex , idcol);
	myOci.ReadBOLBDataFromDB(strFilename , tt , idcol) ; // �����ݿ��ж�ȡBLOB����
}

//��ASCII��ʽ���ļ��ж�ȡDEM�̵߳����� , ��д��߳�������
void CT3DSystemView::ReadDataFromFiles(CString strfiles ,  int Index)
{
	float hh; 
	int i , j;
    int mCount=theApp.m_Dem_BlockSize ; // �����ӿ��С(��ֿ��СΪ33��33 , ������ӿ��С=33 , ��������)
    FILE *fp=fopen(strfiles , "r") ; // ���ļ�
	//ѭ����ȡDEM����
	for( i=0;i<mCount;i++)
	{
		for( j=0;j<mCount;j++)
		{
			fscanf(fp , "%f " , &hh);  
			
			m_pHeight_My[Index][i*mCount+j]=hh ; // ��DEM�߳�ֵд������
			if(m_maxHeight<hh) m_maxHeight=hh; //�������߳�ֵ
			if(m_minHeight>hh && hh!=-9999) m_minHeight=hh ; // ������С�߳�ֵ
			
		}
	}
	fclose(fp) ; // �ر��ļ�
	DeleteFile(strfiles) ; // ɾ����ʱASCII�ļ�
}

//��ȡ�����ض�ӦDEM�����ӿ��Ӱ������
void CT3DSystemView::getDemBlockTexture(int RowIndex ,  int ColIndex ,  int Index)
{
	CString strsql;
	int mID;
	_RecordsetPtr mRst;
	mRst.CreateInstance(_uuidof(Recordset));
		
	strsql.Format("select *  from TEXTURE WHERE �к�=%d AND �к�=%d  AND ������������=%d" , RowIndex , ColIndex , m_currebtPhramid);
	try
	{
		//�����ݿ��
		mRst->Open(_bstr_t(strsql) , (IDispatch*)(theApp.m_pConnection) , adOpenDynamic , adLockOptimistic , adCmdText);    
	}
	
	catch(_com_error& e)	//������
	{
		CString errormessage;
		errormessage.Format("�����ݿ��ʧ��!\r\n������Ϣ:%s" , e.ErrorMessage());
		MessageBox(errormessage , "��ȡӰ������" , MB_ICONSTOP);
		mRst->Close() ; // �ر����ݿ��
		return;
	} 
	
	if(mRst->adoEOF)	
	{
		mRst->Close() ; // �ر����ݿ��
		return;
	}
	
	//�õ���IndexӰ�����������º�����x , y����
	Thevalue = mRst->GetCollect("���½�����X"); 
	m_Texturexy[Index][0]=(double)Thevalue;
	
	Thevalue = mRst->GetCollect("���½�����Y"); 
	m_Texturexy[Index][1]=(double)Thevalue;
	
	Thevalue = mRst->GetCollect("���Ͻ�����X"); 
	m_Texturexy[Index][2]=(double)Thevalue ;
	
	Thevalue = mRst->GetCollect("���Ͻ�����Y"); 
	m_Texturexy[Index][3]=(double)Thevalue;
	
	Thevalue = mRst->GetCollect("���"); 
	mID=(long)Thevalue;
	
	mRst->Close() ; // �ر����ݿ��
	strsql.Format("C:\\%d_%d.bmp" , RowIndex , ColIndex) ; // ������ʱӰ�������ļ���
	if(ExportBlobTextureToFIle(strsql , RowIndex , ColIndex , mID)==TRUE)//��oracle���ݿ���ж�ȡBLOB���͵�Ӱ���������ݲ�д����ʱӰ�������ļ�
		m_demTextureID[Index]=m_texturesName.LoadGLTextures(_bstr_t(strsql)) ; // �洢�����Ӱ�������ӿ������ID , ���ڰ�����
	DeleteFile(strsql) ; // ɾ����ʱ�ļ�

}

//��ʼ�������OCI
void CT3DSystemView::Init_ArrayData()
{
	if(theApp.bLoadImage==FALSE) //���Ӱ���������ʧ�ܣ�����
        return ;
	
	if(theApp.bLoginSucceed==TRUE && m_BhasInitOCI==FALSE)//������ݼ��سɹ�����OCIδ��ʼ��
	{
		m_nMapSize=theApp.m_Dem_BlockSize-1 ; // 
		int blocks=m_nMapSize/2;
		//���������ڴ�
		m_AllocUnAlloc2D3D.Alloc2D_float(m_pHeight_My , blocks*blocks , (m_nMapSize+1)*(m_nMapSize+1)) ; // �洢��������ӿ�ĸ̵߳�
		m_AllocUnAlloc2D3D.Alloc2D_bool(m_pbQuadMat , blocks*blocks , (m_nMapSize+1)*(m_nMapSize+1)) ; // ��ʶ�����ӿ�Ľڵ��Ƿ���Ҫ�����ָ�
		m_AllocUnAlloc2D3D.Alloc1D_bool(m_pbm_DemLod , theApp.m_BlockCols *theApp.m_BlockRows) ; // ��ʶ���ο��Ƿ񱻵���
		m_AllocUnAlloc2D3D.Alloc2D_int(m_DemLod_My , theApp.m_BlockCols*theApp.m_BlockRows+1 , 3) ; // �洢��������ӿ���к� , �кŵ���Ϣ
		if(m_BhasInitOCI==FALSE)//���OCI��δ����ʼ��
		{
			myOci.Init_OCI(); //��ʼ��OCI
			m_BhasInitOCI=TRUE ; // ��ʶΪTRUE  
		}
	}
}

//��Ϣ��ʼ���ͼ��ص��� , Ӱ������
void CT3DSystemView::InitTerr()
{
	Init_ArrayData() ; // ��ʼ�������OCI
	if(LoadInitDemData()==FALSE) //������ݼ���ʧ�� , ����
		return ; // ����
}


//��ά���λ���(��ά������Ⱦ)
void CT3DSystemView::DrawTerrain()
{
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
	
	//glShadeModel��������������Ӱ��Ч������Ҫ��GL_SMOOTH��GL_FLAT����Ч����
	//����GL_SMOOTHΪĬ��ֵ����ʾƽ����ӰЧ����
	glShadeModel(GL_SMOOTH);

	glDisable(GL_TEXTURE_2D) ; // �ر�2D����ӳ�书��
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // ѡ��TEXTURE0Ϊ����Ŀ��
	glEnable(GL_TEXTURE_2D) ; // ����TEXTURE0��Ԫ

	glActiveTextureARB(GL_TEXTURE1_ARB) ; // ѡ��TEXTURE1Ϊ����Ŀ��
	glEnable(GL_TEXTURE_2D) ; // ����TEXTURE1��Ԫ , ����2D����ӳ��
	glTexEnvi(GL_TEXTURE_ENV ,  GL_TEXTURE_ENV_MODE ,  GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV ,  GL_RGB_SCALE_ARB ,  2);
	glMatrixMode(GL_TEXTURE); //�������Ϊģ���������
	glLoadIdentity() ; // ����ǰ�����û�Ϊ��λ����
	glDisable(GL_TEXTURE_2D) ; // �ر�������
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // ѡ��TEXTURE0Ϊ����Ŀ��
	SetDrawMode() ; // 
	
	
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();            
	gluPerspective(50.0 + m_ViewWideNarrow , (float)WinViewX/(float)WinViewY , m_near , m_far);		
	
	glMatrixMode(GL_MODELVIEW); //�������Ϊģ��ģ�;���
	glLoadIdentity(); //����ǰ�����û�Ϊ��λ����       

/*
	glClearDepth����������Ȼ������ģ����ĺ������OpenGL���ڻ��Ƶ�ͼ�����뵽��Ļ�еĳ̶ȣ�
	��ȵ������������ά�ռ��е�z�������ֵ��zȡ0ʱ��ʾ��ƽ���ϣ���Ϳ����������е�ͼ���ˣ�
	  ���Ը�ֵԽС��ԽԶ�봰��ƽ�����˵�������е�ͼ�������ǹ۲��ߵľ����Զ�ˣ�
*/
	glClearDepth(1.0f); //���ó�ʼ����Ȼ���ֵ
	glEnable(GL_DEPTH_TEST); // ������Ȳ���
	glDepthFunc(GL_LESS); //�ڵ���glEnable(GL_DEPTH_TEST); ������������Ժ󣬵���ȱ仯С�ڵ�ǰ���ֵʱ���������ֵ��

	
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		
	
	int nCount=0;


	if(this->m_stereo==TRUE) //�����˫Ŀ����ģʽ
	{
		SetCamra(1); //�������
	}
	else	//������
	{
		SetCamra(0) ; // �������
	}

	glViewport(0 ,  0 ,  WinViewX ,  WinViewY); //�����ӿڴ�С��λ��
	
	if(b_haveGetRegion==TRUE && m_ifZoomonRoad==TRUE)//�������·��������
	{
		DrawTerrainZoomonRoad() ; // ���Ƶ�������ά��·ģ��
	}
	else //�����Ƶ���
	{
		if(theApp.bLoginSucceed==TRUE && m_bLoadInitDemData==TRUE)
		{
			//����֡��
			float currentTime1 = timeGetTime() * 0.001f;
			nCountFrame++;
			CalculateViewPortTriCord(m_vPosition.x , m_vPosition.z , m_vView.x , m_vView.z);
			
			//Ϊ����m_pbQuadMat�����ڴ�(LOD�ڵ�ָ�ı�־)
			for(int j=0;j<m_LodDemblockNumber;j++)
			{
				memset(m_pbQuadMat[j] , 0 , m_nMapSize*m_nMapSize);
			}
		
			CalcFPS() ; // ����֡��

			//����������ʾ�б�
			glNewList(m_TerrainList , GL_COMPILE_AND_EXECUTE);
				m_RenderDemblockNumber=0 ; // ��Ⱦ�ĵ��ο�����
				View=m_vView-m_vPosition;
				for(int i=0;i<m_LodDemblockNumber;i++)
				{
					mCurrentTextID=i;
					m_CurrentDemArrayIndex=i;
					glBindTexture(GL_TEXTURE_2D ,  m_demTextureID[i]) ; // �󶨵�i�ر��ӿ������
					m_lodDemBlock[i][3]=0 ; // ��ʼֵΪδ������Ⱦ
					//�����ǰ���ο鲻���Ӿ�����
					if(bnTriangle(m_triPtA[0] , m_triPtA[1] , m_triPtB[0] , m_triPtB[1] , m_triPtC[0] , m_triPtC[1] , m_DemBlockCenterCoord[i][0] , m_DemBlockCenterCoord[i][1])==FALSE)
						continue;
					m_RenderDemblockNumber++ ; // ��Ⱦ�ĵ��ο�����+1
					m_lodDemBlock[i][3]=1 ; // ��ǰ���ο������Ⱦ
                    //�Ե�ǰ���ο����LOD�Ĳ����ָ�
					UpdateQuad(m_nMapSize/2 , m_nMapSize/2 , m_nMapSize/2 , 1 , m_lodDemBlock[i][0] , m_lodDemBlock[i][1]);
					//��ȾLOD�Ĳ����ָ��ĵ�ǰ���ο� , ���������ǰ�����Ƶ�������������
					nCount+= RenderQuad(m_nMapSize/2 , m_nMapSize/2 , m_nMapSize/2 , m_lodDemBlock[i][0] , m_lodDemBlock[i][1]);	
				}

				if(m_checkt==TRUE)//������д��󸺷�������
				{
					if(nCount>=m_maxTrinum) //������������������������������
						m_lodScreenError=m_lodScreenError*m_k1; //��Ļ��������
					if(nCount<=m_minTrinum) //�������������С����С����������
					m_lodScreenError=m_lodScreenError/m_k2 ; // ��Ļ���Ӽ�С
				}

			glEndList(); //������ʾ�б�
			
			CString	strText;
			strText.Format("���ڴ�/��Ⱦ������=%d/%d" , m_LodDemblockNumber , m_RenderDemblockNumber);
	  		pMainFrame->Set_BarText(0 , strText , 0); //��ʾ�ڴ��к���Ⱦ�ĵ��ο�����
			
			if(m_bShowbreviary==TRUE)//��ʾ������ͼ
			{
				glViewport(WinViewX*5/6 ,  WinViewY*5/6 , WinViewX/6 ,  WinViewY/6);
				glCallList(m_TerrainList) ; // ���õ�����ʾ�б� , ���µ��ӿڻ�����ά����
				glViewport(0 ,  0 ,  WinViewX ,  WinViewY) ; // ���������ӿڴ�С
				
			}

			
			float currentTime2 = timeGetTime() * 0.001f;
			mTimeElaps+=currentTime2-currentTime1;
			if(mTimeElaps>=1.0)//�������ʱ����>=1��
			{
				strText.Format("Ƶ�� %d FPS" , nCountFrame);
				pMainFrame->Set_BarText(1 , strText , 0); //��״̬��ָʾ������ʾ����֡��
				mTimeElaps=nCountFrame=0;
				
			}
		

			strText.Format("������ %d " , nCount);
			pMainFrame->Set_BarText(2 , strText , 0); //��״̬��ָʾ������ʾ��ǰ֡�����Ƶĵ�������������
		}
	}


	glActiveTextureARB(GL_TEXTURE1_ARB) ; // ѡ��TEXTURE1Ϊ����Ŀ��
	glDisable(GL_TEXTURE_2D) ; // �ر�TEXTURE1������
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // ѡ��TEXTURE0Ϊ����Ŀ��		
	glDisable(GL_TEXTURE_2D) ; // �ر�TEXTURE0������
	glDisable(GL_DEPTH_TEST) ; // �ر���Ȼ��������Թ���
}

//����֡��
void CT3DSystemView::CalcFPS()
{
	static DWORD dwStart = 0;
	static nCount = 0;
	nCount++;
	DWORD dwNow = ::GetTickCount();//���شӳ��������������������ĺ�����
	
	if(dwNow-dwStart>=1000)//ÿ1�����һ��֡��
	{
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		CString strText;
		strText.Format("Ƶ�� %d FPS " , nCount , 0);
		pMainFrame->Set_BarText(1 , strText , 0); //��״̬����ָʾ������ʾ֡��ֵ
		dwStart = dwNow;
		nCount = 0;
	}
}

//�������
void CT3DSystemView::SetCamra(int mStyle)
{
	
		switch(mStyle)
		{
		case 0://��˫Ŀ����ģʽ
			gluLookAt(m_vPosition.x ,  m_vPosition.y ,  m_vPosition.z , 	
				m_vView.x , 	 m_vView.y ,      m_vView.z , 	
				m_vUpVector.x ,  m_vUpVector.y ,  m_vUpVector.z);
			break;
		case 1://˫Ŀ����ģʽ , �����
			gluLookAt(m_vPosition.x-m_camraDistence/2.0 ,  m_vPosition.y ,  m_vPosition.z , 	
				m_vView.x , 	 m_vView.y ,      m_vView.z , 	
				m_vUpVector.x ,  m_vUpVector.y ,  m_vUpVector.z);
			break;
		case 2://˫Ŀ����ģʽ , �����
			gluLookAt(m_vPosition.x+m_camraDistence/2.0 ,  m_vPosition.y ,  m_vPosition.z , 	
				m_vView.x , 	 m_vView.y ,      m_vView.z , 	
				m_vUpVector.x ,  m_vUpVector.y ,  m_vUpVector.z);
		}
		
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		CString strText;
		float dy=m_vPosition.y-m_vView.y;
		float dz=fabs(m_vPosition.z-m_vView.z);
		if(theApp.bLoginSucceed==TRUE) 
		{
			if(fabs(dz)<=0.000001)
				m_viewdegree=0;
			else
				m_viewdegree=HDANGLE*atan(dy/dz);
		}
		
		//��״̬��ָʾ������ʾ�����Ϣ
		strText.Format("�����ӽǡ�A=%.2f" , m_viewdegree);
		pMainFrame->Set_BarText(3 , strText , 0); 
		
		if(m_ifZoomonRoad==FALSE)//������·�������� , ���� , ��ʾ��ǰ���
		{
			strText.Format("�ӵ�����:x=%.3f , y=%.3f , z=%.3f" , m_vPosition.x  , m_vPosition.y , fabs(m_vPosition.z));
			pMainFrame->Set_BarText(4 , strText , 0); 
		}
		
		if(m_ifZoomonRoad==FALSE)//������·�������� , ���� , ��ʾ��ǰ���
		{
			strText.Format("�۲������:x=%.3f , y=%.3f , z=%.3f" , m_vView.x  , m_vView.y , fabs(m_vView.z));
			pMainFrame->Set_BarText(5 , strText , 0); 
		}
		
}

//��ʼ����ʾ�б�
void CT3DSystemView::InitList()
{
	m_TerrainList=glGenLists(20);
	m_SkyList=m_TerrainList+1 ; // ���������ʾ�б�
	m_QLanList=m_TerrainList+2; //����������ʾ�б�
	m_QDList=m_TerrainList+3;//�����Ŷ���ʾ�б�
	m_Rail3DwayList=m_TerrainList+4; //��·��άģ����ʾ�б�(͸��ͶӰģʽ)
	m_HazardList_Ortho=m_TerrainList+5;//��·��άģ����ʾ�б�(����ͶӰģʽ)
	m_clockList=m_TerrainList+6;//ʱ��ָ������ʾ�б�
	m_NavigateList=m_TerrainList+7;
	m_Rail3DwayList_Ortho=m_TerrainList+8;
	m_TerrainZoomroadList=m_TerrainList+9;
	m_TunnelDMList=m_TerrainList+10; //���������ʾ�б�


	makeSkykList() ; // ���ɻ��Ʊ��������ʾ�б�
	BuildQDModelList();//�����Ŷ���ʾ�б�
	makeQLList();//������������//��ʾ�б�
	makeClockList();//����ʱ��ָ������ʾ�б�
	BuildTunnelDMModelList();//�������������ʾ�б�
		
	
}

//����·��������ʱ���Ʊ���·ģ�ͼ��к����ά����
void CT3DSystemView::DrawTerrainZoomonRoad()
{

	double x,y,z;
	if(theApp.bLoginSucceed==TRUE && m_bLoadInitDemData==TRUE && m_BlockTriInfos.GetSize()>0)
	{
		m_bShowbreviary=FALSE;
		glViewport(0, 0, WinViewX, WinViewY);
		
		
		float dz=m_maxHeight-m_minHeight;
		glLineWidth(2);
		
		float currentTime1 = timeGetTime() * 0.001f;
		nCountFrame++;
		CalculateViewPortTriCord(m_vPosition.x,m_vPosition.z,m_vView.x,m_vView.z);
		CalcFPS();
		
		for( long i=0;i<m_BlockTriInfos.GetSize();i++)
		{
			
			BOOL bt=GetIfINView(m_BlockTriInfos.GetAt(i)->mDemBlockRow,m_BlockTriInfos.GetAt(i)->mDemBlockCol); 
			if(bt==FALSE)
				continue;
			
			for(long j=0;j<m_BlockTriInfos.GetAt(i)->TriPts.GetSize();j++)
			{
				
				int mtextureID=(m_BlockTriInfos.GetAt(i)->mDemBlockRow-1)*theApp.m_BlockCols+(m_BlockTriInfos.GetAt(i)->mDemBlockCol-1);
				
				glBindTexture(GL_TEXTURE_2D, m_demTextureID[mtextureID]); //������
				
				if(m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt1.x!=-9999)
				{
					
					{
						glBegin( GL_TRIANGLES);
						
						x=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt1.x;
						y=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt1.y;
						z=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt1.z;
						
						SetTextureCoordZoomRoad(x,y,m_BlockTriInfos.GetAt(i)->mDemBlockRow,m_BlockTriInfos.GetAt(i)->mDemBlockCol);
						glVertex3f(x,z,-y);
						
						x=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt2.x;
						y=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt2.y;
						z=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt2.z;
						SetTextureCoordZoomRoad(x,y,m_BlockTriInfos.GetAt(i)->mDemBlockRow,m_BlockTriInfos.GetAt(i)->mDemBlockCol);
						glVertex3f(x,z,-y);
						
						x=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt3.x;
						y=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt3.y;
						z=m_BlockTriInfos.GetAt(i)->TriPts.GetAt(j)->Pt3.z;
						SetTextureCoordZoomRoad(x,y,m_BlockTriInfos.GetAt(i)->mDemBlockRow,m_BlockTriInfos.GetAt(i)->mDemBlockCol);
						glVertex3f(x,z,-y);
						glEnd();
					}
				}
			}
		}
		
		
		float currentTime2 = timeGetTime() * 0.001f;
		mTimeElaps+=currentTime2-currentTime1;
		
		if(mTimeElaps>=1.0)
		{
			CString strText;
			strText.Format("Ƶ�� %d FPS",nCountFrame);
			
			mTimeElaps=nCountFrame=0;
			
		}
	}
}

//�жϵ��νڵ��Ƿ��ڼ������Ӿ�����
BOOL CT3DSystemView::bnTriangle(double cneterx ,  double cnetery ,  double x2 ,  double y2 ,  double x3 ,  double y3 ,  double x ,  double y)
{
	double m_dx , m_dz;
	float remianAngle;
	
	
	double d1 , d2;
	double mDis=(cneterx-x)*(cneterx-x)+(cnetery-y)*(cnetery-y);
	mDis=sqrt(mDis);
	if(mDis>=m_R)
		return FALSE;
	else if(mDis<=1000)
		return TRUE;
	
		
	m_dx=cneterx-x;
	m_dz=cnetery-y;
	
    if(m_dx<=0 && m_dz>=0) 
	{
		if(m_dx==0)	
			remianAngle=90;
		else
			remianAngle=atan(fabs(m_dz/m_dx))*HDANGLE;
		
	}
    else if(m_dx>=0 && m_dz>=0) 
	{
		if(m_dx==0)	
			remianAngle=90;
		else
			remianAngle=180-atan(fabs(m_dz/m_dx))*HDANGLE;
		
	}
    else if(m_dx>=0 && m_dz<=0) 
	{
		if(m_dx==0)	
			remianAngle=270;
		else
			remianAngle=180+atan(fabs(m_dz/m_dx))*HDANGLE;
		
	}
    else if(m_dx<=0 && m_dz<=0) 
	{
		if(m_dx==0)	
			remianAngle=270;
		else
			remianAngle=360-atan(fabs(m_dz/m_dx))*HDANGLE;
		
	}
	

	if(mDis<=m_R)
	{  
		if(remianAngle>=m_sectorStartAngle && remianAngle<=m_sectorEndAngle)
			return TRUE;
		else
		{
			d1=mCalF.GetPointToLineDistence(x , y , cneterx , cnetery , x2 , y2) ; // ����㵽ֱ�ߵľ���
			d2=mCalF.GetPointToLineDistence(x , y , cneterx , cnetery , x3 , y3) ; // ����㵽ֱ�ߵľ���
            if(d1<=m_r || d2<=m_r)
				return TRUE;
		}
	}
    else
	{
		if(remianAngle>=m_sectorStartAngle && remianAngle<=m_sectorEndAngle)
		{
			if(mDis<=m_R+m_r)
				return TRUE;
		}
		
	}
	
	return FALSE;
}

//����������Ӿ����ڵ�������������
void CT3DSystemView::CalculateViewPortTriCord(double View_x ,  double View_z ,  double look_x ,  double look_z)
{
	double m_derx=look_x-View_x;
	double m_derz=look_z-View_z;
	float angle_arefa;
	
	m_triPtA[0]=View_x;m_triPtA[1]=View_z;
	
    if(m_derx<=0 && m_derz>0) 
	{
		if(m_derx==0)	
			angle_arefa=270;
		else
			angle_arefa=180+atan(fabs(m_derz/m_derx))*HDANGLE;
		
	}
    else if(m_derx>=0 && m_derz>0) 
	{
		if(m_derx==0)	
			angle_arefa=0;
		else
			angle_arefa=360-atan(fabs(m_derz/m_derx))*HDANGLE;
		
	}
    else if(m_derx>=0 && m_derz<0) 
	{
		if(m_derx==0)	
			angle_arefa=0;
		else
			angle_arefa=atan(fabs(m_derz/m_derx))*HDANGLE;
		
	}
    else if(m_derx<=0 && m_derz<0) 
	{
		if(m_derx==0)	
			angle_arefa=90;
		else
			angle_arefa=180-atan(fabs(m_derz/m_derx))*HDANGLE;
		
	}
	
	m_sectorStartAngle=angle_arefa-m_FrustumAngle/2;
	m_triPtB[0]=m_R*cos(m_sectorStartAngle*PAI_D180)+m_triPtA[0];
	m_triPtB[1]=-m_R*sin(m_sectorStartAngle*PAI_D180)+m_triPtA[1];
	
	m_sectorEndAngle=angle_arefa+m_FrustumAngle/2;
	m_triPtC[0]=m_R*cos(m_sectorEndAngle*PAI_D180)+m_triPtA[0];
	m_triPtC[1]=-m_R*sin(m_sectorEndAngle*PAI_D180)+m_triPtA[1];
	
	
	m_Viewpolygon[0].x=m_triPtA[0]; 	m_Viewpolygon[0].y=-m_triPtA[1];
	m_Viewpolygon[1].x=m_triPtB[0]; 	m_Viewpolygon[1].y=-m_triPtB[1];
	m_Viewpolygon[2].x=m_triPtC[0]; 	m_Viewpolygon[2].y=-m_triPtC[1];
	
	////�洢�ӿ��������ε�����������е������С����
	m_Viewpolygon_Minx=m_Viewpolygon[0].x;
	m_Viewpolygon_Miny=m_Viewpolygon[0].y;
	m_Viewpolygon_Maxx=m_Viewpolygon[0].x;
	m_Viewpolygon_Maxy=m_Viewpolygon[0].y;
	
	if(m_Viewpolygon_Minx>m_Viewpolygon[1].x) m_Viewpolygon_Minx=m_Viewpolygon[1].x;
	if(m_Viewpolygon_Maxx<m_Viewpolygon[1].x) m_Viewpolygon_Maxx=m_Viewpolygon[1].x;
	if(m_Viewpolygon_Miny>m_Viewpolygon[1].y) m_Viewpolygon_Miny=m_Viewpolygon[1].y;
	if(m_Viewpolygon_Maxy<m_Viewpolygon[1].y) m_Viewpolygon_Maxy=m_Viewpolygon[1].y;
	
	if(m_Viewpolygon_Minx>m_Viewpolygon[2].x) m_Viewpolygon_Minx=m_Viewpolygon[2].x;
	if(m_Viewpolygon_Maxx<m_Viewpolygon[2].x) m_Viewpolygon_Maxx=m_Viewpolygon[2].x;
	if(m_Viewpolygon_Miny>m_Viewpolygon[2].y) m_Viewpolygon_Miny=m_Viewpolygon[2].y;
	if(m_Viewpolygon_Maxy<m_Viewpolygon[2].y) m_Viewpolygon_Maxy=m_Viewpolygon[2].y;
}

//�Ե��ο�����Ĳ���LOD�ָ�
void CT3DSystemView::UpdateQuad(int nXCenter ,  int nZCenter ,  int nSize ,  int nLevel ,  int mRowIndex ,  int mColIndex)
{
	double mx=(mColIndex-1)*theApp.m_Dem_BlockWidth;
	double mz=(mRowIndex-1)*theApp.m_Dem_BlockWidth;
	//������νڵ㲻���Ӿ����� , ����
	if(bnTriangle(m_triPtA[0] , m_triPtA[1] , m_triPtB[0] , m_triPtB[1] , m_triPtC[0] , m_triPtC[1] , nXCenter*theApp.m_Cell_xwidth+mx , -nZCenter*theApp.m_Cell_ywidth-mz)==FALSE)
		return ;
	
	
	if(m_ifZoomonRoad==FALSE) //�Ƿ�����·��������
	{
		CVector3 vPos=GetPos();
		
		CVector3 vDst(nXCenter*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter , nZCenter ,  mRowIndex ,  mColIndex) , -nZCenter*theApp.m_Cell_ywidth-(mRowIndex-1)*theApp.m_Dem_BlockWidth);
		float nDist=mCalF.maxValueXYZ(fabs(vPos.x-vDst.x) , fabs(vPos.y-vDst.y) , fabs(vPos.z-vDst.z));
		float es , em;
		
		em=GetNodeError(nXCenter ,  nZCenter ,  nSize , mRowIndex ,  mColIndex) ; // ����ڵ����
		es=m_es*(em/nDist);
		if(es<m_lodScreenError) //������С����Ļ���� , ������
			return;
	}
		
	if(nSize>1) //��ʾ���ο�ڵ㻹��Ҫ�����ָ�
	{	
		m_pbQuadMat[m_CurrentDemArrayIndex][nXCenter+nZCenter*m_nMapSize]=true;		
		UpdateQuad(nXCenter-nSize/2 , nZCenter-nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // �ָ������ӽڵ�
		UpdateQuad(nXCenter+nSize/2 , nZCenter-nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // �ָ������ӽڵ�
		UpdateQuad(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // �ָ������ӽڵ�
		UpdateQuad(nXCenter-nSize/2 , nZCenter+nSize/2 , nSize/2 , nLevel+1 , mRowIndex ,  mColIndex) ; // �ָ������ӽڵ�
	}
}

//���ݽڵ��X , Y�͵����ӿ���кź��кŴӸ߳������еõ���Ӧ�Ľڵ�߳�ֵ
float CT3DSystemView::GetHeightValue(int X ,  int Y ,  int mRowIndex ,  int mColIndex)
{
	return m_pHeight_My[m_CurrentDemArrayIndex][X+Y*(m_nMapSize+1)]*m_heighScale;
	
}

//�õ�����۲����ά����
CVector3 CT3DSystemView::GetPos()
{
	return m_vPosition;
}

//�õ�����ӵ���ά����
CVector3 CT3DSystemView::GetView()
{
	return m_vView;
}

//�õ��������ʸ����ά����
CVector3 CT3DSystemView::UpVector()
{
	return m_vUpVector;
}

//�õ�����²�����CVector3���ͱ���
CVector3 CT3DSystemView::Strafe()
{
	return m_vStrafe;
}


//�ڵ�������
float CT3DSystemView::GetNodeError(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	float nMax = GetHeightValue(nXCenter , nZCenter ,  mRowIndex ,  mColIndex);
	float nMin = nMax;
	float nH1 = GetHeightValue(nXCenter-nSize , nZCenter-nSize , mRowIndex ,  mColIndex);
	float nH2 = GetHeightValue(nXCenter+nSize , nZCenter-nSize , mRowIndex ,  mColIndex);
	float nH3 = GetHeightValue(nXCenter+nSize , nZCenter+nSize , mRowIndex ,  mColIndex);
	float nH4 = GetHeightValue(nXCenter-nSize , nZCenter+nSize , mRowIndex ,  mColIndex);
	if(nMax<nH1)nMax = nH1;
	if(nMax<nH2)nMax = nH2;
	if(nMax<nH3)nMax = nH3;
	if(nMax<nH4)nMax = nH4;
	if(nMin>nH1)nMin = nH1;
	if(nMin>nH2)nMin = nH2;
	if(nMin>nH3)nMin = nH3;
	if(nMin>nH4)nMin = nH4;
	return nMax-nMin;
}

//���ݵ��ο���кź��к��жϸ�����ο��Ƿ��ӿ���������
BOOL CT3DSystemView::GetIfINView(int mBlockRow ,  int mBlockCol)
{
	Point *polygonPs;	
	polygonPs=new Point[4];

	polygonPs[0].x=(mBlockCol-1)*theApp.m_Dem_BlockWidth;
	polygonPs[0].y=(mBlockRow-1)*theApp.m_Dem_BlockWidth;
	
	polygonPs[1].x=polygonPs[0].x+theApp.m_Dem_BlockWidth;
	polygonPs[1].y=polygonPs[0].y;

	polygonPs[2].x=polygonPs[0].x;
	polygonPs[2].y=polygonPs[0].y+theApp.m_Dem_BlockWidth;

	polygonPs[3].x=polygonPs[1].x;
	polygonPs[3].y=polygonPs[2].y;



	BOOL Bt=FALSE;
	bool Fin=false;
	
   //�ӿ�������(���εļ�)������ӿ�(����)�жϹ�������:
/*
	������������κ�һ�ֶ���Ϊ�õ����ӿ���Ҫ����
	(1)�ӿ���������ȫλ�ڻ򲿷��ӿ������ζ���λ�ڵ����ӿ�(����)��
	(2)�����ӿ�(����)��ȫλ���ӿ���������
	(3)�����ӿ�(����)���ӿ����������ཻ
*/
	////�洢�ӿ��������ε�����������е������С����
	//����ٵ����ӿ����Сx , y���궼�����ӿ������ε����x , y����
	//    �ڵ����ӿ�����x , y���궼С���ӿ������ε���Сx , y����
	//��õ����ӿ�һ����λ���ӿ��������� , �����ٽ����ж�
	if(polygonPs[0].x>=m_Viewpolygon_Maxx || polygonPs[0].y>=m_Viewpolygon_Maxy)
		return FALSE;
	if(polygonPs[3].x<=m_Viewpolygon_Minx || polygonPs[3].y<=m_Viewpolygon_Miny)
		return FALSE;
	

		
	//(1)ֻҪ�ӿ���������һ������λ�ڵ����ӿ�(����)�ھ���
	if(m_triPtA[0]>polygonPs[0].x && m_triPtA[0]<polygonPs[3].x && m_triPtA[1]<-polygonPs[0].y && m_triPtA[1]>-polygonPs[3].y) //���ھ�����
		Bt=TRUE;
	if(Bt==FALSE && m_triPtB[0]>polygonPs[0].x && m_triPtB[0]<polygonPs[3].x && m_triPtB[1]<-polygonPs[0].y && m_triPtB[1]>-polygonPs[3].y) //���ھ�����
		Bt=TRUE;
	if(Bt==FALSE && m_triPtC[0]>polygonPs[0].x && m_triPtC[0]<polygonPs[3].x && m_triPtC[1]<-polygonPs[0].y && m_triPtC[1]>-polygonPs[3].y) //���ھ�����
		Bt=TRUE;
	if(Bt==FALSE)
	{
		Bt=mCalF.InPolygon(m_Viewpolygon , 3 , polygonPs[0]);
		if(Bt==FALSE)
			Bt=mCalF.InPolygon(m_Viewpolygon , 3 , polygonPs[1]);
		if(Bt==FALSE)
			Bt=mCalF.InPolygon(m_Viewpolygon , 3 , polygonPs[2]);
		if(Bt==FALSE)
			Bt=mCalF.InPolygon(m_Viewpolygon , 3 , polygonPs[3]);
	}
	
	//���п��ܴ�Խ�����ӿ��
	//(1)�����ε�������01 , 12 , 02
	//(2)���ε�4���� 01 , 23 , 02 , 13
		
	//01��
	if(Bt==FALSE)
	{
		//�ж������߶��Ƿ��ཻ(�н���)
		Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[0] , polygonPs[1]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[0] , polygonPs[2]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[2] , polygonPs[3]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[1] , polygonPs[1] , polygonPs[3]);
	}

	//12��
	if(Bt==FALSE)
	{
		//�ж������߶��Ƿ��ཻ(�н���)
		Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[0] , polygonPs[1]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[0] , polygonPs[2]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[2] , polygonPs[3]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[1] ,  m_Viewpolygon[2] , polygonPs[1] , polygonPs[3]);
	}

	//02��
	if(Bt==FALSE)
	{
		//�ж������߶��Ƿ��ཻ(�н���)
		Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[2] , polygonPs[0] , polygonPs[1]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[2] , polygonPs[0] , polygonPs[2]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[2] , polygonPs[2] , polygonPs[3]);
		if(Bt==FALSE)
			Bt=mCalF.IsLineSegmentCross(m_Viewpolygon[0] ,  m_Viewpolygon[2] , polygonPs[1] , polygonPs[3]);
	}
	return Bt;
}

//������·����ʱ���ο���������
void CT3DSystemView::SetTextureCoordZoomRoad(double x ,  double z ,  int mRowIndex ,  int mColIndex)
{
	//��Ӧ���ο����Сx , y����
	double mminx=(mColIndex-1)*theApp.m_Dem_BlockWidth;
	double mminy=(mRowIndex-1)*theApp.m_Dem_BlockWidth;
	
	float u=(x-mminx)/theApp.m_Dem_BlockWidth;
	float v=(z-mminy)/theApp.m_Dem_BlockWidth;
	
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB ,  u ,  v);
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB ,  u ,  v);
}

//��Ⱦ���νڵ�
int CT3DSystemView::RenderQuad(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	float hjh;
	int kk;
	CVector3 pos , VPos;

	
	int nH0 , nH1 , nH2 , nH3 , nH4;
	int nCount = 0;
	if(nSize>=1.0f)//���ο�ڵ�ߴ�>=1.0����ʾ�ýڵ㻹���ӽڵ�
	{
		//�ڵ����ĵ��4���ǵ�ĸ߳�
		nH0 = GetHeightValue(nXCenter , nZCenter ,  mRowIndex ,  mColIndex);
		nH1 = GetHeightValue(nXCenter-nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex);
		nH2 = GetHeightValue(nXCenter+nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex);
		nH3 = GetHeightValue(nXCenter+nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex);
		nH4 = GetHeightValue(nXCenter-nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex);
	}

	int mnum=0;

	double mx=(mColIndex-1)*theApp.m_Dem_BlockWidth;
	double mz=(mRowIndex-1)*theApp.m_Dem_BlockWidth;
	

	//������νڵ㲻���Ӿ����� , ����
	if(bnTriangle(m_triPtA[0] , m_triPtA[1] , m_triPtB[0] , m_triPtB[1] , m_triPtC[0] , m_triPtC[1] , nXCenter*theApp.m_Cell_xwidth+mx , -nZCenter*theApp.m_Cell_ywidth-mz)==FALSE)
		return 0;

	float dz=m_maxHeight-m_minHeight;

	double x , z;
	double xcenter , zcenter;


	/*
	�����ڵ����ʾ��ͼ
	nH4
	  |----------------|nH3
	  |                |
	  |                |
	  |                |
	  |       nH0      |
	  |    �ڵ�����    |
	  |                |
	  |                |
	  |----------------|
      nH1              nH2 
	
	  ���ж����Խڵ�����(nH0)��ʼ���л��� , 
	  
	˳��ΪnH0--nH1--nH2--nH3--nH4--nH1
	������4������(nH1--nH2 , nH2--nH3 , nH3--nH4 , nH4--nH1)���ܻᲹ������Ӧ��
	�����������ٽڵ�ֱ��ʲ�һ����ɵĿն� , Ҳ����˵һ�����νڵ����ٻ���4��������

    ��ʹ������� , ������Ȼ���Խڵ�����nH0��ʼ , ����һϵ����
	����(��GL_TRIANGLE_FAN��ʽ����) , ����߻����ٶ�


	*/
	
	if(m_pbQuadMat[m_CurrentDemArrayIndex][nXCenter+nZCenter*m_nMapSize]==true /*&& nSize>1.0/nLodScale*/)			
			
	{
		nCount += RenderQuad(nXCenter-nSize/2 , nZCenter-nSize/2 , nSize/2 ,  mRowIndex ,  mColIndex);
		nCount += RenderQuad(nXCenter+nSize/2 , nZCenter-nSize/2 , nSize/2 ,  mRowIndex ,  mColIndex);
		nCount += RenderQuad(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 ,  mRowIndex ,  mColIndex);
		nCount += RenderQuad(nXCenter-nSize/2 , nZCenter+nSize/2 , nSize/2 ,  mRowIndex ,  mColIndex);
	}
	else
	{
			//�����λ��Ƶ��ο�ڵ�
			glBegin( GL_TRIANGLE_FAN );
		
				x=nXCenter*theApp.m_Cell_xwidth+mx;z=-nZCenter*theApp.m_Cell_ywidth-mz;
				VPos.x=x-m_vPosition.x;VPos.y=nH0-m_vPosition.y;VPos.z=z-m_vPosition.z;
				xcenter=x;
				zcenter=-z;
				if(DotProduct(View , VPos)>0) //������ӵ㷶Χ��
				{	
					if(nH0!=theApp.m_DEM_IvalidValue)	//����߳���Ч
					{
						//������ɫ
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH0-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH0-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH0-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x , nH0 ,  z);  //���÷���
						SetTextureCoord(nXCenter , nZCenter ,  mRowIndex ,  mColIndex);  //������������
						glVertex3i(x ,  nH0 ,  z) ; // д�����ĵ�����
					}
					
				}
				x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z= -(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
				VPos.x=x-m_vPosition.x;VPos.y=nH1-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)
				{	

					if(nH1!=theApp.m_DEM_IvalidValue )	//����߳���Ч
					{
						//������ɫ
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH1-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH1-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH1-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x , nH1  ,  x);  //���÷���
						SetTextureCoord(nXCenter-nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex); //������������
						glVertex3i(x , nH1  ,  z) ; // ���½ǵ�
						CracksPatchTop(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // �ڵ��ѷ��޲�
						nCount++;
					}
				}
				if(nZCenter-nSize==0) 
				{
					for(kk=1;kk<=2*nSize-1;kk++)
					{
						hjh = GetHeightValue(nXCenter-nSize+kk , nZCenter-nSize ,  mRowIndex ,  mColIndex);
						x=(nXCenter-nSize+kk)*theApp.m_Cell_xwidth+mx;z=-(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
						VPos.x=x-m_vPosition.x;VPos.y=hjh-m_vPosition.y;VPos.z=z-m_vPosition.z;
						if(DotProduct(View , VPos)>0)//����ڵ������Ӿ�����
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//����߳���Ч	
							{
								//������ɫ
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z);  //���÷���
								SetTextureCoord(nXCenter-nSize+kk , nZCenter-nSize ,  mRowIndex ,  mColIndex); //������������
								glVertex3i(x ,  hjh ,  z);
								
								mnum++;
							}
						}
						
					}
				
				}

					
				x=(nXCenter+nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
				
				VPos.x=x-m_vPosition.x;VPos.y=nH2-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//����ڵ������Ӿ�����
				{	
					if(nH2!=theApp.m_DEM_IvalidValue)	//����߳���Ч
					{
						//������ɫ
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH2-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH2-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH2-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH2 ,  z) ; // ���÷���
						SetTextureCoord(nXCenter+nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex); //������������
						glVertex3i(x ,  nH2 ,  z) ; // ���Ͻǵ�
						CracksPatchRight(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // �ڵ��ѷ��޲�
						nCount++;
					}
				}


				if(nXCenter+nSize>=m_nMapSize)
				{
					for(kk=1;kk<=2*nSize-1;kk++)
					{
						hjh = GetHeightValue(nXCenter+nSize , kk+(nZCenter-nSize) ,  mRowIndex ,  mColIndex);
						x=(nXCenter+nSize)*theApp.m_Cell_xwidth+mx;z=-(kk+(nZCenter-nSize))*theApp.m_Cell_ywidth-mz;
						
						VPos.x=x-m_vPosition.x;VPos.y=hjh-m_vPosition.y;VPos.z=z-m_vPosition.z;
						if(DotProduct(View , VPos)>0)//����ڵ������Ӿ�����
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//����߳���Ч	
							{
								//������ɫ
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z) ; // ���÷���
								SetTextureCoord(nXCenter+nSize , kk+(nZCenter-nSize) ,  mRowIndex ,  mColIndex); //������������
								glVertex3i(x ,  hjh ,  z);
								mnum++;
							}
						}
					}
				
				}


				x=(nXCenter+nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter+nSize)*theApp.m_Cell_ywidth-mz;
				
				VPos.x=x-m_vPosition.x;VPos.y=nH3-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//����ڵ������Ӿ�����
				{	
					if(nH3!=theApp.m_DEM_IvalidValue)		//����߳���Ч
					{
						//������ɫ
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH3-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH3-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH3-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH3 ,  z) ; // ���÷���
						SetTextureCoord(nXCenter+nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex); //������������
						glVertex3i(x ,  nH3 ,  z) ; // ���Ͻǵ�
						CracksPatchBottom(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // �ڵ��ѷ��޲�
						nCount++;
					}
				}

				if(nZCenter+nSize>=m_nMapSize) 
				{
					for(kk=1;kk<=2*nSize-1;kk++)
					{
						hjh = GetHeightValue(nXCenter+nSize-kk , nZCenter+nSize ,  mRowIndex ,  mColIndex);
						x=(nXCenter+nSize-kk)*theApp.m_Cell_xwidth+mx;z=-(nZCenter+nSize)*theApp.m_Cell_ywidth-mz;
						
						VPos.x=x-m_vPosition.x;VPos.y=hjh-m_vPosition.y;VPos.z=z-m_vPosition.z;
						if(DotProduct(View , VPos)>0)//����ڵ������Ӿ�����
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//����߳���Ч	
							{
								//������ɫ
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z) ; // ���÷���
								SetTextureCoord(nXCenter+nSize-kk , nZCenter+nSize ,  mRowIndex ,  mColIndex); //������������
								glVertex3i(x ,  hjh ,  z);
								mnum++;
							}
						}
						
					}
				}

				
				x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter+nSize)*theApp.m_Cell_ywidth-mz;
				
				VPos.x=x-m_vPosition.x;VPos.y=nH4-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//����ڵ������Ӿ�����
				{	
					if(nH4!=theApp.m_DEM_IvalidValue)	//����߳���Ч	
					{	
						//������ɫ
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH4-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH4-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH4-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH4 ,  z) ; // ���÷���
						SetTextureCoord(nXCenter-nSize , nZCenter+nSize ,  mRowIndex ,  mColIndex) ; // ������������
						glVertex3i(x ,  nH4 ,  z) ; // ���Ͻǵ�
						CracksPatchLeft(nXCenter , nZCenter , nSize , mRowIndex , mColIndex) ; // �ڵ��ѷ��޲�
						nCount++;
					}
				}
			
				if(nXCenter-nSize<=0) 
				{
					for(kk=2*nSize-1;kk>0;kk--)
					{
						hjh = GetHeightValue(nXCenter-nSize , kk+(nZCenter-nSize) ,  mRowIndex ,  mColIndex);
						x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z=-(kk+(nZCenter-nSize))*theApp.m_Cell_ywidth-mz;
						
						VPos.x=x-m_vPosition.x;VPos.y=hjh-m_vPosition.y;VPos.z=z-m_vPosition.z;
						if(DotProduct(View , VPos)>0)//����ڵ������Ӿ�����
						{	
							if(hjh!=theApp.m_DEM_IvalidValue)	//����߳���Ч	
							{							
								//������ɫ
								glColor3f(
									(maxZ_color_R-minZ_color_R)*(hjh-m_minHeight)/dz+minZ_color_R , 
									(maxZ_color_G-minZ_color_G)*(hjh-m_minHeight)/dz+minZ_color_G , 
									(maxZ_color_B-minZ_color_B)*(hjh-m_minHeight)/dz+minZ_color_B);
								glNormal3f(x ,  hjh ,  z) ; // ���÷���
								SetTextureCoord(nXCenter-nSize , kk+(nZCenter-nSize) ,  mRowIndex ,  mColIndex); //������������
								glVertex3i(mx ,  hjh ,  z);
								mnum++;
							}
						}
					}
					
				}
				

				x=(nXCenter-nSize)*theApp.m_Cell_xwidth+mx;z=-(nZCenter-nSize)*theApp.m_Cell_ywidth-mz;
				VPos.x=x-m_vPosition.x;VPos.y=nH1-m_vPosition.y;VPos.z=z-m_vPosition.z;
				if(DotProduct(View , VPos)>0)//����ڵ������Ӿ�����
				{	
						
					if(nH1!=theApp.m_DEM_IvalidValue)	//����߳���Ч	
					{
						//������ɫ
						glColor3f(
							(maxZ_color_R-minZ_color_R)*(nH1-m_minHeight)/dz+minZ_color_R , 
							(maxZ_color_G-minZ_color_G)*(nH1-m_minHeight)/dz+minZ_color_G , 
							(maxZ_color_B-minZ_color_B)*(nH1-m_minHeight)/dz+minZ_color_B);
						glNormal3f(x ,  nH1 ,  z) ; // ���÷���
						SetTextureCoord(nXCenter-nSize , nZCenter-nSize ,  mRowIndex ,  mColIndex); //������������
						glVertex3i(x ,  nH1 , z) ; // ��д���½ǵ�
						nCount++;
					}
				}

				
			glEnd();
			
			nCount=nCount+mnum ; // ����������
			mnum=0;
		}
	return nCount ; // ��������������
}

//������������
void CT3DSystemView::SetTextureCoord(float x ,  float z ,  int mRowIndex ,  int mColIndex)
{
	double X=x*theApp.m_Cell_xwidth;
	double Y=-z*theApp.m_Cell_xwidth;
	
	float u=(X)/(m_Texturexy[mCurrentTextID][2]-m_Texturexy[mCurrentTextID][0]);
	float v=-(Y)/(m_Texturexy[mCurrentTextID][3]-m_Texturexy[mCurrentTextID][1]);	
	glMultiTexCoord2fARB(GL_TEXTURE0_ARB ,  u ,  v) ; // ָ����������ԪTEXTURE0����������
	glMultiTexCoord2fARB(GL_TEXTURE1_ARB ,  u ,  v) ; // ָ����������ԪTEXTURE1����������
}

//�ڵ��ѷ��޲�(�ײ�)
void CT3DSystemView::CracksPatchBottom(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	if(nSize<=0) return;
	if(m_ifZoomonRoad==FALSE) return;
	
	if(nZCenter+2*nSize<m_nMapSize)
	{
		if(!m_pbQuadMat[m_CurrentDemArrayIndex][nXCenter+(nZCenter+2*nSize)*m_nMapSize])
			return;
	}
	else
		return;
	CracksPatchBottom(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex) ; // �ڵ��ѷ��޲�
	SetTextureCoord(nXCenter , nZCenter+nSize ,  mRowIndex ,  mColIndex); //������������
	glVertex3i(nXCenter*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter , nZCenter+nSize , mRowIndex ,  mColIndex) , -(nZCenter+nSize)*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	CracksPatchBottom(nXCenter-nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
}

//�ڵ��ѷ��޲�(���)
void CT3DSystemView::CracksPatchLeft(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	
	if(nSize<=0) return;
	if(m_ifZoomonRoad==FALSE) return;
	
	if(nXCenter-2*nSize>=0)
	{
		if(!m_pbQuadMat[m_CurrentDemArrayIndex][(nXCenter-2*nSize)+nZCenter*m_nMapSize])
			return;
	}
	else
		return;
	CracksPatchLeft(nXCenter-nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
	SetTextureCoord(nXCenter-nSize , nZCenter ,  mRowIndex ,  mColIndex); //������������
	glVertex3i((nXCenter-nSize)*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter-nSize , nZCenter , mRowIndex ,  mColIndex) , -nZCenter*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	
	CracksPatchLeft(nXCenter-nSize/2 , nZCenter-nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
	
}
//�ڵ��ѷ��޲�(�Ҳ�)
void CT3DSystemView::CracksPatchRight(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	
	if(nSize<=0) return;
	if(m_ifZoomonRoad==FALSE) return;
	
	if(nXCenter+2*nSize<m_nMapSize)
	{
		if(!m_pbQuadMat[m_CurrentDemArrayIndex][(nXCenter+2*nSize)+nZCenter*m_nMapSize])
			return;
	}
	else
		return;
	CracksPatchRight(nXCenter+nSize/2 , nZCenter-nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
	SetTextureCoord(nXCenter+nSize , nZCenter ,  mRowIndex ,  mColIndex); //������������
	glVertex3i((nXCenter+nSize)*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter+nSize , nZCenter , mRowIndex ,  mColIndex) , -nZCenter*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	
	CracksPatchRight(nXCenter+nSize/2 , nZCenter+nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
}

//�ڵ��ѷ��޲�(����)
void CT3DSystemView::CracksPatchTop(int nXCenter ,  int nZCenter ,  int nSize ,  int mRowIndex ,  int mColIndex)
{
	if(nSize<=0) return;
	if(m_ifZoomonRoad==FALSE) return;
	
	if(nZCenter-2*nSize>=0)
	{
		if(!m_pbQuadMat[m_CurrentDemArrayIndex][nXCenter+(nZCenter-2*nSize)*m_nMapSize])
			return;
	}
	else
		return;
	CracksPatchTop(nXCenter-nSize/2 , nZCenter-nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
	SetTextureCoord(nXCenter , nZCenter-nSize ,  mRowIndex ,  mColIndex); //������������
	glVertex3i(nXCenter*theApp.m_Cell_xwidth+(mColIndex-1)*theApp.m_Dem_BlockWidth , GetHeightValue(nXCenter , nZCenter-nSize , mRowIndex ,  mColIndex) , -(nZCenter-nSize)*theApp.m_Cell_ywidth-((mRowIndex-1)*theApp.m_Dem_BlockWidth));
	CracksPatchTop(nXCenter+nSize/2 , nZCenter-nSize/2 , nSize/2 , mRowIndex ,  mColIndex);
}

//��������
void CT3DSystemView::DrawScene()
{
	InitTerr();
    SetDrawMode() ; // ���û�ͼģʽ


	if(this->m_stereo==TRUE)
	{
		SetCamra(1);
		glDrawBuffer(GL_BACK_LEFT);                      
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawSky();
		DrawClock();		
		DrawTerrain();
//		DrawRangeNavigate();

		glDrawBuffer(GL_BACK_RIGHT);                      
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		SetCamra(2);
		DrawSky();
		DrawClock();
		glCallList(m_TerrainList);
//		glCallList(m_NavigateList);

	}
	else
	{
	//	SetCamra(0) ; // �������
		glDrawBuffer(GL_BACK);                     
		glClearColor(1.0f , 1.0f , 1.0f , 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawSky();
		if(m_ViewType==GIS_VIEW_ORTHO)		
		{
			DrawTerrain_ORTHO();
		}
		else if(m_ViewType==GIS_VIEW_PERSPECTIVE)
		{
			DrawClock();//����ʱ��ָ����
			DrawTerrain() ; // ��ά���λ���
			
		}
		
		if(m_QueryType==QUERY_COORDINATE || m_QueryType==QUERY_DISTENCE || m_QueryType==SELECTLINE)
			DrawSearchPoint() ; // ���ƿռ��ѯ��־
		

		if(m_ViewType==GIS_VIEW_ORTHO)	
		{
			DrawRailwaythesme_Ortho();
		}
		else if(m_ViewType==GIS_VIEW_PERSPECTIVE) 
		{
			DrawRailwaythesme();
		}
		DrawTerrainDelaunay();	//���ƾ�����·����άģ�����άDelaunay����
		DrawFlyPath();//���Ʒ���·��

	}

}

//����Ŀ
void CT3DSystemView::OnMenuOpenproject() 
{
	COpenProject dlg;
	BeginWaitCursor() ; // ���ñ�������ʾɳ©��� , �����û�ϵͳæ
	if(dlg.DoModal()==IDOK)
	{
		theApp.bLoadImage=TRUE ; // Ӱ����سɹ�
		OnDraw (GetDC()) ; // �򿪳ɹ� , ������ά����
	}
	EndWaitCursor();	//������л�ΪĬ�Ϲ�� , �����ȴ�
}

//��oracle���ݿ���ж�ȡBLOB���͵�Ӱ���������ݲ�д����ʱӰ�������ļ�
BOOL CT3DSystemView::ExportBlobTextureToFIle(CString strFilename ,  int RowIndex ,  int ColIndex ,  int mID)
{
	CString tt;
	
	tt.Format("SELECT �������� FROM Texture WHERE �к�=%d AND �к�=%d AND ������������=%d AND ���= :%d FOR UPDATE" , RowIndex , ColIndex , m_currebtPhramid , mID);
	BOOL bt=myOci.ReadBOLBDataFromDB(strFilename , tt , mID) ; // �����ݿ��ж�ȡBLOB����
	return bt;
}

//���û�ͼģʽ
void CT3DSystemView::SetDrawMode()
{
	switch(m_Drawmode)//����ģʽ 
	{
	case 1://�߿�ģʽ
		glDisable(GL_TEXTURE_2D) ; // �ر�������
		glPolygonMode(GL_FRONT_AND_BACK , GL_LINE);
		break;
	case 2://����ģʽ
		glDisable(GL_TEXTURE_2D) ; // ����������
		glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
		break;
	case 3://����ģʽ
		glEnable(GL_TEXTURE_2D) ; // ����������
		glPolygonMode(GL_FRONT_AND_BACK , GL_FILL);
		break;
	}

	
}


//�߿�ģʽ
void CT3DSystemView::OnDrawmodeLine() 
{

	if(m_Drawmode!=1) 
	{
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
	}
	
	m_Drawmode =1;
	OnDraw (GetDC()) ; // �򿪳ɹ� , ������ά����
	
}

//����ģʽ
void CT3DSystemView::OnDrawmodeRender() 
{
	if(m_Drawmode!=2) 
	{
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
	}
	m_Drawmode =2;
	OnDraw (GetDC()) ; // �򿪳ɹ� , ������ά����
}

//����ģʽ
void CT3DSystemView::OnDrawmodeTexture() 
{
	if(m_Drawmode!=3) 
	{
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
	}
	m_Drawmode =3;
	OnDraw (GetDC()) ; // �򿪳ɹ� , ������ά����
}

//������ձ���
void CT3DSystemView::DrawSky()
{
	
	glPushMatrix();
	SetSkyProjection() ; // ���ñ������ͶӰ
	glCallList(m_SkyList);
	if(m_bShowbreviary==TRUE)  //�����ʾ����ͼ
	{
		SetSkyProjectionNavigate() ; // ���õ���ͼ�ı������ͶӰ
		glCallList(m_SkyList); ; // ���ñ��������ʾ�б�
	}
	glPopMatrix();
	glViewport(0 ,  0 ,  WinViewX , WinViewY) ; // ���������ӿڴ�С
	
}

//�������ͶӰ����
void CT3DSystemView::SetSkyProjection()
{
	glViewport(0 ,  0 ,  WinViewX , WinViewY) ; // �����ӿڴ�С
	
    glMatrixMode( GL_PROJECTION ); //����ǰ��������ΪͶӰ����
    glLoadIdentity() ; // ����ǰ�����û�Ϊ��λ��  
	
    //��������ͶӰ�Ӿ���
	if (WinViewX <= WinViewY) 
		glOrtho (0.0f ,  1.0f ,  0.0f , 1.0f*(GLfloat)WinViewX/(GLfloat)WinViewY ,  -1.0f , 1.0f);
    else 
		glOrtho (0.0f , 1.0f*(GLfloat)WinViewY/(GLfloat)WinViewX ,  0.0f ,  1.0f ,  -1.0f ,  1.0f);
	
	glMatrixMode( GL_MODELVIEW ) ; // ����ǰ��������Ϊģ�;���	
	glLoadIdentity ();	//����ǰ�����û�Ϊ��λ��  
}

//������յ���ͼͶӰ����
void CT3DSystemView::SetSkyProjectionNavigate()
{
	glViewport(WinViewX*5/6 ,  WinViewY*5/6 , WinViewX/6 ,  WinViewY/6) ; // �����ӿڴ�С
	
    glMatrixMode( GL_PROJECTION ); //����ǰ��������ΪͶӰ����
    glLoadIdentity() ; // ����ǰ�����û�Ϊ��λ��  
	
	//��������ͶӰ�Ӿ���
    if (WinViewX <= WinViewY) 
		glOrtho (0.0f ,  1.0f ,  0.0f , 1.0f*(GLfloat)WinViewX/(GLfloat)WinViewY ,  -1.0f , 1.0f);
    else 
		glOrtho (0.0f , 1.0f*(GLfloat)WinViewY/(GLfloat)WinViewX ,  0.0f ,  1.0f ,  -1.0f ,  1.0f);
	
	glMatrixMode( GL_MODELVIEW ) ; // ����ǰ��������Ϊģ�;���	
	glLoadIdentity ();	//����ǰ�����û�Ϊ��λ��  
}

//���ɻ��Ʊ��������ʾ�б�
void CT3DSystemView::makeSkykList()
{
	glNewList(m_SkyList , GL_COMPILE);
		DrawBackground(); //���Ʊ������         
	glEndList();
}

//���Ʊ������    
void CT3DSystemView::DrawBackground()
{
	glPushMatrix();	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	
	glPolygonMode(GL_FRONT_AND_BACK , GL_FILL); 
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D ,  m_cTxtSky.GetTxtID());
	
	glBegin(GL_QUADS);
	{			
		glTexCoord2f((float)0.0 ,  (float)1.0);	glVertex2f(0.0 , 1.0);
		glTexCoord2f((float)1.0 ,  (float)1.0);	glVertex2i(1.0 , 1.0);
		
		glTexCoord2f((float)1.0 ,  (float)0.0); glVertex2f(1.0f , 0.0f);
		glTexCoord2f((float)0.0 ,  (float)0.0); glVertex2f(0.0f , 0.0f);
	}
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK , GL_LINE); 
	glDisable(GL_TEXTURE_2D);	
	glEnable(GL_DEPTH_TEST);	
	glPopMatrix();
	
}

//˫Ŀ������ʾ��/�ر�
void CT3DSystemView::OnMenuStereo() 
{
	if(m_stereo==TRUE)//���������ģʽ
		m_stereo=FALSE;//��־Ϊ�ر�
	else ////�����������ģʽ
	{
		m_stereo=TRUE;//��־Ϊ��
		
	}
	OnDraw (GetDC());//ˢ����ά����
}

//����"˫Ŀ����ģʽ"�Ӳ˵�ѡ�б�־
void CT3DSystemView::OnUpdateMenuStereo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(bStereoAvailable); //�����ʾ��֧������ģʽ
	pCmdUI->SetCheck(m_stereo);//����m_stereoֵ��������"˫Ŀ����ģʽ"�Ӳ˵�ѡ�б�־
	
}

//�ռ��ѯ��־����
void CT3DSystemView::OnSpacequerySet() 
{
	CSpaceSearchSet dlg;
	
	dlg.m_shizxLength=m_shizxLength ; // ��ѯ��־ʮ���߳���
	dlg.m_shuzxHeight=m_shuzxHeight ; // ��ѯ��־��ֱ�߸߶�
	dlg.m_QueryLineWidth=m_QueryLineWidth ; // ��ѯ��־�ߵĿ��
	dlg.m_QueryColorR=m_QueryColorR ; // ��ѯ��־�ߵ���ɫ(��)
	dlg.m_QueryColorG=m_QueryColorG ; // ��ѯ��־�ߵ���ɫ(��)
	dlg.m_QueryColorB=m_QueryColorB ; // ��ѯ��־�ߵ���ɫ(��)
	if(dlg.DoModal()==IDOK) //����Ի���򿪳ɹ�
	{
		m_shizxLength=dlg.m_shizxLength ; // �õ������õĲ�ѯ��־ʮ���߳���
		m_shuzxHeight=dlg.m_shuzxHeight ; // �õ������õĲ�ѯ��־��ֱ�߸߶�
		m_QueryLineWidth=dlg.m_QueryLineWidth ; // �õ������õĲ�ѯ��־�ߵĿ��
		m_QueryColorR=dlg.m_QueryColorR ; // �õ������õĲ�ѯ��־�ߵ���ɫ(��)
		m_QueryColorG=dlg.m_QueryColorG ; // �õ������õĲ�ѯ��־�ߵ���ɫ(��)
		m_QueryColorB=dlg.m_QueryColorB ; // �õ������õ�//��ѯ��־�ߵ���ɫ(��)
	}	
}


void CT3DSystemView::OnLButtonDown(UINT nFlags ,  CPoint point) 
{
	/**/
	if(m_ViewType==GIS_VIEW_ORTHO)	//���������ͶӰģʽ	
	{
		if(m_OrthoZommPan==ORTHO_ZOOMIN) //�Ŵ�Ӱ��ģʽ
			OnOrthoZoomIn(); 
		else if(m_OrthoZommPan==ORTHO_ZOOMOUT)//��СӰ��ģʽ
			OnOrthoZoomOut();
		else if(m_OrthoZommPan==ORTHO_PAN)//ƽ��Ӱ��ģʽ
		{
			m_preX=point.x;
			m_preY=point.y;
			OnOrthoPan();
		}
		else if(m_OrthoZommPan==ORTHO_ZOOMWINDOW) //�����Ŵ�ģʽ
		{
			if(m_pushNumb<=0) //
			{
				m_preX=point.x;//��¼����1������
				m_preY=point.y;
				
				m_pushNumb=1;
				SetCapture();
			}
			else if(m_pushNumb==1)
			{
				m_currentX=point.x;//��¼����2������
				m_currentY=point.y;
				
				m_OrthoZoomWindowRect_x1=mCalF.MinValueXY(m_preX,m_currentX);
				m_OrthoZoomWindowRect_y1=mCalF.MinValueXY(m_preY,m_currentY);
				m_OrthoZoomWindowRect_x2=mCalF.MaxValueXY(m_preX,m_currentX);
				m_OrthoZoomWindowRect_y2=mCalF.MaxValueXY(m_preY,m_currentY);
				
				float bl1=WinViewX/(m_OrthoZoomWindowRect_x2-m_OrthoZoomWindowRect_x1);
				float bl2=WinViewY/(m_OrthoZoomWindowRect_y2-m_OrthoZoomWindowRect_y1);
				float bl=bl1;
				if(bl>bl2)	
					bl=bl2;
				
				m_OrthoViewSize=m_OrthoViewSize/(1+bl/5);
				OnDraw (GetDC());
				m_pushNumb=0;
				ReleaseCapture();
				
			}
		}
		
	}


	if(m_QueryType==QUERY_COORDINATE)//�ռ���ά�����ѯ
	{
		m_bmouseView=false;
		m_oldMousePos=point;
		ScreenToGL(point);
	}
	else if(m_QueryType==QUERY_DISTENCE)//�ռ�����ѯ
	{
		m_bmouseView=false; // �ر����������ת
		m_oldMousePos=point;
		ScreenToGL(point);
	}	
	else if(m_QueryType==SELECTLINE)
	{
		m_bmouseView=false; // �ر����������ת
		m_oldMousePos=point;
		ScreenToGL(point); 
	}
	else if(m_QueryType==SELECTFLYPATH)//���з���·��ѡ��
	{
		m_bmouseView=false;
		m_oldMousePos=point;
		ScreenToGL(point);
	}
	else
	{
		m_bmouseView=true;
		m_oldMousePos=point;
	}

	CView::OnLButtonDown(nFlags ,  point);
}

//��ѯ��ά����
void CT3DSystemView::OnQueryCoordinate() 
{
	m_OrthoZommPan=-1;
	if(m_QueryType==QUERY_COORDINATE) //�����ǰ�Ѿ��ǲ�ѯ��ά����״̬����ر�
		m_QueryType=-1;
	else //�����ǰ�Ѿ����ǲ�ѯ��ά����״̬�����
		m_QueryType=QUERY_COORDINATE;
}

//�����Ƿ�ѡ��״̬
void CT3DSystemView::OnUpdateQueryCoordinate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_QueryType==QUERY_COORDINATE);
	
}

//��ѯ�ռ����
void CT3DSystemView::OnQueryDistence() 
{
	m_OrthoZommPan=-1;
	
	if(m_QueryType==QUERY_DISTENCE) //�����ǰ�Ѿ��ǲ�ѯ�ռ����״̬����ر�
		m_QueryType=-1;
	else // �����ǰ���ǲ�ѯ�ռ����״̬����رգ����
		m_QueryType=QUERY_DISTENCE;
}

//�����Ƿ�ѡ��״̬
void CT3DSystemView::OnUpdateQueryDistence(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_QueryType==QUERY_DISTENCE);
	
}

//
void CT3DSystemView::ScreenToGL(CPoint point)
{
	int mouse_x=point.x;
	int mouse_y=point.y;
	
	GLint viewport[4];
	GLdouble modelview[16] , projection[16];
	GLdouble wx , wy , wz;
	float winX , winY , winZ;
	
	glPushMatrix();
	glGetDoublev(GL_MODELVIEW_MATRIX ,  modelview);
	glGetDoublev(GL_PROJECTION_MATRIX ,  projection);
	glGetIntegerv(GL_VIEWPORT ,  viewport);
	glPopMatrix();
	
	winX=(float)mouse_x;
	winY=(float)viewport[3]-(float)mouse_y-1;
	glReadPixels(mouse_x , 
		int(winY) , 
		1 , 1 , 
		GL_DEPTH_COMPONENT , 
		GL_FLOAT , 
		&winZ);
	gluUnProject((GLdouble)winX , (GLdouble)winY , (GLdouble)
		winZ , modelview , projection , viewport , &wx , &wy , &wz);
	
	CString tt;
	

	
	
	if(winZ>=0 && winZ<1.0) 
	{
		if(m_QueryType==QUERY_COORDINATE)//��ѯ��ά����
		{
			if(m_ViewType==GIS_VIEW_ORTHO) //���������ͶӰģʽ
			{
				double mx=wx+m_ortho_CordinateOriginX; //����x����
				double my=wy+m_ortho_CordinateOriginY; //����y����
				mx=theApp.m_DemLeftDown_x+mx*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//ת��Ϊ�������
				my=theApp.m_DemLeftDown_y+my*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//ת��Ϊ�������
				wz=m_demInsert.GetHeightValue(mx,my,2);//��DEM���ڲ����Ӧ�ĸ߳�
				tt.Format("��ǰ����(x,y,z)=(%.3f,%.3f,%.3f)",mx,my,wz);
			}
			else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�����͸��ͶӰģʽ
			{
				tt.Format("��ǰ����(x,y,z)=(%.3f,%.3f,%.3f)",wx+theApp.m_DemLeftDown_x,-wz+theApp.m_DemLeftDown_y,wy);	
				
			}
			pt1[0]=wx;pt1[1]=wy;pt1[2]=wz; //��ѯ��õ���ά�������
			OnDraw(GetWindowDC()); //ˢ����ά����
			MessageBox(tt,"��ά�����ѯ",MB_ICONINFORMATION); //���������ѯ��Ϣ
		}	
		else if(m_QueryType==QUERY_DISTENCE) // ��ѯ�ռ����
		{
			if(	m_bSearchDistencePtNums>=2) // ���ѡ�����2��������
				m_bSearchDistencePtNums=0;
			
			m_bSearchDistencePtNums++ ; //  ѡ����� + 1
			
			if(m_bSearchDistencePtNums==1) // ���ֻѡ����1����
			{
				pt1[0]=wx;pt1[1]=wy;pt1[2]=wz;	// ����ά������洢������ pt1[] ����
			}
			else	//ѡ���������㣬���ʾ���Լ���ռ������		 		
			{
				pt2[0]=wx;pt2[1]=wy;pt2[2]=wz; // ����ά������洢������ pt2[] ����

				double mdistence;
				
				if(m_ViewType==GIS_VIEW_ORTHO)	 //���������ͶӰģʽ
				{
					double nx1,ny1,nz1,nx2,ny2,nz2;
					nx1=pt1[0]+m_ortho_CordinateOriginX;//����P1��x����
					nx1=theApp.m_DemLeftDown_x+nx1*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//��P1��x����ת��Ϊ�������
					ny1=pt1[1]+m_ortho_CordinateOriginY;//����P1��y����
					ny1=theApp.m_DemLeftDown_y+ny1*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//��P1��y����ת��Ϊ�������
					nz1	=m_demInsert.GetHeightValue(nx1,ny1,2);//��DEM���ڲ��P1���Ӧ�ĸ߳�
					pt1[2]=nz1;
					
					nx2=pt2[0]+m_ortho_CordinateOriginX;//����P2��x����
					nx2=theApp.m_DemLeftDown_x+nx2*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//��P2��x����ת��Ϊ�������
					ny2=pt2[1]+m_ortho_CordinateOriginY;//����P2��y����
					ny2=theApp.m_DemLeftDown_y+ny2*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//��P2��y����ת��Ϊ�������
					nz2	=m_demInsert.GetHeightValue(nx2,ny2,2);//��DEM���ڲ��P2���Ӧ�ĸ߳�
					pt2[2]=nz2;
					
					//�������
					mdistence=sqrt((nx2-nx1)*(nx2-nx1)+(ny2-ny1)*(ny2-ny1)+(nz2-nz1)*(nz2-nz1));
					tt.Format("����Ϊ:\n(x1,y1,z1)=(%.3f,%.3f,%.3f)\n(x2,y2,z2)=(%.3f,%.3f,%.3f)\n����Dis=%.3f",\
						nx1,ny1,nz1,nx2,ny2,nz2,mdistence);
					
				}
				else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�����͸��ͶӰģʽ
				{
					//�������
					mdistence=sqrt((pt2[0]-pt1[0])*(pt2[0]-pt1[0])+(pt2[1]-pt1[1])*(pt2[1]-pt1[1])+(pt2[2]-pt1[2])*(pt2[2]-pt1[2]));
					tt.Format("����Ϊ:\n(x1,y1,z1)=(%.3f,%.3f,%.3f)\n(x2,y2,z2)=(%.3f,%.3f,%.3f)\n����Dis=%.3f",pt1[0]+theApp.m_DemLeftDown_x,-pt1[2]+theApp.m_DemLeftDown_y,pt1[1],pt2[0]+theApp.m_DemLeftDown_x,-pt2[2]+theApp.m_DemLeftDown_y,pt2[1],mdistence);
				}
				
				OnDraw(GetWindowDC());//ˢ����ά����
				MessageBox(tt,"��ά�����ѯ",MB_ICONINFORMATION);//���������ѯ��Ϣ

			}
		}
		else if(m_QueryType==SELECTLINE) //�������άѡ�����
		{
			
			PCordinate ppt = new Cordinate;  //����
			if( ppt == NULL )      //���ʧ�� 
			{  
				AfxMessageBox( "Failed to add a new ppt"); 
				return ;        
			}
			
			if(m_ViewType==GIS_VIEW_ORTHO)	//���������ͶӰģʽ	
			{
				double mx=wx+m_ortho_CordinateOriginX; //����x����
				double my=wy+m_ortho_CordinateOriginY; //����y����
				mx=theApp.m_DemLeftDown_x+mx*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//ת��Ϊ�������
				my=theApp.m_DemLeftDown_y+my*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//ת��Ϊ�������
				wz=m_demInsert.GetHeightValue(mx,my,2);//��DEM���ڲ����Ӧ�ĸ߳�
				mx-=theApp.m_DemLeftDown_x;
				my-=theApp.m_DemLeftDown_y;
				ppt->x=mx;ppt->y=wz;ppt->z=-my; //��¼ת�������ƽ�����ά����				
			}
			else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�����͸��ͶӰģʽ
			{
				ppt->x=wx;ppt->y=wy;ppt->z=wz;  //��¼��ƽ�����ά����	
			}
			
			
			m_oldlinePtnums=myDesingScheme.PtS_JD.GetSize();//��ǰ��·����ԭ����ƽ�����

			if(m_oldlinePtnums==0) //�����ǰ��·����û����ƽ���,����û�н��и÷��������
			{
				myDesingScheme.PtS_JD.Add(ppt); //������ƽ��㵽PtS_JD����
				m_linePtnums=myDesingScheme.PtS_JD.GetSize();//��ǰ��·����ԭ����ƽ�����
				
				PLineCurve pTempCurveElements = new LineCurve; //�����µĽ������
				//��һ����ƽ���
				
				//ֱ�����=������������   ��ֱ���=������������
				pTempCurveElements->ZH=pTempCurveElements->HZ=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC;

				//��Բ���=������������   Բ�����=������������
				pTempCurveElements->HY=pTempCurveElements->YH=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC;
				
				//ת��ǡ����߳������߳�=0
				pTempCurveElements->Alfa=pTempCurveElements->T=pTempCurveElements->L=0;
			
				//���߰뾶����ת���͡���ʸ����=0
				pTempCurveElements->R=pTempCurveElements->RoateStyle=pTempCurveElements->E=0;
				
				//�³����������߳���Բ���߳�����ֱ�߳�=0
				pTempCurveElements->P=pTempCurveElements->L0=pTempCurveElements->Ly=pTempCurveElements->Jzxc=0;

				//�������=������������
				pTempCurveElements->JDLC=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC;

				//����ID="JD0";
				pTempCurveElements->ID="JD0";

				pTempCurveElements->x=myDesingScheme.PtS_JD.GetAt(0)->x;			//�����x����				
				pTempCurveElements->y=fabs(myDesingScheme.PtS_JD.GetAt(0)->z);		//�����yx����				
				pTempCurveElements->z=-myDesingScheme.PtS_JD.GetAt(0)->y;			//�����z����

				//���뽻��Ԫ�ص�DCurveElementssģ��������
				myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].Add(pTempCurveElements); 
			}
			else  //�����ǰ��·������ƽ�����>0,��ʾ�Ѿ����и÷��������
			{
				CPLaneRL0 dlg; 
				if(m_linePtnums<=0)
					m_linePtnums=myDesingScheme.PtS_JD.GetSize();
				tt.Format("JD%d",m_linePtnums); //����ID�Զ�����
				
				dlg.m_ID=tt; //����ID
				if(dlg.DoModal()==IDOK) //���������Ϣ��Ƴɹ�
				{
					PLineCurve pTempCurveElements = new LineCurve; 
					
					pTempCurveElements->R=dlg.R;
					pTempCurveElements->L0=dlg.m_L0;
					pTempCurveElements->ID=dlg.m_ID;
					pTempCurveElements->P=(pTempCurveElements->L0*pTempCurveElements->L0)/(pTempCurveElements->R*24.0); 
					
					
					pTempCurveElements->x=ppt->x;
					pTempCurveElements->y=-ppt->z;
					pTempCurveElements->z=ppt->y;
					myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].Add(pTempCurveElements);
					myDesingScheme.PtS_JD.Add(ppt);
					
					
					m_linePtnums=myDesingScheme.PtS_JD.GetSize();
					
					if(myDesingScheme.PtS_JD.GetSize()>1)
						OnDraw(GetWindowDC());
					
				}
			}
			
		}
		else if(m_QueryType==SELECTFLYPATH) // ��������÷���·��
		{
			PCordinate ppt = new Cordinate;  
			if(m_ViewType==GIS_VIEW_ORTHO)	//���������ͶӰģʽ	
			{
				double mx=wx+m_ortho_CordinateOriginX;//����x����
				double my=wy+m_ortho_CordinateOriginY;//����y����
				mx=theApp.m_DemLeftDown_x+mx*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);//ת��Ϊ�������
				my=theApp.m_DemLeftDown_y+my*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)/m_ortho_CordinateXYScale;//ת��Ϊ�������
				wz=m_demInsert.GetHeightValue(mx,my,2);//��DEM���ڲ����Ӧ�ĸ߳�
				mx-=theApp.m_DemLeftDown_x; //x����任
				my-=theApp.m_DemLeftDown_y;//y����任
				ppt->x=mx;ppt->y=wz;ppt->z=-my; //��¼����·������ά����
			}
			else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�����͸��ͶӰģʽ
			{
				ppt->x=wx;ppt->y=wy;ppt->z=wz;//��¼����·������ά����
			}
			
			m_FlayPath.Add(ppt); //������·������ά����洢������m_FlayPath
			OnDraw(GetDC()); //ˢ����ά����,������ʾ���Ƶķ���·��
		}
	}
	else
	{
		MessageBox("���ѡ��㲻����ȷ , �뾫ȷѡ���!");
		m_bSearchDistencePtNums=0;
	}
}

//���ƿռ��ѯ��־
void CT3DSystemView::DrawSearchPoint()
{
 
    glViewport(0 ,  0 ,  WinViewX ,  WinViewY) ; // ���������ӿڴ�С
	if(m_QueryType==QUERY_COORDINATE) //��ά�ռ������ѯ
	{
		if(pt1[0]!=-99999)
		{
			glLineWidth(m_QueryLineWidth) ; // ���ò�ѯ��־�߿��
			glColor3f(m_QueryColorR/255.0 , m_QueryColorG/255.0 , m_QueryColorB/255.0) ; // ���ò�ѯ��־����ɫ
			//����ʮ���Ͳ�ѯ��־��
			glBegin(GL_LINES);
				glVertex3f(pt1[0]-m_shizxLength , pt1[1] , pt1[2]);
				glVertex3f(pt1[0]+m_shizxLength , pt1[1] , pt1[2]);
				glEnd();
				
				glBegin(GL_LINES);
				glVertex3f(pt1[0] , pt1[1] , pt1[2]-m_shizxLength);
				glVertex3f(pt1[0] , pt1[1] , pt1[2]+m_shizxLength);
				glEnd();
				
				glBegin(GL_LINES);
				glVertex3f(pt1[0] , pt1[1] , pt1[2]);
				glVertex3f(pt1[0] , pt1[1]+m_shuzxHeight , pt1[2]);
			glEnd();
		}

	}
	else if(m_QueryType==QUERY_DISTENCE && m_bSearchDistencePtNums==2)//��ά�ռ�����ѯ(��ѡ�������ռ��֮����ܹ�����ռ����)
	{
		glLineWidth(m_QueryLineWidth) ; // ���ò�ѯ��־�߿��
		glColor3f(m_QueryColorR/255.0 , m_QueryColorG/255.0 , m_QueryColorB/255.0) ; // ���ò�ѯ��־����ɫ
		
		//����ʮ���Ͳ�ѯ��־��
		glBegin(GL_LINES);
		glVertex3f(pt1[0]-m_shizxLength , pt1[1] , pt1[2]);
		glVertex3f(pt1[0]+m_shizxLength , pt1[1] , pt1[2]);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]-m_shizxLength);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]+m_shizxLength);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]);
		glVertex3f(pt1[0] , pt1[1]+m_shuzxHeight , pt1[2]);
		glEnd();
		
		
		glBegin(GL_LINES);
		glVertex3f(pt2[0]-m_shizxLength , pt2[1] , pt2[2]);
		glVertex3f(pt2[0]+m_shizxLength , pt2[1] , pt2[2]);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f (pt2[0] , pt2[1] , pt2[2]-m_shizxLength);
		glVertex3f (pt2[0] , pt2[1] , pt2[2]+m_shizxLength);
		glEnd();
		
		glBegin(GL_LINES);
		glVertex3f(pt2[0] , pt2[1] , pt2[2]);
		glVertex3f(pt2[0] , pt2[1]+m_shuzxHeight , pt2[2]);
		glEnd();
		
		
		glBegin(GL_LINES);
		glVertex3f(pt1[0] , pt1[1] , pt1[2]);
		glVertex3f(pt2[0] , pt2[1] , pt2[2]);
		glEnd();

		glLineWidth(1.0);

	}
	else if(m_QueryType==SELECTLINE ||myDesingScheme.PtS_JD.GetSize()>0 )//�����ǰ�Ѿ���άѡ��״̬
	{
		//����ѡ������е���ƽ�������
		m_oldlinePtnums=m_linePtnums;
		glColor3f(0,0,1);
		glLineWidth(2.0);
	
		
		if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//�����͸��ͶӰģʽ
		{
			for (int i=0;i<myDesingScheme.PtS_JD.GetSize()-1;i++)
			{
				DrawCenterLine(i,TRUE,m_currentSchemeIndexs); //������·������
			}
		}
		else if(m_ViewType==GIS_VIEW_ORTHO)		//���������ͶӰģʽ
		{
			
			for (int i=0;i<myDesingScheme.PtS_JD.GetSize()-1;i++)
			{
				DrawCenterLine(i,TRUE,m_currentSchemeIndexs);//������·������
			}
		}
	}

}



//��Ӧ����Ƶ�����
void CT3DSystemView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(theApp.bLoginSucceed==FALSE) //��֤δ����Ŀ�������,����Ҫ��Ӧ����Ƶ���Ϣ
		return ; //����
	
	if(m_bmouseView==TRUE) //��������Ƴ�����ʱ
	{
		mCamraUpdate(); //�������ͼ���ʵ����ά����������ƶ�����ת����
		OnDraw (GetDC()); //ˢ����ά����
		
	}
	CView::OnMouseMove(nFlags, point);
}

//�������ͼ���ʵ����ά����������ƶ�����ת����
void CT3DSystemView::mCamraUpdate()
{
	CVector3 vCross = CrossProduct(m_vView - m_vPosition, m_vUpVector); //�������
	m_vStrafe = Normalize(vCross); //vCross��һ��
	SetViewByMouse(); //ͨ�����ʵ���������
	CheckForMovement();//ͨ������ʵ���������
	m_vPosition.y+=(m_viewHeight-m_oldviewHeight); //�µ�����ӵ�y����
	m_oldviewHeight=m_viewHeight; //��¼��ǰ����ӵ�߶�
}

//ͨ�����ʵ���������
void CT3DSystemView::SetViewByMouse()
{
	if(m_bmouseView==false) //��������Ƴ����ر�ʱ,����
		return;
 
	float angleY = 0.0f;							
	float angleZ = 0.0f;							
	static float currentRotX = 0.0f;
	
	POINT mousePos;									
	GetCursorPos(&mousePos);//�õ�����λ�ã�����Ļ�����ʾ,�洢��	mousePos������			
	
	//����������û�б仯,����
	if( (mousePos.x == m_oldMousePos.x) && (mousePos.y == m_oldMousePos.y) )
		return;
	
   /* �����y����ǰ��֮�������С(������С500��,���ֵ�ɸ���ʵ�ʵ�������),���angleYֵ
	̫��,��ʾ��ʹ���y����ǰ��֮���С,Ҳ�ᵼ����ά���γ�����Y�����ϱ仯�ܴ�*/
	angleY = (float)( (m_oldMousePos.x - mousePos.x) ) / 500.0f;

	/* �����z����ǰ��֮�������С(������С4000��,���ֵ�ɸ���ʵ�ʵ�������),���angleZֵ
	̫��,��ʾ��ʹ���z����ǰ��֮���С,Ҳ�ᵼ����ά���γ�����Z�����ϱ仯�ܴ�*/
	angleZ = (float)( (m_oldMousePos.y - mousePos.y) ) / 4000.0f;
	
	currentRotX -= angleZ;  
	
	CVector3 vAxis = CrossProduct(m_vView - m_vPosition, m_vUpVector); //�������
	vAxis = Normalize(vAxis);	//vAxis��һ��
	
	RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);//ͨ���������������ת(��ת�ӽ�)
	RotateView(angleY, 0, 1, 0);//ͨ���������������ת(��ת�ӽ�)

	m_oldMousePos.x=mousePos.x;		//��¼��ǰ���x����
	m_oldMousePos.y=mousePos.y;		//��¼��ǰ���y����
		
}

//ͨ���������������ת(��ת�ӽ�)
void CT3DSystemView::RotateView(float angle, float x, float y, float z)
{
	CVector3 vNewView;
	
	CVector3 vView = m_vView - m_vPosition;	//����ӵ���۲����ά�����ֵ	
	
	float cosTheta = (float)cos(angle); //�õ���ת�ӽǵ�cos����ֵ
	float sinTheta = (float)sin(angle);//�õ���ת�ӽǵ�sin����ֵ
	
	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;
	
	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;
	
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;
	
	m_vView = m_vPosition + vNewView; //�õ���ת�������ӵ�����

	GetNorthPtangle(); //����ʱ��ָ����ָ��Ƕ�
}

//��Z�᷽�����ƶ�ʱ��������۲����ӵ�����
void CT3DSystemView::MoveCamera(float speed)
{
	CVector3 vVector = m_vView - m_vPosition;//����ӵ���۲����ά�����ֵ
	vVector = Normalize(vVector); //����ӵ���۲����ά�����ֵ��һ��
	m_vPosition.x += vVector.x * speed;	//����ӵ�x������	
	m_vPosition.z += vVector.z * speed;	//����ӵ�z������	
	m_vView.x += vVector.x * speed;		//����۲��x������
	m_vView.z += vVector.z * speed;		//����۲��z������
}

//���ݼ��̰���ֵ�������������
void CT3DSystemView::CheckForMovement()
{
	if(m_keynumber ==1)	// ���ϼ�ͷ�������򳡾����ƶ�(Z��������)
	{		
		MoveCamera(m_Step_Z); //��Z�᷽�����ƶ�ʱ��������۲����ӵ�����
	}
	
	if(m_keynumber ==2) 	// ���¼�ͷ�������򳡾����ƶ�(Z�Ḻ����)
	{
		MoveCamera(-m_Step_Z);	//��Z�᷽�����ƶ�ʱ��������۲����ӵ�����
	}
	
	if(m_keynumber ==3)	// �����ͷ�������������ƶ�����(X�Ḻ����)
	{
		StrafeCamera(-m_Step_X);	//��X�᷽�����ƶ�ʱ��������۲����ӵ�����
	}

	if(m_keynumber ==4)	// ���Ҽ�ͷ���������ҷ����ƶ�����(X��������)
	{
		StrafeCamera(m_Step_X);	//��X�᷽�����ƶ�ʱ��������۲����ӵ�����
	}

	Derx=m_vPosition.x-m_oldvPosition.x;//����ӵ���X�����ϵı仯����ֵ
	Derz=m_vPosition.z-m_oldvPosition.z;//����ӵ���Z�����ϵı仯����ֵ
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	
	//�������ӵ���X�����ϻ�Z�����ϵı仯����ֵ>=DEM�����ӿ���ܿ��ʱ,�����µĵ��ο�
	if(fabs(Derz)>=theApp.m_Dem_BlockWidth || fabs(Derx)>=theApp.m_Dem_BlockWidth)
	{
		if(m_loddem_StartRow!=1 && m_loddem_StartCol!=1 \
			&& m_loddem_EndRow!=theApp.m_BlockRows && m_loddem_EndCol!=theApp.m_BlockCols)
		{
// 			LoadNewData();
		}
	}
}

//��X�᷽�����ƶ�ʱ��������۲����ӵ�����
void CT3DSystemView::StrafeCamera(float speed)
{
	m_vPosition.x += m_vStrafe.x * speed;	//����ӵ�x������
	m_vPosition.z += m_vStrafe.z * speed;	//����ӵ�z������
	m_vView.x += m_vStrafe.x * speed;	//����۲��x������
	m_vView.z += m_vStrafe.z * speed;	//����۲��z������
}

//���̰�����Ӧ����
void CT3DSystemView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  m_keynumber=0;

   switch (nChar) //���ݰ����ַ���������Ӧ����
   {
   case VK_LEFT:  
	   m_keynumber=3;
	   m_xTrans-=m_Step_X;	//��X�������ƶ��ľ����ۼ�
	   OnDraw (GetDC());	//ˢ����ά����
	   break;
   case VK_RIGHT:
	   m_keynumber=4;
	   m_xTrans+=m_Step_X;	//��X�������ƶ��ľ����ۼ�
	   OnDraw (GetDC());	//ˢ����ά����
	   break;
   case VK_UP:
		m_zTrans -= m_Step_Z;	//��Z�������ƶ��ľ����ۼ�
	    m_keynumber=1;
	   OnDraw (GetDC());	//ˢ����ά����
	   break;
   case VK_DOWN:
		m_zTrans += m_Step_Z;	//��Z�������ƶ��ľ����ۼ�
		m_keynumber=2;
	   OnDraw (GetDC());	//ˢ����ά����
	   break;
	case 'F':     
		m_ViewWideNarrow += 1.0;	//������Ұ����,����������Χ������,�൱�������ͷ����Ļ�ⷽ���ƶ�	
		OnDraw (GetDC());//ˢ����ά����
		break;
	case 'V':     
		m_ViewWideNarrow -= 1.0;    //������Ұ��С,����������Χ��С��,�൱�������ͷ����Ļ�﷽���ƶ�
		OnDraw (GetDC());//ˢ����ά����
		break;
	case 'H':     					   //�ӽ�����
		m_ViewUpDown -= 0.2;
		OnDraw (GetDC());//ˢ����ά����
		break;
	case 'N':     					   //�ӽ�����
		m_ViewUpDown += 0.2;
		OnDraw (GetDC());//ˢ����ά����
		break;
	case 'J':     					   //����
		m_flyspeed -= 1;
		if(m_flyspeed<=1)
			m_flyspeed=1;
		SetFLyTimer();//���÷��м�ʱ��
		break;
	case 'M':     					   //����
		m_flyspeed += 1;
		SetFLyTimer();//���÷��м�ʱ��
		break;
	case 'G':     
		m_StaticHeight=m_StaticHeight*1.1;
		OnDraw (GetDC());//ˢ����ά����
		break;
	case 'B':     
		m_StaticHeight=m_StaticHeight/1.1; //���ٹ̶����и߶�
		OnDraw (GetDC());//ˢ����ά����
		break;
	case VK_F2:								 //��ʾ�����ȼ�����
		DisplayHelp();					   
		break;
	case 'Z':								//�ط���������
		OnFlyRoutinschemeline();					   
		break;
	case 'S':								//ֹͣ����
		OnFlyStop();					   
		break;
	case 'P':								//��ʼ/��ͣ����
		OnFlyPlaypause();					   
		break;
   }
	mCamraUpdate();	//���µ������
	m_keynumber=0; //�ָ�����0ֵ

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//��������Ҽ���Ӧ����
void CT3DSystemView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_QueryType=-1;//�ر���ά�ռ��ѯ,ѡ����ơ�����·������

	m_bmouseView=FALSE; //�ر����������ת
	m_OrthoZommPan=-1;	//�ر�����ͶӰģʽ�³�������
	
	CView::OnRButtonDown(nFlags, point);
}


//�˵�"����ͶӰģʽ"��Ӧ����
void CT3DSystemView::OnMenuProjecttionortho() 
{
 	m_stereo=FALSE; //�ر�
	m_ViewType =GIS_VIEW_ORTHO; //����ͶӰģʽ
	SetProjection(); //��������
	OnDraw (GetDC());	//ˢ����ά����
}

//"����ͶӰģʽ"����/ȡ��ѡ�б�־
void CT3DSystemView::OnUpdateMenuProjecttionortho(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ViewType ==GIS_VIEW_ORTHO);//����m_ViewTypeֵ�Ƿ�����ѡ�б�־
	
}

void CT3DSystemView::OnMenuPerspective() 
{
	m_ViewType =GIS_VIEW_PERSPECTIVE;
	SetProjection();//��������
	OnDraw (GetDC());	//ˢ����ά����
	
}

//"͸��ͶӰģʽ"����/ȡ��ѡ�б�־
void CT3DSystemView::OnUpdateMenuPerspective(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_ViewType ==GIS_VIEW_PERSPECTIVE);//����m_ViewTypeֵ�Ƿ�����ѡ�б�־
		pCmdUI->Enable(TRUE);
}


//����ͶӰģʽ�Ĳ�ͬ,��������ͶӰ����
void CT3DSystemView::SetProjection()
{
	glViewport(0, 0, WinViewX, WinViewY);//�����ӿڴ�С
    glMatrixMode(GL_PROJECTION);//����ǰ��������ΪͶӰ����
    glLoadIdentity();//����ǰ�����û�Ϊ��λ��
	
	if(m_ViewType==GIS_VIEW_ORTHO)	//���ͶӰģʽΪ����ͶӰģʽ	
	{
		float MS=0.6; //��ʼ����ͶӰ���ڴ�С,���ֵ�ɸ��ݵ��η�Χ���е���
		if (WinViewX <= WinViewY) 
		{
			//��������ͶӰ����
			glOrtho (-MS, MS, -MS*(GLfloat)WinViewY/(GLfloat)WinViewX, 
				MS*(GLfloat)WinViewY/(GLfloat)WinViewX, -1,1);
			
			m_ViewXYscale=(GLfloat)WinViewY/(GLfloat)WinViewX;//�洢�ӿڿ�߱���
		}
		else 
		{
			//��������ͶӰ����
			glOrtho (-MS*(GLfloat)WinViewX/(GLfloat)WinViewY, 
				MS*(GLfloat)WinViewX/(GLfloat)WinViewY, -MS, MS, -1, 1);
			
			m_ViewXYscale=(GLfloat)WinViewX/(GLfloat)WinViewY;//�洢�ӿڿ�߱���
		}
	}
	else if(m_ViewType==GIS_VIEW_PERSPECTIVE) 	//���ͶӰģʽΪ͸��ͶӰģʽ
	{
		//����͸��ͶӰ����
		gluPerspective(50.0 + m_ViewWideNarrow , m_aspectRatio , m_near , m_far);	
	}

	glMatrixMode(GL_MODELVIEW); //����ǰ��������Ϊģ�;���		
	glLoadIdentity();   //����ǰ�����û�Ϊ��λ��       
	
}

//��������ͶӰ���ϵ���ά����
void CT3DSystemView::DrawTerrain_ORTHO()
{
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
		

	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_TEXTURE_2D) ; // �ر�2D����ӳ�书��
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // ѡ��TEXTURE0Ϊ����Ŀ��
	glEnable(GL_TEXTURE_2D) ; // ����TEXTURE0��Ԫ
	
	glActiveTextureARB(GL_TEXTURE1_ARB) ; // ѡ��TEXTURE1Ϊ����Ŀ��
	glEnable(GL_TEXTURE_2D) ; // ����TEXTURE1��Ԫ , ����2D����ӳ��
	glTexEnvi(GL_TEXTURE_ENV ,  GL_TEXTURE_ENV_MODE ,  GL_COMBINE_ARB);
	glTexEnvi(GL_TEXTURE_ENV ,  GL_RGB_SCALE_ARB ,  2);
	glMatrixMode(GL_TEXTURE); //�������Ϊģ���������
	glLoadIdentity() ; // ����ǰ�����û�Ϊ��λ����
	glDisable(GL_TEXTURE_2D) ; // �ر�������
	glActiveTextureARB(GL_TEXTURE0_ARB) ; // ѡ��TEXTURE0Ϊ����Ŀ��
	SetDrawMode() ; // 
				
	glClearDepth(1.0f); 
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LESS); 
	
    glViewport(0, 0, WinViewX, WinViewY);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho (-m_OrthoViewSize*m_ViewXYscale, m_OrthoViewSize*m_ViewXYscale,-m_OrthoViewSize,m_OrthoViewSize,-1,1);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();  
	
	glTranslatef(m_OrthotranslateX,m_OrthotranslateY,0);//�ƶ�

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		
	int nCount=0;
		
	for(int j=0;j<m_LodDemblockNumber;j++)
	{
		memset(m_pbQuadMat[j],0,m_nMapSize*m_nMapSize);
	}

	//�½���ʾ�б�
	 glNewList(m_TerrainList,GL_COMPILE_AND_EXECUTE);

	 m_RenderDemblockNumber=0;
	 glColor3f(1,0,1);
	 for(int i=0;i<m_LodDemblockNumber;i++)
	 {
		   mCurrentTextID=i;
			m_CurrentDemArrayIndex=i;
			glBindTexture(GL_TEXTURE_2D, m_demTextureID[i]);//������
			m_lodDemBlock[i][3]=0;
			m_RenderDemblockNumber++;
			m_lodDemBlock[i][3]=1;
			DrawBlockOrtho(i); //���Ƶ��ο�
	}

	glEndList();
	  
		
	CString strText;
	strText.Format("���ڴ�/��Ⱦ������=%d/%d",m_LodDemblockNumber,m_RenderDemblockNumber);
		pMainFrame->Set_BarText(0,strText,0); 

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glDisable(GL_TEXTURE_2D);
	
	glActiveTextureARB(GL_TEXTURE0_ARB);		
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
}

//��������ͶӰģʽ�µ��ο�
void CT3DSystemView::DrawBlockOrtho(int DemBlockIndex)
{
	float mcolorR,mcolorG;
	
	//���ο�����x,y����
	double centerx=m_DemBlockCenterCoord[DemBlockIndex][0];
	double centery=fabs(m_DemBlockCenterCoord[DemBlockIndex][1]);
	
	
	double m_leftDownx,m_leftDowny,m_RightUpx,m_RightUpy;
	
	double Lx=(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);
	double Ly=(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y);
	
	m_leftDownx=centerx-theApp.m_Dem_BlockWidth/2-Lx/2;
	m_leftDowny=centery-theApp.m_Dem_BlockWidth/2-Ly/2;
	if((centerx+theApp.m_Dem_BlockWidth/2)>Lx)
		m_RightUpx=Lx-Lx/2;
	else
		m_RightUpx=centerx+theApp.m_Dem_BlockWidth/2-Lx/2;
	
	if((centery+theApp.m_Dem_BlockWidth/2)>Ly)
		m_RightUpy=Ly-Ly/2;
	else
		m_RightUpy=centery+theApp.m_Dem_BlockWidth/2-Ly/2;
	
	
	float m_scaleX=1.0/(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x);
	float m_scaleY=1.0/(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y);
	double x1,y1,x2,y2;
	x1=m_leftDownx*m_scaleX;
	y1=m_leftDowny*m_scaleX;
	x2=m_RightUpx*m_scaleX;
	y2=m_RightUpy*m_scaleX;
	
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0f,0.0f);
	GetOrthoColor(x1,y1,&mcolorR,&mcolorG);
	glColor3f(mcolorR,mcolorG,0.5);
	glVertex2f(x1,y1);
	
	glTexCoord2f(1.0f,0.0f);
	GetOrthoColor(x2,y1,&mcolorR,&mcolorG);
	glColor3f(mcolorR,mcolorG,0.5);
	glVertex2f(x2,y1);
	
	glTexCoord2f(1.0f,1.0f);
	GetOrthoColor(x2,y2,&mcolorR,&mcolorG);
	glColor3f(mcolorR,mcolorG,0.5);
	glVertex2f(x2,y2);
	
	glTexCoord2f(0.0f,1.0f);
	GetOrthoColor(x1,y2,&mcolorR,&mcolorG);
	glColor3f(mcolorR,mcolorG,0.5);
	glVertex2f(x1,y2);
	glEnd();
	
}

void CT3DSystemView::GetOrthoColor(double x1, double y1, float *mColorR, float *mColorG)
{
	//return;
	double mx=(x1+m_ortho_CordinateOriginX)*(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x)+theApp.m_DemLeftDown_x;
	double my=(y1+m_ortho_CordinateOriginY)*(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)+theApp.m_DemLeftDown_y;
	double mz=m_demInsert.GetHeightValue(mx,my,2);
	//��ߺ�ɫ 255,0,0  �����ɫ 0,255,0
	//Dr=255 DG=-255 DB=0
	*mColorR=(mz-m_minHeight)/(m_maxHeight-m_minHeight);
	*mColorG=1-(mz-m_minHeight)/(m_maxHeight-m_minHeight);
}

//�Ŵ�Ӱ��
void CT3DSystemView::OnOrthoZoomIn() 
{
	m_OrthoZommPan=ORTHO_ZOOMIN;
	m_OrthoViewSize=m_OrthoViewSize/1.1;
	
	OnDraw(GetDC());
	
}
//��СӰ��
void CT3DSystemView::OnOrthoZoomOut() 
{
	m_OrthoZommPan=ORTHO_ZOOMOUT;
	m_OrthoViewSize=m_OrthoViewSize*1.1;
	OnDraw(GetDC()); //ˢ����ά����
	
}

//�ƶ�Ӱ��
void CT3DSystemView::OnOrthoPan() 
{
	m_OrthoZommPan=ORTHO_PAN;
	OnDraw(GetDC());//ˢ����ά����
				
}

//�ָ���ʼ��С
void CT3DSystemView::OnOrthoZoomOrigin() 
{
	m_OrthoZommPan=ORTHO_ZOOMORIGIN;
	m_OrthoViewSize=0.3;
	OnDraw(GetDC());//ˢ����ά����
	
}

//��������
void CT3DSystemView::OnOrthoZoomWindow() 
{
	m_OrthoZommPan=ORTHO_ZOOMWINDOW;
	OnDraw(GetDC());//ˢ����ά����
	
}

void CT3DSystemView:: OnUpdateOnOrthoZoomIn(CCmdUI*  pCmdUI)   
{   
	pCmdUI->Enable(m_ViewType==GIS_VIEW_ORTHO);   
}

void CT3DSystemView:: OnUpdateOnOrthoZoomOut(CCmdUI*  pCmdUI)   
{   
	pCmdUI->Enable(m_ViewType==GIS_VIEW_ORTHO);   
}

void CT3DSystemView:: OnUpdateOnOrthoPan(CCmdUI*  pCmdUI)   
{   
	pCmdUI->Enable(m_ViewType==GIS_VIEW_ORTHO);   
}

void CT3DSystemView:: OnUpdateOnOrthoZoomOrigin(CCmdUI*  pCmdUI)   
{   
	pCmdUI->Enable(m_ViewType==GIS_VIEW_ORTHO);   
}

void CT3DSystemView:: OnUpdateOnOrthoZoomWindow(CCmdUI*  pCmdUI)   
{   
	pCmdUI->Enable(m_ViewType==GIS_VIEW_ORTHO);   
}

//��Ӧ������̧����Ϣ
void CT3DSystemView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	m_bmouseView=false; //�ر������ת�������
	
	//���������ͶӰģʽ�������ƶ�����ģʽ��
	if(m_ViewType==GIS_VIEW_ORTHO && m_OrthoZommPan==ORTHO_PAN)	
	{
		int dx=point.x-m_preX;//��X�����ƶ����� 
		int dy=point.y-m_preY;//��Y�����ƶ�����
		m_OrthotranslateX+=dx*0.00007;//X����任������ͶӰģʽ���ƶ�ֵ
		m_OrthotranslateY+=-dy*0.00007;//Y����任������ͶӰģʽ���ƶ�ֵ
		OnDraw (GetDC());//ˢ����ά����
	}
	
	CView::OnLButtonUp(nFlags, point);
}

//��άѡ�����
void CT3DSystemView::OnMenuLinedesign() 
{
	m_OrthoZommPan=-1;
	
	if(m_QueryType==SELECTLINE) //�����ǰ�Ѿ���άѡ��״̬����ر�
		m_QueryType=-1;
	else // //�����ǰ������άѡ��״̬�����
		m_QueryType=SELECTLINE;
}

//����ѡ��״̬
void CT3DSystemView::OnUpdateMenuLinedesign(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_QueryType==SELECTLINE);
}


//��������ͶӰģʽ�µ���ά��·
void CT3DSystemView::DrawRailwaythesme_Ortho()
{
	CString tt,strSql,m_style;
// 	long i;

	//������ݿ�û�м��سɹ����������ʧ�ܣ�����
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
	
	glLineWidth(4.0);//�����߿�
	SetDrawMode();//���û�ͼģʽ

	glViewport(0, 0, WinViewX, WinViewY);//���������ӿڴ�С
	
	if(b_haveMadeRail3DwayList_Ortho==FALSE )   //�����û�й�����·��άģ�͵���ʾ�б�
	{

		ReLoadCenterPt();//���´����ݿ��ж�ȡ��·�������������
		
		glNewList(m_Rail3DwayList_Ortho,GL_COMPILE_AND_EXECUTE);//������ʾ�б�
				
			glColor3f(0.75,0.75,0.75);//������ɫ
			glLineWidth(1.0);//�����߿�
		
				//1. �������·������
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//��·����������
				for (long i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
				{
					m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
					if(m_style!="������" && m_style!="����м��" &&m_style!="����յ�" &&m_style!="�������"  &&m_style!="�����м��" &&m_style!="�����յ�")
					{	
						DrawBP_Ortho(i,1);//�������·������
					}
					
				}
		
				//4.�����Ҳ�·������
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//��·����������
				
				for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
				{
					m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//��������
					//������������Ƿ�����������εĵ㣬�����·������		
					
					if(m_style!="������" && m_style!="����м��" &&m_style!="����յ�" &&m_style!="�������"  &&m_style!="�����м��" &&m_style!="�����յ�")
					{
				
					    glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//��·����������
						DrawBP_Ortho(i,2);//�����Ҳ�·������
						glBindTexture(GL_TEXTURE_2D, m_cTxtureSuigou.GetTxtID());//��ˮ������
						DrawSuiGou_Ortho(i);//����ˮ��
						
					}
				}
		

		//5.����������		
		
		m_TempPts.RemoveAll();
		PCordinate pt;
		glLineWidth(8.0);
		glColor3f(1,0,1);


		for (i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			
			//���δ������·��ά��ģ�������DrawCenterLine()����������·����
			if(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()<=0)
				DrawCenterLine(i,FALSE,m_currentSchemeIndexs);//������·����
			else
			{
			
				tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;

				if(tt!="����м��" && i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x;
					pt->y=-myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z; 
					pt->strJDStyle=tt;
					m_TempPts.Add(pt);
				}
				else //������ֵ���·λ�ڵ������£�������
				{		
					if(m_TempPts.GetSize()>1)
					{	
				
						glBegin(GL_LINE_STRIP);

						for(int k=0;k<m_TempPts.GetSize();k++)
						{
							tt=m_TempPts.GetAt(k)->strJDStyle;
							if(tt=="��������" || tt=="ֱ��������" || tt=="��ֱ������" || tt=="����-ֱ��������")
								glColor3f(1,0,0);
							else
								glColor3f(0,0,1);

							glVertex2f(GetOrthoX(m_TempPts.GetAt(k)->x),GetOrthoY(m_TempPts.GetAt(k)->y));
						}
						glEnd();
						m_TempPts.RemoveAll();
					}			
				}
			}
		}		


		//6.���ƹ��
		glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID());//�󶨹������
		glColor3f(0.5,0,0.4);//������ɫ
		glLineWidth(2.0);//�����߿�
		
		CString tt1,tt2;
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			tt1=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//��ǰ��������
			tt2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//��һ��������
			if(tt1!="����м��"  &&  tt2!="����м��")
			{
				//�Ծ��η�ʽ����ǰ�����ٹ������
				glBegin(GL_POLYGON);
				glTexCoord2f(0.0f,0.0f);//������������(��ǰ�����������)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1));
				
				glTexCoord2f(1.0f,0.0f); //������������(��ǰ��������Ҳ��)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2));
				
				glTexCoord2f(1.0f,1.0f);//������������(��һǰ��������Ҳ��)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
				
				glTexCoord2f(0.0f,1.0f);//������������(��һǰ�����������)
				glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
					GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
				
				glEnd();
			}
		
		}		


		//7.���Ƶ�������
		glBindTexture(GL_TEXTURE_2D, m_cTxtureGdToLJ.GetTxtID());//�󶨵�����������		
		glColor3f(1,1,0);//������
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			tt1=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//��ǰ��������
			tt2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//��һ��������
			if(tt1!="����м��"  &&  tt2!="����м��")
			{
				
			//�Ծ��η�ʽ���ӷ�ʽ��������������
			glBegin(GL_POLYGON);
			glTexCoord2f(1.0f,0.0f);//������������(��ǰ��������������)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1));
			
			glTexCoord2f(1.0f,1.0f);//������������(��ǰ�����������Ҳ��)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(0.0f,1.0f);//������������(��һ�����������Ҳ��)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(0.0f,0.0f);//������������(��һ��������������)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1));			
			glEnd();
			
			//�Ծ��η�ʽ���ӷ�ʽ�����Ҳ��������
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//������������(��ǰ�Ҳ������������)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			glTexCoord2f(0.0f,1.0f);//������������(��ǰ�Ҳ���������Ҳ��)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glTexCoord2f(1.0f,1.0f);//������������(��һ�Ҳ���������Ҳ��)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glTexCoord2f(1.0f,0.0f);//������������(��һ�Ҳ������������)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			glEnd();
			}
		}		
		


		//8.����·��
		glBindTexture(GL_TEXTURE_2D, m_cTxtureLJ.GetTxtID());//��·������
		glColor3f(1,0.5,0.25);//������ɫ
		for (i=0;i<myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			tt1=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//��ǰ��������
			tt2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//��һ��������
			if(tt1!="����м��"  &&  tt2!="����м��")
			{
				
			//�Ծ��η�ʽ���ӷ�ʽ�������·��
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//������������(��ǰ���·���������)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1));
			
			glTexCoord2f(0.0f,1.0f);//������������(��ǰ���·������Ҳ��)	
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(1.0f,1.0f);;//������������(��һ���·������Ҳ��)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1));
			
			glTexCoord2f(1.0f,0.0f);//������������(��һ���·���������)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1));
						
			glEnd();
			
			//�Ծ��η�ʽ���ӷ�ʽ�����Ҳ�·��
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//������������(��ǰ�Ҳ�·���������)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			
			glTexCoord2f(1.0f,0.0f);//������������(��ǰ�Ҳ�·������Ҳ��)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2));
			
			glTexCoord2f(1.0f,1.0f);//������������(��һ�Ҳ�·������Ҳ��)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glTexCoord2f(0.0f,1.0f);//������������(��һ�Ҳ�·���������)
			glVertex2f(GetOrthoX(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2),\
				GetOrthoY(-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2));
			
			glEnd();
			}
		}		

		glLineWidth(1.0);//�ָ��߿�
		glEndList();//������ʾ�б�
		b_haveMadeRail3DwayList_Ortho=TRUE;//��ʶ�Ѿ�������ʾ�б�
	}
	else  //����Ѿ�������·��άģ�͵���ʾ�б�,��ֱ�ӵ�����ʾ�б�
	{ 
		glCallList(m_Rail3DwayList_Ortho); //������·��άģ����ʾ�б�
	}
	

}

//����������
//λ�ڵ������µĲ��ֲ�����
void CT3DSystemView::DrawCenterLine(long index, BOOL ifSelectLine, int SchemeIndex)
{
	CString tt;
	double x1,y1,z1,x2,y2,z2;
	double x0,y0,z0;
	float DerDistence=2.0;

	float Dh;
	
	m_TempPts.RemoveAll();
	
	if(ifSelectLine==TRUE) //��ѡ�����
	{
		Dh=5;
		x1=myDesingScheme.PtS_JD.GetAt(index)->x;
		y1=myDesingScheme.PtS_JD.GetAt(index)->y;
		z1=myDesingScheme.PtS_JD.GetAt(index)->z;
		
		x2=myDesingScheme.PtS_JD.GetAt(index+1)->x;
		y2=myDesingScheme.PtS_JD.GetAt(index+1)->y;
		z2=myDesingScheme.PtS_JD.GetAt(index+1)->z;
	}
	else  //����Ŀʱ,���ƴ򿪵ķ���
	{
		Dh=5;
		x1=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index)->x;
		y1=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index)->y;
		z1=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index)->z;
		
		x2=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index+1)->x;
		y2=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index+1)->y;
		z2=myDesingScheme.PtS_3DLineZX[SchemeIndex].GetAt(index+1)->z;
		
	}
	glColor3f(0,0,1);

	PCordinate pt;
	
	double L=myDesingScheme.GetDistenceXYZ(x1,y1,z1,x2,y2,z2);
	double L0=0;
	if(m_ViewType==GIS_VIEW_ORTHO) //���������ͶӰģʽ
	{		
		while(L0<=L)
		{
			
			x0=x1+L0/L*(x2-x1);
			y0=y1+L0/L*(y2-y1);//�߼��߸߳�
			z0=z1+L0/L*(z2-z1);

			//����߳�
			float dmh=m_demInsert.GetHeightValue(x0+theApp.m_DemLeftDown_x,-z0+theApp.m_DemLeftDown_y,2);
			if(y0>=dmh-Dh) //����ߵ�̴߳��ڵ���߳�
			{
				pt=new Cordinate;
				pt->x =x0;
				pt->y=y0;
				pt->z =z0;
				m_TempPts.Add(pt);
			}
			else
			{
				if(m_TempPts.GetSize()>1) //��ʱ��������1
				{	
					
					glBegin(GL_LINE_STRIP); //��������ʽ����
					
					for(int k=0;k<m_TempPts.GetSize();k++)
					{
						glVertex2f(GetOrthoX(m_TempPts.GetAt(k)->x),GetOrthoY(-m_TempPts.GetAt(k)->z));
					}
					glEnd();
					m_TempPts.RemoveAll(); //���
					L0-=DerDistence;
				}
			}

			L0+=DerDistence;
			if(L0>=L)
			{
				x0=x2;
				y0=y2;
				z0=z2;
				dmh=m_demInsert.GetHeightValue(x0+theApp.m_DemLeftDown_x,-z0+theApp.m_DemLeftDown_y,2);
				if(y0>=dmh-Dh ) //����ߵ�̴߳��ڵ���߳�
				{
					pt=new Cordinate;
					pt->x =x0;
					pt->y=y0;
					pt->z =z0;
					m_TempPts.Add(pt);
					if(m_TempPts.GetSize()>1)
					{	
						
						glBegin(GL_LINE_STRIP); //��������ʽ����
						
						for(int k=0;k<m_TempPts.GetSize();k++)
						{
							glVertex2f(GetOrthoX(m_TempPts.GetAt(k)->x),GetOrthoY(-m_TempPts.GetAt(k)->z));
						}
						glEnd();
						m_TempPts.RemoveAll();
						
					}
				}
				break;
			}
		
		}
		if(m_TempPts.GetSize()>1)//��ʱ��������1
		{	
			
			glBegin(GL_LINE_STRIP);  //��������ʽ����
			
			for(int k=0;k<m_TempPts.GetSize();k++)
			{
				glVertex2f(GetOrthoX(m_TempPts.GetAt(k)->x),GetOrthoY(-m_TempPts.GetAt(k)->z));
			}
			glEnd();
			m_TempPts.RemoveAll();
		}
	}
	else if (m_ViewType==GIS_VIEW_PERSPECTIVE) //�����͸��ͶӰģʽ
	{
		while(L0<=L)
		{
			
			x0=x1+L0/L*(x2-x1);
			y0=y1+L0/L*(y2-y1);//���߸߳�
			z0=z1+L0/L*(z2-z1);
			
			//����߳�
			float dmh=m_demInsert.GetHeightValue(x0+theApp.m_DemLeftDown_x,-z0+theApp.m_DemLeftDown_y,2);
			if(y0>=dmh-Dh)  //����ߵ�̴߳��ڵ���߳�
			{
				pt=new Cordinate;
				pt->x =x0;
				pt->y=y0;
				pt->z =z0;
				m_TempPts.Add(pt);
			}
			else
			{
				if(m_TempPts.GetSize()>1)
				{	
					
					glBegin(GL_LINE_STRIP);
					
					for(int k=0;k<m_TempPts.GetSize();k++)
					{
						glVertex3f(m_TempPts.GetAt(k)->x,m_TempPts.GetAt(k)->y,
							m_TempPts.GetAt(k)->z);
						
					}
					glEnd();
					m_TempPts.RemoveAll();
					L0-=DerDistence;
				}
			}
			
			L0+=DerDistence;
			if(L0>=L)
			{
				x0=x2;
				y0=y2;
				z0=z2;
				dmh=m_demInsert.GetHeightValue(x0+theApp.m_DemLeftDown_x,-z0+theApp.m_DemLeftDown_y,2);
				if(y0>=dmh-Dh )//����ߵ�̴߳��ڵ���߳�
				{
					pt=new Cordinate;
					pt->x =x0;
					pt->y=y0;
					pt->z =z0;
					m_TempPts.Add(pt);
					if(m_TempPts.GetSize()>1)
					{	
						
						glBegin(GL_LINE_STRIP);
						
						for(int k=0;k<m_TempPts.GetSize();k++)
						{
							glVertex3f(m_TempPts.GetAt(k)->x,m_TempPts.GetAt(k)->y,
								m_TempPts.GetAt(k)->z);
						}
						glEnd();
						m_TempPts.RemoveAll();
						
					}
				}
				break;
			}
		}

		if(m_TempPts.GetSize()>1)
		{	
			
			glBegin(GL_LINE_STRIP);
			
			for(int k=0;k<m_TempPts.GetSize();k++)
			{
				glVertex3f(m_TempPts.GetAt(k)->x,m_TempPts.GetAt(k)->y,
					m_TempPts.GetAt(k)->z);
				
			}
			glEnd();
			m_TempPts.RemoveAll();
		}

	}
	
	
}

//��������ͶӰģʽ��x����
float CT3DSystemView::GetOrthoX(double x)
{
	float xt=x/(theApp.m_DemRightUp_x-theApp.m_DemLeftDown_x)-m_ortho_CordinateOriginX;
	return xt;
	
}

//��������ͶӰģʽ��y����
float CT3DSystemView::GetOrthoY(double y)
{
	float yt=y/(theApp.m_DemRightUp_y-theApp.m_DemLeftDown_y)*m_ortho_CordinateXYScale-m_ortho_CordinateOriginY;
	return yt;
	
}

//������Ʒ���
void CT3DSystemView::OnMenuLinesavescheme() 
{
	int manswer=MessageBox("�Ƿ�ȷ�ϱ��淽��?","���淽��",MB_ICONQUESTION|MB_YESNO);
	if(manswer==7)
		return;
	
	b_haveMadeRail3DwayList=FALSE;
	b_haveMadeRail3DwayList_Ortho=FALSE;
	if(myDesingScheme.JDCurveElementss[m_currentSchemeIndexs].GetSize()>0)
	{
		myDesingScheme.m_bHaveSaveScheme=TRUE;
		myDesingScheme.SavePlaneCurveData();//��������Ҫ�ص����ݿ���	
	}	
	
}


//ʵ��͸��ͶӰģʽ�µ���·��άģ�ͻ���
void CT3DSystemView::DrawRailwaythesme()
{

	//ѹ�����Զ�ջ
	glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_ENABLE_BIT|GL_POLYGON_BIT );
		glEnable(GL_DEPTH_TEST|GL_CULL_FACE);
		glCullFace(GL_BACK);

	//������ݿ�û�м��سɹ����������ʧ�ܣ�����
	if(theApp.bLoginSucceed==FALSE || m_bLoadInitDemData==FALSE)
		return;
	
	CString tt,strSql;
	CString m_style,m_stylePre,m_styleNext;
	PCordinate pt;
	

	SetDrawMode();//���û�ͼģʽ
	glViewport(0, 0, WinViewX, WinViewY); //���������ӿڴ�С
	
	
	if(b_haveMadeRail3DwayList==FALSE )  //�����û�й�����·��άģ�͵���ʾ�б�
	{

		
		ReLoadCenterPt();//���´����ݿ��ж�ȡ��·�������������
			


		glNewList(m_Rail3DwayList,GL_COMPILE_AND_EXECUTE); //������ʾ�б�
		
		glColor3f(0.75,0.75,0.75);//������ɫ
		glLineWidth(2.0);//�����߿�
		

		//1. �����Ŷ�
		myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].RemoveAll();
		myDesingScheme.GetBirdgeQDcordinate(m_Bridge.m_Bridge_QDSpace);//�����Ŷռ����������Ŷ�����
		for (long i=0;i<myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetSize();i++)
		{
		 	DrawSceneQD(myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->y1,\
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->z1,
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->y2,\
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->z2,
				myDesingScheme.PtS_BridgeQD3D[m_currentSchemeIndexs].GetAt(i)->QDHeight);
		}		

		
		//2. ��������������ά����
		myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].RemoveAll();
		myDesingScheme.GetBirdgeLGcordinate(m_Bridge.m_Bridge_HLSpace);//���������˼�������������������
		
		//3. �������·������
		glColor3f(1,0,0);		
		int mBridgeIndex=0;//������ʼ������
		glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID()); //��·����������
		for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle; //��������
			m_styleNext=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;	
		
			//������������Ƿ�����������εĵ㣬�����·������
			if(m_style!="������" && m_style!="����м��" &&m_style!="����յ�" \
				&&m_style!="�����м��" &&m_style!="�����յ�" && m_styleNext!="������" )
			{	
				DrawBP(i,1); //�������·������
				
			}
			if(m_style=="�������" || m_style=="�����յ�")	
			{
				
				glColor3f(0.5,0,1);
				if(i>0)
				{
					//��һ�㴦�Ľ�������
					m_styleNext=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;
						//�������յ㴦����
						//(��������:���������ֱ������,����Ҫ���ƻ���)
						int Innum;
						//���������·�������
						if(m_style=="�������")
							Innum=i;//i-1;
						else if(m_style=="�����յ�")
							Innum=i+1;
						
						//���������·�������
						DrawQDHP(Innum,m_style,m_Bridge.m_Bridge_HPangle/180.0*PAI,m_styleNext,mBridgeIndex);
				
				}
				if(m_style=="�����յ�")
					mBridgeIndex++;
			}
		}


		//4.�����Ҳ�·������
		glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());//��·����������
		for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//��������
			m_styleNext=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;//��һ��Ľ�������
			

			//������������Ƿ�����������εĵ㣬�����·������		
			if(m_style!="������" && m_style!="����м��" &&m_style!="����յ�" \
				&&m_style!="�����м��" &&m_style!="�����յ�" && m_styleNext!="������")
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				DrawBP(i,2);//�����Ҳ�·������
				
			}
			if(m_style!="������" && m_style!="����м��"  \
				&& m_style!="�������" && m_style!="�����м��" && m_style!="����м��" )
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureSuigou.GetTxtID());//��ˮ������
				DrawSuiGou(i);//����ˮ��
				
			}
		}
	


		//5.������·����
		glLineWidth(3.0);
		m_TempPts.RemoveAll();
		for ( i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
		{

			//���δ������·��ά��ģ�������DrawCenterLine()����������·����
			if(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()<=0)
				DrawCenterLine(i,FALSE,m_currentSchemeIndexs); //������·����
			else
			{				
				tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;//��������
				
				if(tt!="����м��" && i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x;
					pt->y=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y; 
					pt->z=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z; 
					pt->strJDStyle=tt;
					m_TempPts.Add(pt);
				}
				else //������ֵ���·λ�ڵ������£�������
				{		
					if(m_TempPts.GetSize()>1)
					{	
						
						glBegin(GL_LINE_STRIP);
						
						for(int k=0;k<m_TempPts.GetSize();k++)
						{
							tt=m_TempPts.GetAt(k)->strJDStyle;
							if(tt=="��������" || tt=="ֱ��������" || tt=="��ֱ������" || tt=="����-ֱ��������")
								glColor3f(1,0,0);
							else
								glColor3f(0,0,1);
							glVertex3f(m_TempPts.GetAt(k)->x,m_TempPts.GetAt(k)->y,m_TempPts.GetAt(k)->z);							
						}
						glEnd();
						m_TempPts.RemoveAll();
					}
				}
			}
		}	


	
		///////////////////////////////
       //6.���ƹ��
		glBindTexture(GL_TEXTURE_2D, m_cTxtureRailway.GetTxtID()); //�󶨹������
	 	glLineWidth(2.0);//�����߿�
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			
			if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Derh==0) //�����Ϊ0
				glColor3f(0,1,1); //������ɫ
			else
				glColor3f(1,0,1); //������ɫ
			float L=myDesingScheme.GetDistenceXY(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
		
			//�Ծ��η�ʽ����ǰ�����ٹ������	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f); //������������(��ǰ�����������)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1);
			glTexCoord2f(1.0f,0.0f); //������������(��ǰ��������Ҳ��)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1.0f,L/10);//������������(��һǰ��������Ҳ��)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(0.0f,L/10); //������������(��һǰ�����������)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			
			glEnd();

		}		
	
		//7.���Ƶ�������
		glBindTexture(GL_TEXTURE_2D, m_cTxtureGdToLJ.GetTxtID());//�󶨵�����������
		glColor3f(1,1,0);//������ɫ
		for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			//�Ծ��η�ʽ���ӷ�ʽ��������������	
			glBegin(GL_POLYGON);
			glTexCoord2f(1.0f,0.0f);//������������(��ǰ��������������)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1);
			glTexCoord2f(1.0f,1.0f);//������������(��ǰ�����������Ҳ��)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(0.0f,1.0f);//������������(��һ�����������Ҳ��)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(0.0f,0.0f);//������������(��һ��������������)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1);
			
			glEnd();
			
			//�Ծ��η�ʽ���ӷ�ʽ�����Ҳ��������
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//������������(��ǰ�Ҳ������������)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(0.0f,1.0f);//������������(��ǰ�Ҳ���������Ҳ��)
			glVertex3f(myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(1.0f,1.0f);//������������(��һ�Ҳ���������Ҳ��)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(1.0f,0.0f);//������������(��һ�Ҳ������������)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glEnd();
		}		
		
		//8.����·��
		glBindTexture(GL_TEXTURE_2D, m_cTxtureLJ.GetTxtID());//��·������
		glColor3f(1,0.5,0.25);//������ɫ
		for (i=0;i<myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			//�Ծ��η�ʽ���ӷ�ʽ�������·��	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//������������(��ǰ���·���������)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1);
			glTexCoord2f(0.0f,1.0f);//������������(��ǰ���·������Ҳ��)	
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(1.0f,1.0f);//������������(��һ���·������Ҳ��)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glTexCoord2f(1.0f,0.0f);//������������(��һ���·���������)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1);
			
			glEnd();			

			//�Ծ��η�ʽ���ӷ�ʽ�����Ҳ�·��	
			glBegin(GL_POLYGON);
			glTexCoord2f(0.0f,0.0f);//������������(��ǰ�Ҳ�·���������)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1.0f,0.0f);//������������(��ǰ�Ҳ�·������Ҳ��)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1.0f,1.0f);//������������(��һ�Ҳ�·������Ҳ��)
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(0.0f,1.0f);//������������(��һ�Ҳ�·���������)
			glVertex3f(myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,
				myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			
			glEnd();
		}		

		//9.������������
		DrawBridgeHL();

		//10.�������	
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].RemoveAll();//������������������
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].RemoveAll();//�����Ϣ�����������
		//����GetTunnelcordinate()�������¼����������
		myDesingScheme.GetTunnelcordinate(m_Tunnel.height,\
			m_Tunnel.Archeight,\
			m_Tunnel.WallHeight,\
			m_Tunnel.width/2.0,\
			m_Tunnel.ArcSegmentNumber);
		DrawTunnel(); //�������	
	
		glLineWidth(1.0);//�ָ��߿�
		glEndList();//������ʾ�б�
	
		b_haveMadeRail3DwayList=TRUE; //��ʶ�Ѿ�������ʾ�б�
	}
	else //����Ѿ�������·��άģ�͵���ʾ�б�,��ֱ�ӵ�����ʾ�б�
	{
		glCallList(m_Rail3DwayList);  //������·��άģ����ʾ�б�
	}
	glPopAttrib();//�������Զ�ջ
}

void CT3DSystemView::DrawBP(long index, int BPside)
{


	float mNCDistence=4.0;
	long i=index;

	int j;


	if(BPside==1) //�����
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_L;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L;

		if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->TW_left==0 ||\
			myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->TW_right==0)
				glColor3f(0,1,1);
		else
				glColor3f(1,0,0);
		
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				//���·��������ͬ(ͬΪ·ǵ��·��)
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f); 
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z);
					glTexCoord2f(0.0f,0.0f); 
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f); 
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f); 
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z);
					glEnd();
				}
				else  //���·��������ͬ(·ǵ,·������)
				{
					
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z);
					glEnd();
					


	
					glBegin(GL_POLYGON);
						glTexCoord2f(0.0f,0.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z);
						glTexCoord2f(0.5f,0.5f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].z);
						glTexCoord2f(0.5f,1.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z);
						glTexCoord2f(1.0f,0.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
						glEnd();
	
					

					
				}
				if(j>0) 
					{
						glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
						glBegin(GL_POLYGON);
						glTexCoord2f(0.0f,0.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
						glTexCoord2f(1.0f,0.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z);
						glTexCoord2f(1.0f,1.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z);
						glTexCoord2f(0.0f,1.0f);
						glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
						glEnd();
	
					
					}
	
			}
		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z);
					glEnd();
					
				
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z);
					glEnd();
					
				}
			

				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z);
					glEnd();
				}

			}
			
		}
		
	}
	else if(BPside==2) 
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_R;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R;
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z);
					glEnd();
					

			
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glEnd();
			

					
				}
				
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());

					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glEnd();
				}
			}
		


		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z);
					glEnd();
					
						
		
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].z);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z);
					glEnd();
	
				}
				
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z);
					glEnd();
				}
			}

		}
		
	}
	
	glLineWidth(1.0);
	glColor3f(1,1,1);

	
	

}

void CT3DSystemView::DrawBP_Ortho(long index, int BPside)
{

	float mNCDistence=4.0;
	long i=index;

	int j;


	glLineWidth(2.0);
	glColor3f(1,0,0);

	if(BPside==1) 
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_L;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L;
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f); 
			
			
			
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z));
					
					glTexCoord2f(0.0f,0.0f); 
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f); 
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f); 
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z));
					
					glEnd();
				}
				else 
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z));
					
					glEnd();
					


					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z));
					
					glTexCoord2f(0.5f,0.5f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].z));
					
					glTexCoord2f(0.5f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glEnd();


					
				}
			
	
				if(j>0) 
					{
						glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					
						
						glBegin(GL_POLYGON);
						glTexCoord2f(0.0f,0.0f);
 
 
 
						glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
							GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
						
						glTexCoord2f(1.0f,0.0f);
 
 
 
						glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x),\
							GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z));
						
						glTexCoord2f(1.0f,1.0f);
 
 
 
						glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x),\
							GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z));
						
						glTexCoord2f(0.0f,1.0f);
 
 
 
						glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
							GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
						
						glEnd();
	
					
					}
	
			}
		
			
		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z));
					
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z));
					
					glEnd();
					
				
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z));
					
					glEnd();
					
				}
			

				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z));
					
					glEnd();
				}

			}
			
		}
		
	}
	else if(BPside==2) 
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_R;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R;
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z));
					
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z));
					
					glEnd();
					

			
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].z));
					
					glTexCoord2f(1.0f,1.0f);
	
	
	
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
						
					glEnd();
			

					
				}
				
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());

					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glEnd();
				}
			}
		


		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z));
					
					glEnd();
				}
				else
				{
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z));
					
					glEnd();
					
						
		
					glBegin(GL_POLYGON);
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].z));
					
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z));
					
					glEnd();
	
				}
				
				if(j>0) 
				{
					glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
					glBegin(GL_POLYGON);
					glTexCoord2f(0.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z));
					
					glTexCoord2f(1.0f,0.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z));
					
					glTexCoord2f(1.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z));
					
					glTexCoord2f(0.0f,1.0f);
 
 
 
					glVertex2f(GetOrthoX(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x),\
						GetOrthoY(-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z));
					
					glEnd();
				}
			}

		}
		
	}
	
	glLineWidth(1.0);
	glColor3f(1,1,1);

}

void CT3DSystemView::DrawSuiGou(long index)
{
	glColor3f(1.0,0.4,1);
	glLineWidth(2.0);

 /*
 //4.�����Ҳ�ˮ����������
	/*
	��ˮ����4����ȷ��,�ֱ�Ϊ1-4�ŵ�,����0�ŵ�ΪLjToBp��,�Ѵ洢
		5____4  1____0
   (b4) \     /(b3)
		3\___/2

	����:
	�๵��� SuiGou_h,
	�๵����� SuiGou_b1,
	�๵�׿�� SuiGou_b2,
	�๵����µĿ��  SuiGou_b3
	�๵�ڱ���[����·��һ��]б�� SuiGou_m1,
	�๵�����[Զ��·��һ��]б�� SuiGou_m2,
	float SuiGou_h,SuiGou_b1,SuiGou_b2,SuiGou_b3,SuiGou_b4,SuiGou_m1,SuiGou_m2;
	SuiGou_b2=0.4;//�๵�׿��[�淶Ҫ��]
	SuiGou_h=0.6;//�๵���[�淶Ҫ��]
	SuiGou_b3=0.3;
	SuiGou_b4=0.6;//�๵����µĿ��[�淶Ҫ��:·ǵ:0.8  ·��:0.6 ,����Ϊ�˼��,ͳһȡΪ0.6]
	SuiGou_m1=SuiGou_m2=1;//��/�����б��[�淶Ҫ��]
    SuiGou_b1=SuiGou_h/SuiGou_m1+SuiGou_h/SuiGou_m2+SuiGou_b2;//�๵�����
	����ˮ���ܿ��=0.6+2*0.6+0.4+0.3=2.5
 */
 	float SGLL=2.5;//2.8;
//	float b=
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_L==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_L==TRUE)
	{
		glBegin(GL_QUAD_STRIP);
		for(int i=5;i>=0;i--)
		{

			switch(i)
			{
			case 5:
				glTexCoord2f(0.0f,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(0.0f,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;	
			case 4:
				glTexCoord2f(0.6f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(0.6f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;	
			case 3:
				glTexCoord2f(1.2f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(1.2f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;		
			case 2:
				glTexCoord2f(1.6f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(1.6f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;		
			case 1:
				glTexCoord2f(2.2f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(2.2f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;		
			case 0:
				glTexCoord2f(1.0f,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z);
				glTexCoord2f(1.0f,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z);
				break;		
			}

		}
		glEnd();
	}
	else if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_L==FALSE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_L==TRUE)
	{
		//��ǰ��û��ˮ��,����һ����ˮ��
		
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f(1.0f,0.0f); 
			glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->x1,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->y1,\
				myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->z1);
			glTexCoord2f(0.0f,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[5].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[5].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[5].z);
			glTexCoord2f(0.6f/SGLL,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[4].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[4].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[4].z);
			
			glTexCoord2f(1.2f/SGLL,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[3].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[3].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[3].z);
			glTexCoord2f(1.6f/SGLL,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[2].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[2].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[2].z);
			glTexCoord2f(2.2f/SGLL,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[1].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[1].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[1].z);
			glTexCoord2f(1.0f,1.0f); 
			glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[0].x,
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[0].y,	
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[0].z);
			
		glEnd();
	}
	else if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_L==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_L==FALSE)
	{
		//��ǰ����ˮ��,����һ��û��ˮ��
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(1.0f,1.0f); 
		glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->x1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->y1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->z1);
		glTexCoord2f(0.0f,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[5].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[5].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[5].z);
		glTexCoord2f(0.6f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[4].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[4].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[4].z);
		
		glTexCoord2f(1.2f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[3].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[3].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[3].z);
		glTexCoord2f(1.6f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[2].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[2].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[2].z);
		glTexCoord2f(2.2f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[1].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[1].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[1].z);
		glTexCoord2f(1.0f,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[0].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[0].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[0].z);
		
		glEnd();
		
		
	}
	
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_R==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_R==TRUE)
	{
		glBegin(GL_QUAD_STRIP);
		for(int i=5;i>=0;i--)
		{

			switch(i)
			{
			case 5:
				glTexCoord2f(1.0f,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(1.0f,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;	
			case 4:
				glTexCoord2f(1.9f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(1.9f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;	
			case 3:
				glTexCoord2f(1.3f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(1.3f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;		
			case 2:
				glTexCoord2f(0.9f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(0.9f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;		
			case 1:
				glTexCoord2f(0.3f/SGLL,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(0.3f/SGLL,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;		
			case 0:
				glTexCoord2f(0.0f,0.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z);
				glTexCoord2f(0.0f,1.0f); 
				glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,	
					myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z);
				break;		
			}

		}
		glEnd();
	}
	else if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_R==FALSE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_R==TRUE)
	{
		//��ǰ��û��ˮ��,����һ����ˮ��
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(0.0f,0.0f); 
		glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->x2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->y2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index)->z2);
		glTexCoord2f(1.0f,1.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[5].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[5].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[5].z);
		glTexCoord2f(1.9f/SGLL,1.0f);  
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[4].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[4].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[4].z);
		glTexCoord2f(1.3f/SGLL,1.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[3].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[3].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[3].z);
		glTexCoord2f(0.9f/SGLL,1.0f);  
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[2].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[2].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[2].z);
		glTexCoord2f(0.3f/SGLL,1.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[1].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[1].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[1].z);
		glTexCoord2f(0.0f,1.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[0].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[0].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[0].z);
		
		glEnd();
	}
	else if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_R==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_R==FALSE)
	{
		//��ǰ����ˮ��,����һ��û��ˮ��
		
		glBegin(GL_TRIANGLE_FAN);
		glTexCoord2f(1.0f,1.0f); 
		glVertex3f(myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->x2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->y2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(index+1)->z2);
		glTexCoord2f(1.0f,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[5].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[5].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[5].z);
		glTexCoord2f(1.9f/SGLL,0.0f);  
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[4].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[4].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[4].z);
		glTexCoord2f(1.3f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[3].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[3].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[3].z);
		glTexCoord2f(0.9f/SGLL,0.0f);  
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[2].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[2].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[2].z);
		glTexCoord2f(0.3f/SGLL,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[1].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[1].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[1].z);
		glTexCoord2f(0.0f,0.0f); 
		glVertex3f(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[0].x,
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[0].y,	
			myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[0].z);
		
		glEnd();
	}
	

	glLineWidth(1.0);
	glColor3f(1,1,1);
	
}

void CT3DSystemView::DrawSuiGou_Ortho(long index)
{
	glColor3f(1.0,0.4,1);
	glLineWidth(2.0);

	
	float SGLL=2.8;
	
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_L==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_L==TRUE)
	{
		glBegin(GL_QUAD_STRIP);
		for(int i=5;i>=0;i--)
		{
			switch(i)
			{
			case 5:
				glTexCoord2f(0.0f,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));

				glTexCoord2f(0.0f,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;	
			case 4:
				glTexCoord2f(0.5f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));
				
				glTexCoord2f(0.5f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;	
			case 3:
				glTexCoord2f(1.3f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));
				
				glTexCoord2f(1.3f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;		
			case 2:
				glTexCoord2f(1.7f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));
				
				glTexCoord2f(1.7f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;		
			case 1:
				glTexCoord2f(2.5f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));
				
				glTexCoord2f(2.5f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;		
			case 0:
				glTexCoord2f(1.0f,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z));
				
				glTexCoord2f(1.0f,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z));
				
				break;		
			}

		}
		glEnd();
	}
	
	
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_R==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_R==TRUE)
	{

		glBegin(GL_QUAD_STRIP);
		for(int i=5;i>=0;i--)
		{

			switch(i)
			{
			case 5:
				glTexCoord2f(0.0f,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(0.0f,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;	
			case 4:
				glTexCoord2f(0.5f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(0.5f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;	
			case 3:
				glTexCoord2f(1.3f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(1.3f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;		
			case 2:
				glTexCoord2f(1.7f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(1.7f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;		
			case 1:
				glTexCoord2f(2.5f/SGLL,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(2.5f/SGLL,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;		
			case 0:
				glTexCoord2f(1.0f,0.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z));
				
				glTexCoord2f(1.0f,1.0f); 
 
 
 
				glVertex2f(GetOrthoX(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x),\
					GetOrthoY(-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z));
				
				break;		
			}

		}
		glEnd();
	}

	glLineWidth(1.0);
	glColor3f(1,1,1);
}

//���������·�������
void CT3DSystemView::DrawQDHP(long Index, CString mCurrentPtstyle, float mHPangle, CString mNextPtstyle, int mBridgeIndex)
{
	//	���������ֱ������,����Ҫ���ƻ���)
	if(mNextPtstyle=="������")
		return;
	//	������ƻ�����ĵ�

	//	���:���µ�HuPo_L+PtS_RailwayLj3D����(x1,y1,z1)
	//	�Ҳ�:PtS_RailwayLj3D����(x2,y2,z2)+���µ�HuPo_R
			
	//�������������(mCurrentPtstyle="�������")����
	//�����յ�(mCurrentPtstyle="�����յ�")���ֱ���л���,��
	//�߻�����ķ������෴��
	double x1,y1,z1,x2,y2,z2;
	double tx,ty,tz;
	
	PCordinate pt;
	
	int i;
	double ax,ay,az;
	int N1,N2;

	
	N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->Huponums_L-1;//��������
	N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->Huponums_R-1;//�Ҳ������

	if(N1<0 || N2<0)
		return;

	x1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[N1].Hp[2].x;
	y1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[N1].Hp[2].y;
	z1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[N1].Hp[2].z;
	x2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[N2].Hp[2].x;
	y2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[N2].Hp[2].y,
	z2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[N2].Hp[2].z;
	
		
	float dx=x2-x1;
	float dz=z2-z1;
	float mangle;
	
	if(mCurrentPtstyle=="�������")
	{
		if(fabs(dx)<=0.000001) 
		{
			mangle=0;
		}  
		else 
		{
			mangle=atan(fabs(dz/dx));
			if(dx>=0 && dz<=0)  //1����
			{
				mangle=PAI/2+mangle;
			}
			else if(dx<=0 && dz<=0) //2���� 
			{
				mangle=PAI*3.0/2-mangle;
			}
			else if(dx<=0 && dz>=0) //3����
			{
				mangle=2*PAI-mangle;
			}
			else if(dx>=0 && dz>=0) //4����
			{
				mangle=PAI/2-mangle;
			}
			
		}
	}
	else if(mCurrentPtstyle=="�����յ�")
	{
		if(fabs(dx)<=0.000001) 
		{
			mangle=PAI*3.0/2;
		}  
		else 
		{
			mangle=atan(fabs(dz/dx));
			if(dx>=0 && dz<=0)  //1����
			{
				mangle=2*PAI-mangle;
			}
			else if(dx<=0 && dz<=0) //2���� 
			{
				mangle=PAI/2-mangle;
			}
			else if(dx<=0 && dz>=0) //3����
			{
				mangle=PAI/2+mangle;
			}
			else if(dx>=0 && dz>=0) //4����
			{
				mangle=PAI*3.0/2-mangle;
			}
			
		}
	}
	
		//	(1)//������㻤����
		PtBridgeHPUp.RemoveAll();
		PtBridgeHPDown.RemoveAll();
	
		//������ð�����������Ƕ������Ľ���
		//(1)��໤�µ�
		for(i=N1;i>=0;i--)
		{
			for(int j=2;j>=0;j--)
			{
				tx=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[i].Hp[j].x;
				ty=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[i].Hp[j].y;
				tz=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_L[i].Hp[j].z;
				myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
				pt=new Cordinate;
				pt->x=ax;pt->y=ay;pt->z=az;
				PtBridgeHPDown.Add(pt);
				pt=new Cordinate;
				pt->x=tx;pt->y=ty;pt->z=tz;
				PtBridgeHPUp.Add(pt); //���뻤����
			}
		}
	
		//(2) ���·��TO���µ�
		tx=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->x1;
		ty=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->y1;
		tz=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->z1;
		myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
		pt=new Cordinate;
		pt->x=ax;pt->y=ay;pt->z=az;
		PtBridgeHPDown.Add(pt);
		pt=new Cordinate;
		pt->x=tx;pt->y=ty;pt->z=tz;
		PtBridgeHPUp.Add(pt);
		
		//(3) ���·���
		tx=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->x1;
		ty=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->y1;
		tz=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->z1;
		myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
		pt=new Cordinate;
		pt->x=ax;pt->y=ay;pt->z=az;
		PtBridgeHPDown.Add(pt);
		pt=new Cordinate;
		pt->x=tx;pt->y=ty;pt->z=tz;
		PtBridgeHPUp.Add(pt);
		
		//(4) ������
		tx=myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(Index)->x1;
		ty=myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(Index)->y1;
		tz=myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(Index)->z1;
		myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
		pt=new Cordinate;
		pt->x=ax;pt->y=ay;pt->z=az;
		PtBridgeHPDown.Add(pt);
		pt=new Cordinate;
		pt->x=tx;pt->y=ty;pt->z=tz;
		PtBridgeHPUp.Add(pt);
		
		//(5) �Ҳ�·���
			tx=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->x2;
			ty=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->y2;
			tz=myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(Index)->z2;
			myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
			pt=new Cordinate;
			pt->x=ax;pt->y=ay;pt->z=az;
			PtBridgeHPDown.Add(pt);
			pt=new Cordinate;
			pt->x=tx;pt->y=ty;pt->z=tz;
			PtBridgeHPUp.Add(pt);
			
		//(6) �Ҳ�·��TO���µ�
			tx=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->x2;
			ty=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->y2;
			tz=myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(Index)->z2;
			myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
			pt=new Cordinate;
			pt->x=ax;pt->y=ay;pt->z=az;
			PtBridgeHPDown.Add(pt);
			pt=new Cordinate;
			pt->x=tx;pt->y=ty;pt->z=tz;
			PtBridgeHPUp.Add(pt);
			
		
			//(7)�Ҳ໤�µ�
			for(i=0;i<=N2;i++)
			{
				for(int j=0;j<=2;j++)
				{
					
					tx=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[i].Hp[j].x;
					ty=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[i].Hp[j].y;
					tz=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(Index)->HuPo_R[i].Hp[j].z;
					myDesingScheme.GetHpD(tx,ty,tz,mangle,mHPangle,&ax,&ay,&az);
					pt=new Cordinate;
					pt->x=ax;pt->y=ay;pt->z=az;
					PtBridgeHPDown.Add(pt);
					pt=new Cordinate;
					pt->x=tx;pt->y=ty;pt->z=tz;
					PtBridgeHPUp.Add(pt);
				}
			}
	
		glLineWidth(4.0);
		glColor3f(1,0,1);

	//��¼�������������潻��
	if(mCurrentPtstyle=="�������")
	{
		myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeIndex)->m_ReginPt_Start.RemoveAll();
		for(int j=0;j<PtBridgeHPDown.GetSize();j++)
		{
			pt=new Cordinate;
			pt->x=PtBridgeHPDown.GetAt(j)->x;
			pt->y=PtBridgeHPDown.GetAt(j)->y;
			pt->z=PtBridgeHPDown.GetAt(j)->z;
			myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeIndex)->m_ReginPt_Start.Add(pt);
		}
	}
	else if(mCurrentPtstyle=="�����յ�")
	{
		myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeIndex)->m_ReginPt_End.RemoveAll();
		for(int j=0;j<PtBridgeHPDown.GetSize();j++)
		{
			pt=new Cordinate;
			pt->x=PtBridgeHPDown.GetAt(j)->x;
			pt->y=PtBridgeHPDown.GetAt(j)->y;
			pt->z=PtBridgeHPDown.GetAt(j)->z;
			myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeIndex)->m_ReginPt_End.Add(pt);
		}
	}
	



		double mMin_X,mMin_Y,mMax_X,mMax_Y,Lx,Ly;
		GetMinMaxXY_bridgeHPm(&mMin_X,&mMin_Y,&mMax_X,&mMax_Y);
		Lx=mMax_X-mMin_X;
		Ly=mMax_Y-mMin_Y;

		glBindTexture(GL_TEXTURE_2D, m_cBridgeHpm.GetTxtID());
		glBegin(GL_TRIANGLE_STRIP);
		for(i=0;i<PtBridgeHPDown.GetSize();i++)
		{
			glTexCoord2f((PtBridgeHPUp.GetAt(i)->x-mMin_X)/Lx,(PtBridgeHPUp.GetAt(i)->y-mMin_Y)/Ly);
			glVertex3f(PtBridgeHPUp.GetAt(i)->x,PtBridgeHPUp.GetAt(i)->y,PtBridgeHPUp.GetAt(i)->z);
			glTexCoord2f((PtBridgeHPDown.GetAt(i)->x-mMin_X)/Lx,(PtBridgeHPDown.GetAt(i)->y-mMin_Y)/Ly);
			glVertex3f(PtBridgeHPDown.GetAt(i)->x,PtBridgeHPDown.GetAt(i)->y,PtBridgeHPDown.GetAt(i)->z);
		}
		glEnd();


		
		glColor3f(1,1,1);
		glLineWidth(0);
		

}

//�����Ŷ�
void CT3DSystemView::DrawSceneQD(double x1, double y1, double z1, double x2, double y2, double z2, float QDheight)
{
	//�Ŷ�Ӧ���еĿ��
	float Xwidth=m_Railway.m_Railway_width+2*m_Railway.m_Lj_width+2*m_Railway.m_GuiMianToLujianWidth;
	float mangle=myDesingScheme.GetANgle(x1,z1,x2,z2); //�����Ŷ�ģ��Ӧ��ת�ĽǶ�(ʹ֮����·��ֱ)
	if(mangle>180)
		mangle=mangle-180;
	
	float xscale=Xwidth/(m_QD_maxx-m_QD_minx); //�����Ŷ�ģ����X�����ϵ����ű���(���)
	float yscale=QDheight/(m_QD_maxy-m_QD_miny);//�����Ŷ�ģ����Y�����ϵ����ű���(�߶�)
	
	glPushMatrix(); //ѹ���ջ
	glScalef(xscale,yscale,1); //�Ŷ�����
	glTranslatef(((x1+x2)/2-(m_QD_maxx+m_QD_minx)/2)/xscale,y2/yscale-m_QD_maxy,(z1+z2)/2); //ƽ��
	glRotatef(mangle,0,1,0); //��ת
	glCallList(m_QDList); //�����Ŷ���ʾ�б�����Ŷ�
	glPopMatrix(); //������ջ
	
}


//�������
void CT3DSystemView::DrawTunnel()
{
//	m_Tunnel.H;//���Բ�����������ϵĸ߶�
//	m_Tunnel.L;//������Ŷ���������������Ŀ�� 
		
	glColor3f(1,1,1);
	glLineWidth(2.0);
	int index=0;
	
	long m_StartIndex,m_EndIndex;//�洢��ǰ������������������������������������
	m_StartIndex=-1;
	
	//�����������������(���֮����x=y=-1Ϊ�ָ�,)
	//����ʾ������˵��,��ʾ����2�����
	/*
	12345,67,89
	12345,67,89
	12345,67,89
	.....
	12345,67,89
	-1,-1,-1
	12345,67,89
	12345,67,89
	12345,67,89
	.....
	12345,67,89
	-1,-1,-1
	*/
	//
	for (long i=0;i<myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetSize();i++)
	{
		if(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->x1!=-1 && \
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->y1!=-1)
		{
			if(m_StartIndex<0)
				m_StartIndex=i; //��ǰ�����ʼ���������������������������
		}
		else
		{
			m_EndIndex=i-1;//��ǰ�����ֹ���������������������������(m_EndIndex-m_StartIndexȷ���˵�ǰ����ɶ��ٸ���������)
			DrawTunnelEach(m_StartIndex,m_EndIndex,index,m_Tunnel.H,m_Tunnel.L); //�������(index:��ʾ����������������������,�������������·�еڼ������
			index++; //�����������+1
			m_StartIndex=-1;//�ָ�Ϊ-1
		}
	}
	
}

void CT3DSystemView::GetMinMaxXY_bridgeHPm(double *minx, double *miny, double *maxx, double *maxy)
{
	*minx=PtBridgeHPDown.GetAt(0)->x;
	*miny=PtBridgeHPDown.GetAt(0)->y;
	*maxx=PtBridgeHPUp.GetAt(0)->x;
	*maxy=PtBridgeHPUp.GetAt(0)->y;
	
	for(int i=0;i<PtBridgeHPDown.GetSize();i++)
	{
		if(*minx>PtBridgeHPDown.GetAt(i)->x) *minx=PtBridgeHPDown.GetAt(i)->x;
		if(*miny>PtBridgeHPDown.GetAt(i)->y) *miny=PtBridgeHPDown.GetAt(i)->y;
		if(*maxx<PtBridgeHPDown.GetAt(i)->x) *maxx=PtBridgeHPDown.GetAt(i)->x;
		if(*maxy<PtBridgeHPDown.GetAt(i)->y) *maxy=PtBridgeHPDown.GetAt(i)->y;
	}
	
	for(i=0;i<PtBridgeHPUp.GetSize();i++)
	{
		if(*minx>PtBridgeHPUp.GetAt(i)->x) *minx=PtBridgeHPUp.GetAt(i)->x;
		if(*miny>PtBridgeHPUp.GetAt(i)->y) *miny=PtBridgeHPUp.GetAt(i)->y;
		if(*maxx<PtBridgeHPUp.GetAt(i)->x) *maxx=PtBridgeHPUp.GetAt(i)->x;
		if(*maxy<PtBridgeHPUp.GetAt(i)->y) *maxy=PtBridgeHPUp.GetAt(i)->y;
	}
	
}

//�������
/*����˵��:
mStartindex:��ǰ�����ʼ�����������������������ݵ�������
mEndIndex://��ǰ�����ֹ�����������������������ݵ�������
mTunnelIndex:��ʾ����������������������,�������������·�еڼ������(���蹲4�����,��mTunnelIndex=0,1,2,3)
H:���Բ�����������ϵĸ߶�
L:������Ŷ���������������Ŀ�� 
*/
void CT3DSystemView::DrawTunnelEach(long mStartindex, long mEndIndex, int mTunnelIndex, float H, float L)
{
	double minx,miny,Lx,Ly;
	
	//(1)����������ڶ���
	glBindTexture(GL_TEXTURE_2D, m_cTunnel_dm.GetTxtID()); //��������ڶ�������
	DrawTunnelDM(
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->x1,\
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->y1,\
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->z1,\
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->x2,\
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->y2,\
		myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mEndIndex)->z2,\
		H,L,mEndIndex,mTunnelIndex,FALSE,\
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelIndex)->mEndAngle\
		);
	
	/*	����������ڶ�������������ǽ���¶�����(x,y1,z1),(x2,y2,z2)	*/

	//(2)��������ڲ�
	glBindTexture(GL_TEXTURE_2D, m_cTunnel.GetTxtID());//������ڲ�����
	for ( long i=mStartindex;i<mEndIndex;i++)
	{
	//	glBindTexture(GL_TEXTURE_2D, m_cTunnel.GetTxtID());//������ڲ�����
		
			//�����ǽ
			glBegin(GL_POLYGON ); 
				glTexCoord2f(0,0);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->y1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glTexCoord2f(0,1);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->y1+m_Tunnel.WallHeight,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glTexCoord2f(1,1);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->y1+m_Tunnel.WallHeight,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
				glTexCoord2f(1,0);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
			glEnd();

			//�Ҳ���ǽ
			glBegin(GL_POLYGON ); 
			glTexCoord2f(1,0);
			glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->y2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(1,1);
			glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->x2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->y2+m_Tunnel.WallHeight,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->z2);
			glTexCoord2f(0,1);
			glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->y2+m_Tunnel.WallHeight,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glTexCoord2f(0,0);
			glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
				myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
			glEnd();

			
	//		glBindTexture(GL_TEXTURE_2D, m_cTunnel.GetTxtID());
			//����Բ��
			int mNums=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetSize();

			minx=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(mNums-1)->x;
			miny=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(mNums-1)->z;
			Lx=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(0)->x-minx;
			Ly=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(0)->z-miny;
			
			//��������������Ķ���Բ��,����������η�ʽ����(GL_QUAD_STRIP)
			glColor3f(1,0,0);
			glBegin(GL_QUAD_STRIP );
				glTexCoord2f(0,0);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(0)->x,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(0)->y,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(0)->z);
				
				glTexCoord2f(0,1);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(0)->x,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(0)->y,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(0)->z);
				
				glTexCoord2f(1.0/m_Tunnel.ArcSegmentNumber,0);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(1)->x,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(1)->y,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(1)->z);
			
				glTexCoord2f(1.0/m_Tunnel.ArcSegmentNumber,1);
				glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(1)->x,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(1)->y,\
					myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(1)->z);
				
			
				for(int n=2;n<myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetSize();n++)
				{
					
					glTexCoord2f(n*1.0/m_Tunnel.ArcSegmentNumber,0);
					glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(n)->x,\
						myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(n)->y,\
						myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i)->tunnelArc.GetAt(n)->z);
					
					glTexCoord2f(n*1.0/m_Tunnel.ArcSegmentNumber,1);
					glVertex3f(myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(n)->x,\
						myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(n)->y,\
						myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(i+1)->tunnelArc.GetAt(n)->z);
					
				}
			
			glEnd();

			glColor3f(1,1,1);
			
		}
		
		//������������ڶ���
		glBindTexture(GL_TEXTURE_2D, m_cTunnel_dm.GetTxtID());//��������ڶ�������
		DrawTunnelDM(
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->x1,\
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->y1,\
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->z1,\
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->x2,\
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->y2,\
			myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(mStartindex)->z2,\
			H,L,mStartindex,mTunnelIndex,TRUE,\
			myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelIndex)->mStartangle\
			);
}

//�����������
/*
����˵��:
x1,y1,z1:���������������ǽ���¶�����
x2,y2,z2:���������������ǽ���¶�����
H;���Բ�����������ϵĸ߶�
L:������Ŷ���������������Ŀ��
index:������ŵ��������������������������������
tunnelIndex;����������������������,�������������·�еڼ������
bstartDM:��ʾ��������ڶ���(bstartDM=TRUE)����������ڶ���((bstartDM=FALSE)
mangle:���ŵ�����Ƕ�
  */
void CT3DSystemView::DrawTunnelDM(double x1, double y1, double z1, double x2, double y2, double z2, float H, float L, int index, int tunnelIndex, BOOL bstartDM, float mangle)
{
//�����ݵ�����P6(x1,y1,z1),P5(x2,y2,z2)
//H:��Բ���������ϵĸ߶�(Ҳ����Ҫ��Բ�������ټ�һ���ĸ߶�,��Ϊ���ŵ��ܸ߶�)
//L:����ǽ���Ϸ���,������չ�ľ���,���ɶ�ǽʽ���Žṹ
//��GL_TRIANGLE���ơ�P1p2p6  ��P3p4p5 
//P2P3���Ϊ m_Tunnel.ArcSegmentNumber������,��Բ�������Ӧ,��GL_TRIANGLE_STRIP����
/*
�������ʾ��ͼͼ(��ǽʽ����)
	P1   L   P2          P3   L   P4
	--------- |-----------|----------
	 \        |      h_   |        /
	  \       |           |       /   
	   \      |  Բ������ |      /
	    \     |           |     /
		 \    |           |    /
		  \   |           |   /
		   \  |           |  /
	     P7_\_|_P6______P5|_/P8
*/


	double P1[3],P2[3],P3[3],P4[3],P5[3],P6[3],P7[3],P8[3];
	double A1[3],A2[3],A3[3],A4[3],A5[3],A6[3];
	double Lx,Ly,minx,miny,maxx,maxy;
	

	P6[0]=x1;P6[1]=y1;P6[2]=z1;
	P5[0]=x2;P5[1]=y2;P5[2]=z2;
	
	long mIn;
	if(bstartDM==TRUE)//���Ž���
		mIn=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->startIndex-1;//����ֵ
	else
		mIn=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->endIndex-1;//����ֵ

	P7[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[1].x;
	P7[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[1].y;
	P7[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[1].z;

	P8[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[1].x;
	P8[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[1].y;
	P8[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[1].z;
	
		
	//(1)���P2,P3���� P2,P3�����=m_Tunnel.width
	P2[0]=x1;P2[1]=y1+m_Tunnel.height+H;P2[2]=z1;
	P3[0]=x2;P3[1]=y2+m_Tunnel.height+H;P3[2]=z2;
	
	//(2)���P1,P4����
	P1[0]=P2[0]-L*cos(mangle);P1[1]=P2[1];P1[2]=P2[2]+L*sin(mangle);
	P4[0]=P3[0]+L*cos(mangle);P4[1]=P3[1];P4[2]=P3[2]-L*sin(mangle);
		
	
	//////////////////////////////////////////////////////////////////////////
	//�Ŷ�Ӧ���еĿ��
	float Xwidth=fabs(P4[0]-P1[0]);
	float Yheight=fabs(P3[1]-P5[1]);
	mangle=myDesingScheme.GetANgle(x1,z1,x2,z2); //�����������ģ��Ӧ��ת�ĽǶ�(ʹ֮����·��ֱ)
	
	float xscale=Xwidth/(m_TunnelDM_maxx-m_TunnelDM_minx); //�����������ģ����X�����ϵ����ű���(���)
	float yscale=Yheight/(m_TunnelDM_maxy-m_TunnelDM_miny);//�����������ģ����Y�����ϵ����ű���(�߶�)
	glPushMatrix(); //ѹ���ջ
	glScalef(xscale,yscale,1); //�����������
	glTranslatef(((x1+x2)/2-(m_TunnelDM_maxx+m_TunnelDM_minx)/2)/xscale,((y1+y2)/2-(m_TunnelDM_maxy+m_TunnelDM_miny)/2)/yscale,(z1+z2)/2); //ƽ��
	glRotatef(mangle,0,1,0); //��ת
	glCallList(m_TunnelDMList); //�������������ʾ�б�����Ŷ�
	glPopMatrix(); //������ջ
	
	//////////////////////////////////////////////////////////////////////////
	
//	return;

	

	PCordinate pt;

	if(bstartDM==TRUE)//���Ž���
	{
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.RemoveAll();
		
		//����������Ž��ڸ�������
		pt=new Cordinate;
		pt->x =P1[0];	pt->y =P1[1];	pt->z =P1[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.Add(pt);
	
		pt=new Cordinate;
		pt->x =P2[0];	pt->y =P2[1];	pt->z =P2[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.Add(pt);
	
		pt=new Cordinate;
		pt->x =P3[0];	pt->y =P3[1];	pt->z =P3[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.Add(pt);
		
		pt=new Cordinate;
		pt->x =P4[0];	pt->y =P4[1];	pt->z =P4[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_Start.Add(pt);
		
	}
	else
	{
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_End.RemoveAll();
		
		//����������ų��ڸ�������
		pt=new Cordinate;
		pt->x =P1[0];	pt->y =P1[1];	pt->z =P1[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_End.Add(pt);
		
		pt=new Cordinate;
		pt->x =P2[0];	pt->y =P2[1];	pt->z =P2[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_End.Add(pt);
		
		pt=new Cordinate;
		pt->x =P3[0];	pt->y =P3[1];	pt->z =P3[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_End.Add(pt);
		
		pt=new Cordinate;
		pt->x =P4[0];	pt->y =P4[1];	pt->z =P4[2];
		myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(tunnelIndex)->m_ReginPt_End.Add(pt);
	}


		float m_L=0.8;//
		A1[0]=P1[0]-m_L*sin(mangle);A1[1]=P1[1];A1[2]=P1[2]-m_L*cos(mangle);
		A2[0]=P2[0]-m_L*sin(mangle);A2[1]=P2[1];A2[2]=P2[2]-m_L*cos(mangle);
		A3[0]=P3[0]-m_L*sin(mangle);A3[1]=P3[1];A3[2]=P3[2]-m_L*cos(mangle);
		A4[0]=P4[0]-m_L*sin(mangle);A4[1]=P4[1];A4[2]=P4[2]-m_L*cos(mangle);
		
		
		if(bstartDM==TRUE)//�����������ڶ���
		{
			Lx=P4[0]-P1[0];
			Ly=P1[1]-P7[1];
			minx=P1[0];
			miny=P7[1];
		}
		else  //�����������ڶ���
		{
			Lx=P1[0]-P4[0];
			Ly=P1[1]-P7[1];
			minx=P4[0];
			miny=P7[1];
		}

			glLineWidth(3.0);  //�����߿�

			glColor3f(1,0,1); //������ɫ
			glBegin(GL_TRIANGLE_STRIP); //���������߷�ʽ����
			glVertex3dv(A1);
			glVertex3dv(P1);
			glVertex3dv(A2);
			glVertex3dv(P2);
			glVertex3dv(A3);
			glVertex3dv(P3);
			glVertex3dv(A4);
			glVertex3dv(P4);
			glEnd();


			glColor3f(0.4,0.2,1);
			glBegin(GL_TRIANGLES); //���������λ���(p1P2P7)
				glTexCoord2f((P1[0]-minx)/Lx,1);
				glVertex3dv(P1);
				glTexCoord2f((P2[0]-minx)/Lx,1);
				glVertex3dv(P2);
				glTexCoord2f((P7[0]-minx)/Lx,0);
				glVertex3dv(P7);
			glEnd();

			glBegin(GL_TRIANGLES);//���������λ���(p2P7P6)
				glTexCoord2f((P2[0]-minx)/Lx,1);
				glVertex3dv(P2);
				glTexCoord2f((P7[0]-minx)/Lx,0);
				glVertex3dv(P7);
				glTexCoord2f((P6[0]-minx)/Lx,0);
				glVertex3dv(P6);
			glEnd();

			glBegin(GL_TRIANGLES);//���������λ���(p3P5P8)
				glTexCoord2f((P3[0]-minx)/Lx,1);
				glVertex3dv(P3);
				glTexCoord2f((P5[0]-minx)/Lx,0);
				glVertex3dv(P5);
				glTexCoord2f((P8[0]-minx)/Lx,0);
				glVertex3dv(P8);
			glEnd();

			glBegin(GL_TRIANGLES);//���������λ���(p3P8P4)
			glTexCoord2f((P3[0]-minx)/Lx,1);
			glVertex3dv(P3);
			glTexCoord2f((P8[0]-minx)/Lx,0);
			glVertex3dv(P8);
			glTexCoord2f((P4[0]-minx)/Lx,1);
			glVertex3dv(P4);
			glEnd();
			
			
			//���ƶ���Բ��
			int mNums=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(index)->tunnelArc.GetSize();
			double tx,ty,tz;
			double rx,ry,rz;
			glBegin(GL_TRIANGLE_STRIP);
			for(int i=0;i<mNums;i++)
			{
				tx=P3[0]+i*(P2[0]-P3[0])/(mNums-1);
				ty=P3[1];
				tz=P3[2]+i*(P2[2]-P3[2])/(mNums-1);
				glTexCoord2f((tx-minx)/Lx,(ty-miny)/Ly);
				glVertex3f(tx,ty,tz);
				rx=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(index)->tunnelArc.GetAt(i)->x;
				ry=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(index)->tunnelArc.GetAt(i)->y;
				rz=myDesingScheme.PtS_Tunnel3D[m_currentSchemeIndexs].GetAt(index)->tunnelArc.GetAt(i)->z;
				glTexCoord2f((rx-minx)/Lx,(ry-miny)/Ly);
				glVertex3f(rx,ry,rz);
			}
		glEnd();
		
//-----------��ն�����·���߽紦
		//���ƶ���
		if(bstartDM==TRUE)//���Ž���
		{
			glBindTexture(GL_TEXTURE_2D, m_cTunnel_dmwcBp.GetTxtID());
			//(1)���
			if(mIn>=1)
			{
				A1[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[2].x;
				A1[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[2].y;
				A1[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[2].z;
				
				A2[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[1].x;
				A2[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[1].y;
				A2[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_L[0].Hp[1].z;
				
				A3[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].x;
				A3[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].y;
				A3[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].z;
				
				A4[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].x;
				A4[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].y;
				A4[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].z;
			
				A5[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].x;
				A5[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].y;
				A5[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].z;
			
				A6[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].x;
				A6[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].y;
				A6[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].z;
				
				//�� minx,maxx,miny,maxy;
				
				minx=miny=999999999;
				maxx=maxy=-999999999;
				if(minx>A1[0]) minx=A1[0];
				if(maxx<A1[0]) maxx=A1[0];
				if(miny>A1[1]) miny=A1[1];
				if(maxy<A1[1]) maxy=A1[1];
				
				if(minx>A2[0]) minx=A2[0];
				if(maxx<A2[0]) maxx=A2[0];
				if(miny>A2[1]) miny=A2[1];
				if(maxy<A2[1]) maxy=A2[1];
				
				if(minx>A3[0]) minx=A3[0];
				if(maxx<A3[0]) maxx=A3[0];
				if(miny>A3[1]) miny=A3[1];
				if(maxy<A3[1]) maxy=A3[1];
				
				if(minx>A4[0]) minx=A4[0];
				if(maxx<A4[0]) maxx=A4[0];
				if(miny>A4[1]) miny=A4[1];
				if(maxy<A4[1]) maxy=A4[1];
			
				if(minx>A5[0]) minx=A5[0];
				if(maxx<A5[0]) maxx=A5[0];
				if(miny>A5[1]) miny=A5[1];
				if(maxy<A5[1]) maxy=A5[1];
				
				if(minx>A6[0]) minx=A6[0];
				if(maxx<A6[0]) maxx=A6[0];
				if(miny>A6[1]) miny=A6[1];
				if(maxy<A6[1]) maxy=A6[1];
				
				if(minx>P1[0]) minx=P1[0];
				if(maxx<P1[0]) maxx=P1[0];
				if(miny>P1[1]) miny=P1[1];
				if(maxy<P1[1]) maxy=P1[1];
				
				if(minx>P7[0]) minx=P7[0];
				if(maxx<P7[0]) maxx=P7[0];
				if(miny>P7[1]) miny=P7[1];
				if(maxy<P7[1]) maxy=P7[1];
				
		
				
				float L1,L2;
				L1=myDesingScheme.GetDistenceXYZ(A1[0],A1[1],A1[2],P1[0],P1[1],P1[2]);
				L2=myDesingScheme.GetDistenceXYZ(A2[0],A2[1],A2[2],A3[0],A3[1],A3[2]);

				int bsign;
				if(A2[2]>=A3[2])
					bsign=-1;
				else
					bsign=1;
		
				minx=A1[0]+bsign*L1;
				maxx=P7[0];
			
				Lx=maxx-minx;
				Ly=maxy-miny;
				
				glColor3f(1,1,0);
				glBegin(GL_TRIANGLE_FAN);
					glTexCoord2f((P1[0]-minx)/Lx,(P1[1]-miny)/Ly);
					glVertex3dv(P1);
					glTexCoord2f((A1[0]-minx+bsign*L1)/Lx,(A1[1]-miny)/Ly);
					glVertex3dv(A1);
					glTexCoord2f((A2[0]-minx+bsign*L2)/Lx,(A2[1]-miny)/Ly);
					glVertex3dv(A2);
					glTexCoord2f((A3[0]-minx)/Lx,(A3[1]-miny)/Ly);
					glVertex3dv(A3);
					glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
					glVertex3dv(A4);
					glTexCoord2f((P7[0]-minx)/Lx,(P7[1]-miny)/Ly);
					glVertex3dv(P7);
				glEnd();
				
					
				glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f((P7[0]-minx)/Lx,(P7[1]-miny)/Ly);
				glVertex3dv(P7);
				glTexCoord2f((A6[0]-minx)/Lx,(A6[1]-miny)/Ly);
				glVertex3dv(A6);
				glTexCoord2f((A5[0]-minx)/Lx,(A5[1]-miny)/Ly);
				glVertex3dv(A5);
				glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
				glVertex3dv(A4);
				glEnd();
			

			//(2)�Ҳ�
			A1[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[2].x;
			A1[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[2].y;
			A1[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[2].z;
			
			A2[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[1].x;
			A2[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[1].y;
			A2[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn-1)->HuPo_R[0].Hp[1].z;
			
			A3[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].x;
			A3[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].y;
			A3[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].z;
			
			A4[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].x;
			A4[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].y;
			A4[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].z;
			
			A5[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].x;
			A5[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].y;
			A5[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].z;
			
			A6[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].x;
			A6[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].y;
			A6[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].z;
			
			//�� minx,maxx,miny,maxy;
			
			minx=miny=999999999;
			maxx=maxy=-999999999;
			if(minx>A1[0]) minx=A1[0];
			if(maxx<A1[0]) maxx=A1[0];
			if(miny>A1[1]) miny=A1[1];
			if(maxy<A1[1]) maxy=A1[1];
			
			if(minx>A2[0]) minx=A2[0];
			if(maxx<A2[0]) maxx=A2[0];
			if(miny>A2[1]) miny=A2[1];
			if(maxy<A2[1]) maxy=A2[1];
			
			if(minx>A3[0]) minx=A3[0];
			if(maxx<A3[0]) maxx=A3[0];
			if(miny>A3[1]) miny=A3[1];
			if(maxy<A3[1]) maxy=A3[1];
			
			if(minx>A4[0]) minx=A4[0];
			if(maxx<A4[0]) maxx=A4[0];
			if(miny>A4[1]) miny=A4[1];
			if(maxy<A4[1]) maxy=A4[1];
			
			if(minx>A5[0]) minx=A5[0];
			if(maxx<A5[0]) maxx=A5[0];
			if(miny>A5[1]) miny=A5[1];
			if(maxy<A5[1]) maxy=A5[1];
			
			if(minx>A6[0]) minx=A6[0];
			if(maxx<A6[0]) maxx=A6[0];
			if(miny>A6[1]) miny=A6[1];
			if(maxy<A6[1]) maxy=A6[1];
			
			if(minx>P4[0]) minx=P4[0];
			if(maxx<P4[0]) maxx=P4[0];
			if(miny>P4[1]) miny=P4[1];
			if(maxy<P4[1]) maxy=P4[1];
			
			if(minx>P8[0]) minx=P8[0];
			if(maxx<P8[0]) maxx=P8[0];
			if(miny>P8[1]) miny=P8[1];
			if(maxy<P8[1]) maxy=P8[1];
			
		//	
			L1=myDesingScheme.GetDistenceXYZ(A1[0],A1[1],A1[2],P1[0],P1[1],P1[2]);
			L2=myDesingScheme.GetDistenceXYZ(A2[0],A2[1],A2[2],A3[0],A3[1],A3[2]);
			
			
			if(A2[2]>=A3[2])
				bsign=1;
			else
				bsign=-1;
			
			maxx=A1[0]+bsign*L1;
			minx=P8[0];
			
			Lx=maxx-minx;
			Ly=maxy-miny;
			
			
			glColor3f(1,1,0);
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f((P4[0]-minx)/Lx,(P4[1]-miny)/Ly);
			glVertex3dv(P4);
			glTexCoord2f((A1[0]-minx+bsign*L1)/Lx,(A1[1]-miny)/Ly);
			glVertex3dv(A1);
			glTexCoord2f((A2[0]-minx+bsign*L2)/Lx,(A2[1]-miny)/Ly);
			glVertex3dv(A2);
			glTexCoord2f((A3[0]-minx)/Lx,(A3[1]-miny)/Ly);
			glVertex3dv(A3);
			glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
			glVertex3dv(A4);
			glTexCoord2f((P8[0]-minx)/Lx,(P8[1]-miny)/Ly);
			glVertex3dv(P8);
			glEnd();
			
			
			
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f((P8[0]-minx)/Lx,(P8[1]-miny)/Ly);
			glVertex3dv(P8);
			glTexCoord2f((A6[0]-minx)/Lx,(A6[1]-miny)/Ly);
			glVertex3dv(A6);
			glTexCoord2f((A5[0]-minx)/Lx,(A5[1]-miny)/Ly);
			glVertex3dv(A5);
			glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
			glVertex3dv(A4);
			glEnd();
			}
		}
		else if(bstartDM==FALSE)//���ų���
		{
			glBindTexture(GL_TEXTURE_2D, m_cTunnel_dmwcBp.GetTxtID());
			
			//(1)���
			A1[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[2].x;
			A1[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[2].y;
			A1[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[2].z;
			
			A2[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[1].x;
			A2[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[1].y;
			A2[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_L[0].Hp[1].z;
			
			A3[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].x;
			A3[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].y;
			A3[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[1].z;
			
			A4[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].x;
			A4[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].y;
			A4[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_L[0].Hp[0].z;
		
			A5[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].x;
			A5[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].y;
			A5[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[3].z;
		
			A6[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].x;
			A6[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].y;
			A6[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouL[2].z;
			
			//�� minx,maxx,miny,maxy;
			
			minx=miny=999999999;
			maxx=maxy=-999999999;
			if(minx>A1[0]) minx=A1[0];
			if(maxx<A1[0]) maxx=A1[0];
			if(miny>A1[1]) miny=A1[1];
			if(maxy<A1[1]) maxy=A1[1];
			
			if(minx>A2[0]) minx=A2[0];
			if(maxx<A2[0]) maxx=A2[0];
			if(miny>A2[1]) miny=A2[1];
			if(maxy<A2[1]) maxy=A2[1];
			
			if(minx>A3[0]) minx=A3[0];
			if(maxx<A3[0]) maxx=A3[0];
			if(miny>A3[1]) miny=A3[1];
			if(maxy<A3[1]) maxy=A3[1];
			
			if(minx>A4[0]) minx=A4[0];
			if(maxx<A4[0]) maxx=A4[0];
			if(miny>A4[1]) miny=A4[1];
			if(maxy<A4[1]) maxy=A4[1];
		
			if(minx>A5[0]) minx=A5[0];
			if(maxx<A5[0]) maxx=A5[0];
			if(miny>A5[1]) miny=A5[1];
			if(maxy<A5[1]) maxy=A5[1];
			
			if(minx>A6[0]) minx=A6[0];
			if(maxx<A6[0]) maxx=A6[0];
			if(miny>A6[1]) miny=A6[1];
			if(maxy<A6[1]) maxy=A6[1];
			
			if(minx>P1[0]) minx=P1[0];
			if(maxx<P1[0]) maxx=P1[0];
			if(miny>P1[1]) miny=P1[1];
			if(maxy<P1[1]) maxy=P1[1];
			
			if(minx>P7[0]) minx=P7[0];
			if(maxx<P7[0]) maxx=P7[0];
			if(miny>P7[1]) miny=P7[1];
			if(maxy<P7[1]) maxy=P7[1];
			
	
			
			float L1,L2;
			L1=myDesingScheme.GetDistenceXYZ(A1[0],A1[1],A1[2],P1[0],P1[1],P1[2]);
			L2=myDesingScheme.GetDistenceXYZ(A2[0],A2[1],A2[2],A3[0],A3[1],A3[2]);

			int bsign;
			if(A2[2]>=A3[2])
				bsign=-1;
			else
				bsign=1;
	
			minx=A1[0]+bsign*L1;
			maxx=P7[0];
		
			Lx=maxx-minx;
			Ly=maxy-miny;
			
			glColor3f(1,1,0);
			glBegin(GL_TRIANGLE_FAN);
				glTexCoord2f((P1[0]-minx)/Lx,(P1[1]-miny)/Ly);
				glVertex3dv(P1);
				glTexCoord2f((A1[0]-minx+bsign*L1)/Lx,(A1[1]-miny)/Ly);
				glVertex3dv(A1);
				glTexCoord2f((A2[0]-minx+bsign*L2)/Lx,(A2[1]-miny)/Ly);
				glVertex3dv(A2);
				glTexCoord2f((A3[0]-minx)/Lx,(A3[1]-miny)/Ly);
				glVertex3dv(A3);
				glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
				glVertex3dv(A4);
				glTexCoord2f((P7[0]-minx)/Lx,(P7[1]-miny)/Ly);
				glVertex3dv(P7);
			glEnd();
			
				
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f((P7[0]-minx)/Lx,(P7[1]-miny)/Ly);
			glVertex3dv(P7);
			glTexCoord2f((A6[0]-minx)/Lx,(A6[1]-miny)/Ly);
			glVertex3dv(A6);
			glTexCoord2f((A5[0]-minx)/Lx,(A5[1]-miny)/Ly);
			glVertex3dv(A5);
			glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
			glVertex3dv(A4);
			glEnd();
		

			//(2)�Ҳ�
			A1[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[2].x;
			A1[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[2].y;
			A1[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[2].z;
			
			A2[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[1].x;
			A2[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[1].y;
			A2[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn+1)->HuPo_R[0].Hp[1].z;
			
			A3[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].x;
			A3[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].y;
			A3[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[1].z;
			
			A4[0]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].x;
			A4[1]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].y;
			A4[2]=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(mIn)->HuPo_R[0].Hp[0].z;
			
			A5[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].x;
			A5[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].y;
			A5[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[3].z;
			
			A6[0]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].x;
			A6[1]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].y;
			A6[2]=myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(mIn)->SuiGouR[2].z;
			
			//�� minx,maxx,miny,maxy;
			
			minx=miny=999999999;
			maxx=maxy=-999999999;
			if(minx>A1[0]) minx=A1[0];
			if(maxx<A1[0]) maxx=A1[0];
			if(miny>A1[1]) miny=A1[1];
			if(maxy<A1[1]) maxy=A1[1];
			
			if(minx>A2[0]) minx=A2[0];
			if(maxx<A2[0]) maxx=A2[0];
			if(miny>A2[1]) miny=A2[1];
			if(maxy<A2[1]) maxy=A2[1];
			
			if(minx>A3[0]) minx=A3[0];
			if(maxx<A3[0]) maxx=A3[0];
			if(miny>A3[1]) miny=A3[1];
			if(maxy<A3[1]) maxy=A3[1];
			
			if(minx>A4[0]) minx=A4[0];
			if(maxx<A4[0]) maxx=A4[0];
			if(miny>A4[1]) miny=A4[1];
			if(maxy<A4[1]) maxy=A4[1];
			
			if(minx>A5[0]) minx=A5[0];
			if(maxx<A5[0]) maxx=A5[0];
			if(miny>A5[1]) miny=A5[1];
			if(maxy<A5[1]) maxy=A5[1];
			
			if(minx>A6[0]) minx=A6[0];
			if(maxx<A6[0]) maxx=A6[0];
			if(miny>A6[1]) miny=A6[1];
			if(maxy<A6[1]) maxy=A6[1];
			
			if(minx>P4[0]) minx=P4[0];
			if(maxx<P4[0]) maxx=P4[0];
			if(miny>P4[1]) miny=P4[1];
			if(maxy<P4[1]) maxy=P4[1];
			
			if(minx>P8[0]) minx=P8[0];
			if(maxx<P8[0]) maxx=P8[0];
			if(miny>P8[1]) miny=P8[1];
			if(maxy<P8[1]) maxy=P8[1];
			
		//	
			L1=myDesingScheme.GetDistenceXYZ(A1[0],A1[1],A1[2],P1[0],P1[1],P1[2]);
			L2=myDesingScheme.GetDistenceXYZ(A2[0],A2[1],A2[2],A3[0],A3[1],A3[2]);
			
			
			if(A2[2]>=A3[2])
				bsign=1;
			else
				bsign=-1;
			
			maxx=A1[0]+bsign*L1;
			minx=P8[0];
			
			Lx=maxx-minx;
			Ly=maxy-miny;
			
			
			glColor3f(1,1,0);
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f((P4[0]-minx)/Lx,(P4[1]-miny)/Ly);
			glVertex3dv(P4);
			glTexCoord2f((A1[0]-minx+bsign*L1)/Lx,(A1[1]-miny)/Ly);
			glVertex3dv(A1);
			glTexCoord2f((A2[0]-minx+bsign*L2)/Lx,(A2[1]-miny)/Ly);
			glVertex3dv(A2);
			glTexCoord2f((A3[0]-minx)/Lx,(A3[1]-miny)/Ly);
			glVertex3dv(A3);
			glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
			glVertex3dv(A4);
			glTexCoord2f((P8[0]-minx)/Lx,(P8[1]-miny)/Ly);
			glVertex3dv(P8);
			glEnd();
			
			
			
			glBegin(GL_TRIANGLE_FAN);
			glTexCoord2f((P8[0]-minx)/Lx,(P8[1]-miny)/Ly);
			glVertex3dv(P8);
			glTexCoord2f((A6[0]-minx)/Lx,(A6[1]-miny)/Ly);
			glVertex3dv(A6);
			glTexCoord2f((A5[0]-minx)/Lx,(A5[1]-miny)/Ly);
			glVertex3dv(A5);
			glTexCoord2f((A4[0]-minx)/Lx,(A4[1]-miny)/Ly);
			glVertex3dv(A4);
			glEnd();
		}

		glColor3f(1,1,1);
		glLineWidth(0);
}



//��·��ά��ģ
void CT3DSystemView::OnMenuBuild3dlinemodle() 
{
	BeginWaitCursor();
	b_haveGetRegion=FALSE;//�Ƿ��ѻ�ȡ�������
	
	myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_RailwayBP3D[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].RemoveAll();
	myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].RemoveAll();
	

	if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()<2)
		return;
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	float iPer=100.0/(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1);
	CString tt;
	
	
	for (long i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
	{	
		
		if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->Lc<=
			myDesingScheme.SchemeDatass[m_currentSchemeIndexs].EndLC)
		{
			myDesingScheme.Get3DLineModel(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->x,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->y,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->z,\
				m_Railway.m_Railway_width,m_Railway.m_Lj_width,m_Railway.m_Lj_Dh,\
				m_Railway.m_GuiMianToLujianWidth,45,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle,\
				i,\
				myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc
				);
		}
		tt.Format("���ڽ�����·��ά��ģ , ���Ժ�... , �����%.2f%s" , (i+1)*iPer , "%");
		pMainFrame->Set_BarText(4 , tt , 0); 
		
	}
	

	if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)->Lc<=
		myDesingScheme.SchemeDatass[m_currentSchemeIndexs].EndLC)
	{
		myDesingScheme.Get3DLineModelLast(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2)->x,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2)->y,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2)->z,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)->x,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)->y,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)->z,\
			m_Railway.m_Railway_width,m_Railway.m_Lj_width,m_Railway.m_Lj_Dh,\
			m_Railway.m_GuiMianToLujianWidth,45,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2)->strJDStyle,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1)->strJDStyle,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-2)->Lc\
			);
	}

	
	pMainFrame->Set_BarText(4 , "���ص�����Ӱ�������������!" , 0); 
	b_haveMadeRail3DwayList=FALSE;
	b_haveMadeRail3DwayList_Ortho=FALSE;
	OnDraw (GetDC()); //ˢ����ά����
	
}

//�ط���������,Ҳ�Ͳ�����ǰ��·������������Ϊ����·������	
void CT3DSystemView::OnFlyRoutinschemeline() 
{
	m_R=3000;
	m_r=2000;
	
	if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()<=1)
	{
		if(m_FlayPath.GetSize()<=0) //������ǰ�ǰ�·������״̬
			m_PathFlag=FALSE; //��ʶ����·����Ч
		else
			m_PathFlag=TRUE; //��ʶ����·����Ч
		return;
	}
	
	m_FlayPath.RemoveAll();//����·���������
	PCordinate ppt=NULL;
	//����·������Ϊ����·��
	for(int i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize();i++)
	{
		ppt = new Cordinate;
		ppt->x=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x;//x����
		ppt->y=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y;//y����
		ppt->z=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z;//z����
		ppt->Lc=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->Lc;//���
		m_FlayPath.Add(ppt); //����·���������������·��������
	}
	
	if(m_FlayPath.GetSize()>1) //�������·����Ч
	{
		m_bmouseView=FALSE; //ֹͣ�����ת�ӽǹ���
		//	m_ShowFlyPath=TRUE;
// 		m_ShowFlyPath=FALSE;//��·��ά���β���Ҫ��ʾ·��,Ӱ��Ч��
		m_PathFlag=TRUE; //��ʶ����·����Ч
		m_ifZoomonRoad=TRUE; //��ʶ����·��������
		m_far=1500; //��·��ά����ʱ,���ӿ�Զ�����СһЩ,���õ�һЩ������
		//��Ԫ��,�ӿ������ٶ�,ԭ����10000,�൱��10����,��·��ά����ʱ����
		//Ҫ��ô��
		
	}
	else
	{
		m_ifZoomonRoad=FALSE; //��ʶ����·��������ΪFALSE
	}
	
	OnFlyRoutineheight();	//����Ը߶ȷ���	
}





//��������·�����������������������
void CT3DSystemView::GetCameraCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2)
{
	//(x1,y1,x1):����·����ǰ������
	//(x2,y2,x2):����·����һ������
	

	if(m_FlyHeightType == GIS_FLY_STATICHEIGHT)	//�̶��߶ȷ��з�ʽ
	{
		m_vView.x=x2;//�۲��x����
		m_vView.y=m_StaticHeight;//�۲��y����=y2+m_StaticHeight�̶��߶�ֵ
		m_vView.z=z2;//�۲��z����

		m_vPosition.x=x1;//�ӵ�x����
		m_vPosition.y=m_vView.y;//�ӵ�y����=�۲��y����
		m_vPosition.z=z1;//�ӵ�z����
	}
	//����Ը߶�(����·��)����ʱ�������һ�������߶�
	else if(m_FlyHeightType == GIS_FLY_PATHHEIGHT)
	{
		m_vView.x=x2; //�۲��x����
		m_vView.y=y2+m_StaticHeight; //�۲��y����=y2+m_StaticHeight�̶��߶�ֵ
		m_vView.z=z2;//�۲��z����
		
		//�����֮�����
		float distance = sqrt((x2-x1)*(x2-x1)+(z2-z1)*(z2-z1));
		//������Ǽ���߶Ȳ�
		float dh = distance * tan(m_ViewUpDown * PAI_D180);
		
		m_vPosition.x=x1;//�ӵ�x����
		m_vPosition.y=m_vView.y+dh;//�ӵ�y����=�۲��y����+�߲�
		m_vPosition.z=z1;//�ӵ�z����
	}
}

//��������ʱ���ٶ�
void CT3DSystemView::CalZoomSpeed(float mCurZooomLC)
{
	static DWORD dwStart = 0;
	DWORD dwNow = ::GetTickCount();
	if(dwNow-dwStart>=100) //0.1��
	{
		long fgf=dwNow-dwStart;
		CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		CString strText;
		strText.Format("�����ٶ�= %.3f ��/�� ",(mCurZooomLC-m_PreZooomLC)/(((dwNow-dwStart)/1000.0)),0);
		pMainFrame->Set_BarText(4,strText,0); 
		dwStart = dwNow;
		m_PreZooomLC=mCurZooomLC;
		
	}
}



void CT3DSystemView::BuildQDModelList()
{
	g_3dsModels=new C3DSModel;
	char *str = new char[256]; 
	
	CString str3DSfilename;
	
	strcpy(g_sMediaPath,m_3DSfilename_QD);
	GetFilePath(g_sMediaPath);
	g_3dsModels->LoadModelFromFile((LPTSTR)(LPCTSTR)m_3DSfilename_QD);
	
	glNewList(m_QDList,GL_COMPILE);
	g_3dsModels->Draw(2,&m_QD_minx,&m_QD_maxx,&m_QD_miny,&m_QD_maxy,&m_QD_minz,&m_QD_maxz);	
	glEndList();
	
}

//�������������ʾ�б�
void CT3DSystemView::BuildTunnelDMModelList()
{
	g_3dsModels=new C3DSModel;
	char *str = new char[256]; 
	
	CString str3DSfilename;
	
	m_3DSfilename_TunnelDM=".\\ģ��\\�������\\��ǽʽ����\\ģ���ļ�.3DS";
	strcpy(g_sMediaPath,m_3DSfilename_TunnelDM);
	GetFilePath(g_sMediaPath);
	g_3dsModels->LoadModelFromFile((LPTSTR)(LPCTSTR)m_3DSfilename_TunnelDM);
	
	glNewList(m_TunnelDMList,GL_COMPILE);
	g_3dsModels->Draw(2,&m_TunnelDM_minx,&m_TunnelDM_maxx,&m_TunnelDM_miny,&m_TunnelDM_maxy,&m_TunnelDM_minz,&m_TunnelDM_maxz);	
	glEndList();

}


void CT3DSystemView::makeQLList()
{
	glNewList(m_QLanList,GL_COMPILE);
		DrawCylinder(m_Bridge.m_Bridge_HLWidth/100.0,m_Bridge.m_Bridge_HLHeight,500);
	glEndList();
	
}

//��Բ��
void CT3DSystemView::DrawCylinder(GLfloat radii, GLfloat Height, GLint segmentNum)
{
	if(radii==0   ||   Height==0)   
		return;   
	GLint j,k;   
	GLfloat x,y;   
		
	
	glBegin(GL_TRIANGLE_STRIP);
	for(j=0,k=0;j<=segmentNum;j++,k++)
	{
		x=cos(2.0*PI*j/(double)segmentNum);
		y=sin(2.0*PI*j/(double)segmentNum);
		if(k==segmentNum)
			k=0;
		
		glTexCoord2f(x/radii,0);
		glVertex3f(x*radii, 0,-y*radii);
		
		glTexCoord2f(x/radii,1);
		glVertex3f(x*radii,Height,-y*radii);
		
	}
	glEnd();
}

//�����������
void CT3DSystemView::OnMenuTunnelset() 
{
	CTunncelPropertySet dlg;
	dlg.m_tunnel_height=m_Tunnel.height;//����ܸ߶�
	dlg.m_tunnel_Archeight=m_Tunnel.Archeight;//���Բ���߶�
	dlg.m_tunnel_WallHeight =m_Tunnel.height-m_Tunnel.Archeight;//�����ǽ�߶�
	dlg.m_tunnel_ArcSegmentNumber=m_Tunnel.ArcSegmentNumber;//���Բ���ֶ���
	dlg.m_tunnel_H=m_Tunnel.H ;//���Բ�����������ϵĸ߶�
	dlg.m_tunnel_L=m_Tunnel.L;//������Ŷ���������������Ŀ�� 
	if(dlg.DoModal()==IDOK)
	{
		m_Tunnel.height=dlg.m_tunnel_height;//����ܸ߶�
		m_Tunnel.Archeight=dlg.m_tunnel_Archeight;//���Բ���߶�
		m_Tunnel.WallHeight =m_Tunnel.height-m_Tunnel.Archeight;;//�����ǽ�߶�
		m_Tunnel.ArcSegmentNumber=dlg.m_tunnel_ArcSegmentNumber;//���Բ���ֶ���
		m_Tunnel.H= dlg.m_tunnel_H;//���Բ�����������ϵĸ߶�
		m_Tunnel.L=dlg.m_tunnel_L;//������Ŷ���������������Ŀ�� 
		b_haveMadeRail3DwayList=FALSE; //����������ı�ʱ,��Ҫ���¹�����ʾ�б�(͸��ͶӰģʽ)
		b_haveMadeRail3DwayList_Ortho=FALSE;//����������ı�ʱ,��Ҫ���¹�����ʾ�б�(����ͶӰģʽ)
		OnDraw (GetDC()); //ˢ����ά����
	}	
}

//������������
void CT3DSystemView::OnMenuBridgeset() 
{
	CBridgeSet dlg;
	dlg.m_Bridge_HLHeight=m_Bridge.m_Bridge_HLHeight;//�������˸�
	dlg.m_Bridge_HLSpace=m_Bridge.m_Bridge_HLSpace;//�������˼��
	dlg.m_Bridge_HLWidth=m_Bridge.m_Bridge_HLWidth;//�������˿��
	dlg.m_Bridge_QDSpace=m_Bridge.m_Bridge_QDSpace;//�Ŷռ��
	dlg.m_Bridge_HPangle=m_Bridge.m_Bridge_HPangle;//��ͷ�������
	dlg.m_bridgeColorR=m_bridgeColorR;//����������ɫ
	dlg.m_bridgeColorG=m_bridgeColorG;//����������ɫ
	dlg.m_bridgeColorB=m_bridgeColorB;//����������ɫ

	if(dlg.DoModal()==IDOK)
	{
		m_Bridge.m_Bridge_HLHeight=dlg.m_Bridge_HLHeight;//�������˸�
		m_Bridge.m_Bridge_HLSpace=dlg.m_Bridge_HLSpace;;//�������˼��
		m_Bridge.m_Bridge_HLWidth=dlg.m_Bridge_HLWidth;//�������˿��
		m_Bridge.m_Bridge_QDSpace=dlg.m_Bridge_QDSpace;//�Ŷռ��
		m_Bridge.m_Bridge_HPangle=dlg.m_Bridge_HPangle;//��ͷ�������
		m_bridgeColorR=dlg.m_bridgeColorR;//����������ɫ
		m_bridgeColorG=dlg.m_bridgeColorG;//����������ɫ
		m_bridgeColorB=dlg.m_bridgeColorB;////����������ɫ
		b_haveMadeRail3DwayList=FALSE;
		b_haveMadeRail3DwayList_Ortho=FALSE;
		makeQLList(); //������������������ʾ�б�
		OnDraw (GetDC()); //ˢ����ά����
	}	
}

//������������
void CT3DSystemView::DrawBridgeHL()
{
		//������������
		glPushAttrib(GL_TEXTURE_BIT|GL_POLYGON_BIT);
			glDisable(GL_TEXTURE_2D); //�ر�����
			glPolygonMode(GL_FRONT_AND_BACK ,GL_LINE);	//�����ͻ���
			glColor3f(m_bridgeColorR/255.0,m_bridgeColorG/255.0,m_bridgeColorB/255.0);//��������������ɫ
			glLineWidth(m_Bridge.m_Bridge_HLWidth); //���û������˵��߿�
		for (long i=0;i<myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetSize()-1;i++)
		{
			
			//�����ǰ����һ������������!=-1���������������
			if(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1!=-1)
			{	
				
				//������������м����
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
				glEnd();

				//����������˶��˺���
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1+m_Bridge.m_Bridge_HLHeight,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1+m_Bridge.m_Bridge_HLHeight,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z1);
				glEnd();


				//�Ҳ����������м����
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y2+m_Bridge.m_Bridge_HLHeight/2.0,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
				glEnd();
				
				//�Ҳ��������˶��˺���
				glBegin(GL_LINES);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2+m_Bridge.m_Bridge_HLHeight,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glVertex3f(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y2+m_Bridge.m_Bridge_HLHeight,
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->z2);
				glEnd();

				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glCallList(m_QLanList);//��������������ʾ�б�������Բ������������
				glPopMatrix();


		
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glCallList(m_QLanList);//��������������ʾ�б�����Ҳ�Բ������������
				glPopMatrix();
			
			}
			
			if(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1==-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1==-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->x1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->y1!=-1)
			{
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->y1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->z1);
				glCallList(m_QLanList);//��������������ʾ�б�������Բ������������
				glPopMatrix();
				
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->y2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i-1)->z2);
				glCallList(m_QLanList);//��������������ʾ�б�����Ҳ�Բ������������
				glPopMatrix();
				
			}
			if(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1!=-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->x1==-1 && \
				myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i+1)->y1==-1)
			{
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y1,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z1);
				glCallList(m_QLanList);//��������������ʾ�б�������Բ������������
				glPopMatrix();
				
				glPushMatrix();
				glTranslatef(myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->x2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->y2,\
					myDesingScheme.PtS_BridgeLG3D[m_currentSchemeIndexs].GetAt(i)->z2);
				glCallList(m_QLanList);//��������������ʾ�б�����Ҳ�Բ������������
				glPopMatrix();
				
			}

		
		}
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT_AND_BACK ,GL_FILL);	
		glPopAttrib();
}

//���´����ݿ��ж�ȡ��·�������������
void CT3DSystemView::ReLoadCenterPt()
{
	CString tt,strSql;
	PCordinate pt;
	
	//���¶�ȡ�����ĵ���·������������
	//		if(myDesingScheme.SchemeDatass[m_currentSchemeIndexs].EndLC<=myDesingScheme.SchemeDatass[m_currentSchemeIndexs].StartLC)
	//			strSql.Format("SELECT *  FROM  T3DLineZxCorrdinate WHERE ��������='%s' ORDER BY ��� ASC",\
	//			myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename);
	//		else	
	strSql.Format("SELECT *  FROM  T3DLineZxCorrdinate WHERE ��������='%s' \
		ORDER BY ��� ASC",\
		myDesingScheme.SchemeDatass[m_currentSchemeIndexs].Schemename\
		);
	
	try
	{
		//			if(m_Recordset->State) //���
		//				m_Recordset->Close();
		m_Recordset->Open((_bstr_t)strSql,(IDispatch*)(theApp.m_pConnection),adOpenDynamic,adLockOptimistic,adCmdText);   //�����ݱ� 
	}
	
	catch(_com_error& e)	//����׽
	{
		CString errormessage;
		errormessage.Format("�򿪱�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		::MessageBox(NULL,errormessage,"�����ݱ�",MB_ICONSTOP);
		return;
	} 
	
	myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].RemoveAll(); //�����·��������PtS_3DLineZX[]
	while (!m_Recordset->adoEOF)
	{
		pt=new Cordinate;
		
		Thevalue = m_Recordset->GetCollect("x����"); 
		pt->x=(double)Thevalue; //��·���ߵ��x����
		
		Thevalue = m_Recordset->GetCollect("y����"); 
		pt->y=(double)Thevalue;//��·���ߵ��y����
		
		Thevalue = m_Recordset->GetCollect("z����"); 
		pt->z=(double)Thevalue;//��·���ߵ��z����
		
		Thevalue = m_Recordset->GetCollect("��������"); 
		if(Thevalue.vt!=VT_NULL) 
		{
			tt=Thevalue.bstrVal;
			pt->strJDStyle=tt; //��·���ߵ��x����
		}
		
		Thevalue = m_Recordset->GetCollect("����߳�"); 
		pt->dmh=(double)Thevalue; //��Ӧ�ĵ���߳�
		
		Thevalue = m_Recordset->GetCollect("���ڸ�"); 
		pt->Derh=(double)Thevalue; //��Ӧ�����ڸ�
		
		Thevalue = m_Recordset->GetCollect("���"); 
		pt->Lc=(double)Thevalue;//��Ӧ�����
		
		myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].Add(pt); //�洢��·������������
		m_Recordset->MoveNext(); //ָ������
		
	}
	m_Recordset->Close(); //�رռ�¼��
	
}

//��������
void CT3DSystemView::OnMenuTexturebp() 
{
	CTextureBP	dlg;
	CString strTexturename;

	if(dlg.DoModal()==IDOK) //�����IDOK��ʽ�رնԻ���
	{
		strTexturename="����\\���·���\\"+dlg.m_BPtextureName; //�õ������ļ���·����
		m_cTxtureBP.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename); //���ر�������
		b_haveMadeRail3DwayList=FALSE; //��ά��·��ʾ�б��ʶΪFALSE,��ʾ��Ҫ���¹�����·��άģ���б�(͸��ͶӰģʽ��)
		b_haveMadeRail3DwayList_Ortho=FALSE;//��ά��·��ʾ�б��ʶΪFALSE,��ʾ��Ҫ���¹�����·��άģ���б�(����ͶӰģʽ��)
		OnDraw (GetDC()); //ˢ����ά����
	}	
}

//·������
void CT3DSystemView::OnMenuTexturelj() 
{
	CTextureLJ	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//�����IDOK��ʽ�رնԻ���
	{
		strTexturename="����\\·��\\"+dlg.m_LJtextureName;//�õ������ļ���·����
		m_cTxtureLJ.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//����·������
		b_haveMadeRail3DwayList=FALSE; //��ά��·��ʾ�б��ʶΪFALSE,��ʾ��Ҫ���¹�����·��άģ���б�(͸��ͶӰģʽ��)
		b_haveMadeRail3DwayList_Ortho=FALSE;//��ά��·��ʾ�б��ʶΪFALSE,��ʾ��Ҫ���¹�����·��άģ���б�(����ͶӰģʽ��)
		OnDraw (GetDC());//ˢ����ά����
	}	
}

//��������������
void CT3DSystemView::OnMenuTextureqlhpm() 
{
	CTextureQLHpm	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//�����IDOK��ʽ�رնԻ���
	{
		strTexturename="����\\���·�������\\"+dlg.m_HQMtextureName;//�õ������ļ���·����
		m_cBridgeHpm.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//����·������
		b_haveMadeRail3DwayList=FALSE; //��ά��·��ʾ�б��ʶΪFALSE,��ʾ��Ҫ���¹�����·��άģ���б�(͸��ͶӰģʽ��)
		b_haveMadeRail3DwayList_Ortho=FALSE;//��ά��·��ʾ�б��ʶΪFALSE,��ʾ��Ҫ���¹�����·��άģ���б�(����ͶӰģʽ��)
		OnDraw (GetDC());//ˢ����ά����
	}	
}

//�����ǽ����
void CT3DSystemView::OnMenuTexturetunnel() 
{

	CTextureTunnel	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//�����IDOK��ʽ�رնԻ���
	{
		strTexturename="����\\�����ǽ\\"+dlg.m_TunneltextureName;//�õ������ļ���·����
		m_cTunnel.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//����·������
		b_haveMadeRail3DwayList=FALSE; //��ά��·��ʾ�б��ʶΪFALSE,��ʾ��Ҫ���¹�����·��άģ���б�(͸��ͶӰģʽ��)
		b_haveMadeRail3DwayList_Ortho=FALSE;//��ά��·��ʾ�б��ʶΪFALSE,��ʾ��Ҫ���¹�����·��άģ���б�(����ͶӰģʽ��)
		OnDraw (GetDC());//ˢ����ά����
	}		
}

//�����������
void CT3DSystemView::OnMenuTexturetunnelDm() 
{
	CTextureTunnelDm	dlg;
	CString strTexturename;
	if(dlg.DoModal()==IDOK)//�����IDOK��ʽ�رնԻ���
	{
		strTexturename="����\\�������\\"+dlg.m_TunnelDmtextureName;//�õ������ļ���·����
		m_cTunnel_dm.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//����·������
		strTexturename="����\\�������������\\"+dlg.m_TunnelDmtextureName;//�õ������ļ���·����
		m_cTunnel_dmwcBp.LoadGLTextures((LPTSTR)(LPCTSTR)strTexturename);//�������������
		
		b_haveMadeRail3DwayList=FALSE; //��ά��·��ʾ�б��ʶΪFALSE,��ʾ��Ҫ���¹�����·��άģ���б�(͸��ͶӰģʽ��)
		b_haveMadeRail3DwayList_Ortho=FALSE;//��ά��·��ʾ�б��ʶΪFALSE,��ʾ��Ҫ���¹�����·��άģ���б�(����ͶӰģʽ��)
		OnDraw (GetDC());//ˢ����ά����
	}		
}

//ʱ��ָ����Ļ���
void CT3DSystemView::DrawClock()
{
//	if(m_bShowClocFlag==FALSE) return;
	
	glPushMatrix(); //ѹ������ջ
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); //�߻��Ʒ�ʽ
		glDisable(GL_TEXTURE_2D);	//�ر�����	
		SetClockProjectionNavigate(); //����ָ�����ͶӰ����
		glCallList(m_clockList);//����ָ����ʱ�ӵ���ʾ�б�
		DrawNorthPt();	//����ָ����
		
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //�����Ʒ�ʽ
		glEnable(GL_TEXTURE_2D);//������	
		glLineWidth(1.0); //�����߿�
		glColor3f(1.0, 1.0, 1.0); //������ɫ
	glPopMatrix();//���������ջ
}

void CT3DSystemView::SetClockProjectionNavigate()
{
	float wh=120; //����ʱ�ӵĸ߶�
	glViewport(0, WinViewY-wh,wh, wh);//�����ӿ�λ�úʹ�С
    glMatrixMode( GL_PROJECTION ); //���õ�ǰ����Ϊ͸�Ӿ���
    glLoadIdentity(); //����ǰ�����û�Ϊ��λ�� 
	glOrtho (0.0f,1.0,0.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode( GL_MODELVIEW );//���õ�ǰ����Ϊģ�;���
	glLoadIdentity ();//����ǰ�����û�Ϊ��λ�� 
}

//����ʱ��ָ������ʾ�б�
void CT3DSystemView::makeClockList()
{
	glNewList(m_clockList,GL_COMPILE); //������ʾ�б�
	float R=0.5,x,y;//ʱ��Բ�̰뾶
	int i;

	glColor3f(0.0, 1.0, 1.0); //����������ɫ

	x=R*cos((0)*PAI_D180)+0.37;//����ƫ������׼��д����ĸ"E"����ʾ�̶�3
	y=R*sin((0)*PAI_D180)+0.48;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"E"); //����������λ��д��E����ʾ���򡰶���

	x=R*cos((90)*PAI_D180)+0.47;//����ƫ������׼��д����ĸ"N"����ʾ�̶�12
	y=R*sin((90)*PAI_D180)+0.36;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"N");//����������λ��д��N����ʾ���򡰱���
	
	x=R*cos((180)*PAI_D180)+0.59;//����ƫ������׼��д����ĸ"W" ����ʾ�̶�9
	y=R*sin((180)*PAI_D180)+0.48;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"W");//����������λ��д��W����ʾ��������

	x=R*cos((270)*PAI_D180)+0.48;//����ƫ������׼��д����ĸ"S" ����ʾ�̶�6
	y=R*sin((270)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"S");//����������λ��д��S����ʾ�����ϡ�
	
	glColor3f(1.0, 1.0, 1.0); //����ʱ�ӿ̶�������ɫ
	
	x=R*cos((30)*PAI_D180)+0.39; //��������
	y=R*sin((30)*PAI_D180)+0.43;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"2"); //д�����̶ֿ�
	
	
	x=R*cos((60)*PAI_D180)+0.42;
	y=R*sin((60)*PAI_D180)+0.40;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"1");//д�����̶ֿ�1
	
	
	x=R*cos((120)*PAI_D180)+0.49;
	y=R*sin((120)*PAI_D180)+0.38;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"11");//д�����̶ֿ�11
	
	x=R*cos((150)*PAI_D180)+0.55;
	y=R*sin((150)*PAI_D180)+0.42;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"10");//д�����̶ֿ�10


	x=R*cos((210)*PAI_D180)+0.58;
	y=R*sin((210)*PAI_D180)+0.53;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"8");//д�����̶ֿ�8

	x=R*cos((240)*PAI_D180)+0.54;
	y=R*sin((240)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"7");//д�����̶ֿ�7


	x=R*cos((300)*PAI_D180)+0.43;
	y=R*sin((300)*PAI_D180)+0.58;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"5");//д�����̶ֿ�5

	x=R*cos((330)*PAI_D180)+0.40;
	y=R*sin((330)*PAI_D180)+0.52;
	PrintText(x,y,(LPTSTR)(LPCTSTR)"4");//д�����̶ֿ�4
	
    //����ʱ��Բ��Բ�̵���ɫ
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(2.0); //�����߿�
    //����ʱ��Բ��Բ��
	glBegin(GL_LINE_STRIP);
		for ( i=0;i<=360;i++)
		{
			 x=R*cos(i*PAI_D180)+0.5;
			 y=R*sin(i*PAI_D180)+0.5;
			glVertex2f(x,y);
		}
	glEnd();
	
	//����ʱ���ڱ�ʾСʱ֮��Ŀ̶�,��Բ���ʾ	
	float d;
	for (i=0;i<=360;i+=6)
	{

		switch(i)
		{
		case 0: //��N(12��)��
			glColor3f(0.0, 1.0, 1.0);//������ɫ
			glPointSize(4.0); //���õ�Ĵ�С
			break;
		case 90://��W(9��)��
			glColor3f(0.0, 1.0, 1.0);//������ɫ
			glPointSize(4.0); //���õ�Ĵ�С
			break;
		case 180://��S(6��)��
			glColor3f(0.0, 1.0, 1.0);//������ɫ
			glPointSize(4.0); //���õ�Ĵ�С
			break;
		case 270://��E(3��)��
			glColor3f(0.0, 1.0, 1.0);//������ɫ
			glPointSize(4.0); //���õ�Ĵ�С
			break;
		default:
			glColor3f(0.77, 0.67, 0.95);//������ɫ
			glPointSize(2.0); //���õ�Ĵ�С
			break;
		}
	
		if(i%30==0 && i%90!=0)//����ʱ�̴�(��7��,8���)
		{	
			glColor3f(1.0, 0.0, 1.0);//������ɫ
			glPointSize(3.0);//���õ�Ĵ�С
		}
		
		d=0.04;//ƫ����
		x=R*cos(i*PAI_D180)+0.5;//����x����
		y=R*sin(i*PAI_D180)+0.5;//����y����
		
		//���Ƶ��־
		glBegin(GL_POINTS);
			x=x-d*cos(i*PAI_D180);
			y=y-d*sin(i*PAI_D180);
			glVertex2f(x,y);
		glEnd();
		}
	glLineWidth(1.0); //�����߿�
	glEndList();//������ʾ�б�
	
}

//����ָ����
void CT3DSystemView::DrawNorthPt()
{
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); //����䷽ʽ����
	glDisable(GL_TEXTURE_2D); //�ر�����		
	float R=0.5;
		
	float x1,y1,x2,y2,x3,y3;
	float mPtangle=25;
	float tempangle;
	float L,L1,L2;
	L1=0.3; 
	L2=0.2;
	x1=0.5;y1=0.5; //ʱ��Բ�ĵ����ָ꣬����Χ�Ƹõ����ָ����ת
	x3=x1+L1*cos((m_NorthPtangle)*PAI_D180);
	y3=y1+L1*sin((m_NorthPtangle)*PAI_D180);

	//���ָ����ָ���λ�ڵ�1����
	if(m_NorthPtangle>=0 && m_NorthPtangle<=90)
	{	tempangle=m_NorthPtangle-mPtangle;
		L=0.1/cos(mPtangle*PAI_D180);
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1-L2*sin(tempangle*PAI_D180);
		
		glColor3f(1.0, 1.0, 0.0); //������ɫ
		glBegin(GL_TRIANGLES);//�������������
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
		
		glColor3f(1.0, 0.0, 0.0); //������ɫ
		tempangle=m_NorthPtangle+mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1-L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);//�����Ҳ�������
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
	}

	//���ָ����ָ���λ�ڵ�2����
	if(m_NorthPtangle>90 && m_NorthPtangle<=180)
	{	

	tempangle=180-m_NorthPtangle-mPtangle;
	x2=x1+L2*cos(tempangle*PAI_D180);
	y2=y1-L2*sin(tempangle*PAI_D180);
	
	glColor3f(1.0, 1.0, 0.0); //������ɫ
	glBegin(GL_TRIANGLES);//�������������
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
	glEnd();
	
	glColor3f(1.0, 0.0, 0.0); //������ɫ
	tempangle=180-m_NorthPtangle+mPtangle;
	x2=x1+L2*cos(tempangle*PAI_D180);
	y2=y1-L2*sin(tempangle*PAI_D180);
	glBegin(GL_TRIANGLES);//�����Ҳ�������
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glVertex2f(x3,y3);
	glEnd();
	}

	//���ָ����ָ���λ�ڵ�3����
	if(m_NorthPtangle>180 && m_NorthPtangle<=270)
	{	
		
		tempangle=m_NorthPtangle-180-mPtangle;
		x2=x1+L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		
		glColor3f(1.0, 1.0, 0.0);//������ɫ
		glBegin(GL_TRIANGLES);//�������������
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
		
		glColor3f(1.0, 0.0, 0.0);//������ɫ
		tempangle=m_NorthPtangle-180+mPtangle;
		x2=x1+L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);//�����Ҳ�������
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
	}

	//���ָ����ָ���λ�ڵ�4����
	if(m_NorthPtangle>270 && m_NorthPtangle<=360)
	{	
		
		tempangle=360-m_NorthPtangle-mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		
		glColor3f(1.0, 1.0, 0.0);//������ɫ
		glBegin(GL_TRIANGLES);//�������������
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
		
		glColor3f(1.0, 0.0, 0.0);//������ɫ
		tempangle=360-m_NorthPtangle+mPtangle;
		x2=x1-L2*cos(tempangle*PAI_D180);
		y2=y1+L2*sin(tempangle*PAI_D180);
		glBegin(GL_TRIANGLES);//�����Ҳ�������
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
			glVertex2f(x3,y3);
		glEnd();
	}

	glColor3f(0.4, 0.47, 0.72);//������ɫ
	glLineWidth(2.0); //�����߿�
	glBegin(GL_LINES); //ָ�����¶�ֱ��
		glVertex2f(x1,y1);
		x2=x1-0.1*cos((m_NorthPtangle)*PAI_D180);
		y2=y1-0.1*sin((m_NorthPtangle)*PAI_D180);
		glVertex2f(x2,y2);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); 
	glEnable(GL_TEXTURE_2D); //��������		
	glLineWidth(1.0);//�����߿�
}

//��ָ��λ������ı�
void CT3DSystemView::PrintText(float x, float y, char *string)
{
	int length;
	length = (int) strlen(string); //�ַ�������
	glRasterPos2f(x,y); //��λ��ǰ���
	for (int m=0;m<length;m++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[m]);//��λͼ��ʽ��ָ�����������һ���ַ���
	}
	
}

 //����������ӵ�����͹۲���������ʱ��ָ����ָ��Ƕ�
void CT3DSystemView::GetNorthPtangle()
{
	if(theApp.bLoginSucceed==FALSE) return;
	
	float dx,dz,ar;
	dx=m_vPosition.x-m_vView.x;//����ӵ���۲��x����֮��
	dz=m_vPosition.z-m_vView.z;//����ӵ���۲��z����֮��
	
	if(dx==0) //���dx==0
	{
		if(dz>=0) //���dz>=0
			m_NorthPtangle=90; ////ָ�����ʼָ��Ƕ�=90��ָ����Ļ���棨Z�Ḻ����
		else
			m_NorthPtangle=270;////ָ�����ʼָ��Ƕ�=270��ָ����Ļ���棨Z��������
	}
	else
	{
		if(dx>0) 
		{
			if(dz>0) //��2����
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=90+ar*HDANGLE;//ָ�����ʼָ��Ƕ�
			}
			else    //��3����
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=270-ar*HDANGLE;//ָ�����ʼָ��Ƕ�
			}
		}
		
		if(dx<0)
		{
			if(dz>0)  //��1����
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=90-ar*HDANGLE;//ָ�����ʼָ��Ƕ�
			}
			else    //��4����
			{
				ar=fabs(atan(dx/dz));
				m_NorthPtangle=270+ar*HDANGLE;//ָ�����ʼָ��Ƕ�
			}
		}
		
	}
}


//��ȡ�������
void CT3DSystemView::GetRoadCloseRegion()
{
	CString tt,m_style,m_style2;
	
	PCordinate pt=NULL;
	mRegions.RemoveAll();
	
	int m_reginNums=0; //���������
	int mBridgeindex=0;//����������ʼֵ
	int mTunnelindex=0;//���������ʼֵ

	m_ReginPtsLeft.RemoveAll(); //��߽����������ݵ����
	m_ReginPtsRight.RemoveAll();//�ұ߽����������ݵ����

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	float fPer=100.0/(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1);
	for (long i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{

		tt.Format("���ڹ�����·���������,����� %.2f%s",(i+1)*fPer,"%");
		pMainFrame->Set_BarText(4 , tt , 0); 
	
		//��·��ǰ���潻������
		m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
		//��·��һ���潻������
		m_style2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;
		//����������ͷ������������
		if(m_style!="������" && m_style!="����м��" &&m_style!="����յ�" \
			&&m_style!="�������"  &&m_style!="�����м��" &&m_style!="�����յ�" \
			&& m_style2!="������")
		{
			//��·��ǰ������������
			int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_L-1;
			//��·��һ������������
			int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L-1;
			
			//�����������������������Ͳ�ͬ
			if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->TW_left!=\
				myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->TW_left)
			{
				if(N1>=0) //�����·��ǰ������������>=1
				{
					for(int m=N1;m>=0;m--) //�����һ�����¿�ʼ��¼���б��µ�
					{
						for(int n=2;n>=0;n--)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].z;
							m_ReginPtsLeft.Add(pt);//�洢����������
						}
						
					}
				}
				else //��·��ǰ�������պ�������ƽ���,��ֱ�ӽ�·����µ���Ϊ�߽��
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1;
					m_ReginPtsLeft.Add(pt);//�洢����������
				}

				if(N2>=0) //�����·��һ������������>=1
				{
					for(int m=0;m<=N2;m++) //�����һ�����¿�ʼ��¼���б��µ�
					{
						for(int n=0;n<=2;n++)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].z;
							m_ReginPtsLeft.Add(pt);//�洢����������
						}
						
					}
				}
				else //��·��һ�������պ�������ƽ���,��ֱ�ӽ�·����µ���Ϊ�߽��
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1;
					m_ReginPtsLeft.Add(pt);//�洢����������
				}
				
			}
			else //��������������������������ͬ,
			{
				//������·��ǰ���淽��δ��д��ı߽����������
				if(N1>=0) //�����·��ǰ������������>=1
				{
					if(N1<=N2) //�����·��ǰ������������<=��·��һ������������,ֻ��¼��ǰ�������һ�����µ�����
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N1].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N1].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N1].Hp[2].z;
						m_ReginPtsLeft.Add(pt);//�洢����������
					}
					else //�����·��ǰ������������>��·��һ������������
					{
						for(int m=N2+1;m<=N1;m++) //��Ҫ�������¼�¼����һ�������ı������б��µ�����
						{
							for(int n=2;n>=0;n--)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[m].Hp[n].z;
								m_ReginPtsLeft.Add(pt);//�洢����������
							}
								
						}
						//ֻ��Ҫ��¼��·��һ��������һ�����µ�����
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N2].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N2].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[N2].Hp[1].z;
						m_ReginPtsLeft.Add(pt);//�洢����������
						
					}
				}
				else  //��·��ǰ�������պ�������ƽ���,��ֱ�ӽ�·����µ���Ϊ�߽��
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1;
					m_ReginPtsLeft.Add(pt);//�洢����������
				}

				//������·��һ���淽��δ��д��ı߽����������
				if(N2>=0) //�����·��һ������������>=1
				{
					if(N2<=N1)//�����·��һ������������<=��·��ǰ����������,ֻ��¼��һ�������һ�����µ�����
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N2].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N2].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N2].Hp[2].z;
						m_ReginPtsLeft.Add(pt);//�洢����������
					}
					else  //�����·��һ������������>��·��ǰ������������
					{
						for(int m=N1+1;m<=N2;m++)//��Ҫ�������ϼ�¼�ȵ�ǰ�������ı������б��µ�����
						{
							for(int n=0;n<=2;n++)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[m].Hp[n].z;
								m_ReginPtsLeft.Add(pt);//�洢����������
							}
							
						}
						//������·��һ�����Ӧ��ǰ�������һ���ı��µ�����
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N1].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N1].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[N1].Hp[1].z;
						m_ReginPtsLeft.Add(pt);//�洢����������
						
					}
				}
				else  //��·��һ�������պ�������ƽ���,��ֱ�ӽ�·����µ���Ϊ�߽��
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1;
					m_ReginPtsLeft.Add(pt);//�洢����������
				}
			}	
				
		}
		else //�������������"������",��ʾ�����������ʼ��
		{
			
			if(m_style=="������")
			{
				//��·ǰһ������������
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->Huponums_L-1;
				for(int j=N1;j>0;j--) //��¼��·ǰһ����������б��µ�
				{
					for(int k=2;k>=0;k--) //ÿһ��������3�������
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_L[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_L[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_L[j].Hp[k].z;
						m_ReginPtsLeft.Add(pt);//�洢����������
						
					}
				}

				//�õ�������ڶ��Ŵ����������������,��Ϊ�߽������
				int M=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetSize();
				for(int k=0;k<M;k++)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetAt(k)->x;
					pt->y =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetAt(k)->y;
					pt->z =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_Start.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//�洢����������
				}

				WriteRegionPts(m_reginNums,TRUE,-1);//��ǰ����������,д�����߽����������
				m_ReginPtsLeft.RemoveAll();//�������
				m_reginNums++; //���������+1
							
			}
			else if(m_style=="�������") //�������������"�������"
			{
				//�õ���������ʼ�㴦�����Կ����µ���,,��Ϊ�߽������
				int M=myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetSize();
				for(int k=0;k<M;k++)
				{
					
					pt=new Cordinate;
					pt->x =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetAt(k)->x;
					pt->y =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetAt(k)->y;
					pt->z =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_Start.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//�洢����������
					
				}
				WriteRegionPts(m_reginNums,TRUE,-1);//��ǰ����������,д�����߽����������
				m_ReginPtsLeft.RemoveAll();//�������
				m_reginNums++;//���������+1
				
			}			
			
			else if (m_style=="����յ�")//�������������"����յ�",��ʾ�����������ֹ��,��ʾ�µķ������ʼ��
			{
				
				//�õ�������ڶ��Ŵ����������������,��Ϊ�߽������
				int M=myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetSize();
				for(int k=M-1;k>=0;k--)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetAt(k)->x;
					pt->y =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetAt(k)->y;
					pt->z =myDesingScheme.TunnelInfor[m_currentSchemeIndexs].GetAt(mTunnelindex)->m_ReginPt_End.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//�洢����������
					
				}

				//��·��һ������������
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L-1;
                //������·��һ��������1�����µ���ߵ�����
				pt=new Cordinate;
				pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[2].x;
				pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[2].y;
				pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[0].Hp[2].z;
				m_ReginPtsLeft.Add(pt);//�洢����������
				
				//��¼��·��һ���������µ�2��������������б��µ�����,��Ϊ�߽������
				for(int j=1;j<=N1;j++)
				{
					for(int k=0;k<=2;k++)
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[k].z;
						m_ReginPtsLeft.Add(pt);//�洢����������
					}
				}
				mTunnelindex++; //���������ֹ��,��ʾһ�����������,�������+1
			}
			
			else if (m_style=="�����յ�") //�������������"�����յ�",��ʾ������������ֹ��,��ʾ�µķ������ʼ��
			{
				
				//�õ������������·������л��µ���������,��Ϊ�߽������
				int M=myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetSize();
				for(int k=M-1;k>=0;k--)
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetAt(k)->x;
					pt->y =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetAt(k)->y;
					pt->z =myDesingScheme.BridgeInfor[m_currentSchemeIndexs].GetAt(mBridgeindex)->m_ReginPt_End.GetAt(k)->z;
					m_ReginPtsLeft.Add(pt);//�洢����������
					
				}

				mBridgeindex++; //����������ֹ��,��ʾһ������������,����������+1
			}
			
			
		}

	}

	m_reginNums=0;
	m_ReginPtsRight.RemoveAll(); //�Ҳ�߽�����
	for ( i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		tt.Format("���ڹ�����·�Ҳ�������,����� %.2f%s",(i+1)*fPer,"%");
		pMainFrame->Set_BarText(4 , tt , 0); 

		//��·��ǰ���潻������
		m_style=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
 		//��·��һ���潻������
		m_style2=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->strJDStyle;
		
		//����������ͷ������������
		if(m_style!="������" && m_style!="����м��" &&m_style!="����յ�"\
			&&m_style!="�������"  &&m_style!="�����м��" &&m_style!="�����յ�" \
			&&m_style2!="������")
		{
			//��·��ǰ�����Ҳ������
			int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_R-1;
			//��·��һ�����Ҳ������
			int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R-1;
			//�����������������������Ͳ�ͬ
			if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->TW_right!=\
				myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->TW_right)
			{
				if(N1>=0)  //�����·��ǰ�����Ҳ������>=1
				{
					for(int m=N1;m>=0;m--) //�����һ�����¿�ʼ��¼���б��µ�
					{
						for(int n=2;n>=0;n--)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].z;
							m_ReginPtsRight.Add(pt);//�洢����������
						}
						
					}
				}
				else//��·��ǰ�����Ҳ�պ�������ƽ���,��ֱ�ӽ�·����µ���Ϊ�߽��
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2;
					m_ReginPtsRight.Add(pt);
				}
				
				if(N2>=0) //�����·��һ�����Ҳ������>=1
				{
					for(int m=0;m<=N2;m++) //�����һ�����¿�ʼ��¼���б��µ�
					{
						for(int n=0;n<=2;n++)
						{
							pt=new Cordinate;
							pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].x;
							pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].y;
							pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].z;
							m_ReginPtsRight.Add(pt);//�洢����������
						}
						
					}
				}
				else//��·��һ�����Ҳ�պ�������ƽ���,��ֱ�ӽ�·����µ���Ϊ�߽��
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2;
					m_ReginPtsRight.Add(pt);//�洢����������
				}
				
			}
			else//��������������������������ͬ
			{
				//������·��ǰ�������߽����������
				if(N1>=0) //�����·��ǰ�����Ҳ������>=1
				{
					if(N1<=N2)//�����·��ǰ�����Ҳ������<=��·��һ�����Ҳ������,ֻ��¼��ǰ�������һ�����µ�����
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N1].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N1].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N1].Hp[2].z;
						m_ReginPtsRight.Add(pt);//�洢����������
					}
					else //�����·��ǰ�����Ҳ������>��·��һ�����Ҳ������
					{
						for(int m=N2+1;m<=N1;m++) //��Ҫ�������¼�¼����һ�������ı������б��µ�����
						{
							for(int n=2;n>=0;n--)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[m].Hp[n].z;
								m_ReginPtsRight.Add(pt);//�洢����������
							}
						}
						//ֻ��Ҫ��¼��·��һ��������һ�����µ�����
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N2].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N2].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[N2].Hp[1].z;
						m_ReginPtsRight.Add(pt);//�洢����������
					}		
				}
				else //��·��ǰ�����Ҳ�պ�������ƽ���,��ֱ�ӽ�·����µ���Ϊ�߽��
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2;
					m_ReginPtsRight.Add(pt);	//�洢����������
				}
			
				//������·��һ����Ӧ��д��ı߽����������
				if(N2>=0) //�����·��һ�����Ҳ������>=1
				{				
					if(N2<=N1)//�����·��һ�����Ҳ������<=��·��ǰ���Ҳ������,ֻ��¼��һ�������һ�����µ�����
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N2].Hp[2].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N2].Hp[2].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N2].Hp[2].z;
						m_ReginPtsRight.Add(pt);//�洢����������
					}
					else//�����·��һ�����Ҳ������>��·��ǰ�����Ҳ������
					{
						for(int m=N1+1;m<=N2;m++)//��Ҫ�������ϼ�¼�ȵ�ǰ�������ı������б��µ�����
						{
							for(int n=0;n<=2;n++)
							{
								pt=new Cordinate;
								pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].x;
								pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].y;
								pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[m].Hp[n].z;
								m_ReginPtsRight.Add(pt);//�洢����������
							}
						}
						//������·��һ�����Ӧ��ǰ�������һ���ı��µ�����
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N1].Hp[1].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N1].Hp[1].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[N1].Hp[1].z;
						m_ReginPtsRight.Add(pt);//�洢����������
						
					}
				}
				else  //��·��һ�����Ҳ�պ�������ƽ���,��ֱ�ӽ�·����µ���Ϊ�߽��
				{
					pt=new Cordinate;
					pt->x =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2;
					pt->y =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2;
					pt->z =myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2;
					m_ReginPtsRight.Add(pt);//�洢����������
				}
			}
		}
		else
		{
			if(m_style=="������") //�������������"������",��ʾ�����������ʼ��
			{
				//��·ǰһ�����Ҳ������
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->Huponums_R-1;
				for(int j=N1;j>0;j--)//��¼��·ǰһ�����Ҳ����б��µ�
				{
					for(int k=2;k>=0;k--)//ÿһ��������3�������
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_R[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_R[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i-1)->HuPo_R[j].Hp[k].z;
						m_ReginPtsRight.Add(pt);//�洢����������
						
					}
				}

				WriteRegionPts(m_reginNums,FALSE,1); //��ǰ����������,д���Ҳ�߽����������
				m_ReginPtsRight.RemoveAll();//�������
				m_reginNums++;//���������+1
				
			}
			else if(m_style=="�������")//�������������"�������"
			{
				WriteRegionPts(m_reginNums,FALSE,1);//��ǰ����������,д���Ҳ�߽����������
				m_ReginPtsRight.RemoveAll();//�������
				m_reginNums++;//���������+1
				
			}			
			else if(m_style=="����յ�")//�������������"����յ�",��ʾ�����������ֹ��,��ʾ�µķ������ʼ��
			{

				//�õ�������ڶ��Ŵ����������������,��Ϊ�߽������
				int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R-1;
				for(int j=1;j<=N1;j++)
				{
					for(int k=0;k<=2;k++)
					{
						pt=new Cordinate;
						pt->x =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].x;
						pt->y =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].y;
						pt->z =myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[k].z;
						m_ReginPtsRight.Add(pt);//�洢����������
					}
				}
				mTunnelindex++;//���������ֹ��,��ʾһ�����������,�������+1
			}
			
			else if (m_style=="�����յ�")//�������������"�����յ�",��ʾ������������ֹ��,��ʾ�µķ������ʼ��
			{
				mBridgeindex++;//����������ֹ��,��ʾһ������������,����������+1
			}
		}
		
	}

	//�Բ�����ı��������������
	for(i=0;i<mRegions.GetSize();i++)
	{
		if(mRegions.GetAt(i)->ReginPts.GetSize()<=1) //�������������ݵ�<=1
		{
			mRegions.RemoveAt(i);//�Ƴ�
		}
	}
}

//���ƾ�����·����άģ�����ά����TIN
void CT3DSystemView::DrawTerrainDelaunay()
{
	
	if(b_haveTerrainZoomroadList==TRUE)   //����ѳɹ�����·��άģ�͵���ʾ�б�
	{
		glCallList(m_TerrainZoomroadList);
		return;
	}


	if(m_currentSchemeIndexs<0) //�����ǰ��·��������<0������
		return;
	
	if(	b_haveGetRegion==TRUE) //����Ѿ���ȡ��·������򣬷���
		return;
	//û�о�����·��ά��ģ����
	if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()<=1)
		return;
	if(myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()<=1)
		return;
	
	BeginWaitCursor();
	
	CString m_style,m_style2;
	long i;

	//������·��ά��ģ���Ƿ����˵���TINģ�͵���ʾ�б�
	glNewList(m_TerrainZoomroadList,GL_COMPILE_AND_EXECUTE);
	
	glPushAttrib(GL_TEXTURE_BIT|GL_POLYGON_BIT);
	glDisable(GL_TEXTURE_2D); //�ر�����
	glLineWidth(2.0); //�����߿�
	glColor3f(0.2,0,1.0); //������ɫ
	
	GetRoadCloseRegion();//��ȡ�������
	BuildTerrainRegionInfo(); //����ÿ�����ο���ͬ�����������е������ݼ�
	m_BlockTriInfos.RemoveAll(); //���ο���������Ϣ���
	
	CString tt;
	float fPer=100.0/m_BlockLSPts.GetSize();
	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	for( i=0;i<m_BlockLSPts.GetSize();i++)   
	{
		tt.Format("���ڻ��Ƶ���TINģ��,����� %.2f%s",(i+1)*fPer,"%");
		pMainFrame->Set_BarText(4 , tt , 0); 
		
		DrawTerrainTIN(i); //��TIN��ʽ���Ƶ��ο�i
		tempBlockTriInfos=new BlockTriInfos;
		for_each(m_Triangles.begin(), m_Triangles.end(), GetBlockTriangles(i));
		AddBlcokTri(i,m_BlockLSPts.GetAt(i)->mDemBlockRow,m_BlockLSPts.GetAt(i)->mDemBlockCol);//���뵱ǰ���ο�������������(ͬʱҪ�޳�λ����·������������������)
	}
	glEndList();
	b_haveTerrainZoomroadList=TRUE;//��·��ά��ģ���Ƿ����˵���TINģ�͵���ʾ�б�
	EndWaitCursor();
	MessageBox("��ģ���","��·��ά��ģ",MB_ICONINFORMATION);
	pMainFrame->Set_BarText(4 , "���ص�����Ӱ�������������!" , 0); 
}

//���߽����������д��������
void CT3DSystemView::WriteRegionPts(int index, BOOL bAddorAppend, int mLeftorRight)
{
	PRegions tempregion=new Regions;
	PCordinate pt=NULL;
	
	if(bAddorAppend==TRUE)  //��������ӱ߽�㣬mRegions����������Ԫ��
	{
		tempregion->index=index; //�����������
		for(long i=0;i<m_ReginPtsLeft.GetSize();i++)//������߽������
		{
			pt=new Cordinate;
			pt->x=m_ReginPtsLeft.GetAt(i)->x;
			pt->y=m_ReginPtsLeft.GetAt(i)->y;
			pt->z=m_ReginPtsLeft.GetAt(i)->z;
			tempregion->ReginPts.Add(pt);//�洢����ʱ������
		}
		mRegions.Add(tempregion);//����߽�����
	}
	else if(bAddorAppend==FALSE)  //��������������ݣ�ֱ����mRegions��������λ��д������
	{
		//�����ұ߽������
		for(long i=m_ReginPtsRight.GetSize()-1;i>=0;i--)
		{
			pt=new Cordinate;
			pt->x=m_ReginPtsRight.GetAt(i)->x;
			pt->y=m_ReginPtsRight.GetAt(i)->y;
			pt->z=m_ReginPtsRight.GetAt(i)->z;
			mRegions.GetAt(index)->ReginPts.Add(pt);//�����ұ߽������
		}
		m_ReginPtsRight.RemoveAll();//�ұ߽���������
		
		
	}
}

//���ݷ������߽��ϵ����ݵ㣬����÷������Խ�ĵ��ο�ID��
//���������Խ������ο飬�����¼�ĵ��ο�ID��Ҳ�ж��
void CT3DSystemView::GetRegionID(long index)
{
	double x,y;
	int ID;
	mRegions.GetAt(index)->GridID.RemoveAll();
	for(long i=0;i<mRegions.GetAt(index)->ReginPts.GetSize();i++)
	{
		
		x=mRegions.GetAt(index)->ReginPts.GetAt(i)->x;//�������߽��ϵ����ݵ��x����	
		y=-mRegions.GetAt(index)->ReginPts.GetAt(i)->z;//�������߽��ϵ����ݵ��y����
		
		ID=GetBlockID(x,y);	//����x,y������ȡ�����ڵĵ��ο��ID��
		
		bool bhaveExit=FALSE; //��ʼ��ʶΪFALSE
		for(int k=0;k<mRegions.GetAt(index)->GridID.GetSize();k++)
		{
			int mid=mRegions.GetAt(index)->GridID.GetAt(k);
			if(ID==mid) //�����õ��ο�ID���ڼ�¼�е�ID����ͬ������ԣ����ټ�¼
			{
				bhaveExit=TRUE;
				break;
			}
		}
		if(bhaveExit==FALSE) ////�����õ��ο�ID�������м�¼�е�ID�Ų�ͬ�����¼
			mRegions.GetAt(index)->GridID.Add(ID);//��¼ID��
	}
}

//����ÿ�����ο���ͬ�����������е������ݼ�
void CT3DSystemView::BuildTerrainRegionInfo()
{
	//���û�е�������
	if(theApp.m_BlockRows*theApp.m_BlockCols<=0)
		return;

	long i,j;
	//����ÿ��������������С���x,y����
	for( i=0;i<mRegions.GetSize();i++)
	{
		GetRegionID(i);//�õ��������ID
		double minx,miny,maxx,maxy;
		minx=miny=999999999;
		maxx=maxy=-999999999;
		//���������,��С����
		for( j=0;j<mRegions.GetAt(i)->ReginPts.GetSize();j++)
		{
			if(minx>mRegions.GetAt(i)->ReginPts.GetAt(j)->x)
				minx=mRegions.GetAt(i)->ReginPts.GetAt(j)->x;
			if(miny>-mRegions.GetAt(i)->ReginPts.GetAt(j)->z)
				miny=-mRegions.GetAt(i)->ReginPts.GetAt(j)->z;
			if(maxx<mRegions.GetAt(i)->ReginPts.GetAt(j)->x)
				maxx=mRegions.GetAt(i)->ReginPts.GetAt(j)->x;
			if(maxy<-mRegions.GetAt(i)->ReginPts.GetAt(j)->z)
				maxy=-mRegions.GetAt(i)->ReginPts.GetAt(j)->z;
			
		}
		mRegions.GetAt(i)->minx=minx;
		mRegions.GetAt(i)->miny=miny;
		mRegions.GetAt(i)->maxx=maxx;
		mRegions.GetAt(i)->maxy=maxy;
	}
	
	b_haveGetRegion=TRUE; //��ʶ�Ѽ���������ΪTRUE

	//���¶��������С���������ڴ�
	mBlockReginInforMe=new CArray<PBlockReginInforMe,PBlockReginInforMe>[theApp.m_BlockRows*theApp.m_BlockCols];
	m_BlockLSPts.RemoveAll();//���

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
	float fper=100.0/(theApp.m_BlockRows*theApp.m_BlockCols);
	CString tt;
	for(i=1;i<=theApp.m_BlockRows;i++)
	{
		for( j=1;j<=theApp.m_BlockCols;j++)
		{
			tt.Format("���ڼ���ÿ�����ο���ͬ�����������е������ݼ�,����� %.2f%s",i*j*fper,"%");
			pMainFrame->Set_BarText(4 , tt , 0); 
			
			GetBlockInregion(i,j); //�õ����ο���������Ϣ
			WriteBlockLsPts(i,j);//�����ο���������Ϣд��
		}
	}
}

//���Ƶ��ο�����������
void CT3DSystemView::DrawTerrainTIN(long blockIndex)
{
	m_Vertices.clear(); //�������
	m_Triangles.clear();//���������
	double x,y,z;
	
	CDelaunay d; //����CDelaunay����
	//��ȡĳ�����ο���������Ч�������ݵ�,��������������Ĺ���
	for(long j=0;j<m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetSize();j++)
	{
		x=m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetAt(j)->x; //x����
		y=-m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetAt(j)->z;//y����
		z=m_BlockLSPts.GetAt(blockIndex)->ReginPts.GetAt(j)->y;//z����(�߳�)
		if(z!=theApp.m_DEM_IvalidValue) //����߳�����Чֵ,������������������
			m_Vertices.insert(vertex(x, y,z));
	}
	d.Triangulate(m_Vertices, m_Triangles);//���ݵ������ݵ�(m_Vertices�д洢)��������������
}

//���뵱ǰ���ο�������������(ͬʱҪ�޳�λ����·������������������)
void CT3DSystemView::AddBlcokTri(int blockIndex, int DemblcokRow, int DemblcokCol)
{
	for(long i=0;i<tempBlockTriInfos->TriPts.GetSize();i++)
	{
		//�жϵ��ο�TIN�������Ƿ�λ�ڵ��ο��ڷ��������
		BOOL bOk=GetTriOutRegion(\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt1.x,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt1.y,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt2.x,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt2.y,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt3.x,\
			tempBlockTriInfos->TriPts.GetAt(i)->Pt3.y,\
			blockIndex);
		if(bOk==TRUE) //�����������λ�ڵ��ο��ڷ��������,��x����=-9999����ʶ
			tempBlockTriInfos->TriPts.GetAt(i)->Pt1.x=-9999;
	}
	
	tempBlockTriInfos->mDemBlockRow=DemblcokRow;//��ǰ���ο���к�
	tempBlockTriInfos->mDemBlockCol=DemblcokCol;//��ǰ���ο���к�
	m_BlockTriInfos.Add(tempBlockTriInfos);//���뵱ǰ���ο����������Ϣ
}

//�жϵ��ο�TIN�������Ƿ�λ�ڵ��ο��ڷ��������
BOOL CT3DSystemView::GetTriOutRegion(double x1, double y1, double x2, double y2, double x3, double y3, int blockIndex)
{
	Point *polygon;	
	Point pt;
	bool b1,b2,b3;	
	int m_a1,m_a2,m_a3;
	m_a1=m_a2=m_a3=0; //��ʼ��ʶΪ0

	//�Ե�ǰ���ο��ڹ��еķ����������ж�
	//mBlockReginInforMe[blockIndex].GetSize()����ǰ���ο��ڹ��еķ����������
	for(int i=0;i<mBlockReginInforMe[blockIndex].GetSize();i++)
	{
		//��������ε�������ȫ��λ�ڷ�����������С���α߽�֮��
		//��������α�λ�ڷ��������,�������޳�
		if((x1<mBlockReginInforMe[blockIndex].GetAt(i)->minx && \
			x2<mBlockReginInforMe[blockIndex].GetAt(i)->minx && \
			x3<mBlockReginInforMe[blockIndex].GetAt(i)->minx)|| \
			(x1>mBlockReginInforMe[blockIndex].GetAt(i)->maxx && \
			x2>mBlockReginInforMe[blockIndex].GetAt(i)->maxx && \
			x3>mBlockReginInforMe[blockIndex].GetAt(i)->maxx)|| \
			(y1<mBlockReginInforMe[blockIndex].GetAt(i)->miny && \
			y2<mBlockReginInforMe[blockIndex].GetAt(i)->miny && \
			y3<mBlockReginInforMe[blockIndex].GetAt(i)->miny)|| \
			(y1>mBlockReginInforMe[blockIndex].GetAt(i)->maxy && \
			y2>mBlockReginInforMe[blockIndex].GetAt(i)->maxy && \
			y3>mBlockReginInforMe[blockIndex].GetAt(i)->maxy))
		{
			m_a1=m_a2=m_a3=0;//3�㶼λ�ڷ�������ڣ������ʶȫΪ0
		}
		else
		{
			//��ȡ����������еı߽��
			long M=mBlockReginInforMe[blockIndex].GetAt(i)->ReginPts.GetSize();
			polygon=new Point[M];
			for(long j=0;j<M;j++)
			{
				polygon[j].x=mBlockReginInforMe[blockIndex].GetAt(i)->ReginPts.GetAt(j)->x;
				polygon[j].y=-mBlockReginInforMe[blockIndex].GetAt(i)->ReginPts.GetAt(j)->z;
			}
			
			
			pt.x=x1; pt.y=y1;
			b1=mCalF.InPolygon(polygon,M,pt);//�жϵ�(x1,y1)�Ƿ�λ�ڸ÷��������
			if(b1==true) //���λ��
				m_a1=1;
			
			pt.x=x2; pt.y=y2;
			b2=mCalF.InPolygon(polygon,M,pt);//�жϵ�(x2,y2)�Ƿ�λ�ڸ÷��������
			if(b2==true)//���λ��
				m_a2=1;
			
			pt.x=x3; pt.y=y3;//�жϵ�(x3,y3)�Ƿ�λ�ڸ÷��������
			b3=mCalF.InPolygon(polygon,M,pt);
			if(b3==true)//���λ��
				m_a3=1;
			
			//���3�㶼λ���ڲ����ڷ������߽���,��Ҫ��һ���ж�
			//��Ϊ���3�㶼λ�ڷ������߽���,��������ʵ������λ�ڷ������֮�� ,����Ҫɾ��
			if(m_a1==1 && m_a2==1 && m_a3==1)
			{
				pt.x=(x1+x2)/2; pt.y=(y1+y2)/2; //(x1,y1)��(x2,y2)�е�����
				b1=mCalF.InPolygon(polygon,M,pt);//�ж��е��λ�ڸ÷��������
				if(b1==false)//�����λ��
					m_a1=0;
				
				if(m_a1==1) //���(x1,y1)��(x2,y2)�е�����λ�ڸ÷��������
				{
					pt.x=(x2+x3)/2; pt.y=(y2+y3)/2;//(x2,y2)��(x3,y3)�е�����
					b1=mCalF.InPolygon(polygon,M,pt);//�ж��е��λ�ڸ÷��������
					if(b2==false)//�����λ��
						m_a2=0;
				}
				
				if(m_a1==1 && m_a2==1) //���(x1,y1)��(x2,y2)�Լ�(x2,y2)��(x3,y3)���е�����λ�ڸ÷��������
				{
					pt.x=(x1+x3)/2; pt.y=(y1+y3)/2;//(x1,y1)��(x3,y3)�е�����
					b3=mCalF.InPolygon(polygon,M,pt);
					if(b3==false)//�����λ��
						m_a3=0;
				}
			} 
			
			
			
			if(m_a1+m_a2+m_a3>=3) //��������ε�3���Լ������е㶼λ�ڷ��������, �����ά��λ�ڷ��������
			{
				return TRUE; //����TURE,��ʾ������λ�ڷ��������,��Ҫ�޳�
				break;
				
			}
		}
	}
	
	return FALSE;//����FALSE,��ʾ�����β�λ�ڷ��������,����Ҫ�޳�
}

//�õ����ο���������Ϣ
void CT3DSystemView::GetBlockInregion(int blockRow, int blockCol)
{
	int bInCur,bInPre;
	double minx,miny,maxx,maxy;
	double block_minx,block_miny,block_maxx,block_maxy;

	/*
					-------------(block_maxx,block_maxy)
					|        	|
					|        	|
					|        	|
					|        	|
					|        	|
					-------------
				(block_minx,block_miny)
	*/

	block_minx=(blockCol-1)*theApp.m_Dem_BlockWidth;//���ο���Сx����
	block_maxx=blockCol*theApp.m_Dem_BlockWidth;//���ο����x����
	block_miny=(blockRow-1)*theApp.m_Dem_BlockWidth;//���ο���Сy����
	block_maxy=blockRow*theApp.m_Dem_BlockWidth;//���ο����y����
	
	int Mnus;
	PCordinate pt;
	Point  edgePts[4];
	
	long iNdex=(blockRow-1)*theApp.m_BlockCols+(blockCol-1);//�������кż�����ο������е��ο��е�����
	PBlockReginInforMe tempReginInforMe;
	
	for(long i=0;i<mRegions.GetSize();i++)
	{
		tempReginInforMe=new BlockReginInforMe;
		//���
		//(1)��ǰ����������Сx����>=���ο���Сx����
		//(2)��ǰ�����������x����<=���ο����x����
		//(3)��ǰ����������Сy����>=���ο���Сy����
		//(4)��ǰ�����������y����<=���ο����y����
		///�ĸ�����ȫ����ʱ,��ʾ�÷����������ȫλ�ڵ�ǰ���ο���
		if(mRegions.GetAt(i)->minx>=block_minx &&\
			mRegions.GetAt(i)->maxx<=block_maxx&&\
			mRegions.GetAt(i)->miny>=block_miny &&\
			mRegions.GetAt(i)->maxy<=block_maxy)
		{
			//��������������ݵ�
			tempReginInforMe->ReginPts.Copy(mRegions.GetAt(i)->ReginPts);
			tempReginInforMe->minx=mRegions.GetAt(i)->minx;
			tempReginInforMe->miny=mRegions.GetAt(i)->miny;
			tempReginInforMe->maxx=mRegions.GetAt(i)->maxx;
			tempReginInforMe->maxy=mRegions.GetAt(i)->maxy;
			mBlockReginInforMe[iNdex].Add(tempReginInforMe);//
		}
		else 
		{
			//���
			//(1)��ǰ����������Сx����>���ο����x����
			//(2)��ǰ�����������x����<���ο���Сx����
			//(3)��ǰ����������Сy����>���ο����y����
			//(4)��ǰ�����������y����<���ο���Сy����
			//�ĸ�������������֮һʱ,�Ƿ��������ز�λ�ڵ��ο���
			if(mRegions.GetAt(i)->minx>block_maxx ||
				mRegions.GetAt(i)->maxx<block_minx||\
				mRegions.GetAt(i)->miny>block_maxy ||
				mRegions.GetAt(i)->maxy<=block_miny)
			{
			//	Sleep(0);
			}
			else
			{
				bInCur=bInPre=1;
				
				for(long j=0;j<mRegions.GetAt(i)->ReginPts.GetSize();j++)
				{
					double x=mRegions.GetAt(i)->ReginPts.GetAt(j)->x;
					double y=-mRegions.GetAt(i)->ReginPts.GetAt(j)->z;
					double z=mRegions.GetAt(i)->ReginPts.GetAt(j)->y;
				    //�����(x,y,z)λ�ڵ��ο���(�����ڵ��ο�߽���)
					if(x>=block_minx &&	x<=block_maxx&&\
						y>=block_miny && y<=block_maxy)
					{
						bInCur=1; //��ʶ�������߽��Pi(x,y,z)λ�ڵ��ο���
						
						if(j>0 && bInCur*bInPre==-1)
						{
							//�������������뵱ǰ���ο������߽��ߵĽ�������,��õĽ�������
							//Ҳ����Ϊ�õ��ο�����ݵ������λ���.
							GetBlockEdgeJd(block_minx,block_miny,block_maxx,block_maxy,i,j,&Mnus,edgePts);
							for(int k=0;k<Mnus;k++)
							{
								pt=new Cordinate;
								pt->x=edgePts[k].x;pt->y=edgePts[k].y;pt->z=edgePts[k].z;
								tempReginInforMe->ReginPts.Add(pt);//��¼���ݵ�
							}
						}
						
						pt=new Cordinate;
						pt->x=x;pt->y=z;pt->z=-y;//����任
						tempReginInforMe->ReginPts.Add(pt);//��¼���ݵ�
						
					}
					else 
					{
						bInCur=-1;//��ʶ�������߽��Pi(x,y,z)λ�ڵ��ο��� 
						if(j>0 && bInCur*bInPre==-1)
						{
							//�������������뵱ǰ���ο������߽��ߵĽ�������,��õĽ�������
							//Ҳ����Ϊ�õ��ο�����ݵ������λ���.
							GetBlockEdgeJd(block_minx,block_miny,block_maxx,block_maxy,i,j,&Mnus,edgePts);
							for(int k=0;k<Mnus;k++) //��λ�ڵ��ο��ڵĲ��ֱ߽��洢
							{
								pt=new Cordinate;
								pt->x=edgePts[k].x;pt->y=edgePts[k].y;pt->z=edgePts[k].z;
								tempReginInforMe->ReginPts.Add(pt);//��¼���ݵ�
							}
						}
						
					}
					bInPre=bInCur;
				}

				//������С���x,y����
				minx=miny=999999999;
				maxx=maxy=-999999999;
				for(long k=0;k<tempReginInforMe->ReginPts.GetSize();k++)
				{
					if(minx>tempReginInforMe->ReginPts.GetAt(k)->x)
						minx=tempReginInforMe->ReginPts.GetAt(k)->x;
					if(miny>-tempReginInforMe->ReginPts.GetAt(k)->z)
						miny=-tempReginInforMe->ReginPts.GetAt(k)->z;
					if(maxx<tempReginInforMe->ReginPts.GetAt(k)->x)
						maxx=tempReginInforMe->ReginPts.GetAt(k)->x;
					if(maxy<-tempReginInforMe->ReginPts.GetAt(k)->z)
						maxy=-tempReginInforMe->ReginPts.GetAt(k)->z;
					
				}
				
				tempReginInforMe->minx=minx;
				tempReginInforMe->miny=miny;
				tempReginInforMe->maxx=maxx;
				tempReginInforMe->maxy=maxy;
				mBlockReginInforMe[iNdex].Add(tempReginInforMe);//��¼���������Ϣ
			}
		}
	}
}

//д����ο����������
void CT3DSystemView::WriteBlockLsPts(long Blcokrow, long Blcokcol)
{
	PBlockLSPts tempBlockLSPts=new BlockLSPts;
	
	tempBlockLSPts->ReginPts.RemoveAll();
	
	PCordinate pt=new Cordinate;
	double x,y,z;
	long INX,mTerrainBlockID;
	mTerrainBlockID=(Blcokrow-1)*theApp.m_BlockCols+Blcokcol-1;//���ο��ID��

    //���ݵ��ο�ķֿ��С,���ν����е������ݵ�д����ο�������������
	for(int i=0;i<theApp.m_Dem_BlockSize;i++)
	{
		for (int j=0;j<theApp.m_Dem_BlockSize;j++)
		{
			
			x=(Blcokcol-1)*theApp.m_Dem_BlockWidth+j*theApp.m_Cell_xwidth;//ת�����X����
			y=(Blcokrow-1)*theApp.m_Dem_BlockWidth+i*theApp.m_Cell_ywidth;//ת�����Y����
			
			INX=i*theApp.m_Dem_BlockSize+j;
			z=m_pHeight_My[mTerrainBlockID][INX];//��ö�Ӧ�ĸ߳�ֵ
			
            pt=new Cordinate;
			pt->x =x;
			pt->y=z;
			pt->z =-y;
			tempBlockLSPts->ReginPts.Add(pt);//�������ݵ�
		}
	}
	
	//����������λ�ڵ��ο������ο�߽��ཻ�����ݵ�
	long iNdex=(Blcokrow-1)*theApp.m_BlockCols+(Blcokcol-1);
	for(int k=0;k<mBlockReginInforMe[iNdex].GetSize();k++)
	{
		tempBlockLSPts->ReginPts.Append(mBlockReginInforMe[iNdex].GetAt(k)->ReginPts);
	}
	
	tempBlockLSPts->mDemBlockRow=Blcokrow; //��ǰ���ο��Ӧ���к�
	tempBlockLSPts->mDemBlockCol=Blcokcol; //��ǰ���ο��Ӧ�����
	m_BlockLSPts.Add(tempBlockLSPts);//��ǰ���ο���������ݵ�
	
}

//�������������뵱ǰ���ο������߽��ߵĽ�������,��õĽ�������
//Ҳ����Ϊ�õ��ο�����ݵ������λ���.
void CT3DSystemView::GetBlockEdgeJd(double block_minx, double block_miny, double block_maxx, double block_maxy, long RegionsIndex, long ReginPtsIndex, int *jdNus, Point edgePts[])
{
	Point p1,p2,q1,q2,crossPoint;
	
	int m=0; //��ʼ������Ϊ0
	bool bCross=false; //��ʼ���ཻ
	
	//��ǰ��������������߽��
	q1.x=mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex)->x;
	q1.y=-mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex)->z;
	q2.x=mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex-1)->x;
	q2.y=-mRegions.GetAt(RegionsIndex)->ReginPts.GetAt(ReginPtsIndex-1)->z;
	
	
	//���ο��ϱ߽���
	p1.x =block_minx;p1.y=block_maxy;
	p2.x =block_maxx;p2.y=block_maxy;
	
	//������p1p2ֱ����q1q2ֱ���Ƿ��ཻ
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true)  //����ཻ,��������ο��ϱ߽����ཻ
	{
		edgePts[m].x=crossPoint.x; //��¼����x����
		edgePts[m].z=-crossPoint.y;//��¼����z����
		//��DEM���ڲ���߳�,��ý���y����
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++; //��������1
	}
	
	//���ο���߽���
	p1.x =block_minx;p1.y=block_maxy;
	p2.x =block_minx;p2.y=block_miny;
	
	//������p1p2ֱ����q1q2ֱ���Ƿ��ཻ
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true) //����ཻ,��������ο���߽����ཻ
	{
		edgePts[m].x=crossPoint.x;//��¼����x����
		edgePts[m].z=-crossPoint.y;//��¼����z����
		//��DEM���ڲ���߳�,��ý���y����
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++;//��������1
	}
	
	//���ο��±߽���
	p1.x =block_minx;p1.y=block_miny;
	p2.x =block_maxx;p2.y=block_miny;
	
	//������p1p2ֱ����q1q2ֱ���Ƿ��ཻ
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true) //����ཻ,��������ο��±߽����ཻ
	{
		edgePts[m].x=crossPoint.x;//��¼����x����
		edgePts[m].z=-crossPoint.y;//��¼����z����
		//��DEM���ڲ���߳�,��ý���y����
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++;//��������1
	}
	
	//���ο��ұ߽���
	p1.x =block_maxx;p1.y=block_maxy;
	p2.x =block_maxx;p2.y=block_miny;

	//������p1p2ֱ����q1q2ֱ���Ƿ��ཻ
	crossPoint =mCalF.GetCrossPoint(p1,p2,q1,q2,&bCross);
	if(bCross==true)//����ཻ,��������ο��ұ߽����ཻ
	{
		edgePts[m].x=crossPoint.x;
		edgePts[m].z=-crossPoint.y;
		//��DEM���ڲ���߳�,��ý���y����
		edgePts[m].y=m_demInsert.GetHeightValue(edgePts[m].x+theApp.m_DemLeftDown_x,-edgePts[m].z+theApp.m_DemLeftDown_y,2);
		m++;//��������1
	}
	
	*jdNus=m; //������ý�����		
}



//���ݵ��ε��x,y �˲ļ���õ��ε����������ο�ID��
int CT3DSystemView::GetBlockID(double x, double y)
{
	//	theApp.m_BlockCols//DEM��������
	//	theApp.m_BlockRows;//DEM��������
	//	theApp.m_Dem_BlockWidth//ÿ��DEM����
	//	��������,�м��㷽��
	
	int mrow,mcol;
	if((y/theApp.m_Dem_BlockWidth)==(int)(y/theApp.m_Dem_BlockWidth))
		mrow=y/theApp.m_Dem_BlockWidth;
	else
		mrow=(int)(y/theApp.m_Dem_BlockWidth)+1;
	if(mrow<=0) //����к�<=0,�к�=1
		mrow=1;
	
	if((x/theApp.m_Dem_BlockWidth)==(int)(x/theApp.m_Dem_BlockWidth))
		mcol=x/theApp.m_Dem_BlockWidth;
	else
		mcol=(int)(x/theApp.m_Dem_BlockWidth)+1;
	if(mcol<=0)//����к�<=0,�к�=1
		mcol=1;
	int ID=(mrow-1)*theApp.m_BlockCols+mcol;
	return ID; //����ID��
}

//���÷���·��
void CT3DSystemView::OnPathManuinput() 
{
	m_ShowFlyPath=TRUE;  //��ʶ�Ƿ���ʾ����·��
	m_QueryType=SELECTFLYPATH;//���з���·��ѡ��
	m_FlayPath.RemoveAll();//�洢���з���·�������������
}

//���Ʒ���·��
void CT3DSystemView::DrawFlyPath()
{
	//�����ʾ����·�����ҷ���·���������>1,�Ż��Ʒ���·��
	if(m_ShowFlyPath==TRUE  && m_FlayPath.GetSize()>1)//���з���·��ѡ��
	{
		glPushMatrix(); //ѹ������ջ
		glDisable(GL_TEXTURE_2D);//�ر�����(������·������������)
		glLineWidth(3.0);//���÷���·���߿�
		glColor3f(0,1,1); //���÷���·����ɫ
		if(m_ViewType==GIS_VIEW_ORTHO)	//��������ͶӰģʽ�µķ���·��
		{
			glBegin(GL_LINE_STRIP); //�����߷�ʽ���Ʒ���·��
			for(int i=0;i<m_FlayPath.GetSize();i++)
				glVertex2f(GetOrthoX(m_FlayPath.GetAt(i)->x),GetOrthoY(-m_FlayPath.GetAt(i)->z));
			glEnd();
			
			//�ڷ���·��ÿ������㴦���Ƶ�Բ���Ա�ʶÿ�������
			for(i=0;i<m_FlayPath.GetSize();i++)
			{
				glColor3f(0,0.5,0.5); //�����ɫ
				glPointSize(4.0); //��Ĵ�С
				glBegin(GL_POINTS);
					glVertex2f(GetOrthoX(m_FlayPath.GetAt(i)->x),GetOrthoY(-m_FlayPath.GetAt(i)->z));
				glEnd();
			}
			glPointSize(0); //�ָ����Ĭ�ϴ�С
			
		}
		else  if(m_ViewType==GIS_VIEW_PERSPECTIVE) //����͸��ͶӰģʽ�µķ���·��
		{
			glBegin(GL_LINE_STRIP);
			for(int i=0;i<m_FlayPath.GetSize();i++)
				glVertex3f(m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
			glEnd();
			
		}
		glEnable(GL_TEXTURE_2D); //��������
		glLineWidth(1.0); //�ָ��߿�
		glColor3f(1,1,1); //�ָ���ɫ
		glPopMatrix(); //���������ջ
	}
}

//·�������ֵ
void CT3DSystemView::OnFlppathInterpolation() 
{
	float m_InsertDdis=10; //��ֵ��� 
	
	double x1,y1,z1,x2,y2,z2;
	PCordinate ppt ;  
	
	m_FlayPathTempPts.RemoveAll(); //��ʱ�洢����·��
	for(int i=0;i<m_FlayPath.GetSize()-1;i++)
	{
		x1=m_FlayPath.GetAt(i)->x; //��ȡ����·����ǰ���x����
		y1=m_FlayPath.GetAt(i)->y; //��ȡ����·����ǰ���y����
		z1=m_FlayPath.GetAt(i)->z; //��ȡ����·����ǰ���z����
		
		x2=m_FlayPath.GetAt(i+1)->x; //��ȡ����·����һ���x����
		y2=m_FlayPath.GetAt(i+1)->y;//��ȡ����·����һ���y����
		z2=m_FlayPath.GetAt(i+1)->z;//��ȡ����·����һ���z����
		
		if(i==0) //����Ƿ���·������ʼ��,���¼
		{
			ppt = new Cordinate;
			ppt->x=x1;
			ppt->y=y1;
			ppt->z=z1;
			m_FlayPathTempPts.Add(ppt);
		}
		
		//�������·����ǰ������һ��ľ���
		double L=myDesingScheme.GetDistenceXYZ(x1,y1,z1,x2,y2,z2);
		int M=L/m_InsertDdis; //����Ӧ�ڲ���������
		for(int j=1;j<=M;j++)
		{
			//�����ڲ������µ��ڲ�����ά����
			ppt = new Cordinate;
			ppt->x=x1+j*m_InsertDdis/L*(x2-x1);
			ppt->z=z1+j*m_InsertDdis/L*(z2-z1);
			ppt->y=m_demInsert.GetHeightValue(ppt->x+theApp.m_DemLeftDown_x,-ppt->z+theApp.m_DemLeftDown_y,2);
			m_FlayPathTempPts.Add(ppt); //��¼�ڲ������
			
		}
		
		ppt = new Cordinate;
		ppt->x=x2;
		ppt->y=y2;
		ppt->z=z2;
		m_FlayPathTempPts.Add(ppt); //������·����һ�������Ҳ��¼����
		
	}
	
	m_FlayPath.RemoveAll(); //����·���������
	for(i=0;i<m_FlayPathTempPts.GetSize();i++)
	{
		ppt = new Cordinate;
		ppt->x=m_FlayPathTempPts.GetAt(i)->x;
		ppt->y=m_FlayPathTempPts.GetAt(i)->y;
		ppt->z=m_FlayPathTempPts.GetAt(i)->z;
		m_FlayPath.Add(ppt); //����������·������
		
	}
	OnDraw(GetDC()); //ˢ����ά����
	MessageBox("·�������ֵ���!","·�������ֵ",MB_ICONINFORMATION);	
}

//�������·��
void CT3DSystemView::OnFlypathSave() 
{
	CString 	NeededFile;
	char 		FileFilter[] = "����·��(*.pth)|*.pth||";

	//�����ļ��Ի�������
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog FileDialogBoxFile(FALSE, NULL, 0, FileDialogFlag, FileFilter, this);
	FileDialogBoxFile.m_ofn.lpstrTitle = "�������·���ļ�";
	char		FileName[200];
	
	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK ) //����Ի���ɹ���
	{	
		NeededFile = FileDialogBoxFile.GetPathName(); //�õ��ļ���
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(),"pth")!=0) 
			strcat(FileName,".pth"); //��ӷ���·���ļ���չ��
		
		if(FlyPathSave(FileName)) //�������·������ɹ�
			MessageBox("·���㱣�����","�������·��",MB_ICONWARNING);
		
	}			
}

//����·������
int CT3DSystemView::FlyPathSave(char *pathfile)
{
	FILE	*fpw;
	char	message[200];
	
	if((fpw = fopen(pathfile, "w")) == NULL)//���д���ļ�ʧ��
  	{ 
		sprintf(message, "�ļ� %s ������Ч", pathfile);
		MessageBox(message,"�������·�����굽�ļ�",MB_ICONWARNING);
		return 0; //����ʧ��
  	}
	
	
	fprintf(fpw, "%d\n", m_FlayPath.GetSize());//д�����·�����������
	for(int i=0;i<m_FlayPath.GetSize();i++)
	{
		//���ļ�fpw��д�����·����������ά����
		fprintf(fpw, "%lf,%lf,%lf\n",m_FlayPath.GetAt(i)->x, m_FlayPath.GetAt(i)->y, m_FlayPath.GetAt(i)->z);
		
	}
	
	fclose(fpw); //�ر��ļ�
	
	return 1;  //���سɹ�
}

//�򿪷���·��
void CT3DSystemView::OnFlyOpenpath() 
{
	CString 	NeededFile;
	char 		FileFilter[] = "����·��(*.pth)|*.pth||";
	//�����ļ��Ի�������
	DWORD 		FileDialogFlag = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog FileDialogBoxFile(TRUE, NULL, 0, FileDialogFlag, FileFilter, this);
	FileDialogBoxFile.m_ofn.lpstrTitle = "�򿪷���·���ļ�";
	char		FileName[200];
	
	CString tt[3];
	if( FileDialogBoxFile.DoModal() == IDOK )//����Ի���ɹ���
	{	
		NeededFile = FileDialogBoxFile.GetPathName();//�õ��ļ���
		sprintf(FileName, "%s", NeededFile);
		if(strcmp(FileDialogBoxFile.GetFileExt(),"pth")!=0) 
			strcat(FileName,".pth");//��ӷ���·���ļ���չ��
		
		if(FlyPathRead(FileName)) //��ȡ����·���ļ����ݶ�̬������
			MessageBox("��·�������","��ʾ",MB_ICONWARNING);
		if(m_FlayPath.GetSize()>1) //�������·�������������>1
		{
			m_ShowFlyPath=TRUE; //��ʾ����·��
			m_PathFlag=TRUE; //��ʶ����·���򿪳ɹ�
		}
		else
			m_PathFlag=FALSE;//��ʶ����·����ʧ��
	}			
}

//��ȡ����·���ļ����ݶ�̬������
int CT3DSystemView::FlyPathRead(char *pathfile)
{
	CString tt,m_strszLine;
	PCordinate ppt = new Cordinate;  
	
	m_FlayPath.RemoveAll(); //����·���������
	
	CStdioFile m_inFile;	
			
	if(m_inFile.Open (pathfile,CFile::modeRead)==FALSE) //���ļ�
	{
		return 0; //����ʧ�ܱ�־
	}
	m_inFile.ReadString(m_strszLine); //��ȡ����·�����������
	while( m_inFile.ReadString(m_strszLine))
	{
		ppt = new Cordinate;
		
		m_strszLine.TrimLeft(" ");
		m_strszLine.TrimRight("	");
		int nPos=m_strszLine.Find(",");
		tt=m_strszLine.Left(nPos);
		ppt->x=atof(tt);
		m_strszLine=m_strszLine.Right(m_strszLine.GetLength()-nPos-1);
		nPos=m_strszLine.Find(",");
		tt=m_strszLine.Left(nPos);
		ppt->y=atof(tt); 
		m_strszLine=m_strszLine.Right(m_strszLine.GetLength()-nPos-1);
		ppt->z=atof(m_strszLine);
		m_FlayPath.Add(ppt); //��¼����·�������
		
	}
	m_inFile.Close(); //�ر��ļ�
	
	return 1; //���سɹ���־
}

//��ʾ��رշ���·��
void CT3DSystemView::OnFlyOnoffpath() 
{
	if(m_ShowFlyPath==TRUE) //�����ǰ����ʾ����·��
		m_ShowFlyPath=FALSE; //��ʶ����ΪFALSE
	else
		m_ShowFlyPath=TRUE; //��֮,����ΪTRUE	
	OnDraw(GetDC());  //ˢ����ά���� 
	
}

//����m_ShowFlyPathֵ�޸Ĳ˵��ı�
void CT3DSystemView::OnUpdateFlyOnoffpath(CCmdUI* pCmdUI) 
{
	if(m_ShowFlyPath==TRUE) //�����ǰ����ʾ����·��
		pCmdUI->SetText("�رշ���·��"); //���˵���������Ϊ"�رշ���·��"
	else   //�����ǰ�ǹرշ���·��
		pCmdUI->SetText("��ʾ����·��");//���˵���������Ϊ"��ʾ����·��"
}

//���̶��߶�����
void CT3DSystemView::OnFlyStaticheight() 
{
	if(m_FlayPath.GetSize()<=0) //�������·�����������<=0��������·��Ϊ��
	{
		MessageBox("û������·���ļ�","�������",MB_ICONWARNING);
		return;
	}
	
	m_R=4000;
	m_r=3000;
	
	m_FlyHeightType = GIS_FLY_STATICHEIGHT; //������������Ϊ�̶��߶�����
	m_StaticHeight = (m_maxHeight+m_minHeight)/4.0;  //ȡ�̶��߶�ֵ=����������С�߶ȵ�1/4
	m_flypathPtIndex=0; //����·����������=0
	
	SetFLyTimer();	//������ά���μ�ʱ��
}

void CT3DSystemView::OnUpdateFlyStaticheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_PathFlag == TRUE); //�����Ƿ������Ч����·��ֵ���ò˵�״̬
	if (m_FlyHeightType==GIS_FLY_STATICHEIGHT) //�����ǰ��"�ع̶��߶�����"��ʽ
        pCmdUI->SetCheck(TRUE); //�˵�ǰ����ѡ�б�־"��"
    else
		pCmdUI->SetCheck(FALSE); //��������		
}

//���÷��м�ʱ��
void CT3DSystemView::SetFLyTimer()
{
	SetTimer(1,m_flyspeed,0); //m_flyspeed:���м�ʱ��ʱ����,
	
}

//��ʱ��
void CT3DSystemView::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 1:  //��ά����
		if(m_flypathPtIndex<=m_FlayPath.GetSize()-2) //�����ǰ����·�����������<=·�����������-1
		{
			//��������·�����������������������
			GetCameraCorrdinate(
				m_FlayPath.GetAt(m_flypathPtIndex)->x,\
				m_FlayPath.GetAt(m_flypathPtIndex)->y,\
				m_FlayPath.GetAt(m_flypathPtIndex)->z,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->x,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->y,\
				m_FlayPath.GetAt(m_flypathPtIndex+1)->z
				);
			if(m_ifZoomonRoad==TRUE)//�������·��������
			{
				//���㵱ǰ���
				CString tt,tt2;
				tt=myDesingScheme.GetLC(m_FlayPath.GetAt(m_flypathPtIndex)->Lc);
				tt2="��ǰ���="+tt;
				CMainFrame *pMainFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
				pMainFrame->Set_BarText(5,tt2,0); 
				CalZoomSpeed(m_FlayPath.GetAt(m_flypathPtIndex)->Lc);
			}
			else
			{
				double L=myDesingScheme.GetDistenceXYZ(
					m_FlayPath.GetAt(m_flypathPtIndex)->x,\
					m_FlayPath.GetAt(m_flypathPtIndex)->y,\
					m_FlayPath.GetAt(m_flypathPtIndex)->z,\
					m_FlayPath.GetAt(m_flypathPtIndex+1)->x,\
					m_FlayPath.GetAt(m_flypathPtIndex+1)->y,\
					m_FlayPath.GetAt(m_flypathPtIndex+1)->z
					);
					m_CurZooomLC+=L;
					CalZoomSpeed(m_CurZooomLC);
			}
			OnDraw(GetDC()); //ˢ����ά����
			m_flypathPtIndex++; //����·����ǰ����������+1
		}

		else
		{
			m_flypathPtIndex=0; //���˷���β,������·����ǰ��������������Ϊ0,���ӷ���·����ʼ�㿪ʼ����
		}
		break;
	case 2: //¼��ͼ������
		RecordPictures();
		break;
	case 3:
	//	m_snows.DrawSnow ();
		break;
	}
	
	CView::OnTimer(nIDEvent);
}

//����Ը߶����η�ʽ
void CT3DSystemView::OnFlyRoutineheight() 
{
	if(m_FlayPath.GetSize()<=0)//�������·�����������<=0��������·��Ϊ��
	{
		MessageBox("û������·���ļ�","�������",MB_ICONWARNING);
		return;
	}
	
	m_FlyHeightType = GIS_FLY_PATHHEIGHT;//������������Ϊ��Ը߶�����
	m_R=3000;
	m_r=2000;
	
	if(m_ifZoomonRoad==TRUE) 
		m_StaticHeight =5;
	else
		m_StaticHeight =80; //������Ը߲�ֵ
	
	m_flypathPtIndex=0;//����·�������ʼ����=0
	SetFLyTimer();	//������ά���μ�ʱ��
}

//���ò˵��Ƿ�����ѡ�б�ʶ"��"
void CT3DSystemView::OnUpdateFlyRoutineheight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_PathFlag == TRUE); //�����Ƿ������Ч����·��ֵ���ò˵�״̬
	if (m_FlyHeightType==GIS_FLY_PATHHEIGHT) //�����ǰ��"����Ը߶�����"��ʽ
        pCmdUI->SetCheck(TRUE); //�˵�ǰ����ѡ�б�־"��"
    else
		pCmdUI->SetCheck(FALSE); //��������	
}

//��ʼ/��ͣ����
void CT3DSystemView::OnFlyPlaypause() 
{
	if(m_FlyPause==FALSE) //���������ͣ����,����������״̬
	{
		m_FlyPause=TRUE; //������ͣ��ʶm_FlyPause=TRUE
		KillTimer(1); //���ٶ�ʱ��1
	}
	else //�����������״̬
	{
		m_FlyPause=FALSE; //������ͣ��ʶm_FlyPause=FALSE
		SetFLyTimer();//���÷���ʱ����,��������
	}
}

//����m_FlyPauseֵ���ò˵�ID_FLY_PLAYPAUSE�ı�
void CT3DSystemView::OnUpdateFlyPlaypause(CCmdUI* pCmdUI) 
{
	if(m_FlyPause==TRUE) //�����������״̬
		pCmdUI->SetText("��ʼ����"); //���ò˵�ID_FLY_PLAYPAUSE�ı�
	else  //���������ͣ����,����������״̬
		pCmdUI->SetText("��ͣ����");//���ò˵�ID_FLY_PLAYPAUSE�ı�
	
}

//ֹͣ����
void CT3DSystemView::OnFlyStop() 
{
	KillTimer(1); //���ٶ�ʱ��1
	m_flypathPtIndex=0;//����·����������=0
	m_FlyPause=FALSE; //��ͣ��ʶΪFALSE
	m_ifZoomonRoad=FALSE; //��ʶ����·����������ΪFALSE
	m_far=10000;	//�ָ�gluPerspective()��������ƽ��ͷ���Զ����ƽ��ľ���
}

//����ǰ��
void CT3DSystemView::OnFlyOnestep() 
{
	//�������·����������>=0����<����·����������-1,��������ʾ����
	//ֻҪ����·����������û�е�����·��β,�Ϳ���ִ�е���ǰ��
	if(m_flypathPtIndex>=0 && m_flypathPtIndex<m_FlayPath.GetSize()-1)
	{
		
		KillTimer(1);	//���ٶ�ʱ��1		
		m_FlyPause=TRUE;//��ͣ��ʶΪTRUE
		//��������·�����������������������
		GetCameraCorrdinate(
			m_FlayPath.GetAt(m_flypathPtIndex)->x,\
			m_FlayPath.GetAt(m_flypathPtIndex)->y,\
			m_FlayPath.GetAt(m_flypathPtIndex)->z,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->x,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->y,\
			m_FlayPath.GetAt(m_flypathPtIndex+1)->z
			);
		
		OnDraw(GetDC()); //ˢ����ά���� 
		m_flypathPtIndex++; //��ǰ��·����������+1
	}	
}

//������Ұ����
void CT3DSystemView::OnFlyViewEnlarge() 
{
	m_ViewWideNarrow += 5.0; //m_ViewWideNarrowֵ����
	OnDraw (GetDC()); //ˢ����ά����
}

//������Ұ��С
void CT3DSystemView::OnFlyViewSmall() 
{
	m_ViewWideNarrow -= 5.0;//m_ViewWideNarrowֵ��С
	OnDraw (GetDC());//ˢ����ά����
}

//���и߶�����
void CT3DSystemView::OnFlyHeightUp() 
{
	m_StaticHeight += 8;// �߶�ֵ����(����=8,�������趨)
	OnDraw (GetDC());//ˢ����ά����	
}

//���и߶Ƚ���
void CT3DSystemView::OnFlyHeightDown() 
{
	m_StaticHeight -= 8;// �߶�ֵ����(����=8,�������趨)
	OnDraw (GetDC());//ˢ����ά����	
	
}

//�����ӽ�����(����)
void CT3DSystemView::OnFlyViewUp() 
{
	m_ViewUpDown += 1.0;
	OnDraw (GetDC());//ˢ����ά����	
}

//�����ӽ�����(����)
void CT3DSystemView::OnFlyViewDown() 
{
	m_ViewUpDown -= 1.0;
	OnDraw (GetDC());//ˢ����ά����	
}

//����
void CT3DSystemView::OnFlySpeedUp() 
{
	m_flyspeed-=2; //����ʱ�ļ�ʱ��ʱ�������� 
	if(m_flyspeed<=1) //�����ʱ��ʱ����<=1,����
		m_flyspeed=1;
	SetFLyTimer();	//���÷��м�ʱ��
}

//����
void CT3DSystemView::OnFlySpeedDown() 
{
	m_flyspeed+=2;//����ʱ�ļ�ʱ��ʱ�������� 
	SetFLyTimer();//���÷��м�ʱ��
}

//��ά���ε����ȼ�����
void CT3DSystemView::DisplayHelp()
{
	char str[20][50],strdis[2000];
	
	strdis[0]='\0';
	
	strcpy(str[0]," �����   ��ǰ�����ƶ�\n");
	strcpy(str[1]," �����   �������ƶ�\n");
	strcpy(str[2]," �����   �������ƶ�\n");
	strcpy(str[3]," �����   ���ҷ����ƶ�\n");
	strcpy(str[4],"  J ��    ���м���\n");
	strcpy(str[5],"  M ��    ���м���\n");
	strcpy(str[6],"  F ��    ������Ұ����\n");
	strcpy(str[7],"  V ��    ������Ұ��С\n");
	strcpy(str[8],"  G ��     ���߷��и߶�\n");
	strcpy(str[9],"  B ��     ���ͷ��и߶�\n");
	strcpy(str[10],"  H ��    ���й۲�����\n");
	strcpy(str[11],"  N ��    ���й۲�����\n");
	strcpy(str[12],"  Z ��    �ط���������\n");
	strcpy(str[13],"  P ��    ��ʼ/��ͣ����\n");
	strcpy(str[14],"  S ��    ֹͣ����");
	
	for(int i=0;i<15; i++)
		strcat(strdis,str[i]);
	
	MessageBox(strdis,"��ά�����ȼ�˵��",MB_OK);
}

//�Ŷ�ģ��
void CT3DSystemView::OnMenuModleqd() 
{
	CModelMangerQD dlg;
	if(dlg.DoModal()==IDOK) //����Ի�����IDOK��ʽ�ر�
	{
		if(!dlg.m_3DSfilename_QD.IsEmpty()) //����Ŷ�ģ�����Ʋ�Ϊ��
		{
			m_3DSfilename_QD=dlg.m_3DSfilename_QD; //�õ��Ŷ�ģ������
			BuildQDModelList(); //���¹����Ŷ�ģ����ʾ�б�
			
		}
	}	
}

//�����·��άģ�͵�CAD
void CT3DSystemView::OnMenuOuptcad3dlinemodel() 
{
	CString tt,DxfFilename;
	
	CDXF mdxf;
	CStdioFile *Dxffile=new CStdioFile;
	CFileDialog fielDlg(FALSE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"AutoCAD Dxf(*.dxf)|*dxf||",NULL);
	
	fielDlg.m_ofn.lpstrTitle = "�����·��άģ�͵�CAD";   
	
	if(fielDlg.DoModal()==IDCANCEL) //�򿪶Ի���
		return;
	
	DxfFilename=fielDlg.GetPathName(); //�õ�DXF�ļ���
	if(DxfFilename.IsEmpty()) //���DXF�ļ���Ϊ�գ�����
		return;

	//ȷ��DXF�ļ���".dxf"��չ����β
	tt=DxfFilename.Right(4);
	tt.MakeUpper();
	if(strcmp(tt,".DXF")!=0)
		DxfFilename+=".dxf";
	
	//����´�����DXF�ļ��Ѿ��򿪣���������Ϣ	 
	if(Dxffile->Open (DxfFilename,CFile::modeCreate | CFile::modeWrite)==FALSE)
	{
		this->MessageBox("�ļ�"+DxfFilename+"�ѱ���������򿪻�ռ��,��ر�����!","�����·��άģ�͵�CAD",MB_ICONINFORMATION);
		return;
	}

	mdxf.DxfHeader(Dxffile); //д��DXF�ļ�ͷ
	mdxf.DxfLineType(Dxffile);//д��DXF���Ͷ���
	mdxf.DxfBeginDrawEnties(Dxffile); //��ʼд��ͼ��ʵ��

	//д����·�����߲���
	for (long i=0;i<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		
		mdxf.DxfDraw_Line(Dxffile,"��·������",1,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x,\
			-myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->z,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->y,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->x,\
			-myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->z,\
			myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i+1)->y);
	}	

	//д��������������߲���
	for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		mdxf.DxfDraw_Line(Dxffile,"�������������",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2);
		mdxf.DxfDraw_Line(Dxffile,"�������������",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"�������������",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"�������������",6,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1);
	}		

	//д������������ż�����߲���
	for (i=0;i<myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		
	
		mdxf.DxfDraw_Line(Dxffile,"����������ż������",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"����������ż������",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"����������ż������",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1);
		mdxf.DxfDraw_Line(Dxffile,"����������ż������",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y1);
		
		
		mdxf.DxfDraw_Line(Dxffile,"����������ż������",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"����������ż������",3,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"����������ż������",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2);
		mdxf.DxfDraw_Line(Dxffile,"����������ż������",3,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_Railway3D[m_currentSchemeIndexs].GetAt(i)->y2);
		

	}
	
	//д����������·�������߲���
	for (i=0;i<myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetSize()-1;i++)
	{
	
		
		mdxf.DxfDraw_Line(Dxffile,"��������·��������",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"��������·��������",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1);
		mdxf.DxfDraw_Line(Dxffile,"��������·��������",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1);
		mdxf.DxfDraw_Line(Dxffile,"��������·��������",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x1,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z1,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y1);
		
		
		
		mdxf.DxfDraw_Line(Dxffile,"��������·��������",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"��������·��������",4,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2);
		mdxf.DxfDraw_Line(Dxffile,"��������·��������",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i+1)->y2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2);
		mdxf.DxfDraw_Line(Dxffile,"��������·��������",4,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLj3D[m_currentSchemeIndexs].GetAt(i)->y2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->x2,\
			-myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->z2,\
			myDesingScheme.PtS_RailwayLjToBP3D[m_currentSchemeIndexs].GetAt(i)->y2);
		
	}		
	
	//д�������²���(�����������д��)
	for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
		if(tt!="������" && tt!="����м��" &&tt!="����յ�" &&tt!="�������"  &&tt!="�����м��" &&tt!="�����յ�")
		{	
			DrawBP_CAD(i,1,Dxffile);//������
		
		}
	}
	
	//д���Ҳ���º�����ˮ������(�����������д��)
	for (i=0;i<myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetSize()-1;i++)
	{
		tt=myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->strJDStyle;
		if(tt!="������" && tt!="����м��" &&tt!="����յ�" &&tt!="�������"  &&tt!="�����м��" &&tt!="�����յ�")
		{
			DrawBP_CAD(i,2,Dxffile); //�Ҳ����
			DrawSuiGou_CAD(i,2,Dxffile);//����ˮ��
		
		}
	}
	
	mdxf.DxfSectionEnd(Dxffile); //д���ļ�������־
	tt.Format("dxf�ļ�%s��������!",DxfFilename);
	MessageBox(tt,"���ͼ�ε�AuotCAD",MB_ICONINFORMATION); //����DXF�ļ���������Ϣ
		
}

//д��������²��ֵ�DXF�ļ���(�����������д��)
void CT3DSystemView::DrawBP_CAD(long index, int BPside, CStdioFile *Dxffile)
{
	long i=index;

	int j;


	if(BPside==1) 
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_L;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_L;
	
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				
				
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{

					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
				}
				else 
				{
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j+1].Hp[2].y);
				}
			
	
				if(j>0) 
					{
						glBindTexture(GL_TEXTURE_2D, m_cTxturePT.GetTxtID());
						mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y);
						mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y);
						mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
						mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
							-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
							myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
						
				}
	
			}
			
		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				glBindTexture(GL_TEXTURE_2D, m_cTxtureBP.GetTxtID());
				
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].style)
				{
 
 					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
					
				}
				else
				{
 
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y);

 
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j+1].Hp[2].y);
					
					
				}
			

				if(j>0) 
				{
 
 					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_L[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_L[j].Hp[1].y);
					
				}

			}
			
		}
		
	}
	else if(BPside==2) 
	{
		
		int N1=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->Huponums_R;
		int N2=myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->Huponums_R;
		if(N1<=N2 && N1>0 && N2>0)
		{
			for(j=0;j<N1;j++)
			{
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
 
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x<myDesingScheme.PtS_3DLineZX[m_currentSchemeIndexs].GetAt(i)->x)
					{
					}
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);					
				}
				else
				{
 
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);
					
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j+1].Hp[2].y);
					
				}
				
				if(j>0) 
				{
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					
				}
			}
		}
		else 
		{
			for(j=0;j<N2;j++)
			{
				if(myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].style==\
					myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].style)
				{
 
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);
					
				}
				else
				{
 
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y);
					

					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[2].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j+1].Hp[2].y);
					
				}
				
				if(j>0) 
				{
 
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[0].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y);
					mdxf.DxfDraw_Line(Dxffile,"·��������",2,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i+1)->HuPo_R[j].Hp[1].y,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].x,\
						-myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].z,\
						myDesingScheme.PtS_HuPo[m_currentSchemeIndexs].GetAt(i)->HuPo_R[j].Hp[1].y);
					
				}
			}

		}
		
	}
}

void CT3DSystemView::DrawSuiGou_CAD(long index, int BPside, CStdioFile *Dxffile)
{
	float SGLL=2.8;
	int i;
	
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_L==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_L==TRUE)
	{
		
		for( i=0;i<=5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"ˮ��",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y);
		}
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"ˮ��",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouL[i+1].y);
		}
		
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"ˮ��",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouL[i+1].y);
		}
		
		
	}
	
	
	if(myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->bhaveSuiGou_R==TRUE\
		&& myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->bhaveSuiGou_R==TRUE)
	{
		for( i=0;i<=5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"ˮ��",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y);
		}
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"ˮ��",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index)->SuiGouR[i+1].y);
		}
		
		for( i=0;i<5;i++)
		{
			
			mdxf.DxfDraw_Line(Dxffile,"ˮ��",5,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i].y,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i+1].x,\
				-myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i+1].z,\
				myDesingScheme.PtS_PaiSuiGou[m_currentSchemeIndexs].GetAt(index+1)->SuiGouR[i+1].y);
		}
		
	}
}

//����¼�Ʋ�������
void CT3DSystemView::OnAviParameter() 
{
	CRect rect;
	this->GetClientRect(&rect); //�õ��ͻ�����С��
	
	CAviParameter	 dlg;
	

	//ȷ��AVI��Ⱥ͸߶���Ч
    if(m_MovieWidth<=0 || m_MovieHeight<=0)
	{
		m_MovieWidth=rect.right; //AVI�Ŀ��
		m_MovieHeight=rect.bottom;//AVI�ĸ߶�
	}
	
	
	dlg.m_MoviemaxWidth=rect.right;   //AVI�������
	dlg.m_MoviemaxHeight=rect.bottom; //AVI�����߶�
	
	dlg.m_AviFilename=m_AviFilename;  //AVI�ļ���
	dlg.m_AVIFrame=m_AVIFrame;//AVI�ļ�¼��Ƶ��
	
	dlg.m_MovieWidth=m_MovieWidth; //AVI�Ŀ��
    dlg.m_MovieHeight=m_MovieHeight; //AVI�ĸ߶� 
	
	if(dlg.DoModal ()==IDOK)  
	{
		m_AviFilename=dlg.m_AviFilename; //AVI�ļ���
		m_AVIFrame=dlg.m_AVIFrame; //AVI�ļ�¼��Ƶ��
		m_MovieWidth=dlg.m_MovieWidth;  //AVI�Ŀ��
		m_MovieHeight=dlg.m_MovieHeight; //AVI�ĸ߶� 
	}	
}



//��ʼ¼�ƶ���
void CT3DSystemView::OnAviStart() 
{
	if(m_Beginrecording==TRUE)  //�����ʼ¼�ƶ�����ʶm_Beginrecording=TRUE,��ʾ�Ѿ�����¼�ƶ���,����
	{
		recordBegin(); //��¼��ʼ¼�ƶ���
		return; //����
	}
	
	//��AVI�����ļ�
	CFileDialog fd(FALSE,"avi",0,OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY|OFN_PATHMUSTEXIST,"Microsoft AVI (*.avi)|*.avi||");
	
	CDC *dc=GetDC();
	wglMakeCurrent( dc->m_hDC, m_hRC );//��RC�뵱ǰDC����
	
	CRect rect;
	GetClientRect(&rect); //�õ��ͻ�����
	
	//ȷ��AVI��Ⱥ͸߶���Ч
	if(m_MovieWidth<=0 ||m_MovieHeight<=0) 
	{
		m_MovieWidth=rect.right;
		m_MovieHeight=rect.bottom;
	}
	
	BeginWaitCursor(); //��ʾɳ©���
    bool success = false;

	//����׽��������д��AVI�ļ���
	success = BeginMovieCapture(m_AviFilename,m_MovieWidth,m_MovieHeight,m_AVIFrame);
	if (!success)
    {
        MessageBox("����¼�ƶ���!", "¼�ƶ���", MB_OK | MB_ICONERROR);
		return;
    }
	
	if (m_movieCapture != NULL)
    {
        if (isRecording())
            OnAviPause(); //��ͣ¼�ƶ���
        else
            recordBegin(); //��ʼ¼�ƶ���
    }
	
    EndWaitCursor();//����ɳ©���,�ָ��������
	
	wglMakeCurrent( 0, 0 );//�ͷ�DC��RC 
	ReleaseDC(dc);	//�ͷ�dc		
}

//��ʼ��׽
bool CT3DSystemView::BeginMovieCapture(CString filename, int width, int height, float framerate)
{
	m_movieCapture = new CAVICapture();
	//����AVI�ļ����ơ�¼��֡�Ĵ�С��¼��֡�ʡ�AVI�ļ�ѹ����ʽ����Ϣ
    bool success = m_movieCapture->start(filename, width, height, framerate);
    if (success) //������óɹ�
        initMovieCapture(m_movieCapture); //��ʼ��m_movieCapture����
    else
        delete m_movieCapture; //���ʧ��,ɾ��m_movieCapture
    
    return success;
}

//��ʼ��m_movieCapture����
void CT3DSystemView::initMovieCapture(CAVICapture *mc)
{
	if (m_movieCapture == NULL)
        m_movieCapture = mc;
	
}

//��ȡ�Ƿ���¼�ƶ���
bool CT3DSystemView::isRecording()
{
	return m_Recording;
	
}

//���m_movieCapture��ΪNULL,��ʼ���ɹ�,������¼�Ʊ�ʶ=true
void CT3DSystemView::recordBegin()
{
	if (m_movieCapture != NULL) //���m_movieCapture��ΪNULL
        m_Recording = true;
	
}

//��ͣ¼�ƶ���
void CT3DSystemView::OnAviPause() 
{
	m_Recording = false;
}

//����¼�ƶ���
void CT3DSystemView::OnAviEnd() 
{
	if (m_movieCapture != NULL) //���m_movieCapture ��Ϊ��,��ʾ�Ѳ�׽����
	{
        recordEnd(); //����¼�ƶ���		
	}		
}

//����¼�ƶ���
void CT3DSystemView::recordEnd()
{
	if (m_movieCapture != NULL) //���m_movieCapture ��Ϊ��,��ʾ�Ѳ�׽����
    {
        OnAviPause();//��ͣ,����׽�����ݲ���д���ļ�
        m_movieCapture->end();//����¼��
        delete m_movieCapture; //ɾ��m_movieCapture(�������¼�Ƶ�����)
        m_movieCapture = NULL; //��������m_movieCaptureΪ��
    }
}

//����ͼ��ɼ�Ƶ��
void CT3DSystemView::OnSavepictureSpeed() 
{
	CRecordPictureSpeed	 dlg;
	dlg.m_recordPictSpeed=m_recordPictSpeed;//��ǰ�����õĲɼ�ͼ��Ƶ��
	if(dlg.DoModal ()==IDOK) //����Ի�����IDOK��ʽ�ر�
	{
		m_recordPictSpeed=dlg.m_recordPictSpeed; //�õ������õĲɼ�ͼ��Ƶ��
	}			
}


//¼��(ͼ������)
void CT3DSystemView::OnSavepictureContinue() 
{
	m_RecordPicture=TRUE;  //¼��ͼ�����еı�־ΪTRUE
	SetPictureName(); //����¼��ͼ��ʱ�ĳ�ʼ�ļ�����
	SetTimer(2,m_recordPictSpeed,NULL);	 //����¼��ͼ���ʱ��
	
}

//����¼��ͼ��ʱ�ĳ�ʼ�ļ����ƣ�����ɼ���ͼ���ļ������Դ˳�ʼ�ļ���+¼��������
void CT3DSystemView::SetPictureName()
{
	CFileDialog FileDialog( FALSE, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY,
		_T("Windows Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL );
	
	if(FileDialog.DoModal() == IDOK) //���ļ��Ի���
	{
		m_RecordPicturename = FileDialog.GetPathName(); //�õ�ͼ���ļ���
		
	}	
}

//¼��ͼ������
void CT3DSystemView::RecordPictures()
{
	
	CString str,str1,fname;
	
	str.Format("%s",m_RecordPicturename);
	int n=str.GetLength ();
	str=str.Left (n-4);
	m_PictureNumbers++; //�ɼ���ͼ������+1
	
	str1.Format ("%d",m_PictureNumbers);
	switch(str1.GetLength ())
	{
		case 1:str1="0000"+str1;break;
		case 2:str1="000"+str1;break;
		case 3:str1="00"+str1;break;
		case 4:str1="0"+str1;break;
	}
	
	fname=str+str1+".bmp"; //�õ�Ҫ�����λͼ�ļ���
	CRect rcDIB;
	GetClientRect(&rcDIB);
    
	OnDraw (GetDC());//ˢ����ά���� 
	CapturedImage.Capture(GetDC(), rcDIB);
	
	CapturedImage.WriteDIB(fname); //���ɼ�������д��λͼ���ļ���
	CapturedImage.Release();	//�ͷ�CapturedImage
}

//��ӡԤ��
void CT3DSystemView::OnFilePrintPreview() 
{
	CRect rcDIB;
	GetClientRect(&rcDIB); //�õ��ͻ�����С
	OnDraw (GetDC()); //ˢ����ά���� 
	CapturedImage.Capture(GetDC(), rcDIB);//��DDBͼ��ת��Ϊ���豸�޹ص�λͼDIB
	CView::OnFilePrintPreview(); //����	CView::OnFilePrintPreview()������ӡԤ��
}

//ֹͣ¼��ͼ��
void CT3DSystemView::OnSavepictureStop() 
{
	m_RecordPicture=FALSE; //��ʶ¼��ͼ��ΪFALSE
	KillTimer(2);	//���ټ�����2	
	
}

//������Ļ��λͼ
void CT3DSystemView::OnMenuSavescreentobmp() 
{
	CString strFilename;
	
	HDC   dc;   
	dc=::GetDC(NULL);   
	CRect rcDIB;
	GetClientRect(&rcDIB);
	rcDIB.right = rcDIB.Width();
	rcDIB.bottom = rcDIB.Height();
	HBITMAP mybitmap=GetSrcBit(dc,rcDIB.Width(),rcDIB.Height());
	
	CFileDialog FileDialog( FALSE, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY,
		_T("Windows Bitmap Files (*.bmp)|*.bmp||"), NULL );
	if(FileDialog.DoModal()==IDOK)
	{
		strFilename=FileDialog.GetPathName(); //�õ�λͼ�ļ���
		if(!strFilename.IsEmpty()) //���λͼ�ļ���Ϊ��
		{
			DeleteFile(strFilename); //ɾ��ԭ���ļ�
			BOOL bOK=SaveBmp(mybitmap,strFilename);  //���浽λͼ�ļ�
			if(bOK==TRUE) //�������ɹ�
				MessageBox("ͼ�񱣴�ɹ�","������Ļ��λͼ",MB_ICONINFORMATION);
			else
				MessageBox("ͼ�񱣴�ʧ��","������Ļ��λͼ",MB_ICONINFORMATION);
		}
		
	}	
}

//����λͼ���ļ�
BOOL CT3DSystemView::SaveBmp(HBITMAP hBitmap, CString FileName)
{
	//�豸������   
	HDC   hDC;   
	//��ǰ�ֱ�����ÿ������ռ�ֽ���   
	int   iBits;   
	//λͼ��ÿ������ռ�ֽ���   
	WORD   wBitCount;   
	//�����ɫ���С��   λͼ�������ֽڴ�С   ��λͼ�ļ���С   ��   д���ļ��ֽ���     
	DWORD   dwPaletteSize=0,   dwBmBitsSize=0,   dwDIBSize=0,   dwWritten=0;     
	//λͼ���Խṹ     
	BITMAP   Bitmap;       
	//λͼ�ļ�ͷ�ṹ   
	BITMAPFILEHEADER   bmfHdr;       
	//λͼ��Ϣͷ�ṹ     
	BITMAPINFOHEADER   bi;       
	//ָ��λͼ��Ϣͷ�ṹ       
	LPBITMAPINFOHEADER   lpbi;       
	//�����ļ��������ڴ�������ɫ����     
	HANDLE   fh,   hDib,   hPal,hOldPal=NULL;     
    
	//����λͼ�ļ�ÿ��������ռ�ֽ���     
	hDC   =   CreateDC("DISPLAY",   NULL,   NULL,   NULL);   
	iBits   =   GetDeviceCaps(hDC,   BITSPIXEL)   *   GetDeviceCaps(hDC,   PLANES);     
	DeleteDC(hDC);     
	if   (iBits   <=   1)   wBitCount   =   1;     
	else   if   (iBits   <=   4)     wBitCount   =   4;     
	else   if   (iBits   <=   8)     wBitCount   =   8;     
	else       wBitCount   =   24;     
    
	GetObject(hBitmap,   sizeof(Bitmap),   (LPSTR)&Bitmap);    //����λͼ�ļ�ǰͨ��GetObject����ȡ��λͼ����
	bi.biSize   =   sizeof(BITMAPINFOHEADER);   
	bi.biWidth   =   Bitmap.bmWidth;   
	bi.biHeight   =   Bitmap.bmHeight;   
	bi.biPlanes   =   1;   
	bi.biBitCount   =   wBitCount;   
	bi.biCompression   =   BI_RGB;   
	bi.biSizeImage   =   0;   
	bi.biXPelsPerMeter   =   0;   
	bi.biYPelsPerMeter   =   0;   
	bi.biClrImportant   =   0;   
	bi.biClrUsed   =   0;   
    
	dwBmBitsSize   =   ((Bitmap.bmWidth   *   wBitCount   +   31)   /   32)   *   4   *   Bitmap.bmHeight;   
    
	//Ϊλͼ���ݷ����ڴ�     
	hDib   =   GlobalAlloc(GHND,dwBmBitsSize   +   dwPaletteSize   +   sizeof(BITMAPINFOHEADER));     
	lpbi   =   (LPBITMAPINFOHEADER)GlobalLock(hDib);     
	*lpbi   =   bi;     
    
	//   �����ɫ��       
	hPal   =   GetStockObject(DEFAULT_PALETTE);     
	if   (hPal)     
	{     
		hDC   =   ::GetDC(NULL);     
		hOldPal   =   ::SelectPalette(hDC,   (HPALETTE)hPal,   FALSE);     
		RealizePalette(hDC);     
	}   
	
	//�õ�DCλͼ��� 
	GetDIBits(hDC,   hBitmap,   0,   (UINT)   Bitmap.bmHeight,   (LPSTR)lpbi   +   sizeof(BITMAPINFOHEADER)     
		+dwPaletteSize,   (BITMAPINFO   *)lpbi,   DIB_RGB_COLORS);     
    
	//�ָ���ɫ��       
	if   (hOldPal)     
	{     
		::SelectPalette(hDC,   (HPALETTE)hOldPal,   TRUE);     
		RealizePalette(hDC);     
		::ReleaseDC(NULL,   hDC);     
	}     
    
	//����λͼ�ļ�       
	fh   =   CreateFile(FileName,   GENERIC_WRITE,0,   NULL,   CREATE_ALWAYS,     
		FILE_ATTRIBUTE_NORMAL   |   FILE_FLAG_SEQUENTIAL_SCAN,   NULL);     
    
	if   (fh   ==   INVALID_HANDLE_VALUE)     return   FALSE;     
    
	//   ����λͼ�ļ�ͷ     
	bmfHdr.bfType   =   0x4D42;   //   "BM"     
	dwDIBSize   =   sizeof(BITMAPFILEHEADER)   +   sizeof(BITMAPINFOHEADER)   +   dwPaletteSize   +   dwBmBitsSize;       
	bmfHdr.bfSize   =   dwDIBSize;     
	bmfHdr.bfReserved1   =   0;     
	bmfHdr.bfReserved2   =   0;     
	bmfHdr.bfOffBits   =   (DWORD)sizeof(BITMAPFILEHEADER)   +   (DWORD)sizeof(BITMAPINFOHEADER)   +   dwPaletteSize;     
	//   д��λͼ�ļ�ͷ     
	WriteFile(fh,   (LPSTR)&bmfHdr,   sizeof(BITMAPFILEHEADER),   &dwWritten,   NULL);     
	//   д��λͼ�ļ���������     
	WriteFile(fh,   (LPSTR)lpbi,   dwDIBSize,   &dwWritten,   NULL);     
	//���       
	GlobalUnlock(hDib);     
	GlobalFree(hDib);     
	CloseHandle(fh);     
    
	return   TRUE;   
}

//�õ�DCλͼ���
HBITMAP CT3DSystemView::GetSrcBit(HDC hDC, DWORD BitWidth, DWORD BitHeight)
{
	HDC   hBufDC;   
	HBITMAP   hBitmap,   hBitTemp;   
    
	//�����豸������(HDC)   
	hBufDC   =   CreateCompatibleDC(hDC);   
    
	//����HBITMAP   
	hBitmap   =   CreateCompatibleBitmap(hDC,   BitWidth,   BitHeight);   
	hBitTemp   =   (HBITMAP)   SelectObject(hBufDC,   hBitmap);   
    
	//�õ�λͼ������   
	StretchBlt(hBufDC,   0,   0,   BitWidth,   BitHeight,   
		hDC,   0,   0,   BitWidth,   BitHeight,   SRCCOPY);   
    
	//�õ����յ�λͼ��Ϣ   
	hBitmap   =   (HBITMAP)   SelectObject(hBufDC,   hBitTemp);   
    
	//�ͷ��ڴ�   
    
	DeleteObject(hBitTemp);   
	::DeleteDC(hBufDC);   
    
	return   hBitmap;   
}




