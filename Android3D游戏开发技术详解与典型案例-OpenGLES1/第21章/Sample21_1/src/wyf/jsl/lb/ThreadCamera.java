package wyf.jsl.lb;

import static wyf.jsl.lb.Constant.*;
import android.util.Log;

public class ThreadCamera extends Thread 
{
	Activity_GL_Demo activity;
	GLGameView gl;
	boolean flag=true;
	static float rSpan=20;//�뾶�仯���������������תԲ�İ뾶
	static float angleSpan=CAMERA_START_ANGLE;//��ǰ��ת�ĽǶ�
	
	public ThreadCamera(GLGameView gl,Activity_GL_Demo activity)
	{
		this.gl=gl;
		this.activity=activity;
	}
	
	@SuppressWarnings("static-access")
	public void run()
	{
		while(flag) 
		{
			if(angleSpan<=CAMERA_START_ANGLE+360)
			{
		        gl.cx=FORT_X+CARERA_R*rSpan*(float)(Math.cos(Math.toRadians(angleSpan)));//�����x����
		        gl.cy=FORT_Y+20f;//�����y����
		        gl.cz=FORT_Z+CARERA_R*rSpan*(float)(Math.sin(Math.toRadians(angleSpan)));//�����z����
		        
		        //rSpan+=0.5f; 
		        angleSpan+=5;
			}
			else
			{
				flag=false;//����ѭ��
				gl.flagFinish=true;//��Ϸ���������������תʱ�����̲��ɿأ���ת������ʹ���ָ̻��ɿ��ơ�
				angleSpan=CAMERA_START_ANGLE;//Ϊ��һ��ѭ�����̵�
				
				//�̶���̨λ��
//	        	gl.cx=FORT_X;
//	        	gl.cy=FORT_Y+DISTANCE/2;
//	        	gl.cz=FORT_Z+DISTANCE;	        	
		        gl.cx=FORT_X+CARERA_R*rSpan*(float)(Math.cos(Math.toRadians(CAMERA_START_ANGLE+360)));//�����x����
		        gl.cy=FORT_Y+20f;//�����y����
		        gl.cz=FORT_Z+CARERA_R*rSpan*(float)(Math.sin(Math.toRadians(CAMERA_START_ANGLE+360)));//�����z����
  	
	        	//����̹�ˡ��ڵ��˶��߳�
	        	gl.bgt.start();
	        	gl.gtlt.start();
	        	gl.gtwt.start();   
	        	gl.tl.start();//������Դ��ת�߳�
	        	gl.xk.start();//�����ǿ���ת�߳�
	        	gl.tm.start();//��������ת�߳�
	        	if(BACK_SOUND_FLAG)
	        	{Log.d("BACK_SOUND_FLAG",BACK_SOUND_FLAG+"");
	        		activity.mpBack.start(); 
	        	}
			}
	        try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		
		
	}
}

