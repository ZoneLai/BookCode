package com.rss.sax;

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.ext.DefaultHandler2;
import org.xml.sax.helpers.DefaultHandler;

import android.util.Log;

import com.rss.data.RssFeed;
import com.rss.data.RssItem;
//RSS����SAX����
public class RssHandler extends DefaultHandler {
	RssFeed rssFeed;
	RssItem rssItem;
	private static boolean a = false;
	String lastElementName = "";
	final int RSS_TITLE = 1;
	final int RSS_LINK = 2;
	final int RSS_DESCRIPTION = 3;
	final int RSS_PUBDATE = 5;
	int currentstate = 0;
	
	public RssHandler() {
		
	}
	//����rssFeed��ʽ����Ϣ
	public RssFeed getFeed() {
		return rssFeed;
	}
	//��ʼ�����ĵ�
	public void startDocument()throws SAXException {
		System.out.println("startDocument");
		//ʵ����RssFeed���RssItem��
		rssFeed = new RssFeed();
		rssItem = new RssItem();
	}
	//�ĵ�����
	@Override
	public void endDocument() throws SAXException {
		super.endDocument();
	}
	//��ʼ������ǩ
	@Override
	public void startElement(String uri, String localName, String qName,
			Attributes attributes) throws SAXException {
		super.startElement(uri, localName, qName, attributes);
		//channel��ǩ
		if(localName.equals("channel")) {
			currentstate = 0;
			return;
		}
		//item��ǩ
		if(localName.equals("item")) {
			rssItem = new RssItem();
			return;
		}
		//title��ǩ
		if(localName.equals("title")) {
			currentstate = RSS_TITLE;
			return;
		}
		//��ϸ��Ϣ��ǩ
		if(localName.equals("description")) {	
				//������һ��������description��ǩ
			if(a == true) {
				currentstate = RSS_DESCRIPTION;
				return;
			} else {
				a = true;
				return;
			}
		}
		//����
		if(localName.equals("link")) {
			currentstate = RSS_LINK;
			return;
		}
		//����
		if(localName.equals("pubDate")) {
			currentstate = RSS_PUBDATE;
			return;
		}
		currentstate = 0;
	}
	//��ǩ����
	@Override
	public void endElement(String uri, String localName, String qName)	
			throws SAXException {
		//����Ϣ��ӵ�rssFeed��
		if(localName.equals("item")) {
			rssFeed.addItem(rssItem);
			return;
		}
	}
	//������ǩ����ı�
	@Override
	public void characters(char[] ch, int start, int length)
			throws SAXException {
		if(length <= 5) return ;
		String theString = new String(ch, start, length);
		switch (currentstate) {
		//����
		case RSS_TITLE:
			rssItem.setTitle(theString);
			Log.e("title",theString);
			currentstate = 0;
			break;
			//����
		case RSS_LINK:
			rssItem.setLink(theString);
			currentstate = 0;
			break;
			//��ϸ��Ϣ
		case RSS_DESCRIPTION:
			System.out.println("RSS_DESCRIPTION=" + theString);		
			if(a == true) {
				rssItem.setDescription(theString);
				currentstate = 0;
			}else {			
				a = true;
			}
			break;
			//����
		case RSS_PUBDATE:
			rssItem.setPubDate(theString);
			currentstate = 0;
			break;
		default:
			return;
		}
	}
}