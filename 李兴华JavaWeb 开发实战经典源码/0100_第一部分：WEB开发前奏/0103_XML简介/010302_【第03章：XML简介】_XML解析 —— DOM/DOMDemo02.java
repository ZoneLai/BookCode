package org.lxh.xml.dom ;
import java.io.* ;
import org.w3c.dom.* ;
import javax.xml.parsers.* ;
public class DOMDemo02 {
	public static void main(String args[]) throws Exception {
		// ȡ��DocumentBuilderFactory��Ķ���
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance() ;
		// ȡ��DocumentBuilder��Ķ���
		DocumentBuilder build = factory.newDocumentBuilder()  ;
		Document doc = build.parse(new File("D:" + File.separator + "dom_demo_01.xml")) ;
		// �õ����е�linkman�ڵ�
		NodeList nl = doc.getElementsByTagName("linkman") ;
		for(int x=0;x<nl.getLength();x++){
			Element e = (Element) nl.item(x) ;	// ȡ��ÿһ��Ԫ��
			System.out.println("������" + e.getElementsByTagName("name").item(0).getFirstChild().getNodeValue()) ;
			System.out.println("���䣺" + e.getElementsByTagName("email").item(0).getFirstChild().getNodeValue()) ;
		}
	}
}