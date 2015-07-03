package com.supermario.playmusic;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
public class PlayMusicActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        //��ʼ��ť
        Button start=(Button)findViewById(R.id.button1);
        //ֹͣ��ť
        Button stop=(Button)findViewById(R.id.button2);
        //����������ֹͣService��intent
        final Intent it=new Intent("android.guo.service.playmusic");
        //Ϊ����ʼ����ť�󶨼�����
        start.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				//��������
				startService(it);
			}      	
        });
        //Ϊ��ֹͣ����ť�󶨼�����
        stop.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				//ֹͣ����
				stopService(it);
			}      	
        });
    }
}