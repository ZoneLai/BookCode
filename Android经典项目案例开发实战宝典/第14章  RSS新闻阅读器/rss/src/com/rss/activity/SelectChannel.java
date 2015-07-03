package com.rss.activity;

import java.util.ArrayList;
import java.util.List;
import com.rss.data.ChannelDataHelper;

import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;
//RSSԴѡ�����
public class SelectChannel extends ListActivity{
	//menu�˵���id
	private static final int MENU_ADD = Menu.FIRST;
	private static final int MENU_QUIT = MENU_ADD + 1;
	//RSSԴ������
	ChannelAdapter mAdapter;
	//RSSԴ���ݿ���
	ChannelDataHelper mChannel;
	//RSSԴ����
	List<String> channelList=new ArrayList<String>();
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mChannel=new ChannelDataHelper(this);
		//ȡ�����ݿ���������
		channelList=mChannel.GetChannelList();
		mAdapter=new ChannelAdapter(this);
		//���ݿ�������
		if(mAdapter.getCount() == 0)
			Toast.makeText(this, "��δ����κ�Ƶ��", Toast.LENGTH_SHORT).show();
		setTitle("Ƶ��ѡ��");
		//����������
		setListAdapter(mAdapter);
		
	}
	//ListView��������
	class ChannelAdapter extends BaseAdapter  {
		private LayoutInflater mInflator;
		//���캯��
		public ChannelAdapter(Context context) {
			this.mInflator = LayoutInflater.from(context);
		}
		//ȡ�������С
		public int getCount() {
			return channelList.size();
		}
		//ȡ�õ�ǰλ�õ�Ԫ��
		public String getItem(int position) {
			return channelList.get(position);
		}
		//ȡ�õ�ǰλ�õ�id
		public long getItemId(int position) {
			return 0;
		}
		//ȡ�õ�ǰλ�õ���ͼ
		public View getView(int position, View convertView, ViewGroup parent) {
			ViewHolder vRss = null;
			//��¼��ǰ��λ��
			final int row = position;
			//��ʼ������Ԫ����
			vRss = new ViewHolder();
			//���ͳ�����
			convertView = mInflator.inflate(R.layout.item, null);
			//ȡ�ý���Ԫ��
			vRss.textLayout=(LinearLayout)convertView.findViewById(R.id.textLayout);	
			vRss.channel = (TextView)convertView.findViewById(R.id.title);	
			//���ñ��������С
			vRss.channel.setTextSize(25);
			vRss.delBtn = (Button)convertView.findViewById(R.id.del_btn);				
			//ȡ�ñ�����ı�����
			String title = channelList.get(position);
			vRss.channel.setText(title);			
			Log.e("guojs",channelList.get(row));
			//���ð����������
			vRss.textLayout.setOnClickListener(new OnClickListener(){
				@Override
				public void onClick(View v) {
					// TODO Auto-generated method stub
					String channelName=channelList.get(row);
					Intent it=new Intent();
					Log.e("channel-url",mChannel.getUrlByChannel(channelName));
					//���ݵ�ǰ���RSSԴ��Ӧ��URL��ַ
					it.putExtra("channel", mChannel.getUrlByChannel(channelName));
					it.setClass(SelectChannel.this, ActivityMain.class);
					//������ʾ��ǰRSSԴ��Ӧ��Ϣ�Ľ���
					startActivity(it);
				}				
			});
			//ɾ����ǰRSSԴ
			vRss.delBtn.setOnClickListener(new OnClickListener() {				
				public void onClick(View v) {
					delRssInfo();					
				}
				private void delRssInfo() {
					//ɾ���ɹ�
					if(-1 != mChannel.DelChannelInfo(channelList.get(row)))
					{
						Toast.makeText(SelectChannel.this, "ɾ���ɹ���", Toast.LENGTH_SHORT).show();
						//�Ƴ�����Ԫ��
						channelList.remove(row);
						//֪ͨ�ı����
						mAdapter.notifyDataSetChanged();
						//ɾ��ʧ��
					}else{
						Toast.makeText(SelectChannel.this, "ɾ��ʧ�ܣ�", Toast.LENGTH_SHORT).show();
					}
					
				}
			});
			return convertView;
		}		
	}
	//ÿһ��Ԫ�صĽ���Ԫ�����
	final class ViewHolder {
		public LinearLayout textLayout;
		public TextView channel;
		public Button delBtn;
	}
    
	//����menu�˵�
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		//���RSSԴ
		menu.add(0, MENU_ADD, 0, R.string.add_rss);
		//�˳�����
		menu.add(0,MENU_QUIT,1,R.string.rss_quit);
		return super.onCreateOptionsMenu(menu);
	}		
	//Ϊmenu�˵������󶨼�����
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		//���RSSԴ
		case MENU_ADD:
			Intent intent = new Intent();
			intent.setClass(SelectChannel.this, AddRss.class);
			startActivity(intent);
			return true;
			//�˳�����
		case MENU_QUIT:
			SelectChannel.this.finish();
		default:
			break;
		}
		return super.onOptionsItemSelected(item);
	}
}