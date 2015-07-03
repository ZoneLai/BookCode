package com.guo.taskmanager;
import java.util.List;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
public class PackageUtil {
	/* ApplicationInfo �࣬��������ͨӦ�ó������Ϣ��
	 *��Ҫ��ָManifest.xml��application��ǩ�е���Ϣ
	 **/
	private List<ApplicationInfo> allAppList;
	//���캯��
	public PackageUtil(Context context) {
		//���ͨ����������
		PackageManager pm = context.getApplicationContext().getPackageManager();
		//��ȡ����Ӧ�ó��򣬰�����Щ��ж�ص������Ա�������Ŀ¼�ĳ���
		allAppList = pm.getInstalledApplications(PackageManager.GET_UNINSTALLED_PACKAGES);
	}	
	/**
	 * ͨ��һ�����������ظó����һ��ApplicationInfo����
	 * @param name ������
	 * @return ApplicationInfo
	 */
	public ApplicationInfo getApplicationInfo(String appName) {
		if (appName == null) {
			return null;
		}
		//���������ض�Ӧ��Ӧ�ó�����Ϣ
		for (ApplicationInfo appinfo : allAppList) {
			if (appName.equals(appinfo.processName)) {
				return appinfo;
			}
		}
		return null;
	}
}
