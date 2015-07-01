package wyf.zcl;
import java.io.ByteArrayOutputStream;		//������ذ�
import java.io.InputStream;					//������ذ�
import android.app.Activity;				//������ذ�
import android.os.Bundle;					//������ذ�
import android.view.View;					//������ذ�
import android.widget.Button;				//������ذ�
import android.widget.EditText;				//������ذ�
import android.widget.Toast;				//������ذ�
public class MyActivity extends Activity {
    /** Called when the activity is first created. */
	private Button but;//�򿪰�ť
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        but=(Button)findViewById(R.id.Button01);//�򿪰�ťʵ����
        but.setOnClickListener(new View.OnClickListener() {//�򿪰�ť��Ӽ�����
			@Override
			public void onClick(View v) {
				String contentResult=loadFromAssert("AndroidSummary.txt");
				EditText etContent=(EditText)findViewById(R.id.EditText01);	
				etContent.setText(contentResult);
			}
		});
    }
    public String loadFromAssert(String fileName){
    	String content=null;//����ַ���
    	try{
    		InputStream is=this.getResources().getAssets().open(fileName);//���ļ�
    		int ch=0;
    		 ByteArrayOutputStream baos = new ByteArrayOutputStream();//ʵ����һ�������
    		 while((ch=is.read())!=-1){
 		      	baos.write(ch);					// ��ָ�����ֽ�д��� byte �����������									
 		    }
    		 byte[] buff=baos.toByteArray();	//�� byte �������ʽ���ش�������ĵ�ǰ����
    		 baos.close();						//�ر���
    		 is.close();						//�ر���
    		 content=new String(buff,"UTF-8"); 	//�����ַ�������
    	}catch(Exception e){
    		Toast.makeText(this, "�Բ���û���ҵ�ָ���ļ���", Toast.LENGTH_SHORT).show();
    	} 
    	return content;
    }
}