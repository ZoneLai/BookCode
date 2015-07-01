package wyf.zcl;
import android.app.Activity;			//������ذ�
import android.media.AudioManager;		//������ذ�
import android.media.MediaPlayer;		//������ذ�
import android.os.Bundle;				//������ذ�
import android.view.View;				//������ذ�
import android.widget.Button;			//������ذ�
import android.widget.Toast;
public class MyActivity extends Activity {
    /** Called when the activity is first created. */
	private Button bPlay;					//���Ű�ť
	private Button bPause;					//��ͣ��ť
	private Button bStop;					//ֹͣ��ť
	private Button bAdd;					//��������
	private Button bReduce;					//��������
	private boolean pauseFlag=false;		//��ͣ��ǣ�true��̬ͣ��false����̬ͣ
	MediaPlayer mp;							//MediaPlayer����
	AudioManager am;						//AudioManager����
    @Override
    public void onCreate(Bundle savedInstanceState) {	//Activity����ʱ����
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);					//����Activity����ʾ����
        bPlay=(Button)findViewById(R.id.ButtonPlay);	//���Ű�ť��ʵ����
        bPause=(Button)findViewById(R.id.ButtonPause);	//��ͣ��ť��ʵ����
        bStop=(Button)findViewById(R.id.ButtonStop);	//ֹͣ��ť��ʵ����
        bAdd=(Button)findViewById(R.id.ButtonVAdd);		//����������ť��ʵ����
        bReduce	=(Button)findViewById(R.id.ButtonVReduce);//����������ť��ʵ����
        mp=new MediaPlayer();
        am=(AudioManager) this.getSystemService(this.AUDIO_SERVICE);
        bPlay.setOnClickListener(new View.OnClickListener() {//���Ű�ť�ļ�����
			@Override
			public void onClick(View v) {
				 try{
			        	mp.setDataSource("/sdcard/dl.mid");		//������Ƶ������Initialized״̬��
			        }catch(Exception e){e.printStackTrace();}
			        try{
			        	mp.prepare();							//����prepared״̬��
			        }catch(Exception e){e.printStackTrace();}
				mp.start();										//��������
				Toast.makeText(MyActivity.this, "��������", Toast.LENGTH_SHORT).show();
		}});
        bPause.setOnClickListener(new View.OnClickListener() {	//��ͣ��ť��Ӽ�����
			@Override
			public void onClick(View v) {
				if(mp.isPlaying()){								//������ڲ���̬
					mp.pause();									//������ͣ����
					pauseFlag=true;								//������ͣ���
				}else if(pauseFlag){
					mp.start();									//��������
					pauseFlag=false;							//������ͣ���
				Toast.makeText(MyActivity.this, "��ͣ����", Toast.LENGTH_SHORT).show();	
			}}
		});
        bStop.setOnClickListener(new View.OnClickListener() {	//ֹͣ��ť��Ӽ�����
			@Override
			public void onClick(View v) {
				mp.stop();										//ֹͣ����
			     mp.reset();									//����״̬��uninitialized̬
			     try{
			        	mp.setDataSource("/sdcard/dl.mid");		//������Ƶ������Initialized״̬��
			     }catch(Exception e){e.printStackTrace();}
			        try{
			        	mp.prepare();							//����prepared״̬��
			        }catch(Exception e){e.printStackTrace();}
			        Toast.makeText(MyActivity.this, "ֹͣ����", Toast.LENGTH_SHORT).show();
		}});
        bAdd.setOnClickListener(new View.OnClickListener() {	//��������ť��Ӽ�����
			@Override
			public void onClick(View v) {
			am.adjustVolume(AudioManager.ADJUST_RAISE, 0);		//��������
			System.out.println("faaa");
			Toast.makeText(MyActivity.this, "��������", Toast.LENGTH_SHORT).show();
		}});
        bReduce.setOnClickListener(new View.OnClickListener() {	//�������Ͱ�ť��Ӽ�����
			@Override
			public void onClick(View v) {
			am.adjustVolume(AudioManager.ADJUST_LOWER, 0);		//��С����
			Toast.makeText(MyActivity.this, "��С����", Toast.LENGTH_SHORT).show();
		}});
    }
}