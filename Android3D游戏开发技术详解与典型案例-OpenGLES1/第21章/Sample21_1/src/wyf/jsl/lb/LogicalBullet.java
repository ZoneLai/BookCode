package wyf.jsl.lb;

import javax.microedition.khronos.opengles.GL10;
import static wyf.jsl.lb.Constant.*;

//�����ӵ�����
public class LogicalBullet 
{
	//���ڻ����ӵ����������
	DrawBall btbv;
	//�ӵ��ĳ���λ��
	float startX;
	float startY;
	float startZ;
	//�ӵ���ʵʱλ��
	float cuerrentX;
	float cuerrentY;	
	float cuerrentZ;
	//�ӵ��ĳ����ٶ�
	float vx;
	float vy;
	float vz;	
	//�ӵ��������ۼ�ʱ��
	float timeLive=0;
	//��ը�����Ƿ�ʼ��־
	boolean anmiStart=false;
	//��ը����֡����
	int anmiIndex=0;
	//��ը����������εı�־��Ƕ�
	float anmiYAngle;
	//MySurfaceView������
	GLGameView mv;
	//��ը�������־λ
	boolean flag=false;
	
	public LogicalBullet(DrawBall btbv,
			float startX,float startY,float startZ,float vx,float vy,float vz,
			GLGameView mv)
	{
		this.mv=mv;
		
		this.btbv=btbv;
		this.startX=startX;
		this.startY=startY;
		this.startZ=startZ;
		
		this.vx=vx;
		this.vy=vy;
		this.vz=vz;
		
		cuerrentX=startX;
		cuerrentY=startY;
		cuerrentZ=startZ;	
	}
	
	public void go()
	{		
	    if(!anmiStart)//����û�п�ʼʱ�����˶��߼�
	    {
	    	//�ڵ�����һ��λ��
			float tempTimeLive=timeLive+TIME_SPAN;//�ڵ�����ʱ��
			float tempCuerrentX=startX+vx*tempTimeLive;
			float tempCuerrentZ=startZ+vz*tempTimeLive;
			float tempCuerrentY=startY+vy*tempTimeLive-0.5f*G*tempTimeLive*tempTimeLive;
			
			//�ж��ڵ��з�ײɽ
			boolean shootLand=CollectionUtil.isBulletCollectionsWithLand(tempCuerrentX, tempCuerrentY, tempCuerrentZ);
			//�ж��ڵ��з�ײˮ
			boolean shootWater=ShootWater(tempCuerrentY);
			//�ж��ڵ��з����½��̹��
			boolean shootWaterTank=ShootWaterTank(tempCuerrentX, tempCuerrentY, tempCuerrentZ,mv);
			//�ж��ڵ��з����ˮ��̹��
			boolean shootLandTank=ShootTank(tempCuerrentX, tempCuerrentY, tempCuerrentZ,mv);
			
			//�ж��ڵ��з�ɳ�½�ط�Χ���ɳ���������ڵ�
			if(tempCuerrentX<-170||tempCuerrentX>170||tempCuerrentZ<-170||tempCuerrentZ>170)
			{
	    		try
	    		{
		    		mv.bulletList.remove(this);
	    		}catch(Exception e)
	    		{
	    			e.printStackTrace();
	    		}
			}
			else
			{
				if(!shootLand&&!shootLandTank&&!shootWater&&!shootWaterTank)//����ײ�����ڵ������˶�
				{
					timeLive=tempTimeLive;
					cuerrentX=tempCuerrentX;
					cuerrentY=tempCuerrentY;
					cuerrentZ=tempCuerrentZ;
				}
				else	
				{
					//��������ʼ���ű�ը����
					anmiYAngle=calculateBillboardDirection();//�����־��Ƕ�
					anmiStart=true;	//���ö�����ʼ��־Ϊtrue�����ٴε���go()ʱ�����Ʊ�ը������
					if(SOUND_FLAG)
					{
						mv.father.playSound(2, 0);//���ű�ը��Ч
					}
					if(shootLandTank||shootWaterTank)//����̹�ˣ�����̹��������1��
					{
						flag=true;//����̹�ˣ����������־λΪtrue�����Ż���̹�˵ı�ը����Ϊfalse���Ż���½�صı�ը����
						Count+=1;
					}
				}
			}			
	    } 
	    else
	    {//������ʼ��֡
	    	if(anmiIndex<mv.mRenderer.trExplo.length-1)
	    	{//����û�в����궯����֡
	    		anmiIndex=anmiIndex+1;
	    		//try{//��ը֡������
	    		//	Thread.sleep(1000);
	    		//}catch(Exception e)
	    		//{
	    		//	e.printStackTrace();
	    		//}
	    	}
	    	else
	    	{//���������꽫�ڵ����б���ɾ��
	    		try
	    		{
		    		mv.bulletList.remove(this);
	    		}catch(Exception e)
	    		{
	    			e.printStackTrace();
	    		}
	    	}
	    }
	}
	
	public void drawSelf(GL10 gl)
	{
		gl.glPushMatrix();//�����ֳ�
		gl.glTranslatef(cuerrentX, cuerrentY, cuerrentZ);//�ƶ���ָ��λ��
		if(!anmiStart)
		{//����ը����û�п�ʼ�����������ڵ�
			btbv.drawSelf(gl);
		}
		else
		{//����ը������ʼ�ˣ����Ʊ�ը����֡
			gl.glRotatef(anmiYAngle, 0, 1, 0);//��־����ת
			gl.glEnable(GL10.GL_BLEND);
			gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
			if(flag)//����̹�˻��ƻ���̹�˱�ըͼ
			{
				mv.mRenderer.shootExplo[anmiIndex].drawSelf(gl);
			}
			else{//û����̹�˻��ƻ���½�ر�ըͼ
				mv.mRenderer.trExplo[anmiIndex].drawSelf(gl);//���Ʊ�ը������ǰ֡
			}
			gl.glDisable(GL10.GL_BLEND);
		}
		gl.glPopMatrix();
	}
	
	//���������λ�ü��㱬ը�����泯��
	public float calculateBillboardDirection()
	{
		float yAngle=0;
		
		float xspan=cuerrentX-GLGameView.cx;
		float zspan=cuerrentZ-GLGameView.cz;
		
		if(zspan<=0)
		{
			yAngle=(float)Math.toDegrees(Math.atan(xspan/zspan));	
		}
		else
		{
			yAngle=180+(float)Math.toDegrees(Math.atan(xspan/zspan));
		}
		
		return yAngle;
	}
	
	//��ǰ�ڵ���½��̹�˵���ײ���
	public boolean ShootTank(float tempX,float tempY,float tempZ,GLGameView gl)
	{
		try
		{
			for(LogicalLandTank llt:gl.landTankList)
			{
				if(
						tempX>llt.currentX-T&&tempX<llt.currentX+T&&
						tempY>llt.currentY-T&&tempY<llt.currentY+T&&
						tempZ>llt.currentZ-T&&tempZ<llt.currentZ+T
				  )
				{
					try{//����½��̹������Ӧ��ˮ��̹�ˡ���½��̹����ʧʱ����ˮ��̹��Ҳ��ʧ��
						for(LogicalWaterTank lwt:gl.waterTankList)
						{
							if(
									(int)(lwt.currentX)==(int)(llt.startX+40*Math.sin(Math.toRadians(lwt.angle)))
								  ||(int)(lwt.currentZ)==(int)(llt.startZ+40*Math.cos(Math.toRadians(lwt.angle)))
							   )
							{
								try{						
									gl.waterTankList.remove(lwt);
									gl.landTankList.remove(llt);
								}catch(Exception e){
									e.printStackTrace();
								}
							}
							else{
								try{
									gl.landTankList.remove(llt);
								}catch(Exception e)
								{
									e.printStackTrace();
								}
							}
						}
					}catch(Exception e){
						e.printStackTrace();
					}
					return true;
				}
			}
		}catch(Exception e)
		{
			e.printStackTrace();
		}
		return false;
	}
	
	//��ǰ�ڵ���ˮ��̹�˵���ײ���
	public boolean ShootWaterTank(float tempX,float tempY,float tempZ,GLGameView gl)//��ײ����true������ײ����false��
	{
		try{
			for(LogicalWaterTank lwt:gl.waterTankList)
			{
				if(
						tempX>lwt.currentX-WT&&tempX<lwt.currentX+WT&&
						tempY>lwt.currentY-WT&&tempY<lwt.currentY+WT&&
						tempZ>lwt.currentZ-WT&&tempZ<lwt.currentZ+WT	
				  ){
					try{
						gl.waterTankList.remove(lwt);
					}catch(Exception e)
					{
						e.printStackTrace();
					}
					return true;
				}
			}
		}catch(Exception e)
		{
			e.printStackTrace();
		}
		return false;
	}
	
	//��ǰ�ڵ���ˮ�����ײ���
	public boolean ShootWater(float tempY)
	{
		if(tempY<=WATER_HEIGHT){//���ڵ��߶�С��ˮ��߶�ʱ��������ײ
			return true;
		}
		return false;
	}
}
