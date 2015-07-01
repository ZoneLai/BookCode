package wyf.jsl.lb;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import static wyf.jsl.lb.Constant.*;

public class SurfaceViewOver extends SurfaceView implements SurfaceHolder.Callback{
	
	Activity_GL_Demo activity;
	GLGameView game;
	
	private Bitmap over;
	private Bitmap retry;
	private Bitmap exit;
	
	Paint paint;
	
	public SurfaceViewOver(Activity_GL_Demo activity,GLGameView game) {
		super(activity);
		// TODO Auto-generated constructor stub
		this.activity=activity;
		this.game=game;
		
		this.getHolder().addCallback(this);
		
		paint=new Paint();
		paint.setAntiAlias(true);
		
		initBitmap();
	}
	
	
	@Override
	public void onDraw(Canvas canvas)
	{
		super.onDraw(canvas);
		canvas.drawBitmap(over, 0, 0, paint);
		canvas.drawBitmap(retry, 10, 280, paint);
		canvas.drawBitmap(exit, 330, 150, paint);
	}

	@Override
	public boolean onTouchEvent(MotionEvent e)
	{
		float x=e.getX();
		float y=e.getY();
		
		switch(e.getAction())
		{
		case MotionEvent.ACTION_UP:
			if(x>=10&&x<=110&&y>=280&&y<=320)
			{
				game.bgt.flag=false;//�ر��ܵ��߳�
				game.gtlt.flag=false;//�ر�½��̹���߳�
				game.gtwt.flag=false;//�ر�ˮ��̹���߳�
				game.tl.flag=false;//�رչ�Դ��ת�߳�
				game.xk.flag=false;//�ر��ǿ���ת�߳�
				game.tm.flag=false;//�ر�����ת�߳�
				//SOUND_FLAG=false;//�ر�����
				inGame=true;
				activity.mpBack.pause();//ֹͣ������
				Count=0;//��ջ���̹����
				
				activity.hd.sendEmptyMessage(GAME_LOAD);
			}
			if(x>=330&&x<=480&&y>=150&&y<=320)
			{
				System.exit(0);
			}
			break;
		}
		return true;
	}
	 
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		// TODO Auto-generated method stub
		
	}

	public void surfaceCreated(SurfaceHolder holder) {
		// TODO Auto-generated method stub
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

	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		
	}

	public void initBitmap()
	{
		over=BitmapFactory.decodeResource(getResources(), R.drawable.over);
		retry=BitmapFactory.decodeResource(getResources(), R.drawable.retry);
		exit=BitmapFactory.decodeResource(getResources(), R.drawable.exit);
	}
}
