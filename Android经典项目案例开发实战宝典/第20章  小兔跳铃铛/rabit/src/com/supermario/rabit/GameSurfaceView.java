package com.supermario.rabit;

import java.util.ArrayList;
import java.util.List;
import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
//��Ϸ������
public class GameSurfaceView extends SurfaceView implements
		SurfaceHolder.Callback {
	//����
	private Rabit rabit;
	//ˢ����
	private RefurbishThread refurbishThread;
	//����
	private List<Bell> bell_list = new ArrayList<Bell>();
	//����
	private Backgroud bg;
	//������
	private Context context;
	//����������
	private BellCreator bell_creator;
	//С��
	private Bird bird;
	private SurfaceHolder holder;
	private Bitmap bitmap_jump;
	//��������ť�Ƿ񱻰���
	private boolean jump_button_clicked = false;
	private boolean jump_comm_flag = false;
	//�Ƿ񲥷����ֱ�־λ
	private boolean audio_on = false;
	//�����ṩ��
	private AudioProvider audioProvider;
	//����
	private int score = 0;
	//��߷���
	private int highest_score;
	//ײ������
	private int hit_count = 0;
	private Paint paint;
	//��Ϸ������־
	private boolean game_over = false;
	//��������
	private Conclusion conclusion;
	//���캯��
	public GameSurfaceView(Context context) {
		super(context);
		this.context = context;
		//ʵ����С��
		rabit = new Rabit(context);
		//ʵ��������
		bg = new Backgroud(context);
		//ʵ������������
		conclusion = new Conclusion(this);
		bitmap_jump = BitmapFactory.decodeResource(context.getResources(),
				R.drawable.button);
		//��ʼ����������
		init_audio();
		//��ʼ����߷�����ʾ
		init_highest_score();
		//��ʼ������������
		bell_creator = new BellCreator(context);
		bird = new Bird(context);
		//ˢ����
		refurbishThread = new RefurbishThread();
		//��ʼ�������б�
		init_bell_list();
		paint = new Paint();
		this.holder = this.getHolder();
		holder.addCallback(this);
		this.setFocusable(true);
	}

	private void init() {
		rabit.init();
		bg.init();
		init_bird();
		jump_button_clicked = false;
		jump_comm_flag = false;
		for (int i = 0; i < bell_list.size(); ++i) {
			bell_creator.recycle(bell_list.get(i));
		}
		bell_creator.init();
		init_bell_list();
		//����������߷���
		highest_score = (highest_score > score) ? highest_score : score;
		score = 0;
		hit_count = 0;
	}
	//��ʼ��С��
	private void init_bird() {
		bird.setState(Bird.BIRD_LEFT_FLY0);
		//����С���ʼλ��
		bird.setCenter_x(240);
		bird.setCenter_y(30);
		//��ʾ����Ļ��
		bird.setOn_screen(true);
	}
	//��ʼ����߷���ʾ
	private void init_highest_score() {
		SharedPreferences settings = ((GameActivity) context)
				.getPreferences(Activity.MODE_PRIVATE);
		//ȡ�ô洢���ļ��е���߼�¼
		highest_score = settings.getInt("highestscore", 0);
	}
	//��ʼ��������
	private void init_audio() {
		this.audio_on = ((GameActivity) context).isAudio_on();
		if (audio_on) {
			audioProvider = new AudioProvider(context);
		}
	}
	//��ʼ������
	private void init_bell_list() {
		//�����5������
		Bell bell0 = bell_creator.createBell();
		Bell bell1 = bell_creator.createBell();
		Bell bell2 = bell_creator.createBell();
		Bell bell3 = bell_creator.createBell();
		Bell bell4 = bell_creator.createBell();
		//���������ĳ�ʼY����
		bell0.setCenter_y(170);
		bell1.setCenter_y(130);
		bell2.setCenter_y(90);
		bell3.setCenter_y(50);
		bell4.setCenter_y(10);
		//��������ӽ������б���
		bell_list.removeAll(bell_list);
		bell_list.add(bell0);
		bell_list.add(bell1);
		bell_list.add(bell2);
		bell_list.add(bell3);
		bell_list.add(bell4);
	}
	//���ƽ���
	protected void onDraw(Canvas canvas) {
		super.onDraw(canvas);
		bg.onDraw(canvas);
		//���Ϊ�����Ծ��ť���������½���ʾ��Ծ��ť
		if (!jump_button_clicked) {
			canvas.drawBitmap(bitmap_jump, 333, 199, paint);
		}
		//��������
		drawBell(canvas);
		//����С��
		rabit.onDraw(canvas);
		//���Ʒ���
		drawScore(canvas);
		//�����Ϸ����������ƽ�������
		if (game_over) {
			conclusion.onDraw(canvas);
		}
		//���С������Ļ�����С��
		if (bird.isOn_screen()) {
			bird.onDraw(canvas);
		}
	}
	//��������
	private void drawBell(Canvas canvas) {
		for (int i = 0; i < bell_list.size(); ++i) {
			bell_list.get(i).onDraw(canvas);
		}
	}
	//���Ʒ���
	private void drawScore(Canvas canvas) {
		//����������ɫΪ��ɫ
		paint.setColor(Color.WHITE);
		paint.setTextSize(15);
		canvas.drawText("" + score, 22, 22, paint);
	}
	//��������
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		if(keyCode == KeyEvent.KEYCODE_BACK) {
			this.refurbishThread.setGo_on(false);
		}
		return true;
	}
	//���������¼�
	public boolean onTouchEvent(MotionEvent event) {
		//��ô���λ�õ�xy����
		float x = event.getX();
		float y = event.getY();
		//�����Ϸ�Ѿ�����
		if (game_over) {
			//��Ϸ������Ĵ�������
			switch (event.getAction()) {
			//����˰�ť����
			case MotionEvent.ACTION_DOWN:
				if (x >= 165 && x <= 237 && y >= 154 && y <= 180) {
					conclusion.setPressed(true);
				}
				break;
			case MotionEvent.ACTION_MOVE:
				break;
			//����˷ǰ�ť����
			case MotionEvent.ACTION_UP:
				if (x >= 165 && x <= 237 && y >= 154 && y <= 180) {
					conclusion.setPressed(false);
					init();
					game_over = false;
				}
				break;
			default:
				break;
			}
		} else {
			//��Ϸ�еĴ�������
			if (jump_button_clicked) {
				//����С�õ�x��Ŀ��λ��
				switch (event.getAction()) {
				case MotionEvent.ACTION_DOWN:
				case MotionEvent.ACTION_MOVE:
				case MotionEvent.ACTION_UP:
					rabit.setX_destination(x);
					break;
				default:
					rabit.setX_destination(rabit.getX());
				}
			} else {
				//�������Ծ��ť
				if (x > 327 && x < 364 && y > 196 && y < 230) {
					if(event.getAction() == MotionEvent.ACTION_UP){
						jump_comm_flag = true;
						jump_button_clicked = true;
					}
				} else {
					switch (event.getAction()) {
					case MotionEvent.ACTION_DOWN:
					case MotionEvent.ACTION_MOVE:
					case MotionEvent.ACTION_UP:
						rabit.setX_destination(x);
						break;
					default:
						rabit.setX_destination(rabit.getX());
					}
				}
			}
		}
		return true;
	}
	//����ı�
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
	}
	//�����ʼ��
	public void surfaceCreated(SurfaceHolder holder) {
		refurbishThread.setGo_on(true);
		//�����߳�
		refurbishThread.start();
		if (audio_on) {
			//���ű�������
			audioProvider.play_bg();
		}
	}
	//��������
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		refurbishThread.setGo_on(false);
		if (audio_on) {
			//�ͷ�ý����Դ
			audioProvider.release();
		}
		//������߷�
		highest_score = (highest_score > score) ? highest_score : score;
		SharedPreferences pre = ((GameActivity) context).getPreferences(0);
		SharedPreferences.Editor editor = pre.edit();
		editor.putInt("highestscore", highest_score);
	}
	//ˢ�½���
	class RefurbishThread extends Thread {
		private boolean go_on = false;
		//ȡ���Ƿ����
		public boolean isGo_on() {
			return go_on;
		}
		//�����Ƿ����
		public void setGo_on(boolean goOn) {
			go_on = goOn;
		}
		//����
		public void run() {
			while (go_on) {
				try {
					// Thread.sleep(50);
					Thread.sleep(100);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				//�����������
				update_all_components();
				synchronized (holder) {
					Canvas canvas = holder.lockCanvas();
					//���ƻ���
					GameSurfaceView.this.onDraw(canvas);
					holder.unlockCanvasAndPost(canvas);
				}
			}
		}
	}
	//����С�õ�״̬
	private void update_rabit(){
		//���С���ڵ���
		if (rabit.isOnGround()) {
			// ����ˮƽ�����ƶ�
			// rabit ����Ŀ��λ��
			if (Math.abs(rabit.getX() - rabit.getX_destination()) < 5) {
				//���С���泯��
				if (rabit.isFaceLeft()) {
					//С��״̬Ϊ�泯��ͣ��
					rabit.setPic_state(Rabit.RABIT_PIC_LEFT_STOP);
					//����С�ó���
					rabit.setFace_state(Rabit.RABIT_FACE_LEFT);
					//С���ڵ���״̬Ϊͣ��
					rabit.setGround_state(Rabit.RABIT_LEFT_STOP);
				} else {
					//С��״̬Ϊ�泯��ͣ��
					rabit.setPic_state(Rabit.RABIT_PIC_RIGHT_STOP);
					//����С�ó���
					rabit.setFace_state(Rabit.RABIT_FACE_RIGHT);
					//С���ڵ���״̬Ϊͣ��
					rabit.setGround_state(Rabit.RABIT_RIGHT_STOP);
				}
			} else if (rabit.getX() - rabit.getX_destination() >= 5) {
				// rabit ��destination�����棬���������ƶ�
				rabit.setFace_state(Rabit.RABIT_FACE_LEFT);
				rabit.setX(rabit.getX() - Rabit.SPEED_X);
					//С���ڵ����������˶���ʾ��ͼƬ0
				if (rabit.getGround_state() == Rabit.RABIT_LEFT_MOVE1_ON_GROUND) {
					rabit.setGround_state(Rabit.RABIT_LEFT_MOVE2_ON_GROUND);
					rabit.setPic_state(Rabit.RABIT_PIC_ON_GROUND_LEFT_JUMP1);
					//С���ڵ����������˶���ʾ��ͼƬ1
				} else if (rabit.getGround_state() == Rabit.RABIT_LEFT_MOVE2_ON_GROUND) {
					rabit.setGround_state(Rabit.RABIT_LEFT_MOVE1_ON_GROUND);
					rabit.setPic_state(Rabit.RABIT_PIC_ON_GROUND_LEFT_JUMP0);
					//С���ڵ��������˶�һ��ʼ��ʾ��ͼƬ
				} else {
					rabit.setGround_state(Rabit.RABIT_LEFT_MOVE1_ON_GROUND);
					rabit.setPic_state(Rabit.RABIT_PIC_ON_GROUND_LEFT_JUMP0);
				}

			} else if (rabit.getX_destination() - rabit.getX() > 5) {
				// rabit ��destination�����棬���������ƶ�
				rabit.setX(rabit.getX() + Rabit.SPEED_X);
				rabit.setFace_state(Rabit.RABIT_FACE_RIGHT);
					//С���ڵ����������˶���ʾ��ͼƬ0
				if (rabit.getGround_state() == Rabit.RABIT_RIGHT_MOVE1_ON_GROUND) {
					rabit.setGround_state(Rabit.RABIT_RIGHT_MOVE2_ON_GROUND);
					rabit.setPic_state(Rabit.RABIT_PIC_ON_GROUND_RIGHT_JUMP1);
					//С���ڵ����������˶���ʾ��ͼƬ1
				} else if (rabit.getGround_state() == Rabit.RABIT_RIGHT_MOVE2_ON_GROUND) {
					rabit.setGround_state(Rabit.RABIT_RIGHT_MOVE1_ON_GROUND);
					rabit.setPic_state(Rabit.RABIT_PIC_ON_GROUND_RIGHT_JUMP0);
				} else {
					//С���ڵ��������˶�һ��ʼ��ʾ��ͼƬ
					rabit.setGround_state(Rabit.RABIT_RIGHT_MOVE1_ON_GROUND);
					rabit.setPic_state(Rabit.RABIT_PIC_ON_GROUND_RIGHT_JUMP0);
				}
			}
			//�������Ծ��ť
			if (jump_comm_flag) {
				rabit.setAir_state(Rabit.RABIT_ON_AIR_UP0);
				rabit.setGround_state(Rabit.RABIT_NOT_ON_GROUND);
				rabit.setY(rabit.getY() - Rabit.SPEED_Y);
				//�泯��
				if (rabit.isFaceLeft()) {
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_JUMP);
				} else {
					//�泯��
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_JUMP);
				}
				jump_comm_flag = false;
			}

		} else {
			// rabit�ڿ���
			// ����ˮ�����ƶ�
			if (rabit.getX() - rabit.getX_destination() >= 10) {
				// rabit ��destination�����棬���������ƶ�
				rabit.setFace_state(Rabit.RABIT_FACE_LEFT);
				rabit.setX(rabit.getX() - Rabit.SPEED_X_ON_AIR);
			} else if (rabit.getX_destination() - rabit.getX() > 10) {
				// rabit ��destination�����棬���������ƶ�
				rabit.setX(rabit.getX() + Rabit.SPEED_X_ON_AIR);
				rabit.setFace_state(Rabit.RABIT_FACE_RIGHT);
			}
			// ����ֱ���� �ƶ�
			if (rabit.getAir_state() == Rabit.RABIT_ON_AIR_UP0) {
				// С�������˶�
				rabit_move_up();
				rabit.setAir_state(Rabit.RABIT_ON_AIR_UP1);
				//С�ó�����
				if (rabit.isFaceLeft())
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_JUMP);
				//С�ó���
				else
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_JUMP);
				//����״̬1
			} else if (rabit.getAir_state() == Rabit.RABIT_ON_AIR_UP1) {
				// rabit.setY(rabit.getY()-Rabit.SPEED_Y);
				rabit_move_up();
				rabit.setAir_state(Rabit.RABIT_ON_AIR_UP2);
				if (rabit.isFaceLeft())
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_JUMP);
				else
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_JUMP);
				//����״̬2
			} else if (rabit.getAir_state() == Rabit.RABIT_ON_AIR_UP2) {
				// rabit.setY(rabit.getY()-Rabit.SPEED_Y);
				rabit_move_up();
				rabit.setAir_state(Rabit.RABIT_ON_AIR_UP3);
				if (rabit.isFaceLeft())
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_JUMP);
				else
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_JUMP);
				//����״̬3
			} else if (rabit.getAir_state() == Rabit.RABIT_ON_AIR_UP3) {
				// rabit.setY(rabit.getY()-Rabit.SPEED_Y);
				rabit_move_up();
				rabit.setAir_state(Rabit.RABIT_ON_AIR_UP4);
				if (rabit.isFaceLeft())
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_JUMP);
				else
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_JUMP);
				//����״̬4
			} else if (rabit.getAir_state() == Rabit.RABIT_ON_AIR_UP4) {
				// rabit.setY(rabit.getY()-Rabit.SPEED_Y);
				rabit_move_up();
				rabit.setAir_state(Rabit.RABIT_ON_AIR_UP5);
				if (rabit.isFaceLeft())
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_JUMP);
				else
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_JUMP);
				//����״̬5
			} else if (rabit.getAir_state() == Rabit.RABIT_ON_AIR_UP5) {
				rabit.setAir_state(Rabit.RABIT_ON_AIR_STOP);
				if (rabit.isFaceLeft())
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_STOP);
				else
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_STOP);
				//ֹͣ����
			} else if (rabit.getAir_state() == Rabit.RABIT_ON_AIR_STOP) {
				rabit.setAir_state(Rabit.RABIT_ON_AIR_DOWN);
				if (rabit.isFaceLeft())
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_STOP);
				else
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_STOP);
				//��ʼ���µ�
			} else if (rabit.getAir_state() == Rabit.RABIT_ON_AIR_DOWN) {
				// rabit.setY(rabit.getY() + Rabit.SPEED_Y);
				rabit.setAir_state(Rabit.RABIT_ON_AIR_DOWN);
				if (rabit.isFaceLeft())
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_DOWN);
				else
					rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_DOWN);
				rabit_move_down();
			}
		}
	}
	//����������״̬
	private void update_bells(){
		for (int i = 0; i < bell_list.size(); ++i) {
			Bell bell = bell_list.get(i);
			//������ը
			if (bell.isExplode()) {
				//��ը״̬0
				if (bell.getState() == Bell.BELL_EXPLODE0) {
					bell.setState(Bell.BELL_EXPLODE1);
				//��ը״̬1
				} else if (bell.getState() == Bell.BELL_EXPLODE1) {
					bell.setState(Bell.BELL_EXPLODE2);
				//��ը״̬2
				} else if (bell.getState() == Bell.BELL_EXPLODE2) {
					bell_list.remove(bell);
					bell_creator.recycle(bell);
					--i;
				}
			} else {
				if (rabit.isHitBell(bell)) {
					++hit_count;
					//�����ۼ�
					score += hit_count * 10;
					//������������
					if(audio_on) audioProvider.play_bell_ding();
					bell.setState(Bell.BELL_EXPLODE0);
					rabit.setAir_state(Rabit.RABIT_ON_AIR_UP0);
					if (rabit.isFaceLeft()) {
						rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_JUMP);
					} else {
						rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_JUMP);
					}
				}
			}
		}
	}
	//����С���״̬
	private void update_bird(){
		if (bird.isOn_screen()) {
			// ����ֱ
			if (bird.getCenter_y() > Constant.SCREEN_HEIGHT) {
				bird.setOn_screen(false);
			}
		}
		//��С������Ļ
		if (bird.isOn_screen()) {
			// С�񱻻���
			if (bird.isHited()) {
				if (bird.isFaceLeft()) {
					//����
					bird.setCenter_x(bird.getCenter_x() - Bird.BIRD_SPEED_POWER);
					if (bird.getCenter_x() < -5) {
						bird.setOn_screen(false);
					}
				} else {
					//����
					bird.setCenter_x(bird.getCenter_x()
									+ Bird.BIRD_SPEED_POWER);
					if (bird.getCenter_x() > Constant.SCREEN_WIDTH + 5) {
						bird.setOn_screen(false);
					}
				}
			} else {
				if (bird.isFaceLeft()) {
					//�����ٶ�
					bird.setCenter_x(bird.getCenter_x() - Bird.BIRD_SPEED);
					if (bird.getCenter_x() < -5) {
						bird.setCenter_x(0);
						bird.setState(Bird.BIRD_RIGHT_FLY0);
					} else {
						if (rabit.isHitBird(bird)) {
							++hit_count;
							//��������
							score *= 2;
							//�������
							if(audio_on) audioProvider.play_twitter();
							bird.setState(Bird.BIRD_LEFT_FLY_POWER);
							rabit.setAir_state(Rabit.RABIT_ON_AIR_UP0);
							if (rabit.isFaceLeft()) {
								rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_JUMP);
							} else {
								rabit.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_JUMP);
							}
						} else if (bird.getState() == Bird.BIRD_LEFT_FLY0) {
							bird.setState(Bird.BIRD_LEFT_FLY1);
						} else if (bird.getState() == Bird.BIRD_LEFT_FLY1) {
							bird.setState(Bird.BIRD_LEFT_FLY2);
						} else {
							bird.setState(Bird.BIRD_LEFT_FLY0);
						}
					}

				} else {
					bird.setCenter_x(bird.getCenter_x() + Bird.BIRD_SPEED);
					if (bird.getCenter_x() > Constant.SCREEN_WIDTH + 5) {
						bird.setCenter_x(Constant.SCREEN_WIDTH);
						bird.setState(Bird.BIRD_LEFT_FLY0);
					} else {
						if (rabit.isHitBird(bird)) {
							++hit_count;
							score *= 2;
							if(audio_on) audioProvider.play_twitter();
							bird.setState(Bird.BIRD_LEFT_FLY_POWER);
							rabit.setAir_state(Rabit.RABIT_ON_AIR_UP0);
							if (rabit.isFaceLeft()) {
								rabit
										.setPic_state(Rabit.RABIT_PIC_ON_AIR_LEFT_JUMP);
							} else {
								rabit
										.setPic_state(Rabit.RABIT_PIC_ON_AIR_RIGHT_JUMP);
							}
						} else if (bird.getState() == Bird.BIRD_RIGHT_FLY0) {
							bird.setState(Bird.BIRD_RIGHT_FLY1);
						} else if (bird.getState() == Bird.BIRD_RIGHT_FLY1) {
							bird.setState(Bird.BIRD_RIGHT_FLY2);
						} else {
							bird.setState(Bird.BIRD_RIGHT_FLY0);
						}
					}
				}
			}
		}
		// ���һ��bird���߼�
		if (hit_count % 11 == 0 && bird.isOn_screen() == false
				&& rabit.getY() < 210) {
			init_bird();
		}
	}
	//�����������
	private void update_all_components() {
		if (game_over)
			return;
		//����С��
		update_rabit();
		//��������
		update_bells();
		//����С��
		update_bird();
	}
	//С�������˶�
	private void rabit_move_up() {
		//���С�õ�λ������Ļ��������ʱ��ֻ����С�õ�����
		if (rabit.getCenter_y() > Constant.SCREEN_HEIGHT / 2) {
			rabit.setY(rabit.getY() - Rabit.SPEED_Y);
			return;
		}
		// ������Ļ�����ı仯
		// ����bells��λ��
		// ���е�bell����	
		// rabit��Ծ����Ļ1/2��~2/3ʱ��������������Components�仯
		if (rabit.getCenter_y() > 0.33 * Constant.SCREEN_HEIGHT) {
			for (int i = 0; i < bell_list.size(); ++i) {
				Bell bell = bell_list.get(i);
				//����������λ������
				bell.setCenter_y(bell.getCenter_y() + Rabit.SPEED_Y / 2);
			}
			//�����԰�������
			bg.drag_down((int) Rabit.SPEED_Y / 2);
			//С���԰�������
			bird.setCenter_y(bird.getCenter_y() + Rabit.SPEED_Y / 2);
			//С���԰�������
			rabit.setCenter_y(rabit.getCenter_y() - Rabit.SPEED_Y / 2);
		} else {
			// rabit��Ծ����Ļ��2/3������ʱ���������������ı仯
			for (int i = 0; i < bell_list.size(); ++i) {
				Bell bell = bell_list.get(i);
				//������ȫ������
				bell.setCenter_y(bell.getCenter_y() + Rabit.SPEED_Y);
			}
			bg.drag_down((int) Rabit.SPEED_Y);
			if (bird.isOn_screen()) {
				//С����ȫ������
				bird.setCenter_y(bird.getCenter_y() + Rabit.SPEED_Y);
			}
		}
		// �Ƿ���Ҫ������ص�bell, bell_list[0] ������״����ж����Ƿ����
		Bell lowBell = bell_list.get(0);
		if (lowBell != null) {
			if (lowBell.getCenter_y() > 230) {
				bell_list.remove(lowBell);
				//������ʧ����Ļ��Ұ������
				bell_creator.recycle(lowBell);
			}
		}
		// �ж��Ƿ���Ҫ����µ�bell�� bell_list[size-1] ������ߴ���ͨ�������ж�
		if (bell_list.size() > 0) {
			Bell upBell = bell_list.get(bell_list.size() - 1);
			if (upBell.getCenter_y() > 50)
				bell_list.add(bell_creator.createBell());
		}

	}
	//С�������ƶ�
	private void rabit_move_down() {
		if (rabit.getY() > 210) {
			//rabit�Ѿ���������Ļ�ײ���������������bell�� rabit���˸߿���׹ʱ������bell��bird��λ�ô���
			if (bg.isLowest()) {
				game_over = true;
				rabit.setY(Constant.RABIT_INIT_Y);
				if (rabit.isFaceLeft()) {
					rabit.setPic_state(Rabit.RABIT_PIC_LEFT_STOP);
				} else {
					rabit.setPic_state(Rabit.RABIT_PIC_RIGHT_STOP);
				}
				bg.init();
			} else {
				// ���������϶�
				bg.drag_up((int) Rabit.SPEED_Y);
				//��Ļ�ϵ�bird�����ƶ�
				if (bird.isOn_screen()) {
					bird.setCenter_y(bird.getCenter_y() - Rabit.SPEED_Y);
					if (bird.getCenter_y() < 0) {
						bird.setOn_screen(false);
					}
				}
				// ���е�bell�����ƶ�
				for (int i = 0; i < bell_list.size(); ++i) {
					Bell bell = bell_list.get(i);
					bell.setCenter_y(bell.getCenter_y() - Rabit.SPEED_Y);
				}
				// �����ƶ�����Ļ���bell
				if (bell_list.size() > 0) {
					Bell bell_up = bell_list.get(bell_list.size() - 1);
					if (bell_up.getCenter_y() < -Bell.BELL_OK_HEIGHT / 2) {
						//�Ƴ�����
						bell_list.remove(bell_up);
						bell_creator.recycle(bell_up);
					}
				}
			}
		} else {
			// rabit ��û������
			rabit.setY(rabit.getY() + Rabit.SPEED_Y);
		}
	}
	//ȡ�÷���
	public int getScore() {
		return score;
	}
	//���÷���
	public void setScore(int score) {
		this.score = score;
	}
	//ȡ����߷�
	public int getHighest_score() {
		return highest_score;
	}
	//������߷�
	public void setHighest_score(int highestScore) {
		highest_score = highestScore;
	}
}