package wyf.jsc.tdb;
import java.net.Socket;
import java.util.HashMap;
import android.app.Activity;
import android.content.Context;
import android.content.pm.ActivityInfo;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.media.SoundPool;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import static wyf.jsc.tdb.Constant.*;


public class MyActivity extends Activity {  
		
	///////////////////////////////////////////////
	Button mButtonOk;
	Button  mButtonEnter;
	EditText mEditTextIp;
	EditText mEditTextSocket;
	EditText mEditTextPlayer;
   	private String mStr;
	private int port;
	ClientThread ct;
	Socket sc=null;
	boolean netFlag=false;
	//////////////////////////////////////////////
	Handler hd;//��Ϣ������
	SoundControl isound;		//������ʾ����
	MenuView menuView;			//���˵�����
	AboutView aboutView;		//���ڲ˵�	
	HelpView helpView;   		//�����˵�
	SetupView setupView; 		//���ò˵�
	MySurfaceView surfaceView;   //��Ϸ����
	SelectView selectView;
	LoadView loadView;
	WaitView waitView;
	OverView overView;			//��������
	WinView winView;			//��ʤ����
	LoseView loseView;			//ʧ�ܽ���
	MediaPlayer mpBack;//���ű�������
	//MediaPlayer mpWin;
	SoundPool soundPool;//���ֳ�
	HashMap<Integer,Integer> soundPoolMap;//������������ID���Զ�������ID��Map
	boolean isWin=false;
	int mainCode=-1;
	//GameActivity gameActivity;
	/** Called when the activity is first created. */
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        //����Ϊ����
    	this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        //����Ϊ����
    	//this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
    	
        //����ȫ��
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
        					WindowManager.LayoutParams.FLAG_FULLSCREEN);

        hd=new Handler()
        {

			@Override
        	public void handleMessage(Message msg)
        	{
        		super.handleMessage(msg);
        		switch(msg.what)
        		{
        			case ENTER_SOUND://�����������ý���
        					isound=new SoundControl(MyActivity.this);
							isound.setFocusableInTouchMode(true);
							setContentView(isound); 
							isound.requestFocus();
							break;
        			case ENTER_MENU://����˵�����
        				    menuView=new MenuView(MyActivity.this);        				   
        				    menuView.setFocusableInTouchMode(true);
							setContentView(menuView);
							initSound();
							menuView.requestFocus();
							break;
        			case ENTER_HELP://�����������
        					helpView=new HelpView(MyActivity.this);
        					helpView.setFocusableInTouchMode(true);
        					setContentView(helpView);  
        					helpView.requestFocus();
        					break;
        			case ENTER_ABOUT://������ڽ���
        					aboutView=new AboutView(MyActivity.this);
        					aboutView.setFocusableInTouchMode(true);
        					setContentView(aboutView);  
        					aboutView.requestFocus();
        					break;
        			case START_ONE://����ѡ�����
	    					selectView=new SelectView(MyActivity.this);	    					
	    					setContentView(selectView);
	    					selectView.setFocusableInTouchMode(true);
	    					selectView.requestFocus();	    					
	    				    break;
	        		case START_LOAD:	//������ؽ���
	        			    netFlag=false;
	    					loadView=new LoadView(MyActivity.this);
	    					loadView.setFocusableInTouchMode(true);
	    					setContentView(loadView);
	    					loadView.requestFocus();
	    					surfaceView=new MySurfaceView(MyActivity.this);
	    					new Thread()//�����߳�
	    					{
	    						public void run()
	    						{
	    							try{
	    								sleep(2000);
	    							}
	    							catch(Exception e)
	    							{
	    								e.printStackTrace();
	    							}
	    							
	    								toAnotherView(START_GAME);//���뿪ʼ��Ϸ����
	    								
	    						}
	    					}.start();
	    					break;
	        		case ENTER_WIN://��ʤ����
	        				winView=new WinView(MyActivity.this);
	        				winView.setFocusableInTouchMode(true);
	        				setContentView(winView);
	        				winView.requestFocus();	        				
	    					toAnotherView(ENTER_OVER);
	        				break;
        			case ENTER_SETUP://���ý���
        					setupView=new SetupView(MyActivity.this);
        					setupView.setFocusableInTouchMode(true);
        					setContentView(setupView);
        					setupView.requestFocus();
        					break;
        			case START_GAME:     //��ʼ��Ϸ   	����			
        				surfaceView.setFocusableInTouchMode(true); 
        				setContentView(surfaceView);
        				surfaceView.requestFocus();
        				break;
        			case ENTER_WAIT://�ȴ�����
        				waitView=new WaitView(MyActivity.this);
        				waitView.setFocusableInTouchMode(true);
        				setContentView(waitView);
        				waitView.requestFocus();
        				surfaceView=new MySurfaceView(MyActivity.this);
        				break;
        			case ENTER_NET://�������ý���
        				    setContentView(R.layout.main);
        				    mButtonOk=(Button)findViewById(R.id.Button01);
        			        mEditTextIp=(EditText)findViewById(R.id.EditText01);
        			        mEditTextSocket=(EditText)findViewById(R.id.EditText02);
        			        
        		        	 //��½,����waiting����
        		            mButtonOk.setOnClickListener
        		             (
        		             		new OnClickListener()
        		             		{
        		        					@Override
        		        					public void onClick(View v) {
        		        						// TODO Auto-generated method stub
        		        						port=0;
        		        						try
        		        						{
        		        							mStr=mEditTextIp.getText().toString().trim();//���IP��ַ
        		        							port=Integer.parseInt(mEditTextSocket.getText().toString().trim());//��ö˿ں�
        		        						}catch(NumberFormatException ea)
        		        						{
        		        							Toast.makeText(MyActivity.this, "�˿ںű���Ϊ����", Toast.LENGTH_SHORT).show();
        		        							ea.printStackTrace();
        		        							return;
        		        						}
        		        						if(port<0||port>65535)//Port�Ƿ��ڷ�Χ��
        		        						{
        		        							Toast.makeText//��ʾ��Ϣ
        		        							(
        		        									MyActivity.this, 
        		        									"�˿ںű�����0~65535֮��", 
        		        									Toast.LENGTH_SHORT
        		        							).show();
        		        							return;
        		        						}
        		        						Socket sc=null;//��������
        		        					    try
        		        					    {
        		        					    	sc=new Socket(mStr,port); //��������
        		        					    	ct=new ClientThread(MyActivity.this,sc);
        		        					    }catch(Exception ea)
        		        					    {
        		        					    	Toast.makeText//��ʾ��Ϣ
        		        							(
        		        									MyActivity.this, 
        		        									"����ʧ��", 
        		        									Toast.LENGTH_SHORT
        		        							).show();
        		        					    	ea.printStackTrace();	
        		        					    	return;
        		        					    }        		        					    
        		        					    ct.start();	        //�����߳�		        					    
        		        					    mButtonOk.setClickable(false);//��������ٴε��
        		        					}
        		             		}
        		             );        		                   		     
        		             netFlag=true;
        		       break;
        			case ENTER_OVER://��������
        				overView=new OverView(MyActivity.this);
        				overView.setFocusableInTouchMode(true);
        				setContentView(overView);
        				overView.requestFocus();
        				break;
        			case ENTER_LOSE://ʧ�ܽ���
        				loseView=new LoseView(MyActivity.this);
        				loseView.setFocusableInTouchMode(true);
        				setContentView(loseView);
        				loseView.requestFocus();
        				new Thread()
    					{
    						public void run()
    						{
    							try
    							{
    								sleep(8000);
    							}catch(Exception e)
    							{
    								e.printStackTrace();
    							}
    						}
    					};
    					toAnotherView(ENTER_OVER);
        				break;
        			case USER_FULL://�����������
        				Toast.makeText
						(
								MyActivity.this, 
								"��ǰ�û����������Ժ�����", 
								Toast.LENGTH_SHORT
						).show();
        			break;
        		}
        	}
        };
       
        StartView startView=new StartView(this);//��ʼ����
        this.setContentView(startView);
        
        new Thread()
        {
        	public void run()
        	{
        		waitTwoSeconds();
        		hd.sendEmptyMessage(ENTER_SOUND);
        	}        	
        }.start();
    }
	public void waitTwoSeconds()
    {
		try {
				Thread.sleep(6000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}  
    }
    public void toAnotherView(int flag)
    {
    	switch(flag)
    	{
    	case 0:break;
    	case 1:hd.sendEmptyMessage(ENTER_MENU);break;    	//���˵�
    	case 2:hd.sendEmptyMessage(ENTER_HELP);break;		//����
    	case 3:hd.sendEmptyMessage(ENTER_ABOUT);break;		//����
    	case 4:hd.sendEmptyMessage(START_ONE);break;		//���뿪ʼѡ�����  
   		case 5:hd.sendEmptyMessage(START_LOAD);break;		//Loading���� 	
    	case 6:hd.sendEmptyMessage(ENTER_SETUP);break;		//����
    	case 7:hd.sendEmptyMessage(ENTER_WIN);break;		//ʤ��
    	case 8:hd.sendEmptyMessage(START_GAME);break;		//��ʼ��Ϸ
    	case 9:hd.sendEmptyMessage(ENTER_WAIT);break;		//�ȴ�����
    	case 10:hd.sendEmptyMessage(ENTER_NET);break;		//�������ý���
    	case 11:hd.sendEmptyMessage(ENTER_OVER);break;		//��������
    	case 12:hd.sendEmptyMessage(ENTER_LOSE);break;		//ʧ�ܽ���
    	}  
    }
    protected void initSound() 
    {
    	if(mpBack==null)//����������δ����
    	{
    		mpBack=MediaPlayer.create(this,R.raw.backsound);//������������
        	mpBack.setLooping(true);//����Ϊѭ��
    		if(soundFlag)		//���ű������ֱ�־λ
    		{
    			mpBack.start();//���ű�������
    		}
        	//���ֳ� 
        	soundPool=new SoundPool(10,AudioManager.STREAM_MUSIC,100);
        	soundPoolMap=new HashMap<Integer,Integer>();
        	//���ֵ�����
        	soundPoolMap.put(1,soundPool.load(this,R.raw.start,1));
        	//������ײ������
        	soundPoolMap.put(2, soundPool.load(this,R.raw.hit,1));
        	//�����ײ,�����������
        	soundPoolMap.put(3,soundPool.load(this,R.raw.ballin,1));
    	}
	}
	public void playSound(int sound, int loop) 
    {
	    if(pauseFlag){return;}
		AudioManager mgr = (AudioManager)this.getSystemService(Context.AUDIO_SERVICE);   
	    float streamVolumeCurrent = mgr.getStreamVolume(AudioManager.STREAM_MUSIC);   
	    float streamVolumeMax = mgr.getStreamMaxVolume(AudioManager.STREAM_MUSIC);       
	    float volume = streamVolumeCurrent / streamVolumeMax;    
	    soundPool.play(soundPoolMap.get(sound), volume, volume, 1, loop, 0.5f);
    }
	@Override
    public void onResume()
    {
    	super.onResume();//���ø��෽��
    	if(soundFlag)
    	{
    		mpBack.start();//��ʼ���ű�������
    	}	
    	pauseFlag=false;    	
    }
	@Override
    public void onPause()
    {
		pauseFlag=true;		
    	super.onPause(); 
    	if(soundFlag)
    	{
    		mpBack.pause();
    	}
    } 
	@Override
	public boolean onKeyDown(int keyCode,KeyEvent e)//��д�����·���
	{
		if(keyCode==4)//���·��ؼ�
		{
		    hd.sendEmptyMessage(START_ONE);	//����ѡ�����
			return true;
		}
		return false;//��ʾ������ϵͳ�ķ��ع���
	}
}






