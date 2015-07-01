package wyf.jsl.lb;

import static wyf.jsl.lb.Constant.*;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class SurfaceViewTag extends SurfaceView implements SurfaceHolder.Callback{

	Activity_GL_Demo activity;
	Paint paint;
	
	Bitmap[] logos=new Bitmap[2];
	Bitmap currentLogo;
	int currentX;
	int currentY;
	int currentAlpha;
	
	public SurfaceViewTag(Activity_GL_Demo activity) {
		super(activity);
		// TODO Auto-generated constructor stub
		this.activity=activity;
		this.getHolder().addCallback(this);//�����������ڻص��ӿڵ�ʵ����
		paint=new Paint();
		paint.setAntiAlias(true);
		
		initBitmap();
	}
	@Override
	public void onDraw(Canvas canvas)
	{
		super.onDraw(canvas);
		paint.setColor(Color.BLACK);
		paint.setAlpha(255);
		
		canvas.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,paint);
		
		//����
		if(currentLogo!=null)
		{
			paint.setAlpha(currentAlpha);
			canvas.drawBitmap(currentLogo, currentX, currentY, paint);
		}
	}
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		// TODO Auto-generated method stub
		
	}

	public void surfaceCreated(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		//SurfaceHolder myholder=holder;
		new Thread()
		{
			public void run()
			{
				for(Bitmap bm : logos)//��һ��ѭ������ͼƬ��ѭ��
				{
					currentLogo=bm;
					//���㵱ǰͼƬλ��
					currentX=SCREEN_WIDTH/2-currentLogo.getWidth()/2;
					currentY=SCREEN_HEIGHT/2-currentLogo.getHeight()/2;
					
					for(int i=255;i>0;i=i-10)//�ڶ���ѭ������ǰͼƬ�Ĳ�͸���ȵ�ѭ��
					{
						currentAlpha=i;
						if(currentAlpha<0)
						{
							currentAlpha=0;
						}
						SurfaceHolder myholder=SurfaceViewTag.this.getHolder();// �о�һ��
						Canvas canvas=myholder.lockCanvas();
						try
						{
							synchronized(myholder)
							{
								onDraw(canvas);//��ͼ
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
								myholder.unlockCanvasAndPost(canvas);
							}
						}
						try
						{
							if(currentAlpha==255)//������ͼƬ����Եȴ�һ�ᣬ������ͼƬ���л�ʱ���� 1 ��
							{
								Thread.sleep(1000);
							}
							Thread.sleep(50);//50�����һ�Σ���͸����
						}
						catch(Exception e)
						{
							e.printStackTrace();
						}
					}//��һ��for����
				}//�ڶ���for����
				activity.hd.sendEmptyMessage(GAME_SOUND);
			}
		}.start();
	}

	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		
	}

	public void initBitmap()
	{
		logos[0]=BitmapFactory.decodeResource(getResources(),R.drawable.bnkj);
		logos[1]=BitmapFactory.decodeResource(getResources(),R.drawable.huidu1);
		//logos[2]=BitmapFactory.decodeResource(getResources(),R.drawable.huidu2);
	}

}
