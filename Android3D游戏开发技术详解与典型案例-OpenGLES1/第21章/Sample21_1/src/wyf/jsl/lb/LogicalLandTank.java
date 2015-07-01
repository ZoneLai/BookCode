package wyf.jsl.lb;

import static wyf.jsl.lb.Constant.*;
import javax.microedition.khronos.opengles.GL10;

import android.util.Log;

public class LogicalLandTank
{	
	GLGameView gl;
	PackageLandTank lt;//½��̹������	
	float startX;//��ʼλ��
	float startY;
	float startZ;	
	float vx;//�ٶ�
	float vy;
	float vz;
	float currentX;//��ǰλ��
	float currentY;
	float currentZ;	
	float nextX;//��һ��λ��
	float nextY;
	float nextZ;
	float timeLive=0;//����ʱ��
	float angle=0;//̹����ʼ����Ƕ�
	
	public LogicalLandTank(float startX,float startZ,float angle,PackageLandTank lt,GLGameView gl)
	{
		this.gl=gl;
		this.lt=lt;
		this.startX=startX;
		this.startZ=startZ;
		this.angle=angle;
		
		vx=(float) (L_V*Math.sin(Math.toRadians(angle+180)));
		vz=(float) (L_V*Math.cos(Math.toRadians(angle+180)));
		currentX=startX;//��ǰλ��
		currentY=L_START_Y;
		currentZ=startZ;
		nextX=currentX+vx;//��һ��λ��
		nextZ=currentZ+vz;
	}
	
	public void drawSelf(GL10 gl)
	{
		gl.glPushMatrix();
		gl.glTranslatef(currentX, currentY, currentZ);
		gl.glRotatef(-90, 0, 1, 0);
		gl.glRotatef(angle, 0, 1, 0);
		lt.drawSelf(gl);
		gl.glPopMatrix();
	}
	
	public void move()//½��̹���˶�����
	{
		//���ڹ�λ��������̹�˵���ײ���
		float GunCurrentX=(float) (currentX+lt.cylinderGunLength()*Math.sin(Math.toRadians(angle+180)));//�ڹܵ�ǰ����
		float GunCurrentZ=(float) (currentZ+lt.cylinderGunLength()*Math.cos(Math.toRadians(angle+180)));
		float GunNextX=(float) (nextX+lt.cylinderGunLength()*Math.sin(Math.toRadians(angle+180)));//��һ���ڹܵ�����
		float GunNextZ=(float) (nextZ+lt.cylinderGunLength()*Math.cos(Math.toRadians(angle+180)));
		
		//�ж���ɽ�ص���ײ���ڹܶ�Ӧ½�صĸ߶��Ƿ�����ڹܸ߶ȣ�̧��̹�ˡ�
		boolean b=CollectionUtil.isBulletCollectionsWithLand
					(
							GunCurrentX, 
							L_START_Y, 
							GunCurrentZ
					);
		
		//�ж���ˮ�����ײ���ڹܶ�Ӧ½�صĸ߶ȸ���ˮ��߶�ʱ��̹�˼����˶�������ˮ��߶�ʱ��̹����ʧ��
		boolean w=CollectionUtil.isBulletCollectionsWithLand
					(
							GunCurrentX, 
							WATER_HEIGHT, 
							GunCurrentZ
					);
		if(!b&&w)//��̹��û����ײɽ������̹�˻���½����ʱ��̹�˼����˶���
		{
			currentX=startX+vx*timeLive;//��ǰλ��
			currentZ=startZ+vz*timeLive;
		}
		else//����ײ
		{
	/*		
			if(b)//���̹����ײ��ɽ��ʱ��̹�����������������ֵ�Ƿ񳬹���ֵ����������ǰ�˶���
			{
				if(//��һλ�õ�½�ظ߶��뵱ǰλ��½�ظ߶ȵĲ���������ֵ����̹����ʧ��С����ֵ��̧��̹�ˡ�
						CollectionUtil.getLandHeight(GunNextX, GunNextZ)
					   -CollectionUtil.getLandHeight(GunCurrentX, GunCurrentZ)<WW
				   )
				{
					currentY=currentY+WW_SPAN;//̧��̹��
					currentX=startX+vx*timeLive;//������ǰ�˶�
					currentZ=startZ+vz*timeLive;
				}
				else
				{
					try{
						for(LogicalWaterTank lwt:gl.waterTankList)
						{
							if(
									(int)(lwt.currentX)==(int)(startX+40*Math.sin(Math.toRadians(lwt.angle)))
								  ||(int)(lwt.currentZ)==(int)(startZ+40*Math.cos(Math.toRadians(lwt.angle)))
							   )
							{
								try{						
									gl.waterTankList.remove(lwt);
									gl.landTankList.remove(this);
								}catch(Exception e){
									e.printStackTrace();
								}
							}
						}
					}catch(Exception e){
						e.printStackTrace();
					}
				}
			}
			else
			{
	*/			
				try{
					for(LogicalWaterTank lwt:gl.waterTankList)
					{
						if(
								(int)(lwt.currentX)==(int)(startX+40*Math.sin(Math.toRadians(lwt.angle)))
							  ||(int)(lwt.currentZ)==(int)(startZ+40*Math.cos(Math.toRadians(lwt.angle)))
						   )
						{
							try{						
								gl.waterTankList.remove(lwt);
								gl.landTankList.remove(this);
							}catch(Exception e){
								e.printStackTrace();
							}
						}
					}
				}catch(Exception e){
					e.printStackTrace();
				}
			//}	
		}
	}	
}