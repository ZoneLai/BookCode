package wyf.zcl;
import java.util.Date;								//������ذ�
import android.app.Activity;						//������ذ�
import android.content.Context;						//������ذ�
import android.content.SharedPreferences;			//������ذ�
import android.os.Bundle;							//������ذ�
import android.widget.TextView;						//������ذ�
import android.widget.Toast;						//������ذ�
public class MyActivity extends Activity {
    /** Called when the activity is first created. */
	private TextView tv;
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        SharedPreferences sp=this.getSharedPreferences("sharePre", Context.MODE_PRIVATE);
        //����һ��SharedPreferencesʵ������һ��������Preferences���֣��ڶ���������ʹ��Ĭ�ϵĲ���
        String lastLogin=sp.getString(				//��SharedPreferences�ж�ȡ�ϴη��ʵ�ʱ��
        		"ll",								//��ֵ
        		null								//Ĭ��ֵ
        );
        if(lastLogin==null){
        	lastLogin="��ӭ�������ǵ�һ�η��ʱ�Preferences";
        }else{
        	lastLogin="��ӭ���������ϴ���"+lastLogin+"��¼";
        }
        //��SharedPreferences��д�ر��η���ʱ��
        SharedPreferences.Editor editor=sp.edit();
        editor.putString("ll", new Date().toLocaleString());	//��editor�з������ڵ�ʱ��
        editor.commit();										//�ύeditor
        tv=(TextView)this.findViewById(R.id.TextView01);
        tv.setText(lastLogin);
    }
}