package wyf.sj;
import java.io.IOException;
import java.io.InputStream;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.opengles.GL11;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.GLUtils;
import android.view.KeyEvent;
import static wyf.sj.Constant.*;

public class MySurfaceView extends GLSurfaceView {

	static float direction=DIRECTION_INI;//���߷���
    static float cx;//�����x����
    static float cy;//�����y����
    static float cz;//�����z����
    
    static float tx;//�۲�Ŀ���x����  
    static float ty;//�۲�Ŀ���y����
    static float tz;//�۲�Ŀ���z����   
    
    private SceneRenderer mRenderer;//������Ⱦ��	
	
	public MySurfaceView(Context context) {
        super(context);
        Constant.initConstant(this.getResources());
        
        cx=CAMERA_INI_X;//�����x����
        cy=CAMERA_INI_Y;//�����y����
        cz=CAMERA_INI_Z;//�����z����
        
        tx=(float)(cx-Math.sin(direction)*DISTANCE);//�۲�Ŀ���x����  
        //ty=CAMERA_INI_Y+0.2f;//ƽ�ӹ۲�Ŀ���y����
        ty=CAMERA_INI_Y-2f;//��۲�Ŀ���y����
        tz=(float)(cz-Math.cos(direction)*DISTANCE);//�۲�Ŀ���z����   
        
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ        
    }
    
	@Override
    public boolean onKeyDown(int keyCode, KeyEvent e)
    { 
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
		int grassTextureId;//�������������ID
		int waterTextureId;//ˮ�����������ID
		LandForm landform;//����
		Water[] water=new Water[16];//ˮ��
		int currentWaterIndex;//��ǰˮ��֡����
		
        public void onDrawFrame(GL10 gl) {            
        	//����ƽ����ɫ
            gl.glShadeModel(GL10.GL_SMOOTH);            
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
            
            //���Ƶײ��������
            landform.drawSelf(gl);
            water[currentWaterIndex].drawSelf(gl);
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            //�����Ӵ���С��λ�� 
        	gl.glViewport(0, 0, width, height);
        	//���õ�ǰ����ΪͶӰ����
            gl.glMatrixMode(GL10.GL_PROJECTION);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();
            //����͸��ͶӰ�ı���
            float ratio = (float) width / height;
            //���ô˷����������͸��ͶӰ����
            gl.glFrustumf(-ratio*0.7f, ratio*0.7f, -0.7f*0.7f, 1.3f*0.7f, 1, 400);   
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            //�رտ����� 
        	gl.glDisable(GL10.GL_DITHER);
        	//�����ض�Hint��Ŀ��ģʽ������Ϊ����Ϊʹ�ÿ���ģʽ
            gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT,GL10.GL_FASTEST);
            //����Ϊ�򿪱������
    		gl.glEnable(GL10.GL_CULL_FACE);
    		//�������   
            gl.glEnable(GL10.GL_BLEND); 
            //����Դ���������Ŀ��������
            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
            //������Ļ����ɫ��ɫRGBA
            gl.glClearColor(0,0,0,0);           
            //������Ȳ���
            gl.glEnable(GL10.GL_DEPTH_TEST);                
            //��ʼ������
            grassTextureId=initTexture(gl,R.drawable.grass);  
            waterTextureId=initTexture(gl,R.drawable.water); 
            //��������
            landform=
            	new LandForm(grassTextureId,yArray,yArray.length-1,yArray[0].length-1);
            
            for(int i=0;i<water.length;i++)
            {
            	water[i]=new Water
            	(
            			waterTextureId,
            			Math.PI*2*i/water.length,
            			8,
            			8,
            			yArray.length/8
            	);
            }
            
            //����һ���̶߳�̬�л�֡
            new Thread()
            {
            	@Override
            	public void run()
            	{
            		while(true)
            		{
            			currentWaterIndex=(currentWaterIndex+1)%water.length;            		
	            		try {
							Thread.sleep(100);
						} catch (InterruptedException e) {
							e.printStackTrace(); 
						}
            		}
            		
            	}
            }.start();
        }
    }
	
	//��ʼ������
	public int initTexture(GL10 gl,int drawableId)//textureId
	{
		//��������ID
		int[] textures = new int[1];
		gl.glGenTextures(1, textures, 0);    
		int currTextureId=textures[0];    
		gl.glBindTexture(GL10.GL_TEXTURE_2D, currTextureId);
		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER, GL10.GL_NEAREST);
		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MAG_FILTER, GL10.GL_LINEAR);
//		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER,GL10.GL_LINEAR_MIPMAP_NEAREST);//mipmap����
//      gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_MAG_FILTER,GL10.GL_LINEAR_MIPMAP_LINEAR);
//      ((GL11)gl).glTexParameterf(GL10.GL_TEXTURE_2D, GL11.GL_GENERATE_MIPMAP, GL10.GL_TRUE);
		
		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S,GL10.GL_CLAMP_TO_EDGE);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T,GL10.GL_CLAMP_TO_EDGE);
//        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S, GL10.GL_REPEAT);//�����ظ�ճ��
//        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T, GL10.GL_REPEAT);
        
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
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmapTmp, 0);
        bitmapTmp.recycle(); 
        
        return currTextureId;
	}
}
