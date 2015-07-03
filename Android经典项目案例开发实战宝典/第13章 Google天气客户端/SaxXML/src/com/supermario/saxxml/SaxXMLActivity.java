package com.supermario.saxxml;

import java.util.ArrayList;  
import java.util.Iterator;  
import java.util.List;  
import javax.xml.parsers.SAXParserFactory;  
import org.xml.sax.InputSource;  
import org.xml.sax.XMLReader;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;

public class SaxXMLActivity extends Activity {  

	//�½�һ������
	private Button button;  
	//�½�һ���б�
	private ListView listView;
	//�½�һ�������б����ڴ���ַ�������
	private ArrayList<String> list=new ArrayList<String>();  
public void onCreate(Bundle savedInstanceState) {  
    super.onCreate(savedInstanceState);  
    setContentView(R.layout.main); 
    button=(Button)findViewById(R.id.btn1);  
    listView=(ListView) findViewById(R.id.listView1);
    //Ϊ�����󶨼�����
    button.setOnClickListener(new ButtonListener());  
}  

class ButtonListener implements OnClickListener{  

    @Override  
    public void onClick(View v) {  
	  //��������Ľ���洢��students��   
	   List<Student> students=parserXMl();
	   //ö�������е�Ԫ��
	   for (Iterator iterator = students.iterator(); iterator.hasNext();) {  
		   Student student = (Student) iterator.next();  
		   //���������ת�����ַ��������δ洢��list��
		   list.add(String.valueOf(student.getId())+" "+student.getName()+" "+student.getSpeciality()+" "+String.valueOf((student.getQQ())));  
	}  
	   //�½�һ��������daapter���ڸ�listview�ṩ����
	   ArrayAdapter<String> adapter=new ArrayAdapter<String>(SaxXMLActivity.this, android.R.layout.simple_list_item_1, list);  
	  //Ϊlistview��������
	   listView.setAdapter(adapter);  
    }  
   
      
}  
  //����xml�ļ�
private List<Student> parserXMl()  
{  
	//ʵ����һ��SAX��������
    SAXParserFactory factory=SAXParserFactory.newInstance();  
    List<Student>students=null;   
    try {
    //��ȡxml������
	XMLReader reader=factory.newSAXParser().getXMLReader();  
	students=new ArrayList<Student>();  
	reader.setContentHandler(new StudentHandler(students));  
	//����Assets�µ�student.xml�ļ�
	reader.parse(new InputSource(SaxXMLActivity.this.getResources().getAssets().open("student.xml"))); 
    } catch (Exception e) {  
	// TODO: handle exception   
    }
    return students;  
}  
}  