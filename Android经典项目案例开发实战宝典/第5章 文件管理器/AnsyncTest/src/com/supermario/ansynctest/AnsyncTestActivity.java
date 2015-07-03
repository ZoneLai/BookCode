package com.supermario.ansynctest;
import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
public class AnsyncTestActivity extends Activity {
    /** Called when the activity is first created. */    
    TextView text =null;
    Button button=null;
    String str=null;
    AnsyTry anys=null;
    double result=0;   
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        //��ʼ������Ԫ��
        text=(TextView) findViewById(R.id.text);
        button=(Button) findViewById(R.id.button);
        //��������һ������
        str="flag";
        //���ü�����
        button.setOnClickListener(new OnClickListener() {           
            @Override
            public void onClick(View v) {
                // TODO Auto-generated method stub
                anys=new AnsyTry(text);
                //ִ���߳�
                anys.execute(str);                
            }
        });
    }       
    class AnsyTry extends AsyncTask<String, TextView, Double>{       
        TextView te=null;     
        public AnsyTry(TextView te) {
            super();
            this.te = te;
        }
        //ִ�к�̨����
        @Override
        protected Double doInBackground(String... params) {
            // TODO Auto-generated method stub
            double dou=0;
            if(params[0].equals("flag")){
            	//��ʾ��ǰ�̵߳�����
            	Log.e("ansync",Thread.currentThread().getName()+"");
                dou=100;
            }
            publishProgress(te);
            return dou;
        }
        //��̨����ִ�����
        @Override
        protected void onPostExecute(Double result) {
            // TODO Auto-generated method stub
            super.onPostExecute(result);
            Log.e("ansync","postExecute---double---"+result);
        }
        //��̨����ִ��֮ǰ
        @Override
        protected void onPreExecute() {
            // TODO Auto-generated method stub\
        	Log.e("ansync","pretExecute------");
            super.onPreExecute();
        }
        //���ڸ��½���
        @Override
        protected void onProgressUpdate(TextView... values) {
            // TODO Auto-generated method stub
        	//����TextView������
            values[0].setText(values[0].getText()+"A");
            super.onProgressUpdate(values);
        }        
    }
}