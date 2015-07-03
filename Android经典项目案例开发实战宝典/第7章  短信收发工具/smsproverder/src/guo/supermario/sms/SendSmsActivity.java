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
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
//������Ϣ����
public class SendSmsActivity extends Activity {
	//�ռ��˺���
	EditText ednum;
	//��������
	EditText edbody;
	//���Ͱ�ť
	Button send;
	//����״̬�㲥
	BroadcastReceiver send_sms;
	//�Է�����״̬�㲥
	BroadcastReceiver delivered_sms;
	String SENT_SMS_ACTION = "SENT_SMS_ACTION";
	String DELIVERED_SMS_ACTION = "DELIVERED_SMS_ACTION";
	String getnum;
	String getmsg;
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.sendmsg);
		//�����ʼ��
		ednum = (EditText) findViewById(R.id.ednum);
		edbody = (EditText) findViewById(R.id.edbody);
		send = (Button) findViewById(R.id.send);
		//���Ͱ�ť������
		send.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				//ȡ������ĺ���
				getnum = ednum.getText().toString();
				//ȡ�����������
				getmsg = edbody.getText().toString();
				//ʵ����������Ϣ��
				SendMassage sendmsg = new SendMassage(SendSmsActivity.this,
						getmsg, getnum);
				//������Ϣ
				sendmsg.sendmsg(send_sms,delivered_sms);
				//����Ϣ�洢�����ݿ⡰�ѷ��͡���
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
				edbody.setText("");
				//������Ϣ�б����
				back();

			}
		});
		send_sms=new BroadcastReceiver() {
			@Override
			public void onReceive(Context _context, Intent _intent) {
				switch (getResultCode()) {
				//���ͳɹ�
				case Activity.RESULT_OK:
					Toast.makeText(_context,
							"���ŷ��ͳɹ���", Toast.LENGTH_SHORT)
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
		// ע��㲥������
		registerReceiver(send_sms, new IntentFilter(SENT_SMS_ACTION));
		registerReceiver(delivered_sms, new IntentFilter(DELIVERED_SMS_ACTION));
	}
	//������Ϣ�б�
	private void back() {
		Intent intent = new Intent(SendSmsActivity.this, MsgListActivity.class);
		SendSmsActivity.this.startActivity(intent);
		SendSmsActivity.this.finish();

	}
	@Override
	public void onDestroy()
	{
		//ע���㲥������
		unregisterReceiver(send_sms);
		unregisterReceiver(delivered_sms);
		super.onDestroy();
	}
}