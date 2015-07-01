package wyf.jsc.tdb;



import static wyf.jsc.tdb.Constant.*;


//������ײ������������Ĺ�����
public class CollisionUtil
{
	MySurfaceView mv;
	public CollisionUtil(MySurfaceView mv)
	{
		this.mv=mv;
	}
	//�����������ĵ��
	public static float dotProduct(float[] vec1,float[] vec2)
	{
		return
			vec1[0]*vec2[0]+
			vec1[1]*vec2[1]+
			vec1[2]*vec2[2];
		
	}   
	
	//��������ģ
	public static float mould(float[] vec)
	{
		return (float)Math.sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
	}
	
	//�����������ļн�
	public static float angle(float[] vec1,float[] vec2)
	{
		//������
		float dp=dotProduct(vec1,vec2);
		//��������������ģ
		float m1=mould(vec1);
		float m2=mould(vec2);
		
		float acos=dp/(m1*m2);
		
		//Ϊ�˱������������������
		if(acos>1)
		{
			acos=1;
		}
		else if(acos<-1)
		{
			acos=-1;
		}
			
		return (float)Math.acos(acos);
	}
	
	//�����������ײ�������ķ���
	public  boolean collision(BallForControl balla,BallForControl ballb)
	{
		
		//����ײֱ������B->A ��Ҳ��������������ײ�������������ߵ�������
		float BAx=balla.xOffset-ballb.xOffset;
		float BAz=balla.zOffset-ballb.zOffset;		
		
		//������������ģ
		float mvBA=mould(new float[]{BAx,0,BAz});	
		
		//��������������뾶��������û����ײ
		if(mvBA>BALL_R*2)
		{
			hitSound=false;
			return false;
		}		
		hitSound=true;
		if(hitSound)
		{
			mv.activity.playSound(2, 0);
			hitSound=false;
		}
		/*
		 * ���������ײ���㷨Ϊ��
		 * 1�����������������ߵ�����
		 * 2����ÿ������ٶȷֽ�Ϊƽ���봹ֱ��������������
		 * 3��������ȫ������ײ��֪ʶ����ײ��ƽ�����������ٶ����򽻻�����ֱ���������ٶȲ���
		 * 4��������װ��������ٶȼ���
		 * vax=vax��ֱ+vbxƽ��    vaz=vaz��ֱ+vbzƽ��    
		 * vbx=vbx��ֱ+vaxƽ��    vbz=vbz��ֱ+vazƽ��    
		 */
		
	    //�ֽ�B���ٶ�========================================begin=============	
		
		//��b����ٶȴ�С
		float vB=(float)Math.sqrt(ballb.vx*ballb.vx+ballb.vz*ballb.vz);
		//ƽ�з����XZ���ٶ�
		float vbCollx=0;
		float vbCollz=0;
		//��ֱ�����XZ���ٶ�
		float vbVerticalX=0;
		float vbVerticalZ=0;
		
		//�����ٶ�С����ֵ����Ϊ�ٶ�Ϊ�㣬���ý��зֽ������
		if(V_THRESHOLD<vB)
		{
			//��B����ٶȷ�����������ײֱ������B->A�ļн�(����)
			float bAngle=angle
			(
				new float[]{ballb.vx,0,ballb.vz},
			    new float[]{BAx,0,BAz}
			);
			
			//��B������ײ������ٶȴ�С
			float vbColl=vB*(float)Math.cos(bAngle);
			
			//��B������ײ������ٶ�����
			vbCollx=(vbColl/mvBA)*BAx;
			vbCollz=(vbColl/mvBA)*BAz;
			
			//��B������ײ��ֱ������ٶ�����
			vbVerticalX=ballb.vx-vbCollx;
			vbVerticalZ=ballb.vz-vbCollz;
		}
		//�ֽ�B���ٶ�========================================end===============
		
		//�ֽ�A���ٶ�========================================begin=============	
		
		//��a����ٶȴ�С
		float vA=(float)Math.sqrt(balla.vx*balla.vx+balla.vz*balla.vz);
		//ƽ�з����XZ���ٶ�
		float vaCollx=0;
		float vaCollz=0;
		//��ֱ�����XZ���ٶ�
		float vaVerticalX=0;
		float vaVerticalZ=0;
		
		//�����ٶ�С����ֵ����Ϊ�ٶ�Ϊ�㣬���ý��зֽ������
		if(V_THRESHOLD<vA)
		{
			//��A����ٶȷ�����������ײֱ������B->A�ļн�(����)
			float aAngle=angle
			(
				new float[]{balla.vx,0,balla.vz},
			    new float[]{BAx,0,BAz}
			);			
			
			//��A������ײ������ٶȴ�С
			float vaColl=vA*(float)Math.cos(aAngle);
			
			//��A������ײ������ٶ�����
			vaCollx=(vaColl/mvBA)*BAx;
			vaCollz=(vaColl/mvBA)*BAz;
			
			//��A������ײ��ֱ������ٶ�����
			vaVerticalX=balla.vx-vaCollx;
			vaVerticalZ=balla.vz-vaCollz;
		}		
		//�ֽ�A���ٶ�========================================end===============
		
		//����ײ��AB����ٶ�
		//����˼��Ϊ��ֱ�����ٶȲ��䣬��ײ���������ٶȽ�������ֱ�����ٶȲ���
		balla.vx=vaVerticalX+vbCollx;
		balla.vz=vaVerticalZ+vbCollz;
		
		ballb.vx=vbVerticalX+vaCollx;
		ballb.vz=vbVerticalZ+vaCollz;		
		
		
		//��������������ײ������˶���������ת�ǶȲ���
		balla.distance=0;
		balla.angleTemp=0;		
		ballb.distance=0;
		ballb.angleTemp=0;
		
		
		//========================================
		//�˴����ò���������ײ�����Ĵ���
		//�˴����ò���������ײ�����Ĵ���
		//�˴����ò���������ײ�����Ĵ���
		//========================================
		
		return true;
	}
}
   
