package guo.com.baiduditu;

import android.app.Application;
import android.util.Log;
import android.widget.Toast;

import com.baidu.mapapi.*;
//���������
public class BMapApp extends Application {	
	static BMapApp mDemoApp;
	//�ٶ�MapAPI�Ĺ�����
	BMapManager mBMapMan = null;
	
	// ��ȨKey
	// TODO: ����������Key,
	// �����ַ��http://dev.baidu.com/wiki/static/imap/key/
	String mStrKey = "5288097969F6ABF9F9C2FAAE9ED0C8F438BC4AFD";
	// ��ȨKey��ȷ����֤ͨ��
	boolean m_bKeyRight = true;	
	
	// �����¼���������������ͨ�������������Ȩ��֤�����
	static class MyGeneralListener implements MKGeneralListener {
		@Override
		public void onGetNetworkState(int iError) {
			Log.d("MyGeneralListener", "onGetNetworkState error is "+ iError);
			Toast.makeText(BMapApp.mDemoApp.getApplicationContext(), "���������������",
					Toast.LENGTH_LONG).show();
		}
		@Override
		public void onGetPermissionState(int iError) {
			Log.d("MyGeneralListener", "onGetPermissionState error is "+ iError);
			if (iError ==  MKEvent.ERROR_PERMISSION_DENIED) {
				// ��ȨKey����
				Toast.makeText(BMapApp.mDemoApp.getApplicationContext(), 
						"����BMapApiDemoApp.java�ļ�������ȷ����ȨKey��",
						Toast.LENGTH_LONG).show();
				BMapApp.mDemoApp.m_bKeyRight = false;
			}
		}
	}

	@Override
    public void onCreate() {
		Log.v("BMapApiDemoApp", "onCreate");
		mDemoApp = this;
		mBMapMan = new BMapManager(this);
		boolean isSuccess = mBMapMan.init(this.mStrKey, new MyGeneralListener());
		// ��ʼ����ͼsdk�ɹ������ö�λ����ʱ��
		if (isSuccess) {
		    mBMapMan.getLocationManager().setNotifyInternal(10, 5);
		}
		else {
		    // ��ͼsdk��ʼ��ʧ�ܣ�����ʹ��sdk
		}	
		super.onCreate();
	}

	@Override
	//��������app���˳�֮ǰ����mapadpi��destroy()�����������ظ���ʼ��������ʱ������
	public void onTerminate() {
		// TODO Auto-generated method stub
		if (mBMapMan != null) {
			mBMapMan.destroy();
			mBMapMan = null;
		}
		super.onTerminate();
	}
}