package irdc.ex03_10;

/* import相關class */
import java.text.DecimalFormat;
import java.text.NumberFormat;
import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

public class EX03_10_1 extends Activity 
{
  /** Called when the activity is first created. */
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    /* 載入main.xml Layout */
    setContentView(R.layout.myalyout);
    
    /* 取得Intent中的Bundle物件 */
    Bundle bunde = this.getIntent().getExtras();
    
    /* 取得Bundle物件中的資料 */
    String sex = bunde.getString("sex");
    double height = bunde.getDouble("height");
    
    /* 判斷性別 */
    String sexText="";
    if(sex.equals("M")){
    	sexText="男性";
    }else{
    	sexText="女性";
    }
    
    /* 取得標準體重 */
    String weight=this.getWeight(sex, height);
    
    /* 設定輸出文字 */
    TextView tv1=(TextView) findViewById(R.id.text1);
    tv1.setText("你是一位"+sexText+"\n你的身高是"+height+"公分\n你的標準體重是"+weight+"公斤");
  }
  
  /* 四捨五入的method */
  private String format(double num)
  {
    NumberFormat formatter = new DecimalFormat("0.00");
	String s=formatter.format(num);
	return s;
  }

  /* 以findViewById()取得Button物件，並加入onClickListener */	
  private String getWeight(String sex,double height)
  {
    String weight="";
	if(sex.equals("M"))
	{
	  weight=format((height-80)*0.7);
    }else
	{
	  weight=format((height-70)*0.6);
	}	
	return weight;
  }
}
