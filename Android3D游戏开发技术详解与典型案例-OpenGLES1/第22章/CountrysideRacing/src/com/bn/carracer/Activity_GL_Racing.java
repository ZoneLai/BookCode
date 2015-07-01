package com.bn.carracer;
import static com.bn.carracer.Constant.*;

import java.util.HashMap;
import java.util.Map;
import android.app.Activity;
import android.app.Service;
import android.content.pm.ActivityInfo;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.hardware.SensorListener;
import android.hardware.SensorManager;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.os.Bundle; 
import android.os.Handler;
import android.os.Message;
import android.os.Vibrator;
import android.util.DisplayMetrics;
import android.view.KeyEvent;
import android.view.Window;
import android.view.WindowManager;

public class Activity_GL_Racing extends Activity {
	private MyGLSurfaceView mGLSurfaceView;//��Ϸ����
	ViewStart viewStart;//��Ϸ��ʼ����ʱ���棬���ɺ�logoͼƬ
	SoundControl soundControl;//����ѡ�����
	ViewMainMenu viewMainMenu;//��Ϸ���˵�����
	ViewSet viewSet;//��Ϸ���ò˵�����
	ViewHelp viewHelp;//��Ϸ�����˵�����
	ViewAbout viewAbout;//���ڽ���
	static ViewLoading loading;//���ؽ���
	ViewOver over;//��������
	ViewChoose choose;//ѡ�����
	ViewHistory history;//��ʷ����
	ViewBreaking breaking;//�Ƽ�¼����
	ViewTry strive;//�ٽ�������ʾ����
	
	Handler hd;//��Ϣ������
	
	static Resources rs;
	private  Vibrator mVibrator;
	  
	//�����������ֲ��������ã���������õ� 
	static MediaPlayer mpBack;//������
	static SoundPool soundPool;//������ 
	static Map<Integer,Integer> soundPoolMap;//�����ؼ�ֵMap
	static boolean pauseFlag=false;//��Ч��ͣ��־λ
	static boolean soundFlag=true;//��Ч���Ʊ�־λ��Ĭ��Ϊ��������
	static boolean inGame=false;//����Ϸ�б�־λ��TRUE��ʾ����Ϸ�У�FALSE��ʾ������Ϸ�С�
		
	static float screenHeight;//��Ļ�߶�
	static float screenWidth;//��Ļ���
	static float screenRatio;//��Ļ��߱�
	static int screenId;//��ĻId
	 
	static float screenPictureWidth=480;
	static float screen_xoffset;//��ĻͼƬ����Ӧƫ����
	
	static boolean sensorFlag=true;//�Ƿ����ô�����ģʽ�ı�־λ��false��ʾΪ����ģʽ��true��ʾΪ������+�������ģʽ��
	static boolean keyFlag=false;//���ؼ�����,Ĭ��Ϊ���ɿأ���ΪstartView�м��̲��ɿء�
	static int viewFlag;//��ǰ�����־λ	 
	
	static Bitmap number[]=new Bitmap[12];//����1���飬ǳ�Ұ�
	static Bitmap shu[] =new Bitmap[11];//����2���飬����
    
	//=========================sensor begin============================
	//SensorManager�������� 
	SensorManager mySensorManager;	
	//=========================sensor end==============================
	
	//����ʵ����SensorEventListener�ӿڵĴ�����������
	private SensorListener mySensorListener = new SensorListener(){
		public void onAccuracyChanged(int sensor, int accuracy) 
		{	
		}
		public void onSensorChanged(int sensor, float[] values) 
		{//��ʹ�ô�������־λΪtrue,���ҳ����ɴ��ر�־λΪtrue,��ʹ�ô������� 
			if(sensor == SensorManager.SENSOR_ORIENTATION&&sensorFlag==true&&inGame==true)
			{//�ж��Ƿ�Ϊ���ٶȴ������仯����������	
				int[] directionDotXY=RotateUtil.getDirectionDot 
				(
						new double[]{values[0],values[1],values[2]}
			    );
				if(directionDotXY[0]>20)
				{//right
					MyGLSurfaceView.keyState=MyGLSurfaceView.keyState|0x4;
				}
				else if(directionDotXY[0]<-20)
				{//left
					MyGLSurfaceView.keyState=MyGLSurfaceView.keyState|0x8; 
				}
				else
				{//no left and no right
					MyGLSurfaceView.keyState=MyGLSurfaceView.keyState&0x3;
				}
			}	
		}		
	}; 
	
    @Override 
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        rs=this.getResources();
        
    	number[0]=BitmapFactory.decodeResource(this.getResources(), R.drawable.zero);//����ͼƬ
    	number[1]=BitmapFactory.decodeResource(this.getResources(), R.drawable.one);//����ͼƬ
    	number[2]=BitmapFactory.decodeResource(this.getResources(), R.drawable.two);//����ͼƬ
    	number[3]=BitmapFactory.decodeResource(this.getResources(), R.drawable.three);//����ͼƬ
    	number[4]=BitmapFactory.decodeResource(this.getResources(), R.drawable.four);//����ͼƬ
    	number[5]=BitmapFactory.decodeResource(this.getResources(), R.drawable.five);//����ͼƬ
    	number[6]=BitmapFactory.decodeResource(this.getResources(), R.drawable.six);//����ͼƬ
    	number[7]=BitmapFactory.decodeResource(this.getResources(), R.drawable.seven);//����ͼƬ
    	number[8]=BitmapFactory.decodeResource(this.getResources(), R.drawable.eight);//����ͼƬ
    	number[9]=BitmapFactory.decodeResource(this.getResources(), R.drawable.nine);//����ͼƬ
    	number[10]=BitmapFactory.decodeResource(this.getResources(), R.drawable.colon);//����ͼƬ
    	number[11]=BitmapFactory.decodeResource(this.getResources(), R.drawable.line);//����ͼƬ
    	
    	shu[0]=BitmapFactory.decodeResource(this.getResources(), R.drawable.shu0);//��������
    	shu[1]=BitmapFactory.decodeResource(this.getResources(), R.drawable.shu1);//
    	shu[2]=BitmapFactory.decodeResource(this.getResources(), R.drawable.shu2);//
    	shu[3]=BitmapFactory.decodeResource(this.getResources(), R.drawable.shu3);//
    	shu[4]=BitmapFactory.decodeResource(this.getResources(), R.drawable.shu4);//
    	shu[5]=BitmapFactory.decodeResource(this.getResources(), R.drawable.shu5);//
    	shu[6]=BitmapFactory.decodeResource(this.getResources(), R.drawable.shu6);//
    	shu[7]=BitmapFactory.decodeResource(this.getResources(), R.drawable.shu7);//
    	shu[8]=BitmapFactory.decodeResource(this.getResources(), R.drawable.shu8);//
    	shu[9]=BitmapFactory.decodeResource(this.getResources(), R.drawable.shu9);//
    	shu[10]=BitmapFactory.decodeResource(this.getResources(), R.drawable.baifenhao);//

        
        //����Ϊ����
        this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        
        //������Ϊ����ȫ��
        requestWindowFeature(Window.FEATURE_NO_TITLE); 
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN ,  
		              WindowManager.LayoutParams.FLAG_FULLSCREEN);  
        
        //��ȡ��Ļ�ֱ���
        DisplayMetrics dm=new DisplayMetrics();
        getWindowManager().getDefaultDisplay().getMetrics(dm);
        screenHeight=dm.heightPixels;
        screenWidth=dm.widthPixels;
        
        float screenHeightTemp=screenHeight;//��¼ϵͳ���ص���Ļ�ֱ��ʡ�
        float screenWidthTemp=screenWidth;
        
        if(screenHeightTemp>screenWidthTemp) //ָ����Ļ�Ŀ�͸ߡ�
        {
        	screenWidth=screenHeightTemp;
        	screenHeight=screenWidthTemp;
        }
        screenRatio=screenWidth/screenHeight;//��ȡ��Ļ�Ŀ�߱�
        if(Math.abs(screenRatio-screenRatio854x480)<0.01f)
        {
        	screenId=2;
       	}
        else if(Math.abs(screenRatio-screenRatio800x480)<0.01f)
        {
        	screenId=1;
        }
        else
        {
        	screenId=0;
        }
        
        
        mVibrator=(Vibrator)getApplication().getSystemService(Service.VIBRATOR_SERVICE);//����Ч
        
        initSounds();//��ʼ������

        screen_xoffset=(screenWidth-screenPictureWidth)/2;
        
        hd=new Handler() 
        {
        	@Override
        	public void handleMessage(Message msg)
        	{
        		super.handleMessage(msg);
        		switch(msg.what)
        		{
        		case ENTER_SOUND://�����������ƽ���
        			viewFlag=ENTER_SOUND;//��¼��ǰ���ڽ���
        			keyFlag=true;//���̿ɴ���
        			soundControl=new SoundControl(Activity_GL_Racing.this);//��������
        			setContentView(soundControl);//����Ϊ��ǰ����
        			soundControl.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        			soundControl.requestFocus();//��ȡ����
        		break;
        		case ENTER_MENU://������Ϸ�˵�����
        			viewFlag=ENTER_MENU;//��¼��ǰ���ڽ���
        			keyFlag=true;//���̿ɴ���
        			viewMainMenu=new ViewMainMenu(Activity_GL_Racing.this);//��������
        			setContentView(viewMainMenu);//����Ϊ��ǰ����
        			viewMainMenu.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        			viewMainMenu.requestFocus();//��ȡ����
        		break;
        		case ENTER_SET_VIEW://������Ϸ���ý���
        			viewFlag=ENTER_SET_VIEW;//��¼��ǰ���ڽ���
        			keyFlag=true;//���̿ɴ���
        			viewSet=new ViewSet(Activity_GL_Racing.this);//��������
        			setContentView(viewSet);//����Ϊ��ǰ����
        			viewSet.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        			viewSet.requestFocus();//��ȡ����
        		break;
        		case ENTER_HELP_VIEW://������Ϸ��������
        			viewFlag=ENTER_HELP_VIEW;//��¼��ǰ���ڽ���
        			keyFlag=true;//���̿ɴ���
        			viewHelp=new ViewHelp(Activity_GL_Racing.this);//��������
        			setContentView(viewHelp);//����Ϊ��ǰ����
        			viewHelp.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        			viewHelp.requestFocus();//��ȡ����
        		break;
        		case ENTER_ABOUT_VIEW://������ڽ���
        			viewFlag=ENTER_ABOUT_VIEW;//��¼��ǰ���ڽ���
        			keyFlag=true;//���̿ɴ���
        			viewAbout=new ViewAbout(Activity_GL_Racing.this);
        			setContentView(viewAbout);
        			viewAbout.setFocusableInTouchMode(true);
        			viewAbout.requestFocus();
        		break;
        		case START_GAME://������Ϸ����
        			viewFlag=START_GAME;//��¼��ǰ���ڽ���
        	        mGLSurfaceView = new MyGLSurfaceView(Activity_GL_Racing.this);
        	        setContentView(mGLSurfaceView); 
        	        mGLSurfaceView.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        	        mGLSurfaceView.requestFocus();//��ȡ����
        		break;
        		case LOADING://������ؽ���
        			viewFlag=LOADING;//��¼��ǰ���ڽ���
        			keyFlag=false;//���̲��ɴ��ء�
        			loading=new ViewLoading(Activity_GL_Racing.this);
        			setContentView(loading);        			
        			loading.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        			loading.requestFocus();//��ȡ����
        			
        			new Thread()
        			{
        				public void run()
        				{
        					MyGLSurfaceView.loadObjectVertex();
        					toAnotherView(START_GAME);//������Ϸ���� 
        				}
        			}.start();
        			
					
        		break;
        		case OVER:
        			viewFlag=OVER;//��¼��ǰ���ڽ���
        			over=new ViewOver(Activity_GL_Racing.this);//��������
        			setContentView(over);//����Ϊ��ǰ����
        			over.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        			over.requestFocus();//��ȡ����
        		break;
        		case CHOOSE:
        			viewFlag=CHOOSE;
        			choose=new ViewChoose(Activity_GL_Racing.this);//��������
        			setContentView(choose);//����Ϊ��ǰ����
        			choose.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        			choose.requestFocus();//��ȡ����
        		break;
        		case HISTORY:
        			viewFlag=HISTORY;
        			history=new ViewHistory(Activity_GL_Racing.this);//��������
        			setContentView(history);//����Ϊ��ǰ����
        			history.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        			history.requestFocus();//��ȡ����
        		break;
        		case BREAKING:
        			viewFlag=BREAKING;
        			breaking=new ViewBreaking(Activity_GL_Racing.this);//��������
        			setContentView(breaking);//����Ϊ��ǰ����
        			breaking.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        			breaking.requestFocus();//��ȡ����
					new Thread()
					{
						public void run()
						{
							try  
							{
								Thread.sleep(1000);
							}
							catch(Exception e)
							{
								e.printStackTrace();
							}
							toAnotherView(OVER);//������Ϸ���� 
						}
					}.start();
        		break;
        		case STRIVE:
        			viewFlag=STRIVE;
        			strive=new ViewTry(Activity_GL_Racing.this);//��������
        			setContentView(strive);//����Ϊ��ǰ����
        			strive.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        			strive.requestFocus();//��ȡ����
					new Thread()
					{
						public void run()
						{
							try 
							{
								Thread.sleep(1000);
							}
							catch(Exception e)
							{
								e.printStackTrace();
							}
							toAnotherView(OVER);//������Ϸ���� 
						}
					}.start();
        		break;
        		}
        	}
        };
        
        viewFlag=START_VIEW;//��¼��ǰ���ڽ���
        viewStart=new ViewStart(this);
        setContentView(viewStart);//���뿪ʼ����
        
        //=========================sensor begin============================
		//���SensorManager����
            mySensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);
        //=========================sensor end==============================
        
 
    } 
    
    @Override  
    protected void onResume() {
        super.onResume();
        mySensorManager.registerListener(			//ע�������
				mySensorListener, 					//����������
				SensorManager.SENSOR_ORIENTATION,	//����������
				SensorManager.SENSOR_DELAY_UI		//�������¼����ݵ�Ƶ��
				);      
        
    	if(soundFlag&&inGame)//��������
    	{
        	mpBack.start();
    	}
    	pauseFlag=false;
    	MyGLSurfaceView.keyState=0;//����״̬���� 
    } 

    @Override
    protected void onPause() {
        super.onPause();
        mySensorManager.unregisterListener(mySensorListener);	//ȡ��ע�������
        
        pauseFlag=true;
    	if(soundFlag)//��������
    	{
        	mpBack.pause();
    	}
    	MyGLSurfaceView.keyState=0;//����״̬����
    } 
     
    public void initSounds()
    {
    	mpBack=MediaPlayer.create(this,R.raw.backsound); 
    	mpBack.setLooping(true);//ѭ������
    	soundPool=new SoundPool 
    	(
    			4,
    			AudioManager.STREAM_MUSIC,
    			100
    	); 
    	soundPoolMap=new HashMap<Integer,Integer>();
    	soundPoolMap.put(1,soundPool.load(this, R.raw.lightsound1, 1));//���̵���Ч
    	soundPoolMap.put(2,soundPool.load(this, R.raw.shache, 1));//ɲ����Ч
    	soundPoolMap.put(3,soundPool.load(this, R.raw.jianyou, 1));//��������Ч
    	soundPoolMap.put(4,soundPool.load(this, R.raw.cartisu, 1));//��������Ч
    	soundPoolMap.put(6,soundPool.load(this, R.raw.zhuangche, 1));//ײ����Ч
    	soundPoolMap.put(7,soundPool.load(this, R.raw.gotobject, 1));//�Ӽ�����Ч
    	soundPoolMap.put(8,soundPool.load(this, R.raw.lightsound2, 1));//���̵���Ч
    	
    }
    
    public void playSound(int soundId,int Loop)
    {
    	if(pauseFlag)return;
    	
    	AudioManager mgr=(AudioManager) this.getSystemService(AUDIO_SERVICE); 
    	float volumnCurr=mgr.getStreamVolume(AudioManager.STREAM_MUSIC);
    	float volumnMax=mgr.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
    	float volumn=volumnCurr/volumnMax;
    	
    	if(soundId==1||soundId==8)
    	{
    		soundPool.play(soundPoolMap.get(soundId), volumn, volumn, 1, Loop, 1f);
    	}
    	else
    	{
    		soundPool.play(soundPoolMap.get(soundId), volumn, volumn, 1, Loop, 0.5f);
    	}
    }
    
    public void toAnotherView(int flag)
    {
    	switch(flag) 
    	{
    	case 0:hd.sendEmptyMessage(ENTER_SOUND);break;//���ͽ�������ѡ��������Ϣ
    	case 1:hd.sendEmptyMessage(ENTER_MENU);break;//���ͽ������˵��������Ϣ
    	case 2:hd.sendEmptyMessage(ENTER_SET_VIEW);break;//���ͽ������ý������Ϣ
    	case 3:hd.sendEmptyMessage(ENTER_HELP_VIEW);break;//���ͽ�������������Ϣ
    	case 4:hd.sendEmptyMessage(ENTER_ABOUT_VIEW);break;//������Ϣ������ڽ������Ϣ
    	case 5:hd.sendEmptyMessage(START_GAME);break;//������Ϣ������Ϸ����
    	case 6:hd.sendEmptyMessage(LOADING);break;//������Ϣ������ؽ���
    	case 8:hd.sendEmptyMessage(OVER);break;//������Ϣ�����������
    	case 9:hd.sendEmptyMessage(CHOOSE);break;//������Ϣ����ѡ����� 
    	case 10:hd.sendEmptyMessage(HISTORY);break;//������Ϣ������ʷ����
    	case 11:hd.sendEmptyMessage(BREAKING);break;//������Ϣ�����Ƽ�¼��ʾ����
    	case 12:hd.sendEmptyMessage(STRIVE);break;//������Ϣ�����ٽ�������ʾ����
    	}
    }
    
    //���ؼ�����
    public boolean onKeyDown(int keyCode,KeyEvent e)
    {
    	if(keyFlag==false)
    	{
    		return true;
    	}  
    	if(keyCode==4)//���ؼ�����
    	{ 
    		switch(viewFlag)
    		{
    		case ENTER_SET_VIEW:
    		case ENTER_SOUND:
    		case OVER:
    		case CHOOSE:
    			toAnotherView(ENTER_MENU);//�����ý�����������ý���ͽ������水���ؼ������ص����˵�����
    		break;
    		case ENTER_HELP_VIEW:
    			if(ViewHelp.viewFlag==0)
    			{
    				toAnotherView(ENTER_MENU);//�������˵�
    				ViewHelp.hvt.flag=false;//�ر��߳�
    			}
    			else if(ViewHelp.viewFlag==1)
    			{
    				ViewHelp.viewFlag=0;
    			}
    			else if(ViewHelp.viewFlag==2)
    			{ 
    				ViewHelp.viewFlag=1;
    			} 
    			else if(ViewHelp.viewFlag==3)
    			{
    				ViewHelp.viewFlag=2;
    			}     			
    			else if(ViewHelp.viewFlag==4)
    			{
    				ViewHelp.viewFlag=3;
    			}   
    			else if(ViewHelp.viewFlag==5)
    			{
    				ViewHelp.viewFlag=4;
    			}
    			else if(ViewHelp.viewFlag==6)
    			{
    				ViewHelp.viewFlag=5;
    			}
    		break;
    		case ENTER_ABOUT_VIEW:
    			if(ViewAbout.viewFlag==0)
    			{
    				toAnotherView(ENTER_MENU);//�������˵�
    				ViewAbout.avt.flag=false;
    			} 
    			else if(ViewAbout.viewFlag==1)
    			{
    				ViewAbout.viewFlag=0;
    			}
    		break;
    		case HISTORY:
    			toAnotherView(CHOOSE);//���ص�ѡ����� 
    		break;
    		case BREAKING:
    		case STRIVE:
    			toAnotherView(OVER);//���ص���������
    		break;
    		case ENTER_MENU://�����˵������ؼ����˳���Ϸ
    			System.exit(0);
    		break;
    		}
    		return true;
    	}
    	return false;
    }
    
  //����
    public void vibrator()
    {
    	mVibrator.vibrate(new long[]{100,10,100,1000}, -1);
    }
}