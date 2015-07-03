package com.guo.taskmanager;

import java.io.Serializable;
import android.content.pm.ActivityInfo;
import android.content.pm.ServiceInfo;
import android.text.format.DateFormat;
public class DetailProgramUtil implements Serializable{
	private static final long serialVersionUID = 1L;
	/*
	 * ����Ӧ�ó������չ��Ϣ����
	 */

	private String packageName;						// ����
	private int pid;								// ����Ľ���id
	private String processName;						// �������еĽ�����
	
	private String companyName;						// ��˾����
	private int versionCode;						// �汾����
	private String versionName;						// �汾����
	
	private String dataDir;							// ���������Ŀ¼
	private String sourceDir;						// �������ԴĿ¼
	
	private String firstInstallTime;				// ��һ�ΰ�װ��ʱ��
	private String lastUpdateTime;					// ����ĸ���ʱ��
	
	private String userPermissions;					// Ӧ�ó����Ȩ��
	private String activities;						// Ӧ�ó��������Activities
	private String services;						// Ӧ�ó�������ķ���
	
	// android.content.pm.PackageState��İ���Ϣ
	//���캯������ʼ������
	public DetailProgramUtil() {
		pid = 0;
		processName = "";
		companyName = "";
		versionCode = 0;
		versionName = "";
		dataDir = "";
		sourceDir = "";
		firstInstallTime = "";
		lastUpdateTime = "";
		userPermissions = "";
		activities = "";
		services = "";
	}
	//��ý���id
	public int getPid() {
		return pid;
	}
	//���ý���id
	public void setPid(int pid) {
		this.pid = pid;
	}
	//��ð汾��
	public int getVersionCode() {
		return versionCode;
	}
	//���ð汾��
	public void setVersionCode(int versionCode) {
		this.versionCode = versionCode;
	}
	//��ð汾��Ϣ
	public String getVersionName() {
		return versionName;
	}
	//���ð汾��Ϣ
	public void setVersionName(String versionName) {
		this.versionName = versionName;
	}
	//��ù�˾����
	public String getCompanyName() {
		return companyName;
	}
	//���ù�˾����
	public void setCompanyName(String companyString) {
		this.companyName = companyString;
	}
	//��ó��ΰ�װʱ��
	public String getFirstInstallTime() {
		if (firstInstallTime == null || firstInstallTime.length() <= 0) {
			firstInstallTime = "null";
		}
		return firstInstallTime;
	}
	//���ó��ΰ�װʱ��
	public void setFirstInstallTime(long firstInstallTime) {
		this.firstInstallTime = DateFormat.format(
				"yyyy-MM-dd", firstInstallTime).toString();
	}
	//���������ʱ��
	public String getLastUpdateTime() {
		if (lastUpdateTime == null || lastUpdateTime.length() <= 0) {
			lastUpdateTime = "null";
		}
		return lastUpdateTime;
	}
	//����������ʱ��
	public void setLastUpdateTime(long lastUpdateTime) {
		this.lastUpdateTime = DateFormat.format(
				"yyyy-MM-dd", lastUpdateTime).toString();
	}
	//��û
	public String getActivities() {
		if (activities == null || activities.length() <= 0) {
			activities = "null";
		}
		return activities;
	}
	//���û
	public void setActivities(ActivityInfo[] activities) {
		this.activities = Array2String(activities);
	}
	//����û�Ȩ��
	public String getUserPermissions() {
		if (userPermissions == null || userPermissions.length() <= 0) {
			userPermissions = "null";
		}
		return userPermissions;
	}
	//�����û�Ȩ��
	public void setUserPermissions(String[] userPermissions) {
		this.userPermissions = Array2String(userPermissions);	
	}
	//��÷���
	public String getServices() {
		if (services == null || services.length() <= 0) {
			services = "null";
		}
		return services;
	}
	//���÷���
	public void setServices(ServiceInfo[] services) {
		this.services = Array2String(services);
	}
	//��ý�������
	public String getProcessName() {
		if (processName == null || processName.length() <= 0) {
			processName = "null";
		}
		return processName;
	}
	//���ý�������
	public void setProcessName(String processName) {
		this.processName = processName;
	}
	//�������Ŀ¼
	public String getDataDir() {
		if (dataDir == null || dataDir.length() <= 0) {
			dataDir = "null";
		}
		return dataDir;
	}
	//��������Ŀ¼
	public void setDataDir(String dataDir) {
		this.dataDir = dataDir;
	}
	//��û����Ŀ¼
	public String getSourceDir() {
		if (sourceDir == null || sourceDir.length() <= 0) {
			sourceDir = "null";
		}
		return sourceDir;
	}
	//����Դ·��
	public void setSourceDir(String sourceDir) {
		this.sourceDir = sourceDir;
	}
	//���ð���
	public void setPackageName(String packageName) {
		this.packageName = packageName;
	}
	//��ð���
	public String getPackageName() {
		return packageName;
	}
	/*
	 * �������ط�����������ͬ�����ò�ͬ�ķ��������ڽ�object����ת����Ҫ����ַ���
	 */
	// �û�Ȩ����Ϣ
    public String Array2String(String[] array) {
    	
    	String resultString = "";
    	if (array != null && array.length > 0) {
    		resultString = "";
    		//�������飬ʹ�û��з�ƴ������
			for (int i = 0; i < array.length; i++) {
				resultString += array[i];
				if (i < (array.length - 1)) {
					resultString += "\n";
				}
			}
		}
		return resultString;
    }
    
    // ������Ϣ
    public String Array2String(ServiceInfo[] array) {
    	String resultString = "";
    	//�������飬ʹ�û��з�ƴ������
    	if (array != null && array.length > 0) {
    		resultString = "";
			for (int i = 0; i < array.length; i++) {
				if (array[i].name == null) {
					continue;
				}
				resultString += array[i].name.toString();
				if (i < (array.length - 1)) {
					resultString += "\n";
				}
			}
		}
		return resultString;
    }
    
    // ���Ϣ
    public String Array2String(ActivityInfo[] array) {
    	String resultString = "";
    	//�������飬ʹ�û��з�ƴ������
    	if (array != null && array.length > 0) {
    		resultString = "";
			for (int i = 0; i < array.length; i++) {
				if (array[i].name == null) {
					continue;
				}
				resultString += array[i].name.toString();
				if (i < (array.length - 1)) {
					resultString += "\n";
				}
			}
		}
    	return resultString;
    }

}