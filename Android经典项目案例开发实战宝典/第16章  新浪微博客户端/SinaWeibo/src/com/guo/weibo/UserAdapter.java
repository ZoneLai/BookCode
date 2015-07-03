package com.guo.weibo;

import java.util.List;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
//�û���Ϣ������
public class UserAdapter extends BaseAdapter{  
	private List<UserInfo> userList;
	private Context mContext;
	//���캯��
	 public UserAdapter(Context context,List<UserInfo> info)
	 {
		 mContext=context;
		 userList=info;
	 }
	 //����б��Ԫ�ظ���
	@Override  
	public int getCount() {  
		return userList.size();  
	}  
	//���ָ��λ�õ�Ԫ��
	@Override  
	public Object getItem(int position) {  
		return userList.get(position);  
	}  
	//���λ����Ϣ
	@Override  
	public long getItemId(int position) {  
		return position;  
	}  
	 //���ÿ��Ԫ�ص���ͼ
	@Override  
	public View getView(int position, View convertView, ViewGroup parent) {  
		convertView = LayoutInflater.from(mContext.getApplicationContext()).inflate(R.layout.item_user, null);  	  
		ImageView iv = (ImageView) convertView.findViewById(R.id.iconImg);  
		TextView tv = (TextView) convertView.findViewById(R.id.name);  
		UserInfo user = userList.get(position);  
		try {  
		//����ͼƬ��ʾ  
		iv.setImageDrawable(user.getUserIcon());  
		//������Ϣ  
		tv.setText(user.getUserName());  		  	  
		} catch (Exception e) {  
		e.printStackTrace();  
		}  
		return convertView;  
	}
}