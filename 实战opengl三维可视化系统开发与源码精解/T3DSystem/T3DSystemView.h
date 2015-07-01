// T3DSystemView.h : interface of the CT3DSystemView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_T3DSYSTEMVIEW_H__3A8D7F07_F2EE_46F8_A484_C22327088E9C__INCLUDED_)
#define AFX_T3DSYSTEMVIEW_H__3A8D7F07_F2EE_46F8_A484_C22327088E9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum { QUERY_COORDINATE,QUERY_DISTENCE,SELECTLINE,SELECTFLYPATH};
enum {GIS_VIEW_ORTHO,GIS_VIEW_PERSPECTIVE};
enum {ORTHO_ZOOMIN,ORTHO_ZOOMOUT,ORTHO_PAN,ORTHO_ZOOMORIGIN,ORTHO_ZOOMWINDOW};
enum {GIS_FLY_STATICHEIGHT,	GIS_FLY_PATHHEIGHT};

#define MAX_TEXTURENUM  500  //��������ͬʱ���صĵ��ο�����

#include "AllocUnAlloc2D3D.h"
#include "Vector.h"	
#include "Texture.h"
#include "3DSModel.h"
#include "Delaunay.h"
#include "DXF.h"
#include "AVICapture.h"
#include "ClientCapture.h"	
#include "Snow.h"


#define SKYFRONT 0						// Give Front ID = 0
#define SKYBACK  1						// Give Back  ID = 1
#define SKYLEFT  2						// Give Left  ID = 2
#define SKYRIGHT 3						// Give Right ID = 3
#define SKYUP    4						// Give Up    ID = 4
#define SKYDOWN  5						// Give Down  ID = 5

//�����������߽ṹ
typedef struct  
{
	int index;//�����������
	CArray<PCordinate,PCordinate> ReginPts;//��·�������߽�㼯��
	CArray<int,int>GridID;//�����ڷֿ�ID��(�ֿ��׼������DEM�ֿ��С)
	double minx;//��Сx����
	double miny;//��Сy����
	double maxx;//���x����
	double maxy;//���y����
	
}Regions,*PRegions;


typedef struct  
{
	BOOL bInRegion;//�ڵ���Ƿ��ڷ������(ֻ�е��ڵ�4���ǵ�������ڷ�������ڲ�Ϊ��)
	
} BlockReginInfor,*PBlockReginInfor;

typedef struct
{
	int RegionNum;//�õ��ο��ڷ����������
	CArray<int,int>GridID;//�����ڷֿ�ID��(�ֿ��׼������DEM�ֿ��С)
	CArray<PCordinate,PCordinate> ReginPts;//��·�������߽�㼯��
	double minx; //��Сx����
	double miny;//��Сy����
	double maxx;//���x����
	double maxy;//���y����
	
}BlockReginInforMe,*PBlockReginInforMe;

//������ο���ɢ�㼯��
typedef struct
{
	CArray<PCordinate,PCordinate> ReginPts;//���ο�����ɢ�㼯��(�������ε�ͷ�������)
	int mDemBlockRow;//��Ӧ��DEM�ӿ���к�
	int mDemBlockCol;//��Ӧ��DEM�ӿ���к�
	
}BlockLSPts,*PBlockLSPts;


//������3��������Ϣ
typedef struct
{
	Point Pt1;
	Point Pt2;
	Point Pt3;
}TriPt,*PTriPt;

//�洢ÿ�����ο��ڵ���������Ϣ
typedef struct
{
	CArray<PTriPt,PTriPt>TriPts;
	int mDemBlockRow;//��Ӧ��DEM�ӿ���к�
	int mDemBlockCol;//��Ӧ��DEM�ӿ���к�
}BlockTriInfos,*PBlockTriInfos;




class CT3DSystemView : public CView
{
protected: // create from serialization only
	CT3DSystemView();
	DECLARE_DYNCREATE(CT3DSystemView)

// Attributes
public:
	CT3DSystemDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CT3DSystemView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CArray<PBlockTriInfos,PBlockTriInfos> m_BlockTriInfos;//�洢ÿ�����ο����������Ϣ
	
	virtual ~CT3DSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	CArray<PCordinate,PCordinate> m_FlayPath;//�洢���з���·��ѡ��ʱ��ѡ���һϵ�е�����
	CArray<PCordinate,PCordinate> m_FlayPathTempPts;//�洢��ʱ���з���·��ѡ��ʱ��ѡ���һϵ�е�����
	int m_flypathPtIndex; //����·������������
	int m_flyPathCurrentPtIndex;//�ڷ��й����м�¼��ǰ·�����������,������ͣ������
	BOOL m_FlyPause;//�Ƿ���ͣ����

	CArray<PCordinate,PCordinate> m_TempPts;
	BOOL m_ifZoomonRoad; //��ʶ�Ƿ�����·��������
	
	CArray<PCordinate,PCordinate> m_ReginPtsLeft;//��·�������߽������·��
	CArray<PCordinate,PCordinate> m_ReginPtsRight;//��·�������߽��Ҳ���·��
	CArray<PRegions,PRegions> mRegions;//��·�������߽��
	
	CArray<PBlockReginInforMe,PBlockReginInforMe> *mBlockReginInforMe;//���νڵ��������Ƿ�λ�ڷ������߽���Ϣ
	
	CArray<PBlockLSPts,PBlockLSPts> m_BlockLSPts;//
	
	//{{AFX_MSG(CT3DSystemView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMenuOpenproject();
	afx_msg void OnDrawmodeLine();
	afx_msg void OnDrawmodeRender();
	afx_msg void OnDrawmodeTexture();
	afx_msg void OnSpacequerySet();
	afx_msg void OnQueryCoordinate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnQueryDistence();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMenuStereo();
	afx_msg void OnUpdateMenuStereo(CCmdUI* pCmdUI);
	afx_msg void OnMenuProjecttionortho();
	afx_msg void OnUpdateMenuProjecttionortho(CCmdUI* pCmdUI);
	afx_msg void OnOrthoZoomIn();
	afx_msg void OnUpdateOnOrthoZoomIn(CCmdUI*  pCmdUI);   
	afx_msg void OnOrthoZoomOut();
	afx_msg void OnUpdateOnOrthoZoomOut(CCmdUI*  pCmdUI);   
	afx_msg void OnOrthoPan();
	afx_msg void OnUpdateOnOrthoPan(CCmdUI*  pCmdUI);   
	afx_msg void OnOrthoZoomOrigin();
	afx_msg void OnUpdateOnOrthoZoomOrigin(CCmdUI*  pCmdUI);   
	afx_msg void OnOrthoZoomWindow();
	afx_msg void OnUpdateOnOrthoZoomWindow(CCmdUI*  pCmdUI);   
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMenuLinedesign();
	afx_msg void OnUpdateMenuLinedesign(CCmdUI* pCmdUI);
	afx_msg void OnUpdateQueryCoordinate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateQueryDistence(CCmdUI* pCmdUI);
	afx_msg void OnMenuLinesavescheme();
	afx_msg void OnUpdateMenuPerspective(CCmdUI* pCmdUI);
	afx_msg void OnMenuPerspective();
	afx_msg void OnMenuBuild3dlinemodle();
	afx_msg void OnFlyRoutinschemeline();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFlyStop();
	afx_msg void OnMenuTunnelset();
	afx_msg void OnMenuBridgeset();
	afx_msg void OnMenuTexturebp();
	afx_msg void OnMenuTexturelj();
	afx_msg void OnMenuTextureqlhpm();
	afx_msg void OnMenuTexturetunnel();
	afx_msg void OnMenuTexturetunnelDm();
	afx_msg void OnPathManuinput();
	afx_msg void OnFlypathSave();
	afx_msg void OnFlppathInterpolation();
	afx_msg void OnFlyOpenpath();
	afx_msg void OnFlyOnoffpath();
	afx_msg void OnUpdateFlyOnoffpath(CCmdUI* pCmdUI);
	afx_msg void OnFlyStaticheight();
	afx_msg void OnUpdateFlyStaticheight(CCmdUI* pCmdUI);
	afx_msg void OnFlyRoutineheight();
	afx_msg void OnUpdateFlyRoutineheight(CCmdUI* pCmdUI);
	afx_msg void OnFlyPlaypause();
	afx_msg void OnUpdateFlyPlaypause(CCmdUI* pCmdUI);
	afx_msg void OnFlyOnestep();
	afx_msg void OnFlyViewEnlarge();
	afx_msg void OnFlyViewSmall();
	afx_msg void OnFlyHeightUp();
	afx_msg void OnFlyHeightDown();
	afx_msg void OnFlyViewDown();
	afx_msg void OnFlyViewUp();
	afx_msg void OnFlySpeedUp();
	afx_msg void OnFlySpeedDown();
	afx_msg void OnMenuModleqd();
	afx_msg void OnMenuOuptcad3dlinemodel();
	afx_msg void OnAviParameter();
	afx_msg void OnAviStart();
	afx_msg void OnAviPause();
	afx_msg void OnAviEnd();
	afx_msg void OnSavepictureSpeed();
	afx_msg void OnSavepictureContinue();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnSavepictureStop();
	afx_msg void OnMenuSavescreentobmp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HBITMAP GetSrcBit(HDC hDC, DWORD BitWidth, DWORD BitHeight);
	BOOL SaveBmp(HBITMAP hBitmap, CString FileName);
	void RecordPictures();
	void SetPictureName();
	void recordEnd();
	void recordBegin();
	bool isRecording();
	void initMovieCapture(CAVICapture *mc);
	bool BeginMovieCapture(CString filename, int width, int height, float framerate);
	void DrawSuiGou_CAD(long index, int BPside,CStdioFile* Dxffile);
	void DrawBP_CAD(long index, int BPside,CStdioFile* Dxffile);
	void DisplayHelp();
	int FlyPathRead(char *pathfile);
	int FlyPathSave(char *pathfile);
	void DrawFlyPath();
	int GetBlockID(double x, double y);
	void GetRoadCloseRegion();
	void GetBlockEdgeJd(double block_minx, double block_miny, double block_maxx, double block_maxy, long RegionsIndex, long ReginPtsIndex, int *jdNus, Point edgePts[]);
	void WriteBlockLsPts(long Blcokrow, long Blcokcol);
	void GetBlockInregion(int blockRow, int blockCol);
	BOOL GetTriOutRegion(double x1, double y1, double x2, double y2, double x3, double y3, int blockIndex);
	void AddBlcokTri(int blockIndex, int DemblcokRow, int DemblcokCol);
	void DrawTerrainTIN(long blockIndex);
	void BuildTerrainRegionInfo();
	void GetRegionID(long index);
	void WriteRegionPts(int index, BOOL bAddorAppend,int mLeftorRight);
	void DrawTerrainDelaunay();
	void GetNorthPtangle();
	void PrintText(float x, float y, char *string);
	void DrawNorthPt();
	void makeClockList();
	void SetClockProjectionNavigate();
	void DrawClock();
	void ReLoadCenterPt();
	void DrawBridgeHL();
	void DrawCylinder(GLfloat radii, GLfloat Height, GLint segmentNum);
	void makeQLList();
	void BuildQDModelList();
	void BuildTunnelDMModelList();//�������������ʾ�б�
	void CalZoomSpeed(float mCurZooomLC);
	void GetCameraCorrdinate(double x1, double y1, double z1, double x2, double y2, double z2);
	void SetFLyTimer();
	void DrawTunnelDM(double x1, double y1, double z1, double x2, double y2, double z2, float H, float L, int index, int tunnelIndex, BOOL bstartDM,float mangle);
	void DrawTunnelEach(long mStartindex, long mEndIndex,int mTunnelIndex,float H,float L);
	void GetMinMaxXY_bridgeHPm(double *minx, double *miny, double *maxx, double *maxy);
	void DrawTunnel();
	void DrawSceneQD(double x1, double y1, double z1, double x2, double y2, double z2, float QDheight);
	void DrawQDHP(long Index, CString mCurrentPtstyle, float mHPangle, CString mNextPtstyle,int mBridgeIndex);
	void DrawSuiGou_Ortho(long index);
	void DrawSuiGou(long index);
	void DrawBP_Ortho(long index, int BPside);
	void DrawBP(long index, int BPside);
	void DrawRailwaythesme();
	void DrawCenterLine(long index,BOOL ifSelectLine,int SchemeIndex);
	void DrawRailwaythesme_Ortho();
	float GetOrthoX(double x);	//��������ͶӰģʽ��x����
	float GetOrthoY(double y);	//��������ͶӰģʽ��y����
	void ExporttotalDemToFIle(CString strFilename);
	void ReadHdata(CString strfilename);
	void GetOrthoColor(double x1,double y1,float *mColorR,float *mColorG);
	void DrawBlockOrtho(int DemBlockIndex);
	void DrawTerrain_ORTHO();
	void SetProjection();
	void mCamraUpdate();
	void CheckForMovement();
	void MoveCamera(float speed);
	void RotateView(float angle, float x, float y, float z);
	void SetViewByMouse();
	void StrafeCamera(float speed);
	void DrawSearchPoint();
	void ScreenToGL(CPoint point);
	void SetDrawMode();
	BOOL ExportBlobTextureToFIle(CString strFilename, int RowIndex, int ColIndex,int mID);
	void DrawScene();
	void SetTextureCoord(float x, float z,int mRowIndex,int mColIndex);
	int RenderQuad(int nXCenter, int nZCenter, int nSize,int mRowIndex,int mColIndex);
	void CracksPatchTop(int nXCenter, int nZCenter, int nSize,int mRowIndex,int mColIndex);
	void CracksPatchRight(int nXCenter, int nZCenter, int nSize,int mRowIndex,int mColIndex);
	void CracksPatchLeft(int nXCenter, int nZCenter, int nSize,int mRowIndex,int mColIndex);
	void CracksPatchBottom(int nXCenter, int nZCenter, int nSize,int mRowIndex,int mColIndex);
	void SetTextureCoordZoomRoad(double x, double z,int mRowIndex,int mColIndex);
	BOOL GetIfINView(int mBlockRow,int mBlockCol);
	float GetNodeError(int nXCenter, int nZCenter, int nSize, int mRowIndex, int mColIndex);
	float GetHeightValue(int X, int Y,int mRowIndex,int mColIndex);
	void UpdateQuad(int nXCenter, int nZCenter, int nSize, int nLevel,int mRowIndex,int mColIndex);
	void CalculateViewPortTriCord(double View_x, double View_z, double look_x, double look_z);
	BOOL bnTriangle(double cneterx, double cnetery, double x2, double y2, double x3, double y3, double x, double y);
	void DrawTerrainZoomonRoad();
	void InitList();
	void SetCamra(int mStyle);
	void CalcFPS();
	void DrawTerrain();
	void InitTerr();
	void Init_ArrayData();
	void getDemBlockTexture(int RowIndex, int ColIndex, int Index);
	void ReadDataFromFiles(CString strfiles, int Index);
	void ExportBlobDemToFIle(CString strFilename, int RowIndex, int ColIndex);
	void PositionCamera(double positionX, double positionY, double positionZ, double viewX, double viewY, double viewZ, double upVectorX, double upVectorY, double upVectorZ);
	void Init_data();
	CVector3 Strafe();
	CVector3 UpVector();
	CVector3 GetView();
	CVector3 GetPos();

	void SetSkyProjection(); //�������ͶӰ����
	void SetSkyProjectionNavigate();//������յ���ͼͶӰ����
	void DrawBackground();////���Ʊ������
	void makeSkykList();
	void DrawSky();
	
	

	CDC*	    m_pDC;			
	HGLRC		m_hRC;	
	
	int m_SCREEN_WIDTH;		//��Ļ���
	int m_SCREEN_HEIGHT;	//��Ļ�߶�
	
	int WinViewX,WinViewY;	//�洢�������ӿڵĿ�Ⱥ͸߶�
	BOOL bStereoAvailable;	//�Կ��Ƿ�֧��������ʾ
	
	GLfloat m_ViewWideNarrow;   //��������gluPerspective()��������ƽ��ͷ�����Ұ�ĽǶ�(������С)
	double m_near,m_far;	//gluPerspective()��������ƽ��ͷ��Ľ�����ƽ���Զ����ƽ��ľ���
	float m_aspectRatio; //gluPerspective()���������ƽ��ͷ����ݺ��
	float m_FrustumAngle;
	float m_viewdegree;	//�۲�����ӵ�֮��ĸ��ӽ�
	float m_es;
	
	//������ͶӰģʽ�µ��ε�x,y���������x,y����ı���
	float m_ortho_CordinateOriginX;//������ͶӰģʽ�µ��ε�x��������
	float m_ortho_CordinateOriginY;//������ͶӰģʽ�µ��ε�y��������
	float m_ortho_CordinateXYScale;//������ͶӰģʽ�µ��ε�x,y����ı���
	
	AllocUnAlloc2D3D m_AllocUnAlloc2D3D;//��������ʵ�ֶ�һά����ά����ά�������������ڴ���������
	BOOL m_BhasInitOCI;//��ʶ�Ƿ��ʼ��OCI
	int m_nMapSize;//��¼�����ӿ��С,��Ⱦ����ʹ��
	long m_Radius;//��Χ��뾶,����ʵ�ֶԵ��μ���(λ�ڰ�Χ��뾶�Ա�ĵ��ο鲻�����)
	float m_lodScreenError;//�趨����Ļ���

	//�Ӿ�����ð뾶
	long m_R;
	long m_r;
	
	
	//���β�������
	int m_loddem_StartRow;//�洢����ĵ��ο����ʼ��
	int m_loddem_StartCol;//�洢����ĵ��ο����ʼ��
	int m_loddem_EndRow;//�洢����ĵ��ο�Ľ�����
	int m_loddem_EndCol;//�洢����ĵ��ο�Ľ�����
	float **m_pHeight_My;//�洢��������ӿ�ĸ̵߳�
	int m_LodDemblockNumber; //�洢�����صĵ��ο�����
	double m_DemBlockCenterCoord[MAX_TEXTURENUM][2]; //�洢�����صĵ��ο����Ĵ������
	int m_lodDemBlock[MAX_TEXTURENUM][4];//�洢����ĵ��ο���к�,�к�,����ĵ��ο�����
	bool *m_pbm_DemLod;//��ʶ���ο��Ƿ񱻵���
	int **m_DemLod_My;//�洢��������ӿ���к�,�кŵ���Ϣ
	int m_DemLodIndex[MAX_TEXTURENUM];//�洢����ĵ����ӿ��������
	int *m_tempDemLodIndex;//�洢ǰһDEM�ӿ������
	int *m_bsign;//��ʶ������ĵ��ο��Ƿ�������(��ֵΪ1,��ʾ����ĵ����ӿ�������,=0,��ʾδ�������,λ���Ӿ�����,���޳�����)
	bool **m_pbQuadMat;//��ʶ�����ӿ�Ľڵ��Ƿ���Ҫ�����ָ�
	float  m_maxHeight,m_minHeight;//DEM���ݵ�������С�߳�ֵ
	float m_heighScale;//DEM���ݵ�߳�ʽ���ű���( <1:�̼߳�С =1:�̲߳��� >1:�߳�����)
	bool m_bLoadInitDemData;//��ʶ���س�ʼ�����κ�Ӱ�������Ƿ�ɹ�
	
	//�����������
	double m_Texturexy[MAX_TEXTURENUM][4];//�洢�����Ӱ�������ӿ�����º����Ͻ�x,y����
	int m_demTextureID[MAX_TEXTURENUM];//�洢�����Ӱ�������ӿ������ID,���ڰ�����
	int m_currebtPhramid; //�洢��ǰӰ�������LOD����
	CTexture m_texturesName; //����CTexture��ı���,����ʵ��Ӱ������ļ��� 
	CTexture m_cTxtSky;//����CTexture��ı���,����ʵ�ֱ����������ļ��� 
	
	
	//����������� 
	BOOL m_bCamraInit;//��ʶ����Ƿ��ʼ�� 
	CVector3 m_vPosition;	//����ӵ�����
	CVector3 m_vView;		//����۲������
	CVector3 m_vUpVector;	//���������άʸ��
	CVector3 m_oldvPosition;//���ǰһ�ӵ�����
	float m_viewHeight;//�ӵ�߶�
	float m_oldviewHeight;//ǰһ�ӵ�߶�
	float m_camraDistence;//������� 
	CVector3 m_originView;//�����ʼ�ӵ�����
	CVector3	m_originPosition;//�����ʼ�۲������
	
	
	//���ڼ�������²�����CVector3���ͱ���
	CVector3 m_vStrafe;		
	CVector3 View;		

	//ˢ��Ƶ�ʲ���
	float mTimeElaps; //���ڼ���ˢ��Ƶ�ʵ�ʱ��ֵ
	int nCountFrame;//���Ƶ�֡��
	
	//��Ļ����������
	BOOL    m_checkt; //��ʶ�Ƿ����Ļ����������
	long	m_maxTrinum;//�������������
	long	m_minTrinum;//��С����������
	float	m_k1; //�Ŵ����
	float	m_k2;//��С����

	int m_Drawmode; //����ģʽ(1://�߿�ģʽ  2://����ģʽ	3://����ģʽ)
 	BOOL m_stereo;  //�Ƿ�����ģʽ(TRUE:���� FALSE:������)
	BOOL m_bShowbreviary;//�Ƿ���ʾ������ͼ
	
	//�Ӿ������
	float m_sectorStartAngle,m_sectorEndAngle;
	double m_triPtA[2],m_triPtB[2],m_triPtC[2];
	Point m_Viewpolygon[3];	 //�洢�ӿ��������ε����������
	//�洢�ӿ��������ε�����������е������С����
	double m_Viewpolygon_Minx,m_Viewpolygon_Miny,m_Viewpolygon_Maxx,m_Viewpolygon_Maxy;

	
	//��Ⱦ����
	int  m_RenderDemblockNumber;//��Ⱦ�ĵ��ο�����
	int mCurrentTextID;//��ǰ��Ⱦ���ο������ID��
	int m_CurrentDemArrayIndex;//��ǰ��Ⱦ���ο����������

	//��ʾ�б���� 
	GLuint m_clockList; //ʱ��ָ������ʾ�б�
	GLuint m_SkyList;//���������ʾ�б�
	GLuint m_TerrainList;
	GLuint m_TerrainZoomroadList;
	GLuint m_NavigateList;
	GLuint m_HazardList;
	GLuint m_HazardList_Ortho;
	GLuint m_TunnelDMList;//���������ʾ�б�

	GLuint m_FAHPList;
	GLuint m_Rail3DwayList; //��·��άģ����ʾ�б�(͸��ͶӰģʽ)
	GLuint m_Rail3DwayList_Ortho;//��·��άģ����ʾ�б�(����ͶӰģʽ)
	GLuint m_Rail3DwayList_Ortho_Multi;
	GLuint m_QDList;//�����Ŷ���ʾ�б�
	GLuint m_QMList;
	GLuint m_QLanList;//����������ʾ�б�
//	GLuint m_TrainList;// ��ģ�͵�
	GLuint m_SelectBridgeList;//
	

	CalCulateF mCalF;//�Ӿ�����㹫������� 

	//�洢�����С�̶߳�ӦϷ���̡�����ɫ����ɫֵ
	float minZ_color_R,minZ_color_G,minZ_color_B;
	float maxZ_color_R,maxZ_color_G,maxZ_color_B;
	
	//�ռ��ѯ��־����
	int		m_shizxLength;//��ѯ��־��ʮ���߳���
	int		m_shuzxHeight;//��ѯ��־����ֱ�߳���
	int m_QueryLineWidth;//��ѯ��־�ߵĿ��
	int m_QueryColorR,m_QueryColorG,m_QueryColorB;//��ѯ��־�ߵ���ɫ(��,��,��)
	
	//�ռ��ѯ��־
	BOOL m_bSearchCorrdinate;
	BOOL m_bSearchDistence;
	BYTE m_QueryType; //��ʶ�ռ��ѯ���
	int m_bSearchDistencePtNums;//��ѯʱ��ȡ�Ŀռ����
	double pt1[3],pt2[3];//�洢��ѯ������
	long m_linePtnums;//��ǰ��·������ƽ�������
	long m_oldlinePtnums; //ԭ����·������ƽ�����
	
	
	bool m_bmouseView;	//�Ƿ��������������
	POINT m_oldMousePos;//ǰһ���λ��
	
	//�����ת����
	float	m_Step_X; //�����X�����ƶ��Ĳ���(������)
	float	m_Step_Z; //�����Z�����ƶ��Ĳ���(������)
	float Derx;	//����ӵ���X�����ϵı仯��
	float Derz;	//����ӵ���Z�����ϵı仯��

	float m_xTrans;	//��X�������ƶ��ľ���(���̿���)
	float m_zTrans;	//��Z�������ƶ��ľ���(���̿���)
	int m_keynumber;//��ʶ���̰���ֵ

	BYTE m_ViewType;   // ��ʶͶӰ��ʽ���
	float m_ViewXYscale;//�洢�ӿڸ߿����
	float m_OrthoViewSize;//����ͶӰģʽ���Ӿ����С
	float m_OrthotranslateX,m_OrthotranslateY;//����ͶӰģʽ��X�᷽���Y�᷽���ƶ��ľ���ֵ
	BYTE m_OrthoZommPan; //����ͶӰģʽ�³�������ģʽ
	//��������ʱ��¼���δ��ڵ����º�����x,y����
	int m_OrthoZoomWindowRect_x1,m_OrthoZoomWindowRect_y1,m_OrthoZoomWindowRect_x2,m_OrthoZoomWindowRect_y2;
	int m_preX,m_preY; //ǰһ����
	int m_currentX,m_currentY;//��ǰ����
	int m_pushNumb;//��������
	
	BOOL b_haveMadeRail3DwayList; //�Ƿ��Ѿ�����ά��·��ʾ�б�(͸��ͶӰģʽ��)
	BOOL b_haveMadeRail3DwayList_Ortho;//�Ƿ��Ѿ�����ά��·��ʾ�б�(����ͶӰģʽ��)
	BOOL b_haveTerrainZoomroadList;///��·��ά��ģ���Ƿ����˵���TINģ�͵���ʾ�б�
	
	Bridge m_Bridge; //����
	Tunnel  m_Tunnel; //���
	Railway m_Railway; //��··���ṹ
	
	
	
	C3DSModel *g_3dsModels; 
	BOOL bHaveLoadModel;
	double m_QD_minx,m_QD_miny,m_QD_maxx,m_QD_maxy,m_QD_minz,m_QD_maxz; 
	double m_QM_minx,m_QM_miny,m_QM_maxx,m_QM_maxy,m_QM_minz,m_QM_maxz;	
	double m_Train_minx,m_Train_miny,m_Train_maxx,m_Train_maxy,m_Train_minz,m_Train_maxz; 
	double m_TunnelDM_minx,m_TunnelDM_miny,m_TunnelDM_maxx,m_TunnelDM_maxy,m_TunnelDM_minz,m_TunnelDM_maxz; 
	

	CTexture m_txture;
	CTexture m_cTxtureDetail;
	CTexture m_txt;
	CTexture m_cTxtDetail;
	CTexture m_LitLodtextureName;
	
	CTexture m_cTxtureBP; //·����������
	CTexture m_cTxtureLJ;//·������
	CTexture m_cTxtureGdToLJ;//������������
	CTexture m_cTxtureRailway;//�������
	CTexture m_cTxtureSuigou;//ˮ������
	CTexture m_cBridgeHpm; ////��ͷ�·�����������
	CTexture m_cBridgeHL; //����
	CTexture m_cTxturePT;//����ƽ̨����	
	CTexture m_cTunnel;//�����ǽ����
	CTexture m_cTunnel_dm;//�����������
	CTexture m_cTunnel_dmwcBp;//�����������������
	

	//����·������
	GLfloat m_StaticHeight;		//�̶����и߶�
	GLfloat m_ViewUpDown;		//�ӽ���,����
	int m_flyspeed;//����ʱ�ļ�ʱ��ʱ���� 
	BOOL m_PathFlag;//�Ƿ��������·��
	
	int m_bridgeColorR,m_bridgeColorG,m_bridgeColorB; //������ɫ	
	CArray<PCordinate,PCordinate> PtBridgeHPUp;
	CArray<PCordinate,PCordinate> PtBridgeHPDown;
	
	BOOL b_haveGetRegion;//��ʶ�Ƿ�����·�������
	
	double m_PreZooomLC;//����ʱ��¼ǰһ���
	double m_CurZooomLC;//����ʱ��¼��ǰ���
	
	CString m_3DSfilename_QD; //�Ŷ�ģ���ļ�����
	CString m_3DSfilename_TunnelDM; //�������ģ���ļ�����
	
	float m_NorthPtangle; //ָ�����ʼָ��Ƕ�
	
	CDXF mdxf; //����DXF����
	

	vertexSet m_Vertices; //�洢��������
	triangleSet m_Triangles; //�洢����������

	BOOL m_bSelectFlyPath; //��ʶ�ڽ��з���·����ѡȡ 
	BOOL m_ShowFlyPath; //��ʶ�Ƿ���ʾ����·��

	BYTE m_FlyHeightType;//��ά��������(�̶��߶�����,�̶��߲�����)
	

	//¼��AVI����
	int m_MovieWidth;  //AVI�Ŀ��
	int m_MovieHeight; //AVI�ĸ߶� 
	int m_MoviemaxWidth;  //AVI�������
	int m_MoviemaxHeight; //AVI�����߶� 
	int m_AVIFrame;  //AVI��׽֡��
	CString m_AviFilename; //AVI�ļ���
	BOOL m_Beginrecording;       //��ʼ¼��AVI��Ƶ�����ı�־
	CAVICapture *m_movieCapture; //��׽����
	bool m_Recording; //��ʶ�Ƿ����ڲ�׽��Ƶ����
	

//	
	//¼��ͼ�����в���
	CClientCapture CapturedImage;
	CString m_RecordPicturename; //¼��ͼ������
    int		m_PictureNumbers; //¼��ͼ�������
	int		m_recordPictSpeed;  //�ɼ�ͼ���Ƶ�ʣ���ÿ�����ٺ���¼��һ��ͼ��
	BOOL	m_RecordPicture;     //¼��ͼ�����еı�־
	CRect m_rcPrintRect;  //��¼ͼ��ͻ�����С
	
	BOOL SetupPixelFormat();
	BOOL InitializeOpenGL(CDC *pDC);
	BOOL LoadInitDemData();

	Snow m_snows;
	CWinThread* m_lpThread;
	
};

#ifndef _DEBUG  // debug version in T3DSystemView.cpp
inline CT3DSystemDoc* CT3DSystemView::GetDocument()
   { return (CT3DSystemDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_T3DSYSTEMVIEW_H__3A8D7F07_F2EE_46F8_A484_C22327088E9C__INCLUDED_)
