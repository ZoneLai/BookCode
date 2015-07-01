package wyf.jsl.lb;

import static wyf.jsl.lb.Constant.*;

public class ThreadMenu extends Thread {
	
	SurfaceViewMenu mv;
	int afterCurrentIndex;//�����������ĵ�ǰ�˵�ͼƬ��������
	
	public ThreadMenu(SurfaceViewMenu mv,int afterCurrentIndex)
	{
		this.mv=mv;
		this.afterCurrentIndex=afterCurrentIndex;
	}
	
	@Override
	public void run()
	{
		for(int i=0;i<=TOTAL_STEPS;i++)//ѭ��ָ���Ĳ�����ɶ���
		{
			mv.changePercent=PERCENT_STEP*i;//����˲���ռ�����İٷֱ�
			mv.initMenu();//��ʼ������λ�õ�ֵ
			
			if(mv.anmiState==1)//���״̬��1����������
			{
				//���ݵ�ǰ�ٷֱȼ��㵱ǰ�˵���λ�ã���С
				mv.currentSelectX=mv.currentSelectX+(BIGWIDTH+MENU_SPAN)*mv.changePercent;
				mv.currentSelectY=mv.currentSelectY+(BIGHEIGHT-SMALLHEIGHT)*mv.changePercent;
				mv.currentSelectWidth=BIGWIDTH-(BIGWIDTH-SMALLWIDTH)*mv.changePercent;
				mv.currentSelectHeight=BIGHEIGHT-(BIGHEIGHT-SMALLHEIGHT)*mv.changePercent;
				//������֮�󣬽��ڵ�ǰ�˵������˵���Ҫ�������Ҫ����
				mv.leftWidth=SMALLWIDTH+(BIGWIDTH-SMALLWIDTH)*mv.changePercent;
				mv.leftHeight=SMALLHEIGHT+(BIGHEIGHT-SMALLHEIGHT)*mv.changePercent;
				
				
			}
			else if(mv.anmiState==2)//���״̬��2����������
			{
				//���ݵ�ǰ�ٷֱȼ��㵱ǰ�˵���λ�ã���С
				mv.currentSelectX=mv.currentSelectX-(SMALLWIDTH+MENU_SPAN)*mv.changePercent;
				mv.currentSelectY=mv.currentSelectY+(BIGHEIGHT-SMALLHEIGHT)*mv.changePercent;
				mv.currentSelectWidth=BIGWIDTH-(BIGWIDTH-SMALLWIDTH)*mv.changePercent;
				mv.currentSelectHeight=BIGHEIGHT-(BIGHEIGHT-SMALLHEIGHT)*mv.changePercent;
				//������֮�󣬽��ڵ�ǰ�˵����Ҳ�˵���Ҫ�������Ҫ����
				mv.rightWidth=SMALLWIDTH+(BIGWIDTH-SMALLWIDTH)*mv.changePercent;
				mv.rightHeight=SMALLHEIGHT+(BIGHEIGHT-SMALLHEIGHT)*mv.changePercent;
			}
			//������������Ĳ˵���λ��
			mv.leftX=mv.currentSelectX-MENU_SPAN-mv.leftWidth;
			mv.leftY=mv.currentSelectY+(mv.currentSelectHeight-mv.leftHeight);//������
			//����������Ҳ�Ĳ˵���λ��
			mv.rightX=mv.currentSelectX+mv.currentSelectWidth+MENU_SPAN;
		    mv.rightY=mv.currentSelectY+(mv.currentSelectHeight-mv.rightHeight);//������
		    
		    mv.repaint();
		    try
		    {
		    	Thread.sleep(ANMI_TIMESPAN);
		    }
		    catch(Exception e)
		    {
		    	e.printStackTrace();
		    }
		}//for����
		mv.anmiState=0;
		mv.currentIndex=afterCurrentIndex;
		mv.initMenu();
		mv.repaint();
	}//run����
}
