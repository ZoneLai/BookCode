package com.bn.carracer;

import static com.bn.carracer.MyGLSurfaceView.*;

//��ʱ������ײ�ɵĲ������罻ͨͲ�Ʋ������Ƿ���ײ���߳�
public class ThreadColl extends Thread
{
	MyGLSurfaceView surface;
	
	static boolean flag=true;
	
	public ThreadColl(MyGLSurfaceView surface)
	{ 
		this.surface=surface;
	}
	
	public void run()
	{
		while(flag) 
		{
			for(KZBJForControl kzbjfcTemp:MyGLSurfaceView.kzbjList)
			{
				if(!kzbjfcTemp.state)
				{
					kzbjfcTemp.checkColl(carX, carZ, carAlpha);
				}				
				kzbjfcTemp.go();
			}
			try
			{
				Thread.sleep(50);//50
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
}