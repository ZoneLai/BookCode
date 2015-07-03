package com.rss.data;

import java.util.ArrayList;
import java.util.List;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteDatabase.CursorFactory;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;
//RSS���ݿ������
public class ChannelDataHelper {
		//���ݿ�����  
		private static String DB_NAME = "RssChannel.db";  
		//���ݿ�汾  
		private static int DB_VERSION = 1;  
		private SQLiteDatabase db;  
		private SqliteHelper dbHelper;  
		//���캯��
		public ChannelDataHelper(Context context){  
			//ʵ�������ݿ������
			dbHelper=new SqliteHelper(context,DB_NAME, null, DB_VERSION);  
			//��õ�ǰ���ݿ�
			db= dbHelper.getWritableDatabase();  
		}  
		//�ر����ݿ� 
		public void Close()  
		{  
			db.close();  
			dbHelper.close();  
		}  
		//��ȡ���е�RSSԴ��Ϣ 
		public List<String> GetChannelList()  
		{  
			List<String> ChannelList = new ArrayList<String>();  
			//������ݱ��е���������
			Cursor cursor=db.query(SqliteHelper.TB_NAME, null, null, null, null, null, ID+" DESC");  
			//���α��ƶ�����ʼ
			cursor.moveToFirst();  
			//ѭ�������������ݿ�
			while(!cursor.isAfterLast()&& (cursor.getString(1)!=null)){  
				//ȡ��Դ������Ϣ
				String channel=cursor.getString(1); 
				//��ӵ�����
				ChannelList.add(channel);  
				//�ƶ��α굽��һ��Ԫ��
				cursor.moveToNext();  
			}  
			cursor.close();  
			return ChannelList;
		}  
		//ͨ��url���ƻ��RSSԴurl��ַ
		public String getUrlByChannel(String name)
		{
			Cursor cursor=db.query(SqliteHelper.TB_NAME, null, NAME+"=?", new String[]{name}, null, null, null);
			//���α��ƶ�����ʼ
			cursor.moveToFirst(); 
			if(!cursor.isAfterLast()&& (cursor.getString(1)!=null))
					return cursor.getString(2);
			return null;
		}
		//��Ӽ�¼  
		public Long SaveChannelInfo(String name,String url)  
		{  
			ContentValues values = new ContentValues();  
			values.put(NAME, name);  
			values.put(URL, url);  
			//�����¼�¼
			Long id = db.insert(SqliteHelper.TB_NAME, null, values);  
			Log.e("SaveChannelInfo",id+"");  
			return id;
		}		  
		//ɾ��ָ��channle�ļ�¼  
		public int DelChannelInfo(String name){  
			int id= db.delete(SqliteHelper.TB_NAME, NAME +"='"+name+"'", null);  
			Log.e("DelChannelInfo",id+"");  
			return id;  
		}
		//���ݱ������Ϣ
	static String ID="id";
	static String NAME="name";
	static String URL="url";
	//���ݿ������
	class SqliteHelper extends SQLiteOpenHelper{  
		
		//��������   RSSƵ���ı��� 	 
		public static final String TB_NAME="channel";  
		public SqliteHelper(Context context, String name, CursorFactory factory, int version) {  
		super(context, name, factory, version);  
		}  
		//������  
		@Override  
		public void onCreate(SQLiteDatabase db) {  
			db.execSQL("CREATE TABLE IF NOT EXISTS "+  
			TB_NAME+"("+  
			ID+" integer primary key,"+  
			NAME+" varchar,"+  
			URL+" varchar"+
			")"  
			);  
			Log.e("Database","onCreate");  
		}  
		//���±�  
		@Override  
		public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {  
			db.execSQL("DROP TABLE IF EXISTS " + TB_NAME);  
			onCreate(db);  
			Log.e("Database","onUpgrade");  
		} 
	}
}