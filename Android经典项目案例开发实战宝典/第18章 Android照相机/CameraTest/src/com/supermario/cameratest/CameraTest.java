package com.supermario.cameratest;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.graphics.PixelFormat;
import android.graphics.drawable.BitmapDrawable;
import android.hardware.Camera;
import android.hardware.Camera.AutoFocusCallback;
import android.hardware.Camera.PictureCallback;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceHolder.Callback;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.Button;
import android.widget.ImageView;

public class CameraTest extends Activity implements    
Callback, AutoFocusCallback{    
	//surfaceView����    
    SurfaceView mySurfaceView;
    //surfaceHolder���� 
    SurfaceHolder holder;   
    //�������    
    Camera myCamera;
    //��Ƭ����·��    
    String filePath="/sdcard/Pictures/";
    //�Ƿ�����־λ
    boolean isClicked = false; 
    //���հ�ť
    Button capture;
    //��Ƭ����ͼ
    ImageView editPic;
    Context mContext;
    //����jpegͼƬ�ص����ݶ���    
    /** Called when the activity is first created. */    
    @Override    
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);    
        //�ޱ���      
        requestWindowFeature(Window.FEATURE_NO_TITLE);         
        //�������㷽��    
        this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_SENSOR_PORTRAIT);   
        setContentView(R.layout.main);    
        //��ÿؼ�    
        mySurfaceView = (SurfaceView)findViewById(R.id.surfaceView1);    
        //��þ��    
        holder = mySurfaceView.getHolder();    
        //��ӻص�    
        holder.addCallback(this);   
        mContext=this;
        //�������ͣ�û����佫����ʧ��
        holder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
        //���հ�ť
        capture=(Button)findViewById(R.id.capture);
        //����ͼ
        editPic=(ImageView)findViewById(R.id.editPic);
        //���ð���������    
        capture.setOnClickListener(takePicture);  
        editPic.setOnClickListener(editOnClickListener);

    }     	
    @Override    
    public void surfaceChanged(SurfaceHolder holder, int format, int width,    
            int height) {    
        // TODO Auto-generated method stub    
        //���ò���
        Camera.Parameters params = myCamera.getParameters();   
        params.setPictureFormat(PixelFormat.JPEG);    
        myCamera.setParameters(params);   
        //����Ԥ��������ת90��
        myCamera.setDisplayOrientation(90);
        //��ʼԤ��    
        myCamera.startPreview();    
            
    }    
    @Override    
    public void surfaceCreated(SurfaceHolder holder) {    
        // TODO Auto-generated method stub    
        //�������    
        if(myCamera == null)    
        {    
            myCamera = Camera.open();    
            try {    
                myCamera.setPreviewDisplay(holder);    
            } catch (IOException e) {    
                // TODO Auto-generated catch block    
                e.printStackTrace();    
            }    
        }    
            
    }    
    @Override    
    public void surfaceDestroyed(SurfaceHolder holder) {    
        // TODO Auto-generated method stub    
        //�ر�Ԥ�����ͷ���Դ    
        myCamera.stopPreview();    
        myCamera.release();    
        myCamera = null;    
            
    }
    //�鿴ͼƬ
    OnClickListener editOnClickListener=new OnClickListener(){
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			String picPath=(String) v.getTag();
	        Intent intent=new Intent();
	        //��ͼƬ��·���󶨵�intent��
	        intent.putExtra("path", picPath);
	        intent.setClass(mContext, Picture.class);
	        //�����鿴ͼƬ����
			startActivity(intent);
			//�رյ�ǰ����
			CameraTest.this.finish();
		}			
	};
	//���հ���������
    OnClickListener takePicture=new OnClickListener(){
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
	        if(!isClicked)    
	        {    
	        	//�Զ��Խ�    
	            myCamera.autoFocus(CameraTest.this);
	            isClicked = true;    
	        }else    
	        {    
	        	//����Ԥ��  
	            myCamera.startPreview();  
	            isClicked = false;    
	        }
		}
	}; 
    //�Զ��Խ�ʱ����
    @Override    
    public void onAutoFocus(boolean success, Camera camera) {    
        // TODO Auto-generated method stub    
        if(success)    
        {    
            //��ò��� 
            Camera.Parameters params = myCamera.getParameters();    
            //���ò���
            params.setPictureFormat(PixelFormat.JPEG);      
            myCamera.setParameters(params);    
            //����
            myCamera.takePicture(null, null, jpeg);    
        }              
    }    
    PictureCallback jpeg = new PictureCallback() {               
        @Override    
        public void onPictureTaken(byte[] data, Camera camera) {    
            // TODO Auto-generated method stub    
            try    
            {
            // ���ͼƬ    
            Bitmap bm = BitmapFactory.decodeByteArray(data, 0, data.length);     
            SimpleDateFormat sDateFormat = new SimpleDateFormat("yyyyMMddhhmmss");     
            String date = sDateFormat.format(new java.util.Date()); 
            filePath=filePath+date+".jpg";
            File file = new File(filePath);
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(file));  
	          //��������ͼƬ�õ�matrix����
	   		 Matrix matrix = new Matrix();
	   		 matrix.postRotate(90);
	   		 //�����µ�ͼƬ
	   		 Bitmap rotateBitmap = Bitmap.createBitmap(bm, 0, 0, bm.getWidth(), bm.getHeight(), matrix, true);
            //��ͼƬ��JPEG��ʽѹ��������    
	   		rotateBitmap.compress(Bitmap.CompressFormat.JPEG, 100, bos);
         	//���    
            bos.flush();
            //�ر�    
            bos.close();
            editPic.setBackgroundDrawable(changeBitmapToDrawable(rotateBitmap));
            editPic.setTag(filePath);
            }catch(Exception e)    
            {    
                e.printStackTrace();    
            }                   
        }    
    };    
    public BitmapDrawable changeBitmapToDrawable(Bitmap bitmapOrg)
    {
    	 int width = bitmapOrg.getWidth();
		 int height = bitmapOrg.getHeight();
		 
		 //����Ԥת���ɵ�ͼƬ�Ŀ�͸�
		 int newWidth = 100;
		 
		 //���������ʣ��³ߴ��ԭ�ߴ�
		 float scaleWidth = (float)newWidth/width;
		 float scaleHeight = scaleWidth;
		 //��������ͼƬ�õ�matrix����
		 Matrix matrix = new Matrix();	 
		 //����ͼƬ����
		 matrix.postScale(scaleWidth, scaleHeight);
		 //�����µ�ͼƬ
		 Bitmap resizedBitmap = Bitmap.createBitmap(bitmapOrg, 0, 0, width, height, matrix, true);		 
		 //�����洴����Bitmapת����Drawable����ʹ�������ʹ����imageView��imageButton�ϡ�
		 BitmapDrawable bitmapDrawable = new BitmapDrawable(resizedBitmap);
		 return bitmapDrawable;
    }
} 