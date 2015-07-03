package com.guo.taskmanager;
/**
 * ActivityManager.RunningAppProcessInfo {
 *     public int importance				// ������ϵͳ�е���Ҫ����
 *     public int importanceReasonCode		// ���̵���Ҫԭ�����
 *     public ComponentName importanceReasonComponent	// �����������������Ϣ
 *     public int importanceReasonPid		// ��ǰ���̵��ӽ���Id
 *     public int lru						// ��ͬһ����Ҫ�����ڵĸ�������ֵ
 *     public int pid						// ��ǰ����Id
 *     public String[] pkgList				// �����뵱ǰ���̵����а���
 *     public String processName			// ��ǰ���̵�����
 *     public int uid						// ��ǰ���̵��û�Id
 * }
 */
import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ListActivity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.os.Debug.MemoryInfo;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;

public class TaskManagerActivity extends ListActivity {
	
	// ��ȡ���������ͻ��������ʵ��
	private static PackageManager packageManager = null;
	private static ActivityManager activityManager = null;

	// �������еĽ����б�
	private static List<RunningAppProcessInfo> runningProcessList = null;
	private static List<ProgramUtil> infoList = null;
	//���ڻ��Ӧ�ó��������Ϣ
	private static PackageUtil packageUtil = null;
	
	// ��ѡ�еĽ�������
	private static RunningAppProcessInfo processSelected = null;	
	//ˢ�°�ť
	private static Button btnRefresh = null;
	//�������̰�ť
	private static Button btnCloseAll = null;
	
	// ���ں�̨ˢ���б���ʾˢ����ʾ
	private static RefreshHandler handler = null;
	// ������ʾˢ�½�����
	private static ProgressDialog pd = null;
	// ListView��������
	private static ProcListAdapter procListAdapter = null;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.proc_list);
        
        btnRefresh = (Button)findViewById(R.id.btn_refresh_process);
        btnRefresh.setOnClickListener(new RefreshButtonListener());
        btnCloseAll = (Button)findViewById(R.id.btn_closeall_process);
        btnCloseAll.setOnClickListener(new CloseAllButtonListener());
        
        // ��ȡ������������Ҫͨ������������ȡ�����ͼ��ͳ�����
    	packageManager = this.getPackageManager();
		activityManager = (ActivityManager) getSystemService(ACTIVITY_SERVICE);
		packageUtil = new PackageUtil(this);
        
		// ��ȡ�������еĽ����б�		
		runningProcessList = new ArrayList<RunningAppProcessInfo>();
    	infoList = new ArrayList<ProgramUtil>();
    	
        updateProcessList();
    }
    //��ý���ռ���ڴ���Ϣ
	public String getUsedMemory(int pid)
	{
		//��û������ʵ��
		ActivityManager am = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
		//����int����
		int[] pids = {pid};
		MemoryInfo[] memoryInfos =  am.getProcessMemoryInfo(pids);
		//��ý���ռ���ڴ�����������kBֵ
		int memorysize = memoryInfos[0].getTotalPrivateDirty();
		return "�ڴ�ռ��Ϊ "+ memorysize +" KB";
	}
    private void updateProcessList() {
    	// �½�һ�����ȶԻ�����ˢ���б�ʱ�������ڸ���ͼ֮��    	
    	pd = new ProgressDialog(TaskManagerActivity.this);
        pd.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        pd.setTitle(getString(R.string.progress_tips_title));
        pd.setMessage(getString(R.string.progress_tips_content));    
        // �������̣߳�ִ�и����б����
		handler = new RefreshHandler();
		RefreshThread thread = new RefreshThread();
		thread.start();	
		// ��ʾ���ȶԻ���
        pd.show();
    }
    
    private class RefreshHandler extends Handler {
    	@Override
		public void handleMessage(Message msg) {
			// ���½���
    		getListView().setAdapter(procListAdapter);
			// ȡ�����ȿ�
    		pd.dismiss();
		}
    }
    //���ڸ��½���Ľ���
    class RefreshThread extends Thread {
		@Override
		public void run() {
			// TODO : Do your Stuff here.
			procListAdapter = buildProcListAdapter();
			Message msg = handler.obtainMessage();
			handler.sendMessage(msg);
		}
	}
    //�б���������
	@Override
	protected void onListItemClick(ListView l, View v, int position, long id) {
		//��õ�ǰѡ�еĽ���
    	processSelected = runningProcessList.get(position);
    	//�½��Ի���
    	AlertButtonListener listener = new AlertButtonListener();
    	Dialog alertDialog = new AlertDialog.Builder(this)
    		.setIcon(android.R.drawable.ic_dialog_info)
    		.setTitle(R.string.please_select)
    		.setNegativeButton(R.string.kill_process, listener)
    		.setNeutralButton(R.string.info_detail, listener).create();
    	alertDialog.show();
    	super.onListItemClick(l, v, position, id);
	}
    
    private class AlertButtonListener implements 
    		android.content.DialogInterface.OnClickListener {
    	//��������
		@Override
		public void onClick(DialogInterface dialog, int which) {
			switch (which) {
			case Dialog.BUTTON_NEUTRAL:
				Intent intent = new Intent();
				intent.setClass(TaskManagerActivity.this, ProcDetailActivity.class);
				// Ϊѡ�еĽ��̻�ȡ��װ������ϸ��Ϣ
				DetailProgramUtil programUtil = buildProgramUtilComplexInfo(processSelected.processName);
				if (programUtil == null) {
					break;
				}
				Bundle bundle = new Bundle();
				// ʹ��Serializable��Activity֮�䴫�ݶ���
				bundle.putSerializable("process_info", (Serializable)programUtil);
				intent.putExtras(bundle);
				//�򿪽�����ϸ��Ϣ����
				startActivity(intent);				
				break;
			case Dialog.BUTTON_NEGATIVE:
				//��������
				closeOneProcess(processSelected.processName);
				//���½���
				updateProcessList();
				break;
			default:
				break;
			}
		}
    }
    //�����б�
    private class RefreshButtonListener implements android.view.View.OnClickListener {
		@Override
		public void onClick(View v) {
			updateProcessList();
		}
    }
    //�ر������û�����
    private class CloseAllButtonListener implements android.view.View.OnClickListener {
		@Override
		public void onClick(View v) {
			int count = infoList.size();
			ProgramUtil bpu = null;
			//�������н��̣�����ر�
			for (int i = 0; i < count; i++) {
				bpu = infoList.get(i);
				closeOneProcess(bpu.getProcessName());
			}
			//�����б�
			updateProcessList();
		}
    }
    //�ر�ָ������
    private void closeOneProcess(String processName) {
    	//��ֹ�û�����������
		if (processName.equals(R.string.my_package)) {		
			Toast.makeText(TaskManagerActivity.this, "Canot Terminate Myself!", Toast.LENGTH_LONG).show();
			return;
		}
		//ͨ��һ�����������ظó����һ��ApplicationInfo����
		ApplicationInfo tempAppInfo = packageUtil.getApplicationInfo(processName);
		if (tempAppInfo == null) {
			return;
		}
		//���ݰ����رս���
		activityManager.killBackgroundProcesses(tempAppInfo.packageName);
    }
	//����һ��ListAdapter
	public ProcListAdapter buildProcListAdapter() {
		//����������еĳ���
		if (!runningProcessList.isEmpty()) {
			runningProcessList.clear();	
		}
		//��մ�����г�����Ϣ������
		if (!infoList.isEmpty()) {
			infoList.clear();
		}
		// ��ȡ�������еĽ���
    	runningProcessList = activityManager.getRunningAppProcesses();
    	RunningAppProcessInfo procInfo = null;
    	for (Iterator<RunningAppProcessInfo> iterator = runningProcessList.iterator(); iterator.hasNext();) {
    		procInfo = iterator.next();
    		//���������Ϣ�洢������
    		ProgramUtil programUtil = buildProgramUtilSimpleInfo(procInfo.pid, procInfo.processName);
    		//��������Ϣ��ӵ�������
    		infoList.add(programUtil);
		}
    	
    	ProcListAdapter adapter = new ProcListAdapter(infoList, this);
    	return adapter;
	}

	/*
	 * Ϊ���̻�ȡ��������Ϣ
	 */
    public ProgramUtil buildProgramUtilSimpleInfo(int procId, String procNameString) {

		ProgramUtil programUtil = new ProgramUtil();
		programUtil.setProcessName(procNameString);
		
		//���ݽ���������ȡӦ�ó����ApplicationInfo����
		ApplicationInfo tempAppInfo = packageUtil.getApplicationInfo(procNameString);

		if (tempAppInfo != null) {
			//Ϊ���̼���ͼ��ͳ�������
			programUtil.setIcon(tempAppInfo.loadIcon(packageManager));
    		programUtil.setProgramName(tempAppInfo.loadLabel(packageManager).toString());
		} 
		else {
			//�����ȡʧ�ܣ���ʹ��Ĭ�ϵ�ͼ��ͳ�����
			programUtil.setIcon(getApplicationContext().getResources().getDrawable(R.drawable.unknown));
			programUtil.setProgramName(procNameString);
		}
		//���ý����ڴ�ʹ����
		String str = getUsedMemory(procId);
		programUtil.setMemString(str);
		return programUtil;
    }

	/*
	 * Ϊ���̻�ȡ��װ��������
	 */
    public DetailProgramUtil buildProgramUtilComplexInfo(String procNameString) {

    	DetailProgramUtil complexProgramUtil = new DetailProgramUtil();
		// ���ݽ���������ȡӦ�ó����ApplicationInfo����
		ApplicationInfo tempAppInfo = packageUtil.getApplicationInfo(procNameString);
		if (tempAppInfo == null) {
			return null;
		}
		
		PackageInfo tempPkgInfo = null;
		try {
			tempPkgInfo = packageManager.getPackageInfo(
					tempAppInfo.packageName, 
					PackageManager.GET_UNINSTALLED_PACKAGES | PackageManager.GET_ACTIVITIES
					| PackageManager.GET_SERVICES | PackageManager.GET_PERMISSIONS);
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}
		if (tempPkgInfo == null) {
			return null;
		}
		
		complexProgramUtil.setProcessName(procNameString);
		complexProgramUtil.setCompanyName(getString(R.string.no_use));
		complexProgramUtil.setVersionName(tempPkgInfo.versionName);
		complexProgramUtil.setVersionCode(tempPkgInfo.versionCode);
		complexProgramUtil.setDataDir(tempAppInfo.dataDir);
		complexProgramUtil.setSourceDir(tempAppInfo.sourceDir);
		complexProgramUtil.setPackageName(tempPkgInfo.packageName);
		// ��ȡ����������Ϣ����ҪΪPackageManager������Ȩ(packageManager.getPackageInfo()����)
		complexProgramUtil.setUserPermissions(tempPkgInfo.requestedPermissions);
		complexProgramUtil.setServices(tempPkgInfo.services);
		complexProgramUtil.setActivities(tempPkgInfo.activities);
		
		return complexProgramUtil;
    }
    

}