package wyf.zcl;
import android.app.Activity;				//������ذ�
import android.os.Bundle;					//������ذ�
public class MyActivity extends Activity {
	MySurfaceView msv;						//MySurfaceView����
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);			
        msv=new MySurfaceView(this);		//ʵ����MySurfaceView����
        setContentView(msv);				//����Activity����
    }
}