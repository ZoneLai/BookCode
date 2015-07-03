package com.supermario.activitytest;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
public class ActivityTest extends Activity {
    /** Called when the activity is first created. */
	private static String TAG="ActivityTest";
    @Override
    //���򴴽�
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        Log.e(TAG,"onCreate");
        Button button1 = (Button) findViewById(R.id.button1);  
        // ����button���¼���Ϣ   
        button1.setOnClickListener(new Button.OnClickListener() {  
            public void onClick(View v)  
            {  
                // �½�һ��Intent����   
                Intent intent = new Intent();  
                // ָ��intentҪ��������  
                intent.setClass(ActivityTest.this, Activity2.class);  
                //����һ���µ�Activity  
                startActivity(intent);  
                // �رյ�ǰ��Activity   
                ActivityTest.this.finish();  
            }  
        });  
        Button button2 = (Button) findViewById(R.id.button2);  
        // ����button���¼���Ϣ  
        button2.setOnClickListener(new Button.OnClickListener() {  
            public void onClick(View v)  
            {  
                // �رյ�ǰ��Activity   
            	ActivityTest.this.finish();  
            }  
        });  
    }  
    //����ʼ
    public void onStart()
    {
    	super.onStart();
    	Log.e(TAG,"onStart");
    }
    //����ָ�
    public void onResume()  
    {  
        super.onResume();  
        Log.v(TAG, "onResume");  
    }
    //������ͣ
    public void onPause()  
    {  
        super.onPause();  
        Log.v(TAG, "onPause");  
    }    
    //����ֹͣ
    public void onStop()  
    {  
        super.onStop();  
        Log.v(TAG, "onStop");  
    }  
    //��������
    public void onDestroy()  
    {  
        super.onDestroy();  
        Log.v(TAG, "onDestroy");  
    }  
    //��������
    public void onRestart()  
    {  
        super.onRestart();  
        Log.v(TAG, "onReStart");  
    }  
}