package wyf.jsc.tdb;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import static wyf.jsc.tdb.Constant.*;

public class HelpView extends SurfaceView implements SurfaceHolder.Callback {
 
	MyActivity activity;
	Bitmap ishelp;
	

	float mPreviousX;  				//��¼�ϴδ��ص�X����
	float mPreviousY;  				//��¼�ϴδ��ص�Y����
	
	public HelpView(MyActivity activity) {
		super(activity);
		// TODO Auto-generated constructor stub
		getHolder().addCallback(this);
		this.activity=activity;
		ishelp=BitmapFactory.decodeResource(this.getResources(), R.drawable.help);
	}
	@Override
	protected void onDraw(Canvas canvas)
	{
		super.onDraw(canvas);		
		canvas.drawBitmap(ishelp, 0,0, null);
	}
	
	
	@Override
	public boolean onTouchEvent(MotionEvent e)
	{		
		//��ȡ��ǰ���ص��XY����
        float x = e.getX();
        float y = e.getY();
        //���ݴ��صĶ���ִ��ҵ���߼�
		switch(e.getAction())
		{
			case MotionEvent.ACTION_DOWN:    //������Ϊ���´��ر����¼XYλ��
				mPreviousX=x;				//��¼���ر�Xλ��
				mPreviousY=y;				//��¼���ر�Yλ��
				break;
			case MotionEvent.ACTION_UP:      //����Xλ��ִ��ҵ���߼�
				//����Xλ��
				float dx=x-mPreviousX;
				if(dx<-slideSpan)
				{   		//��Xλ��С����ֵ�򷵻����˵�
					activity.toAnotherView(ENTER_MENU);
				}
				break;
		}
		return true;
	}	
	@Override
	public boolean onKeyDown(int keyCode,KeyEvent e)    //�����¼�
	{
		if(keyCode==4)     //����ϵͳ  
		{			
			activity.toAnotherView(ENTER_MENU);
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
