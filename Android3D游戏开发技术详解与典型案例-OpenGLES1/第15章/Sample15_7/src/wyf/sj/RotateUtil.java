package wyf.sj;

import android.util.Log;

/*
 * ����Ϊ��̬�����࣬�ṩ��̬����������
 * С��Ӧ�õ��˶�����
 */
public class RotateUtil
{
	//angleΪ���� gVector  Ϊ��������[x,y,z,1]
	//����ֵΪ��ת�������
	public static double[] xRotate(double angle,double[] gVector)
	{
		double[][] matrix=//��x����ת�任����
		{
		   {1,0,0,0},
		   {0,Math.cos(angle),Math.sin(angle),0},		   
		   {0,-Math.sin(angle),Math.cos(angle),0},		  
		   {0,0,0,1}	
		};
		
		double[] tempDot={gVector[0],gVector[1],gVector[2],gVector[3]};
		for(int j=0;j<4;j++)
		{
			gVector[j]=(tempDot[0]*matrix[0][j]+tempDot[1]*matrix[1][j]+
			             tempDot[2]*matrix[2][j]+tempDot[3]*matrix[3][j]);    
		}
		
		return gVector;
	}
	
	//angleΪ���� gVector  Ϊ��������[x,y,z,1]
	//����ֵΪ��ת�������
	public static double[] yRotate(double angle,double[] gVector)
	{
		double[][] matrix=//��y����ת�任����
		{
		   {Math.cos(angle),0,-Math.sin(angle),0},
		   {0,1,0,0},
		   {Math.sin(angle),0,Math.cos(angle),0},
		   {0,0,0,1}	
		};
		
		double[] tempDot={gVector[0],gVector[1],gVector[2],gVector[3]};
		for(int j=0;j<4;j++)
		{
			gVector[j]=(tempDot[0]*matrix[0][j]+tempDot[1]*matrix[1][j]+
			             tempDot[2]*matrix[2][j]+tempDot[3]*matrix[3][j]);    
		}
		
		return gVector;
	}		
	
	//angleΪ���� gVector  Ϊ��������[x,y,z,1]
	//����ֵΪ��ת�������
	public static double[] zRotate(double angle,double[] gVector)
	{
		double[][] matrix=//��z����ת�任����
		{
		   {Math.cos(angle),Math.sin(angle),0,0},		   
		   {-Math.sin(angle),Math.cos(angle),0,0},
		   {0,0,1,0},
		   {0,0,0,1}	
		};
		
		double[] tempDot={gVector[0],gVector[1],gVector[2],gVector[3]};
		for(int j=0;j<4;j++)
		{
			gVector[j]=(tempDot[0]*matrix[0][j]+tempDot[1]*matrix[1][j]+
			             tempDot[2]*matrix[2][j]+tempDot[3]*matrix[3][j]);    
		}
		
		return gVector;
	}
	
	public static float[] calculateABPosition
	(
		float tx,//����X����
		float ty,//����Y����
		float w,// ��Ļ���
		float h,// ��Ļ�߶�
		float left,//�ӽ�leftֵ
		float top,//�ӽ�topֵ
		float near,//�ӽ�nearֵ
		float far,//�ӽ�farֵ
		float alpha,//		 ������Ƕ�
		float cx,//�����x����
		float cy,//�����y����
		float cz//�����z����
	)
	{
		Log.d("tx,ty",tx+"|"+ty);		
		
		float k=tx-w/2;//�����ֻ���Ļƽ���ϴ��ص�����ĵ����X
		float p=h/2-ty;//�����ֻ���Ļƽ���ϴ��ص�����ĵ����Y
		
		float kNear=2*k*left/w;//����nearƽ��A�������ԭ�����X
		float pNear=2*p*top/h;//����nearƽ��A�������ԭ�����Y
		
		Log.d("kNear,pNear",kNear+"|"+pNear);
		
		float ratio=far/near;
		float kFar=ratio*kNear;//����farƽ��B������x
		float pFar=ratio*pNear;//����farƽ��B������y
		
		Log.d("kFar,pFar",kFar+"|"+pFar);

        float beforeNX=0+kNear;//�ƶ������ǰA������
        float beforeNY=0+pNear;
        float beforeNZ=-near;
        
        float beforeFX=0+kFar;//�ƶ������ǰB������
        float beforeFY=0+pFar;
        float beforeFZ=-far;
        
        double[] beforeN=new double[]{beforeNX,beforeNY,beforeNZ,1};       
        double[] afterN=yRotate(Math.toRadians(alpha),beforeN);//����ת����������A������
        
        double[] beforeF=new double[]{beforeFX,beforeFY,beforeFZ,1};       
        double[] afterF=yRotate(Math.toRadians(alpha),beforeF);//����ת����������B������
		
		return new float[]//�������յ�AB��������
		{
				(float)afterN[0]+cx,(float)afterN[1]+cy,(float)afterN[2]+cz,
				(float)afterF[0]+cx,(float)afterF[1]+cy,(float)afterF[2]+cz
		};
	} 

}