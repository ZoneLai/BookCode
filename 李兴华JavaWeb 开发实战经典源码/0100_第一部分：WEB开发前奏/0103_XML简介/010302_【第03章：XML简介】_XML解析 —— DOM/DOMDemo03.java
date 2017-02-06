package org.lxh.xml.dom ;
import java.io.* ;
import org.w3c.dom.* ;
import javax.xml.parsers.* ;
import javax.xml.transform.* ;
import javax.xml.transform.dom.* ;
import javax.xml.transform.stream.* ;

public class DOMDemo03 {
	public static void main(String args[]) throws Exception {
		// ȡ��DocumentBuilderFactory��Ķ���
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance() ;
		// ȡ��DocumentBuilder��Ķ���
		DocumentBuilder build = factory.newDocumentBuilder()  ;
		Document doc = build.newDocument() ;	// ����һ���µ�XML�ĵ�
		Element addresslist = doc.createElement("addresslist") ;
		Element linkman = doc.createElement("linkman") ;
		Element name = doc.createElement("name") ;
		Element email = doc.createElement("email") ;
		// ���ýڵ�����
		name.appendChild(doc.createTextNode("���˻�")) ;
		email.appendChild(doc.createTextNode("mldnqa@163.com")) ;
		// �����ø����ڵ�Ĺ�ϵ
		linkman.appendChild(name) ;	// name��linkeman���ӽڵ�
		linkman.appendChild(email) ;	// email��linkman���ӽڵ�
		addresslist.appendChild(linkman) ;
		doc.appendChild(addresslist) ;
		TransformerFactory tf = TransformerFactory.newInstance() ;
		Transformer t = tf.newTransformer() ;
		t.setOutputProperty(OutputKeys.ENCODING, "GBK")  ;	// �������ĵ�
		DOMSource source = new DOMSource(doc) ;	// ׼������ĵ�
		StreamResult result = new StreamResult(new File("d:"+File.separator+"output.xml")) ;
		t.transform(source,result) ;
	}
}