package wyf.jsl.lb;

import static wyf.jsl.lb.Constant.*;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class SurfaceViewMenu extends SurfaceView implements SurfaceHolder.Callback {

	Activity_GL_Demo activity;
	Paint paint;//����
	Bitmap[] menu=new Bitmap[4];//�˵���ͼƬ����
	Bitmap menubg;//�˵�ҳ�汳��
	
	int currentIndex=1;//��ǰѡ�еĲ˵���������
	float changePercent=0;//�������еİٷֱ�
	int anmiState=0;//0:û�ж�����1�������ߣ�2��������
	//��ǰѡ�в˵��Ŀ��߼������Ͻ�����
	float currentSelectWidth;
	float currentSelectHeight;
	float currentSelectX;
	float currentSelectY;
	//���ڵ�ǰѡ�в˵����˵��Ŀ��߼������Ͻ�����
	float leftWidth;
	float leftHeight;
	float leftX;
	float leftY;
	//���ڵ�ǰѡ�в˵��Ҳ�˵��Ŀ��߼������Ͻ�����
	float rightWidth;
	float rightHeight;
	float rightX;
	float rightY;
	//�ϴδ��ص�X,Y����
	float previousX;
	float previousY;
	
	public SurfaceViewMenu(Activity_GL_Demo activity) {
		super(activity);
		// TODO Auto-generated constructor stub
		this.activity=activity;
		this.getHolder().addCallback(this);
		paint=new Paint();
		paint.setAntiAlias(true);
		
		initBitmap();
		initMenu();
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent e)
	{
		//�������������򴥿���Ч 
		if(anmiState!=0)
		{
			return true;
		}
		//��õ�ǰ���ص��X,Y����
		float x=e.getX();
		float y=e.getY();
		//���ݴ��صĲ�ͬ����ִ�в�ͬ��ҵ���߼�
		switch(e.getAction())
		{
			case MotionEvent.ACTION_DOWN://������Ϊ���´��ر����¼XY����
				previousX=x;
				previousY=y;
			break;
			case MotionEvent.ACTION_UP://������Ϊ̧�������Xλ�ƵĲ�ִͬ���󻬣��һ���ѡ�в˵����ҵ���߼�
				float dx=x-previousX;//����Xλ��
				if(dx<-MENU_SLIDESPAN)//��Xλ��С�ڸ���ֵ��������
				{
					if(currentIndex<menu.length-1)// ����ǰ�˵�������һ���˵���������
					{
						int afterCurrentIndex=currentIndex+1;//�µĵ�ǰ�˵�������
						anmiState=2;//����״̬��Ϊ2����������
						new ThreadMenu(this,afterCurrentIndex).start();
					}
				}
				else if(dx>MENU_SLIDESPAN)
				{
					if(currentIndex>0)// ����ǰ�˵���ǵ�һ���˵���������
					{
						int afterCurrentIndex=currentIndex-1;//�µĵ�ǰ�˵�������
						anmiState=1;//����״̬��Ϊ1����������
						new ThreadMenu(this,afterCurrentIndex).start();
					}
				}
				else
				{
					if
					(
							previousX>=SELECT_X&&previousX<=(SELECT_X+BIGWIDTH)&&
							previousY>=SELECT_Y&&previousY<=SELECT_Y+menu[currentIndex].getHeight()&&//
							x>=SELECT_X&&x<=SELECT_X+BIGWIDTH&&
							y>=SELECT_Y&&y<=SELECT_Y+menu[currentIndex].getHeight()	
					)
					{
						//���ݵ����ͼƬ��ͬ�����Ͳ�ͬ����Ϣ
						if(currentIndex==0)
						{
							activity.hd.sendEmptyMessage(GAME_LOAD);
							inGame=true;
						}
						else if(currentIndex==1)
						{
							activity.hd.sendEmptyMessage(GAME_HELP);
						}
						else if(currentIndex==2)
						{
							activity.hd.sendEmptyMessage(GAME_ABOUT);
						}
						else if(currentIndex==3)
						{
							//activity.hd.sendEmptyMessage(GAME_OVER);
							System.exit(0);
						}
						
					}
				}
				break;
		}
		return true;
	}
	
	
	@Override
	public void onDraw(Canvas canvas)
	{
		//super.onDraw(canvas);
		
		canvas.drawBitmap(menubg, 0, 0, paint);
		
		Bitmap selectbm=menu[currentIndex];
		selectbm=Bitmap.createScaledBitmap
		(
				selectbm,
				(int)currentSelectWidth,//����һ��Ҫ��int��
				(int)currentSelectHeight,
				false
		);
		canvas.drawBitmap(selectbm, currentSelectX, currentSelectY, paint);
		
		//����ǰ�˵���ǵ�һ�����ƽ��ڵ�ǰ�˵����Ĳ˵���
		if(currentIndex>0)
		{
			Bitmap leftbm=Bitmap.createScaledBitmap
			(
					menu[currentIndex-1],
					(int)leftWidth,
					(int)leftHeight,
					false
			);
			canvas.drawBitmap(leftbm, leftX, leftY, paint);
		}
		if(currentIndex<menu.length-1)
		{
			Bitmap rightbm=Bitmap.createScaledBitmap
			(
					menu[currentIndex+1],
					(int)rightWidth,
					(int)rightHeight,
					false
			);
			canvas.drawBitmap(rightbm, rightX, rightY, paint);
		}
		for(int i=currentIndex-2;i>=0;i--)
		{
			float tempx=leftX-(MENU_SPAN+SMALLWIDTH)*((currentIndex-1)-i);
			if(tempx<-SMALLWIDTH)
			{
				break;
			}
			float tempy=SELECT_Y+(BIGHEIGHT-SMALLHEIGHT);
			
			Bitmap tempbm=Bitmap.createScaledBitmap
			(
					menu[i],
					(int)SMALLWIDTH,
					(int)SMALLHEIGHT,
					false
			);
			canvas.drawBitmap(tempbm, tempx, tempy, paint);
		}
		for(int i=currentIndex+2;i<menu.length;i++)
		{
			float tempx=rightX+(SMALLWIDTH+MENU_SPAN)*(i-(currentIndex+1));
			if(tempx>SCREEN_WIDTH)
			{
				break;
			}
			float tempy=SELECT_Y+(BIGHEIGHT-SMALLHEIGHT);
			
			Bitmap tempbm=Bitmap.createScaledBitmap
			(
					menu[i],
					(int)SMALLWIDTH,
					(int)SMALLHEIGHT,
					false
			);
			canvas.drawBitmap(tempbm, tempx, tempy, paint);
		}
		
	}
	
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		// TODO Auto-generated method stub
		
	}

	public void surfaceCreated(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		repaint();
	}

	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		
	}
	//�ػ����ķ���
	public void repaint()
	{
		SurfaceHolder holder=this.getHolder();
		Canvas canvas=holder.lockCanvas();
		try
		{
			synchronized(holder)
			{
				onDraw(canvas);
			}
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			if(canvas!=null)
			{
				holder.unlockCanvasAndPost(canvas);
			}
		}
	}
	//��ʼ���˵�����������ʼ����ǰ���������ҵĲ˵����λ�ô�С����
	public void initMenu()
	{
		//��ʼ����ǰ�˵���Сλ��
		 currentSelectWidth=BIGWIDTH;
		 currentSelectHeight=BIGHEIGHT;
		 currentSelectX=SELECT_X;
		 currentSelectY=SELECT_Y;
		 //��ʼ�����ڵ�ǰ�˵����˵��Ĵ�Сλ��
		 leftWidth=SMALLWIDTH;
		 leftHeight=SMALLHEIGHT;
		 //leftX=SELECT_X-MENU_SPAN-SMALLWIDTH;
	     //leftY=SELECT_Y+BIGHEIGHT-SMALLHEIGHT;
		 leftX=currentSelectX-MENU_SPAN-leftWidth;
		 leftY=currentSelectY+currentSelectHeight-leftHeight;
		 //��ʼ�����ڵ�ǰ�˵��Ҳ�˵��Ĵ�Сλ��
		 rightWidth=SMALLWIDTH;
		 rightHeight=SMALLHEIGHT;
		 //rightX=SELECT_X+BIGWIDTH+MENU_SPAN;
		 //rightY=SELECT_Y+BIGHEIGHT-SMALLHEIGHT;
		 rightX=currentSelectX+currentSelectWidth+MENU_SPAN;
		 rightY=currentSelectY+currentSelectHeight-rightHeight;
	}
	//��ʼ��λͼ����
	public void initBitmap()
	{
		menubg=BitmapFactory.decodeResource(getResources(), R.drawable.face);
		menu[0]=BitmapFactory.decodeResource(getResources(), R.drawable.menu0);
		menu[1]=BitmapFactory.decodeResource(getResources(), R.drawable.menu3);
		menu[2]=BitmapFactory.decodeResource(getResources(), R.drawable.menu2);
		menu[3]=BitmapFactory.decodeResource(getResources(), R.drawable.menu1);
	}

}
