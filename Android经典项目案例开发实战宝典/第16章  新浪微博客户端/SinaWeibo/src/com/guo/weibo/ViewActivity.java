package com.guo.weibo;

import org.json.JSONException;
import org.json.JSONObject;

import com.guo.weibo.HomeActivity.AsyncImageLoader;
import com.guo.weibo.HomeActivity.ImageCallback;
import com.weibo.net.Weibo;
import com.weibo.net.WeiboParameters;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

public class ViewActivity extends Activity{
	//���浱ǰ������
	Context mContext;
	Weibo weibo;
	//������ʾ�û��ǳ�
	TextView username; 
	//������ʾ΢����������
	TextView content;
	//������ʾ�û�ͷ��
	ImageView icon; 
	//ת����ť
	Button btn_zf;
	//���۰�ť
	Button btn_pl;
	//΢����id
	String key;
	//���붯��
	LinearLayout loading;
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.weibo_detail);
		weibo=Common.weibo;
		mContext=this;
		//��ʼ������
		username=(TextView)findViewById(R.id.username); 
		content=(TextView)findViewById(R.id.text); 
		icon=(ImageView)findViewById(R.id.usericon);
		//ת����ť
		btn_zf=(Button)findViewById(R.id.btn_gz);
		//���۰�ť
		btn_pl=(Button)findViewById(R.id.btn_pl); 
		//ˢ�°�ť
		Button btn_refresh=(Button)findViewById(R.id.btn_refresh);
		//�ղذ�ť
		Button btn_sc=(Button)findViewById(R.id.btn_sc);
		//����������ҳ���ImageView
		ImageButton btn_home=(ImageButton)findViewById(R.id.homeBtn);
		loading=(LinearLayout)findViewById(R.id.loadingLayout);
		//Ϊ���۰�ť���ð���������
		btn_zf.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				//���ͳ�EditText��ͼ
				LayoutInflater inflater=(LayoutInflater)mContext.getSystemService(LAYOUT_INFLATER_SERVICE);
				final View view=inflater.inflate(R.layout.comment, null);
				//ȡ��EditText
				final EditText retrans=(EditText)view.findViewById(R.id.comment);
				new AlertDialog.Builder(mContext)
				.setTitle("ת��")
				.setView(view)
				.setPositiveButton("�ύ", new android.content.DialogInterface.OnClickListener(){
					@Override
					public void onClick(DialogInterface dialog, int which) {
						// TODO Auto-generated method stub	
						String str=retrans.getText().toString();
						//ת��
						JSONObject data=repost(mContext,weibo,key,str);
						if(!data.has("error"))
							Toast.makeText(ViewActivity.this, "ת���ɹ���", Toast.LENGTH_SHORT).show();
					}})
				.setNegativeButton("ȡ��",null).show();
			}			
		});
		//Ϊ���۰�ť���ð���������
		btn_pl.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				LayoutInflater inflater=(LayoutInflater)mContext.getSystemService(LAYOUT_INFLATER_SERVICE);
				final View view=inflater.inflate(R.layout.comment, null);
				final EditText comment=(EditText)view.findViewById(R.id.comment);
				new AlertDialog.Builder(mContext)
				.setTitle("����")
				.setView(view)
				.setPositiveButton("�ύ", new android.content.DialogInterface.OnClickListener(){
					@Override
					public void onClick(DialogInterface dialog, int which) {
						// TODO Auto-generated method stub	
						String str=comment.getText().toString();
						if(str != null)
						{
							//����
							JSONObject data=comment(mContext,weibo,key,str);
							if(!data.has("error"))
								Toast.makeText(ViewActivity.this, "���۳ɹ���", Toast.LENGTH_SHORT).show();
						}
					}})
				.setNegativeButton("ȡ��", null).show();				
			}			
		});
		//Ϊˢ�°�ť���ð���������
		btn_refresh.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				view(key);
			}			
		});
		//Ϊ�Ѳذ�ť���ð���������
		btn_sc.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				//�ղ�
				JSONObject data=collect(mContext,weibo,key);
				if(!data.has("error"))
					Toast.makeText(ViewActivity.this, "�ղسɹ���", Toast.LENGTH_SHORT).show();
			}			
		});
		//Ϊ������ҳ�水ť���ð���������
		btn_home.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent it=new Intent(ViewActivity.this,HomeActivity.class);
				startActivity(it);
				ViewActivity.this.finish();
			}			
		});
		//��ȡ��һ��ҳ�洫�ݹ�����key��keyΪĳһ��΢����id  
		Intent i=this.getIntent();
		Bundle b=null;
		if(!i.equals(null)){
			b=i.getExtras();  
		}
		if(b!=null && b.containsKey("key")){
			key = b.getString("key");
			//��ʼ��ҳ��
			view(key);
		}
	}
	//��ʼ��ҳ��
	private void view(String id){  
		//����΢��id���΢����ϸ��Ϣ
		JSONObject data=getOneWeibo(mContext,weibo,id);
		if(data!=null){  
			JSONObject u;
			String userName="δ֪";
			String userIcon=null;
			String text=null;
			try {
				//���΢����Ӧ�û���Ϣ
				u = data.getJSONObject("user");
				//ȡ���ǳ�
				userName=u.getString("screen_name");  
				//ȡ���û�ͷ���ַ
				userIcon=u.getString("profile_image_url");  
				Log.e("userIcon", userIcon); 
				Log.e("username","username"+userName);
				//ȡ��΢������
				text=data.getString("text");  
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} 
			//�����û��ǳ�
			username.setText(userName);
			//����΢������
			content.setText(text);  			  
			 //�½��첽ͼ�������
			AsyncImageLoader asyncImageLoader = new AsyncImageLoader();  
			//�����û�ͷ��
			Drawable cachedImage = asyncImageLoader.loadDrawable(userIcon,icon, new ImageCallback(){  
				@Override  
				public void imageLoaded(Drawable imageDrawable,ImageView imageView, String imageUrl) {  			  
					imageView.setImageDrawable(imageDrawable);  
				}  
			});  
			if (cachedImage == null)   
			{  
				//���ûȡ���û�ͷ�������ó�Ĭ�ϵ�ͷ��
				icon.setImageResource(R.drawable.default_icon);  
			}  
			else  
			{  
				//�����û�ͷ��
				icon.setImageDrawable(cachedImage);  
			}  
			//���΢����ͼƬ�����ͼƬ
			if(data.has("bmiddle_pic")){  
				String picurl=null;
				String picurl2=null;
				try {
					picurl = data.getString("bmiddle_pic");
					picurl2 = data.getString("original_pic");
				} catch (JSONException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
				//ͬ�������첽ͼ���������м���
				ImageView pic=(ImageView)findViewById(R.id.pic);
				Drawable cachedImage2 = asyncImageLoader.loadDrawable(picurl,pic, new ImageCallback(){  
					@Override  
					public void imageLoaded(Drawable imageDrawable,ImageView imageView, String imageUrl) {  
						showImg(imageView,imageDrawable);  
					}  
				});  
				if (cachedImage2 == null)   
				{  
					//���û���ص���Ӧͼ������Ĭ��ͼ�����
					pic.setImageResource(R.drawable.default_icon);  
				}  
				else  
				{
					//����ͼ��
					showImg(pic,cachedImage2);  
				}
			}  			 
			String rt=null;
			String comments=null;
			try {
				//ȡ��ת������
				rt = data.getString("reposts_count");
				//ȡ����������
				comments=data.getString("comments_count");
			} catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} 
			btn_zf.setText(" ת��("+rt+")");  
			btn_pl.setText(" ����("+comments+")");  
		}  
		loading.setVisibility(View.GONE);
	}  
	//����APIȡ�ö�Ӧ��΢����ϸ��Ϣ
	public JSONObject getOneWeibo(Context mContext,Weibo weibo,String id)
	{
	      String url=Weibo.SERVER+"statuses/show.json";
		  WeiboParameters bundle=new WeiboParameters();
		  bundle.add("source", ConstParam.CONSUMER_KEY);
		  //����΢��id
		  bundle.add("id", id);
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
	//����API����ת��
	public JSONObject repost(Context mContext,Weibo weibo,String id,String str)
	{
		//ת����API
	      String url=Weibo.SERVER+"statuses/repost.json";
		  WeiboParameters bundle=new WeiboParameters();
		  bundle.add("source", ConstParam.CONSUMER_KEY);
		  bundle.add("id", id);
		  //���ת������
		  bundle.add("status",str);
		  String rlt="";
			try {
				rlt = weibo.request(mContext, url, bundle, "POST", weibo.getAccessToken());
				return new JSONObject(rlt);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return null;				
			}
	}
	//����API�����ղ�΢��
	public JSONObject collect(Context mContext,Weibo weibo,String id)
	{
		//�ղص�API
	      String url=Weibo.SERVER+"favorites/create.json";
		  WeiboParameters bundle=new WeiboParameters();
		  bundle.add("source", ConstParam.CONSUMER_KEY);
		  //����΢����id
		  bundle.add("id", id);
		  String rlt="";
			try {
				rlt = weibo.request(mContext, url, bundle, "POST", weibo.getAccessToken());
				return new JSONObject(rlt);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return null;				
			}
	}
	//����API��������΢��
	public JSONObject comment(Context mContext,Weibo weibo,String id,String comment)
	{
		  //���۵�API
	      String url=Weibo.SERVER+"comments/create.json";
		  WeiboParameters bundle=new WeiboParameters();
		  bundle.add("source", ConstParam.CONSUMER_KEY);
		  //����΢����id
		  bundle.add("id", id);
		  //�������۵�����
		  bundle.add("comment", comment);
		  String rlt="";
			try {
				rlt = weibo.request(mContext, url, bundle, "POST", weibo.getAccessToken());
				return new JSONObject(rlt);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return null;				
			}
	}
	//��ʾ΢����ͼ��
	private void showImg(ImageView view,Drawable img){  
		int w=img.getIntrinsicWidth();  
		int h=img.getIntrinsicHeight();  
		Log.e("w", w+"/"+h);  
		//�����ȳ���300����������Ŵ���
		if(w>300)  
		{  
			int hh=300*h/w;  
			Log.e("hh", hh+"");  
			LayoutParams para=view.getLayoutParams();  
			para.width=300;  
			para.height=hh;  
			view.setLayoutParams(para);  
		}  
		//��ʾͼ��
		view.setImageDrawable(img);  
	}
}