package com.supermario.rabit;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
//С����
public class Bird {
	//������
	private Context context;
	//С����ٶ�
	private float speed = Constant.BIRD_SPEED;
	//С���ײ��֮����ٶ�
	private float speed_power = Constant.BIRD_SPEED_POWER;
	//С�����������
	private float center_x;
	private float center_y;
	//С���Ƿ��������Ļ
	private boolean on_screen = false;
	//С���״̬
	private int state;
	//С��ͼƬ��
	private Bitmap[] bitmaps  = new Bitmap[8];
	//����
	private Paint paint = new Paint();
	//С��ĸ߿�
	public static final float BIRD_WIDTH = Constant.BIRD_WIDTH;
	public static final float BIRD_HIGHT = Constant.BIRD_HIGHT;
	//С����ٶ�
	public static final float BIRD_SPEED = Constant.BIRD_SPEED;
	public static final float BIRD_SPEED_POWER = Constant.BIRD_SPEED_POWER;
	//С��ķ���״̬���������
	public static final int BIRD_LEFT_FLY0 = 0;
	public static final int BIRD_LEFT_FLY1 = 1;
	public static final int BIRD_LEFT_FLY2 = 2;
	//���ҷ���
	public static final int BIRD_RIGHT_FLY0 = 3;
	public static final int BIRD_RIGHT_FLY1 = 4;
	public static final int BIRD_RIGHT_FLY2 = 5;
	//������ٷ���
	public static final int BIRD_LEFT_FLY_POWER = 6;
	//���Ҽ��ٷ���
	public static final int BIRD_RIGHT_FLY_POWER = 7;
	//���캯��
	public Bird(Context context){
		this.context = context;
		//��ʼ��С���״̬
		state = BIRD_LEFT_FLY0;
		//��ʼ��ͼƬ��
		init_bitmaps();
	}
	//��ʼ��ͼƬ��
	public void init_bitmaps(){
		//�������
		bitmaps[0] = BitmapFactory.decodeResource(context.getResources(), R.drawable.bird_left_fly0);
		bitmaps[1] = BitmapFactory.decodeResource(context.getResources(), R.drawable.bird_left_fly1);
		bitmaps[2] = BitmapFactory.decodeResource(context.getResources(), R.drawable.bird_left_fly2);
		//���ҷ���
		bitmaps[3] = BitmapFactory.decodeResource(context.getResources(), R.drawable.bird_right_fly0);
		bitmaps[4] = BitmapFactory.decodeResource(context.getResources(), R.drawable.bird_right_fly1);
		bitmaps[5] = BitmapFactory.decodeResource(context.getResources(), R.drawable.bird_right_fly2);
		//������ٷ���
		bitmaps[6] = bitmaps[1];
		//���Ҽ��ٷ���
		bitmaps[7] = bitmaps[4];
	}
	//����С��
	public void onDraw(Canvas canvas){
		canvas.drawBitmap(bitmaps[state], center_x-BIRD_WIDTH/2, center_y-BIRD_HIGHT/2, paint);	
	}
	//�Ƿ���ײ��
	public boolean isHited(){
		return (state == BIRD_LEFT_FLY_POWER || state == BIRD_RIGHT_FLY_POWER);
	}
	//�Ƿ��泯��
	public boolean isFaceLeft(){
		return (state == BIRD_LEFT_FLY0 || state == BIRD_LEFT_FLY1 || state == BIRD_LEFT_FLY2 || state == BIRD_LEFT_FLY_POWER);
	}
	//�Ƿ��泯��
	public boolean isFaceRight(){
		return !isFaceLeft();
	}
	//ȡ���޶�
	public float getSpeed() {
		return speed;
	}
	//�����ٶ�
	public void setSpeed(int speed) {
		this.speed = speed;
	}
	//ȡ�ñ�ײ������ٶ�
	public float getSpeed_power() {
		return speed_power;
	}
	//��ñ�ײ������ٶ�
	public void setSpeed_power(int speedPower) {
		speed_power = speedPower;
	}
	//ȡ������x����
	public float getCenter_x() {
		return center_x;
	}
	//��������x����
	public void setCenter_x(float centerX) {
		center_x = centerX;
	}
	//ȡ������y����
	public float getCenter_y() {
		return center_y;
	}
	//��������y����
	public void setCenter_y(float centerY) {
		center_y = centerY;
	}
	//�ж��Ƿ�����Ļ
	public boolean isOn_screen() {
		return on_screen;
	}
	//�����Ƿ�����Ļ
	public void setOn_screen(boolean onScreen) {
		on_screen = onScreen;
	}
	//ȡ��״̬
	public int getState() {
		return state;
	}
	//����״̬
	public void setState(int state) {
		this.state = state;
	}
}