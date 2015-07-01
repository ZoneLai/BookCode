package wyf.jazz;

import static wyf.jazz.Constant.*;
import java.util.ArrayList;
import javax.microedition.khronos.opengles.GL10;

public class LogicalBall
{
	float vx;//����X�᷽����ٶ�
	float mass;//�������
	float timeLive=0;//����˶���ʱ��
	BallForDraw ball;	//��
	
	//�����ʼλ��
	float startX;
	float startY=0;
	float startZ=0;
	
	//��ǰλ��
	float currentX;
	float currentY;
	float currentZ;
	
	float xAngle=0;//��ת���Ƕ�
	
	Ball_Go_Thread bgt;
	public LogicalBall(BallForDraw ball,float startX,float vx,float mass)
	{
		this.ball=ball;
		this.mass=mass;
		this.startX=startX;
		this.vx=vx;
		
		currentX=startX; 
		currentY=startY+SCALE;
		currentZ=startZ;
	}
	
	public void drawSelf(GL10 gl)
	{
		gl.glEnable(GL10.GL_BLEND);//�������
		gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
		
		gl.glPushMatrix();
		gl.glTranslatef(currentX, currentY, currentZ);
		gl.glRotatef(xAngle, 0, 0, 1);
		ball.drawSelf(gl);		
		gl.glPopMatrix();		
	}
	
	public void move(ArrayList<LogicalBall> ballAl)
	{
		timeLive=timeLive+TIME_SPAN;
		currentX=startX+vx*timeLive;
		
		//�����Ƿ���ײ
		for(int i=0;i<ballAl.size();i++)
		{
			LogicalBall bfcL=ballAl.get(i);
			if(bfcL!=this)
			{
				float distance=Math.abs(this.currentX-bfcL.currentX);//��ȡ�������ĵľ���
				this.xAngle=(float) -Math.toDegrees(currentX/SCALE);
				bfcL.xAngle=(float) Math.toDegrees(currentX/SCALE);
				float vPreviousA=this.vx;
				float vPreviousB=bfcL.vx;
				if(distance<2*SCALE)//�ж����ľ��Ƿ�С������뾶�ͣ���С��������ײ
				{
					this.vx=vPreviousA-2*bfcL.mass*(vPreviousA-vPreviousB)/(this.mass+bfcL.mass);
					bfcL.vx=vPreviousB-2*this.mass*(vPreviousB-vPreviousA)/(this.mass+bfcL.mass);
					this.startX=this.currentX;
					bfcL.startX=bfcL.currentX;
					this.timeLive=0;
					bfcL.timeLive=0;
				}
			}
		}
	}
}