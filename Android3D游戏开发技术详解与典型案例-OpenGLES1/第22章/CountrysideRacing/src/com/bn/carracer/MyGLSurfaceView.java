package com.bn.carracer;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.GLUtils; 
import android.view.KeyEvent;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.opengles.GL11;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import static com.bn.carracer.Constant.*;
import static com.bn.carracer.Activity_GL_Racing.*;

public class MyGLSurfaceView extends GLSurfaceView {
	static Activity_GL_Racing activity;
    private SceneRenderer mRenderer;//������Ⱦ��
    
    static float carX;//����XYZ����
    static float carOldX;//����һ����X����
    static float carY; 
    static float carZ;    
    static float carAlpha=DIRECTION_INI;//���ĽǶȣ�0��Ϊz�Ḻ���򣬽Ƕ�Ϊ��Y������������ת    
    static float carAlphaRD=0;//�����Ŷ��Ƕ�ֵ
    static float carV;//���ĵ�ǰ�ٶ�
    static float carLightAngle=135;//������ƹ⵱ǰ�Ƕȡ�
    
    static boolean timeFlag=false;//��ʼ��¼ʱ���־λ��falseΪ����¼��trueΪ��ʼ��¼ʱ�䡣
    
    static boolean rsLoadFlag=false;//�������������������ر�־
    static boolean isBrake;//ɲ���б�־,���ڿ��Ƴ�β�ƵĿ���/�ر�
    static boolean viewFlag=true;//���ڿ��������ӽǣ�trueΪ�����˳��ӽǣ�falseΪ��һ�˳��ӽ�
    static boolean yibiaopanFlag=true;//�����շ��Ǳ��̡�
    static boolean mapFlag=true;//�����շ������ͼ��
    static boolean daojishiFlag=false;//���ڿ��Ƶ���ʱ���Ƶı�־λ 
    
    static int quanshu=0;//��¼��ʻȦ��
    static boolean halfFlag=false;//��ʻ��Ȧ��־
    
    static float SpeedFactor=1;//�ٶ��������� ,����0.3f
    static int SpeedFactorControl=0;//�ٶ�����״̬��1Ϊ����30%״̬��0Ϊ��׼״̬��-1Ϊ����30%״̬
    
    static long gameStartTime;//��Ϸ��ʼʱ��
    static long benquanStartTime;//��Ϸ��Ȧʱ��
    
    static float airshipRow;//��ͧ���ڵ�ͼ��
    static float airshipCol;//��ͧ���ڵ�ͼ��
    
    //key-pointerId  value-0������٣�1������٣�2�������������������շ�С��ͼ���շ��ٶȱ��л���һ�˳ơ������˳��ӽ�
    static HashMap<Integer,Integer> isSpeedVirtualButton=new HashMap<Integer,Integer>();

    public static long gameContinueTime()//��ȡ��Ϸʱ��
    {
    	return System.currentTimeMillis()-gameStartTime;
    }
    
    public static long thisCycleContinueTime()//��ȡ��Ȧʱ��
    {
    	return System.currentTimeMillis()-benquanStartTime;
    }
    
    static ArrayList<TreeForControl> treeList=new ArrayList<TreeForControl>();//���ڻ��Ƶ����б�
    
    //�ӳ����������������������
    public static float[] calFromCarXYZToCameraXYZ(float carXtemp,float carYtemp,float carZtemp,float carAlphaTemp)
    {   
    	if(viewFlag)
    	{//��Ϊ�����˳��ӽ�
    		float cy=carYtemp+20.0f;
        	float cz=(float) (carZtemp+40*Math.cos(Math.toRadians(carAlphaTemp)));
        	float cx=(float) (carXtemp+40*Math.sin(Math.toRadians(carAlphaTemp)));  
        	return new float[]{cx,cy,cz,carXtemp,carYtemp,carZtemp};
    	}
    	else
    	{//��Ϊ��һ�˳��ӽ�
    		float cx=(float)(carXtemp+1*Math.sin(Math.toRadians(carAlphaTemp))); 
    		float cy=carYtemp+12;
    		float cz=(float)(carZtemp+1*Math.cos(Math.toRadians(carAlphaTemp)));
    		
    		float ty=cy-1;
        	float tz=(float) (cz-40*Math.cos(Math.toRadians(carAlphaTemp)));
        	float tx=(float) (cx-40*Math.sin(Math.toRadians(carAlphaTemp)));  
        	return new float[]{cx,cy,cz,tx,ty,tz};
    	}    	
    }
    
    static int keyState=0;//����״̬  1-up 2-down 4-left 8-right
    static ThreadKey kt;//����״̬����߳�
    static ThreadColl kc;//��ײ�����˶��߳�
    static ThreadSpeed ts;//�Ӽ��ٵ��ɵļ���߳�
    
    ThreadCamera tc;//�����Ѳ���߳�
    
    static int grassTextureId;//�ݵ�����id
    static int moutainTextureId;//ɽ����id
    static int roadTextureId;//��·����id
    static int lubiaoTextureId;//·��������id
    static int zwTextureId;//��ʻ���������id
    static int waterTextureId;//ˮ������id
    static int skyTextureId;//���������id
    static int beginTextureId;//������ʼ��־����id
    static int tunnelTextureId;//�������id
    static int bridgeTextureId;//������id
    static int buildingTextureId;//��¥����id
    static int guanggaoTextureId;//�������id
    static int houseTextureId;//ũ������id
    static int treeTextureId;//������id
    static int chePaiTextureId1;//����1����id
    static int chePaiTextureId2;//����2����id
    static int upTextureId;//�������UP��id
    static int downTextureId;//�������DOWN��id
    static int mTextureId;//�������M��id
    static int qTextureId;//�������Q��id
    static int sTextureId;//�������S��id
    static int miniMapTextureId;//С��ͼ����id
    static int yibiaopanTextureId;//�Ǳ�������id
    static int roadSignTextureId;//·������id
    static int airshipTextureId;//��ͧ����id
    static int trafficLightTextrueId;//��ͨ������id
    static int timeTextureId;//ʱ������id
    static int daojishiTextureId;//����ʱ����id
    static int zhangaiwuTextureId;//�ϰ�������id
    static int drumTextureId;//��ͨͲ����id
    static int prismTextureId;//��ͨ��������id
    
    static Bitmap grassTextureBm;//�ݵ�����ͼ
    static Bitmap moutainTextureBm;//ɽ����ͼ
    static Bitmap roadTextureBm;//��·����ͼ
    static Bitmap lubiaoTextureBm;//·��������ͼ
    static Bitmap zwTextureBm;//��ʻ���������ͼ
    static Bitmap waterTextureBm;//ˮ������ͼ
    static Bitmap skyTextureBm;//���������ͼ
    static Bitmap beginTextureBm;//������ʼ��־����ͼ
    static Bitmap tunnelTextureBm;//�������ͼ
    static Bitmap bridgeTextureBm;//������ͼ
    static Bitmap buildingTextureBm;//��¥����ͼ
    static Bitmap guanggaoTextureBm;//�������ͼ
    static Bitmap houseTextureBm;//ũ������ͼ
    static Bitmap treeTextureBm;//������ͼ
    static Bitmap chePaiTextureBm1;//����1����ͼ
    static Bitmap chePaiTextureBm2;//����2����ͼ
    static Bitmap upTextureBm;//�������UP��ͼ
    static Bitmap downTextureBm;//�������DOWN��ͼ
    static Bitmap mTextureBm;//�������M��ͼ
    static Bitmap qTextureBm;//�������Q��ͼ
    static Bitmap sTextureBm;//�������S��ͼ
    static Bitmap miniMapTextureBm;//С��ͼ����ͼ
    static Bitmap yibiaopanTextureBm;//�Ǳ�������ͼ
    static Bitmap roadSignTextureBm;//·������ͼ
    static Bitmap airshipTextureBm;//��ͧ����ͼ
    static Bitmap trafficLightTextrueBm;//��ͨ������ͼ
    static Bitmap timeTextureBm;//ʱ������ͼ
    static Bitmap daojishiTextureBm;//����ʱ����ͼ
    static Bitmap zhangaiwuTextureBm;//�ϰ�������ͼ
    static Bitmap drumTextureBm;//��ͨͲ����ͼ
    static Bitmap prismTextureBm;//��ͨ��������ͼ
    
	static DrawGrassAndMoutain plain;//ƽԭƽԭ
	static DrawGrassAndMoutain moutain;//ʯͷɽ����
	static DrawPool pool;//��������
	static DrawSky sky;//����򲿼�
	static WDBJ_N wdbj_n;//��ʱ���������
	static WDBJ_S wdbj_s;//˳ʱ���������
	static ZDBJ zdbj;//ֱ������
	static DrawBegin begin;//��ʼ��־����
	static DrawTunnel tunnel;//�������
	static DrawBridgeOuter bridge;//�Ų���
	static DrawBuilding building;//��¥����
	static DrawBillBoard guanggao;//��沿��
	static DrawHouse house;//ũ������
	static DrawTree tree;//������
	static DrawLicensePlate chepai;//���Ʋ���
	static TextureRect goButton;//����ǰ����ť
	static TextureRect backButton;//������˰�ť
	static TextureRect MButton;//���������ͼ���ư�ť
	static TextureRect QButton;//�����ӽǿ��ư�ť
	static TextureRect SButton;//�����Ǳ��̿��ư�ť
	static DrawMiniMap minimap;//С��ͼ����
	static Car miniCar;//���㳵����
	static DrawPanel panel;//�Ǳ��̲���
	static DrawRoadSign roadSign;//·�겿��
	static DrawAirship airship;//��ͧ����
	static DrawTrafficLights tl;//��ͨ�Ʋ���
	static DrawIt time;//ʱ���¼����
	static DrawCountdown daojishi;//����ʱ����
	static Obstacle zhangaiwu;//�ϰ��ﲿ��
	static DrawDrum drum;//��ͨͲ����
	static DrawPrism prism;//��ͨ��������
	
	static BNShape[] kzbjyylb=new BNShape[3];//��ײ���������б�
	static int[] kzbjwllb=new int[3];//��ײ�����������б�
	static ArrayList<KZBJForControl> kzbjList;//��ײ�������������б�
	static ArrayList<SpeedSpringForControl> ssfcList;//�Ӽ��ٵ��ɲ������������б�
	
	//��obj�ļ��м��ص�3D����
	static LoadedObjectVertexNormal lovn_car_body;//���� 
	static LoadedObjectVertexNormal lovn_car_wd;//β��
    static LoadedObjectVertexNormal lovn_car_lt;//��̥
    static LoadedObjectVertexNormal lovn_car_wheel;//����
    static LoadedObjectVertexNormal lovn_speed_spring;//�ٶȵ���
	
	public MyGLSurfaceView(Activity_GL_Racing activity) {
        super(activity);
        MyGLSurfaceView.activity=activity; 
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
        
        carX=CAR_X;
        carY=CAR_Y;
        carZ=CAR_Z;
        
        //�������������̼���߳� 
        kt=new ThreadKey(this);
        //����ײ�����˶��߳�
        kc=new ThreadColl(this);
        //�Ӽ��ٵ��ɵļ���߳�
        ts=new ThreadSpeed(this);
    }   
	
	@Override 
    public boolean onKeyDown(int keyCode, KeyEvent e)
    {//�������¼��ص�����	
		if(Activity_GL_Racing.keyFlag==false)//��Ϸ���������������תʱ�����̲��ɿأ���ת������ʹ���ָ̻��ɿ��ơ���flagFinishΪfalseʱ�����̲��ɿأ���ΪTrueʱ���ָ��ɿء�
		{
			return true;
		}			
		
		if(keyCode==4)//�����ؼ�����
		{
			initState();//���ؼ�����
			activity.toAnotherView(ENTER_MENU);//���ز˵�����
		}
		
		if(Activity_GL_Racing.sensorFlag==true&&Activity_GL_Racing.inGame==true)//���Ǵ�����ģʽ�����������Ҽ���������
		{
			switch(keyCode)
			{
    		case 45://�л��ӽ�Q��
    			viewFlag=!viewFlag;
    		break; 
    		case 41://�շ������ͼ,M��
    			mapFlag=!mapFlag;
    		break;
    		case 47://�շ��Ǳ���,S��
    			yibiaopanFlag=!yibiaopanFlag;
    		break;
			}
		}
		else
		{
	    	switch(keyCode)
	    	{
	    		case 19://up
	    			keyState=keyState|0x1;
	    		break;
	    		case 20://down
	    			keyState=keyState|0x2;
	        	break;
	    		case 21://left
	    			keyState=keyState|0x4;
	    	    break;
	    		case 22://right
	    			keyState=keyState|0x8;
		        break;
	    		case 45://�л��ӽ�Q��
	    			viewFlag=!viewFlag;
	    		break;
	    		case 41://�շ������ͼ,M��
	    			mapFlag=!mapFlag;
	    		break;
	    		case 47://�շ��Ǳ���,S��
	    			yibiaopanFlag=!yibiaopanFlag;
	    		break;
	    	} 
		}
    	return true;
    }
	
	@Override
	public boolean onKeyUp(int keyCode, KeyEvent e)
	{//��̧���¼��ص�����
		if(keyCode==4){
			return false;//̧��return��
		}		
		switch(keyCode)
    	{
    		case 19://up
    			keyState=keyState&0xE;
    		break;
    		case 20://down
    			keyState=keyState&0xD;
        	break; 
    		case 21://left
    			keyState=keyState&0xB;
    	    break;
    		case 22://right
    			keyState=keyState&0x7;
	        break;
    	} 	
		return true;
	}
	
	//�����¼��ص�����
    @Override 
    public boolean onTouchEvent(MotionEvent e) 
    {
    	if(Activity_GL_Racing.sensorFlag==false)//������Ǵ�����ģʽ��������̲����á�
    	{
    		return true;
    	}
    	if(Activity_GL_Racing.inGame==true)//������������ã���������Ϸ�У�������̲ſ���
    	{    		
    		int index=(e.getAction()&MotionEvent.ACTION_POINTER_ID_MASK)>>>MotionEvent.ACTION_POINTER_ID_SHIFT;
            float y = e.getY();
            float x = e.getX();                 
            float yRatio=y/Activity_GL_Racing.screenHeight;
            float xRatio=x/Activity_GL_Racing.screenWidth;   
            switch (e.getAction()&MotionEvent.ACTION_MASK) {
    	        case MotionEvent.ACTION_DOWN://���¶���
    	        case MotionEvent.ACTION_POINTER_DOWN:
    	        	if((e.getAction()&MotionEvent.ACTION_MASK)==MotionEvent.ACTION_POINTER_DOWN)
    	        	{ 
    	        		x=e.getX(index);
    	        		y=e.getY(index);    	 
    	        		yRatio=y/Activity_GL_Racing.screenHeight;
    	                xRatio=x/Activity_GL_Racing.screenWidth;   
    	        	}  
    	            if(yRatio>XNAN_ON_TOUCH[Activity_GL_Racing.screenId][0]&&yRatio<XNAN_ON_TOUCH[Activity_GL_Racing.screenId][1]
    	               &&xRatio>XNAN_ON_TOUCH[Activity_GL_Racing.screenId][2]&&xRatio<XNAN_ON_TOUCH[Activity_GL_Racing.screenId][3])
    	            {//����ǰ�����ⰴť
    	            	keyState=keyState|0x1;
    	            	isSpeedVirtualButton.put(index, 0);
    	            }
    	            else if(yRatio>XNAN_ON_TOUCH[Activity_GL_Racing.screenId][4]&&yRatio<XNAN_ON_TOUCH[Activity_GL_Racing.screenId][5]
    	    	               &&xRatio>XNAN_ON_TOUCH[Activity_GL_Racing.screenId][6]&&xRatio<XNAN_ON_TOUCH[Activity_GL_Racing.screenId][7])
    	            {//���º������ⰴť
    	            	keyState=keyState|0x2;
    	            	isSpeedVirtualButton.put(index, 1);
    	            }
    	            else if(yRatio>XNAN_ON_TOUCH[Activity_GL_Racing.screenId][8]&&yRatio<XNAN_ON_TOUCH[Activity_GL_Racing.screenId][9]
    	    	               &&xRatio>XNAN_ON_TOUCH[Activity_GL_Racing.screenId][10]&&xRatio<XNAN_ON_TOUCH[Activity_GL_Racing.screenId][11])
     	            {//����M���ⰴť
    	            	mapFlag=!mapFlag;
    	            	isSpeedVirtualButton.put(index, 2);
     	            }
    	            else if(yRatio>XNAN_ON_TOUCH[Activity_GL_Racing.screenId][12]&&yRatio<XNAN_ON_TOUCH[Activity_GL_Racing.screenId][13]
    	    	               &&xRatio>XNAN_ON_TOUCH[Activity_GL_Racing.screenId][14]&&xRatio<XNAN_ON_TOUCH[Activity_GL_Racing.screenId][15])
     	            {//����Q���ⰴť
    	            	viewFlag=!viewFlag;
    	            	isSpeedVirtualButton.put(index, 2);
     	            }
    	            else if(yRatio>XNAN_ON_TOUCH[Activity_GL_Racing.screenId][16]&&yRatio<XNAN_ON_TOUCH[Activity_GL_Racing.screenId][17]
    	    	               &&xRatio>XNAN_ON_TOUCH[Activity_GL_Racing.screenId][18]&&xRatio<XNAN_ON_TOUCH[Activity_GL_Racing.screenId][19])
     	            {//����S���ⰴť
    	            	yibiaopanFlag=!yibiaopanFlag;
    	            	isSpeedVirtualButton.put(index, 2);
     	            }    	            
    	        break;
    	        case MotionEvent.ACTION_UP://̧���� 
    	        case MotionEvent.ACTION_POINTER_UP:
    	        	Integer ii=isSpeedVirtualButton.get(index);    	   
    	        	isSpeedVirtualButton.remove(index);
    	        	if(ii!=null)
    	        	{
    	        		int ac=ii.intValue();    	        		
        	        	if(ac==0||ac==1)
        	        	{
        	        		keyState=keyState&0xC;
        	        	}   
    	        	}         	        	
    	        	if(index==0) 
    	        	{
    	        		ii=isSpeedVirtualButton.get(1);    
    	        		if(ii!=null)
    	        		{
    	        			isSpeedVirtualButton.remove(1);
    	        			isSpeedVirtualButton.put(0, ii);
    	        		}
    	        	}
    	        break;
            } 
    	}
        return true;
    }

	private class SceneRenderer implements GLSurfaceView.Renderer 
    { 
        public void onDrawFrame(GL10 gl) {                	
        	//�����ɫ����
        	gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        	//���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
           gl.glLoadIdentity();     

           float carXtemp=carX;//����λ�ã��Գ�Ϊ�������Ŀ��㡣
           float carYtemp=carY;
           float carZtemp=carZ;
           float carAlphaTemp=carAlpha;//������ת�Ƕ�
           float[] cameraPosition=calFromCarXYZToCameraXYZ(carXtemp,carYtemp,carZtemp,carAlphaTemp);//���ݳ���λ����ȷ���������λ��           
       
           if(ThreadCamera.cameraFlag==false)//��Ϸ���ӽ�
           { 
        	   carY=CAR_Y;//��ԭ����Y����λ��
        	   
        	   GLU.gluLookAt
               ( 
              		gl, 
              		cameraPosition[0],   //�����λ��X
              		cameraPosition[1],
              		cameraPosition[2],   //�����λ��Z
              		cameraPosition[3], 	//�����򿴵ĵ�X
              		cameraPosition[4],   //�����򿴵ĵ�Y
              		cameraPosition[5],   //�����򿴵ĵ�Z
              		0, 
              		1, 
              		0
             ); 
           }
           else//�����Ѳ���ӽ�
           {
               carX=CAR_X;
               carY=ThreadCamera.cary;
               carZ=CAR_Z;
               
        	   GLU.gluLookAt
        	   (
        			   gl, 
        			   ThreadCamera.cx, 
        			   ThreadCamera.cy, 
        			   ThreadCamera.cz, 
        			   carX, 
        			   carY, 
        			   carZ, 
        			   0,  
        			   1, 
        			   0
        	   );
           }            
            
            drawSky(gl,cameraPosition,carXtemp,carYtemp,carZtemp,carAlphaTemp);//���������            
            drawMapA(gl);//����½�ز�����
            drawMapB(gl);            
            drawAirship(gl);//���Ʒ�ͧ
            drawTreeList(gl);//������ 
            
            drawCar(gl,carXtemp,carYtemp,carZtemp,carAlphaTemp);//���Ƴ�
             
            if(Activity_GL_Racing.sensorFlag==true)
            {
                drawButton(gl,Activity_GL_Racing.screenId);//�������ⰴť 
            }
 
            if(mapFlag)
            {
            	 drawMiniMap(gl,Activity_GL_Racing.screenId);//���������ͼ 
            } 
           
            if(yibiaopanFlag)
            { 
            	drawPanel(gl,Activity_GL_Racing.screenId);//�����Ǳ���
            } 
             
            if(timeFlag)//���ʱ�俪ʼ��¼������㵱ǰʱ����ʾֵ
            {            	
            	time.toTotalTime(MyGLSurfaceView.gameContinueTime());//��ȡ��Ϸ������ʱ��
            	time.toBenQuanTime(MyGLSurfaceView.thisCycleContinueTime());//��ȡ��Ȧ��Ϸ���е�ʱ��
            }            
            drawTime(gl,Activity_GL_Racing.screenId);//����ʱ��
            
            if(daojishiFlag)
            {
                drawCountdown(gl);//���Ƶ���ʱ
            }
        }  
        
        public void drawCar(GL10 gl,float carXtemp,float carYtemp,float carZtemp,float carAlphaTemp)//���Ƴ�����
        {
        	gl.glPushMatrix();
            gl.glTranslatef(carXtemp,carYtemp,carZtemp); 
            if(viewFlag)//�����˳��ӽǣ��������Ŷ�ֵ��
            {
            	gl.glRotatef(carAlphaTemp+carAlphaRD, 0, 1, 0);
            }
            else//��һ�˳��ӽǣ��������Ŷ�
            {
            	gl.glRotatef(carAlphaTemp, 0, 1, 0);
            }
        	
        	//�������       
            gl.glEnable(GL10.GL_LIGHTING);
            initLight(gl);
        	lovn_car_body.drawSelf(gl,1,1,0);
        	if(isBrake==true)//��ǰ������β�Ʋ���
        	{ 
        		lovn_car_wd.drawSelf(gl,1,0,0); 
        	}
        	else //�����ˣ���β����
        	{
        		lovn_car_wd.drawSelf(gl,0.5f,0,0);  
        	}
        	 
        	gl.glPushMatrix();//�Һ��� 
        	gl.glTranslatef(WHEEL_X_OFFSET,WHEEL_Y_OFFSET, WHEEL_Z_OFFSET);
        	lovn_car_wheel.drawSelf(gl, 1, 1, 1);
        	lovn_car_lt.drawSelf(gl, 0, 0, 0);
        	gl.glPopMatrix();
        	 
        	gl.glPushMatrix();//�����
        	gl.glTranslatef(-WHEEL_X_OFFSET,WHEEL_Y_OFFSET, WHEEL_Z_OFFSET);
        	lovn_car_wheel.drawSelf(gl, 1, 1, 1); 
        	lovn_car_lt.drawSelf(gl, 0, 0, 0);
        	gl.glPopMatrix();
        	
        	gl.glPushMatrix();//��ǰ��
        	gl.glTranslatef(WHEEL_X_OFFSET,WHEEL_Y_OFFSET, -WHEEL_Z_OFFSET);
        	gl.glRotatef(carAlphaRD*2, 0, 1, 0);
        	lovn_car_wheel.drawSelf(gl, 1, 1, 1);
        	lovn_car_lt.drawSelf(gl, 0, 0, 0);
        	gl.glPopMatrix();
        	
        	gl.glPushMatrix();//��ǰ��
        	gl.glTranslatef(-WHEEL_X_OFFSET,WHEEL_Y_OFFSET, -WHEEL_Z_OFFSET);
        	gl.glRotatef(carAlphaRD*2, 0, 1, 0);
        	lovn_car_wheel.drawSelf(gl, 1, 1, 1);
        	lovn_car_lt.drawSelf(gl, 0, 0, 0);
        	gl.glPopMatrix();
        	
        	//�رչ���       
            gl.glDisable(GL10.GL_LIGHTING);
            
            gl.glPushMatrix();//���ƺ���
            gl.glTranslatef(0, 8.2f, 21.3f);
            gl.glRotatef(-20, 1, 0, 0);//ת��15��
            chepai.drawSelf(gl, chePaiTextureId1);//���Ƴ���
            gl.glPopMatrix();            
        	
            gl.glPushMatrix();//����ǰ����
            gl.glTranslatef(0, 6.2f, -21.3f);
            gl.glRotatef(180, 0, 1, 0);
            gl.glRotatef(-20, 1, 0, 0);//ת��15��            
            chepai.drawSelf(gl, chePaiTextureId1);//���Ƴ���
            gl.glPopMatrix();              
        	gl.glPopMatrix();
        } 
        
        public void drawSky(GL10 gl,float[] cameraPosition,float carXtemp,float carYtemp,float carZtemp,float carAlphaTemp)//���������
        {
        	gl.glPushMatrix();
            //���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();
            if(viewFlag)//�����˳��ӽǵ������
            {
            	gl.glTranslatef(carXtemp-cameraPosition[0], carYtemp-cameraPosition[1]+200, carZtemp-cameraPosition[2]);
            }
            else//��һ�˳��ӽǵ������
            {
            	gl.glTranslatef(carXtemp-cameraPosition[0], carYtemp-cameraPosition[1]-600, carZtemp-cameraPosition[2]);
            }        	
        	gl.glRotatef(-(carAlphaTemp+carAlphaRD+45), 0, 1, 0);        	
        	sky.drawSelf(gl, skyTextureId, 0);        	
        	gl.glPopMatrix();
        }
        
        public void drawMapA(GL10 gl)//½�ز������Ʒ���,ɨ�貿�����飬���Ʋ���
        {
        	float cameraCol=(float)(Math.floor((carX-X_OFFSET)/X_SPAN));//��������ڵ�ͼ��λ����
        	float cameraRow=(float)(Math.floor((carZ-Z_OFFSET)/Z_SPAN));//��������ڵ�ͼ��λ����
        	treeList.clear();        	
        	for(int i=0;i<MAP_LEVEL0.length;i++)//����������ͼ��ֻ�����������Χ����Ϊ3��½�ز�������֮�ڵĲ����Ż��ơ���Լ�ڴ棬������Ⱦ����
        	{
        		if(Math.abs(cameraRow-i)>=3)
        		{
        			continue;
        		}
        		for(int j=0;j<MAP_LEVEL0[0].length;j++)
        		{        			
        			if(Math.abs(cameraCol-j)>=3) 
        			{
        				continue;
        			}
        			drawMapLevel0Item(gl,MAP_LEVEL0[i][j],i,j);//����ɽ��ƽԭ�ͳ���
        			drawPartItem(gl,i,j);//���ƾ�ɫ����
        			drawKZBJ(gl,i,j);
        			drawSpeedSpring(gl,i,j);
        			addTreeToDrawList(gl,i,j);        			
        		}
        	} 
        }
        
        public void drawMapB(GL10 gl)//½�ز������Ʒ���,ɨ�貿�����飬���Ʋ�������������·
        {        	
        	float cameraCol=(float)(Math.floor((carX-X_OFFSET)/X_SPAN));//��������ڵ�ͼ��λ����
        	float cameraRow=(float)(Math.floor((carZ-Z_OFFSET)/Z_SPAN));//��������ڵ�ͼ��λ����
        	
        	for(int i=0;i<MAP_LEVEL0.length;i++)//����������ͼ��ֻ�����������Χ����Ϊ3��½�ز�������֮�ڵĲ����Ż��ơ���Լ�ڴ棬������Ⱦ����
        	{
        		if(Math.abs(cameraRow-i)>=3)
        		{
        			continue;
        		}
        		for(int j=0;j<MAP_LEVEL0[0].length;j++)
        		{        			
        			if(Math.abs(cameraCol-j)>=3) 
        			{
        				continue;
        			}
        			drawMapLevel1Item(gl,MAP_LEVEL1[i][j],i,j);      			
        		}
        	} 
        }
        
        //���Ʋ�����ײ����
        public void drawPartItem(GL10 gl,float row,float col)
        {	
        	for(float[] partT:PART_LIST)
        	{
        		if(row==partT[0]&&col==partT[1])
        		{
        			switch((int)partT[2])
        			{ 
        				case 0://0Ϊ�������
        		            gl.glPushMatrix();
        		            gl.glTranslatef(partT[3], partT[4], partT[5]);
        		            gl.glRotatef(partT[6], 0, 1, 0);
        		            tunnel.drawSelf(gl, tunnelTextureId, 0);
        		            gl.glPopMatrix();       					
        				break;  
        				case 1://1Ϊ�ŵĻ���
        					gl.glPushMatrix();
        		            gl.glTranslatef(partT[3], partT[4], partT[5]);
        		            gl.glRotatef(partT[6], 0, 1, 0);
        		            bridge.drawSelf(gl, bridgeTextureId, 0);
        		            gl.glPopMatrix();   
        				break;
        				case 2://2Ϊ��¥�Ļ���
        					gl.glPushMatrix();
        		            gl.glTranslatef(partT[3], partT[4], partT[5]);
        		            gl.glRotatef(partT[6], 0, 1, 0);
        		            building.drawSelf(gl, buildingTextureId, 0);
        		            gl.glPopMatrix(); 
        				break;
        				case 3://3������ʼ�߲���
        					gl.glPushMatrix();
        		            gl.glTranslatef(partT[3], partT[4], partT[5]);
        		            gl.glRotatef(partT[6], 0, 1, 0);
        		            begin.drawSelf(gl, beginTextureId, 0);
        		            gl.glPopMatrix(); 
        				break;
        				case 4://4���ƹ���Ʋ���
        					gl.glPushMatrix();
        		            gl.glTranslatef(partT[3], partT[4], partT[5]); 
        		            gl.glRotatef(partT[6], 0, 1, 0);
        		            guanggao.drawSelf(gl, guanggaoTextureId, (int)partT[7]);
        		            gl.glPopMatrix(); 
        				break;
        				case 5://5����ũ������
        					gl.glPushMatrix();
        		            gl.glTranslatef(partT[3], partT[4], partT[5]); 
        		            gl.glRotatef(partT[6], 0, 1, 0);
        		            house.drawSelf(gl, houseTextureId, 0);
        		            gl.glPopMatrix();
        				break;
        				case 6://6����·�겿��
        					gl.glPushMatrix();
        		            gl.glTranslatef(partT[3], partT[4], partT[5]); 
        		            gl.glRotatef(partT[6], 0, 1, 0);
        		            roadSign.drawSelf(gl, roadSignTextureId, (int)partT[7]);
        		            gl.glPopMatrix();
        				break;
        				case 7://7���ƽ�ͨ�Ʋ���
        					gl.glPushMatrix();
        		            gl.glTranslatef(partT[3], partT[4], partT[5]); 
        		            gl.glRotatef(partT[6], 0, 1, 0);
        		            tl.drawSelf(gl, trafficLightTextrueId, (int)partT[7]);
        		            gl.glPopMatrix(); 
        				break;
        			}
        		}
        	}
        }
        
        //���ƿ�ײ����
        public void drawKZBJ(GL10 gl,float row,float col)
        {
        	for(KZBJForControl kzbjfcTemp:kzbjList)
        	{
        		if(kzbjfcTemp.row==row&&kzbjfcTemp.col==col)
        		{
        			kzbjfcTemp.drawSelf(gl);
        		}
        	}
        }
        
        //���ƼӼ��ٵ���
        public void drawSpeedSpring(GL10 gl,int row,int col)
        {
        	try
        	{
        		for(int i=0;i<ssfcList.size();i++)
            	{
            		ssfcList.get(i).drawSelf(gl,row,col);
            	}
        	}
        	catch(Exception e)
        	{
        		e.printStackTrace();
        	}
        }
        
        //����Ҫ���Ƶ�����ӽ������б�
        public void addTreeToDrawList(GL10 gl,float row,float col)
        {
        	for(float[] partTree:TREE_LIST)//����������
        	{ 
        		if(partTree[0]==row&&partTree[1]==col)//������Ⱦ��Χ��������ӵ��������б���
        		{
        			treeList.add(new TreeForControl(partTree[2], partTree[3], partTree[4], (int)partTree[6]));					
        		}
        	}
        }
        
        //�������б�ķ���
        public void drawTreeList(GL10 gl)
        {
        	//���㵱���������λ��
        	float[] cameraPosition=calFromCarXYZToCameraXYZ(carX,carY,carZ,carAlpha);
        	
        	//���Ȱ����������������λ�ã�Զ����ǰ�ߣ������ź��
        	for(TreeForControl tfc:treeList)
        	{
        		tfc.setCameraPosition(cameraPosition);
        	}
        	
        	Collections.sort(treeList);
        	
        	
        	//�������б�����ÿ�������л���
        	for(TreeForControl tfc:treeList)
        	{
        		gl.glPushMatrix();
	            gl.glTranslatef(tfc.xOffset,tfc.yOffset,tfc.zOffset); 
	            tree.calculateDirection(tfc.xOffset, tfc.zOffset, cameraPosition[0], cameraPosition[2]);
	            tree.drawSelf(gl, treeTextureId, tfc.id);
	            gl.glPopMatrix();
        	}
        	
        }
        
        
        //���ݲ�����id��ȷ����Ҫ���ƵĲ����������λ��,�˲����ɽ��ƽԭ�ͳ�����
        public void drawMapLevel0Item(GL10 gl,byte id,int row,int col)
        {
        	gl.glPushMatrix();
        	gl.glTranslatef((col+0.5f)*X_SPAN, 0, (row+0.5f)*Z_SPAN);
        	
        	if(id==0)//ƽԭ����
        	{
                plain.drawSelf(gl);
        	}    
        	else if(id==1)//ɽ����
        	{
        		moutain.drawSelf(gl);
        	}
        	else if(id==2)//��������
        	{
        		pool.drawSelf(gl);
        	}
        	gl.glPopMatrix();
        }
        
       //���ݲ�����id��ȷ����Ҫ���ƵĲ����������λ��,�˲����ֱ�����֣�˳ʱ���������ʱ����������֡�
        public void drawMapLevel1Item(GL10 gl,byte id,int row,int col)
        {
        	if(id==-1)//idΪ-1,�����ƹ�·��������-1λ�ÿɻ���ɽ�ء������Ȳ�����
        	{
        		return;
        	}
        	gl.glPushMatrix();
        	gl.glTranslatef((col+0.5f)*X_SPAN, 2f, (row+0.5f)*Z_SPAN);  
        	
        	if(id==0||id==1)//���������ֱ����������
        	{
        		if(id==1) 
        		{
        			gl.glRotatef(90, 0, 1, 0);
        		}
                zdbj.drawSelf(gl);
        	} 
        	else if(id>=2&&id<=5)//˳ʱ�������������
        	{  
        		int k=(id-2)*(-90);//���㵱�ڲ�����Ҫ��ת�ĽǶȡ�
        		gl.glRotatef(k, 0, 1, 0);
        		
        		wdbj_s.drawSelf(gl);
        	}
        	else if(id>=6&&id<=9)//��ʱ�������������
        	{
        		int k=(id-6)*(-90);//���㵱�ڲ�����Ҫ��ת�ĽǶȡ�
        		gl.glRotatef(k, 0, 1, 0);
        		
        		wdbj_n.drawSelf(gl);
        	}
        	gl.glPopMatrix();
        	gl.glEnable(GL10.GL_DEPTH_TEST);
        }
        
        //������Ļ���ⰴť��������ǰ�������ˣ�M��Q��S��
        public void drawButton(GL10 gl,int id)
        {
            //����ǰ���������ⰴť=======spectial begin=======
            gl.glPushMatrix();            
            //���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity(); 
            //�������   
            gl.glEnable(GL10.GL_BLEND); 
            //����Դ���������Ŀ��������
            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
            
            gl.glPushMatrix(); 
            gl.glTranslatef(XNAN_TRASLATE[id][19], XNAN_TRASLATE[id][20], XNAN_TRASLATE[id][21]);   
            goButton.drawSelf(gl);
            gl.glPopMatrix();
            
            gl.glPushMatrix();
            gl.glTranslatef(XNAN_TRASLATE[id][22], XNAN_TRASLATE[id][23], XNAN_TRASLATE[id][24]);  
            backButton.drawSelf(gl);
            gl.glPopMatrix();
            
            gl.glPushMatrix();
            gl.glTranslatef(XNAN_TRASLATE[id][7], XNAN_TRASLATE[id][8], XNAN_TRASLATE[id][9]);  
            MButton.drawSelf(gl);
            gl.glPopMatrix();
            
            gl.glPushMatrix();
            gl.glTranslatef(XNAN_TRASLATE[id][10], XNAN_TRASLATE[id][11], XNAN_TRASLATE[id][12]);  
            QButton.drawSelf(gl);
            gl.glPopMatrix();
            
            gl.glPushMatrix();
            gl.glTranslatef(XNAN_TRASLATE[id][13], XNAN_TRASLATE[id][14], XNAN_TRASLATE[id][15]);  
            SButton.drawSelf(gl);
            gl.glPopMatrix();
            
            gl.glDisable(GL10.GL_BLEND); 
            gl.glPopMatrix();
            
            
        }
        
        //���������ͼ
        public void drawMiniMap(GL10 gl,int id)
        {
            float carCol=(float) Math.floor(carX/X_SPAN);//�������к�
            float carRow=(float) Math.floor(carZ/X_SPAN); //�������к�
        	
            //���������ͼ
            gl.glPushMatrix();
            //���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity(); 
            gl.glTranslatef(XNAN_TRASLATE[id][4], XNAN_TRASLATE[id][5], XNAN_TRASLATE[id][6]); 
            //�������   
            gl.glEnable(GL10.GL_BLEND);   
            //����Դ���������Ŀ��������
            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
            for(int i=0;i<MAP_LEVEL1.length;i++)
            {
            	for(int j=0;j<MAP_LEVEL1[i].length;j++)
            	{
            		minimap.drawSelf(gl, miniMapTextureId, MAP_LEVEL1[i][j],i,j);
            	}
            }
            gl.glDisable(GL10.GL_BLEND);//�رջ��   
             
            gl.glPushMatrix(); 
            gl.glTranslatef 
            	( 
            			(-DrawMiniMap.MAP_LENGHT*minimap.scale+(1+2*carCol)*minimap.scale*DrawMiniMap.WIDTH+miniCar.scale*Car.RADIUS), 
            			(DrawMiniMap.MAP_HEIGHT*minimap.scale-(1+2*carRow)*minimap.scale*DrawMiniMap.HEIGHT-miniCar.scale*Car.RADIUS), 
            			0
            	);
            miniCar.drawSelf(gl);
            gl.glPopMatrix();
            
            gl.glPopMatrix();
        }
        
        //�����Ǳ��̡�������ģ������
        public void drawPanel(GL10 gl,int id)
        {
            //�����Ǳ���
            gl.glPushMatrix();
            //���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();
          //�������   
            gl.glEnable(GL10.GL_BLEND); 
            //����Դ���������Ŀ��������
            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
            gl.glTranslatef(XNAN_TRASLATE[id][16], XNAN_TRASLATE[id][17], XNAN_TRASLATE[id][18]);
            panel.changepointer(Math.abs(carV)); 
            panel.drawSelf(gl, yibiaopanTextureId, 0);
            gl.glDisable(GL10.GL_BLEND); 
            gl.glPopMatrix();
        }

        //���Ƽ�ʱ��
        public void drawTime(GL10 gl,int id)
        {
              gl.glPushMatrix();
              //���õ�ǰ����Ϊģʽ����
	          gl.glMatrixMode(GL10.GL_MODELVIEW);
	          //���õ�ǰ����Ϊ��λ���� 
	          gl.glLoadIdentity();
	          gl.glTranslatef(XNAN_TRASLATE[id][1], XNAN_TRASLATE[id][2], XNAN_TRASLATE[id][3]);
	          time.drawSelf(gl, timeTextureId, 0); 
	          gl.glPopMatrix();
        }
        
        //���Ƶ���ʱ
        public void drawCountdown(GL10 gl)
        {
            gl.glPushMatrix();
        	//���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();  
            //�������   
            gl.glEnable(GL10.GL_BLEND); 
            //����Դ���������Ŀ��������
            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
            daojishi.drawSelf(gl,daojishiTextureId,0);//����
            gl.glDisable(GL10.GL_BLEND);
            gl.glPopMatrix();
        }
     
        //���Ʒ�ͧ
        public void drawAirship(GL10 gl)
        {
        	for(float[] partT:AIRSHIP_LIST)
        	{
        		float cameraCol=(float)(Math.floor((carX-X_OFFSET)/X_SPAN));//��������ڵ�ͼ��λ����
            	float cameraRow=(float)(Math.floor((carZ-Z_OFFSET)/Z_SPAN));//��������ڵ�ͼ��λ����
            	
        		float airshipRow=(float) Math.floor((partT[2]+DrawAirship.feitingZ)/X_SPAN);//��ͧ���ڵ�ͼ���к���
        		float airshipCol=(float) Math.floor((partT[0]+DrawAirship.feitingX)/X_SPAN);
        		
        		if(airshipRow-cameraRow>3||airshipRow-cameraRow<-3&&airshipCol-cameraCol>3||airshipCol-cameraCol<-3)
        		{
        			gl.glPushMatrix();
                    gl.glTranslatef(partT[0], partT[1], partT[2]);  
                    gl.glRotatef(partT[3], 0, 1, 0); 
                    airship.drawSelf(gl, airshipTextureId, 0);
                    gl.glPopMatrix();
        		}
        	}          
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
            gl.glFrustumf(-ratio, ratio, -0.8f*0.8f, 1.2f*0.8f, 1.0f, 4000);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            //�رտ����� 
        	gl.glDisable(GL10.GL_DITHER);
        	//�����ض�Hint��Ŀ��ģʽ������Ϊ����Ϊʹ�ÿ���ģʽ
            gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT,GL10.GL_FASTEST);
            //������Ļ����ɫ��ɫRGBA
            gl.glClearColor(0,0,0,0); 
            //������ɫģ��Ϊƽ����ɫ   
            //����Ϊ�򿪱������ 
    		gl.glEnable(GL10.GL_CULL_FACE);
            gl.glShadeModel(GL10.GL_SMOOTH);
            //������Ȳ���  
            gl.glEnable(GL10.GL_DEPTH_TEST);

        	grassTextureId=initTexture(gl,grassTextureBm);//ƽԭ����  
        	moutainTextureId=initTexture(gl,moutainTextureBm);//ʯɽ����  
        	roadTextureId=initTexture(gl,roadTextureBm);//��·����
        	lubiaoTextureId=initTexture(gl,lubiaoTextureBm);//·��������
        	zwTextureId=initTexture(gl,zwTextureBm);//��ʻ���������
        	waterTextureId=initTexture(gl,waterTextureBm);//ˮ������
        	skyTextureId=initTexture(gl,skyTextureBm);//���������
        	beginTextureId=initTexture(gl,beginTextureBm);//������ʼ��־����
        	tunnelTextureId=initTexture(gl,tunnelTextureBm);//�������
        	bridgeTextureId=initTexture(gl,bridgeTextureBm);//������
        	buildingTextureId=initTexture(gl,buildingTextureBm);//��¥����
        	guanggaoTextureId=initTexture(gl,guanggaoTextureBm);//�������
        	houseTextureId=initTexture(gl,houseTextureBm);//ũ������
        	treeTextureId=initTexture(gl,treeTextureBm);//������
        	chePaiTextureId1=initTexture(gl,chePaiTextureBm1);//����1����
        	chePaiTextureId2=initTexture(gl,chePaiTextureBm2);//����2����
        	upTextureId=initTexture(gl,upTextureBm);//�������UP��
        	downTextureId=initTexture(gl,downTextureBm);//�������DOWN��
        	mTextureId=initTexture(gl,mTextureBm);//�������M��
        	qTextureId=initTexture(gl,qTextureBm);//�������Q��
        	sTextureId=initTexture(gl,sTextureBm);//�������S��
        	miniMapTextureId=initNormalTexture(gl,miniMapTextureBm);//С��ͼ����
        	yibiaopanTextureId=initTexture(gl,yibiaopanTextureBm);//�Ǳ�������
        	roadSignTextureId=initTexture(gl,roadSignTextureBm);//·������
        	airshipTextureId=initTexture(gl,airshipTextureBm);//��ͧ����
        	trafficLightTextrueId=initTexture(gl,trafficLightTextrueBm);//��ͨ������
        	timeTextureId=initNormalTexture(gl,timeTextureBm);//ʱ������
        	daojishiTextureId=initTexture(gl,daojishiTextureBm);//����ʱ����
        	zhangaiwuTextureId=initTexture(gl,zhangaiwuTextureBm);//�ϰ�������
        	drumTextureId=initNormalTexture(gl,drumTextureBm);//��ͨͲ����
        	prismTextureId=initNormalTexture(gl,prismTextureBm);//��ͨ��������
        	
        	kzbjwllb[0]=drumTextureId;
        	kzbjwllb[1]=zhangaiwuTextureId;
        	kzbjwllb[2]=prismTextureId;
        	
        	plain.setTexId(grassTextureId);              
            moutain.setTexId(moutainTextureId);                
            pool.setTexId(grassTextureId, waterTextureId);     
            zdbj.setTexId(roadTextureId, lubiaoTextureId);  
            wdbj_n.setTexId(roadTextureId,lubiaoTextureId,zwTextureId); 
            wdbj_s.setTexId(roadTextureId,lubiaoTextureId,zwTextureId);
            goButton.setTexId(upTextureId);
            backButton.setTexId(downTextureId);
            MButton.setTexId(mTextureId);
            QButton.setTexId(qTextureId);
            SButton.setTexId(sTextureId);
                
            tl.initLightTurn();      
            tc=new ThreadCamera(); 
            tc.start();
        }
    }
	
	//�������д�������Ķ��㻺��
	public static void loadObjectVertex()
	{
        {
        	Constant.initConstant(Activity_GL_Racing.rs);//��ʼ������        	
        	
            plain=new DrawGrassAndMoutain(PyArray,ROWS,COLS);//ƽԭ
            loadProcessGo(1);
            moutain=new DrawGrassAndMoutain(SyArray,ROWS,COLS); //ʯɽ
            loadProcessGo(1);
            pool=new DrawPool(X_SPAN);  //����
            loadProcessGo(1);
            zdbj=new ZDBJ(X_SPAN,ROAD_W);//ֱ����·
            loadProcessGo(1);
            wdbj_n=new WDBJ_N(X_SPAN,ROAD_W);//��ʱ�������· 
            loadProcessGo(1);
            wdbj_s=new WDBJ_S(X_SPAN,ROAD_W);//˳ʱ�������· 
            loadProcessGo(1);
            goButton=new TextureRect(0.047f,0.04f,1,1);//����ǰ����ť
            loadProcessGo(1);
            backButton=new TextureRect(0.047f,0.04f,1,1);//������˰�ť     
            loadProcessGo(1);
            MButton=new TextureRect(0.047f,0.04f,1,1);//���������ͼ���ư�ť    
            loadProcessGo(1);
            QButton=new TextureRect(0.047f,0.04f,1,1);//�����ӽǿ��ư�ť    
            loadProcessGo(1);
            SButton=new TextureRect(0.047f,0.04f,1,1);//�����Ǳ��̿��ư�ť     
            loadProcessGo(1);
            
            lovn_car_wheel=
        		LoadUtil.loadFromFileVertexOnly("licenseplate.obj", Activity_GL_Racing.rs);//���س��� 
        	loadProcessGo(10);
            lovn_car_body=
        		LoadUtil.loadFromFileVertexOnly("carbody.obj", Activity_GL_Racing.rs);//���س���
            loadProcessGo(18);
        	lovn_car_wd=
        		LoadUtil.loadFromFileVertexOnly("tailight.obj", Activity_GL_Racing.rs);//���س�β��
        	loadProcessGo(10);
        	lovn_car_lt=
        		LoadUtil.loadFromFileVertexOnly("tire.obj", Activity_GL_Racing.rs);//������̥
        	loadProcessGo(10);
        	lovn_speed_spring=
        		LoadUtil.loadFromFileVertexOnly("spring.obj", Activity_GL_Racing.rs);//�����ٶȵ���
        	loadProcessGo(12);
            
            sky=new DrawSky(4f);//�����                       
            loadProcessGo(1);
            begin=new DrawBegin(ROAD_W/2);//������ʼ��־����
            loadProcessGo(1);
            tunnel=new DrawTunnel(1);//�������
            loadProcessGo(1);
            bridge=new DrawBridgeOuter(16);//�Ų���
            loadProcessGo(1);
            building=new DrawBuilding(1.5f);//��¥����
            loadProcessGo(1);
            guanggao=new DrawBillBoard(1.5f);//��沿��
            loadProcessGo(1);
            house=new DrawHouse(10f);//ũ������
            loadProcessGo(1);
            tree=new DrawTree(3);//������
            loadProcessGo(1);
            chepai=new DrawLicensePlate(2.0f);//���Ʋ���           
            loadProcessGo(1);
            minimap=new DrawMiniMap(0.1f);//С��ͼ����
            loadProcessGo(1);
            miniCar=new Car(0.1f);//���㳵����
            loadProcessGo(1);
            panel=new DrawPanel(3f);//�Ǳ��̲���
            loadProcessGo(1);
            roadSign=new DrawRoadSign(2.0f);//·�겿��
            loadProcessGo(1);
            airship=new DrawAirship(25);//��ͧ����
            loadProcessGo(1);
            tl=new DrawTrafficLights(2.0f);//��ͨ�Ʋ���  
            loadProcessGo(1);
            time=new DrawIt(20f);//ʱ���¼����
            loadProcessGo(1);
            daojishi=new DrawCountdown(0.25f);//����ʱ����
            loadProcessGo(1);
            zhangaiwu=new Obstacle(10.0f);//�ϰ��ﲿ��
            loadProcessGo(1);
            prism=new DrawPrism(15f);//��ͨ��������
            drum=new DrawDrum(5f);//��ͨͲ����
            loadProcessGo(1);
            kzbjyylb[0]=drum; 
            kzbjyylb[1]=zhangaiwu;
            kzbjyylb[2]=prism;
        	
        	
        	//��ײ�����б�
        	kzbjList=new ArrayList<KZBJForControl>();
        	for(float[] fa:KEZHUANG_LIST)
        	{
        		KZBJForControl tempkzfc=new KZBJForControl((int)fa[0],fa[1],fa[2],fa[3],(int)fa[4],(int)fa[5]);
        		kzbjList.add(tempkzfc);
        	}
        	//�Ӽ��ٵ����б�
        	ssfcList=new ArrayList<SpeedSpringForControl>();
        	for(float[] fa:SPEED_SPRING_LIST)
        	{
        		SpeedSpringForControl ssfc=new SpeedSpringForControl((int)fa[0],fa[1],fa[2],fa[3],(int)fa[4],(int)fa[5]);
        		ssfcList.add(ssfc);
        	}
        	
        	//����������Դ
        	grassTextureBm=loadBitmap(R.drawable.grass);//ƽԭ���� 
        	moutainTextureBm=loadBitmap(R.drawable.moutain);//ʯɽ����
        	loadProcessGo(1);
        	roadTextureBm=loadBitmap(R.drawable.road);//��·����
        	lubiaoTextureBm=loadBitmap(R.drawable.lubiao);//·��������
        	loadProcessGo(1);
        	zwTextureBm=loadBitmap(R.drawable.zw);//��ʻ���������
        	waterTextureBm=loadBitmap(R.drawable.water);//ˮ������
        	loadProcessGo(1);
        	skyTextureBm=loadBitmap(R.drawable.tkqn);//���������
        	beginTextureBm=loadBitmap(R.drawable.begin);//������ʼ��־����        	
        	tunnelTextureBm=loadBitmap(R.drawable.fortunnelred);//�������
        	bridgeTextureBm=loadBitmap(R.drawable.birdge);//������
        	loadProcessGo(1);
        	buildingTextureBm=loadBitmap(R.drawable.buildings);//��¥����
        	guanggaoTextureBm=loadBitmap(R.drawable.guanggao);//�������
        	loadProcessGo(1);
        	houseTextureBm=loadBitmap(R.drawable.house);//ũ������
        	treeTextureBm=loadBitmap(R.drawable.tree);//������
        	loadProcessGo(1);
        	chePaiTextureBm1=loadBitmap(R.drawable.cpone);//����1����
        	chePaiTextureBm2=loadBitmap(R.drawable.cptwo);//����2����
        	upTextureBm=loadBitmap(R.drawable.up);//�������UP��
        	loadProcessGo(1);
        	downTextureBm=loadBitmap(R.drawable.down);//�������DOWN��
        	mTextureBm=loadBitmap(R.drawable.m);//�������M��
        	qTextureBm=loadBitmap(R.drawable.q);//�������Q��
        	sTextureBm=loadBitmap(R.drawable.s);//�������S��
        	loadProcessGo(1);
        	miniMapTextureBm=loadBitmap(R.drawable.minimaproad);//С��ͼ����
        	yibiaopanTextureBm=loadBitmap(R.drawable.yibiaopan);//�Ǳ�������
        	roadSignTextureBm=loadBitmap(R.drawable.jiaotong);//·������
        	airshipTextureBm=loadBitmap(R.drawable.feiting);//��ͧ����
        	loadProcessGo(1);
        	trafficLightTextrueBm=loadBitmap(R.drawable.trafficlights);//��ͨ������
        	timeTextureBm=loadBitmap(R.drawable.time);//ʱ������
        	daojishiTextureBm=loadBitmap(R.drawable.daojishi);//����ʱ����
        	zhangaiwuTextureBm=loadBitmap(R.drawable.zhaw);//�ϰ�������
        	drumTextureBm=loadBitmap(R.drawable.drum);//��ͨͲ����
        	loadProcessGo(1);
        	prismTextureBm=loadBitmap(R.drawable.prism);//��ͨ��������        	
        	 
            rsLoadFlag=true; 
        } 		
	} 
	
	public static void loadProcessGo(int k)
	{
		Activity_GL_Racing.loading.process+=k;
    	Activity_GL_Racing.loading.repaint();
	}
	
  private void initLight(GL10 gl)
  {
    gl.glEnable(GL10.GL_LIGHT0);//��0�ŵ�  
    
    //����������
    float[] ambientParams={0.8f,0.8f,0.8f,1.0f};//����� RGBA
    gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_AMBIENT, ambientParams,0);            

    //ɢ�������
    float[] diffuseParams={0.9f,0.9f,0.9f,1.0f};//����� RGBA
    gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_DIFFUSE, diffuseParams,0); 
    
    //���������
    float[] specularParams={0.8f,0.8f,0.8f,1.0f};//����� RGBA
    gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_SPECULAR, specularParams,0);    
    
    float[] positionParamsGreen=//����0��ʾ�Ƕ�λ��
    {
    		(float) (113*Math.cos(Math.toRadians(carLightAngle))),
    		80,
    		(float) (113*Math.sin(Math.toRadians(carLightAngle))),
    		1
    };
    gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_POSITION, positionParamsGreen,0); 
  }
  
  //��������λͼ��Դ����
  public static Bitmap loadBitmap(int drawableId)
  {
	  InputStream is = rs.openRawResource(drawableId);
      Bitmap bitmapTmp=null; 
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
      return bitmapTmp;
  }
	 
	//��ʼ��������������id
	public int initTexture(GL10 gl,Bitmap bitmapTmp)//textureId
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
        
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmapTmp, 0);
        bitmapTmp.recycle();         
        return currTextureId;
	}
	
	//��ʼ����ͨ������������id
	public int initNormalTexture(GL10 gl,Bitmap bitmapTmp)//textureId 
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
        
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmapTmp, 0);
        bitmapTmp.recycle(); 
        
        return currTextureId;
	}
	
	//���ؼ���ʼ������
	public void initState() 
	{
		ThreadCamera.cameraFlag=true;//���������Ѳ������
		ThreadCamera.angle=180;//��ʼ�������Ѳ���Ƕ�   
		
		carY=ThreadCamera.cary;//��ԭ����Ѳ��Y����
		carV=0;//���㳵��	 
		carAlpha=DIRECTION_INI;//������ת�Ƕȳ�ʼ��
		carAlphaRD=0;//�����Ŷ��Ƕ�ֵ��ʼ��
		 
		DrawTrafficLights.count=0;//��ͨ�Ʋ�������
		DrawTrafficLights.flag=true;//���ý�ͨ�Ʋ��ſ��� 
				
		timeFlag=false;//���ü�ʱ��������
		
		DrawPool.waterFlag=false;//�ر�ˮ�沨���߳� 
		
		DrawAirship.thread.flag=false;//�رշ�ͧ�˶��߳�
		DrawAirship.angle=360;//��ͧ�˶��Ƕȳ�ʼ�� 
		DrawAirship.angle_Y=270;//��ͧ�������ߵ�ǰ֡�Ƕ� ��ʼ��
		DrawAirship.angle_Rotate=0;//��ͧ�Ŷ��Ƕȳ�ʼ��
		
		ThreadKey.flag=false;//�رռ����߳�
		ThreadColl.flag=false;//�رտ���ײ�����˶��߳�
		ThreadSpeed.flag=false;//�رռӼ��ٵ�����ײ����߳�
		
		keyState=0;//�ָ����̳�ʼ״̬
		 
		Car.flag=false;//�ر������ͼ��������־�˶��߳�
		
		Activity_GL_Racing.inGame=false;//��ʾ��ǰ״̬Ϊ������Ϸ�� 
		Activity_GL_Racing.mpBack.pause();//�رձ�����Ч
		
		halfFlag=false;//�����ʻ��¼��
		quanshu=0;
		
		ViewLoading.loadFlag=true;//����loading�����־λ
		
		DrawCountdown.PictureFlag=3;//��ʼ������ʱ
		DrawCountdown.Countdown_Z_Offset=-20;
		DrawCountdown.flag=true; 
		
		SpeedFactor=1;
		SpeedFactorControl=0;
		
		isSpeedVirtualButton.clear();
	}
}
