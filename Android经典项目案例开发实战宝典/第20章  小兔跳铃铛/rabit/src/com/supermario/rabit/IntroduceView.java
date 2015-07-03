package com.supermario.rabit;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.View;
//��Ϸ��������
public class IntroduceView extends View{
	private Bitmap bg;
	private Paint paint;
	//�½����ʣ����ͼƬ
	public IntroduceView(Context context) {
		super(context);
		paint = new Paint();
		bg = BitmapFactory.decodeResource(this.getResources(), R.drawable.introduce);
	}
	//��ͼƬ���Ƶ�������
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		canvas.drawBitmap(bg, 0, 0, paint);
	}	
}
