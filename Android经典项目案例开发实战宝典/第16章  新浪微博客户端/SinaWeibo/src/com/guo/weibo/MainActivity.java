package com.guo.weibo;

import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.os.Bundle;

public class MainActivity extends Activity {
    /** Called when the activity is first created. */	
	DataHelper dbHelper;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        //��ȡ�˺��б�  
        dbHelper=new DataHelper(this);  
        //��ȡ���ݿ��û��б�
        final List<UserInfo> userList= dbHelper.GetUserList(true);  
        //�ر����ݿ�
        dbHelper.Close();
        //Ϊ�˿�����������Ч���������ӳ�1sִ���ж�
        TimerTask task=new TimerTask(){
        		public void run()
        		{
        			  //���Ϊ��˵����һ��ʹ�ã������Ի��������û�������Ȩ
        			 if(userList.isEmpty())
        		        {  
        		        	Builder mBuilder=new AlertDialog.Builder(MainActivity.this);
        		        	mBuilder.setTitle("��ʾ");
        		        	mBuilder.setMessage("����δ�����κ��˻����Ƿ����ڴ�����");
        		        	mBuilder.setPositiveButton("ȷ��", new OnClickListener(){      		
        						@Override
        						public void onClick(DialogInterface dialog, int which) {
        							// TODO Auto-generated method stub
        							Intent intent = new Intent();  
        							//����AuthorizeActivityҳ�����OAuth��֤  
        					        intent.setClass(MainActivity.this, AuthorizeActivity.class);  
        					        startActivity(intent);  
        					        //�رյ�ǰ����
        					        MainActivity.this.finish();
        						}     
        		        	}).setNegativeButton("ȡ��", new OnClickListener(){
        						@Override
        						public void onClick(DialogInterface dialog, int which) {
        							// TODO Auto-generated method stub
        							//ȡ����رձ�����
        							MainActivity.this.finish();
        						}      		
        		        	});
        		        	mBuilder.create().show();        
        		        }  
        		        else  
        		        {  
        			        Intent it=new Intent();
        			        //�����Ϊ�գ�����ת����½����
        			        it.setClass(MainActivity.this, LoginActivity.class);
        			        startActivity(it);
        			        //�رձ�����
        			        MainActivity.this.finish();
        		        }
        		}};
	    Timer timer=new Timer();
	    timer.schedule(task,1000);
    }
}