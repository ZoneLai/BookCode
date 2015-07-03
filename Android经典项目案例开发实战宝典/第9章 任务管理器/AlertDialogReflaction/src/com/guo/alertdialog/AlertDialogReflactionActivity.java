package com.guo.alertdialog;

import java.lang.ref.WeakReference;
import java.lang.reflect.Field;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.app.Dialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class AlertDialogReflactionActivity extends Activity {
	//�Ի���
	 AlertDialog alertDialog = null;
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        //�½�һ���Ի���
        Builder mBuilder=new AlertDialog.Builder(this); 
        mBuilder.setMessage("Hello!");
        mBuilder.setTitle("��ʾ��");
        mBuilder.setNegativeButton("�ر�", new myListener());
        mBuilder.setPositiveButton("ȷ��", new myListener());
        alertDialog= mBuilder.create();
        try {
        	//���mAlert˽�б���
			Field mfield=alertDialog.getClass().getDeclaredField("mAlert");
			mfield.setAccessible(true);
			//���mAlert������alertDialog��ֵ
			Object obj=mfield.get(alertDialog);
			mfield=obj.getClass().getDeclaredField("mHandler");
			//�����Ƿ���ʹ��Ȩ�ޣ�true��ʾ�����
			mfield.setAccessible(true);
			//�����ض���obj��mfield��ֵ
			mfield.set(obj, new MyHandler(alertDialog));
		} catch (Exception e) {
			e.printStackTrace();
		}
		alertDialog.show();
    }
    class myListener implements DialogInterface.OnClickListener{
		@Override
		public void onClick(DialogInterface dialog, int which) {
			// TODO Auto-generated method stub
			switch(which)
			{
			//ȷ����ť
				case DialogInterface.BUTTON_POSITIVE:
					dialog.dismiss();
					break;
			//ȡ����ť
				case DialogInterface.BUTTON_NEGATIVE:
					break;
			}
		}   	
    }
    //�Զ���Ĵ�����
    private class MyHandler extends Handler{
    private static final int MSG_DISMISS_DIALOG = 1;
    private WeakReference<DialogInterface> mDialog;
    public MyHandler(DialogInterface dialog){
    	mDialog=new WeakReference<DialogInterface>(dialog);
    }
    @Override
    public void handleMessage(Message msg) {
        switch (msg.what) {
            case DialogInterface.BUTTON_POSITIVE:
            case DialogInterface.BUTTON_NEGATIVE:
            case DialogInterface.BUTTON_NEUTRAL:
            	((DialogInterface.OnClickListener) msg.obj).onClick(mDialog.get(), msg.what);
                break;
                //�˴�ȥ�������ضԻ���Ĳ���
            case MSG_DISMISS_DIALOG:    
            	break;
        	}
    	} 
    };
}