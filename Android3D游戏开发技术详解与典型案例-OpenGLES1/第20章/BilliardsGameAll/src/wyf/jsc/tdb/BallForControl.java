package wyf.jsc.tdb;
import java.util.ArrayList;
import javax.microedition.khronos.opengles.GL10;
import android.util.Log;

import static wyf.jsc.tdb.Constant.*;

//���ڿ��Ƶ�����
public class BallForControl 
{	
	MySurfaceView mSurfaceView;//����MySurfaceView������ 
	BallTextureByVertex btv;//���ڻ��Ƶ�����	
	int texId;//����ID	
	float xOffset;//�����Xλ��
	float zOffset;//�����Zλ��
	float yOffset=1;//�����yλ��
	//������ٶȣ�������һֱ���������˶������û��Y���ٶȣ�
	float vx;
	float vz;
	//������������еĸ����Ŷ�ֵ
	float angleTemp;//�Ƕ��Ŷ�ֵ
	float axisX;//��ת��������X����
	float axisZ;//��ת��������Z����
	float axisY=0;//��ת��������Y��������Ϊ�����������˶���ת��ƽ�������棬���û��Y������
	float distance;//���������ƶ��ľ���	
	float angleX;//��X��ת���ĽǶ�
	float angleY;//��Y��ת���ĽǶ�
	float angleZ;//��Z��ת���ĽǶ�
	public BallForControl(BallTextureByVertex btv,float xOffset,float zOffset,int texId)
	{
		this.btv=btv;
		this.xOffset=xOffset;
		this.zOffset=zOffset;
		this.texId=texId;
	}	
	public void drawSelf(GL10 gl)
	{//���������Լ�	
		gl.glPushMatrix();
		//�ƶ���ָ��λ��
		gl.glTranslatef(xOffset, BALL_Y*yOffset, zOffset);
		//����ת��
		gl.glRotatef(angleX, 1, 0, 0);
		gl.glRotatef(angleY, 0, 1, 0);
		gl.glRotatef(angleZ, 0, 0, 1);
		
		//����ת����ת����ת�ᴹֱ���˶�����ƽ�������棩
		if(angleTemp!=0)
		{
			gl.glRotatef(angleTemp, axisX, axisY, axisZ);
		}
		//������
		btv.drawSelf(gl,texId);		
		gl.glPopMatrix();
	}	
	//���յ�ǰ�ٶ���ǰ�˶�һ���ķ���
	public void go(ArrayList<BallForControl> ballAl,CollisionUtil cu)
	{	
		//�������ٶ�
		float vTotal=(float)Math.sqrt(vx*vx+vz*vz);
		//�����ٶ�С����ֵʱ��Ϊ��ֹͣ��
		if(vTotal<V_THRESHOLD)
		{
			distance=0;
			vx=0;
			vz=0;
			//angleTemp=0;
			return;
		}		
		
		//��¼��λ��
		float tempX=xOffset;
		float tempZ=zOffset;
		
		//�����ٶȲ�С����ֵ�����������һ����λ��
		xOffset=xOffset+vx*TIME_SPAN;
		zOffset=zOffset+vz*TIME_SPAN;
		
		boolean flag=false;//�Ƿ���������ײ  false-δ��ײ
		
		//������һ����λ�ú��ж��Ƿ���������ײ
		for(int i=0;i<ballAl.size();i++)
		{
			BallForControl bfcL=ballAl.get(i);
			if(bfcL!=this)
			{
				boolean tempFlag=cu.collision(this, bfcL);
				if(tempFlag)
				{
					flag=true;
				}
			}	
		}
		
		//ײa��
		float aX=-TABLE_AREA_WIDTH/2;
		float aZ=TABLE_AREA_LENGTH/2-EDGE_SMALL;     //�趨A������   
		float disSquare=(this.xOffset-aX)*(this.xOffset-aX)+(this.zOffset-aZ)*(this.zOffset-aZ);//�������A�ľ���
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;//�ٶ��跴
			flag=true;//��ײ��־Ϊ��Ϊtrue
		}
		
		//ײb��
		float bX=-TABLE_AREA_WIDTH/2;
		float bZ=MIDDLE/2;        
		disSquare=(this.xOffset-bX)*(this.xOffset-bX)+(this.zOffset-bZ)*(this.zOffset-bZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
		}
		
		//ײc��
		float cX=-TABLE_AREA_WIDTH/2;
		float cZ=-MIDDLE/2;        
		disSquare=(this.xOffset-cX)*(this.xOffset-cX)+(this.zOffset-cZ)*(this.zOffset-cZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
		}
		
		//ײd��
		float dX=-TABLE_AREA_WIDTH/2;
		float dZ=-TABLE_AREA_LENGTH/2+EDGE_SMALL;        
		disSquare=(this.xOffset-dX)*(this.xOffset-dX)+(this.zOffset-dZ)*(this.zOffset-dZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
		}
		
		//ײe��
		float eX=-TABLE_AREA_WIDTH/2+EDGE_SMALL;
		float eZ=-TABLE_AREA_LENGTH/2;        
		disSquare=(this.xOffset-eX)*(this.xOffset-eX)+(this.zOffset-eZ)*(this.zOffset-eZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
		}
		
		//ײf��
		float fX=TABLE_AREA_WIDTH/2-EDGE_SMALL;
		float fZ=-TABLE_AREA_LENGTH/2;        
		disSquare=(this.xOffset-fX)*(this.xOffset-fX)+(this.zOffset-fZ)*(this.zOffset-fZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
		}
		
		//ײg��
		float gX=TABLE_AREA_WIDTH/2;
		float gZ=-TABLE_AREA_LENGTH/2+EDGE_SMALL;        
		disSquare=(this.xOffset-gX)*(this.xOffset-gX)+(this.zOffset-gZ)*(this.zOffset-gZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
		}
		
		//ײh��
		float hX=TABLE_AREA_WIDTH/2;
		float hZ=-MIDDLE/2;        
		disSquare=(this.xOffset-hX)*(this.xOffset-hX)+(this.zOffset-hZ)*(this.zOffset-hZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
			Log.d("H Angle"+texId,"x="+this.xOffset+",z="+this.zOffset+", vx="+this.vx+",vz="+this.vz);
		}
		
		//ײi��
		float iX=TABLE_AREA_WIDTH/2;
		float iZ=MIDDLE/2;        
		disSquare=(this.xOffset-iX)*(this.xOffset-iX)+(this.zOffset-iZ)*(this.zOffset-iZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
		}
		
		//ײj��
		float jX=TABLE_AREA_WIDTH/2;
		float jZ=TABLE_AREA_LENGTH/2-EDGE_SMALL;        
		disSquare=(this.xOffset-jX)*(this.xOffset-jX)+(this.zOffset-jZ)*(this.zOffset-jZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
		}
		
		//ײk��
		float kX=TABLE_AREA_WIDTH/2-EDGE_SMALL;
		float kZ=TABLE_AREA_LENGTH/2;        
		disSquare=(this.xOffset-kX)*(this.xOffset-kX)+(this.zOffset-kZ)*(this.zOffset-kZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
		}
		
		//ײl��
		float lX=-TABLE_AREA_WIDTH/2+EDGE_SMALL;
		float lZ=TABLE_AREA_LENGTH/2;        
		disSquare=(this.xOffset-lX)*(this.xOffset-lX)+(this.zOffset-lZ)*(this.zOffset-lZ);
		if(disSquare<BALL_R_POWER_TWO)
		{
			this.vz=-this.vz;
			this.vx=-this.vx;
			flag=true;
		}
		
		//����˽ǾͲ�����ײ��
		if(flag==false)
		{
			//�ж��Ƿ����ĸ���̨����ײ
			if(this.zOffset<-BOTTOM_LENGTH/2f+BALL_R||this.zOffset>BOTTOM_LENGTH/2f-BALL_R)//��Χ
			{
				//���󵲰���ҵ��壬Z���ٶ��÷�
				this.vz=-this.vz;
				flag=true;
//				Log.d("coll 1"+texId,"x="+this.xOffset+",z="+this.zOffset+", vx="+this.vx+",vz="+this.vz);
			}
			if(this.xOffset<-BOTTOM_WIDE/2f+BALL_R||this.xOffset>BOTTOM_WIDE/2f-BALL_R)//��Χ
			{
				//��ǰ�����󵲰壬X���ٶ��÷�
				this.vx=-this.vx;
				flag=true;
//				Log.d("coll 2"+texId,"x="+this.xOffset+",z="+this.zOffset+", vx="+this.vx+",vz="+this.vz);
			}
			
			//
			if(this.zOffset>MIDDLE/2&&this.zOffset<BOTTOM_LENGTH/2-EDGE)//��Χ���
			{
				if(this.xOffset>TABLE_AREA_WIDTH/2-BALL_R||this.xOffset<-TABLE_AREA_WIDTH/2+BALL_R)//������ײ���
				{
					this.vx=-this.vx;				
					flag=true;
//					Log.d("coll 3"+texId,"x="+this.xOffset+",z="+this.zOffset+", vx="+this.vx+",vz="+this.vz);
				}
			}
			if(this.zOffset<-MIDDLE/2&&this.zOffset>-BOTTOM_LENGTH/2+EDGE)//�ڲ��Ҳ�
			{
				if(this.xOffset>TABLE_AREA_WIDTH/2-BALL_R||this.xOffset<-TABLE_AREA_WIDTH/2+BALL_R)//������ײ���
				{
					this.vx=-this.vx;
					flag=true;
//					Log.d("coll 4"+texId,"x="+this.xOffset+",z="+this.zOffset+", vx="+this.vx+",vz="+this.vz
//							+" MIDDLE/2"+(MIDDLE/2)+" BOTTOM_LENGTH/2-EDGE"+(BOTTOM_LENGTH/2-EDGE));
				}
			}
			if(this.xOffset>-BOTTOM_WIDE/2+EDGE&&this.xOffset<BOTTOM_WIDE/2-EDGE)//�ڲ� ������ײ���
			{
				if(this.zOffset>TABLE_AREA_LENGTH/2-BALL_R||this.zOffset<-TABLE_AREA_LENGTH/2+BALL_R)
				{
					this.vz=-this.vz;
					flag=true;
//					Log.d("coll 5"+texId,"x="+this.xOffset+",z="+this.zOffset+", vx="+this.vx+",vz="+this.vz);
				}
			}
			
			//������ab��cd����ײ���
			if(this.xOffset>-BOTTOM_WIDE/2&&this.xOffset<-TABLE_AREA_WIDTH/2)
			{
				//ab�ߣ�������ab֮������һ���ߣ���ʵ������Ϊ���ⷢ������������Ϊ��Ϊ�ߵ���ײ��ͷ�����ײ���ഫ�ֹ��¼���
				if((this.zOffset>MIDDLE/2-BALL_R&&this.zOffset<TABLE_AREA_LENGTH/4)||
						(this.zOffset<BOTTOM_LENGTH/2-EDGE+BALL_R&&this.zOffset>TABLE_AREA_LENGTH/4))
				{
					this.vz=-this.vz;
					flag=true;
//					Log.d("coll 6"+texId,"x="+this.xOffset+",z="+this.zOffset+", vx="+this.vx+",vz="+this.vz);
//					Log.d("coll 6"+texId,"BOTTOM_LENGTH/2-EDGE+BALL_R="+(BOTTOM_LENGTH/2-EDGE+BALL_R)+",TABLE_AREA_LENGTH/4="+(TABLE_AREA_LENGTH/4));
				}
				//cd�ߣ�������cd֮������һ���ߣ���ʵ������Ϊ���ⷢ������������Ϊ��Ϊ�ߵ���ײ��ͷ�����ײ���ഫ�ֹ��¼���
				if((this.zOffset<-MIDDLE/2+BALL_R&&this.zOffset>-TABLE_AREA_LENGTH/4)||
					(this.zOffset>-BOTTOM_LENGTH/2+EDGE-BALL_R&&this.zOffset<-TABLE_AREA_LENGTH/4))
				{
					this.vz=-this.vz;
					flag=true;
//					Log.d("coll 7"+texId,"x="+this.xOffset+",z="+this.zOffset+", vx="+this.vx+",vz="+this.vz);
//					Log.d("coll 7"+texId,"BOTTOM_LENGTH/2-EDGE+BALL_R="+(BOTTOM_LENGTH/2-EDGE+BALL_R)+",TABLE_AREA_LENGTH/4="+(TABLE_AREA_LENGTH/4));
				}
			}
			
			
			//������GH��IJ����ײ���
			if(this.xOffset>TABLE_AREA_WIDTH/2&&this.xOffset<BOTTOM_WIDE/2)
			{
				//gh�ߣ�������ab֮������һ���ߣ���ʵ������Ϊ���ⷢ������������Ϊ��Ϊ�ߵ���ײ��ͷ�����ײ���ഫ�ֹ��¼���
				if((this.zOffset<-MIDDLE/2+BALL_R&&this.zOffset>-TABLE_AREA_LENGTH/4)||
						(this.zOffset<-TABLE_AREA_LENGTH/4&&this.zOffset>-BOTTOM_LENGTH/2+EDGE-BALL_R))
				{
					this.vz=-this.vz;
					flag=true;
					Log.d("GH Edge"+texId,"x="+this.xOffset+",z="+this.zOffset+", vx="+this.vx+",vz="+this.vz);
				}
				//ij�ߣ�������ij֮������һ���ߣ���ʵ������Ϊ���ⷢ������������Ϊ��Ϊ�ߵ���ײ��ͷ�����ײ���ഫ�ֹ��¼���
				if((this.zOffset>MIDDLE/2-BALL_R&&this.zOffset<TABLE_AREA_LENGTH/4)||
						(this.zOffset<BOTTOM_LENGTH/2-EDGE+BALL_R&&this.zOffset>TABLE_AREA_LENGTH/4))
				{
					this.vz=-this.vz;
					flag=true;
				}
				
			}
			//������EF����ײ���
			if(this.zOffset>-BOTTOM_LENGTH/2&&this.zOffset<-TABLE_AREA_LENGTH/2)
			{
				//��ʵ�������߲�Ӱ����ײ������ȷ�ԣ���Ϊ�򲻿��ܴ�����ײ�����ұ�Ե�����ߣ�����Ϊ�˱����鷳��������ϡ�
				//ef�ߣ�������ef֮������һ���ߣ���ʵ������Ϊ���ⷢ������������Ϊ��Ϊ�ߵ���ײ��ͷ�����ײ���ഫ�ֹ��¼���
				if((this.xOffset<0&&this.xOffset>-BOTTOM_WIDE/2+EDGE-BALL_R)||
						(this.xOffset>0&&this.xOffset<BOTTOM_WIDE/2-EDGE+BALL_R))
				{
					this.vx=-this.vx;
					flag=true;
				}
			}
			//������KL����ײ���
			if(this.zOffset>TABLE_AREA_LENGTH/2&&this.zOffset<BOTTOM_LENGTH/2)
			{
				//��ʵ�������߲�Ӱ����ײ������ȷ�ԣ���Ϊ�򲻿��ܴ�����ײ�����ұ�Ե�����ߣ�����Ϊ�˱����鷳��������ϡ�
				//ef�ߣ�������ef֮������һ���ߣ���ʵ������Ϊ���ⷢ������������Ϊ��Ϊ�ߵ���ײ��ͷ�����ײ���ഫ�ֹ��¼���
				if((this.xOffset>-BOTTOM_WIDE/2+EDGE-BALL_R&&this.xOffset<0)||
						this.xOffset>0&&this.xOffset<BOTTOM_WIDE/2-EDGE+BALL_R)
				{
					this.vx=-this.vx;
					flag=true;
				}
			}
		}
		if(flag==false)
		{//û����ײ
			//������˲��˶��ľ���
			distance=distance+(float)vTotal*TIME_SPAN;
			//�����˶��ľ�����������Ҫ�����ĽǶ�
			angleTemp=(float)Math.toDegrees(distance/(BALL_R));		
			//�������ʱ����ת���������
			axisX=vz;
			axisZ=-vx;
			//ÿ�ƶ�һ�����ٶ���Ҫ˥��
			vx=vx*V_TENUATION;
			vz=vz*V_TENUATION;
		}
		else
		{//��ײ��
			xOffset=tempX;
			zOffset=tempZ;
		}
		
		
		
	}
}

