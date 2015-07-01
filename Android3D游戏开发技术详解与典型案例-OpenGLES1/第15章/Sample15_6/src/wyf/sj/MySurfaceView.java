package wyf.sj;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.GLUtils;
import static wyf.sj.Constant.*;
public class MySurfaceView extends GLSurfaceView{
	SceneRenderer mRenderer;//������Ⱦ��
	MyActivity activity=(MyActivity)this.getContext();//��ȡActivity
	float cx=0;//�����xλ��
	float cy=3;//�����yλ��
	float cz=10;//�����zλ��
	
	float tx=0;////Ŀ���xλ��
	float ty=0;//Ŀ���yλ��
	float tz=0;//Ŀ���zλ��
	ArrayList<BulletForControl> alBFC;//�ӵ������б�
	BulletGoThread bgt;//�ӵ��˶��߳�
	Cube cube;//����������
	public MySurfaceView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
        alBFC=new ArrayList<BulletForControl>();
	}

	private class SceneRenderer implements GLSurfaceView.Renderer
	{

		int taperId;//Բ׶������ID
		int cylinderId;//Բ��������ID
		int cubeId;//����������ID
		int[] exploTextureId=new int[6];//��ը����
		
		Bullet bullet;//�����ӵ�
		TextureRect[] trExplo=new TextureRect[6];

		BulletForControl bfc;
		@Override
		public void onDrawFrame(GL10 gl) {
			// TODO Auto-generated method stub
			//�����ɫ����
        	gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        	//���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();   
            //����cameraλ��
            GLU.gluLookAt
            (
            		gl, 
            		cx,   //�������Xλ��
            		cy, 	//�������Yλ��
            		cz,   //�������Zλ��
            		tx, 	//Ŀ���X
            		ty,   //Ŀ���Y
            		tz,   //Ŀ���Z
            		0, //UPλ��
            		1, 
            		0
            );
            gl.glPushMatrix();
            for(int i=0;i<alBFC.size();i++)
            {
            	alBFC.get(i).drawSelf(gl);//�����ӵ�
            }
            gl.glPopMatrix();
            
            gl.glPushMatrix();
            gl.glTranslatef(CUBE_OFFSET_X, CUBE_OFFSET_Y, CUBE_OFFSET_Z);
            cube.drawSelf(gl);//����������
            gl.glPopMatrix();
            
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
            gl.glClearColor(0.8f,0.8f,0.8f,0);
            //������ɫģ��Ϊƽ����ɫ   
            gl.glShadeModel(GL10.GL_SMOOTH);
            //������Ȳ���
            gl.glEnable(GL10.GL_DEPTH_TEST);            
            //����Ϊ�򿪱������
    		gl.glEnable(GL10.GL_CULL_FACE);  
         
    		
    		taperId=initTexture(gl,R.drawable.bullet);//��ʼ������ID
    		cylinderId=initTexture(gl,R.drawable.bullet);//��ʼ���ӵ�����ID
    		cubeId=initTexture(gl,R.drawable.stone);//����������ID
    		//��ʼ����ը����
    		exploTextureId[0]=initTexture(gl,R.drawable.explode1);
    		exploTextureId[1]=initTexture(gl,R.drawable.explode2);
    		exploTextureId[2]=initTexture(gl,R.drawable.explode3);
    		exploTextureId[3]=initTexture(gl,R.drawable.explode4);
    		exploTextureId[4]=initTexture(gl,R.drawable.explode5);
    		exploTextureId[5]=initTexture(gl,R.drawable.explode6);
    		
    		
    		//������ը�������֡
            trExplo[0]=new TextureRect(exploTextureId[0],LONG_R*3f,LONG_R*3f);
            trExplo[1]=new TextureRect(exploTextureId[1],LONG_R*3f,LONG_R*3f);
            trExplo[2]=new TextureRect(exploTextureId[2],LONG_R*3f,LONG_R*3f);
            trExplo[3]=new TextureRect(exploTextureId[3],LONG_R*3f,LONG_R*3f);
            trExplo[4]=new TextureRect(exploTextureId[4],LONG_R*3f,LONG_R*3f);
            trExplo[5]=new TextureRect(exploTextureId[5],LONG_R*3f,LONG_R*3f);
    		bullet=new Bullet(taperId,cylinderId);//�����ӵ�����
    		cube=new Cube(cubeId,2,0.5f,1);//�������������

    		bfc=new BulletForControl(MySurfaceView.this,bullet,trExplo,-BULLET_OFFSET_X,BULLET_OFFSET_Y,BULLET_OFFSET_Z,VX,0.0f,0.0f);
    		alBFC.add(bfc);//�����б���
    		bgt=new BulletGoThread(alBFC);
    		bgt.start();//�����߳�

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
