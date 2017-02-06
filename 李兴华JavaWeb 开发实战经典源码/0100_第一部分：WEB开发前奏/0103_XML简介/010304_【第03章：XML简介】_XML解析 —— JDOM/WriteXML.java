package org.lxh.xml.jdom ;
import java.io.* ;
import org.jdom.* ;
import org.jdom.output.* ;
public class WriteXML {
	public static void main(String args[]) throws Exception {
		Element addresslist = new Element("addresslist") ;
		Element linkman = new Element("linkman") ;
		Element name = new Element("name") ;
		Element email = new Element("email") ;
		Attribute id = new Attribute("id","lxh") ;
		Document doc = new Document(addresslist) ;	// ����Document����
		name.setText("���˻�") ;
		name.setAttribute(id) ;	// ���������õ�Ԫ��֮��
		email.setText("mldnqa@163.com") ;
		linkman.addContent(name) ;	// ���ù�ϵ
		linkman.addContent(email) ;
		addresslist.addContent(linkman) ;
		XMLOutputter out = new XMLOutputter() ;
		out.setFormat(out.getFormat().setEncoding("GBK")) ;	// ��ʾ�������ñ���
		out.output(doc,new FileOutputStream(new File("D:" + File.separator + "address.xml"))) ;
	}
}