package wyf.zcl;
import android.app.Activity;
import android.os.Bundle;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.RatingBar;
import android.widget.SeekBar;
import android.widget.Toast;
import android.widget.ToggleButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
public class MyActivity extends Activity {
    /** Called when the activity is first created. */
	MySurfaceView msv;
	RatingBar rb;										//��������������
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        msv=new MySurfaceView(this);					//ʵ����SurfaceView����
        setContentView(R.layout.main);					//����Activity����
        rb=(RatingBar)findViewById(R.id.RatingBar01);
        msv.requestFocus();								//��ȡ����
        msv.setFocusableInTouchMode(true);				//����Ϊ�ɴ���
        LinearLayout lla=(LinearLayout)findViewById(R.id.lla);
        lla.addView(msv);
       rb.setOnRatingBarChangeListener(new RatingBar.OnRatingBarChangeListener() {
		@Override										//Ϊ
		public void onRatingChanged(RatingBar ratingBar, float rating,
				boolean fromUser) {
			if(rating>=0&&rating<=1){	//RatingBar�ı仯���ı俪���ƹ��������
				msv.openLightNum=1;
			}else if(rating>1&&rating<=2){
				msv.openLightNum=2;
			}else if(rating>2&&rating<=3){
				msv.openLightNum=3;
			}else if(rating>3&&rating<=4){
				msv.openLightNum=4;
			}else if(rating>4&&rating<=5){
				msv.openLightNum=5;
			}
			Toast.makeText(MyActivity.this, "������"+msv.openLightNum+"ջ��", Toast.LENGTH_SHORT).show();
		}});}
	@Override
	protected void onPause() {
		super.onPause();
		msv.onPause();
	}
	@Override
	protected void onResume() {
		super.onResume();
		msv.onResume();
	}
}