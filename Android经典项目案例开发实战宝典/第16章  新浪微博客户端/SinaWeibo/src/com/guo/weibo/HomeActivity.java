package com.guo.weibo;

import java.io.IOException;
import java.io.InputStream;
import java.lang.ref.SoftReference;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import com.weibo.net.ShareActivity;
import com.weibo.net.Weibo;
import com.weibo.net.WeiboException;
import com.weibo.net.WeiboParameters;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.Spannable;
import android.text.SpannableStringBuilder;
import android.text.style.ForegroundColorSpan;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class HomeActivity extends Activity{
	//���浱ǰ������
	Context mContext;
	//�洢����΢����Ϣ
	private List<WeiboInfo> wbList;  
	//���붯��
	LinearLayout loadingLayout;
	Weibo weibo;
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.home);
		loadingLayout=(LinearLayout)findViewById(R.id.loadingLayout);
		//д΢��
		ImageButton btn_write=(ImageButton)findViewById(R.id.writeBtn);
		btn_write.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				try {
					//д΢��
					weibo.share2weibo(HomeActivity.this, weibo.getAccessToken().getToken(), weibo.getAccessToken()
					        .getSecret(), "abc", "");
				} catch (WeiboException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}			
		});
		//ˢ�½���
		ImageButton refresh=(ImageButton)findViewById(R.id.refreshBtn);
		refresh.setOnClickListener(new OnClickListener(){
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				loadList();
			}			
		});
		mContext=this;
		//��ʼ������
		loadList();
	}
	 
	//΢���б�Adapater  
	public class WeiboAdapater extends BaseAdapter{  
		 //��ȡ�б�������
		@Override  
		public int getCount() {  
			return wbList.size();  
		}		
		//ȡ�õ�ǰѡ�е�΢��
		@Override  
		public Object getItem(int position) {  
			return wbList.get(position);  
		}  
		//ȡ�õ�ǰ��λ��
		@Override  
		public long getItemId(int position) {  
			return position;  
		}  
		 //�õ�ÿһ�е���ͼ
		@Override  
		public View getView(int position, View convertView, ViewGroup parent) {  
			//�첽��ȡͼƬ��
			AsyncImageLoader asyncImageLoader = new AsyncImageLoader();  
			//���ͳ�΢����ͼ
			convertView = LayoutInflater.from(getApplicationContext()).inflate(R.layout.weibo, null);  
			WeiboHolder wh = new WeiboHolder();  
			//ȡ��΢�������Ԫ��
			wh.wbicon = (ImageView) convertView.findViewById(R.id.wbicon);  
			wh.wbtext = (TextView) convertView.findViewById(R.id.wbtext);  
			wh.wbtime = (TextView) convertView.findViewById(R.id.wbtime);  
			wh.wbuser = (TextView) convertView.findViewById(R.id.wbuser);  
			wh.wbimage=(ImageView) convertView.findViewById(R.id.wbimage);  
			//ȡ��΢����Ϣ
			WeiboInfo wb = wbList.get(position);  
			if(wb!=null){ 
				//��΢����id���浽��ǩ����
				convertView.setTag(wb.getId());  
				wh.wbuser.setText(wb.getUserName());  
				wh.wbtime.setText(wb.getTime());  
				wh.wbtext.setText(textHighlight(wb.getText()), TextView.BufferType.SPANNABLE);
				//���΢�����ݺ���ͼƬ������ʾ��־ͼƬ
				if(wb.getHaveImage()){  
					wh.wbimage.setImageResource(R.drawable.images);  
				}  
				//ȡ���û�ͼ��
				Drawable cachedImage = asyncImageLoader.loadDrawable(wb.getUserIcon(),wh.wbicon, new ImageCallback(){		
					//���ýӿ���ʾͼƬ
					@Override  
					public void imageLoaded(Drawable imageDrawable,ImageView imageView, String imageUrl) {  
						imageView.setImageDrawable(imageDrawable);  
					}  		  
				});  
				if (cachedImage == null) {  
					wh.wbicon.setImageResource(R.drawable.default_icon);
				}else{  
					wh.wbicon.setImageDrawable(cachedImage);  
				}
			}  			  
			return convertView;  
		}  
		//���ڴ��΢����ͼԪ�ص���
		class WeiboHolder{
			//΢���Ƿ����ͼƬ��־
			public ImageView wbimage;
			//�û��ǳ�
			public TextView wbuser;
			//΢������ʱ��
			public TextView wbtime;
			//΢������
			public TextView wbtext;
			//�û�ͼ��
			public ImageView wbicon;		
		}		
	}
	public static class AsyncImageLoader {  
		//SoftReference�������ã���Ϊ�˸��õ�Ϊ��ϵͳ���ձ���  
		private HashMap<String, SoftReference<Drawable>> imageCache;  
		public AsyncImageLoader() {  
			imageCache = new HashMap<String, SoftReference<Drawable>>();  
		}  
		  
		public Drawable loadDrawable(final String imageUrl,final ImageView imageView, final ImageCallback imageCallback){  
			if (imageCache.containsKey(imageUrl)) {  
				//�ӻ����л�ȡ  
				SoftReference<Drawable> softReference = imageCache.get(imageUrl);  
				Drawable drawable = softReference.get();  
				if (drawable != null) {
					return drawable;  
				}  
			}  
			final Handler handler = new Handler() {  
			public void handleMessage(Message message) { 
				//���ýӿ���ʾͼƬ
				imageCallback.imageLoaded((Drawable) message.obj, imageView,imageUrl);  
			}};  
			//������һ���µ��߳�����ͼƬ  
			new Thread() {  
				@Override  
				public void run() {  
					Drawable drawable = loadImageFromUrl(imageUrl);  
					//��ͼƬ���뻺��
					imageCache.put(imageUrl, new SoftReference<Drawable>(drawable));  
					Message message = handler.obtainMessage(0, drawable);  
					//������Ϣ���½���
					handler.sendMessage(message);  
				}  
			}.start();  
			return null;  
		}  		  
		//����������ͼƬ
		public static Drawable loadImageFromUrl(String url){  
			URL m;  
			InputStream i = null;  
			try {  
				m = new URL(url);  
				//ȡ��ͼƬ������ת����InputStream
				i = (InputStream) m.getContent();  
			} catch (MalformedURLException e1) {  
				e1.printStackTrace();  
			} catch (IOException e) {  
				e.printStackTrace();  
			}  
			//����һ��Drawable����
			Drawable d = Drawable.createFromStream(i, "src");  
			return d;  
		}      
	}  
	//�ص��ӿ�  
	public interface ImageCallback {  
		public void imageLoaded(Drawable imageDrawable,ImageView imageView, String imageUrl);  
	}
	//������ʾTextView�Ĺؼ�����
	public SpannableStringBuilder textHighlight(String str)
	{
		//������ʾ��#���͡�#��֮�������
    	Pattern pattern =Pattern.compile("#[^#]+#");
    	Matcher matcher = pattern.matcher(str);
    	SpannableStringBuilder style=new SpannableStringBuilder(str);
    	//������ƥ����ַ������д���
    	while(matcher.find()){      
    		String temp=matcher.group();
    		Log.e("guojs","start"+str.indexOf(matcher.group()));
    		//���ùؼ�����ɫΪ��ɫ
    		style.setSpan(new ForegroundColorSpan(Color.BLUE),str.indexOf(temp),str.indexOf(temp)+temp.length(),Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);  
    	}
    	//������ʾ��@���͡�����֮�������
    	pattern=Pattern.compile("@[\\w\\W]:");
    	matcher = pattern.matcher(str);
    	while(matcher.find()){      
    		String temp=matcher.group();
    		Log.e("guojs","start"+str.indexOf(matcher.group()));
    		//���ùؼ��ֵ���ɫΪ��ɫ
    		style.setSpan(new ForegroundColorSpan(Color.BLUE),str.indexOf(temp),str.indexOf(temp)+temp.length(),Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);  
    	}
    	//������ʾhttp://��ͷ����https://��ͷ������
    	pattern=Pattern.compile("(http://|https://){1}[\\w\\.\\-/:]+");
    	matcher = pattern.matcher(str);
    	while(matcher.find()){      
    		String temp=matcher.group();
    		Log.e("guojs","start"+str.indexOf(matcher.group()));
    		//���ùؼ�����ɫΪ��ɫ
    		style.setSpan(new ForegroundColorSpan(Color.BLUE),str.indexOf(temp),str.indexOf(temp)+temp.length(),Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);  
    	}
    	return style;
	}
	//��ʼ��������ʾ
	private void loadList(){  
		//�����ǰû���û���¼ֱ�ӷ���
        if(Common.login_user==null)  
        {  
              return;
        }  
        else  
        {  
        	//ȡ�õ�ǰ��½���û�
            UserInfo user=Common.login_user;  
            //��ʾ��ǰ�û�����  
            TextView showName=(TextView)findViewById(R.id.showName);  
            showName.setText(user.getUserName());          
    		weibo=Common.weibo;
    		//ȡ�õ�ǰ�û���ע���û�������΢����Ϣ
    		JSONObject json = getFriendsTimeline(mContext,weibo);
    		Log.e("guojs",json.toString());
	        JSONArray data;
			try {
				//�ж�access_token�Ƿ����
				if(json.has("error") && json.getString("error_code") == "21315")
	    		{
	    			Toast.makeText(mContext, "��Ȩ���ڣ���������Ȩ��", Toast.LENGTH_LONG).show();
	    			//��������������û�������Ȩ
	    			Intent it=new Intent(HomeActivity.this,LoginActivity.class);
	    			startActivity(it);
	    			HomeActivity.this.finish();
	    			//�жϷ���ֵ�Ƿ����
	    		}else if(json.has("error")){
	    			Toast.makeText(mContext, "�����ˣ��������Ϊ��"+json.getString("error_code"), Toast.LENGTH_LONG).show();
	    			//�����������û����µĵ�½
	    			Intent it=new Intent(HomeActivity.this,LoginActivity.class);
	    			startActivity(it);
	    			HomeActivity.this.finish();
	    		}else{
	    			//ȡ��statuses��Ϣ
					data = new JSONArray(json.getString("statuses")); 
					Log.e("home-length","changdu :"+data.length());
					//����ÿ����Ϣ
			        for(int i=0;i<data.length();i++)  
			        {  
			            JSONObject d=data.getJSONObject(i);  
			            if(d!=null){  
			            	//ȡ��ÿ����Ϣ�а������û�����Ϣ
			                JSONObject u=d.getJSONObject("user");                    
			                //΢��id  
			                String id=d.getString("id");  
			                //ȡ���û�id
			                String userId=u.getString("id");  
			                //ȡ���û��ǳ�
			                String userName=u.getString("screen_name");  
			                //ȡ���û�ͼ���ַ
			                String userIcon=u.getString("profile_image_url");  
			                Log.e("userIcon", userIcon);  
			                //ȡ��΢������ʱ��
			                String time=d.getString("created_at");  
			                //ȡ��΢������
			                String text=d.getString("text");  
			                Boolean haveImg=false;  
			                //�жϵ�ǰ΢�������Ƿ����ͼƬ
			                if(d.has("thumbnail_pic")){  
			                	//�����ͼƬ��������ͼƬ��־λ
			                    haveImg=true;  
			                }                  
			                Date date=new Date(time); 
			                //ת���ɼ�����ǰ����Сʱǰ������
			                time=getTimeDiff(date);  
			                if(wbList == null){  
			                	//�����û�г�ʼ��΢���б�����г�ʼ��
			                    wbList = new ArrayList<WeiboInfo>();  
			                }  
			                //ʵ����һ��WeiboInfo�࣬���ڱ���΢������Ϣ
			                WeiboInfo w=new WeiboInfo();  
			                w.setId(id);  
			                w.setUserId(userId);  
			                w.setUserName(userName);  
			                w.setTime(time);  
			                w.setText(text);  
			                  
			                w.setHaveImage(haveImg);  
			                w.setUserIcon(userIcon);  
			                //����Ϣ��ӵ�΢��������
			                wbList.add(w);  
			            }  
			        }
	    		}
	        } catch (JSONException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
	        }   
	        //�ж�΢���б��Ƿ�Ϊ��
            if(wbList!=null)  
            {  
            	//����΢����Ϣ�б��������
                WeiboAdapater adapater = new WeiboAdapater();  
                ListView Msglist=(ListView)findViewById(R.id.Msglist);  
                //�����б�İ���������
                Msglist.setOnItemClickListener(new OnItemClickListener(){  
                    @Override  
                    public void onItemClick(AdapterView<?> arg0, View view,int arg2, long arg3) {  
                    	//�����ͼ�󶨵�tag��Ϣ
                        Object obj=view.getTag();  
                        if(obj!=null){  
                            String id=obj.toString();  
                            //�����鿴΢����ϸ��Ϣ����ͼ
                            Intent intent = new Intent(HomeActivity.this,ViewActivity.class);  
                            //��΢����id�󶨵�b�з��͸���һ��Activity
                            Bundle b=new Bundle();  
                            b.putString("key", id);  
                            intent.putExtras(b);  
                            startActivity(intent); 
                            HomeActivity.this.finish();
                        }  
                    }  
                      
                });  
                Msglist.setAdapter(adapater);  
            }  
        }  
        //�������������
        loadingLayout.setVisibility(View.GONE);  
    }  
	//����û���ע���û�������΢����Ϣ
	public JSONObject getFriendsTimeline(Context mContext,Weibo weibo)
	{
	      String url=Weibo.SERVER+"statuses/friends_timeline.json";
		  WeiboParameters bundle=new WeiboParameters();
		  //����source
		  bundle.add("source", ConstParam.CONSUMER_KEY);
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
	//ȡ�ô���ʱ���뵱ǰʱ���ʱ���
	public String getTimeDiff(Date date) {
	        Calendar cal = Calendar.getInstance();
	        long diff = 0;
	        Date dnow = cal.getTime();
	        String str = "";
	        diff = dnow.getTime() - date.getTime();
	        //30 * 24 * 60 * 60 * 1000=2592000000 ����
	        if  (diff > 2592000000L) {
	            str="1����ǰ";
	          //21 * 24 * 60 * 60 * 1000=1814400000 ����
	        } else if  (diff > 1814400000) {
	            str="3��ǰ";
	          //14 * 24 * 60 * 60 * 1000=1209600000 ����
	        } else if  (diff > 1209600000) {
	            str="2��ǰ";
	          //7 * 24 * 60 * 60 * 1000=604800000 ����
	        } else if  (diff > 604800000) {
	            str="1��ǰ";
	            //24 * 60 * 60 * 1000=86400000 ����
	        } else if (diff > 86400000) {  
	        	// 60 * 60 * 1000=3600000 ����
	            str=(int)Math.floor(diff/86400000f) + "��ǰ";
	        } else if (diff > 3600000 ) {
	        	//1 * 60 * 1000=60000 ����
	            str=(int)Math.floor(diff/3600000f) + "Сʱǰ";
	        } else if (diff > 60000) {
	            str=(int)Math.floor(diff/60000) +"����ǰ";
	        }else{
	            str=(int)Math.floor(diff/1000) +"��ǰ";
	        }
	        return str;
	    }
}
