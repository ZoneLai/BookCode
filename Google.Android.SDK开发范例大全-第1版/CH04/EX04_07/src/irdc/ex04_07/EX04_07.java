package irdc.ex04_07;


import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

public class EX04_07 extends Activity
{
  /*宣告 Button、ImageView物件*/
  private ImageView mImageView01;
  private ImageView mImageView02;
  private Button mButton01;
  private Button mButton02;
  
  /** Called when the activity is first created. */
  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.main);
    
    /*取得 Button、ImageView物件*/
    mImageView01 = (ImageView)findViewById(R.id.myImageView1);
    mImageView02 = (ImageView)findViewById(R.id.myImageView2);
    mButton01 = (Button) findViewById(R.id.myButton1);
    mButton02 = (Button) findViewById(R.id.myButton2);
    
    /*設定ImageView底圖*/
    mImageView01.setImageDrawable(getResources().
                 getDrawable(R.drawable.right)); 
    mImageView02.setImageDrawable(getResources().
                 getDrawable(R.drawable.oa));
    
    /*用OnClickListener事件來啟動*/
    mButton01.setOnClickListener(new Button.OnClickListener()
    {
      @Override
      public void onClick(View v)
     {
      /*當啟動後，ImageView立刻換底圖*/ 
      mImageView01.setImageDrawable(getResources().
                   getDrawable(R.drawable.right));
     }
   });
    
    mButton02.setOnClickListener(new Button.OnClickListener()
    {
      @Override
      public void onClick(View v)
     {
      mImageView01.setImageDrawable(getResources().
                   getDrawable(R.drawable.left));
     }
   });
    
  }
}