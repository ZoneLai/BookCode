package wyf.jsc.rtb;

import static wyf.jsc.rtb.Constant.*;
public class RotateThread extends Thread
{
   int function;//��ת��ʽ  0-С��˳ʱ�� 1-С����ʱ��  2-����˳ʱ�� 3-������ʱ��
   Cube cube;
   int afterState;
   float afterXOffset;
   float afterZOffset;   
   
   public RotateThread()
   {   
   }
   
   public RotateThread(int function,Cube cube,int afterState,float afterXOffset,float afterZOffset)
   {
	   this.function=function;
	   this.cube=cube;
	   this.afterState=afterState;
	   this.afterXOffset=afterXOffset;
	   this.afterZOffset=afterZOffset;		   
   }
   
   public void run()
   {	  
	  if(function==0)
	  {//0-0˳ʱ����ת
		   float angle=0;
		   while(angle<90)
		   {
			  cube.tempCenterX=(float)(-Math.cos(Math.toRadians(angle+45))*cube.rSmall)+cube.unitLocalSize;
			  cube.tempCenterY=(float)(Math.sin(Math.toRadians(angle+45))*cube.rSmall)-cube.unitLocalSize;
		      cube.angleZ=-angle;
			  angle+=10f;
			  
			  try
			  {
				  Thread.sleep(40);
			  }
			  catch(Exception e)
			  {
				  e.printStackTrace();
			  }
		   }   
	  }
	  else if(function==1)
	  {//0-0��ʱ����ת
		   float angle=0;
		   while(angle<90)
		   {
			  cube.tempCenterX=(float)(Math.cos(Math.toRadians(angle+45))*cube.rSmall)-cube.unitLocalSize;
			  cube.tempCenterY=(float)(Math.sin(Math.toRadians(angle+45))*cube.rSmall)-cube.unitLocalSize;
		      cube.angleZ=angle;
			  angle+=10f;
			  
			  try
			  {
				  Thread.sleep(40);
			  }
			  catch(Exception e)
			  {
				  e.printStackTrace();
			  }
		   }
	  }
	  else if(function==2)
	  {//0-1˳ʱ��
		  float angle=0;
		   while(angle<90)
		   {
			  cube.tempCenterZ=(float)(Math.cos(Math.toRadians(angle+26.565))*cube.rBig)-2*cube.unitLocalSize;
			  cube.tempCenterY=(float)(Math.sin(Math.toRadians(angle+26.565))*cube.rBig)-cube.unitLocalSize;
		      cube.angleX=-angle;
			  angle+=10f;
			  
			  try
			  {
				  Thread.sleep(40);
			  }
			  catch(Exception e)
			  {
				  e.printStackTrace();
			  }
		   }
	  }
	  else if(function==3)
	  {//0-1��ʱ��
		  float angle=0;
		   while(angle<90)
		   {
			  cube.tempCenterZ=(float)(-Math.cos(Math.toRadians(angle+26.565))*cube.rBig)+2*cube.unitLocalSize;
			  cube.tempCenterY=(float)(Math.sin(Math.toRadians(angle+26.565))*cube.rBig)-cube.unitLocalSize;
		      cube.angleX=angle;
			  angle+=10f;
			  
			  try
			  {
				  Thread.sleep(40);
			  }
			  catch(Exception e)
			  {
				  e.printStackTrace();
			  }
		   }
	  }
	  else if(function==4)
	  {//1-2˳ʱ��
		  float angle=0;
		   while(angle<90)
		   {
			  cube.tempCenterX=(float)(-Math.cos(Math.toRadians(angle+63.435))*cube.rBig)+cube.unitLocalSize;
			  cube.tempCenterZ=(float)(-Math.sin(Math.toRadians(angle+63.435))*cube.rBig)+2*cube.unitLocalSize;
		      cube.angleY=-angle;
			  angle+=10f;
			  
			  try
			  {
				  Thread.sleep(40);
			  }
			  catch(Exception e)
			  {
				  e.printStackTrace();
			  }
		   }
	  }
	  else if(function==5)
	  {//1-2��ʱ��
		  float angle=0;
		   while(angle<90)
		   {
			  cube.tempCenterX=(float)(Math.cos(Math.toRadians(angle+63.435))*cube.rBig)-cube.unitLocalSize;
			  cube.tempCenterZ=(float)(-Math.sin(Math.toRadians(angle+63.435))*cube.rBig)+2*cube.unitLocalSize;
		      cube.angleY=angle;
			  angle+=10f;
			  
			  try
			  {
				  Thread.sleep(40);
			  }
			  catch(Exception e)
			  {
				  e.printStackTrace();
			  }
		   }
	  }
	  else if(function==6)
	  {//1-0˳ʱ��
		  float angle=0;
		   while(angle<90)
		   {
			  cube.tempCenterY=(float)(Math.cos(Math.toRadians(angle+63.435))*cube.rBig)-cube.unitLocalSize;
			  cube.tempCenterZ=(float)(-Math.sin(Math.toRadians(angle+63.435))*cube.rBig)+2*cube.unitLocalSize;
		      cube.angleX=-angle;
			  angle+=10f;
			  
			  try
			  {
				  Thread.sleep(40);
			  }
			  catch(Exception e)
			  {
				  e.printStackTrace();
			  }
		   }
	  }
	  else if(function==7)
	  {//1-0��ʱ��
		  float angle=0;
		   while(angle<90)
		   {
			  cube.tempCenterY=(float)(-Math.cos(Math.toRadians(angle+63.435))*cube.rBig)+cube.unitLocalSize;
			  cube.tempCenterZ=(float)(-Math.sin(Math.toRadians(angle+63.435))*cube.rBig)+2*cube.unitLocalSize;
		      cube.angleX=angle;
			  angle+=10f;
			  
			  try
			  {
				  Thread.sleep(40);
			  }
			  catch(Exception e)
			  {
				  e.printStackTrace();
			  }
		   }
	  }
	  else if(function==8)
	  {//2-1˳ʱ��
		  float angle=0;
		   while(angle<90)
		   {
			  cube.tempCenterY=(float)(Math.sin(Math.toRadians(angle+26.565))*cube.rBig)-cube.unitLocalSize;
			  cube.tempCenterZ=(float)(-Math.cos(Math.toRadians(angle+26.565))*cube.rBig)+2*cube.unitLocalSize;
		      cube.angleX=angle;
			  angle+=10f;
			  
			  try
			  {
				  Thread.sleep(40);
			  }
			  catch(Exception e)
			  {
				  e.printStackTrace();
			  }
		   }
	  }
	  else if(function==9)
	  {//2-1 ��ʱ��
		  float angle=0;
		   while(angle<90)
		   {
			  cube.tempCenterY=(float)(Math.sin(Math.toRadians(angle+26.565))*cube.rBig)-cube.unitLocalSize;
			  cube.tempCenterZ=(float)(Math.cos(Math.toRadians(angle+26.565))*cube.rBig)-2*cube.unitLocalSize;
		      cube.angleX=-angle;
			  angle+=10f;
			  
			  try
			  {
				  Thread.sleep(40);
			  }
			  catch(Exception e)
			  {
				  e.printStackTrace();
			  }
		   }
	  }
	  
	  //����Ŷ�
	  cube.tempCenterX=0;
	  cube.tempCenterY=0;
	  cube.tempCenterZ=0;
	  cube.angleX=0;
	  cube.angleY=0;
	  cube.angleZ=0;
	  
	  
	  //������ɺ�����״̬
	  cube.zOffset=this.afterZOffset;
	  cube.xOffset=this.afterXOffset;
	  cube.state=this.afterState;
	  
	  anmiFlag=false;
   }
}
