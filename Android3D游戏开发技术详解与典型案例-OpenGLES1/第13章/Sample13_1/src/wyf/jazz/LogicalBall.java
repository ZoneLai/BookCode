package wyf.jazz;

import static wyf.jazz.Constant.*;
import javax.microedition.khronos.opengles.GL10;

public class LogicalBall{
	float vx;//����X�᷽����ٶ�
	float vy;//����Y�᷽����ٶ�
	float vz;//����Y�᷽����ٶ�
	float vyMax=0;
	float currentVy;
	float timeDown=0;
	float timeLive=0;//����˶���ʱ��
	BallForDraw ball;	//��
	//�����ʼλ��
	float startX;
	float startY;
	float startZ;
	
	//��ǰλ��
	float currentX;
	float currentY;
	float currentZ;
	
	//��һʱ��λ��
	float previousX;
	float previousY;
	float previousZ;	
	
	float xAngle=0;
	float zAngle=0;
	
	int state=0;//������н׶�  0-�ڰ����˶�  1-�״�����  2-�������ط���
	
	Ball_Go_Thread bgt;
	public LogicalBall(BallForDraw ball,float startX,float startZ,float vx,float vz)
	{
		this.ball=ball;
		this.startX=startX;
		startY=2*STARTY+HEIGHT+2*SCALE;
		this.startZ=startZ;
		this.vx=vx;
		this.vz=vz;
		
		currentX=startX; 
		currentY=startY;
		currentZ=startZ;
	}
	
	public void drawSelf(GL10 gl)
	{
		gl.glEnable(GL10.GL_BLEND);//�������
		gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
		
		gl.glPushMatrix();
		gl.glTranslatef(0, 0, 0);//����׵�����ƽ̨��
		gl.glTranslatef(currentX, currentY, currentZ);
		gl.glRotatef(xAngle, 1, 0, 0);
		gl.glRotatef(zAngle, 0, 0, 1);
		ball.drawSelf(gl);		
		gl.glPopMatrix();		
	}
	
	public void move()
	{
		timeLive+=TIME_SPAN;
		currentX=startX+vx*timeLive;
		currentZ=startZ+vz*timeLive;
		xAngle=(float)Math.toDegrees(currentX/SCALE);
		zAngle=(float)Math.toDegrees(currentZ/SCALE);
		
		if(state==0)
		{//�ڰ���ƽ��
			if(currentX>LENGTH/2||currentZ>WIDTH/2)//���忪ʼ����
			{
				state=1;
				timeDown=0;
			}
		}
		else if(state==1)//�״�����
		{
			timeDown=timeDown+TIME_SPAN;
			float tempCurrentY=startY-0.5f*G*timeDown*timeDown;	
			if(tempCurrentY<=SCALE+HEIGHT)
			{//������ײ
				state=2;
				this.vy=G*timeDown*ANERGY_LOST;
				timeDown=0;
			}
			else
			{
				this.currentY=tempCurrentY;
			}
		}
		else if(state==2)
		{//���ط����׶�
			timeDown=timeDown+TIME_SPAN;
			float tempCurrentY=SCALE+HEIGHT+vy*timeDown-0.5f*G*timeDown*timeDown;	
			if(tempCurrentY<=SCALE+HEIGHT)
			{//������ײ
				this.vy=(G*timeDown-vy)*ANERGY_LOST;
				timeDown=0;
			}
			else
			{
				this.currentY=tempCurrentY;
			}
		}	
	}
}





