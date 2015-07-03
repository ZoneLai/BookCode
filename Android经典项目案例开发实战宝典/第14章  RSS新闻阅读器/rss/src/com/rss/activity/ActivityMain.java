package com.rss.activity;

import java.net.URL;
import java.util.List;
import java.util.Map;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.InputSource;
import org.xml.sax.XMLReader;
import android.app.ListActivity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;
import com.rss.data.RssFeed;
import com.rss.sax.RssHandler;
//RSS�ı�����
public class ActivityMain extends ListActivity {
	//RSSԴ��ַ
	public String RSS_URL = "";
	public final String TAG = "RssReader";
	//RSS��Ϣ��
	private RssFeed feed;
	//
	private List<Map<String, Object>> mList;	
	//��ʼ������
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState); 
        Bundle b=getIntent().getExtras();
        //ȡ��RSS��ַ
        RSS_URL=b.getString("channel");
        Log.e("guojs-->get url",RSS_URL);
        //ȡ�ö�ӦRSSԴ��ַ����Ϣ
        feed = getFeed(RSS_URL);    
        //��RSS��Ϣ��ʾ���б���
        showListView();    
    }
    //ȡ�ö�ӦRSSԴ��ַ����Ϣ
    private RssFeed getFeed(String urlString) {
    	try {
    		URL url = new URL(urlString);
    		//����SAX����
    		SAXParserFactory factory = SAXParserFactory.newInstance();
    		SAXParser parser = factory.newSAXParser();
    		XMLReader xmlReader = parser.getXMLReader();
    		//SAX������
    		RssHandler rssHandler = new RssHandler();
    		xmlReader.setContentHandler(rssHandler);
    		//ȡ����ҳ��Ϣ
    		InputSource is = new InputSource(url.openStream());
    		//������ҳ����
    		xmlReader.parse(is);
    		//����RSS��Ϣ
    		return rssHandler.getFeed();
    	}catch (Exception e) {
			return null;
		}
    }
    //��ʾRSS��Ϣ���б���
	@SuppressWarnings("unchecked")
	private void showListView() {
    	if(feed == null) {
    		setTitle("RSS�Ķ���");
    		return;
    	}
    	//ȡ��RSS��Ϣ����
    	mList = feed.getAllItemsForListView();    	
    	MyAdapter adapter = new MyAdapter(this);
    	//����������
    	setListAdapter(adapter);
    	setSelection(0);
	}
	//�½�������������
	class MyAdapter extends BaseAdapter  {
		private LayoutInflater mInflator;
		//���캯��
		public MyAdapter(Context context) {
			this.mInflator = LayoutInflater.from(context);
		}
		//ȡ���б�����
		public int getCount() {
			System.out.println("mList.size()=" + mList.size());
			return mList.size();
		}
		public Object getItem(int position) {
			return null;
		}
		//ȡ��item��id
		public long getItemId(int position) {
			return 0;
		}
		//ȡ��ÿһ��Ԫ�ص���ͼ
		public View getView(int position, View convertView, ViewGroup parent) {
			ViewRss vRss = null;
			final int row = position;
			//ʵ��������Ԫ����
			vRss = new ViewRss();
			//���ͳ�����Ԫ�ص���ͼ
			convertView = mInflator.inflate(R.layout.item, null);
			//��ʼ������Ԫ��
			vRss.mLayout=(LinearLayout)convertView.findViewById(R.id.textLayout);
			vRss.title = (TextView)convertView.findViewById(R.id.title);
			vRss.pubdate = (TextView)convertView.findViewById(R.id.pubdate);				
			vRss.delBtn = (Button)convertView.findViewById(R.id.del_btn);
			//����ɾ����ť���ɼ�
			vRss.delBtn.setVisibility(View.INVISIBLE);
			convertView.setTag(vRss);
			//ȡ������
			String pubDate =  (String) mList.get(position).get("pubDate"); 
			//ȡ�ñ���
			String title = (String)mList.get(position).get("title");
			//���ñ���
			vRss.title.setText(title);
			//��������
			vRss.pubdate.setText(pubDate);					
			//ΪtextLayout���ð���������
			vRss.mLayout.setOnClickListener(new OnClickListener() {				
				public void onClick(View v) {
					Intent intent = new Intent(ActivityMain.this, ActivityShowDescription.class);
					Bundle b = new Bundle();
					//������
					b.putString("title", feed.getItem(row).getTitle());
					b.putString("description", feed.getItem(row).getDescription());
					b.putString("link", feed.getItem(row).getLink());
					b.putString("pubdate", feed.getItem(row).getPubDate());
					intent.putExtra("com.rss.data.RssFeed", b);
					//�����鿴RSS��ϸ��Ϣ����
					startActivity(intent);					
				}
			});
			return convertView;
		}		
	}
	//RSS����Ԫ���࣬���ڴ��RSS����Ԫ��
	public final class ViewRss {
		public LinearLayout mLayout;
		//����
		public TextView title;
		//����
		public TextView pubdate;
		//ɾ������
		public Button delBtn;
	}	
}