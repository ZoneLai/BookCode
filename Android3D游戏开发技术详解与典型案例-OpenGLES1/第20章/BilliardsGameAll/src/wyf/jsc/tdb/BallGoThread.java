package wyf.jsc.tdb;
 
import java.io.IOException;
import java.util.ArrayList;

import static wyf.jsc.tdb.Constant.*;
//�����˶����߳�
public class BallGoThread extends Thread 
{
	//����������б�
	ArrayList<BallForControl> ballAl;
	//�߳��Ƿ���������ı�־λ
	MySurfaceView mv;
	boolean flag=true;
	CollisionUtil cu;
	float tempZL;
	float tempZR;
	float tempXU;
	float tempXD;
	float temp=0.2f;//ƫ����
	public BallGoThread(ArrayList<BallForControl> ballAl,MySurfaceView mv)
	{
		this.ballAl=ballAl;
		this.mv=mv;
		cu=new CollisionUtil(mv);
	}
	public void run()
	{
		while(flag)
		{
			//��ȡ��ĸ���
			int size=ballAl.size();
	
			//�ж�ÿ�����Ƿ��н���
			try
			{
				for(int i=0;i<size;i++)
				{
					BallForControl bfc=ballAl.get(i);
					tempZL=BOTTOM_LENGTH/2-bfc.zOffset;//���ĵ��󵲰�ľ���
					tempZR=bfc.zOffset+BOTTOM_LENGTH/2;//���ĵ��ҵ���ľ���
					tempXU=bfc.xOffset+BOTTOM_WIDE/2;//���ĵ��ϵ���ľ���
					tempXD=BOTTOM_WIDE/2-bfc.xOffset;//���ĵ��µ���ľ���					
					
					if(//�������Ƿ����
							tempZL<GOT_SCORE_DISTANCE||tempZR<GOT_SCORE_DISTANCE||
							tempXU<GOT_SCORE_DISTANCE||tempXD<GOT_SCORE_DISTANCE
					)
					{
						if(bfc==ballAl.get(0))
						{//ĸ�����
							bfc.vx=0;
							bfc.vz=0;
							bfc.yOffset=100f;
							if(cueFlag)
							{
								ballAl.get(0).xOffset=0;ballAl.get(0).zOffset=9;ballAl.get(0).yOffset=1;Cue.angleZ=0;//�ػ�ĸ��
							}							
						}
						else
						{//��ͨ�����
							bfc.vx=0;
							bfc.vz=0;
							bfc.yOffset=10f;
							mv.activity.playSound(3, 0);//�����������
							try
							{
								ballAl.remove(i);//�Ƴ���������
								if(mv.activity.netFlag)
								{
									mv.activity.ct.dout.writeUTF("<#BALL_IN_HOLE#>"+ballAl.size());	//���ͽ�����Ϣ								
								}else
								{
									score++;//�÷��Լ�
								}
								
								if(ballAl.size()==1&&!mv.activity.netFlag)
								{
									overFlag=true;//��Ϸ������־λ��Ϊtrue
								}
								
							}catch(Exception ea)
							{
								ea.printStackTrace();
							}
						}
					}					
				}
			}catch(Exception e)
			{
				e.printStackTrace();
			}
			
			//�����������Ƿ�ֹͣ�ı�־λ���ٶ�������ֹͣ
			boolean allStop=true;
			//��ײ�����Ϻ�ÿ���������һ��
			for(int i=0;i<ballAl.size();i++)
			{
				BallForControl bfc=ballAl.get(i);
				bfc.go(ballAl,cu);
				//�������ٶȲ�Ϊ0�����������Ƿ�ֹͣ�ı�־λ��false
				if(bfc.vx!=0||bfc.vz!=0)
				{
					allStop=false;
					
				}				
			}
			
			if(allStop)
			{
				//�˴������л���������״̬�Ĵ��룬�û��������״̬�л�Ϊ��������򲻻����������
				//��ʽ
				MySurfaceView.turnFlag=true;
				if(mv.activity.netFlag)
				{
					if(sendFlag)
					{

						try {
							mv.activity.ct.dout.writeUTF("<#BALL_GO_OVER#>");//˳���ж��Ƿ����ֹͣ
							mv.activity.ct.dout.flush();
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						sendFlag=false;//���Ʒ�����ͣ��Ϣ��־λ
					}
				}
				else
				{
					cueFlag=true;//������˱�־λ
				}
			}
			
			//�߳�����һ����ʱ��
			try {
				Thread.sleep(Constant.THREAD_SLEEP);
			} catch (InterruptedException e) 
			{
				e.printStackTrace();
			}
		}
	}
	
}