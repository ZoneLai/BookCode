package org.lxh.xml.jdom ;
import java.io.* ;
import java.util.* ;
import org.jdom.* ;
import org.jdom.input.* ;
public class ReadXML {
	public static void main(String args[]) throws Exception {
		SAXBuilder builder = new SAXBuilder() ;
		Document read_doc = builder.build(new File("D:" + File.separator + "address.xml")) ;
		Element root = read_doc.getRootElement() ;	// ȡ�ø�
		List list = root.getChildren("linkman") ;	// �õ����е�linkman
		for(int x=0;x<list.size();x++){
			Element e = (Element) list.get(x) ;
			String name = e.getChildText("name") ;	// �õ�name�ӽڵ������
			String id = e.getChild("name").getAttribute("id").getValue() ;
			String email = e.getChildText("email") ;
			System.out.println("-------------- ��ϵ�� -------------") ;
			System.out.println("������" + name + "����ţ�" + id) ;
			System.out.println("EMAIL��" + email) ;
			System.out.println("-----------------------------------") ;
			System.out.println() ;
		}
	}
}