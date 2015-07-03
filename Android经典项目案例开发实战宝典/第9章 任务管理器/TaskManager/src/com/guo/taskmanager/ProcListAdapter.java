package com.guo.taskmanager;
import java.util.ArrayList;
import java.util.List;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

public class ProcListAdapter extends BaseAdapter{
	List<ProgramUtil> list = new ArrayList<ProgramUtil>();
	// ��LayoutInflater���ڽ�һ��XML�����ļ�ʵ����Ϊһ��View����
	LayoutInflater layoutInflater;
	Context context;
	
	// ���캯��������Ϊ�б���� �� Context
	public ProcListAdapter(List<ProgramUtil> list, Context context) {
		this.list = list;
		this.context = context;
	}
	//����б�Ԫ������
	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return list.size();
	}
	//����б�Ԫ��
	@Override
	public Object getItem(int position) {
		// TODO Auto-generated method stub
		return list.get(position);
	}
	//����б�Ԫ�ص�id
	@Override
	public long getItemId(int position) {
		// TODO Auto-generated method stub
		return position;
	}
	// ��ȡ��ʾ���ݵ��б��View����
	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		
		ViewHolder holder = null;
		
		if (convertView == null) {
			// �Ӹ�����context�л�ȡLayoutInflater����
			layoutInflater = LayoutInflater.from(context);
			// ����inflate() - ���ض���XML�����ļ�inflate���ͳ�һ���µ���ͼ
			convertView = layoutInflater.inflate(R.layout.proc_list_item, null);
			
			holder = new ViewHolder();
			holder.image = (ImageView)convertView.findViewById(R.id.image_app);
			holder.nameText = (TextView)convertView.findViewById(R.id.name_app);
			holder.processName = (TextView)convertView.findViewById(R.id.package_app);
			holder.memInfo = (TextView)convertView.findViewById(R.id.cpumem_app);
			
			// Ϊһ��View��ӱ�ǩ����ǩ������ViewHolder�ж��壬���Կ�����һ���󶨲���
			convertView.setTag(holder);
		} else {
			holder = (ViewHolder) convertView.getTag();
		}
		
		final ProgramUtil pUtils = list.get(position);
		// ����ͼ��
		holder.image.setImageDrawable(pUtils.getIcon());
		// ���ó�����
		holder.nameText.setText(pUtils.getProgramName());
		// ���ð���
		holder.processName.setText(pUtils.getProcessName());
		// ���ڴ���Ϣ
		holder.memInfo.setText(pUtils.getMemString());
		
		return convertView;
	}
}
//���ڴ��ÿһ������Ԫ�ص���
class ViewHolder {
	TextView nameText;
	TextView processName;
	TextView memInfo;
	ImageView image;
}
