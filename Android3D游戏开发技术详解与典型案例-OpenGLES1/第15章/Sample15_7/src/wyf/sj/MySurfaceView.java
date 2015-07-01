package wyf.sj;
import java.io.IOException;
import java.io.InputStream;
import java.util.*;
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
import android.view.MotionEvent;
import static wyf.sj.Constant.*;
public class MySurfaceView extends GLSurfaceView{

	SceneRenderer mRenderer;//������Ⱦ��
	float cx=0;//�����xλ��
	float cy=1;//�����yλ��
	float cz=0;//�����zλ��
	
	float tx;////Ŀ���xλ��
	float ty;//Ŀ���yλ��
	float tz;//Ŀ���zλ��
	float left;//�ӽǵ�ֵ
	float right;
	float top;
	float bottom;
	float near;
	float far;
	float cameraAlpha=70;//������Ƕ�
	
	{
		tx=(float)(cx-CAMERA_DISTANCE*Math.sin(Math.toRadians(cameraAlpha)));
		ty=cy;
		tz=(float)(cz-CAMERA_DISTANCE*Math.cos(Math.toRadians(cameraAlpha)));
	}
	
	
	ArrayList<BNShape> alBN;//�����б�
	ArrayList<Float> alDistance;//��������ľ���
	
	
	public MySurfaceView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
        alBN=new ArrayList<BNShape>();
        alDistance=new ArrayList<Float>();
	}
	@Override
	public boolean onTouchEvent(MotionEvent e)
	{
		float y = e.getY();
        float x = e.getX();
        switch(e.getAction())
        {
        	case MotionEvent.ACTION_DOWN:
        		alDistance.clear();//����б�
        		float bodyDistance=Float.POSITIVE_INFINITY;//��¼�������
        		int bodyFlag=0;//��¼����ı�־λ
        		        		
        		for(int i=0;i<alBN.size();i++)
        		{ 
        			alBN.get(i).setHilight(false);
        			float minMax[]=alBN.get(i).findMinMax();//��ó����
        			float mid[]=alBN.get(i).findMid();//��ȡ���ĵ�λ��
        			float[] bPosition=RotateUtil.calculateABPosition
        			(
        					x, //����X����
        					y, //����Y����
        					MyActivity.screenWidth, //��Ļ���
        					MyActivity.screenHeight, //��Ļ����
        					left, //�ӽ�leftֵ
        					top, //�ӽ�topֵ
        					near, //�ӽ�nearֵ
        				    far,
        				    cameraAlpha,//������Ƕ�
        				    cx,
        				    cy,
        				    cz
        			);
        			float tempDistance=IsIntersectantUtil.isIntersectant
        			(
        					mid[0], mid[1], mid[2], //�������ĵ�λ��
        					minMax[0]/2, minMax[1]/2, minMax[2]/2, //�� �� ��
        					bPosition[0],bPosition[1],bPosition[2],//A��λ��
        					bPosition[3],bPosition[4],bPosition[5]//B��λ��   
        			);
        			alDistance.add(tempDistance);        			
        		}
        		for(int i=0;i<alDistance.size();i++)
        		{
        			float tempA=alDistance.get(i);
        			if(tempA<bodyDistance)
        			{
        					bodyDistance=tempA;//��¼��Сֵ
        					bodyFlag=i;//��¼��Сֵ����                					
        			}
        		}
        		
        		Log.d("bodyDistance",bodyDistance+""); 
        		
        		if(!Float.isInfinite(bodyDistance))
        		{
        			alBN.get(bodyFlag).setHilight(true);//���õ�����С�ķ���
        			Log.d("hi",bodyFlag+"|"+alBN.get(bodyFlag).getClass().toString());
        		}
        		break;
        		
        }
		
		return true;
	}
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent e)
	{
		if(keyCode==4)
		{
			return false;
		}
		switch(keyCode)
		{
		case 21://�����
			
			cameraAlpha+=5f;
			tx=(float)(cx-CAMERA_DISTANCE*Math.sin(Math.toRadians(cameraAlpha)));
			tz=(float)(cz-CAMERA_DISTANCE*Math.cos(Math.toRadians(cameraAlpha)));
			break;
		case 22://���Ҽ�
			cameraAlpha-=5f;
			tx=(float)(cx-CAMERA_DISTANCE*Math.sin(Math.toRadians(cameraAlpha)));
			tz=(float)(cz-CAMERA_DISTANCE*Math.cos(Math.toRadians(cameraAlpha)));
			break;
			
		}
		
		return true;
	}
	private class SceneRenderer implements GLSurfaceView.Renderer
	{

		int cubeId;//����������ID
		int textureId;//����
		int textureZId;//��������ID
		BNShape bnShape;//������״
		//Cube cube;//��������
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
            for(int i=0;i<alBN.size();i++)
            {
            	gl.glPushMatrix();
            	alBN.get(i).drawSelf(gl);
            	gl.glPopMatrix();
            }
           
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
            left=right=ratio*0.5f;
            top=bottom=0.5f;
            near=1;
            far=100;
            //���ô˷����������͸��ͶӰ����
            gl.glFrustumf(-left,right,-bottom,top, near, far);
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
    		
    		cubeId=initTexture(gl,R.drawable.stone);//��ʼ������������ID
    		textureId=initTexture(gl,R.drawable.basketball);//��ʼ������ID
    		textureZId=initTexture(gl,R.drawable.robot);
    		
    		bnShape=new Cube(cubeId,CUBE_X,CUBE_Y,CUBE_Z,-10f,0f,-4.0f);//�������������
    		alBN.add(bnShape);
    		bnShape=new Ball(BALL_R,textureId,-5f,0,1.0f);//������
    		alBN.add(bnShape);
    		bnShape=new ZhuiTi(textureZId,ZHUITI_X,ZHUITI_Y,ZHUITI_Z,-10f,0f,1.0f);//��������
    		alBN.add(bnShape);
    		bnShape=new Cube(cubeId,CUBE_X,CUBE_Y,CUBE_Z,-10f,0f,4.0f);
    		//new Cylinder(cubeId,CYLINDER_LENGTH,CYLINDER_CIRCLE_RADIUS,CYLINDER_DEGREE_SPAN,CYLINDER_COL,-10f,0f,4.0f);//����Բ����
    		alBN.add(bnShape);
    		bnShape=new ZhuiTi(textureZId,ZHUITI_X,ZHUITI_Y,ZHUITI_Z,10f,0f,1.0f);//��������
    		alBN.add(bnShape);
    		bnShape=new Cube(cubeId,CUBE_X,CUBE_Y,CUBE_Z,10f,0f,-4.0f);//�������������
    		alBN.add(bnShape);
    		bnShape=new Ball(BALL_R,textureId,5f,0,1.0f);//������
    		alBN.add(bnShape);
    		
    		bnShape=new Ball(BALL_R,textureId,-5f,0,1.0f);//������
    		alBN.add(bnShape);
    		bnShape=new ZhuiTi(textureZId,ZHUITI_X,ZHUITI_Y,ZHUITI_Z,8f,0f,1.0f);//��������
    		alBN.add(bnShape);
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
