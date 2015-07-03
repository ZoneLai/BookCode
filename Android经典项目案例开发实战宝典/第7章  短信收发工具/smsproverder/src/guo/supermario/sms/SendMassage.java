package guo.supermario.sms;

import java.util.ArrayList;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.telephony.SmsManager;

public class SendMassage {
	Context context;
	//���͵�����
	String msg;
	//�ռ��˵ĺ���
	String mobile;
	//���캯��
	public SendMassage(Context context,String msg,String mobile){
		this.context = context;
		this.msg = msg;
		this.mobile = mobile;		
	}
	//������Ϣ
	public void sendmsg(BroadcastReceiver send_sms,BroadcastReceiver delivered_sms){
		String SENT_SMS_ACTION = "SENT_SMS_ACTION";
		String DELIVERED_SMS_ACTION = "DELIVERED_SMS_ACTION";

		// �½�PendingIntent���ڵ���ָ���㲥������
		Intent sentIntent = new Intent(SENT_SMS_ACTION);
		PendingIntent sentPI = PendingIntent.getBroadcast(context, 0, sentIntent,
				0);
		// �½�PendingIntent���ڵ���ָ���㲥������
		Intent deliverIntent = new Intent(DELIVERED_SMS_ACTION);
		PendingIntent deliverPI = PendingIntent.getBroadcast(context, 0,
				deliverIntent, 0);		
		//ʵ�������Ź�����
		SmsManager smsManager = SmsManager.getDefault();
		//��ֶ���
		ArrayList<String> texts = smsManager.divideMessage(msg);
		for(String text : texts){
			//�������Ͷ���
			smsManager.sendTextMessage(mobile, null, text, sentPI, deliverPI);
		}
	}
}