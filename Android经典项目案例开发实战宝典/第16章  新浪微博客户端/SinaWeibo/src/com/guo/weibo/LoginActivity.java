package com.guo.weibo;

import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import org.json.JSONObject;
import com.weibo.net.AccessToken;
import com.weibo.net.Oauth2AccessTokenHeader;
import com.weibo.net.Utility;
import com.weibo.net.Weibo;
import com.weibo.net.WeiboParameters;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.Context;
import android.content.DialogInterface;
import android.util.Log;
import android.view.View.OnClickListener;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.os.Bundle;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.GridView;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.Toast;
public class LoginActivity extends Activity{
	//���ݿ������
	DataHelper dbHelper;
	//�û���Ϣ����������
	UserAdapter mUserAdapter;
	//���ڱ������ݿ��������û�����Ϣ
	List<UserInfo> userList;
	//������ʾ��ǰ�û����ǳ�
	EditText username;
	//���浱ǰ��������
	Context mContext;
	//��ǰѡ�е��û���Ϣ
	UserInfo selectedUser;
	Weibo weibo;
	//��ǰѡ�е��û�id
	String user_id;
	//��ǰѡ���û���ͼ��
	ImageView icon;
	//�ײ��˵���
	GridView mGridView;
	//�ײ��˵���Ӧ�ı���
	String[] gridview_menu_title={"���","�˳�","ɾ��"};
	AlertDialog alertDialog;
	//�ײ��˵���Ӧ��ͼ��
	int[] girdview_menu_image={R.drawable.add,R.drawable.exit,R.drawable.del};
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.login);
		mContext=this;
		//ʵ�������ݿ������
		dbHelper = new DataHelper(this); 
		icon=(ImageView)findViewById(R.id.icon);
		ImageButton select=(ImageButton)findViewById(R.id.iconSelectBtn);
		Button login=(Button)findViewById(R.id.login);
		username=(EditText)findViewById(R.id.iconSelect);
		//�󶨼�����
		select.setOnClickListener(selectClickListener);
		login.setOnClickListener(loginClickListener);
		//��ʼ���ײ��˵�
		initGridViewMenu();
		//��ʼ���˵�������
        initMenuListener();
		//��ʼ���û���Ϣ
		initUser();
	}
	OnClickListener selectClickListener =new OnClickListener(){
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
		        AlertDialog.Builder builder;	
		        //���ͳ��û��б���ͼ
		        LayoutInflater inflater = (LayoutInflater) mContext.getSystemService(LAYOUT_INFLATER_SERVICE);
		        View layout = inflater.inflate(R.layout.user_list,null);
		        ListView myListView = (ListView) layout.findViewById(R.id.userList);
		        //Ϊ�б�Ԫ�ذ󶨰���������
		        myListView.setOnItemClickListener(listener);
		        Log.e("LoginActivity","userlist-size:"+userList.size());
		        //��������������
		        UserAdapter adapter = new UserAdapter(mContext, userList);
		        myListView.setAdapter(adapter);
		        builder = new AlertDialog.Builder(mContext);
		        builder.setView(layout);
		        alertDialog = builder.create();
		        //��ʾ�Ի���
		        alertDialog.show();
		}		
	};
	OnClickListener loginClickListener =new OnClickListener(){
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			//������֤��ʽ
    		Utility.setAuthorization(new Oauth2AccessTokenHeader());
    		//����access_token
    		String token=selectedUser.getToken();
    		AccessToken accessToken = new AccessToken(token, ConstParam.CONSUMER_SECRET);
    		Common.weibo.setAccessToken(accessToken);
    		weibo=Common.weibo;
    		user_id=selectedUser.getUserId();
    		//���µ�ǰ�û����ǳƺ�ͼ��
    		if(updateNicknameAndIcon())
    		{
    			//��ת���û�������
				GoHome();
				LoginActivity.this.finish();
    		}
		}		
	};
	OnItemClickListener listener=new OnItemClickListener(){
		@Override
		public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
				long arg3) {
			// TODO Auto-generated method stub
			//����ǰѡ�е��û�����Ϣ���浽selectedUser
			selectedUser = userList.get(arg2);
			//���õ�ǰ��ʾ���û��ǳƺ�ͼ��
			setIconAndText();
			alertDialog.dismiss();
		}		
	};
	//��ʼ���û���Ϣ
	private void initUser(){  
		//��ȡ�˺��б�   
		userList = dbHelper.GetUserList(false);  
		if(userList.isEmpty())  
		{  
        	Builder mBuilder=new AlertDialog.Builder(mContext);
        	mBuilder.setTitle("��ʾ");
        	mBuilder.setMessage("����δ�����κ��˻����Ƿ����ڴ�����");
        	mBuilder.setPositiveButton("ȷ��", new android.content.DialogInterface.OnClickListener(){
				@Override
				public void onClick(DialogInterface dialog, int which) {
					// TODO Auto-generated method stub
					Intent intent = new Intent();  
			        intent.setClass(LoginActivity.this, AuthorizeActivity.class);  
			        startActivity(intent);  
			        LoginActivity.this.finish();
				}      		
        	}).setNegativeButton("ȡ��", new android.content.DialogInterface.OnClickListener(){
				@Override
				public void onClick(DialogInterface dialog, int which) {
					// TODO Auto-generated method stub
					LoginActivity.this.finish();
				}      		
        	});
        	mBuilder.create().show(); 
		}  
		else  
		{  
			//��¼��ǰѡ����û�����
			SharedPreferences preferences = getSharedPreferences("select_name", Activity.MODE_PRIVATE);  
			String str= preferences.getString("name", "");  
			if(str!="")  
			{  
				//�����ݿ���ѡ���Ӧ������
				selectedUser=dbHelper.GetUserByName(str);  
			}  
			//���õ�ǰ��ʾ���û��ǳƺ�ͼ��
			setIconAndText();
		}  
	}
	//���õ�ǰ��ʾ���û��ǳƺ�ͼ��
	public void setIconAndText()
	{
		if(selectedUser == null)  
		{  
			//�����ǰѡ����ǿգ���ȡ���ݿ�ĵ�һ������
			selectedUser=userList.get(0);  
		}  
		if(selectedUser.getUserName() == null)
		{
			//�����ݿ���û����Ӧ�û���Ϣ��������Ϊ��δ֪��
			username.setText("δ֪");
		}else{
			username.setText(selectedUser.getUserName()); 
		}
		if(selectedUser.getUserIcon() != null)
		{
			icon.setImageDrawable(selectedUser.getUserIcon());  
		}else{
			//�����ݿ���û����Ӧ�û���ͼ���������û�ͼ��ΪĬ��ͼ��
			icon.setImageDrawable(mContext.getResources().getDrawable(R.drawable.default_icon));
		}	
	}
    /**ΪGridView���β˵���Դ*/
    private void initGridViewMenu(){
    	 mGridView = (GridView)findViewById(R.id.gridview_toolbar);
    	 //����ѡ��ʱ��ı���ͼƬ
    	 mGridView.setSelector(R.drawable.menu_item_selected);
         //���ñ���ͼƬ
    	 mGridView.setBackgroundResource(R.drawable.menu_background);
    	 //����ѡ�к󱳾�ͼƬ
    	 mGridView.setSelector(R.drawable.menu_item_selected);
         //��������
    	 mGridView.setNumColumns(3);
         //���þ��ж���
    	 mGridView.setGravity(Gravity.CENTER);
         //����ˮƽ����ֱ���Ϊ10
    	 mGridView.setVerticalSpacing(10);
    	 mGridView.setHorizontalSpacing(10);
         //����������
    	 mGridView.setAdapter(getMenuAdapter(gridview_menu_title,girdview_menu_image));
    }
    /**�˵�������*/
    private SimpleAdapter getMenuAdapter(String[] menuNameArray,
			int[] imageResourceArray) {
    	//�����б����ڴ��ӳ���
		ArrayList<HashMap<String, Object>> mData = new ArrayList<HashMap<String, Object>>();
		for (int i = 0; i < menuNameArray.length; i++) {
			HashMap<String, Object> mMap = new HashMap<String, Object>();
			//����image��ӳ���ͼƬ��Դ
			mMap.put("image", imageResourceArray[i]);
			//����title��ӳ��ɱ���
			mMap.put("title", menuNameArray[i]);		
			mData.add(mMap);
		}
		//�½����������������������Ĳ����ļ���ӳ���ϵ
		SimpleAdapter mAdapter = new SimpleAdapter(this, mData,R.layout.login_item_menu, new String[] { "image", "title" },new int[] { R.id.item_image, R.id.item_text });
		return mAdapter;
	}
    /**�˵���ļ���*/
    protected void initMenuListener(){
    	mGridView.setOnItemClickListener(new OnItemClickListener(){

			public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
					long arg3) {
				switch(arg2){
				//���
				case 0:
					Intent intent = new Intent();  
					intent.setClass(LoginActivity.this, AuthorizeActivity.class);  
					startActivity(intent);
					LoginActivity.this.finish();
					break;
				//�˳�
				case 1:
					LoginActivity.this.finish();
					break;
				//ɾ��
				case 2:
					delUser();
					break;
				}
			}  		
    	});
    }
    //ɾ����ǰ�û�
    public void delUser()
    {
    	if(selectedUser.getUserId() != null)
    	{
    		dbHelper.DelUserInfo(selectedUser.getUserId());
    		//���µ�ǰ����
    		initUser();
    	}
    }
    //�ڸ�Activity�ݻ��ǹر����ݿ�
    @Override
    public void onDestroy()
    {
    	super.onDestroy();
    	dbHelper.Close();
    }
    //�ڸ�Activityֹͣʱ���浱ǰѡ����û���Ϣ���ļ���
    @Override  
    protected void onStop() {  
	    //���SharedPreferences����  
	    SharedPreferences MyPreferences = getSharedPreferences("select_name", Activity.MODE_PRIVATE);  
	    //���SharedPreferences.Editor����  
	    SharedPreferences.Editor editor = MyPreferences.edit();  
	    //��������е�ֵ  
	    editor.putString("name", username.getText().toString());  
	    editor.commit();  
	    super.onStop();  
    } 
    //�����û���ҳ  
    private void GoHome(){  
	    if(userList!=null)  
	    {  
		    if(selectedUser !=null)  
		    {  
		    	//��ȡ��ǰѡ����û����ұ���  
		    	Common.login_user=selectedUser;
			    //�����û���ҳ  
			    Intent intent = new Intent();  
			    intent.setClass(LoginActivity.this, HomeActivity.class);  
			    startActivity(intent);  
		    }  
	    } 
    }
    //����ǳƺ��û�ͼ��
	  public boolean updateNicknameAndIcon()
	  {
		try {
			//����û�����ϸ��Ϣ
			JSONObject json=getUserDetail(mContext,weibo,user_id);
			Log.e("guojs-json","ddd"+json.toString());
			//������ص����ݺ��С�error�������Ҵ������Ϊ��21315����˵����Ȩ�ѹ���
			if(json.has("error") && json.getString("error_code") == "21315")
    		{
    			Toast.makeText(mContext, "��Ȩ���ڣ���������Ȩ��", Toast.LENGTH_LONG).show();
    			return false;
    			//������������
    		}else if(json.has("error")){
    			Toast.makeText(mContext, "�����ˣ��������Ϊ��"+json.getString("error_code"), Toast.LENGTH_LONG).show();
    			return false;
    			//���û�а���������Ϣ��˵����Ϣ��ȷ
    		}else{
    			//����û��ǳ�
				String nickName = json.getString("screen_name");
				Log.e("guojs","nickname:"+nickName);
				//����û�ͼ���ַ��������ͼ��
				Bitmap bm=Common.getBm(new URL(json.getString("profile_image_url")));
				//�������ݿ���ǳƺ�ͼ����Ϣ
				dbHelper.UpdateUserInfo(nickName,bm,user_id);
				dbHelper.Close();
				return true;
    		}
		} catch (Exception e) {
			Log.e("guojs",e.getMessage());
			return false;
		}
	}
	  //����api������û���Ϣ
	  public JSONObject getUserDetail(Context mContext,Weibo weibo,String uid)
	  {
	      String url=Weibo.SERVER+"users/show.json";
	      WeiboParameters bundle=new WeiboParameters();
	      //���source��uid����
	      bundle.add("source", ConstParam.CONSUMER_KEY);
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