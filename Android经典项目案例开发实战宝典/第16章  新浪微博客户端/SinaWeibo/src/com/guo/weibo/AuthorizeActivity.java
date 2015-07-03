package com.guo.weibo;

import java.net.URL;
import org.json.JSONObject;
import com.weibo.net.AccessToken;
import com.weibo.net.DialogError;
import com.weibo.net.Weibo;
import com.weibo.net.WeiboDialogListener;
import com.weibo.net.WeiboException;
import com.weibo.net.WeiboParameters;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;
//�û���Ȩ��֤
public class AuthorizeActivity extends Activity{
	DataHelper dbHelper;
	//���浱ǰ��Ȩ�ɹ����û���Ϣ
	UserInfo userInfo;
	//���浱ǰ�û���Access_Token
	String token;
	//�û����浱ǰ��Ȩ�ɹ����û�id
	String user_id;
	//ʵ����weibo��
	Weibo weibo;
	//���浱ǰ��������
	Context mContext;
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		mContext=this;
		dbHelper=new DataHelper(this);
		//ʵ����weibo
		weibo = Weibo.getInstance();
		userInfo=new UserInfo();
		//����App_Key��App_Secret
		weibo.setupConsumerConfig(ConstParam.CONSUMER_KEY, ConstParam.CONSUMER_SECRET);
		// Oauth2.0
		// ��ʽ��Ȩ��֤��ʽ
		// �˴��ص�ҳ����Ӧ���滻Ϊ��appkey��Ӧ��Ӧ�ûص�ҳ
		weibo.setRedirectUrl(ConstParam.CALLBACK_URL);
		// ��Ӧ��Ӧ�ûص�ҳ���ڿ����ߵ�½����΢������ƽ̨֮��
		// �����ҵ�Ӧ��--Ӧ������--Ӧ����Ϣ--�߼���Ϣ--��Ȩ����--Ӧ�ûص�ҳ�������úͲ鿴��
		// Ӧ�ûص�ҳ����Ϊ��
		weibo.authorize(this,new AuthDialogListener());
	}
	  class AuthDialogListener implements WeiboDialogListener {
			@Override
			public void onComplete(Bundle values) {
				//���Access_Token
				token = values.getString("access_token");
				//��ù���ʱ��
				String expires_in = values.getString("expires_in");
				user_id = values.getString("uid");
				Log.e("sinaweibo","access_token : " + token + "  expires_in: "
						+ expires_in+" uid :"+user_id);
				AccessToken accessToken = new AccessToken(token, ConstParam.CONSUMER_SECRET);
				accessToken.setExpiresIn(expires_in);
				//����Access_Token
				weibo.setAccessToken(accessToken);
				//�����û���Ϣ
				userInfo.setToken(token);
				userInfo.setUserId(user_id);
				userInfo.setTokenSecret(ConstParam.CONSUMER_SECRET);
				if(dbHelper.HaveUserInfo(user_id))
				{
					//�����û���Ϣ
					dbHelper.UpdateUserInfo(userInfo);
				}else{
					//����û���Ϣ
					dbHelper.SaveUserInfo(userInfo);
				}
				new Thread(mRunnable).start();
				//�����½����
				Intent it=new Intent();
		        it.setClass(AuthorizeActivity.this, LoginActivity.class);
		        startActivity(it);
			}
			//��Ȩ�쳣
			@Override
			public void onWeiboException(WeiboException e) {
				// TODO Auto-generated method stub
				Toast.makeText(AuthorizeActivity.this, e.getMessage(), Toast.LENGTH_LONG).show();
				AuthorizeActivity.this.finish();
			}
			//��Ȩ����
			@Override
			public void onError(DialogError e) {
				// TODO Auto-generated method stub
				Toast.makeText(AuthorizeActivity.this, e.getMessage(), Toast.LENGTH_LONG).show();
				AuthorizeActivity.this.finish();
			}
			//��Ȩ��ȡ��
			@Override
			public void onCancel() {
				// TODO Auto-generated method stub
				AuthorizeActivity.this.finish();
			}
	    }
	  //����ǳƺ��û�ͼ��
	  Runnable mRunnable=new Runnable(){
		@Override
		public void run() {
			// TODO Auto-generated method stub
			try {
				JSONObject json=getUserDetail(mContext,weibo,user_id);
				//����û��ǳ�
				String nickName = json.getString("screen_name");
				Log.e("guojs","nickname:"+nickName);
				Bitmap bm=Common.getBm(new URL(json.getString("profile_image_url")));
				//�����û���Ϣ
				dbHelper.UpdateUserInfo(nickName,bm,user_id);
				//�ر����ݿ�
				dbHelper.Close();
			} catch (Exception e) {
				Log.e("guojs",e.getMessage());
			}
		}  
	  };
	  //����api������û���Ϣ
	  public JSONObject getUserDetail(Context mContext,Weibo weibo,String uid)
	  {
		  //��ȡ�û���ϢAPI
	      String url=Weibo.SERVER+"users/show.json";
	      WeiboParameters bundle=new WeiboParameters();
	      bundle.add("source", ConstParam.CONSUMER_KEY);
	      //����û�id��Ϊ����
	      bundle.add("uid",uid);
	      String rlt="";
			try {
				rlt = weibo.request(mContext, url, bundle, "GET", weibo.getAccessToken());
				return new JSONObject(rlt);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return null;				
			}
	  }
}