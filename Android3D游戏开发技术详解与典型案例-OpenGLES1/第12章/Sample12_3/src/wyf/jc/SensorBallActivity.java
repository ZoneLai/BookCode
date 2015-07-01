package wyf.jc;

import org.openintents.sensorsimulator.hardware.SensorManagerSimulator;

import android.app.Activity;
import android.hardware.SensorListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.view.Window;
import android.view.WindowManager;

public class SensorBallActivity extends Activity {
	
	//=========================sensor begin============================
	//SensorManager��������
	//SensorManager mySensorManager;	
	//ʹ��SensorSimulatorģ��ʱ����SensorSensorManager�������õķ���
	SensorManagerSimulator mySensorManager;	
	//=========================sensor end==============================
	
	static int bx;
	static int by;
	
	MyGameView msv;
	//����ʵ����SensorEventListener�ӿڵĴ�����������
	private SensorListener mySensorListener = new SensorListener(){
		@Override
		public void onAccuracyChanged(int sensor, int accuracy) 
		{	
		}
		@Override
		public void onSensorChanged(int sensor, float[] values) 
		{
			if(sensor == SensorManager.SENSOR_ORIENTATION)
			{//�ж��Ƿ�Ϊ���ٶȴ������仯����������	
				int directionDotXY[]=RotateUtil.getDirectionDot
				(
						new double[]{values[0],values[1],values[2]}
			    );
				//��׼��xyλ����
				double mLength=directionDotXY[0]*directionDotXY[0]+
				            directionDotXY[1]*directionDotXY[1];
				mLength=Math.sqrt(mLength);
				msv.dx=(int)((directionDotXY[0]/mLength)*msv.dLength);
				msv.dy=(int)((directionDotXY[1]/mLength)*msv.dLength);
			}	
		}		
	};
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        //ȫ��
		requestWindowFeature(Window.FEATURE_NO_TITLE); 
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN ,  
		              WindowManager.LayoutParams.FLAG_FULLSCREEN);		
		
		//=========================sensor begin============================
		//���SensorManager����
        //mySensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);	        
        
        //ʹ��SensorSimulatorģ��ʱ����SensorSensorManager�������õķ���
        mySensorManager = SensorManagerSimulator.getSystemService(this, SENSOR_SERVICE);
        mySensorManager.connectSimulator();
        //=========================sensor end==============================
        
        msv = new MyGameView(this);
        this.setContentView(msv);       
        
    }
    
	@Override
	protected void onResume() {						//��дonResume����
		mySensorManager.registerListener(			//ע�������
				mySensorListener, 					//����������
				SensorManager.SENSOR_ORIENTATION,	//����������
				SensorManager.SENSOR_DELAY_UI		//�������¼����ݵ�Ƶ��
				);
		msv.gvdt.pauseFlag=false;
		msv.ballX=bx;
		msv.ballY=by;
		super.onResume();
	}
	
	@Override
	protected void onPause() {									//��дonPause����
		mySensorManager.unregisterListener(mySensorListener);	//ȡ��ע�������
		msv.gvdt.pauseFlag=true;
		bx=msv.ballX;
		by=msv.ballY;
		super.onPause();
	}
}