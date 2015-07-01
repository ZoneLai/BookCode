package wyf.jsl.lb;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.GLUtils;
import android.util.Log;
import android.view.KeyEvent;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.opengles.GL11;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import static wyf.jsl.lb.Constant.*;

class GLGameView extends GLSurfaceView 
{		
	static float direction=DIRECTION_INI;//���߷���
	public float lightAngle=90;//�Ƶĵ�ǰ�Ƕ�
	public float xiaoxingkongAngle=0;//С�ǿճ�ʼ�Ƕ�
	public float daxingkongAngle=0;//���ǿճ�ʼ�Ƕ�
	public float moonAngle=-90;//������XZƽ��ĳ�ʼ�Ƕ�
    static float cx;//�����x����
    static float cy;//�����y����
    static float cz;//�����z����  
    
    static float tx;//�۲�Ŀ���x����   
    static float ty;//�۲�Ŀ���y����
    static float tz;//�۲�Ŀ���z����   
    
    SceneRenderer mRenderer;//������Ⱦ��	
    
    ThreadBullet bgt;//��ʱ�ƶ��ڵ����߳�
    ThreadWaterTank gtwt;//����ˮ��̹���˶����߳�
    ThreadLandTank gtlt;//����½��̹���˶����߳�
    ThreadProductWaterTank tpwt;//ˮ��̹�������߳�
    
    ThreadCamera ct;//������ƶ��߳�
    ThreadLight tl;//��Դ��ת�߳�
    ThreadXingkong xk;//�ǿ���ת�߳�
    ThreadMoon tm;//����ת�߳�
    
    Activity_GL_Demo father;
    
    boolean flagFinish=false;//��Ϸ���������������תʱ�����̲��ɿأ���ת������ʹ���ָ̻��ɿ��ơ�flagFinishΪ����Ʊ�׼λ
        
    public ArrayList<LogicalBullet> bulletList=new ArrayList<LogicalBullet>();//�ڵ��б�
    public ArrayList<LogicalWaterTank> waterTankList=new ArrayList<LogicalWaterTank>();//ˮ��̹���б�
    public ArrayList<LogicalLandTank> landTankList=new ArrayList<LogicalLandTank>();//½��̹���б� 
	
	public GLGameView(Activity_GL_Demo father) 
	{
        super(father);
        this.father=father;
        
        Constant.initConstant(this.getResources());
 
        //�������������ThreadCamera.java����
        
        tx=FORT_X;//�۲�Ŀ���x����  
        ty=FORT_Y;//ƽ�ӹ۲�Ŀ���y����
        tz=FORT_Z;//�۲�Ŀ���z����   
      
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ        
        
        bgt=new ThreadBullet(bulletList);//������ʱ�ƶ��ڵ����߳�
        gtwt=new ThreadWaterTank(waterTankList);//������ʱ�ƶ�ˮ��̹�˵��߳�
        gtlt=new ThreadLandTank(landTankList);//������ʱ�ƶ�½��̹�˵��߳�  
        tpwt=new ThreadProductWaterTank(GLGameView.this);//����ˮ��̹�������߳�
        tl=new ThreadLight(GLGameView.this);//������Դ��ת�߳�
        xk=new ThreadXingkong(GLGameView.this);//�����ǿ���ת�߳�
        tm=new ThreadMoon(GLGameView.this);//��������ת�߳�
    }
    
	@Override
    public boolean onKeyDown(int keyCode, KeyEvent e)
    { 
		if(flagFinish==false)//��Ϸ���������������תʱ�����̲��ɿأ���ת������ʹ���ָ̻��ɿ��ơ���flagFinishΪfalseʱ�����̲��ɿأ���ΪTrueʱ���ָ��ɿء�
		{
			return true;
		}
		
		if(keyCode==4){
			//�ر��߳�
			bgt.flag=false;//�ر��ܵ��߳�
			gtlt.flag=false;//�ر�½��̹���߳�
			gtwt.flag=false;//�ر�ˮ��̹���߳�
			tl.flag=false;//�رչ�Դ��ת�߳�
			tm.flag=false;//�ر�����ת�߳�
			xk.flag=false;//�ر��ǿ���ת�߳�
			//SOUND_FLAG=false;//�ر�����
			//BACK_SOUND_FLAG=false;
			inGame=false;
			father.mpBack.pause();
			Count=0;//��ջ���̹���� 
			 
			father.hd.sendEmptyMessage(GAME_MENU);
			return true; 
		}	
		else
		{
			switch(keyCode)
	    	{
	    		case 19://up
	    			if(mRenderer.ffd.angleElevation<30)
	    			{//���ڹ�����С��60����̧���ڹ�
	    				mRenderer.ffd.angleElevation=mRenderer.ffd.angleElevation+DEGREE_SPAN;
	    			}    			
	    		break;
	    		case 20://down
	    			if(mRenderer.ffd.angleElevation>-10)
	    			{//���ڹ����Ǵ���10�������ڹ�
	    				mRenderer.ffd.angleElevation=mRenderer.ffd.angleElevation-DEGREE_SPAN;
	    			}    			
	        	break;
	    		case 21://left
	    			mRenderer.ffd.angleDirection=mRenderer.ffd.angleDirection+DEGREE_SPAN;//��̨������ת
	    	    break;
	    		case 22://right
	    			mRenderer.ffd.angleDirection=mRenderer.ffd.angleDirection-DEGREE_SPAN;//��̨������ת
		        break;
	    		case 62://�ո��
	    			mRenderer.ffd.fire();//�����ڵ�
	    	    break;
	    	} 		
	    	
	    	 //��̨ת�������¼������������
	    	 cx=FORT_X+DISTANCE*(float)Math.sin(Math.toRadians(mRenderer.ffd.angleDirection));
	    	 cz=FORT_Z+DISTANCE*(float)Math.cos(Math.toRadians(mRenderer.ffd.angleDirection));    	
	  	     		
	    	return true;
		}
    }

	class SceneRenderer implements GLSurfaceView.Renderer 
    {
		int grassTextureId;//�������������ID	
		int cirLongTextureId;//�ڹܵ�������
		int cirShortTextureId;//�ڹܶ���ͲԲ��������				
		int bulletTextureId;//�ڵ�����
		int[] exploTextureId=new int[6];//�ڵ�ײ��½�صı�ը������
		int[] shootTextureId=new int[6];//�ڵ�����̹�˵ı�ը������
		int waterTextureId;//ˮ�����������ID
		int micaiTextureId;//�Բ�����
		int metalTextureId;//��������
		int wheelTextureId;//��������
		int metalTextureId2;//��Ͳ��������
		int circleTextureId;//Բ������
		int zhunxingTextureId;//׼������
		int scoreTextureId;//�Ʒ�����
		int fenTextureId;//����̹������
		int stoneWallTextureId;//ʯǽ����
		int moonTextureId;//��������
		
		DrawLandForm landform;//����
		PackageCannon ffd;//��̨
		DrawBall btbv;//���ڻ����ڵ�����
		DrawTextureRect[] trExplo=new DrawTextureRect[6];//��ը����	
		DrawTextureRect[] shootExplo=new DrawTextureRect[6];//���ж���
		DrawWater[] water=new DrawWater[16];//ˮ��
		int currentWaterIndex;//��ǰˮ��֡����												
		PackageWaterTank wt;//���ڻ���ˮ��̹�˵�̹��		
		PackageLandTank lt;//���ڻ���½��̹�˵�̹��
		Score score;//�Ʒ��Ʊ��
		DrawTextureRect shootTank;//����̹��
		PackageLighthouse lighthouse;//����
		PackageCannonEmplacement cannonEmplacement;//���ڵ���
    	DrawCelestial celestialSmall;//С�����ǿհ���
    	DrawCelestial celestialBig;//�������ǿհ���
    	DrawLightBall moon;//����
		
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
	            
	            //�����ǿ�
	            gl.glPushMatrix(); 
	            gl.glTranslatef(0, 0f, 0.0f);  
	            gl.glRotatef(xiaoxingkongAngle, 0, 1, 0); 
	            celestialSmall.drawSelf(gl);
	            gl.glPopMatrix(); 
	            
	            gl.glPushMatrix();
	            gl.glTranslatef(0, -8.0f, 0.0f);  
	            gl.glRotatef(daxingkongAngle, 0, 1, 0);
	            celestialBig.drawSelf(gl);
	            gl.glPopMatrix(); 
	            
	            //��������
	            gl.glPushMatrix();
	            float moonx=(float)(Math.cos(Math.toRadians(MOON_LIGHT_ANGLE)));
	            float moony=0;
	        	float moonz=(float)(Math.sin(Math.toRadians(MOON_LIGHT_ANGLE)));
	            float[] positionParamsMoon={moonx,moony,moonz,0};//����0��ʾʹ�ö����
	            gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_POSITION, positionParamsMoon,0);
	            initMaterial(gl);
	            gl.glTranslatef(
	            		//LIGHT_X,LIGHT_Y+60f,LIGHT_Z  
	            		(float)(MOON_R*Math.cos(Math.toRadians(MOON_ANGLE_Y))*Math.cos(Math.toRadians(moonAngle))), 
	            		(float)(MOON_R*Math.sin(Math.toRadians(MOON_ANGLE_Y))), 
	            		(float)(MOON_R*Math.cos(Math.toRadians(MOON_ANGLE_Y))*Math.sin(Math.toRadians(moonAngle)))
	            		);
	            initLight0(gl);//���� 
	            moon.drawSelf(gl); 
	            closeLight0(gl);//�ص�  
	            gl.glPopMatrix();  
	             
	            //���Ƶ���
	            gl.glPushMatrix();          
	            //�趨��Դ��λ��
	            float lx=(float)(Math.cos(Math.toRadians(lightAngle)));
	            float ly=0;
	        	float lz=(float)(Math.sin(Math.toRadians(lightAngle)));
	            float[] positionParamsRed={lx,ly,lz,0};//����0��ʾʹ�ö����
	            gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_POSITION, positionParamsRed,0);
	            gl.glShadeModel(GL10.GL_FLAT);//�ر�ƽ��
	            gl.glTranslatef(LIGHT_X, LIGHT_Y, LIGHT_Z);
	            initLight(gl);//����
	            lighthouse.onDraw(gl);
	            closeLight(gl);//�ص�
	            gl.glShadeModel(GL10.GL_SMOOTH); //��ƽ��
	            gl.glPopMatrix();
	            
	            //����ˮ 
	            gl.glPushMatrix();
	            gl.glEnable(GL10.GL_BLEND);//�������
	            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
	            gl.glTranslatef(0,WATER_HEIGHT, 0);
	            gl.glRotatef(90, 0, 1, 0);
	            water[currentWaterIndex].drawSelf(gl);
	            gl.glDisable(GL10.GL_BLEND);//������� 
	            gl.glPopMatrix();         

            try
            {
            	//�����ڵ�
                for(LogicalBullet b:bulletList)
                {
                	b.drawSelf(gl);
                }
            }
            catch(Exception e)
            {
            	e.printStackTrace();
            }
            
            //����ˮ��̹��
            try{
            	for(LogicalWaterTank lwt:waterTankList)
                {
                    //����ˮ��̹��λ�ö�Ӧ��ǰˮ��֡�ĸ߶��Ŷ�ֵ 
                    //����˼��Ϊ˯���ܿ�ȶ�Ӧˮ���ܹ��Ļ��ȿ�ȣ����ݴ���x������԰������������ǰ����
                    //���㵱ǰ����ʱ����Ҫ���Ǵ���x���꣬��Ҫ����ˮ�浱ǰ֡�ı��
                    double waterTankRadis=WATER_RADIS*(lwt.currentX+WATER_UNIT_SIZE*WCOLS/2)/(WCOLS*WATER_UNIT_SIZE);
                    waterTankRadis=Math.PI*2*currentWaterIndex/WATER_FRAMES+waterTankRadis;
                    float hd=(float)(HIGH_DYNAMIC*Math.sin(waterTankRadis));
                	
                    gl.glPushMatrix();
                    gl.glTranslatef(0, hd, 0);			
                	lwt.drawSelf(gl);
                	gl.glPopMatrix();
                }
            }catch(Exception e){
            	e.printStackTrace();
            }
                       
            //����½��̹��
            try{
            	 for(LogicalLandTank llt:landTankList)
                 {
                 	gl.glPushMatrix();
                 	llt.drawSelf(gl);
                 	gl.glPopMatrix();
                 }
            }catch(Exception e){
            	e.printStackTrace();
            }     
            
            //������̨
            gl.glPushMatrix();
            gl.glTranslatef(FORT_X, CANNON_FORT_Y, CANNON_FORT_Z);
            cannonEmplacement.onDraw(gl);
            gl.glPopMatrix();
            
            //���ƴ���
            gl.glPushMatrix();
            gl.glTranslatef(FORT_X, FORT_Y, FORT_Z);
            ffd.drawSelf(gl);
            gl.glPopMatrix();
            
            
            //���ƼƷ��Ʊ��
            //�ָ��ɳ�ʼ״̬���ƾ�̬����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            gl.glLoadIdentity();
            gl.glEnable(GL10.GL_BLEND);//�������
            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
            gl.glTranslatef(-1.5f, 1.6f, -ICON_DIS);
            score.drawSelf(gl);
            gl.glTranslatef(-0.3f, 0, 0);
            shootTank.drawSelf(gl);
            gl.glDisable(GL10.GL_BLEND);//�رջ��            
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
            gl.glFrustumf(-ratio*0.7f, ratio*0.7f, -0.7f*0.7f, 1.3f*0.7f, 1.6f, 400);   
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
            cirShortTextureId=initTexture(gl,R.drawable.cirshort); 
            cirLongTextureId=initTexture(gl,R.drawable.cirlong);  
            bulletTextureId=initTexture(gl,R.drawable.bullet);  
            exploTextureId[0]=initTexture(gl,R.drawable.explode1);  
            exploTextureId[1]=initTexture(gl,R.drawable.explode2);  
            exploTextureId[2]=initTexture(gl,R.drawable.explode3);  
            exploTextureId[3]=initTexture(gl,R.drawable.explode4);  
            exploTextureId[4]=initTexture(gl,R.drawable.explode5);  
            exploTextureId[5]=initTexture(gl,R.drawable.explode6);   
            shootTextureId[0]=initTexture(gl,R.drawable.explode1);  
            shootTextureId[1]=initTexture(gl,R.drawable.explode2);  
            shootTextureId[2]=initTexture(gl,R.drawable.explode3);  
            shootTextureId[3]=initTexture(gl,R.drawable.explode4);  
            shootTextureId[4]=initTexture(gl,R.drawable.explode5);  
            shootTextureId[5]=initTexture(gl,R.drawable.explode6);
			micaiTextureId=initTexture(gl,R.drawable.micai);
			metalTextureId=initTexture(gl,R.drawable.jinshu3);
			metalTextureId2=initTexture(gl,R.drawable.jinshu4);
			wheelTextureId=initTexture(gl,R.drawable.wheel);
			circleTextureId=initTexture(gl,R.drawable.round);
            waterTextureId=initTexture(gl,R.drawable.water); 
            zhunxingTextureId=initTexture(gl,R.drawable.zhunxing);
            scoreTextureId=initTexture(gl,R.drawable.number2);
            fenTextureId=initTexture(gl,R.drawable.jifen);
            stoneWallTextureId=initTexture(gl,R.drawable.wall);
            moonTextureId=initTexture(gl,R.drawable.moon);
            
            //��������  
            landform=
            	new DrawLandForm(grassTextureId,yArray,yArray.length-1,yArray[0].length-1);
            //ˮ��
            for(int i=0;i<water.length;i++)
            {
            	water[i]=new DrawWater
            	(
            			waterTextureId,
            			Math.PI*2*i/water.length,
            			WROWS,
            			WCOLS,
            			yArray.length/8
            	);
            }           
            //����һ���̶߳�̬�л�ˮ��֡
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
            //������̨
            ffd=new PackageCannon 
            (
            		cirLongTextureId,
            		cirShortTextureId, 
            		GLGameView.this  
            );
            
            //�������ڻ����ڵ�����
            btbv=new DrawBall(BULLET_SIZE,bulletTextureId,10) ;            
            
            //������ը�������֡
            trExplo[0]=new DrawTextureRect(exploTextureId[0],CIRCLE_R*LAND_BAOZHA,CIRCLE_R*LAND_BAOZHA);
            trExplo[1]=new DrawTextureRect(exploTextureId[1],CIRCLE_R*LAND_BAOZHA,CIRCLE_R*LAND_BAOZHA);
            trExplo[2]=new DrawTextureRect(exploTextureId[2],CIRCLE_R*LAND_BAOZHA,CIRCLE_R*LAND_BAOZHA);
            trExplo[3]=new DrawTextureRect(exploTextureId[3],CIRCLE_R*LAND_BAOZHA,CIRCLE_R*LAND_BAOZHA);
            trExplo[4]=new DrawTextureRect(exploTextureId[4],CIRCLE_R*LAND_BAOZHA,CIRCLE_R*LAND_BAOZHA);
            trExplo[5]=new DrawTextureRect(exploTextureId[5],CIRCLE_R*LAND_BAOZHA,CIRCLE_R*LAND_BAOZHA);
            
            shootExplo[0]=new DrawTextureRect(shootTextureId[0],CIRCLE_R*TANK_BAOZHA,CIRCLE_R*TANK_BAOZHA);
            shootExplo[1]=new DrawTextureRect(shootTextureId[0],CIRCLE_R*TANK_BAOZHA,CIRCLE_R*TANK_BAOZHA);
            shootExplo[2]=new DrawTextureRect(shootTextureId[0],CIRCLE_R*TANK_BAOZHA,CIRCLE_R*TANK_BAOZHA);
            shootExplo[3]=new DrawTextureRect(shootTextureId[0],CIRCLE_R*TANK_BAOZHA,CIRCLE_R*TANK_BAOZHA);
            shootExplo[4]=new DrawTextureRect(shootTextureId[0],CIRCLE_R*TANK_BAOZHA,CIRCLE_R*TANK_BAOZHA);
            shootExplo[5]=new DrawTextureRect(shootTextureId[0],CIRCLE_R*TANK_BAOZHA,CIRCLE_R*TANK_BAOZHA);
            
            //̹��-------��ˮ��̹����½ʱ��������½�����½��̹��
            wt=new PackageWaterTank(GLGameView.this);
            lt=new PackageLandTank(GLGameView.this);
            
            //�Ʒ��Ʊ��
            score=new Score(scoreTextureId,GLGameView.this);
            shootTank=new DrawTextureRect(fenTextureId,0.12f,0.12f);
 
            //����ˮ��̹�˻����߳�
            tpwt.start();
            //������˶��߳�
            ct=new ThreadCamera(GLGameView.this,father);
            ct.start();
            
            lighthouse=new PackageLighthouse();//��������
            cannonEmplacement=new PackageCannonEmplacement(GLGameView.this);//������̨
            //�����ǿ�
            celestialSmall=new DrawCelestial(0,0,1,200);
            celestialBig=new DrawCelestial(0,0,2,100);
            
            //��������
            moon=new DrawLightBall(MOON_SCALE,moonTextureId,12f);  
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
		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER,GL10.GL_LINEAR_MIPMAP_NEAREST);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_MAG_FILTER,GL10.GL_LINEAR_MIPMAP_LINEAR);
        ((GL11)gl).glTexParameterf(GL10.GL_TEXTURE_2D, GL11.GL_GENERATE_MIPMAP, GL10.GL_TRUE);
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
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmapTmp, 0);
        bitmapTmp.recycle(); 
        
        return currTextureId;
	}
	
	//��ʼ��1�ŵ�
	private void initLight(GL10 gl)
	{    
		gl.glEnable(GL10.GL_LIGHTING);//������� 
        gl.glEnable(GL10.GL_LIGHT1);//��1�ŵ�  
        
        //����������
        float[] ambientParams={0.25f,0.25f,0.25f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_AMBIENT, ambientParams,0);            
        
        //ɢ������� 
        float[] diffuseParams={0.8f,0.8f,0.8f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_DIFFUSE, diffuseParams,0); 
        
        //���������
        float[] specularParams={0.8f,0.8f,0.8f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_SPECULAR, specularParams,0); 
	}
	
	//��ʼ��0�ŵ�
	private void initLight0(GL10 gl)
	{    
		gl.glEnable(GL10.GL_LIGHTING);//������� 
        gl.glEnable(GL10.GL_LIGHT0);//��1�ŵ�   
        
        //����������
        float[] ambientParams={0f,0f,0f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_AMBIENT, ambientParams,0);            
        
        //ɢ������� 
        float[] diffuseParams={251f/255f,226f/255f,125f/255f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_DIFFUSE, diffuseParams,0); 
        
        //���������
        float[] specularParams={251f/255f,226f/255f,125f/255f,1.0f};//����� RGBA  
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_SPECULAR, specularParams,0); 
	}
	
	
	//�صƷ���
	private void closeLight0(GL10 gl)
	{
		gl.glDisable(GL10.GL_LIGHT0);
		gl.glDisable(GL10.GL_LIGHTING);
	}
	
	//�صƷ���
	private void closeLight(GL10 gl)
	{
		gl.glDisable(GL10.GL_LIGHT1);
		gl.glDisable(GL10.GL_LIGHTING);
	}
	
	//��ʼ����ɫ����
	private void initMaterial(GL10 gl)
	{
        //������Ϊ
        float ambientMaterial[] = {1f, 1f, 1, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_AMBIENT, ambientMaterial,0);
        //ɢ���
        float diffuseMaterial[] = {1f, 1f, 1f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_DIFFUSE, diffuseMaterial,0);
        //�߹����
        float specularMaterial[] = {1f, 1f, 1f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_SPECULAR, specularMaterial,0);
        gl.glMaterialf(GL10.GL_FRONT_AND_BACK, GL10.GL_SHININESS, 100.0f);
	}
}
