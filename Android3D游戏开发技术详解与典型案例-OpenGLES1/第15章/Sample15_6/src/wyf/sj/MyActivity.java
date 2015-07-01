package wyf.sj;

import java.util.HashMap;

import android.app.Activity;
import android.content.Context;
import android.media.AudioManager;
import android.media.SoundPool;
import android.os.Bundle;

public class MyActivity extends Activity {
    /** Called when the activity is first created. */
	MySurfaceView mGLSurfaceView;
	SoundPool soundPool;//������
	HashMap<Integer, Integer> soundPoolMap; //������������ID���Զ�������ID��Map	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGLSurfaceView = new MySurfaceView(this);
        mGLSurfaceView.requestFocus();//��ȡ����
        mGLSurfaceView.setFocusableInTouchMode(true);//����Ϊ�ɴ���
        initSound();
        setContentView(mGLSurfaceView);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mGLSurfaceView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        mGLSurfaceView.onPause();
    }
    public void initSound()
    {	
		//������
		soundPool = new SoundPool(4, AudioManager.STREAM_MUSIC, 100);
	    soundPoolMap = new HashMap<Integer, Integer>();   
	    
	    //�ڵ���ը��Ч
	    soundPoolMap.put(1, soundPool.load(this, R.raw.explode, 1));
    }
    
    public void playSound(int sound, int loop) 
    {
	    AudioManager mgr = (AudioManager)this.getSystemService(Context.AUDIO_SERVICE);   
	    float streamVolumeCurrent = mgr.getStreamVolume(AudioManager.STREAM_MUSIC);   
	    float streamVolumeMax = mgr.getStreamMaxVolume(AudioManager.STREAM_MUSIC);       
	    float volume = streamVolumeCurrent / streamVolumeMax;   
	    
	    soundPool.play(soundPoolMap.get(sound), volume, volume, 1, loop, 1f);
	}
}