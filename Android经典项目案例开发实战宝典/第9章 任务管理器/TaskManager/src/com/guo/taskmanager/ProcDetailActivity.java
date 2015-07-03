package com.guo.taskmanager;

import java.lang.reflect.Method;
import android.app.Activity;
import android.app.ActivityManager;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.IPackageStatsObserver;
import android.content.pm.PackageManager;
import android.content.pm.PackageStats;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;
//������ϸ��Ϣ����
public class ProcDetailActivity extends Activity {
	private static final String ATTR_PACKAGE_STATS="PackageStats";	
	private DetailProgramUtil processInfo = null;
	private static TextView textProcessName = null;
	private static TextView textProcessVersion = null;
	private static TextView textInstallDir = null;
	private static TextView textDataDir = null;
	private static TextView textPkgSize = null;
	private static TextView textPermission = null;
	private static TextView textService = null;
	private static TextView textActivity = null;
	private static Button btnKillProcess = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.proc_detail);
		//��ý���Ԫ��
		//��������
		textProcessName = (TextView)findViewById(R.id.detail_process_name);
		//����汾
		textProcessVersion = (TextView)findViewById(R.id.detail_process_copyright);
		//��װĿ¼
		textInstallDir = (TextView)findViewById(R.id.detail_process_install_dir);
		//����Ŀ¼
		textDataDir = (TextView)findViewById(R.id.detail_process_data_dir);
		//����С��Ϣ
		textPkgSize = (TextView)findViewById(R.id.detail_process_package_size);
		//Ȩ����Ϣ
		textPermission = (TextView)findViewById(R.id.detail_process_permission);
		//������Ϣ
		textService = (TextView)findViewById(R.id.detail_process_service);
		//Activity��Ϣ
		textActivity = (TextView)findViewById(R.id.detail_process_activity);
		//ǿ�ƽ�������
		btnKillProcess = (Button)findViewById(R.id.btn_kill_process);
		//�󶨼�����
		btnKillProcess.setOnClickListener(new KillButtonListener());
		//��ô��ݹ���������
		Intent intent = getIntent();
		Bundle bundle= intent.getExtras();
		processInfo = (DetailProgramUtil) bundle.getSerializable("process_info");
		//����õ�������ʾ������
		showAppInfo();
	}
	//��ʾ������ϸ��Ϣ
	public void showAppInfo(){
		//���ó�������
		textProcessName.setText(processInfo.getProcessName());
		//���ó���װĿ¼
		textInstallDir.setText(processInfo.getSourceDir());
		//���ó���汾
		textProcessVersion.setText(
				getString(R.string.detail_process_company) + processInfo.getCompanyName()
				+ "  " + getString(R.string.detail_process_version) + processInfo.getVersionName()
				+ "(" + processInfo.getVersionCode() + ")");
		//��������Ŀ¼
		textDataDir.setText(processInfo.getDataDir());
		//����Ȩ��
		textPermission.setText(processInfo.getUserPermissions());
		//���÷�����Ϣ
		textService.setText(processInfo.getServices());
		//����Activity��Ϣ
		textActivity.setText(processInfo.getActivities());
		//���ð���С��Ϣ
		getpkginfo(processInfo.getPackageName());
	}
	//�������̰���������
	private class KillButtonListener implements OnClickListener {
		@Override
		public void onClick(View v) {
			//��û������
			ActivityManager activityManager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
			PackageUtil packageUtil = new PackageUtil(ProcDetailActivity.this);
			//����Ǳ������򲻽���
			if (processInfo.getProcessName().equals(R.string.my_package)) {
				Toast.makeText(ProcDetailActivity.this, "Canot Terminate Myself!", Toast.LENGTH_LONG).show();
				return;
			}
			//��ó������Ϣ��
			ApplicationInfo tempAppInfo = packageUtil.getApplicationInfo(processInfo.getProcessName());
			activityManager.killBackgroundProcesses(tempAppInfo.packageName);
			Toast.makeText(ProcDetailActivity.this, "Process is killed!", Toast.LENGTH_LONG).show();
		}
	}
		//���ڸ��½���ı����ݴ�����Ϣ
	 private Handler mHandler = new Handler() {
			public void handleMessage(Message msg) {
				switch (msg.what) {
				case 1:
					String infoString="";
					PackageStats newPs = msg.getData().getParcelable(ATTR_PACKAGE_STATS);
					if (newPs!=null) {
						infoString+="Ӧ�ó����С: "+formatFileSize(newPs.codeSize);
						infoString+="\n���ݴ�С: "+formatFileSize(newPs.dataSize);
						infoString+="\n�����С: "+formatFileSize(newPs.cacheSize);
					}
					textPkgSize.setText(infoString);
					break;
				default:
					break;
				}
			}
			};
	//���÷�����ƻ�ó���İ���С��Ϣ
			//ʹ����ͨ��ʽ���ò������Ĵ�С��Ϣ
	public void getpkginfo(String pkg){
		PackageManager pm = getPackageManager();
		try {
			Method getPackageSizeInfo = pm.getClass()
			.getMethod("getPackageSizeInfo", String.class,
					IPackageStatsObserver.class);
			getPackageSizeInfo.invoke(pm, pkg,
			new PkgSizeObserver());
		} catch (Exception e) {
			// TODO: handle exception
		}
	}
	//ʹ��AIDLʵ�ֽ��̼�ͨ�ţ���������Ϣ���͸�mHandler
	class PkgSizeObserver extends IPackageStatsObserver.Stub {
  public void onGetStatsCompleted(PackageStats pStats, boolean succeeded) {
       Message msg = mHandler.obtainMessage(1);
       Bundle data = new Bundle();
       //������Ϣ��ŵ�data��
       data.putParcelable(ATTR_PACKAGE_STATS, pStats);
       msg.setData(data);
       mHandler.sendMessage(msg);
      
   }
}
	 //��ʽ���ļ���С��Ϣ
	public static String formatFileSize(long length) {
		String result = null;
		int sub_string = 0;
		//�ļ���GB��������
		if (length >= 1073741824) {
			sub_string = String.valueOf((float) length / 1073741824).indexOf(
					".");
			result = ((float) length / 1073741824 + "000").substring(0,
					sub_string + 3)
					+ "GB";
			//�ļ���MB��������
		} else if (length >= 1048576) {
			sub_string = String.valueOf((float) length / 1048576).indexOf(".");
			result = ((float) length / 1048576 + "000").substring(0,
					sub_string + 3)
					+ "MB";
			//�ļ���KB��������
		} else if (length >= 1024) {
			sub_string = String.valueOf((float) length / 1024).indexOf(".");
			result = ((float) length / 1024 + "000").substring(0,
					sub_string + 3)
					+ "KB";
			//�ļ���B��������
		} else if (length < 1024)
			result = Long.toString(length) + "B";
		return result;
	}
}
