package wyf.jc;

//��ʱ���������ƶ����߳�
public class BallGoThread extends Thread
{
	MyGameView mgv;
	boolean flag=true;
	
	public BallGoThread(MyGameView mgv)
	{
		this.mgv=mgv;
	}
	
	public void run()
	{
		while(flag)
		{
			//���������λ��
			int dx=mgv.dx;
			int dy=mgv.dy;			
			mgv.ballX=mgv.ballX+dx;
			mgv.ballY=mgv.ballY+dy;
			
			//�ж�X�����Ƿ����ڣ���������ָ�
			if(mgv.ballX<0||mgv.ballX>mgv.getWidth()-mgv.ballSize)
			{
				mgv.ballX=mgv.ballX-dx;
			}
			//�ж�Y�����Ƿ����ڣ���������ָ�
			if(mgv.ballY<0||mgv.ballY>mgv.getHeight()-mgv.ballSize)
			{
				mgv.ballY=mgv.ballY-dy;
			}
			
			try
			{
				Thread.sleep(100);
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
}
