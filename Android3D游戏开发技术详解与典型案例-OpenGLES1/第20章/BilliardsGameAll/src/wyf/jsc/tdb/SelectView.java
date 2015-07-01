package wyf.jsc.tdb;

import static wyf.jsc.tdb.Constant.*;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class SelectView extends SurfaceView implements SurfaceHolder.Callback {
	
	MyActivity activity;
	Bitmap isSelect;  
	public boolean flag=true;
	public SelectView(MyActivity activity) {
		super(activity);
		// TODO Auto-generated constructor stub
		getHolder().addCallback(this);
		this.activity=activity;
		isSelect=BitmapFactory.decodeResource(this.getResources(), R.drawable.select);
	}
	@Override
	protected void onDraw(Canvas canvas)
	{
		super.onDraw(canvas);		
		canvas.drawBitmap(isSelect, 0,0, null);
	}
	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
		switch(event.getAction())
		{
			case MotionEvent.ACTION_DOWN:
				int x = (int) event.getX();
				int y = (int) event.getY();
				if(x>145&&x<340&&y>110&&y<145)
				{
					cueFlag=true;//�ػ���˵ı�־λ
					overFlag=false;//��������ı�־λ
					hitFlag=false;//�����Ƿ����
					hitSound=false;
					score=0;//��¼�÷�
					scoreOne=0;//first player score
					scoreTwo=0;//second player score
					scoreNODFlag=1;//�����жϸ���λ��ҽ���ӷ�  1  ��ʾ���1    2 ��ʾ���2
					scoreNOD=0;//������־������滹�ǵ�����     0  ��ʾ������   1 ��ʾ�����
					scoreTip=1;//������־��һ��˭�л���Ȩ
					sendFlag=false;//���ƿͻ��˷���һ����Ϣ��
					winLoseFlag=0;
					
					activity.toAnotherView(START_LOAD);
					hitFlag=true;//�򿪻�������					
					scoreNOD=0;//��������Ʊ�����
				}						
				else if(x>145&&x<340&&y>170&&y<210)
				{
					MySurfaceView.id=0;
					cueFlag=true;//�ػ���˵ı�־λ
					overFlag=false;//��������ı�־λ
					hitFlag=false;//�����Ƿ����
					hitSound=false;
					score=0;//��¼�÷�
					scoreOne=0;//first player score
					scoreTwo=0;//second player score
					scoreNODFlag=1;//�����жϸ���λ��ҽ���ӷ�  1  ��ʾ���1    2 ��ʾ���2
					scoreNOD=0;//������־������滹�ǵ�����     0  ��ʾ������   1 ��ʾ�����
					scoreTip=1;//������־��һ��˭�л���Ȩ
					sendFlag=false;//���ƿͻ��˷���һ����Ϣ��
					winLoseFlag=0;
					activity.toAnotherView(ENTER_NET);
					scoreNOD=1;//�������Ʊ�����
				break;
				}
			case MotionEvent.ACTION_UP:
				break;
		}
		
		return true;
	}
	
	@Override
	public boolean onKeyDown(int keyCode,KeyEvent e)    //�����¼�
	{
		Log.d("sadsad","onKeyUp"+keyCode);
		if(keyCode==4)
		{
			activity.toAnotherView(ENTER_MENU);			
			Log.d("onKeyUp 77","onKeyUp88");
			return true;
		}
		return true;
	}

	@Override
	public void surfaceChanged(SurfaceHolder arg0, int arg1, int arg2, int arg3) {
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
	public void surfaceDestroyed(SurfaceHolder arg0) {
		// TODO Auto-generated method stub
		
	}

}
