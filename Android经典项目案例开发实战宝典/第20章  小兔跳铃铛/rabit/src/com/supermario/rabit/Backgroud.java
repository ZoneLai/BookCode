package com.supermario.rabit;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
//����ͼƬ������
public class Backgroud {
	private Context context;
	//����ͼƬ
	private Bitmap bg;
	//����
	private Paint paint;
	private int my_y;
	//���캯��
	public Backgroud(Context context){
		this.context = context;
		paint = new Paint();
		//��ʼ��ͼƬ��Դ
		bg = BitmapFactory.decodeResource(context.getResources(), R.drawable.bg);
		//С�õĸ߶�
		my_y  = 0;
	}
	//���Ʊ���
	public void onDraw(Canvas canvas){
		if(my_y >= 0 && my_y <= 480){
			//ͼƬ�ĸ߶�Ϊ720������߶�Ϊ240��
			//����������ͼƬ�ײ��պ������ײ�ƽ��
			int screen_y = my_y - 480;
			canvas.drawBitmap(bg, 0, screen_y, paint);
		}else{
			//���߶ȳ���480
			int y_up = my_y % 480;
			int y_down = (my_y-240) % 480;
			if(y_up>=y_down){
				int screen_y = y_up - 480;
				//����һ�ű���ͼ
				canvas.drawBitmap(bg, 0, screen_y, paint);
			}else{
				//�������ű���ͼ�����ص�
				int screen_y1 = y_up - 480;
				int screent_y2 = y_up;
				canvas.drawBitmap(bg, 0, screen_y1, paint);
				canvas.drawBitmap(bg, 0, screent_y2, paint);
			}
		}
	}
	//��ʼ��С�ø߶�
	public void init(){
		this.my_y = 0;
	}
	//����������
	public void drag_down(int px){
		this.my_y += px;
	}
	//����������
	public void drag_up(int px){
		//Ϊ���½�����ص�ʱ�䲻���ڹ��������������������ı�������
		if(my_y > 960){
			my_y = (my_y - 480) % 480 + 480;
		}
		this.my_y -= px;
	}
	//�ж�С���Ƿ���䵽��͵�
	public boolean isLowest(){
		return (my_y >= -5 && my_y <= 10);
	}
	//ȡ��������
	public Context getContext() {
		return context;
	}
	//����������
	public void setContext(Context context) {
		this.context = context;
	}
	//ȡ�û���
	public Paint getPaint() {
		return paint;
	}
	//���û���
	public void setPaint(Paint paint) {
		this.paint = paint;
	}
}