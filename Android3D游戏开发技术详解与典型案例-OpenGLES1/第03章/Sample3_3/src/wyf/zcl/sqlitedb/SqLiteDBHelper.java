package wyf.zcl.sqlitedb;
import android.content.Context;								//������ذ�
import android.database.sqlite.SQLiteDatabase;				//������ذ�
import android.database.sqlite.SQLiteOpenHelper;			//������ذ�
import android.database.sqlite.SQLiteDatabase.CursorFactory;//������ذ�
public class SqLiteDBHelper extends SQLiteOpenHelper{
	public SqLiteDBHelper(Context context, String name, CursorFactory factory,
			int version) {//�̳�SQLiteOpenHelper���࣬�����иù��캯��
		super(context, name, factory, version);
	}
	@Override
	public void onCreate(SQLiteDatabase db) {
	//�������ݿ�ʱ����,�˷������ڵ�����getReadableDatabase()��getWritableDatabase()��ŵ���
		db.execSQL("create table sqlitetest(uid long,uname varchar(25))");
		System.out.println("already create a database:sqlitetest.");
	}
	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
	//�������ݿ�ʱ����
	}
}
