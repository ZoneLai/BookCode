package com.supermario.autocompletedemo;
import android.app.Activity;
import android.os.Bundle;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
public class AutoCompleteDemo extends Activity {
    //����һ���ַ������飬����Ϊadapter�ṩ������Դ
	String GAME[]=new String[]{"game1","gam2","gamm3","gamek3"};
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        AutoCompleteTextView auto=(AutoCompleteTextView)findViewById(R.id.autoCompleteTextView1);
        //���ɽ�����������adapter�������ݣ��趨����ΪR.layout.list_view
        ArrayAdapter<String> adapter=new ArrayAdapter<String>(this,R.layout.list_view,GAME);
        //ΪAutoCompleteTextView�趨������
        auto.setAdapter(adapter);
    }
}