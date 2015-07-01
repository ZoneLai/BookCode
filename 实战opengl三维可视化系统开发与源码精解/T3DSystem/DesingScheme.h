 
 
 

#if !defined(AFX_DESINGSCHEME_H__5B5184D2_8345_4FB9_A7DA_9D8B33E76043__INCLUDED_)
#define AFX_DESINGSCHEME_H__5B5184D2_8345_4FB9_A7DA_9D8B33E76043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXSCHEMENUMS 25

//��ά������ṹ
typedef struct  
{
	double x;	//x����
	double y;	//y����
	double z;	//z����
}Cordinate3D, *PCordinate3D;


//��ˮ���ܽṹ
typedef struct  
{
	Cordinate3D SuiGouL[6];//���ˮ���ṹ
	Cordinate3D SuiGouR[6];//���ˮ���ṹ
	BOOL bhaveSuiGou_L;//��¼����Ƿ���ˮ�� 
	BOOL bhaveSuiGou_R;//��¼�Ҳ��Ƿ���ˮ��
	
}PaiSuiGou, *PPaiSuiGou;


//���½ṹ
typedef struct  
{
	Cordinate3D Hp[3];//һ�׻��µĻ�������ά����
	float h; //
	float m;
	float b;
	int style;//��������
}HuPo, *PHuPo;

//·���ܽṹ
typedef struct  
{
	HuPo HuPo_L[3];//��໤�½ṹ
	int Huponums_L;//��໤�¼���
	HuPo HuPo_R[3];//�Ҳ໤�½ṹ
	int Huponums_R;//�Ҳ໤�¼���
	int TW_left;//TW_left=-1:·ǵ  0:����ƽ��   1:·�� 99:�����м��
	int TW_right;//TW_right=-1:·ǵ  0:����ƽ��   1:·��  99:�����м��
	double Lc;//���
	CString strJDStyle;// 
}LuQianHuPo,*PLuQianHuPo;

typedef struct 
{
	long InsertIndex;
	CArray<PLuQianHuPo,PLuQianHuPo> tempHuPo;
}LuQianHuPoTemp,*PLuQianHuPoTemp;

//��·�ṹ
typedef struct  
{
	double x1; //�����������
	double y1;
	double z1;
	
	double x2;//�Ҳ���������
	double y2;
	double z2;

	int TW_left; //�����������
	int TW_right;//�����������
	float mAngle;//��ǰ��ת�Ƕ�
	float QDHeight;//�Ŷո߶�
}Railway3DCordinate, *PRailway3DCordinate;


//��·��ά���ۺϽṹ
typedef struct  
{
	double x;//���x����
	double y;//���y����
	double z;//���z����
	CString strJDStyle;
	float dmh; //��ĵ���߳�
	float Derh;//��ĸ߲�
	double Lc;//������
}Cordinate, *PCordinate;

//����ṹ
typedef struct  
{

	double x1;//������ߵ��x����
	double y1;//������ߵ��y����
	double z1;//������ߵ��z����
	
	double x2;//����Ҳ�ߵ��x����
	double y2;//����Ҳ�ߵ��y����
	double z2;//����Ҳ�ߵ��z����
	
	int Tunnnelindex;//���������·����е�������
	CString name;//�������
	CArray<PCordinate,PCordinate> tunnelArc; //����ڶ���Բ����ṹ
	
}Railway3DTunnnel, *PRailway3DTunnnel;

//�������ṹ 
typedef struct  
{
	float	height; //����߶�
	float	Archeight; //���Բ���߶�
	float	WallHeight; //�����ǽ�߶�
	float	ArcSegmentNumber;//���Բ���ֶ���
	float	width; //������
	float	H;//���Բ�����������ϵĸ߶�
	float	L;//������Ŷ���������������Ŀ�� 
	
}Tunnel;

//�����������Ϣ�ṹ
typedef struct 
{
	double StartLC; //�������������ʼ���
	double EndLC;//������������յ����
	float mStartangle; //������������ڶ˽Ƕ�
	float mEndAngle;  //������������ڶ˽Ƕ�
	int startIndex; //���ڶ�������
	int endIndex;//���ڶ˶�������
	Cordinate StartLeftXYZ;//���ڶ����ߵ��x,y,z����
	Cordinate StartRightXYZ;//���ڶ��Ҳ�ߵ��x,y,z����
	Cordinate EndLeftXYZ;//���ڶ����ߵ��x,y,z����
	Cordinate EndRightXYZ;//���ڶ��Ҳ�ߵ��x,y,z����
	CArray<PCordinate,PCordinate> m_ReginPt_Start;	//���/�����������߽���·��(�������)
	CArray<PCordinate,PCordinate> m_ReginPt_End;	//���/�����������߽���·��(�������)
}TunnnelBridgeInformation, *PTunnnelBridgeInformation;

//�����ṹ
typedef struct  
{
	double x1; //�������x����
	double y1;//�������y����
	double z1;//�������z����
	double Lc1; //����������
	double x2;//�����յ�x����
	double y2;//�����յ�y����
	double z2;//�����յ�z����
	double Lc2;//�����յ����
	CString name;//��������
}CordinateBridge, *PCordinateBridge;

//����ģ�ͽṹ
typedef struct  
{
	float	m_Bridge_HLSpace;	//�������˼��
	float	m_Bridge_HLWidth;	//�������˿��
	float	m_Bridge_HLHeight;	//�������˸߶�
	float	m_Bridge_QDSpace;	//�Ŷռ��
	int     m_Bridge_HPangle;  //��ͷ�������

}Bridge;

//��Ʒ�����Ϣ�ṹ
typedef struct 
{
	CString	Schemename;		//��������			
	CString strDesigngrade;	//��Ƶȼ�			
	CString strDraughtstyle;//ǣ������			
	CString strBlocomotiveStyle;//��������		
	CString strCBbsStyle;				
	CString strTerrainstyle;	//�������		
	CString strEngineeringcondition;	//��������
	int		designspeed;			//����ٶ�	
	int		minRadius;				//��С���߰뾶	
	int		dxfLength;				//��������С����	
	float	minSlopeLength;			//��С�³�	
	float	maxSlope;				//����¶�	
	float	maxSlopePddsc;			//����¶ȴ�����
	double	StartLC;				//��ʼ���		
	double	EndLC;					//��ֹ���	
	int Index;						//��������	
}SchemeData, *PSchemeData;

//��·��ƽ���ṹ
typedef struct  
{
	CString  ID;	//����ID��
	double  JDLC;	//�������
	float Alfa;		//����ת��
	float fwj;		//����ƫ��1
	float fwj2;		//����ƫ��2
	float T;		//���߳�
	int L0;			//�������߳�
	float L;		//���߳�
	float Ly;		//
	float Jzxc;		//��ֱ�߳�
	double HZ;		//��ֱ�����
	double ZH;		//ֱ�������
	double HY;		//��Բ�����
	double YH;		//Բ�������
	long R;			//���߰뾶
	float E;		//��ʸ��
	float P;		//
	float Dist;		//
	int  RoateStyle;//��ת����(��ת,��ת)
	double x; //����x����
	double y;//����y����
	double z;//����z����
	
	PCordinate ZH_xy;//ֱ��������
	PCordinate HZ_xy;//��ֱ������
	PCordinate YH_xy;//Բ��������
	PCordinate HY_xy;//��Բ������
	
	double Cneterx; //����Բ��x����
	double Cnetery;//����Բ��y����
	
}LineCurve, *PLineCurve;

//·������ṹ
typedef struct  
{
	float   m_Railway_width; //·�������ܿ��
	float	m_Lj_width;	//·����
	float	m_Lj_Dh;	//�������ŵĸ߶�
	float   m_GuiMianToLujianWidth;//���쵽���ľ���
	float	m_TieGui_width;	//������
	
}Railway;


typedef struct  
{
	long boreLayerID;
	BOOL bDraw;
}BoreLayerDraw, *PBoreLayerDraw;


typedef struct  
{
	double StartPt[3];
	double EndPt[3];
	int mlayerID;
}BoreSectionLine, *PBoreSectionLine;


class CDesingScheme 
{
public:
	int GetBlockID(double x,double y);
	void GetTunnelcordinate(float TotalHeight,float Archeight,float WallHeight,float Width,int  ArcSegmentNumber);
	void GetTieGuicordinate(float Railwaywidth, float m_GDwidth);
	void GetZhenMucordinate(float ZhenMuJJ,float Railwaywidth);
	void drawBitmapFormFile(CString BitmapFilePath, CDC *pDC, CRect rect);
	float GetDistenceXYZ(double x1, double y1, double z1, double x2, double y2,double z2);
	void GetBirdgeQDcordinate(float BridgeQDJJ);
	void GetHs(double x0,double y0,double z0,float alfa,float mangle,int Style,double *px,double *py,double *pz);
	void GetHpD(double x,double y,double z,float mAngle,float mHpangle,double *ax,double *ay,double *az);
	float GetANgle(double x1,double z1,double x2,double z2);
	void GetBirdgeLGcordinate(float BridgeLGJJ);
	void Get3DLineModelLast(double x1, double y1, double z1,double x2, double y2, double z2, float fRailwayWidth, float LjWidth, float h_FromGmToLj,float mWidthGuiMianToLujian,float mAngleLujinaToBianPo,CString strJDstyle,CString strJDstyleNext,long index,double mLC);
	void Get3DLineModel(double x1,double y1,double z1,double x2,double y2,double z2,float fRailwayWidth,float LjWidth,float h_FromGmToLj,float mWidthGuiMianToLujian,float mAngleLujinaToBianPo,CString strJDstyle,CString strJDstyleNext,long index,double mLC);
	void InertHuPoPts();
	double GetDistenceXY(double x1,double y1,double x2,double y2);
	void GetYQXXY(double centerx,double centery, long R, int RoateStyle, float LL,float alfa,double HY_xy_x,double HY_xy_y,double YH_xy_x,double YH_xy_y, double *xc, double *yc);
	void GetQLXY(float L0,long R,int RoateStyle,float LL,float fwj,double ZH_xy_x,double ZH_xy_y,double HZ_xy_x,double HZ_xy_y,double *xc,double *yc,int Q_H_L);
	void LoadData(CString strSchemeName);
	int GetMinRfromCriterion(int mspeed,int EngineeringConditionStyle);
	int GetMinL0(int mRindex);
	CString GetLC(double LC);
	void SavePlaneCurveData();
	
	SchemeData SchemeDatass[MAXSCHEMENUMS];
	
	
	CArray<PLineCurve,PLineCurve> JDCurveElements;
	CArray<PLineCurve,PLineCurve> JDCurveElementss[MAXSCHEMENUMS];
	CArray<PCordinate,PCordinate> PtS_JD;
	CArray<PCordinate,PCordinate> PtS_3DLineZX[MAXSCHEMENUMS];;

	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_Railway3D[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayLj3D[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayLjToBP3D[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayBP3D[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_BridgeLG3D[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_BridgeQD3D[MAXSCHEMENUMS];
	CArray<PRailway3DTunnnel,PRailway3DTunnnel> PtS_Tunnel3D[MAXSCHEMENUMS];
	CArray<PTunnnelBridgeInformation,PTunnnelBridgeInformation> TunnelInfor[MAXSCHEMENUMS];
	CArray<PTunnnelBridgeInformation,PTunnnelBridgeInformation> BridgeInfor[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayZhenMu[MAXSCHEMENUMS];
	CArray<PRailway3DCordinate,PRailway3DCordinate> PtS_RailwayTieGui[MAXSCHEMENUMS];

	CArray<PPaiSuiGou,PPaiSuiGou> PtS_PaiSuiGou[MAXSCHEMENUMS];

	CArray<PLuQianHuPo,PLuQianHuPo> PtS_HuPo[MAXSCHEMENUMS];
	CArray<PLuQianHuPoTemp,PLuQianHuPoTemp> PtSHuPoTemp;
	
	
	CArray<long,long>m_borelayerID;
	CArray<PBoreLayerDraw,PBoreLayerDraw>m_BorelayerDraw;
	CArray<PBoreSectionLine,PBoreSectionLine> P_BoreSectionLine[3];
	BOOL bDrawTerrSurface;
	
	int m_minR160_L0[15][2];
	int m_minR140_L0[17][2];
	int m_minR120_L0[19][2];
	int m_minR100_L0[22][2];
	int m_minR80_L0[23][2];
	
	int m_minPriorityR160_L0[15];
	int m_minPriorityR140_L0[17];
	int m_minPriorityR120_L0[19];
	
	int  m_TotalSchemeNums;
	
	BOOL m_bHaveSaveScheme;
	
	CDesingScheme();
   	virtual ~CDesingScheme();

private:
	void GetTunnelArcCordinate(float TotalHeight, float Archeight, float WallHeight, float Width, int ArcSegmentNumber,double x1,double y1,double z1,double x2,double y2,double z2,float *mAngle);
	void GetBpJD(float H0, float Afla, float mangle, double x0, double z0,int bsignTW,int mLeftRight,double *tx,double *ty,double *tz);
	void GetDMJD(double x1, double y1, double z1,double x2, double y2, double z2,float L, float h0,double x0,double z0,int TW,int LeftRight,\
		double tx0,double ty0,double tz0,double tx1,double ty1,double tz1,double mLC,CString strJDstyle);
	float GetHBridgeHP(float L,float alfa,float mangle,double x0,double z0,int Style,double *xx,double *zz);
	int GetTW(double x,double z,float H);
	float GetH(float L, float Afla, float mAngle,double x0,double z0,int mLeftRight,double *xx,double *zz);
	void Get3DCorrdinate(double x1, double y1, double z1,double x2, double y2, double z2,float dx,float dz, float L,double *x11,double *y11,double *z11,double *x12,double *y12,double *z12,double *x21,double *y21,double *z21,double *x22,double *y22,double *z22 ,float *angle);
	void Save3DlineZXCorrdinateToDB();
	void Save3DlineZX();
	void SavePlaneCurveDataToDB();
	void InitMinR();
	void NeiChaDian(float ZHLength, double x1, double y1, double z1, double x2, double y2, double z2,double lc);
	float GetAlfa(int mTW);
		
	_RecordsetPtr m_pRecordset;
	HRESULT hr;
	_variant_t  Thevalue;  
	_variant_t RecordsAffected;
	
};

#endif // !defined(AFX_DESINGSCHEME_H__5B5184D2_8345_4FB9_A7DA_9D8B33E76043__INCLUDED_)





















