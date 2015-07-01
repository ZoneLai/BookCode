package wyf.jsc.tdb;

import static wyf.jsc.tdb.Constant.*;


public class MenuAnmiThread extends Thread
{
	MenuView mv;
	int afterCurrentIndex;//�����궯����ĵ�ǰ�˵���
	
	public MenuAnmiThread(MenuView mv,int afterCurrentIndex)
	{
		this.mv=mv;
		this.afterCurrentIndex=afterCurrentIndex;
	}
	public void run()
	{
		//ѭ��ָ���Ĵ�����ɶ���
		for(int i=0;i<=totalSteps;i++)//�������ܲ���
		{
			//����˲��İٷֱȡ�
			mv.changePercent=percentStep*i;
			
			mv.init();
			
			//�����ܵ�˼����Ǹ��ݽ��Ȱٷֱȼ������ǰ�˵����λ�á���С			
			//�����ݵ�ǰ�˵����λ�ô�С����������Ҳ���ڲ˵����λ�á���С
			//�ǽ�����Ĵ�С�ǹ̶��ģ�ֻ��Ҫ����λ��
			if(mv.anmiState==1)   //anmiState=  0-û�ж���  1-������  2-������	
			{//���ҵĶ���
				//���ݰٷֱȼ��㵱ǰ�˵���λ�á���С
				mv.currentSelectX=mv.currentSelectX+(bigWidth+span)*mv.changePercent;              		//
				mv.currentSelectY=mv.currentSelectY+(bigHeight-smallHeight)*mv.changePercent;
				mv.menuWidth=(int)(smallWidth+(bigWidth-smallWidth)*(1-mv.changePercent));
				mv.menuHeight=(int)(smallHeight+(bigHeight-smallHeight)*(1-mv.changePercent));
				//���ڶ������ң����˵��������˼������˵����С
				mv.leftWidth=(int)(smallWidth+(bigWidth-smallWidth)*mv.changePercent);
				mv.leftHeight=(int)(smallHeight+(bigHeight-smallHeight)*mv.changePercent);						
			}
			else if(mv.anmiState==2)     //anmiState=  0-û�ж���  1-������  2-������	
			{//����Ķ���
				//���ݰٷֱȼ��㵱ǰ�˵���λ�á���С
				mv.currentSelectX=mv.currentSelectX-(smallWidth+span)*mv.changePercent;
				mv.currentSelectY=mv.currentSelectY+(bigHeight-smallHeight)*mv.changePercent;
				mv.menuWidth=(int)(smallWidth+(bigWidth-smallWidth)*(1-mv.changePercent));
				mv.menuHeight=(int)(smallHeight+(bigHeight-smallHeight)*(1-mv.changePercent));
				//���ڶ��������Ҳ�˵��������˼����Ҳ�˵����С
				mv.rightWidth=(int)(smallWidth+(bigWidth-smallWidth)*mv.changePercent);
				mv.rightHeight=(int)(smallHeight+(bigHeight-smallHeight)*mv.changePercent);					
			}
			//������������Ĳ˵���λ��
			mv.leftmenuX=mv.currentSelectX-(span+mv.leftWidth);			
			mv.leftmenuY=mv.currentSelectY+(mv.menuHeight-mv.leftHeight);	
			//����������Ҳ�Ĳ˵���λ��
			mv.rightmenuX=mv.currentSelectX+(span+mv.menuWidth);
			mv.rightmenuY=mv.currentSelectY+(mv.menuHeight-mv.rightHeight);
			
			//���»滭
			mv.repaint();
			try
			{
				Thread.sleep(timeSpan);
			}
			catch(Exception e)
			{
				e.printStackTrace();
			}		
		}
		//������ɺ����ö���״̬Ϊ0-�޶���
		mv.anmiState=0;
		//������ɺ���µ�ǰ�Ĳ˵�����
		mv.currentIndex=afterCurrentIndex;
		//��ʼ������λ��ֵ
		mv.init();		
		//�ػ滭��
		mv.repaint();
	}
}
















