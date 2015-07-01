package wyf.jsl.lb;


import static wyf.jsl.lb.Constant.*;

import java.util.HashMap;
import java.util.Map;
import android.app.Activity;
import android.content.pm.ActivityInfo;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;
import android.view.Window;
import android.view.WindowManager;

public class Activity_GL_Demo extends Activity {
    /** Called when the activity is first created. */
	static int flag;//�����־λ
	
	//��������������
	private SurfaceViewTag tagView;
	private SurfaceViewSound soundView; 
	private SurfaceViewMenu menuView;
	GLGameView myView;
	
	//������Ϣ����������
	Handler hd;
	//�����������ֲ��������ã���������õ�
	MediaPlayer mpBack;
	SoundPool soundPool;
	Map<Integer,Integer> soundPoolMap;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
          
        tagView=new SurfaceViewTag(this);//�Ҷ�����Ч�������ɣ��Ŷ�
        setContentView(tagView);
        
        initSounds();//��ʼ������
        
        hd=new Handler()//��Ϣ������
        {
        	@Override
        	public void handleMessage(Message msg)
        	{
        		super.handleMessage(msg);
        		switch(msg.what)
        		{
        		case GAME_SOUND:
        			flag=GAME_SOUND;
        			soundView=new SurfaceViewSound(Activity_GL_Demo.this);//�����ˣ������ھֲ��ڲ��ӿ���
        			setContentView(soundView);
        		break;
        		case GAME_MENU:
        			flag=GAME_MENU;
        			menuView=new SurfaceViewMenu(Activity_GL_Demo.this);
        			setContentView(menuView);
        		break;
        		case GAME_LOAD:
        			flag=GAME_LOAD;
        			//����
        			setContentView(R.layout.load);
					new Thread()
					{
						public void run()
						{
							try
							{
								Thread.sleep(3000);
							}
							catch(Exception e)
							{
								e.printStackTrace();
							}
							hd.sendEmptyMessage(GAME_START);
						}
					}.start();
				break;
        		case GAME_START:
        			//����
        			myView=new GLGameView(Activity_GL_Demo.this);
        			setContentView(myView);
        			myView.setFocusableInTouchMode(true); //�ɴ�������Ӧ���ڻ�ý���֮ǰ
        			myView.requestFocus();					
        		
        			new Thread()
					{
						boolean flag=true;//��־λ
						public void run()
						{
							while(flag)
							{
								if(Count>=MAX_COUNT) 
								{
									flag=false;
									extracted();
								}
								try {
									Thread.sleep(1000);
								} catch (InterruptedException e) {
									// TODO Auto-generated catch block
									e.printStackTrace();
								}
							}
						}

						private void extracted() {
							{
								myView.bgt.flag=false;
								myView.gtlt.flag=false;
								myView.gtwt.flag=false;
								myView.tl.flag=false;//�رչ�Դ��ת�߳�
								myView.xk.flag=false;//�ر��ǿ���ת�߳�
								myView.tm.flag=false;//�ر�����ת�߳�
								inGame=false;
								mpBack.pause();//ֹͣ������
								Count=0;
								hd.sendEmptyMessage(GAME_OVER);
							}
						}
					}.start();
					
        		break;
        		case GAME_OVER:
        			flag=GAME_OVER;
        			//����
        			SurfaceViewOver overView=new SurfaceViewOver(Activity_GL_Demo.this,myView);
        			setContentView(overView);
        		break;
        		case GAME_HELP:
        			flag=GAME_HELP;
        			//����
        			SurfaceViewHelp helpView=new SurfaceViewHelp(Activity_GL_Demo.this);
        			setContentView(helpView);
        		break;	
        		case GAME_ABOUT:
        			flag=GAME_ABOUT;
        			//����
        			SurfaceViewAbout aboutView=new SurfaceViewAbout(Activity_GL_Demo.this);
        			setContentView(aboutView);
        		break;	
        		}
        	}
        };
        
        
    }
   
    @Override
    public void onResume()
    {
    	super.onResume();
    	if(BACK_SOUND_FLAG&&inGame)//��������
    	{
        	mpBack.start();
    	}
    	pauseFlag=false;
    }
    public void onPause()
    {
    	pauseFlag=true;
    	super.onPause();   
    	if(BACK_SOUND_FLAG)//��������
    	{
        	mpBack.pause();
    	}
    }
   
    public void initSounds()
    {
    	mpBack=MediaPlayer.create(this,R.raw.seasound);
    	mpBack.setLooping(true);//ѭ������
    	soundPool=new SoundPool
    	(
    			4,
    			AudioManager.STREAM_MUSIC,
    			100
    	);
    	soundPoolMap=new HashMap<Integer,Integer>();
    	soundPoolMap.put(1,soundPool.load(this, R.raw.bulletsound, 1));//�����ڵ���Ч
    	soundPoolMap.put(2,soundPool.load(this, R.raw.explode, 1));//�ڵ���ը��Ч
    }
    
    public void playSound(int soundId,int Loop)
    {
    	if(pauseFlag)return;
    	
    	AudioManager mgr=(AudioManager) this.getSystemService(AUDIO_SERVICE);
    	float volumnCurr=mgr.getStreamVolume(AudioManager.STREAM_MUSIC);
    	float volumnMax=mgr.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
    	float volumn=volumnCurr/volumnMax;
    	
    	soundPool.play(soundPoolMap.get(soundId), volumn, volumn, 1, Loop, 0.5f);
    }
    
    public boolean onKeyDown(int keyCode,KeyEvent e)
    {
    	if(keyCode==4)
    	{
    		switch(flag)
    		{
    		case GAME_ABOUT:
    		case GAME_HELP:
    		case GAME_OVER:
    		case GAME_SOUND:
    			this.hd.sendEmptyMessage(GAME_MENU);
    			break;
    		case GAME_MENU:
    			System.exit(0);
    			break;
    		}
    		return true;
    	}
    	return false;
    }
}