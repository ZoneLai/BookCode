package wyf.zs;

import java.io.IOException;
import static wyf.zs.Constant.*;

import java.io.InputStream;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.GLUtils;
import android.util.Log;
import android.view.KeyEvent;
public class MySurfaceView extends GLSurfaceView
{
	static float cx=0;//�����xλ��
	static float cy=10;//�����yλ��
	static float cz=20;//�����zλ��
	
	static float tx=0;////Ŀ���xλ��
	static float ty=2;//Ŀ���yλ��
	static float tz=0;//Ŀ���zλ��
	
	float xAngle=0;
	float ballx=0;//��ĳ�ʼλ��
	float ballz=0;
	int keyState=0;//����״̬  1-up 2-down 4-left 8-right
	KeyThread keyThread;
	public SceneRenderer mRenderer;
	public MySurfaceView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
        keyThread=new KeyThread(this);
        keyThread.start();      
	}
	@Override
	public boolean onKeyDown(int keyCode,KeyEvent e)
	{
		switch(keyCode)
		{
		case 19:
			keyState=keyState|0x1;
			break;
		case 20:
			keyState=keyState|0x2;
			break;
		case 21:
			keyState=keyState|0x4;
			break;
		case 22:
			keyState=keyState|0x8;
			break;
		}
		return true;
	}
	@Override
	public boolean onKeyUp(int keyCode,KeyEvent e)
	{
		switch(keyCode)
		{		
		case 19:
		case 20:
		case 21:
		case 22:
			direction=0;
			keyState=0;
			break;
		}
		return true;
	}
	
	public class SceneRenderer implements GLSurfaceView.Renderer
	{
		int ballTextureId;//������ID
		int floorTextureId;//��������
		BallForDraw ball;//��
		TextureRect floor;//����

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
            gl.glPushMatrix();//��ȡ������
            gl.glTranslatef(0, 2*STARTY+HEIGHT+SCALE, 0);//�ƶ�������
            gl.glPopMatrix();//�ͷ�������
            
            gl.glPushMatrix();
            gl.glTranslatef(0, 0, 0);
            floor.drawSelf(gl);
            gl.glPopMatrix();
            
            gl.glPushMatrix();
            
            gl.glTranslatef(ballx, SCALE+0.05f, ballz);
            gl.glRotatef(xAngle, 1, 0, 0);
            ball.drawSelf(gl);
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
            gl.glFrustumf(-ratio, ratio, -1f, 1f, 1, 100);
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
    		
    		
    		ballTextureId=initTexture(gl,R.drawable.basketball);//��ʼ��������
    		ball=new BallForDraw(ballx,ballz,11.25f,SCALE,ballTextureId);//������
    		floorTextureId=initTexture(gl,R.drawable.floor);
    		floor=new TextureRect//�����ذ�
    		(
    				20,0,30,floorTextureId,
    				new float[]
			          {
	        				0,0,0,1,1,1,
	        				1,1,1,0,0,0
			          }
    		);
		new Thread()
		{
			public void run()
			{
				while(true)
				{
					xAngle+=3f;
					try {
						sleep(30);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			}
		}.start();
	}
	//��ʼ������
	
 }
	public int initTexture(GL10 gl,int drawableId)
	{
		//��������ID
		int[] textures = new int[1];
		gl.glGenTextures(1, textures, 0);//�ṩδʹ�õ������������    
		int textureId=textures[0];    
		gl.glBindTexture(GL10.GL_TEXTURE_2D, textureId);//������ʹ���������
		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER,GL10.GL_NEAREST);//ָ���Ŵ���С���˷���
        gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_MAG_FILTER,GL10.GL_LINEAR);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S,GL10.GL_REPEAT);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T,GL10.GL_REPEAT);

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
