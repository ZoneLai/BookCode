// DXF.cpp: implementation of the CDXF class.
 
 

#include "stdafx.h"
#include "DXF.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
// Construction/Destruction
 

CDXF::CDXF()
{

}

CDXF::~CDXF()
{

}

//��ʼ����ʵ��
void CDXF::DxfBeginDrawEnties(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SECTION\n"); //��������һ���εĿ�ʼ
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("ENTITIES\n"); 
}

//����ֱ��
void CDXF::DxfDraw_Line(CStdioFile* Dxffile,CString Layername,int color,double x1, double y1, double z1, double x2, double y2, double z2)
{
	CString tt1[3],tt2[3],ttcolor;

	//��(x1,y1,z1)����ת��Ϊ�ַ���
	tt1[0].Format ("%.3f",x1);
	tt1[1].Format ("%.3f",y1);
	tt1[2].Format ("%.3f",z1);

	//��(x2,y2,z2)����ת��Ϊ�ַ���
	tt2[0].Format ("%.3f",x2);
	tt2[1].Format ("%.3f",y2);
	tt2[2].Format ("%.3f",z2);
	
	ttcolor.Format("%d",color);//����ɫֵת��Ϊ�ַ���

	Dxffile->WriteString ("0\n"); 
	Dxffile->WriteString ("LINE\n"); //��ʶֱ�߿�ʼ
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //����
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString (ttcolor+"\n"); //��ɫ
	Dxffile->WriteString ("6\n");
	Dxffile->WriteString ("CONTINUOUS\n"); //����
	Dxffile->WriteString ("10\n");  
	Dxffile->WriteString (tt1[0]+"\n"); //x1����
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n"); //y1����
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt1[2]+"\n"); //z1����
	
	Dxffile->WriteString ("11\n");
	Dxffile->WriteString (tt2[0]+"\n"); //x2����
	Dxffile->WriteString ("21\n");
	Dxffile->WriteString (tt2[1]+"\n"); //y2����
	Dxffile->WriteString ("31\n");
	Dxffile->WriteString (tt2[2]+"\n"); //z2����
}

//���Ƶ�
void CDXF::DxfDraw_Point(CStdioFile* Dxffile,CString Layername, int color,double x, double y, double z)
{
	CString tt2[3],ttcolor;;

	//��(x,y,z)����ת��Ϊ�ַ���
	tt2[0].Format ("%.3f",x);
	tt2[1].Format ("%.3f",y);
	tt2[2].Format ("%.3f",z);

	ttcolor.Format("%d",color);//����ɫֵת��Ϊ�ַ���
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("POINT\n");//��ʶ�㿪ʼ
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //����
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString (ttcolor+"\n"); //��ɫ
	Dxffile->WriteString ("6\n");
	Dxffile->WriteString ("CONTINUOUS\n"); //����
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt2[0]+"\n"); //���x����
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt2[1]+"\n"); //���x����
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt2[2]+"\n"); //���z����
}

//���ƶ����
void CDXF::DxfDraw_PolyLine(CStdioFile* Dxffile,CString Layername, double x, double y, double z)
{
	CString tt1[3];
	
	//��(x,y,z)����ת��Ϊ�ַ���
	tt1[0].Format ("%.3f",x);
	tt1[1].Format ("%.3f",-y); 
	tt1[2].Format ("%.3f",z);


	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("VERTEX\n");//��ʶ���㿪ʼ
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //����
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt1[0]+"\n"); //���x����
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n"); //���y����
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt1[2]+"\n"); //���z����
}

//�������ƶ����
void CDXF::DxfEnd_polyline(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SEQEND\n"); //��ʶ����,������ʵ��������Ѿ�ȫ����¼����
}

//���ƶ����
void CDXF::DxfDraw_Polygon(CStdioFile* Dxffile,CString Layername, double x, double y, double z)
{
	CString tt,tt1[3];

	//��(x,y,z)����ת��Ϊ�ַ���
	tt1[0].Format ("%.3f",x);
	tt1[1].Format ("%.3f",y);
	tt1[2].Format ("%.3f",z);
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("VERTEX\n");//��ʶ���㿪ʼ
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //����
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt1[0]+"\n");//���x����
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n");//���y����
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt1[2]+"\n");//���z����
}

//�������ƶ����
void CDXF::DxfEnd_polygon(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SEQEND\n");//��ʶ����,������ʵ��������Ѿ�ȫ����¼����
}

//����DXF�ļ�ͷ
void CDXF::DxfHeader(CStdioFile* Dxffile)
{
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SECTION\n"); //��������һ���εĿ�ʼ
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("HEADER\n"); //��ʶ����ο�ʼ
	Dxffile->WriteString ("9\n");

	Dxffile->WriteString ("$LIMMIN\n");//����ǰ�ռ�����·�ͼ�ν���
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("0\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$LIMMAX\n");//����ǰ�ռ�����Ϸ�ͼ�ν���
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("5000\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("420\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$VIEWCTR\n");//�洢��ǰ�ӿ�����ͼ�����ĵ�
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("430\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("210\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$VIEWSIZE\n"); //�ӿڴ�С
	Dxffile->WriteString ("40\n");
	Dxffile->WriteString ("5000\n");
	
	Dxffile->WriteString ("9\n");
	Dxffile->WriteString ("$TEXTSTYLE\n"); //��������
	Dxffile->WriteString ("7\n");
	Dxffile->WriteString ("HZ\n");
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("ENDSEC\n"); //������һ�ν�����
	
}

//����ֱ������
void CDXF::DxfLineType(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("SECTION\n"); //��������һ���εĿ�ʼ
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("TABLES\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("TABLE\n");
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("LTYPE\n");
	
	Dxffile->WriteString ("70\n");
	Dxffile->WriteString ("1\n");
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("LTYPE\n");
	
	Dxffile->WriteString ("2\n");
	Dxffile->WriteString ("CONTINUOUS\n");
	Dxffile->WriteString ("70\n");
	Dxffile->WriteString ("64\n");
	Dxffile->WriteString ("3\n");
	Dxffile->WriteString ("Solid line\n");
	Dxffile->WriteString ("72\n");
	Dxffile->WriteString ("65\n");
	Dxffile->WriteString ("73\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("40\n");
	Dxffile->WriteString ("0.0\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("ENDTAB\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("ENDSEC\n");//������һ�ν�����
}

//DXF�ļ�����
void CDXF::DxfSectionEnd(CStdioFile* Dxffile)
{
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("ENDSEC\n");//������һ�ν�����
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("EOF\n"); //�������DXF �ļ�������
	Dxffile->Close ();
}

//��ʼ���ƶ���߱�־
void CDXF::DxfStart_polyline(CStdioFile* Dxffile,CString Layername,double elevation,float startWidth,float endWidth,int mcolor)
{
	CString tt;
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("POLYLINE\n"); //��ʶΪ����� POLYLINE
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString (Layername+"\n"); //����
	Dxffile->WriteString ("66\n");
	Dxffile->WriteString ("1\n");
	Dxffile->WriteString ("62\n");//��ɫ
	tt.Format("%d\n",mcolor);
	Dxffile->WriteString (tt);  
	Dxffile->WriteString ("70\n");
	Dxffile->WriteString ("0\n");   //�Ƿ���(=0:����� =1:���)
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("30\n");
	tt.Format ("%.3f",elevation);
	Dxffile->WriteString (tt+"\n");
	Dxffile->WriteString ("40\n"); //���
	tt.Format("%.2f\n",startWidth); //��ʼ�߶ο��
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("41\n");
	tt.Format("%.2f\n",endWidth);//��ֹ�߶ο��
	Dxffile->WriteString (tt);
}

//��ʼ���ƶ���α�־
void CDXF::DxfStart_polygon(CStdioFile* Dxffile,double elevation)
{
	CString tt;
	tt.Format ("%.3f",elevation); //���
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("POLYLINE\n");
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString ("poline_layer\n");
	Dxffile->WriteString ("66\n");
	Dxffile->WriteString ("1\n");
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString ("4\n"); //��ɫ
	Dxffile->WriteString ("70\n");
	Dxffile->WriteString ("1\n"); //�Ƿ���(=0:����� =1:���)
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString (tt+"\n");//���
	Dxffile->WriteString ("40\n");
	Dxffile->WriteString ("0\n");//��ʼ�߶ο��
	Dxffile->WriteString ("41\n");
	Dxffile->WriteString ("0\n");//��ֹ�߶ο��
}


void CDXF::DxfDraw_Circle(CStdioFile *Dxffile, double centerx, double centery, float R, int mcolor)
{
	CString tt;
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("CIRCLE\n");
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString ("Circle_layer\n");
	Dxffile->WriteString ("62\n");
	tt.Format("%d\n",mcolor);
	Dxffile->WriteString (tt);  
	Dxffile->WriteString ("10\n");
	tt.Format("%f\n",centerx);
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("20\n");
	tt.Format("%f\n",centery);
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("30\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("40\n");   
	tt.Format("%f\n",R);
	Dxffile->WriteString (tt);
}

void CDXF::DxfDraw_Text(CStdioFile *Dxffile, CString strlayername, double x, double y, float HW_Scale, int fonhHeight, float InAngle, CString strText, int style)
{
	CString tt,tt1[3];
	
	tt1[0].Format ("%.3f",x);
	tt1[1].Format ("%.3f",y);
	
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("text\n");
	Dxffile->WriteString ("8\n");
	Dxffile->WriteString ("layrtname\n");
	Dxffile->WriteString ("62\n");
	Dxffile->WriteString ("2\n"); 
	Dxffile->WriteString ("10\n");
	Dxffile->WriteString (tt1[0]+"\n");
	Dxffile->WriteString ("20\n");
	Dxffile->WriteString (tt1[1]+"\n");
	Dxffile->WriteString ("40\n");
	tt.Format("%d\n",fonhHeight);
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("1\n");
	Dxffile->WriteString (strText+"\n");
	Dxffile->WriteString ("41\n");
	tt.Format("%f\n",HW_Scale);
	Dxffile->WriteString (tt);
	Dxffile->WriteString ("71\n");
	Dxffile->WriteString ("0\n");
	Dxffile->WriteString ("50\n");
	tt.Format("%f\n",InAngle);
	Dxffile->WriteString (tt);
	
	
	
	Dxffile->WriteString ("7\n");
	tt.Format("%d\n",style);
	Dxffile->WriteString (tt);
}
