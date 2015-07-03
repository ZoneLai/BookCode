package com.supermario.cameratest;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.os.Bundle;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.ImageView;
import android.widget.ZoomControls;

public class Picture extends Activity {
	 //ͼƬ
	 ImageView iv;	 
	 //�Ŵ���С������
	 ZoomControls zoom;
	 //��Ļ��ʾ������
	 private int displayWidth;
	 //��Ļ��ʾ����߶�
	 private int displayHeight;
	 private float scaleWidth = 1;
	 private float scaleHeight = 1;
	 //ͼƬ���
     int bmpWidth;
     //ͼƬ�߶�
     int bmpHeight;
	 Bitmap bitmapOrg;
	 @Override
	 protected void onCreate (Bundle savedInstanceState) {
	 super.onCreate(savedInstanceState);
	 setContentView(R.layout.picture);
	 zoom=(ZoomControls)findViewById(R.id.zoomControls1);
     //ȡ����Ļ�ֱ��ʴ�С
     DisplayMetrics dm = new DisplayMetrics();
     getWindowManager().getDefaultDisplay().getMetrics(dm);
     displayWidth = dm.widthPixels;
     //��Ļ�߶ȼ�ȥzoomControls�ĸ߶�
     displayHeight = dm.heightPixels-80;
     zoom.setIsZoomInEnabled(true);
     zoom.setIsZoomOutEnabled(true);
    
     //����һ��ImageView
	 iv = (ImageView)findViewById(R.id.img);
	 Intent it=getIntent();
	 String picPath=(String) it.getCharSequenceExtra("path");
	 bitmapOrg=BitmapFactory.decodeFile(picPath,null);	 	 
	 iv.setImageBitmap(bitmapOrg);
	 //���ͼƬ�ĸ߶ȺͿ��
	 bmpWidth = bitmapOrg.getWidth();
	 bmpHeight = bitmapOrg.getHeight();
	 //ͼƬ�Ŵ�
	zoom.setOnZoomInClickListener(new OnClickListener()
	{
	    public void onClick(View v)
	    {
		    //����ͼƬ�Ŵ󵫱���
		    double scale = 1.25;
		    //�������Ҫ�Ŵ�ı���
		    scaleWidth = (float)(scaleWidth*scale);
		    scaleHeight = (float)(scaleHeight*scale);
		    if(scaleWidth > 1.25)
		    {
		    	scaleWidth=1;
		    	scaleHeight=1;
		    }
		    //�����µĴ�С��Bitmap����
		    Matrix matrix = new Matrix();
		    matrix.postScale(scaleWidth, scaleHeight);
		    Bitmap resizeBmp = Bitmap.createBitmap(bitmapOrg,0,0,bmpWidth,bmpHeight,matrix,true);
		    iv.setImageBitmap(resizeBmp);
	    }
	});
	//ͼƬ��С
	zoom.setOnZoomOutClickListener(new OnClickListener(){
	    public void onClick(View v) {
	    //����ͼƬ�Ŵ󵫱���
	    double scale = 0.8;
	    //�������Ҫ�Ŵ�ı���
	    scaleWidth = (float)(scaleWidth*scale);
	    scaleHeight = (float)(scaleHeight*scale);
	    //�����µĴ�С��Bitmap����
	    Matrix matrix = new Matrix();
	    matrix.postScale(scaleWidth, scaleHeight);
	    Bitmap resizeBmp = Bitmap.createBitmap(bitmapOrg,0,0,bmpWidth,bmpHeight,matrix,true);
	    iv.setImageBitmap(resizeBmp);
	    }
	});
	}
		//��Ӳ˵�ѡ��
	    public boolean onCreateOptionsMenu(Menu menu) 
	    {
	        super.onCreateOptionsMenu(menu);
	        //����
	        menu.add(0, 1, 0, "����");
	        //�˳�
	        menu.add(0, 2, 0, "�˳�");
	        return true;	        
	    }	    
	    //����˵�����
	    public boolean onOptionsItemSelected(MenuItem item) 
	    {
	        switch (item.getItemId()) 
	        {
	        case 1:
	        	//�������ս���
	        	Intent intent=new Intent();
		        intent.setClass(this, CameraTest.class);
				startActivity(intent);
	        	this.finish();
	            return true;
	        case 2:
	        	//�˳�����
	        	this.finish();
	            return true;
	        }
	        return super.onOptionsItemSelected(item);
	    }
}     