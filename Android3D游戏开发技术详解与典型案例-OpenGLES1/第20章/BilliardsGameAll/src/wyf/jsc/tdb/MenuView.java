package wyf.jsc.tdb;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import static wyf.jsc.tdb.Constant.*;

  

public class MenuView extends SurfaceView
implements SurfaceHolder.Callback
{
	MyActivity activity;   
	Paint paint;     				//����
	Bitmap[] menu=new Bitmap[5];   	//�˵�ͼƬ����
	Bitmap bj;     					//����ͼƬ
	Bitmap sound;
	
	int currentIndex=2;				//��ǰѡ�еĲ˵����	
	float mPreviousX;  				//��¼�ϴδ��ص�X����
	float mPreviousY;  				//��¼�ϴδ��ص�Y����
	float changePercent=0;   		//�����İٷְ�
	int anmiState=0;   				//0-û�ж���  1-������  2-������	
	
	int menuWidth;     				//��Ǯ�˵��Ŀ��
	int menuHeight;    		 		//��ǰ�˵��ĸ߶�
	float currentSelectX;    		//��ǰ�˵����X����λ��
	float currentSelectY;    		//��ǰ�˵����Y����λ��
	
	float leftWidth;    //����ٽ��˵��Ŀ��
	float leftHeight;	//�߶�
	float leftmenuX;	//X����
	float leftmenuY;	//Y����
	
	float rightWidth;	//�ұ��ٽ��˵��Ŀ��
	float rightHeight;  //�߶�
	float rightmenuX;   //X����
	float rightmenuY;   //Y����
	
	final int HELP_VIEW=0;			//����
	final int ABOUT_VIEW=1;			//����
	final int START_VIEW=2;			//��ʼ��Ϸ
	final int SETUP_VIEW=3;			//����
	final int EXIT_VIEW=4;			//�˳�
	

	public MenuView(MyActivity activity) {
		super(activity);  
		// TODO Auto-generated constructor stub
		this.activity=activity; 
		this.getHolder().addCallback(this);   	//�����������ڽӿ�
		paint=new Paint();						//��������
		paint.setAntiAlias(true);				//�򿪿����		

		
		//��ʼ��ͼƬ
		menu[0]=BitmapFactory.decodeResource(activity.getResources(), R.drawable.menu1);
		menu[1]=BitmapFactory.decodeResource(activity.getResources(), R.drawable.menu2);
		menu[2]=BitmapFactory.decodeResource(activity.getResources(), R.drawable.menu3);
		menu[3]=BitmapFactory.decodeResource(activity.getResources(), R.drawable.menu4);
		menu[4]=BitmapFactory.decodeResource(activity.getResources(), R.drawable.menu5);
		bj=BitmapFactory.decodeResource(activity.getResources(), R.drawable.bg);
		
		//��ʼ����ǰ�����������ҵĲ˵����λ�ô�С����
		init();
	}
	@Override
	public boolean onKeyDown(int keyCode,KeyEvent e)
	{
		if(keyCode==4)
		{
			System.exit(0);
			return true;
		}
		return true;	
	}
	//�����¼��ص�����   
	@Override
	public boolean onTouchEvent(MotionEvent e)
	{
		if(anmiState!=0)
		{    
			return true;
		}  
		//��ȡ��ǰ���ص��XY����
		float x=e.getX();
		float y=e.getY();  
		
		//���ݴ��صĲ�ͬ����ִ�в�ͬ��ҵ���߼�
		switch(e.getAction())
		{
			case MotionEvent.ACTION_DOWN:    //������Ϊ���´��ر����¼XYλ��
				mPreviousX=x;//��¼���ر�Xλ��
				mPreviousY=y;//��¼���ر�Yλ��
				break;
			case MotionEvent.ACTION_UP:     //������Ϊ̧�������Xλ�ƵĲ�ִͬ���󻬡��һ���ѡ�в˵����ҵ���߼�
				
				//����Xλ��
				float dx=x-mPreviousX;
				if(dx<-slideSpan)
				{//��Xλ��С����ֵ�����󻬶�
					if(currentIndex<menu.length-1)
					{//����ǰ�˵�������һ���˵������󻬶�
						//���㻬����ɺ�ĵ�ǰ�˵���ı��
						int afterCurrentIndex=currentIndex+1;
						//����״ֵ̬����Ϊ2 ������
						anmiState=2;
						//�����̲߳��Ŷ���������״ֵ̬
						new MenuAnmiThread(this,afterCurrentIndex).start();
						//(this,afterCurrentIndex)������2������������
					}					
				}
				else if(dx>slideSpan)
				{//��Xλ�ƴ��ڷ�ֵ�����һ���
					if(currentIndex>0)
					{//����ǰ�˵���ǵ�һ���˵��������󻬶�
	            		  //���㻬����ɺ�ĵ�ǰ�˵�����
						int afterCurrentIndex=currentIndex-1;
						//����״ֵ̬����Ϊ2-������
						anmiState=1;
						//�����̲߳��Ŷ���������״ֵ̬
						new MenuAnmiThread(this,afterCurrentIndex).start();
					}	            
				}
				else
				{//��Xλ������ֵ�����ж��з�ѡ��ĳ�˵���
					if
					(
						mPreviousX>selectX&&mPreviousX<selectX+bigWidth&&
		                mPreviousY>selectY&&mPreviousY<selectY+menu[currentIndex].getHeight()&&
		                x>selectX&&x<selectX+bigWidth&&
		                y>selectY&&y<selectY+menu[currentIndex].getHeight()	
					)
						 //��������̧��Ĵ��ص㶼�ڵ�ǰ�˵��ķ�Χ����ִ�а���ĳ�˵����ҵ���߼�
					{				
						
						switch(currentIndex)
						{
							case HELP_VIEW:
								activity.toAnotherView(ENTER_HELP);		//����
								break;
							case ABOUT_VIEW:
								activity.toAnotherView(ENTER_ABOUT);	//����
								break;
							case START_VIEW:
								activity.toAnotherView(START_ONE); 
								break;
							case SETUP_VIEW:
								activity.toAnotherView(ENTER_SETUP);	//����	
								break;
							case EXIT_VIEW:
								System.exit(0);			//�˳�����
								break;
						}
					}
				}
			 break;
		}	
		return true;	
	}
	
	public void onDraw(Canvas canvas)
	{
		
		//���Ʊ���		
		canvas.drawBitmap(bj, 0, 0, paint);
		//��ȡ��ǰ�˵���ͼƬ
		Bitmap selectBM=menu[currentIndex];

		//���ݲ�����������ڻ��Ƶ�ǰ�˵����ͼƬ
		selectBM=Bitmap.createScaledBitmap
		(
				selectBM, 
				menuWidth, 
				menuHeight, 
				false	
		);
		
		
			
		//���Ƶ�ǰ�Ĳ˵���
		canvas.drawBitmap(selectBM, currentSelectX, currentSelectY, paint);

		//����ǰ�˵���ǵ�һ������ƽ��ڵ�ǰ�˵������Ĳ˵���
		if(currentIndex>0)
		{	
			//���ų�������ͼƬ
			Bitmap left=Bitmap.createScaledBitmap
			(
					menu[currentIndex-1], 
					(int)leftWidth, 
					(int)leftHeight, 
					false
			);		
			//����ͼƬ
			canvas.drawBitmap(left, leftmenuX, leftmenuY, paint);
		}			
		
		//����ǰ�˵�������һ������ƽ��ڵ�ǰ�˵����Ҳ�Ĳ˵���
		if(currentIndex<menu.length-1)
		{
			//���ų�������ͼƬ
			Bitmap right=Bitmap.createScaledBitmap
			(
					menu[currentIndex+1], 
					(int)rightWidth, 
					(int)rightHeight, 
					false
			);	
			//����ͼƬ
			canvas.drawBitmap(right, rightmenuX, rightmenuY, paint);
		}
		
		//�����������δѡ�еĲ˵�
		for(int i=currentIndex-2;i>=0;i--)
		{	
			//����Xֵ
			float tempx=leftmenuX-(span+smallWidth)*(currentIndex-1-i);
			if(tempx<-smallWidth)
			{//�����Ƴ���������Ļ�����û�����
				break;
			}
			//����Yֵ
			int tempy=selectY+(bigHeight-smallHeight);	
			
			//���ų�������ͼƬ
			Bitmap tempbm=Bitmap.createScaledBitmap
			(
					menu[i], 
					smallWidth, 
					smallHeight, 
					false
			);
			//����ͼƬ
			canvas.drawBitmap(tempbm, tempx, tempy, paint);			
		}
		
		//���һ�������δѡ�еĲ˵�
		for(int i=currentIndex+2;i<menu.length;i++)
		{	
			//����Xֵ
            float tempx=rightmenuX+rightWidth+span+(span+smallWidth)*(i-(currentIndex+1)-1);			
			if(tempx>screenWidth)
			{//�����Ƴ���������Ļ�����û�����
				break;
			}			
			//����Yֵ
			int tempy=selectY+(bigHeight-smallHeight);					
			
			//���ų�������ͼƬ
			Bitmap tempbm=Bitmap.createScaledBitmap
			(
					menu[i], 
					smallWidth, 
					smallHeight, 
					false
			);	
			//����ͼƬ
			canvas.drawBitmap(tempbm, tempx, tempy, paint);		
		}
	}
	
	public void surfaceCreated(SurfaceHolder holder) {
		repaint();
	}
	
	//�ػ����ķ���
	public void repaint() {
		// TODO Auto-generated method stub
		SurfaceHolder holder=this.getHolder();
		Canvas canvas = holder.lockCanvas();//��ȡ����
		try{
			synchronized(holder){
				onDraw(canvas);//����
			}			
		}
		catch(Exception e){
			e.printStackTrace();
		}
		finally{
			if(canvas != null){
				holder.unlockCanvasAndPost(canvas);
			}
		}
	} 
		

	public void init() {
		// TODO Auto-generated method stub
		menuWidth=bigWidth;//��ǰѡ�в˵����		
		menuHeight=bigHeight;//��ǰѡ�в˵��߶�
		currentSelectX=selectX;//��ǰѡ�в˵�Xλ��
		currentSelectY=selectY;//��ǰѡ�в˵�Yλ��	
		rightWidth=smallWidth;//�����Ҳ�Ŀ��		
		leftWidth=smallWidth;//�������Ŀ��		
		leftHeight=smallHeight;//�������ĸ߶�	
		rightHeight=smallHeight;//�����Ҳ�ĸ߶�
		leftmenuX=currentSelectX-(span+leftWidth);//��������X
		leftmenuY=currentSelectY+(menuHeight-leftHeight);//��������Y����	
		rightmenuX=currentSelectX+(span+menuWidth);//�����Ҳ��X	
		rightmenuY=currentSelectY+(menuHeight-rightHeight);//�����Ҳ��Y����
	}

	@Override
	public void surfaceChanged(SurfaceHolder arg0, int arg1, int arg2, int arg3) {
		// TODO Auto-generated method stub
		
	}	

	@Override
	public void surfaceDestroyed(SurfaceHolder arg0) {
		// TODO Auto-generated method stub
		
	}
	
}
