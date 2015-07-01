package wyf.zcl;
import java.io.File;				//������ذ�
import java.io.FileInputStream;		//������ذ�
import android.app.Activity;		//������ذ�
import android.os.Bundle;			//������ذ�
import android.view.View;			//������ذ�
import android.widget.Button;		//������ذ�
import android.widget.EditText;		//������ذ�
import android.widget.Toast;		//������ذ�
public class MyActivity extends Activity {
    /** Called when the activity is first created. */
	Button but;				//�򿪰�ť����
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        but=(Button)findViewById(R.id.Button01);
        								//�򿪰�ť��ʼ��
        but.setOnClickListener(new View.OnClickListener() {
        								//Ϊ�򿪰�ť��Ӽ�����
			@Override
			public void onClick(View v) {
				String contentResult=loadContentFromSDCard("AndroidSummary.txt");
										//���ö�ȡ�ļ�����������ļ�����
				EditText etContent=(EditText)findViewById(R.id.EditText01);	
										//ʵ����EditText
				etContent.setText(contentResult);
										//����EditText������
			}
		});
    }
    public String loadContentFromSDCard(String fileName){
    	//��SD����ȡ����
    	String content=null;		//sd�� �������ַ���
    	try{
    		File f=new File("/sdcard/"+fileName);//����ȡ���ļ�
    		int length=(int)f.length();
    		byte[] buff=new byte[length];
    		FileInputStream fis=new FileInputStream(f);
    		fis.read(buff);	// �Ӵ��������н� byte.length ���ֽڵ����ݶ���һ�� byte ������
    		fis.close();	//�رմ����������ͷ����������������ϵͳ��Դ
    		content=new String(buff,"UTF-8");
    	}catch(Exception e){
    		Toast.makeText(this, "�Բ���û���ҵ��ļ�", 
    				Toast.LENGTH_SHORT).show();
    	}
		return content;
    }
}