package com.supermario.rabit;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.view.View;
//��Ϸ��������
public class HelpView extends View{
	private Bitmap bg;
	private Paint paint;
	//��ʼ�����ʣ����ͼƬ��Դ
	public HelpView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		paint = new Paint();
		bg = BitmapFactory.decodeResource(getResources(), R.drawable.help);
	}
	//�ڻ����ϻ���ͼƬ
	protected void onDraw(Canvas canvas){
		canvas.drawBitmap(bg, 0, 0, paint);
	}
}