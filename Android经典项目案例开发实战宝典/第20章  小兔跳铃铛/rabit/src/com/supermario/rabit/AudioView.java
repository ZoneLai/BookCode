package com.supermario.rabit;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.View;
//�������ý���
public class AudioView extends View {
	//����
	Paint paint;
	//Ĭ�������ر�
	boolean audio_on = false;
	//Ĭ��δ���
	boolean click = false;
	public AudioView(Context context) {
		super(context);
		paint = new Paint();
	}
	//����ͼƬ
	public void onDraw(Canvas canvas){
		super.onDraw(canvas);
		//������������Ϊ��ɫ
		canvas.drawColor(Color.BLACK);
		paint.setTextSize(20);
		//������ɫΪ��ɫ
		paint.setColor(Color.WHITE);
		//��������
		canvas.drawText("�Ƿ����Ч?", 125, 85, paint);
		if(click){
			if(audio_on){
				//���������򽫡��ǡ���Ϊ��ɫ
				paint.setColor(Color.RED);
				canvas.drawText("��", 33, 197, paint);
				paint.setColor(Color.WHITE);
				canvas.drawText("��", 336, 197, paint);
			}else{
				//���ر������򽫡�����Ϊ��ɫ
				paint.setColor(Color.WHITE);
				canvas.drawText("��", 33, 197, paint);
				paint.setColor(Color.RED);
				canvas.drawText("��", 336, 197, paint);
			}
		}else {
				//δ��������߶���Ϊ��ɫ
				paint.setColor(Color.WHITE);
				canvas.drawText("��", 33, 197, paint);
				canvas.drawText("��", 336, 197, paint);
		}
	}
	//���������Ƿ��
	public boolean isAudio_on() {
		return audio_on;
	}
	//���������Ƿ��
	public void setAudio_on(boolean audioOn) {
		audio_on = audioOn;
	}
	//�����Ƿ�����
	public boolean isClick() {
		return click;
	}
	//�����Ƿ�����
	public void setClick(boolean click) {
		this.click = click;
	}
}