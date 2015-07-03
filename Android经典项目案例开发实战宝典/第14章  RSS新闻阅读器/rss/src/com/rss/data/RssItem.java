package com.rss.data;
//Rssitem��Ϣ�����ڴ��RSS��ÿһ��item
public class RssItem {
	public static final String TITLE = "title";
	public static final String PUBDATE = "pubDate";
	//����
	private String title;
	//��ϸ����
	private String description;
	//����
	private String link;
	//��Դ
	private String source;
	//����
	private String pubDate;
	//��ñ���
	public String getTitle() {
		return title;
	}
	//���� ����
	public void setTitle(String title) {
		this.title = title;
	}
	//ȡ����ϸ��Ϣ
	public String getDescription() {
		return description;
	}
	//������ϸ��Ϣ
	public void setDescription(String description) {
		this.description = description;
	}
	//ȡ������
	public String getLink() {
		return link;
	}
	//��������
	public void setLink(String link) {
		this.link = link;
	}
	//ȡ����Դ
	public String getSource() {
		return source;
	}
	//������Դ
	public void setSource(String source) {
		this.source = source;
	}
	//ȡ������
	public String getPubDate() {
		return pubDate;
	}
	//��������
	public void setPubDate(String pubDate) {
		this.pubDate = pubDate;
	}
	//ת����string
	public String toString() {
		if(title.length() > 20) {
			return title.substring(0, 42) + "...";
		}else {
			return title;
		}
	}
	
}