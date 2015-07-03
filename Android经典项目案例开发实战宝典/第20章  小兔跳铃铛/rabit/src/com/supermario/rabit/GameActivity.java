package com.supermario.rabit;
import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.Window;
import android.view.WindowManager;
//��Ϸ������
public class GameActivity extends Activity {
	private GameSurfaceView gameSurfaceView;
	//����Ĭ��Ϊ��
	private boolean audio_on = true;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		//ȡ���������صĲ���
		audio_on = this.getIntent().getBooleanExtra("audio", true);
		gameSurfaceView = new GameSurfaceView(this);
		//��ʼ���ӽ���
		initWindow();
		this.setContentView(gameSurfaceView);
		//ȡ�ý���
		gameSurfaceView.requestFocus();
	}
	//����ȫ��
	public void initWindow(){
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
	}
	//�����·��ؼ���رս���
	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		gameSurfaceView.onKeyUp(keyCode, event);
		if(keyCode == KeyEvent.KEYCODE_BACK){
			this.finish();
		}
		return true;
	}
	//���������Ƿ��
	public boolean isAudio_on() {
		return audio_on;
	}
	//���������Ƿ��
	public void setAudio_on(boolean audioOn) {
		audio_on = audioOn;
	}	
}