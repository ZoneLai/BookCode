package wyf.sj;
import javax.microedition.khronos.opengles.GL10;
import static wyf.sj.Constant.*;

public class BallForControl {


	public static final float TIME_SPAN=0.05f;//��λʱ����
	public static final float G=0.8f;//�������ٶ�
	
	BallTextureByVertex btv;//���ڻ��Ƶ�����
	float high;//��ߵ�λ��
	float timeLive=0;//�����ڴ��ʱ��
	float currentY=0;//��ǰYλ��
	float vyMax=0;//����ٶ�
	float currentVy;//��ǰ�ٶ�	
	boolean isDown=true;//�Ƿ�Ϊ�½��׶� 
	
	public BallForControl(BallTextureByVertex btv,float highl)
	{
		this.btv=btv;
		this.high=highl;		
		currentY=highl;
		new Thread()
		{//����һ���߳��˶�����
			public void run()
			{
				while(true)
				{
					if(isDown)
					{//�½��׶�
						if(currentY>0)
						{//��û�е��ذ�������½�
							currentY=high-0.5f*G*timeLive*timeLive;
							timeLive+=TIME_SPAN;
						}
						else
						{//�����ذ��򷴵�
							vyMax=G*timeLive;//���㷴���ٶ�
							isDown=false;//�½���־λ�÷�
							timeLive=0;//�½�ʱ����0
							currentVy=vyMax;//��ǰ�ٶ�
							vyMax=vyMax*0.8f;//��ǰ����ٶ�
						}
					}
					else
					{//�����׶�
						if(vyMax<0.35f)
						{//���ٶ�С����ֵ��ֹͣ�˶�
							currentY=0;//��λ����0
							break;
						}
						
						if(currentVy>0)
						{//���ٶȴ��������������
							currentY=vyMax*timeLive-0.5f*G*timeLive*timeLive;//����λ��
							timeLive+=TIME_SPAN;//�˶�ʱ��
							currentVy=vyMax-G*timeLive;//��ǰ�ٶ�
						}
						else
						{//���ٶ�С�ڵ���0������½�����
							timeLive=0;//ʱ����0
							isDown=true;//�½���־λ��true
							high=currentY;//��ǰ��ߵ�
						}
					}
					
					try
					{
						Thread.sleep(20);
					}
					catch(Exception e)
					{
						e.printStackTrace();
					}
				}
			}
		}.start();
	}
	
	public void drawSelf(GL10 gl)
	{//���������Լ�		
		gl.glPushMatrix();
		gl.glTranslatef(0, UNIT_SIZE*BALL_SCALE+currentY, 0);
		btv.drawSelf(gl);		
		gl.glPopMatrix();
	}
	
	public void drawSelfMirror(GL10 gl)
	{//���� ������
		gl.glPushMatrix();
		gl.glTranslatef(0, -UNIT_SIZE*BALL_SCALE-currentY, 0);
		btv.drawSelf(gl);		
		gl.glPopMatrix();
	}
}
