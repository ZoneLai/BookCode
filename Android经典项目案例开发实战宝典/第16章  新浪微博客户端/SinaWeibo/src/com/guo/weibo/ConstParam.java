package com.guo.weibo;

public class ConstParam {
	public static final String CONSUMER_KEY = "2081498321";// �滻Ϊ�����ߵ�appkey������"1646212960";
	public static final String CONSUMER_SECRET = "7907ee613510bb7d3b2ce8beed302dd1";// �滻Ϊ�����ߵ�app_secret������"94098772160b6f8ffc1315374d8861f9";
	public static final String CALLBACK_URL = "http://baidu.com";//�ص���ַ
	public static String ACCESS_TOKEN;
	public static final String GET_USERINFO = "https://api.weibo.com/2/users/show.json?access_token="+ACCESS_TOKEN+"&uid="; //api��ַ
}
