package com.guo.weibo;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.util.ArrayList;
import java.util.List;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Bitmap;
import android.graphics.drawable.Drawable;
import android.util.Log;

public class DataHelper {  
	//���ݿ�����  
	private static String DB_NAME = "sinaweibo.db";  
	//���ݿ�汾  
	private static int DB_VERSION = 2;  
	private SQLiteDatabase db;  
	private SqliteHelper dbHelper;  
	  
	public DataHelper(Context context){  
		dbHelper=new SqliteHelper(context,DB_NAME, null, DB_VERSION);  
		db= dbHelper.getWritableDatabase();  
	}  
	//�ر����ݿ� 
	public void Close()  
	{  
		db.close();  
		dbHelper.close();  
	}  
	//��ȡusers���е�UserID��Access Token��Access Secret�ļ�¼  
	public List<UserInfo> GetUserList(Boolean isSimple)  
	{  
		List<UserInfo> userList = new ArrayList<UserInfo>();  
		//������ݱ��е���������
		Cursor cursor=db.query(SqliteHelper.TB_NAME, null, null, null, null, null, UserInfo.ID+" DESC");  
		//���α��ƶ�����ʼ
		cursor.moveToFirst();  
		//ѭ�������������ݿ�
		while(!cursor.isAfterLast()&& (cursor.getString(1)!=null)){  
		UserInfo user=new UserInfo();  
		user.setId(cursor.getString(0));  
		user.setUserId(cursor.getString(1));  
		user.setToken(cursor.getString(2));  
		user.setTokenSecret(cursor.getString(3));  
	if(!isSimple){
		if(cursor.getString(4) != null && cursor.getBlob(5) != null)
		{
			user.setUserName(cursor.getString(4));  
			ByteArrayInputStream stream = new ByteArrayInputStream(cursor.getBlob(5));   
			Drawable icon= Drawable.createFromStream(stream, "image");  
			user.setUserIcon(icon);  
		}
	}  
		userList.add(user);  
		cursor.moveToNext();  
	}  
		cursor.close();  
		return userList;  
	}  
	  
	//�ж�users���е��Ƿ����ĳ��UserID�ļ�¼  
	public Boolean HaveUserInfo(String UserId)  
	{  
		Boolean b=false;  
		Cursor cursor=db.query(SqliteHelper.TB_NAME, null, UserInfo.USERID + "=" + UserId, null, null, null,null);  
		b=cursor.moveToFirst();  
		Log.e("HaveUserInfo",b.toString());  
		cursor.close();  
		return b;  
	}
	//�ж�users���е��Ƿ����ĳ��UserID�ļ�¼  
	public UserInfo GetUserByName(String userName)  
	{  
		Boolean b=false;  
		//ע�⺺��Ϊ��ѯ����ʱ��Ҫ��''
		Cursor cursor=db.query(SqliteHelper.TB_NAME, null, UserInfo.USERNAME + "='" + userName+"'", null, null, null,null);  
		b=cursor.moveToFirst();  
		Log.e("GetUserByName",b.toString());  
		if(b != false){  
			UserInfo user=new UserInfo();  
			user.setId(cursor.getString(0));  
			user.setUserId(cursor.getString(1));  
			user.setToken(cursor.getString(2));  
			user.setTokenSecret(cursor.getString(3));  
			user.setUserName(cursor.getString(4));  
			ByteArrayInputStream stream = new ByteArrayInputStream(cursor.getBlob(5));   
			Drawable icon= Drawable.createFromStream(stream, "image");  
			user.setUserIcon(icon);  
			cursor.close();
			return user;
		}
		return null;  
	}	  
	//����users��ļ�¼������UserId�����û��ǳƺ��û�ͼ��  
	public int UpdateUserInfo(String userName,Bitmap userIcon,String UserId)  
	{  
		ContentValues values = new ContentValues();  
		values.put(UserInfo.USERNAME, userName);  
		// BLOB����   
		final ByteArrayOutputStream os = new ByteArrayOutputStream();   
		// ��Bitmapѹ����PNG���룬����Ϊ100%�洢   
		userIcon.compress(Bitmap.CompressFormat.PNG, 100, os);   
		// ����SQLite��Content��������Ҳ����ʹ��raw   
		values.put(UserInfo.USERICON, os.toByteArray());  
		int id= db.update(SqliteHelper.TB_NAME, values, UserInfo.USERID + "=" + UserId, null);  
		Log.e("UpdateUserInfo2",id+"");  
		return id;  
	}  
	  
	//����users��ļ�¼  
	public int UpdateUserInfo(UserInfo user)  
	{  
		ContentValues values = new ContentValues();  
		values.put(UserInfo.USERID, user.getUserId());  
		values.put(UserInfo.TOKEN, user.getToken());  
		values.put(UserInfo.TOKENSECRET, user.getTokenSecret());  
		int id= db.update(SqliteHelper.TB_NAME, values, UserInfo.USERID + "=" + user.getUserId(), null);  
		Log.e("UpdateUserInfo",id+"");  
		return id;  
	}  
	  
	//���users��ļ�¼  
	public Long SaveUserInfo(UserInfo user)  
	{  
		ContentValues values = new ContentValues();  
		values.put(UserInfo.USERID, user.getUserId());  
		values.put(UserInfo.TOKEN, user.getToken());  
		values.put(UserInfo.TOKENSECRET, user.getTokenSecret());  
		Long uid = db.insert(SqliteHelper.TB_NAME, UserInfo.ID, values);  
		Log.e("SaveUserInfo",uid+"");  
		return uid;  
	}  
	  
	//ɾ��users��ļ�¼  
	public int DelUserInfo(String UserId){  
		int id= db.delete(SqliteHelper.TB_NAME, UserInfo.USERID +"="+UserId, null);  
		Log.e("DelUserInfo",id+"");  
		return id;  
	}  
}  