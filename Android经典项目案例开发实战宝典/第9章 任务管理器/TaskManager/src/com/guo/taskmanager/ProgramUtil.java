package com.guo.taskmanager;
import android.graphics.drawable.Drawable;

public class ProgramUtil{
	/*
	 * ����Ӧ�ó���ļ�Ҫ��Ϣ����
	 */
	private Drawable icon;							// ����ͼ��
	private String programName;						// ��������
	private String processName;
	private String memString;
	//��ʼ������
	public ProgramUtil() {
		icon = null;
		programName = "";	
		processName = "";	
		memString = "";
	}
	//���ͼ��
	public Drawable getIcon() {
		return icon;
	}
	//����ͼ��
	public void setIcon(Drawable icon) {
		this.icon = icon;
	}
	//���Ӧ�ó�������
	public String getProgramName() {
		return programName;
	}
	//����Ӧ�ó�������
	public void setProgramName(String programName) {
		this.programName = programName;
	}
	//��ó���ռ���ڴ��С
	public String getMemString() {
		return memString;
	}
	//���ó���ռ���ڴ��С
	public void setMemString(String memString) {
		this.memString = memString;
	}
	//��ó�������
	public String getProcessName() {
		return processName;
	}
	//���ó�������
	public void setProcessName(String processName) {
		this.processName = processName;
	}
}
