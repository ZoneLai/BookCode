package org.lxh.xml.dom4j ;
import java.io.* ;
import java.util.* ;
import org.dom4j.* ;
import org.dom4j.io.* ;
public class DOM4JReader {
	public static void main(String args[]) throws Exception {
		File file = new File("d:" + File.separator + "output.xml") ;
		SAXReader reader = new SAXReader() ;
		Document doc = reader.read(file) ;	// ��ȡXML�ļ�
		// JDOM������ʱ����Ҫȡ�ø��ڵ�
		Element root = doc.getRootElement() ;	// ȡ�ø��ڵ�
		// ����Ӧ�ø��ݸ��ڵ��ҵ�ȫ�����ӽڵ㣬linkman
		Iterator iter = root.elementIterator() ;
		while(iter.hasNext()){
			Element linkman = (Element) iter.next() ;
			System.out.println("������" + linkman.elementText("name")) ;
			System.out.println("�ʼ���" + linkman.elementText("email")) ;
		}
	}
}