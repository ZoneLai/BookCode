package wyf.jsl.lb;

import static wyf.jsl.lb.Constant.*;

import javax.microedition.khronos.opengles.GL10;

public class LogicalWaterTank
{	
	PackageWaterTank wt;//ˮ��̹������
	//��ʼλ��
	float startX;
	float startY;
	float startZ;
	//��ʼ�Ƕ�
	float angle;
	//�ٶ�
	float vx;
	float vy;
	float vz;
	//��ǰλ��
	float currentX;
	float currentY;
	float currentZ;
	//����ʱ��
	float timeLive=0;
	
	//½��̹�˴���
	GLGameView mySurface;//��������
	
	public LogicalWaterTank(float startX,float startZ,float angle,PackageWaterTank wt,GLGameView mySurface)
	{
		this.wt=wt;
		this.startX=startX;
		this.startZ=startZ;
		this.angle=angle;		
		this.mySurface=mySurface;

		vx=W_V;
		vz=W_V;
		currentX=startX;
		currentY=W_START_Y;
		currentZ=startZ;
	}
	
	public void drawSelf(GL10 gl)
	{
		gl.glPushMatrix();
		gl.glTranslatef(currentX, currentY, currentZ);
		gl.glRotatef(-90, 0, 1, 0);
		gl.glRotatef(angle, 0, 1, 0);//��ʼ��ת�Ƕ�
		wt.drawSelf(gl);
		gl.glPopMatrix();
	}
	
	public void move()//ˮ��̹���˶�����
	{
		float GunCurrentX=(float) (currentX-wt.WaterTankGunVertex()*Math.sin(Math.toRadians(angle)));//�ڹܵ�ǰ����
		float GunCurrentZ=(float) (currentZ-wt.WaterTankGunVertex()*Math.cos(Math.toRadians(angle)));

		boolean b=CollectionUtil.isBulletCollectionsWithLand//̹������½�أ�ֹͣ
					(
							GunCurrentX,		//�ڹܶ�Ӧλ�õ�½�ظ߶ȸ���ˮ��߶ȣ�̹��ֹͣ��
							WATER_HEIGHT-2.0f, 
							GunCurrentZ
					);
		if(!b)//������ֹͣ������̹�˼����˶���
		{
			currentX=(float) (startX+vx*Math.sin(Math.toRadians(angle))*timeLive);
			currentZ=(float) (startZ+vz*Math.cos(Math.toRadians(angle))*timeLive);
		}
		else{//����ֹͣ����
			for(LogicalLandTank llt:mySurface.landTankList)//�ж��Ƿ��ڸ�λ���Ѿ�������½��̹��
			{
				if(
						llt.startX==(float) (currentX-40*Math.sin(Math.toRadians(angle)))
					  ||llt.startZ==(float) (currentZ-40*Math.cos(Math.toRadians(angle)))
				  )
				{
					return;
				}
			}
			float randomAngle=(float) (Math.random()*60-30);
			//��ˮ��̹�˵�����������½��̹��
			mySurface.landTankList.add(new LogicalLandTank((float) (currentX-40*Math.sin(Math.toRadians(angle))),(float) (currentZ-40*Math.cos(Math.toRadians(angle))),angle+randomAngle,mySurface.mRenderer.lt,mySurface));
		}
	}
}