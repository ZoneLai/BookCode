package com.bn.carracer;

import static com.bn.carracer.Constant.*;

public class ThreadCamera extends Thread
{
	static boolean cameraFlag=true;
	
	static float camera_R=50f;//�����Ѳ��·��Բ�뾶
	static float angle=180;//�������ǰ�Ƕ�
	static float cx;//�������ǰλ��
	static float cary=2f;
	static float cy=15f;
	static float cz;  
	
	public void run()
	{ 
		while(cameraFlag)   
		{ 
			MyGLSurfaceView.carY=cary; 
			
			if(angle>540)//��Ѳ��һȦ��ֹͣѲ������Ѳ�������У�����Ϊ���ɿء�
			{				
				cameraFlag=false;//ֹͣѲ�� 
				MyGLSurfaceView.carLightAngle=135;//��ԭ�����ƹ�Ƕȡ� 
 
				DrawTrafficLights.lt.start();//������ͨ�Ʋ����߳�
//				if(Activity_GL_Racing.soundFlag==true)//���Ž�ͨ������
//				{					
//					MyGLSurfaceView.activity.playSound(1, 0);//��ͨ������
//				}
				DrawCountdown.go.start();//������ʻ����ʱ�߳�
				MyGLSurfaceView.daojishiFlag=true;//���Ƶ���ʱ
				
				DrawAirship.thread.flag=true;//������ͧ�˶��̱߳�־λ
				DrawAirship.thread.start();//������ͧ�˶��߳�
				
				DrawPool.waterFlag=true;//����ˮ�沨���̱߳�־λ
				DrawPool.waterThread.start();//��������ˮ�滻֡�߳� 
				
				Car.flag=true;//���������ͼ��������־�˶���־λ 
				Car.lt.start();//���������ͼ��������־�˶��߳�
				
				ThreadKey.flag=true;//�������̿����߳�
				MyGLSurfaceView.kt.start(); 
				
				ThreadColl.flag=true;//��������ײ������ײ����߳�
				MyGLSurfaceView.kc.start();
				
				ThreadSpeed.flag=true;//�����Ӽ��ٵ�����ײ����߳�
				MyGLSurfaceView.ts.start();
				
			}
			
			cx=(float) (CAR_X+camera_R*Math.cos(Math.toRadians(angle)));
			cz=(float) (CAR_Z+camera_R*Math.sin(Math.toRadians(angle)));
			
			angle=angle+9;
			MyGLSurfaceView.carLightAngle=MyGLSurfaceView.carLightAngle+9;
			
			try
			{
				Thread.sleep(100);
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
}