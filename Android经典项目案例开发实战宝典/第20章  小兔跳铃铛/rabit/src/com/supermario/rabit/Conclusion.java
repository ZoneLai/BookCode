package com.supermario.rabit;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
//��Ϸ��������
public class Conclusion {
	//�Ƿ��°�ť
	private boolean pressed = false;
	private GameSurfaceView context;
	//����ͼƬ
	private Bitmap bg;
	//�𸴰�ť
	private Bitmap replay_button;
	private Paint paint = new Paint();

	public Conclusion(GameSurfaceView context) {
		this.context = context;
		//���ͼƬ��Դ
		this.bg = BitmapFactory.decodeResource(context.getContext()
				.getResources(), R.drawable.conclusion);
		//��ð�ťͼƬ
		replay_button = BitmapFactory.decodeResource(context.getContext()
				.getResources(), R.drawable.replay_button);
	}
	//����ͼƬ
	public void onDraw(Canvas canvas) {
		if (context.getHighest_score() > context.getScore()) {
			//���Ʊ���ͼƬ
			canvas.drawBitmap(bg, 95, 0, paint);
			//����������ɫΪ��ɫ
			paint.setColor(Color.WHITE);
			paint.setTextSize(17);
			canvas.drawText("SCORE", 175, 51, paint);
			//�����Ժ�ɫ������
			paint.setColor(Color.RED);
			canvas.drawText("" + context.getScore(), 180, 77, paint);
			paint.setColor(Color.WHITE);
			//��߷�
			canvas.drawText("HIGHEST SCORE", 148, 105, paint);
			//��ɫ��������߷�
			paint.setColor(Color.YELLOW);
			canvas.drawText(""+context.getHighest_score(), 175, 138, paint);

			if (pressed) {
				canvas.drawBitmap(replay_button, 164, 156, paint);
			}
		} else {
			canvas.drawBitmap(bg, 95, 0, paint);
			paint.setColor(Color.RED);
			paint.setTextSize(20);
			//ʹ�ú�ɫ������ʾ
			canvas.drawText("CONGRATULATIONS!", 100, 70, paint);
			paint.setColor(Color.WHITE);
			paint.setTextSize(17);
			//�Ƽ�¼ʱ�ð�ɫ������ʾ��߷�
			canvas.drawText("New Hightest Score:", 125, 115, paint);
			canvas.drawText(""+context.getScore(), 180, 147, paint);
		}
	}
	//��ʼ�������־λ
	public void init() {
		pressed = false;
	}
	//����Ƿ��ѵ��
	public boolean isPressed() {
		return pressed;
	}
	//�����Ƿ��ѵ��
	public void setPressed(boolean pressed) {
		this.pressed = pressed;
	}
}