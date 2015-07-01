package wyf.jsc.tdb;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class LoseView extends SurfaceView implements SurfaceHolder.Callback
{

	MyActivity activity;
	Bitmap lose;
	public LoseView(MyActivity activity) {
		super(activity);
		// TODO Auto-generated constructor stub
		getHolder().addCallback(this);
		this.activity=activity;
		lose=BitmapFactory.decodeResource(this.getResources(), R.drawable.win2);
	}
	
	//����ͼ��
	@Override
	public void onDraw(Canvas canvas)
	{
		canvas.drawBitmap(lose, 0, 0,null);	//loseͼƬ
	}
	
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		// TODO Auto-generated method stub
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

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		
	}

}
