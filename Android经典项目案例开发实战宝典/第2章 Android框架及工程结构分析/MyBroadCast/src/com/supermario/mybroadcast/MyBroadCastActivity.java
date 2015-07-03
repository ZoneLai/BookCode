package com.supermario.mybroadcast;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
public class MyBroadCastActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        //���͹㲥��ť
        Button btn=(Button)findViewById(R.id.button1);
        //���÷��͹㲥��Ӧ��intent
        final Intent intent=new Intent("com.guo.receiver.myreceiver");
        btn.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				//���͹㲥
				sendBroadcast(intent);
			}       	
        });
    }
}