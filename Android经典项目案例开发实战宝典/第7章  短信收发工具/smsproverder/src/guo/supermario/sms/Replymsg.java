package guo.supermario.sms;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.Uri;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class Replymsg extends Activity {
	//��ʾ�ռ��˺������
	private TextView phonnum;
	//��ʾ�Է����ŷ���ʱ��
	private TextView phontime;
	//��ʾ�Է���������
	private TextView phonmsg;
	//���ڱ༭��������
	private EditText sendcontent;
	//�ظ�����
	private Button rereplybt;
	private Intent intent;
	//������
	BroadcastReceiver send_sms;
	BroadcastReceiver delivered_sms;
	String SENT_SMS_ACTION = "SENT_SMS_ACTION";
	String DELIVERED_SMS_ACTION = "DELIVERED_SMS_ACTION";
	//��ʼ������
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.replysms);
		//����Ԫ�صĳ�ʼ��
		phonnum = (TextView) findViewById(R.id.renum);
		phontime = (TextView) findViewById(R.id.retime);
		phonmsg = (TextView) findViewById(R.id.recontent);
		sendcontent = (EditText) findViewById(R.id.replybody);
		rereplybt = (Button) findViewById(R.id.reply);
		send_sms=new BroadcastReceiver() {
			@Override
			public void onReceive(Context _context, Intent _intent) {
				switch (getResultCode()) {
				case Activity.RESULT_OK:
					Toast.makeText(_context,
							"���ŷ��ͳɹ�!", Toast.LENGTH_SHORT)
							.show();
					break;
					//ͨ�ô���
				case SmsManager.RESULT_ERROR_GENERIC_FAILURE:
					Toast.makeText(_context,
							"SMS generic failure actions", Toast.LENGTH_SHORT)
							.show();
					break;
					//���ߵ类�ر�
				case SmsManager.RESULT_ERROR_RADIO_OFF:
					Toast
							.makeText(_context,
									"SMS radio off failure actions",
									Toast.LENGTH_SHORT).show();
					break;
					//δ�ṩpdu(Э��������Ԫ protocol description unit)
				case SmsManager.RESULT_ERROR_NULL_PDU:
					Toast.makeText(_context,
							"SMS null PDU failure actions", Toast.LENGTH_SHORT)
							.show();
					break;
				}
			}
		};
		delivered_sms=new BroadcastReceiver() {
			@Override
			public void onReceive(Context _context, Intent _intent) {
				Toast.makeText(_context, "�����ѱ����գ�",
						Toast.LENGTH_SHORT).show();
			}
		};
		// ע��㲥
		registerReceiver(send_sms, new IntentFilter(SENT_SMS_ACTION));
		registerReceiver(delivered_sms, new IntentFilter(DELIVERED_SMS_ACTION));
		//��ȡ��Ϣ
		getdata();
		//�ظ�
		send();
	}
	// ��ȡ��Ϣ
	private void getdata() {
		intent = getIntent();
		//��ô��ݹ�������Ϣ
		String listnum = intent.getStringExtra("listnum");
		String listtime = intent.getStringExtra("listtime");
		String listmsg = intent.getStringExtra("listmsg");
		//��ʼ�������ı�
		phonnum.setText(listnum);
		phontime.setText(listtime);
		phonmsg.setText(listmsg);
	}
	//����������
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			back();
		}
		return super.onKeyDown(keyCode, event);
	}
	//������Ϣ��ʾ�б�
	private void back() {
		Intent intentb = new Intent(Replymsg.this, MsgListActivity.class);
		Replymsg.this.startActivity(intentb);
		Replymsg.this.finish();
	}
	//�ظ�����
	private void send() {
		rereplybt.setOnClickListener(new OnClickListener() {
			String getnum;
			String getmsg;
			public void onClick(View v) {
				//��÷��ͺ���
				getnum = phonnum.getText().toString();
				//��÷�������
				getmsg = sendcontent.getText().toString();
				//ʵ����������Ϣ��
				SendMassage sendmsg = new SendMassage(Replymsg.this,getmsg,getnum);
				//������Ϣ
				sendmsg.sendmsg(send_sms,delivered_sms);
				ContentValues values=new ContentValues();
				//����ʱ��
				values.put("date", System.currentTimeMillis());
				//�Ķ�״̬
				values.put("read", 0);
				//1Ϊ��2Ϊ��
				values.put("type", 2);
				//�ʹ����
				values.put("address", getnum);
				//��������
				values.put("body", getmsg);
				getContentResolver().insert(Uri.parse("content://sms/sent"), values);
				sendcontent.setText("");
				//������Ϣ��ʾ����
				back();
			}
		});
	}
	//��������ʱ����
	@Override
	public void onDestroy()
	{
		//ע������
		unregisterReceiver(send_sms);
		unregisterReceiver(delivered_sms);
		super.onDestroy();
	}
}