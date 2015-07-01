package wyf.jazz;

import java.io.IOException;
import static wyf.jazz.Constant.*;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.GLUtils;
public class MySurfaceView extends GLSurfaceView
{
	float cx=0;//�����xλ��
	float cy=10;//�����yλ��
	float cz=30;//�����zλ��
	
	float tx=0;////Ŀ���xλ��
	float ty=2;//Ŀ���yλ��
	float tz=0;//Ŀ���zλ��
	private SceneRenderer mRenderer;
	public MySurfaceView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
	}
	
	
	private class SceneRenderer implements GLSurfaceView.Renderer
	{
		int cubeTextureId;//����������ID
		int ballTextureId;//������ID
		int floorTextureId;//��������
		BallForDraw ball;//��
		Cube cubeTexture;//����������
		TextureRect floor;//����
		Ball_Go_Thread bgt;//���˶��߳�
		List<LogicalBall> albfc=new ArrayList<LogicalBall>();
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
            //gl.glRotatex(90, 1, 0, 0);
            cubeTexture.drawSelf(gl);//������������
            gl.glPopMatrix();//�ͷ�������
            
            gl.glPushMatrix();
            gl.glTranslatef(0, 0, 0);
            floor.drawSelf(gl);
            gl.glPopMatrix();
            
            gl.glPushMatrix();
            for(LogicalBall bfcc:albfc)   
			{				
				bfcc.drawSelf(gl);
			}
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
            gl.glFrustumf(-ratio*0.5f, ratio*0.5f, -0.5f, 0.5f, 1, 100);
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
    		
    		
    		cubeTextureId=initTexture(gl,R.drawable.base);//��ʼ������
    		cubeTexture=new Cube(cubeTextureId,HEIGHT,LENGTH,WIDTH);//������������   	
    		ballTextureId=initTexture(gl,R.drawable.basketball);//��ʼ��������
    		ball=new BallForDraw(11.25f,SCALE,ballTextureId);//������
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
    		albfc.add(new LogicalBall(ball,0,0,0.05f,0));
    		albfc.add(new LogicalBall(ball,-1,0,0,0.05f));
    		albfc.add(new LogicalBall(ball,1,1,0.05f,0.05f));
    		bgt=new Ball_Go_Thread(albfc);
			bgt.start();
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
