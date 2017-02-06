package org.lxh.xml.dom ;
import java.io.* ;
import org.w3c.dom.* ;
import javax.xml.parsers.* ;
public class DOMDemo {
	public static void main(String args[]) throws Exception {
		// ȡ��DocumentBuilderFactory��Ķ���
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance() ;
		// ȡ��DocumentBuilder��Ķ���
		DocumentBuilder build = factory.newDocumentBuilder()  ;
		Document doc = build.parse(new File("D:" + File.separator + "dom_demo_02.xml")) ;
		NodeList nl = doc.getElementsByTagName("name") ;
		// ����ڵ�
		System.out.println("������" + nl.item(0).getFirstChild().getNodeValue()) ;
	}
}