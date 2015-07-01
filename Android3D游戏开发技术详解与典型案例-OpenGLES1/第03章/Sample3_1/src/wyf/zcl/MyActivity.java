package wyf.zcl;

import java.util.HashMap;

import android.app.Activity;
import android.media.AudioManager;
import android.media.SoundPool;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class MyActivity extends Activity {
    /** Called when the activity is first created. */
	SoundPool sp;							//�õ�һ������������
	HashMap<Integer,Integer> spMap;			//�õ�һ��map������
	Button b1;								//�������ſ��ư�ť
	Button b1Pause;								//������ͣ���ư�ť
    Button b2;								//�������ſ��ư�ť
    Button b2Pause;								//������ͣ���ư�ť
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        initSoundPool();						//��ʼ��������
        b1=(Button)findViewById(R.id.Button01);//�������ſ��ư�ťʵ����
        b2=(Button)findViewById(R.id.Button02);//�������ſ��ư�ťʵ����
        b1Pause=(Button)findViewById(R.id.Button1Pause);
        b2Pause=(Button)findViewById(R.id.Button2Pause);
        b1.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				playSound(1,1);		//���ŵ�һ����Ч��ѭ��һ��
				Toast.makeText(MyActivity.this, "������Ч1", Toast.LENGTH_SHORT).show();
		}});
        b1Pause.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				sp.pause(spMap.get(1));
				Toast.makeText(MyActivity.this, "��ͣ��Ч1", Toast.LENGTH_SHORT).show();
		}});
        b2.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				playSound(2,1);		//���ŵڶ�����Ч��ѭ��һ��
			Toast.makeText(MyActivity.this, "������Ч2", Toast.LENGTH_SHORT).show();
		}});
        b2Pause.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View v) {
				sp.pause(spMap.get(2));
				Toast.makeText(MyActivity.this, "��ͣ��Ч2", Toast.LENGTH_SHORT).show();
		}});
    }
    public void initSoundPool(){			//��ʼ��������
    	sp=new SoundPool(
    			5, 				//maxStreams�������ò���Ϊ����ͬʱ�ܹ����Ŷ�����Ч
    			AudioManager.STREAM_MUSIC,	//streamType�������ò���������Ƶ���ͣ�����Ϸ��ͨ������Ϊ��STREAM_MUSIC
    			0				//srcQuality�������ò���������Ƶ�ļ���������Ŀǰ��û��Ч��������Ϊ0ΪĬ��ֵ��
    	);
    	spMap=new HashMap<Integer,Integer>();
    	spMap.put(1, sp.load(this, R.raw.attack02, 1));
    	spMap.put(2, sp.load(this, R.raw.attack14, 1));
    }
    public void playSound(int sound,int number){	//��������,����sound�ǲ�����Ч��id������number�ǲ�����Ч�Ĵ���
    	AudioManager am=(AudioManager)this.getSystemService(this.AUDIO_SERVICE);//ʵ����AudioManager����
    	float audioMaxVolumn=am.getStreamMaxVolume(AudioManager.STREAM_MUSIC);	//���ص�ǰAudioManager������������ֵ
    	float audioCurrentVolumn=am.getStreamVolume(AudioManager.STREAM_MUSIC);//���ص�ǰAudioManager���������ֵ
    	float volumnRatio=audioCurrentVolumn/audioMaxVolumn;
    	sp.play(
    			spMap.get(sound), 					//���ŵ�����id
    			volumnRatio, 						//����������
    			volumnRatio, 						//����������
    			1, 									//���ȼ���0Ϊ���
    			number, 							//ѭ��������0�޲�ѭ����-1����Զѭ��
    			1									//�ط��ٶ� ����ֵ��0.5-2.0֮�䣬1Ϊ�����ٶ�
    	);
    }
}