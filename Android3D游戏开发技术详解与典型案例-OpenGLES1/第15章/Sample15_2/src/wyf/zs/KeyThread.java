package wyf.zs;
import static wyf.zs.Constant.*;
public class KeyThread extends Thread {
	
	MySurfaceView mv; 	
	public KeyThread(MySurfaceView mv)
	{
		this.mv=mv;
	}
	public void run() 
	{
		while(true)
		{
			if((mv.keyState&0x1)!=0) 
			{//��UP������
				float xOffset=0;//���ƶ����λ��
				float zOffset=0;
				
				xOffset=(float)Math.sin(direction)*MOVE_SPAN;
				zOffset=(float)-Math.cos(direction)*MOVE_SPAN;
  			    
  			  //�����˶���Ĵ���XZֵ
  			    float tempbx=mv.ballx+xOffset;
  			    float tempbz=mv.ballz+zOffset;
				
				mv.ballz=tempbz;
				mv.ballx=tempbx;				
			}
			else if((mv.keyState&0x2)!=0)
			{//��down������
				float xOffset=0;//���ƶ����λ��
	    		float zOffset=0;	    		
	    		xOffset=(float)Math.sin(direction)*MOVE_SPAN;
  			    zOffset=(float)Math.cos(direction)*MOVE_SPAN;
  			    
  			    float tempbx=mv.ballx+xOffset;
  			    float tempbz=mv.ballz+zOffset;
  			    
  			    mv.ballz=tempbz;
				mv.ballx=tempbx;
			}
			
			if((mv.keyState&0x4)!=0)
			{//��left������
				direction=direction-DEGREE_SPAN;	
			}
			else if((mv.keyState&0x8)!=0)
			{//��right������
				direction=direction+DEGREE_SPAN; 
			}				
			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
}
