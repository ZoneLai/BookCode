package com.guo.weibo;
public class WeiboInfo {  
	//΢��id  
	private String id;  
	//������id  
	private String userId;
	//����������  
	private String userName; 
	//������ͷ��  
	private String userIcon;	  
	//����ʱ��  
	private String time; 
	//�Ƿ���ͼƬ  
	private Boolean haveImage=false;
	//��������  
	private String text;
	//ȡ��΢��id
	public String getId(){  
		return id;  
	}  
	//����΢��id
	public void setId(String id){  
		this.id=id;  
	}  	  
	//ȡ���û�id
	public String getUserId(){  
		return userId;  
	}  
	//�����û�id
	public void setUserId(String userId){  
		this.userId=userId;  
	}	
	//ȡ���û��ǳ�
	public String getUserName(){  
		return userName;  
	}  
	//�����û��ǳ�
	public void setUserName(String userName){  
		this.userName=userName;  
	}  	  
	//��ȡ�û�ͼ��
	public String getUserIcon(){  
		return userIcon;  
	} 
	//�����û�ͼ��
	public void setUserIcon(String userIcon){  
		this.userIcon=userIcon;  
	} 
	//��ȡʱ��
	public String getTime(){  
		return time;  
	}  
	//����ʱ��
	public void setTime(String time)  
	{  
		this.time=time;  
	}  	  	
	//ȡ���Ƿ����ͼƬ�ı�־
	public Boolean getHaveImage(){  
		return haveImage;  
	}  
	//�����Ƿ����ͼƬ�ı�־
	public void setHaveImage(Boolean haveImage){  
		this.haveImage=haveImage;  
	}  	  
	//ȡ��΢������
	public String getText(){  
		return text;  
	}  
	//����΢������
	public void setText(String text){  
		this.text=text;  
	}  	  
}  