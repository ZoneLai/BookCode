package com.rss.activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

public class LoginActivity extends Activity {
	//��½��ť
	private Button loginButton;
	//��½�ı�
	private TextView loginText;
	//��½ͼƬ
	private ImageView imagView;
	//ͼƬ͸����
	private int i_alpha = 255;
	private Handler mHandler = new Handler();
	boolean isShow = false;
	private Thread thread;
	private Intent intent;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.login);
		//��ʼ������Ԫ��
		loginButton = (Button)findViewById(R.id.login_in);
		loginText = (TextView)findViewById(R.id.logining);		
		imagView = (ImageView)findViewById(R.id.login_rss);
		//��ʼ��ͼƬ�ֱ���
		imagView.setAlpha(i_alpha);
		isShow = true;			
		//����ͼƬ�ֱ���
		mHandler = new Handler() {
			@Override
			public void handleMessage(Message msg) {				
				super.handleMessage(msg);
				imagView.setAlpha(i_alpha);
			}			
		};
		
		//�����߳�ÿ��100ms����һ��ͼƬ͸����
		thread = new Thread(new Runnable() {		
			public void run() {
				while(isShow) {
					try {
						Thread.sleep(100);
						updateAlpha();						
					}catch (InterruptedException  e) {
						e.printStackTrace();
					}
				}				
			}
			
		});			
		//��½����������
		loginButton.setOnClickListener(new OnClickListener() {			
			public void onClick(View v) {
				intent = new Intent();
				intent.setClass(LoginActivity.this, SelectChannel.class);
				//�����߳�
				thread.start();			
				//���õ�½��ť���ɼ�
				loginButton.setVisibility(View.INVISIBLE);
				//���õ�½�ı���ʾ
				loginText.setVisibility(View.VISIBLE);				
			}
		});
	}
	//����ͼƬ͸����
	protected void updateAlpha() {
		//ÿ�μ�25
		if((i_alpha-25) >= 0) {
			i_alpha = i_alpha - 25;		
			
		}else {
			//��͸���ȵ���25���رյ�ǰ���棬�����½���
			i_alpha = 0;
			isShow = false;
			startActivity(intent);	
			LoginActivity.this.finish();
		}		
		//������Ϣ
		mHandler.sendMessage(mHandler.obtainMessage()); 
	}
}