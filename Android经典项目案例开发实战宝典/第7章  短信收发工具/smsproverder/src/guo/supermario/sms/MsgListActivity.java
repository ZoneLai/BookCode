package guo.supermario.sms;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import android.app.Activity;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteException;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SimpleAdapter;
//��ʾ�յ�����Ϣ�б�
public class MsgListActivity extends Activity {
	//�½���Ϣ����
	private Button sendnmsg;
	//��Ϣ�б�
	private ListView msglist;
	//��ʼ������
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		// ȥ������
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.main);
		//��ʼ������Ԫ��
		sendnmsg = (Button) findViewById(R.id.newsms);
		msglist = (ListView) findViewById(R.id.msg_list);
		sendnmsg.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				//�����½���Ϣ����
				Intent intent = new Intent(MsgListActivity.this,
						SendSmsActivity.class);
				MsgListActivity.this.startActivity(intent);
				MsgListActivity.this.finish();
			}
		});		
		//�½�������
		SimpleAdapter adapter = new SimpleAdapter(MsgListActivity.this,
				getSmsInPhone(), R.layout.showlist, new String[] { "imag",
						"listnum", "listmsg", "listtime" ,"listtype"}, new int[] {
						R.id.imag, R.id.listnum, R.id.listmsg, R.id.listtime ,R.id.type});
		//֪ͨ���ݸ���
		adapter.notifyDataSetChanged();
		//����������
		msglist.setAdapter(adapter);
		//������Ŀ����������
		msglist.setOnItemClickListener(new OnItemClickListener() {
			public void onItemClick(AdapterView<?> arg0, View arg1,
					int position, long arg3) {
				//�����ظ���Ϣ����
				Intent intent = new Intent(MsgListActivity.this, Replymsg.class);
				//ȡ�ö�Ӧ�����Ŀ��Ԫ��
				Map<String, Object> getlist = getSmsInPhone().get(position);
				//�����ݰ󶨵�intent�н��д���
				intent.putExtra("listnum", (String) getlist.get("listnum"));
				intent.putExtra("listtime", (String) getlist.get("listtime"));
				intent.putExtra("listmsg", (String) getlist.get("listmsg"));
				intent.putExtra("listtype", (String)getlist.get("listtype"));
				MsgListActivity.this.startActivity(intent);
				MsgListActivity.this.finish();
			}
		});

	}
	//��ȡ�ֻ���������Ϣ
	public List<Map<String, Object>> getSmsInPhone() {
		//������Ϣ��Ӧ��uri��ַ
		final String SMS_URI_ALL = "content://sms/";
		List<Map<String, Object>> contents = new ArrayList<Map<String, Object>>();
		try {
			Uri uri = Uri.parse(SMS_URI_ALL);
			//��Ҫ��ѯ����
			String[] projection = new String[] { "_id", "address", "person",
					"body", "date", "type" };
			//��ѯ
			Cursor cur = getContentResolver().query(uri, projection, null,
					null, "date desc"); // ��ȡ�ֻ��ڲ�����
			//����ѯ������浽�б���
			while (cur.moveToNext()) {
				Map<String, Object> map = new HashMap<String, Object>();
				//ȡ���е�����
				int index_Address = cur.getColumnIndex("address");
				int index_Person = cur.getColumnIndex("person");
				int index_Body = cur.getColumnIndex("body");
				int index_Date = cur.getColumnIndex("date");
				int index_Type = cur.getColumnIndex("type");
				//ȡ�ö��ŷ���Ŀ��ĵ绰
				String strAddress = cur.getString(index_Address);
				//ȡ������
				cur.getInt(index_Person);
				//ȡ����Ϣ������
				String strbody = cur.getString(index_Body);
				//ȡ������
				long longDate = cur.getLong(index_Date);
				//ȡ�ö��ŵ����ͣ�1Ϊ�ѽ��գ�2Ϊ�ѷ���
				int type= cur.getInt(index_Type);
				//��ʽ������
				SimpleDateFormat dateFormat = new SimpleDateFormat(
						"yyyy-MM-dd hh:mm:ss");
				Date d = new Date(longDate);
				String strDate = dateFormat.format(d);
				//�����ݴ洢��map��
				map.put("listnum", strAddress);
				map.put("listmsg", strbody);
				map.put("listtime", strDate);
				if(type == 1)
				{
					map.put("listtype", "��");
				}else{
					map.put("listtype", "��");
				}
				//��map��ӵ��б���
				contents.add(map);
			}
			if (!cur.isClosed()) {
				cur.close();
				cur = null;
			}
		} catch (SQLiteException ex) {
			Log.d("SQLiteException in getSmsInPhone", ex.getMessage());
		}
			//������Ϣ�б�
			return contents;
		}
}