package wyf.zcl;
import wyf.zcl.sqlitedb.SqLiteDBHelper;				//������ذ�
import android.app.Activity;						//������ذ�
import android.content.ContentValues;				//������ذ�
import android.database.Cursor;						//������ذ�
import android.database.sqlite.SQLiteDatabase;		//������ذ�
import android.os.Bundle;							//������ذ�
import android.view.View;							//������ذ�
import android.widget.Button;						//������ذ�	
import android.widget.Toast;
public class MyActivity extends Activity {
    /** Called when the activity is first created. */
	private Button createButton;		//�������ݿⰴť
	private Button insertBut;			//�������ݿ��¼��ť
	private Button updateBut;			//�������ݿ��¼��ť
	private Button queryBut;			//��ѯ���ݿ��¼��ť
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        createButton=(Button)findViewById(R.id.ButtonCreate);	//ʵ�����������ݿⰴť
        insertBut=(Button)findViewById(R.id.ButtonInsert);		//ʵ�����������ݿⰴť
        updateBut=(Button)findViewById(R.id.ButtonUpdate);		//ʵ�����������ݿⰴť
        queryBut=(Button)findViewById(R.id.ButtonQuery);		//ʵ������ѯ���ݿⰴť
        createButton.setOnClickListener(new View.OnClickListener() {//�������ݿ�ʱ����
			@Override
			public void onClick(View v) {
				SqLiteDBHelper dh=new SqLiteDBHelper(MyActivity.this,"testdb",null,1);//�������ݿ�
				System.out.println("create or open database success!");
				SQLiteDatabase sld=dh.getReadableDatabase();
				//�õ�һ��SQLiteDatabase�������ڲٿ����ݿ�
				Toast.makeText(MyActivity.this,	 "����������ݿ�", Toast.LENGTH_SHORT).show();	
		}});
        insertBut.setOnClickListener(new View.OnClickListener() {//�������ݿ��¼ʱ����
			@Override
			public void onClick(View v) {
				ContentValues cv=new ContentValues();	
				//�õ�ContentValues����
				cv.put("uid", 1);						
												//�����ֵ�ԣ���Ҫ������һ�£�ֵҪ���е���������һ��
				cv.put("uname", "zcl");					
												//�����ֵ�ԣ���Ҫ������һ�£�ֵҪ���е���������һ��
				SqLiteDBHelper dh=new SqLiteDBHelper(MyActivity.this,"testdb",null,1);//�������ݿ�	
				Toast.makeText(MyActivity.this,	 "�����¼", Toast.LENGTH_SHORT).show();								
				SQLiteDatabase sld=dh.getWritableDatabase();
												//�õ�һ��SQLiteDatabase�������ڲٿ����ݿ�
				sld.insert("sqlitetest", null, cv);//�������ݿ��¼			
				System.out.println("success insert a new content!");								
		}});
        updateBut.setOnClickListener(new View.OnClickListener() {
        										//�������ݿ��¼ʱ����
			@Override
			public void onClick(View v) {
				SqLiteDBHelper dh=new SqLiteDBHelper(MyActivity.this,"testdb",null,1);
												//�������ݿ�
				SQLiteDatabase sld=dh.getWritableDatabase();	
												//�õ�һ��SQLiteDatabase�������ڲٿ����ݿ�
				ContentValues cv = new ContentValues();	//�õ�ContentValues����
				Toast.makeText(MyActivity.this,	 "���¼�¼", Toast.LENGTH_SHORT).show();										
				cv.put("uname", "zcl_update");
				sld.update("sqlitetest", cv, "uid=?", new String[]{"1"});//�������ݿ��¼
				System.out.println("success updata the content!");								
		}});
        queryBut.setOnClickListener(new View.OnClickListener() {
        										//��ѯ���ݿ��¼ʱ����
			@Override
			public void onClick(View v) {
				SqLiteDBHelper dh=new SqLiteDBHelper(MyActivity.this,"testdb",null,1);//�������ݿ�
				Toast.makeText(MyActivity.this,	 "��ѯ��¼", Toast.LENGTH_SHORT).show();										
				SQLiteDatabase sld=dh.getReadableDatabase();
												//�õ�һ��SQLiteDatabase�������ڲٿ����ݿ�
				Cursor cursor=sld.query("sqlitetest", new String[]{"uid","uname"}, "uid=?", 
						new String[]{"1"}, null, null, null);	
				while(cursor.moveToNext()){				//��ӡ���
					String name=cursor.getString(cursor.getColumnIndex("uname"));
					System.out.println("query result:"+name);
		}}});
    }
}