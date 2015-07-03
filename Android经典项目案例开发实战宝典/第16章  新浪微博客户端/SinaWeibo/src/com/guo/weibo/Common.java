package com.guo.weibo;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.net.URLConnection;
import com.weibo.net.Weibo;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
//�������ͨ�õĺ����ͱ���
public class Common {
	public static UserInfo login_user=null;
	public static Weibo weibo=Weibo.getInstance();
	//ͨ��url��ַȡ��ͼ��
  	public static Bitmap getBm(URL aURL)
	{
		URLConnection conn;
		Bitmap bm=null;
		try {
			//��url����
			conn = aURL.openConnection();
			conn.connect();
			//�����������浽is
			InputStream is = conn.getInputStream();
			BufferedInputStream bis = new BufferedInputStream(is);
			//��λͼ������������������������ת����λͼ
			bm = BitmapFactory.decodeStream(bis);
			bis.close();
			is.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}		
		//����λͼ
		return bm;		
	}
}
