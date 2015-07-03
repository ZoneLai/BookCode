package com.supermario.rabit;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;

public class RabitActivity extends Activity {
	//��Ϸ��������
	private IntroduceView introduceView;
	//��Ϸ��������
	private HelpView helpView;
	//��Ч�򿪹ر����ý���
	private AudioView audioView;
	private View currentView;
	//Ĭ�Ϲر���Ч
	private boolean audio_on = false;
	//���캯��
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		//��������
		introduceView = new IntroduceView(this);
		//��������
		helpView = new HelpView(this);
		//�������ý���
		audioView = new AudioView(this);
		//��ʼ������
		initWindow();
		//���õ�ǰ��ʾ����Ϊ��������
		setContentView(introduceView);
		//��ǰ����Ϊ��������
		this.currentView = introduceView;
	}
	@Override
	protected void onRestart() {
		// TODO Auto-generated method stub
		super.onRestart();
		this.finish();
	}
	//��ʼ������
	private void initWindow() {
		//����ȫ��
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
	}
	//������Ϸ����
	public void toGameActivity() {
		Intent intent = new Intent();
		intent.setClass(this, GameActivity.class);
		//�����������ز���
		intent.putExtra("audio", audio_on);
		this.startActivity(intent);
	}
	//����������¼�
	@Override
	public boolean onTouchEvent(MotionEvent event) {
			//�����ǰ�ڿ�������
		if (currentView == introduceView) {
			if (event.getAction() == MotionEvent.ACTION_UP) {
				//�����������
				this.setContentView(helpView);
				this.currentView = helpView;
			}
			//�����ǰ�ڰ�������
		} else if (currentView == helpView) {
			if (event.getAction() == MotionEvent.ACTION_UP) {
				//�����������ý���
				this.setContentView(audioView);
				this.currentView = audioView;
			}
			//�����ǰ���������ý���
		} else {
			switch (event.getAction()) {
			case MotionEvent.ACTION_DOWN:
				//ȡ�ð��µ�xy����
				float x = event.getX();
				float y = event.getY();
				//�����λ���ڡ��ǡ���
				if (x > 30 && x < 60 && y > 177 && y < 207) {
					audioView.setClick(true);
					audioView.setAudio_on(true);
					//���½���
					audioView.invalidate();
					this.audio_on = true;
				}
				//�����λ���ڡ�����
				if (x > 330 && x < 360 && y > 177 && y < 207) {
					audioView.setClick(true);
					audioView.setAudio_on(false);
					//���½���
					audioView.invalidate();
					this.audio_on = false;
				}
				break;
			case MotionEvent.ACTION_UP:
				if (audioView.isClick()) {
					//������Ϸ����
					this.toGameActivity();
				}
				break;
			}
		}
		return true;
	}
}