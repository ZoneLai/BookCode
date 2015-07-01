package wyf.jsc.rtb;
import static wyf.jsc.rtb.Constant.*;
import java.io.IOException;
import java.io.InputStream;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.GLUtils;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

public class MySurfaceView extends GLSurfaceView {

    private SceneRenderer mRenderer;//������Ⱦ��
    //Cube cubeKong;
    float tX;//Ŀ���ĳ�ʼ���ꡣ
    float tZ;
    float tY;
    float cX;
    float cY;
    float cZ;
    int times;
    MainActivity gkd=(MainActivity)this.getContext();
    boolean turnleft=true;
	boolean turnright=false;
	public MySurfaceView(Context context) {
        super(context);
        tX=-tempFlag+(INIT_I+1)*UNIT_SIZE-0.5f;
        tZ=-tempFlag+(INIT_J+1)*UNIT_SIZE-1.0f;
        cY=9.5f;
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
        
    }
	@Override
	public boolean onTouchEvent(MotionEvent e)
	{
		switch(e.getAction())
		{
		case MotionEvent.ACTION_DOWN:
			previousX=e.getX();
			previousY=e.getY();
			break;
		case MotionEvent.ACTION_UP:
			laterX=e.getX();
			laterY=e.getY();
			float dx=laterX-previousX;
			float dy=laterY-previousY;
			float r=(float)(Math.sqrt(dx*dx+dy*dy));
			if(dy>0&&dx!=0)
			{
				float tempA=(float)Math.toDegrees(Math.acos(dx/r));
				if(tempA>=0&&tempA<45)
				{//right
					mRenderer.cube.keyPress(Constant.RIGHT_KEY);
	    			tX=-tempFlag+(targetX+1)*UNIT_SIZE-0.5f; 	    			
	    			requestRender();
	    			soundAndTimes();
				}
				if(tempA>=45&&tempA<135)
				{//down
					mRenderer.cube.keyPress(Constant.DOWN_KEY);
	    			tZ=-tempFlag+(targetZ+1)*UNIT_SIZE-1.0f;
	    			requestRender();
	    			soundAndTimes();
				}
				if(tempA>=135&&tempA<180)
				{//left
					mRenderer.cube.keyPress(Constant.LEFT_KEY);
	    			tX=-tempFlag+(targetX+1)*UNIT_SIZE-0.5f;
	    			requestRender();
	    			soundAndTimes();
				}
			}
			if(dy<0&&dx!=0)
			{
				float tempB=(float)Math.toDegrees(Math.asin(dy/r));
				if(dx>0)
				{
					if(tempB>=-45&&tempB<0)
					{//right
						mRenderer.cube.keyPress(Constant.RIGHT_KEY);
		    			tX=-tempFlag+(targetX+1)*UNIT_SIZE-0.5f; 	    			
		    			requestRender();
		    			soundAndTimes();
					}
					if(tempB>=-90&&tempB<-45)
					{//up
						mRenderer.cube.keyPress(Constant.UP_KEY);
		    			tZ=-tempFlag+(targetZ+1)*UNIT_SIZE-1.0f;
		    			requestRender();
		    			soundAndTimes();
					}
				}
				if(dx<0)
				{
					tempB=tempB-90;
					if(tempB>=-135&&tempB<-90)
					{//left
						mRenderer.cube.keyPress(Constant.LEFT_KEY);
		    			tX=-tempFlag+(targetX+1)*UNIT_SIZE-0.5f;
		    			requestRender();
		    			soundAndTimes();
					}
					if(tempB>=-180&&tempB<-135)
					{//up
						mRenderer.cube.keyPress(Constant.UP_KEY);
		    			tZ=-tempFlag+(targetZ+1)*UNIT_SIZE-1.0f;
		    			requestRender();
		    			soundAndTimes();
					}
				}
			}
			if(dx==0)
			{
				if(dy>0)
				{//down
					mRenderer.cube.keyPress(Constant.DOWN_KEY);
	    			tZ=-tempFlag+(targetZ+1)*UNIT_SIZE-1.0f;
	    			requestRender();
	    			soundAndTimes();
				}
				if(dy<0)
				{//up
					mRenderer.cube.keyPress(Constant.UP_KEY);
	    			tZ=-tempFlag+(targetZ+1)*UNIT_SIZE-1.0f;
	    			requestRender();
	    			soundAndTimes();
				}
			}
			if(dy==0)
			{
				if(dx>0)
				{//right
					mRenderer.cube.keyPress(Constant.RIGHT_KEY);
	    			tX=-tempFlag+(targetX+1)*UNIT_SIZE-0.5f; 	    			
	    			requestRender();
	    			soundAndTimes();
				}
				if(dx<0)
				{//left
					mRenderer.cube.keyPress(Constant.LEFT_KEY);
	    			tX=-tempFlag+(targetX+1)*UNIT_SIZE-0.5f;
	    			requestRender();
	    			soundAndTimes();
				}
			}
			break;		
		}
		if(winFlag||loseFlag)
		{
			gkd.toAnotherView(ENTER_WINVIEW);
			winFlag=false;
			loseFlag=false;
		}
			
		return true;
	}
	@Override
	public boolean onKeyUp(int keyCode, KeyEvent e)
	{//��̧���¼��ص�����
		if(keyCode==4){
			return false;//̧��return��
		}		
		if(anmiFlag==true)
		{
			return true;
		}
		anmiFlag=true;
		
		switch(keyCode)
    	{
			
    		case 19://up
    			mRenderer.cube.keyPress(Constant.UP_KEY);
    			tZ=-tempFlag+(targetZ+1)*UNIT_SIZE-1.0f;
    		break;
    		case 20://down
    			mRenderer.cube.keyPress(Constant.DOWN_KEY);
    			tZ=-tempFlag+(targetZ+1)*UNIT_SIZE-1.0f;
        	break;
    		case 21://left
    			mRenderer.cube.keyPress(Constant.LEFT_KEY);
    			tX=-tempFlag+(targetX+1)*UNIT_SIZE-0.5f;
    	    break;
    		case 22://right
    			mRenderer.cube.keyPress(Constant.RIGHT_KEY);
    			tX=-tempFlag+(targetX+1)*UNIT_SIZE-0.5f;    			
	        break;
    	} 	
		gkd.playSound(1, 0);//���ŷ�ľ�������
		closeSound();
		dropSound();
		times++;
		if(winFlag||loseFlag)
		{
			gkd.toAnotherView(ENTER_WINVIEW);
			winFlag=false;
			loseFlag=false;
		}
		return true;
	}

	private class SceneRenderer implements GLSurfaceView.Renderer 
    {   
		//��������Id
		int cubeSmallTexId;//������С������Id
		int cubeBigTexId;//�������������Id
		int floorId;//�ذ�����Id
		int iconId;//ͼ�������ID
		int headId;//ͷ����Id
		int numberId;//����Id
		int cloudId;//���Ƶ�Id
		int backId;//����ͼId
		int levelId;//����Id
		
		//����ͼ��
		Cube cube;
		FloorGroup floorGroup;//���Ƶذ�Ķ���
    	TextureRect icon;//ͼ�����
		TextureRect head;//ͷͼ��
		TextureRect backGround;
		TextureRect level;//�ؿ���ͼƬ
		BallCloud cloud;//��
		//TextureRect cloud;
    	Number number;//��Ŀͼ��
    	
		 
    	public SceneRenderer()
    	{
    			
    	}
    	
        public void onDrawFrame(GL10 gl) {
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
            gl.glPushMatrix();
            gl.glTranslatef(0, 0, -25);
            backGround.drawSelf(gl);
            gl.glPopMatrix();
            GLU.gluLookAt
			(
					gl,
					-tempFlag+(targetX+1)*UNIT_SIZE+1.5f,
					9f, //�۲������
					10,
					tX,//Ŀ�������
					UNIT_HIGHT*6,
					tZ,
					0,
					1,
					0
			);
            gl.glPushMatrix();
            gl.glTranslatef(0, 0, -2);
            floorGroup.drawSelf(gl);
            gl.glTranslatef(-tempFlag+(INIT_I+1)*UNIT_SIZE-0.5f, UNIT_HIGHT*6,-tempFlag/2+(INIT_J+1)*UNIT_SIZE-0.5f);
            cube.drawSelf(gl);
            gl.glPopMatrix();  
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            gl.glLoadIdentity();
            //�������   
            gl.glEnable(GL10.GL_BLEND); 
            //����Դ���������Ŀ��������
            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);          
            gl.glTranslatef(0,8.475f*ratio, -15*ratio);
            head.drawSelf(gl);//����ͷ
            gl.glTranslatef(-4.5f*ratio, -0.15f*ratio, 0.015f*ratio);
            icon.drawSelf(gl);//���ƾ���ͼ��
            gl.glTranslatef(1.5f*ratio, 0.0f, 0.015f*ratio);
            number.drawSelf(gl);//����ת������
            gl.glTranslatef(6.75f*ratio, 0, 0);
            level.drawSelf(gl);//����L
            //��ֹ���   
            gl.glDisable(GL10.GL_BLEND);
            gl.glPushMatrix();
            gl.glEnable(GL10.GL_BLEND);
            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA); 
            gl.glTranslatef(-1.2f, -5.5f, -10.0f);
            cloud.drawSelf(gl);//�����Ʋ�  
            gl.glDisable(GL10.GL_BLEND);
            gl.glPopMatrix();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            //�����Ӵ���С��λ�� 
        	gl.glViewport(0, 0, width, height);
        	//���õ�ǰ����ΪͶӰ����
            gl.glMatrixMode(GL10.GL_PROJECTION);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();
            //����͸��ͶӰ�ı���
            ratio = (float) width / height;
            backWidth=width;
            backHeight=height;
            Log.d("backWidth"+backWidth, "backHeight"+backHeight);
            //���ô˷����������͸��ͶӰ����
           gl.glFrustumf(-ratio, ratio, -1, 1, 1.67f, 100);
           number=new Number(numberId,MySurfaceView.this);
           icon=new TextureRect
           (
        		ratio*0.45f,ratio*0.45f,
           		iconId,
           		new float[]
                   {
           				0,0,0,1f,1,1f,
           				1,1f,1,0,0,0	
           		}
           );
           head=new TextureRect
           (
           		ratio*12,ratio*0.75f,
           		headId,
           		new float[]
                   {
           				1,0,0,0,0,1,
           				0,1,1,1,1,0
           		   }
           );
           backGround=new TextureRect
           (
        		ratio*15,ratio*24,
           		backId,
           		new float[]
           	    {
           				0.625f,0,0,0,0,0.93f,
                   		0,0.93f,0.625f,0.93f,0.625f,0 
           	    }
           );
           level=new TextureRect
           (
        		ratio*0.75f,ratio*0.75f,
        		levelId,
           		new float[]
           		{
           				1,0,0,0,0,1,
               		    0,1,1,1,1,0
           		}
           );
           cloud=new BallCloud(15000*ratio,cloudId);
         //ת���Ʋ�
           new Thread()
           {
           	public void run()
           	{
           		try
           		{
           			sleep(40);
           		}catch(Exception e)
           		{
           			e.printStackTrace();
           		}
           		while(true)
           		{
           			
           			cloud.mAngleY+=0.1f;
           			try
           			{
           			sleep(40);	
           			}catch(Exception e)
           			{
           				e.printStackTrace();
           			}
           		}
           	}
           }.start();
          
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            //�رտ����� 
        	gl.glDisable(GL10.GL_DITHER);
        	//�����ض�Hint��Ŀ��ģʽ������Ϊ����Ϊʹ�ÿ���ģʽ
            gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT,GL10.GL_FASTEST);
            //������Ļ����ɫ��ɫRGBA
            gl.glClearColor(0,0,0,0);
        	//����Ϊ�򿪱������
            gl.glEnable(GL10.GL_CULL_FACE);
            //������Ȳ���
            gl.glEnable(GL10.GL_DEPTH_TEST);               
            //��ʼ������
            cubeSmallTexId=initTexture(gl,R.drawable.cubesmall); 
            cubeBigTexId=initTexture(gl,R.drawable.cubebig); 
            floorId=initTexture(gl,R.drawable.floor);
            iconId=initTexture(gl,R.drawable.cubesmall);
            headId=initTexture(gl,R.drawable.head);
            numberId=initTexture(gl,R.drawable.number);
            cloudId=initTexture(gl,R.drawable.cloud);
            backId=initTexture(gl,R.drawable.back);
            levelId=initTexture(gl,R.drawable.l);            
            cube=new Cube
            (
            		0.5f,cubeSmallTexId,cubeBigTexId,
            		new float[]
            			{
            				0,0,0,1f,1,1f,
            				1,1f,1,0,0,0
            	        }
            );
            floorGroup=new FloorGroup(1,floorId);
            Log.d("backWidthC"+backWidth, "backHeightC"+backHeight);           
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
		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER,GL10.GL_NEAREST);
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
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmapTmp, 0);
        bitmapTmp.recycle(); 
        
        return currTextureId;
	}
	
	public void closeSound()
	{
		if(winSound)
		{
			gkd.mpBack.stop();
			gkd.playSound(3, 0);
			winSound=false;
		}
	}
	public void dropSound()
	{
		if(dropFlag)
		{
			gkd.mpBack.stop();
			gkd.playSound(2, 0);
			dropFlag=false;
		}
	}
	public void soundAndTimes()
	{
		gkd.playSound(1, 0);//���ŷ�ľ�������
	    closeSound();
	    dropSound();
	    times++;
	}
}

