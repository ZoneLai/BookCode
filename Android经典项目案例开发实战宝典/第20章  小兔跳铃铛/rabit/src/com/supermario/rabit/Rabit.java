package com.supermario.rabit;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Paint;
//С����
public class Rabit {
	//������
	private Context context;
	//�û��������x����
	private float x;
	//�û��������y����
	private float y;
	//С�õ���������
	private float center_x;
	private float center_y;
	//��ǰ��С��ͼ��
	private Bitmap currentBitmap;
	//С������ͼ������
	private Bitmap[] allBitmaps;
	//������ٶ�
	private float speed_x_left;
	//���ҵ��ٶ�
	private float speed_x_right;
	//���ϵ��ٶ�
	private float speed_y_up;
	//���µ��ٶ�
	private float speed_y_down;
	//С���˶���Ŀ��x����
	private float x_destination;
	//ͼƬ��״̬
	private int pic_state;
	//С�õĳ���
	private int face_state;
	//С���ڵ����״̬
	private int ground_state;
	//С���ڿ��е�״̬
	private int air_state;
	private Bitmap[] bitmaps;
	//С�õĿ��
	public static final float RABIT_WIDTH = Constant.RABIT_WIDTH;
	public static final float RABIT_HEIGHT = Constant.RABIT_HEIGHT;
	
	//rabit ͼƬ��״̬
	public static final int RABIT_PIC_LEFT_STOP = 0;
	public static final int RABIT_PIC_RIGHT_STOP = 1;
	//�ڵ���������Ծ
	public static final int RABIT_PIC_ON_GROUND_LEFT_JUMP0 = 2;
	public static final int RABIT_PIC_ON_GROUND_LEFT_JUMP1 = 3;
	//�ڵ���������Ծ
	public static final int RABIT_PIC_ON_GROUND_RIGHT_JUMP0 = 4;
	public static final int RABIT_PIC_ON_GROUND_RIGHT_JUMP1 = 5;
	//�ڿ���������Ծ
	public static final int RABIT_PIC_ON_AIR_LEFT_JUMP = 6;
	//�ڿ���������Ծ
	public static final int RABIT_PIC_ON_AIR_RIGHT_JUMP = 7;
	//�ڿ���������ֹͣ
	public static final int RABIT_PIC_ON_AIR_LEFT_STOP = 8;
	//�ڿ���������ֹͣ
	public static final int RABIT_PIC_ON_AIR_RIGHT_STOP = 9;
	//�ڿ��������½��˶�
	public static final int RABIT_PIC_ON_AIR_LEFT_DOWN = 10;
	//�ڿ��������½��˶�
	public static final int RABIT_PIC_ON_AIR_RIGHT_DOWN = 11;
	//rabit������״̬
	public static final int RABIT_FACE_LEFT = 1;
	public static final int RABIT_FACE_RIGHT = 2;
	//rabit�ڵ���״̬
	public static final int RABIT_NOT_ON_GROUND = 0;
	public static final int RABIT_LEFT_STOP = 1;
	public static final int RABIT_RIGHT_STOP = 2;
	public static final int RABIT_LEFT_MOVE1_ON_GROUND = 3;
	public static final int RABIT_LEFT_MOVE2_ON_GROUND = 4;
	public static final int RABIT_RIGHT_MOVE1_ON_GROUND = 5;
	public static final int RABIT_RIGHT_MOVE2_ON_GROUND = 6;
	//rabit �ڿ��е�״̬ 
	public static final int RABIT_ON_AIR_UP0 = 0;
	public static final int RABIT_ON_AIR_UP1 = 1;
	public static final int RABIT_ON_AIR_UP2 = 2;
	public static final int RABIT_ON_AIR_UP3 = 3;
	public static final int RABIT_ON_AIR_UP4 = 4;
	public static final int RABIT_ON_AIR_UP5 = 5;
	public static final int RABIT_ON_AIR_STOP = 6;
	public static final int RABIT_ON_AIR_DOWN = 7;
	
	//rabit ÿ����Ծˢ�µĸ߶��ǲ�ͬ��
	public static final float RABIT_UP_DESTIATON0 = 30;
	public static final float RABIT_UP_DESTIATON1 = 20;
	public static final float RABIT_UP_DESTIATON2 = 10;
	//rabit ÿ���½�ˢ�µľ����ǲ�ͬ��
	public static final float RABIT_DOWN_DESTIATON0 = 10;
	public static final float RABIT_DOWN_DESTIATON1 = 20;
	public static final float RABIT_DWON_DESTIATON2 = 30;
	public static final float SPEED_X = 10;
	public static final float SPEED_Y = 15;
	public static final float SPEED_X_ON_AIR = 15;
	private Paint paint;
	
	public Rabit(Context context){
		this.context = context;
		//��ʼ��ͼƬ��Դ
		initBitmaps();
		//����С�õĳ�ʼλ��
		this.setX(Constant.RABIT_INIT_X);
		this.setY(Constant.RABIT_INIT_Y);
		x_destination = x;
		//��ʼ���ٶ�
		speed_x_left = 0;
		speed_x_right = 0;
		speed_y_down = 15;
		speed_y_up = 15;
		paint = new Paint();
		//��ʼ��С�õ�״̬
		ground_state = RABIT_RIGHT_STOP;
		air_state = RABIT_ON_AIR_UP0;
		face_state = RABIT_FACE_RIGHT;
		this.pic_state = RABIT_PIC_RIGHT_STOP;

	}
	//��ʼ������
	public void init(){
		//��ʼ��С�õ�������˶�״̬
		this.setY(Constant.RABIT_INIT_Y);
		ground_state = RABIT_RIGHT_STOP;
		air_state = RABIT_ON_AIR_UP0;
		face_state = RABIT_FACE_RIGHT;
		this.pic_state = RABIT_PIC_RIGHT_STOP;
	}
	//��ʼ��ͼƬ��Դ
	private void initBitmaps(){
		bitmaps = new Bitmap[12];
		bitmaps[Rabit.RABIT_PIC_LEFT_STOP] = BitmapFactory.decodeResource(context.getResources(), R.drawable.rabit_left_stop);
		bitmaps[Rabit.RABIT_PIC_RIGHT_STOP] = BitmapFactory.decodeResource(context.getResources(), R.drawable.rabit_right_stop);
		bitmaps[RABIT_PIC_ON_GROUND_LEFT_JUMP0] = BitmapFactory.decodeResource(context.getResources(), R.drawable.rabit_on_ground_left_jump0);
		bitmaps[RABIT_PIC_ON_GROUND_LEFT_JUMP1] = BitmapFactory.decodeResource(context.getResources(), R.drawable.rabit_on_ground_left_jump1);
		bitmaps[RABIT_PIC_ON_GROUND_RIGHT_JUMP0] = BitmapFactory.decodeResource(context.getResources(), R.drawable.rabit_on_ground_right_jump0);
		bitmaps[RABIT_PIC_ON_GROUND_RIGHT_JUMP1] = BitmapFactory.decodeResource(context.getResources(), R.drawable.rabit_on_ground_right_jump1);
		bitmaps[RABIT_PIC_ON_AIR_LEFT_JUMP] = bitmaps[RABIT_PIC_ON_GROUND_LEFT_JUMP0];
		bitmaps[RABIT_PIC_ON_AIR_RIGHT_JUMP] = bitmaps[RABIT_PIC_ON_GROUND_RIGHT_JUMP0];
		bitmaps[RABIT_PIC_ON_AIR_LEFT_DOWN] = BitmapFactory.decodeResource(context.getResources(), R.drawable.rabit_on_air_left_down);
		bitmaps[RABIT_PIC_ON_AIR_RIGHT_DOWN] = BitmapFactory.decodeResource(context.getResources(), R.drawable.rabit_on_air_right_down);;
		bitmaps[RABIT_PIC_ON_AIR_LEFT_STOP] = BitmapFactory.decodeResource(context.getResources(), R.drawable.rabit_on_air_left_stop);;
		bitmaps[RABIT_PIC_ON_AIR_RIGHT_STOP] = BitmapFactory.decodeResource(context.getResources(), R.drawable.rabit_on_air_right_stop);;
	}
	//����ͼƬ
	public void onDraw(Canvas canvas){
		canvas.drawBitmap(bitmaps[pic_state], x, y, paint);
	}
	//�ж��Ƿ�ײ������
	public boolean isHitBell(Bell bell){
		if(bell.isExplode()) return false;
		//���С�õ���������
		float x1 = center_x;
		float y1 = center_y;
		//�����������������
		float x2 = bell.getCenter_x();
		float y2 = bell.getCenter_y();
		//�ж�������������ľ���С��20�����ײ��
		return Math.pow(x1-x2, 2)+Math.pow(y1-y2, 2) < 400;
	}
	//�ж��Ƿ�ײ������
	public boolean isHitBird(Bird bird){
		//���С�õ���������
		float x1 = center_x;
		float y1 = center_y;
		//���С�����������
		float x2 = bird.getCenter_x();
		float y2 = bird.getCenter_y();
		//�ж�������������ľ���С��20�����ײ��
		return Math.pow(x1-x2, 2)+Math.pow(y1-y2, 2) < 400;
	}
	//�ж�С���Ƿ��ڵ���
	public boolean isOnGround(){
		return !(ground_state==RABIT_NOT_ON_GROUND);
	}
	//�ж�С���Ƿ��ڿ���
	public boolean isOnAir(){
		return !isOnGround();
	}
	//�ж�С���Ƿ�ͣ�ڵ���
	public boolean isOnGroundStop(){
		return ground_state==RABIT_LEFT_STOP||ground_state==RABIT_RIGHT_STOP;
	}
	//�ж�С���Ƿ��泯��
	public boolean isFaceLeft(){
		return face_state==RABIT_FACE_LEFT;
	}
	//�ж�С���Ƿ��泯��
	public boolean isFaceRight(){
		return !isFaceLeft();
	}
	//ȡ��������
	public Context getContext() {
		return context;
	}
	//����������
	public void setContext(Context context) {
		this.context = context;
	}
	//ȡ���û��������X����
	public float getX() {
		return x;
	}
	//�����û��������X����
	public void setX(float x) {
		this.x = x;
		this.center_x = x + RABIT_WIDTH/2;
	}
	//ȡ���û��������Y����
	public float getY() {
		return y;
	}
	//�����û��������Y����
	public void setY(float y) {
		this.y = y;
		this.center_y = y + RABIT_HEIGHT/2;
	}
	//ȡ�õ�ǰС�õ�ͼƬ
	public Bitmap getCurrentBitmap() {
		return currentBitmap;
	}
	//���õ�ǰС�õ�ͼƬ
	public void setCurrentBitmap(Bitmap currentBitmap) {
		this.currentBitmap = currentBitmap;
	}
	//ȡ��ͼƬ��
	public Bitmap[] getAllBitmaps() {
		return allBitmaps;
	}
	//����ͼƬ��
	public void setAllBitmaps(Bitmap[] allBitmaps) {
		this.allBitmaps = allBitmaps;
	}
	//ȡ��������ٶ�
	public float getSpeed_x_left() {
		return speed_x_left;
	}
	//����������ٶ�
	public void setSpeed_x_left(float speedXLeft) {
		speed_x_left = speedXLeft;
	}
	//ȡ�����ҵ��ٶ�
	public float getSpeed_x_right() {
		return speed_x_right;
	}
	//�������ҵ��ٶ�
	public void setSpeed_x_right(float speedXRight) {
		speed_x_right = speedXRight;
	}
	//ȡ�����ϵ��ٶ�
	public float getSpeed_y_up() {
		return speed_y_up;
	}
	//�������ϵ��ٶ�
	public void setSpeed_y_up(float speedYUp) {
		speed_y_up = speedYUp;
	}
	//ȡ�����µ��ٶ�
	public float getSpeed_y_down() {
		return speed_y_down;
	}
	//�������µ��ٶ�
	public void setSpeed_y_down(float speedYDown) {
		speed_y_down = speedYDown;
	}
	//ȡ��ͼƬ��
	public Bitmap[] getBitmaps() {
		return bitmaps;
	}
	//����ͼƬ��
	public void setBitmaps(Bitmap[] bitmaps) {
		this.bitmaps = bitmaps;
	}
	//ȡ�û���
	public Paint getPaint() {
		return paint;
	}
	//���û���
	public void setPaint(Paint paint) {
		this.paint = paint;
	}
	//ȡ��x���յ�λ��
	public float getX_destination() {
		return x_destination;
	}
	//����x���յ�λ��
	public void setX_destination(float xDestination) {
		x_destination = xDestination;
	}
	//ȡ�ó���
	public int getFace_state() {
		return face_state;
	}
	//��ó���
	public void setFace_state(int faceState) {
		face_state = faceState;
	}
	//ȡ�õ���״̬
	public int getGround_state() {
		return ground_state;
	}
	//���õ���״̬
	public void setGround_state(int groundState) {
		ground_state = groundState;
	}
	//ȡ�ÿ���״̬
	public int getAir_state() {
		return air_state;
	}
	//ȡ�ÿ���״̬
	public void setAir_state(int airState) {
		air_state = airState;
	}
	//ȡ��ͼƬ״̬
	public int getPic_state() {
		return pic_state;
	}
	//����ͼƬ״̬
	public void setPic_state(int picState) {
		pic_state = picState;
	}
	//ȡ��С�õ�����x����
	public float getCenter_x() {
		return center_x;
	}
	//����С������x����
	public void setCenter_x(float centerX) {
		center_x = centerX;
		this.x = centerX - RABIT_WIDTH/2;
	}
	//ȡ��С������Y����
	public float getCenter_y() {
		return center_y;
	}
	//����С������Y����
	public void setCenter_y(float centerY) {
		center_y = centerY;
		y = centerY - RABIT_HEIGHT/2;
	}	
}