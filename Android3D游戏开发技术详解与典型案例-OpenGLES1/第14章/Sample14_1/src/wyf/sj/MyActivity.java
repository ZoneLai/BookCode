package wyf.sj;
import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.AdapterView.OnItemSelectedListener;
public class MyActivity extends Activity {
	int[] searchMsgId=//�����㷨
			{
			R.string.depthFirstSearch,R.string.breadthFirstSearch,
			R.string.breadthFirstSearchA,R.string.Dijkstra,
			R.string.DijkstraA
			};
	int[] targetId=//Ŀ���
			{
					R.string.tA,R.string.tB,R.string.tC,R.string.tD,R.string.tE
			};
	MySurfaceView mySurfaceView;//��������
	Button button;//��ʼ��ť
	TextView textViewSybz;//ʹ�ò���
	TextView textViewLjcd;//·������
	Handler hd;//��Ϣ������
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        mySurfaceView = new MySurfaceView(this);
        //this.setContentView(mySurfaceView);
        LinearLayout ly=(LinearLayout)findViewById(R.id.LinearLayout02);
        ly.addView(mySurfaceView);
        
        button=(Button)findViewById(R.id.Button01);//ͨ��ID���Button
        textViewSybz=(TextView)findViewById(R.id.TextView01);//ͨ��ID���ʹ�ò���TextView
        textViewLjcd=(TextView)findViewById(R.id.TextView02);//ͨ��ID���ʹ�ò���TextView
        Spinner spinnerSearch=(Spinner)findViewById(R.id.Spinner01);//����������������б�
        
        //ΪspinnerSearch׼������������
        BaseAdapter ba=new BaseAdapter()
        {
			@Override
			public int getCount() {
				return 5;//�ܹ����ѡ��
			}

			@Override
			public Object getItem(int arg0) { return null; }

			@Override
			public long getItemId(int arg0) { return 0; }

			@Override
			public View getView(int arg0, View arg1, ViewGroup arg2) {
				//��ʼ��LinearLayout
				LinearLayout ll=new LinearLayout(MyActivity.this);
				ll.setOrientation(LinearLayout.HORIZONTAL);		//���ó���	

				
				//��ʼ��TextView
				TextView tv=new TextView(MyActivity.this);
				tv.setText(" "+getResources().getText(searchMsgId[arg0]));//��������
				tv.setTextSize(20);//���������С
				tv.setTextColor(Color.BLACK);//���������ɫ
				ll.addView(tv);//��ӵ�LinearLayout��
				
				return ll;
			}
		};
		spinnerSearch.setAdapter(ba);//ΪSpinner��������������
		
		//����ѡ��ѡ�еļ�����
		spinnerSearch.setOnItemSelectedListener(
           new OnItemSelectedListener()
           {
			@Override
			public void onItemSelected(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {//��дѡ�ѡ���¼��Ĵ�����
				mySurfaceView.game.algorithmId=arg2;
				Log.d(mySurfaceView.game.algorithmId+"", "mySurfaceView.game.algorithmId");
			}

			@Override
			public void onNothingSelected(AdapterView<?> arg0) { }        	   
           }
        );
        
        Spinner spinnerTarget=(Spinner)findViewById(R.id.Spinner02);//����������������б�
        //ΪspinnerTarget׼������������
        BaseAdapter baTarget=new BaseAdapter()
        {
			@Override
			public int getCount() {
				return 5;//�ܹ����ѡ��
			}

			@Override
			public Object getItem(int arg0) { return null; }

			@Override
			public long getItemId(int arg0) { return 0; }

			@Override
			public View getView(int arg0, View arg1, ViewGroup arg2) {
				//��ʼ��LinearLayout
				LinearLayout ll=new LinearLayout(MyActivity.this);
				ll.setOrientation(LinearLayout.HORIZONTAL);		//���ó���	

				
				//��ʼ��TextView
				TextView tv=new TextView(MyActivity.this);
				tv.setText(" "+getResources().getText(targetId[arg0]));//��������
				tv.setTextSize(20);//���������С
				tv.setTextColor(Color.BLACK);//���������ɫ
				ll.addView(tv);//��ӵ�LinearLayout��
				
				return ll;
			}
		};
		spinnerTarget.setAdapter(baTarget);//ΪSpinner��������������
		//����ѡ��ѡ�еļ�����
		spinnerTarget.setOnItemSelectedListener(
           new OnItemSelectedListener()
           {
			@Override
			public void onItemSelected(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {//��дѡ�ѡ���¼��Ĵ�����
				mySurfaceView.game.target=MapList.targetA[arg2];
				mySurfaceView.game.clearState();//���״̬
				mySurfaceView.repaint(mySurfaceView.getHolder());//�ػ� 
			}

			@Override
			public void onNothingSelected(AdapterView<?> arg0) { }        	   
           }
        );
		button.setOnClickListener
		(
				new OnClickListener()
				{

					@Override
					public void onClick(View v) {
						// TODO Auto-generated method stub
						
						mySurfaceView.game.runAlgorithm();//���÷���
						button.setClickable(false);//����Ϊ���ɵ��
					}
				
					
				}
		);
		hd=new Handler()
		{
			 @Override
	        	public void handleMessage(Message msg)
				 {
					 super.handleMessage(msg);
					 switch(msg.what)
					 {
					 	case 1://����ʹ�ò���
					 	case 2:
					 	case 3:
					 	case 4:
					 	case 5:textViewSybz.setText("ʹ�ò�����"+mySurfaceView.game.tempCount);break;
					 	case 6:textViewLjcd.setText("·�����ȣ�"+mySurfaceView.LjcdCount);break;//����·������
					 }
				 }
		 };
		 
		
    }
}