package wyf.jsl.lb;

import java.util.ArrayList;

public class ThreadWaterTank extends Thread
{
	//��Ա����
	ArrayList<LogicalWaterTank> list;//�߼�̹���б�
	boolean flag=true;
	
	public ThreadWaterTank(ArrayList<LogicalWaterTank> list)
	{
		this.list=list;
	}
	public void run()
	{	
		while(flag)
		{
			try{
				for(LogicalWaterTank lwt:list)
				{
					lwt.move();
					lwt.timeLive+=1;
				}
			}catch(Exception e){
				e.printStackTrace();
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