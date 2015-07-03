package com.guo.weibo;

import android.graphics.drawable.Drawable;

public class UserInfo {	
	
	final static String ID = "ID";
	final static String USERID = "USERID";	
	final static String USERNAME = "USERNAME";	
	final static String TOKEN = "TOKEN";	
	final static String TOKENSECRET = "TOKENSECRET";	
	final static String USERICON = "USERICON";
	
	//�û������ݿ��е�id������
	private String id;
	//�û�΢��id
	private String userId;
	//�û�΢���ǳ�
	private String userName;
	//�û�Access_Token��Ϊ������Ȩ���Token���û���ȡ�û����ݵȲ���
	private String token;
	//App��App_Secret
	private String tokenSecret;
	//�û�ͼ��
	private Drawable userIcon;
	//����id
	public void setId(String id)
	{
		this.id=id;
	}
	//�����û�΢��id
	public void setUserId(String userId)
	{
		this.userId=userId;
	}
	//�����û�΢���ǳ�
	public void setUserName(String userName)
	{
		this.userName=userName;
	}
	//����Access_Token
	public void setToken(String token)
	{
		this.token=token;
	}
	//����App_Secret
	public void setTokenSecret(String tokenSecret)
	{
		this.tokenSecret=tokenSecret;
	}
	//�����û�ͼ��
	public void setUserIcon(Drawable userIcon)
	{
		this.userIcon=userIcon;
	}
	//ȡ��id
	public String getId()
	{
		return id;
	}
	//ȡ���û�΢��id
	public String getUserId()
	{
		return userId;
	}
	//ȡ��΢���û���
	public String getUserName()
	{
		return userName;
	}
	//ȡ��Acces_Token
	public String getToken()
	{
		return token;
	}
	//ȡ��App_Secret
	public String getTokenSecret()
	{
		return tokenSecret;
	}
	//ȡ���û�ͼ��
	public Drawable getUserIcon()
	{
		return userIcon;
	}
}