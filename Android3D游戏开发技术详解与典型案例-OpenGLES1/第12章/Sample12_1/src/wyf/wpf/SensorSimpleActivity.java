package wyf.wpf;			//���������
import org.openintents.sensorsimulator.hardware.SensorManagerSimulator;
import android.app.Activity;
import android.hardware.SensorListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.TextView;
public class SensorSimpleActivity extends Activity 
{
	//SensorManager��������
	//SensorManager mySensorManager;	
	//ʹ��SensorSimulatorģ��ʱ����SensorSensorManager�������õķ���
	SensorManagerSimulator mySensorManager;		
	
	TextView tvX;	//TextView��������	
	TextView tvY;	//TextView��������	
	TextView tvZ;	//TextView��������	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        tvX = (TextView)findViewById(R.id.tvX);		
        tvY = (TextView)findViewById(R.id.tvY);		
        tvZ = (TextView)findViewById(R.id.tvZ);		
        
        //���SensorManager����
        //mySensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);	
        
        
        //ʹ��SensorSimulatorģ��ʱ����SensorSensorManager�������õķ���
        mySensorManager = SensorManagerSimulator.getSystemService(this, SENSOR_SERVICE);
        mySensorManager.connectSimulator();
    }
	@Override
	protected void onResume() {						//��дonResume����
		mySensorManager.registerListener(			//ע�������
				mySensorListener, 					//����������
				SensorManager.SENSOR_ACCELEROMETER,	//����������
				SensorManager.SENSOR_DELAY_UI		//�������¼����ݵ�Ƶ��
				);
		super.onResume();
	}	
	@Override
	protected void onPause() {									//��дonPause����
		mySensorManager.unregisterListener(mySensorListener);	//ȡ��ע�������
		super.onPause();
	}
	//����ʵ����SensorEventListener�ӿڵĴ�����������
	private SensorListener mySensorListener = new SensorListener(){
		@Override
		public void onAccuracyChanged(int sensor, int accuracy) 
		{	
		}
		@Override
		public void onSensorChanged(int sensor, float[] values) 
		{
			if(sensor == SensorManager.SENSOR_ACCELEROMETER)
			{//�ж��Ƿ�Ϊ���ٶȴ������仯����������	
				//����ȡ��������ʾ��TextView
				tvX.setText("x�᷽���ϵļ��ٶ�Ϊ��"+values[0]);		
				tvY.setText("y�᷽���ϵļ��ٶ�Ϊ��"+values[1]);		
				tvZ.setText("z�᷽���ϵļ��ٶ�Ϊ��"+values[2]);		
			}	
		}		
	};
}