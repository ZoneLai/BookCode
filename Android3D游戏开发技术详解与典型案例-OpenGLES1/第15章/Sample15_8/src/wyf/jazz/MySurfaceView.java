package wyf.jazz;

import static wyf.jazz.Constant.*;

import java.io.IOException;
import java.io.InputStream;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.GLUtils;
import android.view.KeyEvent;
public class MySurfaceView extends GLSurfaceView
{
	float cx=0;//�����xλ��
	float cy=0;//�����yλ��
	float cz=0;//�����zλ��
	
	float tx=0;////Ŀ���xλ��
	float ty=0;//Ŀ���yλ��
	float tz=-15;//Ŀ���zλ��
	
	float xOffset=0;//��պ�X��λ�� 
	float yOffset=0;//��պ�Y��λ��
	float zOffset=0;//��պ�Z��λ��
	float direction=0.0f;  //���ð�����������
	final float DISTANCE_CAMERA_YACHT=20.0f; 
	final float DISTANCE_CAMERA_TARGET=2.0f;
	final float DEGREE_SPAN=(float)(5.0/180.0f*Math.PI);
	boolean turnFlag=true;
	private SceneRenderer mRenderer;
	public MySurfaceView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		
		cx=CAMERA_INI_X;//�����x����
        cy=CAMERA_INI_Y;//�����y����
        cz=CAMERA_INI_Z;//�����z����
         
        tx=(float)(cx-Math.sin(direction)*DISTANCE);//�۲�Ŀ���x����  
        ty=CAMERA_INI_Y-0.2f;//ƽ�ӹ۲�Ŀ���y����
       // ty=CAMERA_INI_Y-2f;//��۲�Ŀ���y����
        tz=(float)(cz-Math.cos(direction)*DISTANCE);//�۲�Ŀ���z����   
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
	}
	
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent e)
	{
		if(keyCode==4)
		{
			System.exit(0);
			return false;
		}
    	if(keyCode==19||keyCode==20)
    	{//���¼���ʾǰ�������
    		float xOffset=0;//�˲���Xλ��
    		float zOffset=0;//�˲���Zλ��
    		
    		switch(keyCode)
    		{
    		   case 19://���ϼ�����ǰ��
    			  //ǰ��ʱ�˶������뵱ǰ������ͬ
    			  xOffset=(float)-Math.sin(direction)*MOVE_SPAN;
    			  zOffset=(float)-Math.cos(direction)*MOVE_SPAN;
    		   break;
    		   case 20://���¼��������
    			   //����ʱ�˶������뵱ǰ�����෴
    			   xOffset=(float)Math.sin(direction)*MOVE_SPAN;
     			   zOffset=(float)Math.cos(direction)*MOVE_SPAN;
    		   break;
    		}
    		//�����˶����XZֵ
			cx=cx+xOffset;
			cz=cz+zOffset;
    	}
    	else
    	{
    		switch(keyCode)
    		{
	    		case 21:  //���������ת��
	    		  direction=direction+DEGREE_SPAN;	
	    		break;
	    		case 22:  //���Ҵ�����ת��
	    		  direction=direction-DEGREE_SPAN;  
	    		break;
    		}
    	}
    	//�����µĹ۲�Ŀ���XZ����
    	tx=(float)(cx-Math.sin(direction)*DISTANCE);//�۲�Ŀ���x���� 
        tz=(float)(cz-Math.cos(direction)*DISTANCE);//�۲�Ŀ���z����     		
    	return true;
	}
	
	private class SceneRenderer implements GLSurfaceView.Renderer
	{
		int cubeTextureId;
		Cube cube;
		//@Override
		public void onDrawFrame(GL10 gl) {
			// TODO Auto-generated method stub
			//����ƽ����ɫ
            gl.glShadeModel(GL10.GL_SMOOTH);
            //����Ϊ�򿪱������
    		gl.glEnable(GL10.GL_CULL_FACE);            
        	//�����ɫ��������Ȼ���
        	gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        	//���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();  
            
            
            
          //����cameraλ��
            GLU.gluLookAt
            (
            		gl, 
            		cx,   //����λ�õ�X
            		cy, 	//����λ�õ�Y
            		cz,   //����λ�õ�Z
            		tx, 	//�����򿴵ĵ�X
            		ty,   //�����򿴵ĵ�Y
            		tz,   //�����򿴵ĵ�Z
            		0, 
            		1, 
            		0
            ); 
            
            gl.glPushMatrix();
            gl.glTranslatef(xOffset, yOffset, zOffset);
            cube.drawSelf(gl);
            gl.glPopMatrix();
		} 

		//@Override
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			// TODO Auto-generated method stub
			 //�����Ӵ���С��λ�� 
        	gl.glViewport(0, 0, width, height);
        	//���õ�ǰ����ΪͶӰ����
            gl.glMatrixMode(GL10.GL_PROJECTION);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();
            //����͸��ͶӰ�ı���
            float ratio = (float) width / height;
            //���ô˷����������͸��ͶӰ����
            gl.glFrustumf(-ratio*1.5f, ratio*1.5f, -1.5f, 1.5f, 1, 100);
		}

		//@Override
		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			// TODO Auto-generated method stub
			 //�رտ�����  
        	gl.glDisable(GL10.GL_DITHER);
        	//�����ض�Hint��Ŀ��ģʽ������Ϊ����Ϊʹ�ÿ���ģʽ
            gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT,GL10.GL_FASTEST);
            //������Ļ����ɫ��ɫRGBA
            gl.glClearColor(0,0,0,0);
            //������ɫģ��Ϊƽ����ɫ   
            gl.glShadeModel(GL10.GL_SMOOTH);
            //������Ȳ���
            gl.glEnable(GL10.GL_DEPTH_TEST);            
            //����Ϊ�򿪱������
    		gl.glEnable(GL10.GL_CULL_FACE);
    		
    		cubeTextureId=initTexture(gl,R.drawable.sky);
    		cube=new Cube(cubeTextureId,HEIGHT,LENGTH,WIDTH);
		}
		
	}
	//��ʼ������
	public int initTexture(GL10 gl,int drawableId)
	{
		//��������ID
		int[] textures = new int[1];
		gl.glGenTextures(1, textures, 0);//�ṩδʹ�õ������������    
		int textureId=textures[0];    
		gl.glBindTexture(GL10.GL_TEXTURE_2D, textureId);//������ʹ���������
		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER,GL10.GL_NEAREST);//ָ���Ŵ���С���˷���
        gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_MAG_FILTER,GL10.GL_LINEAR);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S,GL10.GL_CLAMP_TO_EDGE);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T,GL10.GL_CLAMP_TO_EDGE);

        InputStream is = this.getResources().openRawResource(drawableId);
        Bitmap bitmapTmp;
        try 
        {
        	bitmapTmp = BitmapFactory.decodeStream(is);
        } 
        finally 
        { 
            try 
            {
                is.close();
            } 
            catch(IOException e) 
            {
                e.printStackTrace();
            }
        }
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmapTmp, 0);//�����ά����
        bitmapTmp.recycle(); 
        
        return textureId;
	}
}
