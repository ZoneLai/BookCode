package com.yarin.android.Examples_15_01;

import android.app.Activity;
import android.os.Bundle;

public class Activity01 extends Activity
{
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		
		try  
		{
			Testing  testing  =  (Testing)  Handler.newInstance(new  TestingImpl());
			testing.testArrayList();
			testing.testLinkedList();
		}catch  (Exception  e){
			e.printStackTrace();
		}
		setContentView(R.layout.main);
	}
}
