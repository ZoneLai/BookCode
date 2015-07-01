package wyf.jc;			//���������
import org.openintents.sensorsimulator.hardware.SensorManagerSimulator;
import android.app.Activity;
import android.hardware.SensorListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.widget.TextView;
public class MyActivity extends Activity 
{
	
	//SensorManager mySensorManager;	//SensorManager��������
	
	SensorManagerSimulator mySensorManager;		//ʹ��SensorSimulatorģ����ʱ����SensorSensorManager�������õķ���
	
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
        
        //mySensorManager = (SensorManager)getSystemService(SENSOR_SERVICE);	//���SensorManager����       
        
        mySensorManager = SensorManagerSimulator.getSystemService(this, SENSOR_SERVICE);//ʹ��SensorSimulatorģ��ʱ����SensorSensorManager�������õķ���
        mySensorManager.connectSimulator();
    }
	@Override
	protected void onResume() {						//��дonResume����
		mySensorManager.registerListener(			//ע�������
				mySensorListener, 					//����������
				SensorManager.SENSOR_ORIENTATION,	//����������
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
		public void onAccuracyChanged(int sensor, int accuracy) 
		{	
		}
		public void onSensorChanged(int sensor, float[] values) 
		{
			if(sensor == SensorManager.SENSOR_ORIENTATION)
			{//�ж��Ƿ�Ϊ���ٶȴ������仯����������	
				//����ȡ��������ʾ��TextView
				tvX.setText("Pitch���ϵ���ת�Ƕ�Ϊ��"+values[0]);		
				tvY.setText("Yaw���ϵ���ת�Ƕ�Ϊ��"+values[1]);		
				tvZ.setText("Roll���ϵ���ת�Ƕ�Ϊ��"+values[2]);		
			}	
		}		
	};
}