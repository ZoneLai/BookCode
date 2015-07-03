package com.rss.data;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Vector;

public class RssFeed {
	//����
	private String title;
	//����
	private String pubdate;
	//����
	private int itemcount;
	//���ڴ��RSS��Ϣ���б�
	private List<RssItem> itemlist;	
	public RssFeed() {
		itemlist = new Vector<RssItem>(0);
	}
	//���Ԫ��
	public int addItem(RssItem item) {
		itemlist.add(item);
		itemcount++;
		return itemcount;
	}	
	//ȡ��Ԫ��
	public RssItem getItem(int location) {
		return itemlist.get(location);
	}
	//ȡ�������б���Ҫ����Ϣ���洢��List
	public List getAllItemsForListView() {
		List<Map<String, Object>> data = new ArrayList<Map<String, Object>>();
		int size = itemlist.size();
		for(int i=0; i<size; i++) {
			HashMap<String, Object> item = new HashMap<String, Object>();
			item.put(RssItem.TITLE, itemlist.get(i).getTitle());
			item.put(RssItem.PUBDATE, itemlist.get(i).getPubDate());
			data.add(item);
		}
		
		return data;
	}
	//ȡ�ñ���
	public String getTitle() {
		return title;
	}
	//���ñ���
	public void setTitle(String title) {
		this.title = title;
	}
	//ȡ������
	public String getPubdate() {
		return pubdate;
	}
	//��������
	public void setPubdate(String pubdate) {
		this.pubdate = pubdate;
	}
	//ȡ������
	public int getItemcount() {
		return itemcount;
	}
	//��������
	public void setItemcount(int itemcount) {
		this.itemcount = itemcount;
	}
	//�����Ϣ����
	public List<RssItem> getItemlist() {
		return itemlist;
	}
	//������Ϣ����
	public void setItemlist(List<RssItem> itemlist) {
		this.itemlist = itemlist;
	}	
}