package wyf.sj;

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
	float cy=3;//�����yλ��
	float cz=10;//�����zλ��
	
	float tx=0;////Ŀ���xλ��
	float ty=0;//Ŀ���yλ��
	float tz=0;//Ŀ���zλ��
	private SceneRenderer mRenderer;
	public MySurfaceView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
	}
	@Override
    public boolean onKeyDown(int keyCode, KeyEvent e)
	{
		switch(keyCode)
		{
		case 21://�������
			if(mRenderer.cover.xOffset>-2)
			{
				mRenderer.cover.xOffset-=0.2f;//ÿ�������ƶ�0.2f
			}
			break;
		case 22://�����Ҽ�
			if(mRenderer.cover.xOffset<2)
			{
				mRenderer.cover.xOffset+=0.2f;//ÿ�������ƶ�0.2f
			}
		}
		return true;
	}
	
	private class SceneRenderer implements GLSurfaceView.Renderer
	{
		int cubeTextureId;//����������ID
		int floorId;//�ذ�ID
		int coverId;//��ͷID
		Cube cubeTexture;//����������
		CubeColor cubeColor;//��ɫ������
		TextureRect floor;//�ذ�
		TextureRect cover;//��ͷ
		@Override
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
            gl.glTranslatef(1, 1, 0);//�ƶ�������
            cubeTexture.drawSelf(gl);//������������
            gl.glPopMatrix();//�ͷ�������
            
            gl.glPushMatrix();//��ȡ������
            gl.glTranslatef(-1, 0, 0);//�ƶ�������
            cubeColor.drawSelf(gl);//������ɫ������
            gl.glPopMatrix();//�ͷ�������
            
            gl.glPushMatrix();   //��ȡ������         
            for(int i=0;i<10;i++)
            { 
            	for(int j=0;j<10;j++)
            	{
            		gl.glPushMatrix();//��ȡ������ 
            		gl.glTranslatef(-2.5f+i*0.5f, 0, -2.5f+j*0.5f);//�ƶ�������
            		floor.drawSelf(gl);//���Ƶذ�
            		gl.glPopMatrix();//�ͷ�������
            	}
            }
            gl.glPopMatrix();//�ͷ�������
            
            gl.glPushMatrix();//��ȡ������ 
            gl.glEnable(GL10.GL_BLEND);//�������
            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);//����Դ���Ӻ�Ŀ������
            gl.glTranslatef(0, 1, 2);//�ƶ�������
            cover.drawSelf(gl);//������׼��
            gl.glDisable(GL10.GL_BLEND);//�رջ��
            gl.glPopMatrix();//�ͷ�������
            
		}

		@Override
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

		@Override
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
    		floorId=initTexture(gl,R.drawable.ground);
    		coverId=initTexture(gl,R.drawable.cover); 
    		cubeTexture=new Cube(cubeTextureId,2,1,1);//������������
    		cubeColor=new CubeColor(1,2,2);//������ɫ������
    		floor=new TextureRect//�����ذ�
    		(
    				1,0,1,floorId,
    				new float[]
			          {
	        				0,0,0,1,1,1,
	        				1,1,1,0,0,0
			          }
    		);
    		cover=new TextureRect//������׼��
    		(
    				1,1,0,coverId,
    				new float[]
			          {
	        				0,0,0,1,1,1,
	        				1,1,1,0,0,0
			          }
    		);
    		
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
