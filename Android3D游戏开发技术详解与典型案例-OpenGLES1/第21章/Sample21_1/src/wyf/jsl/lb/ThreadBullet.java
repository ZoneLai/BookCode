package wyf.jsl.lb;

import java.util.ArrayList;
//��ʱ�ƶ��ӵ����߳�
public class ThreadBullet extends Thread
{
	ArrayList<LogicalBullet> bulletAl;//�ӵ��б�
	boolean flag=true;//ѭ����־λ
	
	public ThreadBullet(ArrayList<LogicalBullet> bulletAl)
	{
		this.bulletAl=bulletAl;
	}
	
	public void run()
	{
		while(flag)
		{//ѭ����ʱ�ƶ��ڵ�
			try
			{
				for(LogicalBullet b:bulletAl)
				{
					b.go();
				}
			}
			catch(Exception e)
			{
				e.printStackTrace();
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
