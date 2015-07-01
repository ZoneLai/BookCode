package wyf.jc;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class MyGameView extends SurfaceView 
implements SurfaceHolder.Callback  //ʵ���������ڻص��ӿ�
{
	SensorBallActivity activity;
	BallGoThread bgt;
	GameViewDrawThread gvdt;
	Paint paint;//����
	Bitmap tableBM;
	Bitmap ballBM;
	
	int ballSize=64;//��ĳߴ�
	int dLength=5;//��׼����
	int ballX=100;
	int ballY=80;
	int dx=2;
	int dy=2;
	
	public MyGameView(SensorBallActivity activity) {
		super(activity);
		this.activity = activity;
		this.getHolder().addCallback(this);//�����������ڻص��ӿڵ�ʵ����
		
		//����ͼƬ
		tableBM=BitmapFactory.decodeResource(activity.getResources(), R.drawable.table);
		ballBM=BitmapFactory.decodeResource(activity.getResources(), R.drawable.ball);
		
		paint = new Paint();//��������
		paint.setAntiAlias(true);//�򿪿����
		
		bgt=new BallGoThread(this);
		gvdt=new GameViewDrawThread(this);
	}

	public void onDraw(Canvas canvas){					
		//������
		canvas.drawBitmap(tableBM, 0, 0, paint);		
		//����
		canvas.drawBitmap(ballBM, ballX, ballY, paint);
	}

	public void surfaceChanged(SurfaceHolder arg0, int arg1, int arg2, int arg3) {
		
	}

	public void surfaceCreated(SurfaceHolder holder) {//����ʱ������
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
		//������ʱ���������ƶ����߳�
		bgt.start();
		//������ʱ���»��ƻ�����߳�
		gvdt.start();
	}

	public void surfaceDestroyed(SurfaceHolder arg0) {//����ʱ������
         
	}
}