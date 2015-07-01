package wyf.sj;

import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

public class Control {

	ZhuiTi zhuiTi;//����׵��
	float minX;//x����Сλ��
	float maxX;//x�����λ��
	float minY;//y����Сλ��
	float maxY;//y�����λ��
	float minZ;//z����Сλ��
	float maxZ;//z�����λ��
	boolean flag=true;//trueʱ��������
	float xOffset;//������X����λ��
	float yOffset;//������Y����λ��
	float zOffset;//������Z����λ��
	float vx;//x���ٶ�
	float vy;//y���ٶ�
	float vz;//z���ٶ�
	final float SPAN_TIME=0.2f;//��λʱ��
	final float V_UNIT=0.5f;
	
	float tempxOffset;//��ʱ�����������ж�x�᷽�������һ���Ƿ���������ײ
	float tempyOffset;
	float tempzOffset;

	public Control(ZhuiTi zhuiTi,float xOffset,float yOffset,float zOffset,float vx,float vy,float vz)
	{
		this.zhuiTi=zhuiTi;
		this.xOffset=xOffset;//��ȡX����λ��
		this.yOffset=yOffset;//��ȡY���ϵ�λ��
		this.zOffset=zOffset;//��ȡZ���ϵ�λ��
		this.vx=vx;
		this.vy=vy;
		this.vz=vz;
		init();//��ʼ��������С���λ��
		findMinMax();//��ø�����С���λ��
	}
	public void drawSelf(GL10 gl)
	{
		gl.glPushMatrix();
		gl.glTranslatef(xOffset, yOffset, zOffset);
		zhuiTi.drawSelf(gl);
		gl.glPopMatrix();
	}
	public void go(ArrayList<Control> al)
	{		
		//����ʱ��������Ƿ�����ײ�����������ٶȣ���û�����ƶ�����
		tempxOffset=xOffset+vx*SPAN_TIME;//X���ƶ�
		tempyOffset=yOffset+vy*SPAN_TIME;//Y���ƶ�
		tempzOffset=zOffset+vz*SPAN_TIME;//Z���ƶ�
		for(int i=0;i<al.size();i++)
		{
			Control ct=al.get(i);
			if(ct!=this)
			{
				float tempV=check(this,ct);				
				if(tempV>V_UNIT)//������ײ
				{
					this.vx=-this.vx;//�ĸ���������ٶȣ��÷����ϵ��ٶ��÷�
//					this.vy=-this.vy;
//					this.vz=-this.vz;
				}
				else
				{
					xOffset=tempxOffset;
					yOffset=tempyOffset;
					zOffset=tempzOffset;
				}
			}
		}
	}
	//��ʼ�������Сֵ
	public void init()
	{
		minX=Float.POSITIVE_INFINITY;
		minY=Float.POSITIVE_INFINITY;
		minZ=Float.POSITIVE_INFINITY;
		maxX=Float.NEGATIVE_INFINITY;
		maxY=Float.NEGATIVE_INFINITY;
		maxZ=Float.NEGATIVE_INFINITY;
	}
	public void findMinMax()
	{
		for(int i=0;i<zhuiTi.tempVerteices.length/3;i++)
		{
			//�ж�X�����С�����λ��
			if(zhuiTi.tempVerteices[i*3]<minX)
			{
				minX=zhuiTi.tempVerteices[i*3];
			}
			if(zhuiTi.tempVerteices[i*3]>maxX)
			{
				maxX=zhuiTi.tempVerteices[i*3];
			}
			//�ж�Y�����С�����λ��
			if(zhuiTi.tempVerteices[i*3+1]<minY)
			{
				minY=zhuiTi.tempVerteices[i*3+1];
			}
			if(zhuiTi.tempVerteices[i*3+1]>maxY)
			{
				maxY=zhuiTi.tempVerteices[i*3+1];
			}
			//�ж�Z�����С�����λ��
			if(zhuiTi.tempVerteices[i*3+2]<minZ)
			{
				minZ=zhuiTi.tempVerteices[i*3+2];
			}
			if(zhuiTi.tempVerteices[i*3+2]>maxZ)
			{
				maxZ=zhuiTi.tempVerteices[i*3+2];
			}
		}
	}

	public float check(Control cA,Control cB)
	{		
		float xOver=calOver(cA.maxX+cA.tempxOffset,cA.minX+cA.tempxOffset,cB.maxX+cB.xOffset,cB.minX+cB.xOffset);
		float yOver=calOver(cA.maxY+cA.tempyOffset,cA.minY+cA.tempyOffset,cB.maxY+cB.yOffset,cB.minY+cB.yOffset);
		float zOver=calOver(cA.maxZ+cA.tempzOffset,cA.minZ+cA.tempzOffset,cB.maxZ+cB.zOffset,cB.minZ+cB.zOffset);
		return xOver*yOver*zOver;
	}
	
	public static float calOver(float amax,float amin,float bmax,float bmin)
	{
		float leftMax=0;
		float leftMin=0;
		float rightMax=0;
		float rightMin=0;
		
		if(amax<bmax)
		{
			leftMax=amax;
			leftMin=amin;
			rightMax=bmax;
			rightMin=bmin;
		}
		else
		{
			leftMax=bmax;
			leftMin=bmin;
			rightMax=amax;
			rightMin=amin;
		}
		
		if(leftMax>rightMin)
		{
			return leftMax-rightMin;
		}
		else
		{
			return 0;
		}
	}
}
