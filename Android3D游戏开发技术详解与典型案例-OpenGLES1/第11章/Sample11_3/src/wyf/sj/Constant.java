package wyf.sj;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;

public class Constant {

	public static final float DEGREE_SPAN=(float)(5.0/180.0f*Math.PI);//�����ÿ��ת���ĽǶ�
	public static final float MOVE_SPAN=0.8f;//�����ÿ���ƶ���λ��	
	public static final float UNIT_SIZE=4f;//ÿ��ĵ�λ����
	public static final float DIRECTION_INI=0.0f;//��ʼ���߷��� ��Z�Ḻ��Ϊ0�ȣ���Y��������ת
	public static final float DISTANCE=2.0f;//�����λ�þ���۲�Ŀ���ľ���
	
	public static final float LAND_HIGH_ADJUST=2f;//½�صĸ߶ȵ���ֵ
	public static final float WATER_HIGH_ADJUST=-0.2f;//ˮ��ĸ߶ȵ���ֵ
	public static final float LAND_HIGHEST=44f;//½�����߲�
	  
	public static float[][] yArray;//½����ÿ������ĸ߶�����
	public static int COLS;//½������
	public static int ROWS;//½������
	//�������ʼXYZ����
	public static float CAMERA_INI_X=0;  
	//public static float CAMERA_INI_Y=10;//ƽ��
	public static float CAMERA_INI_Y=55;//���
	public static float CAMERA_INI_Z=0;	
	 
	public static void initConstant(Resources r)
	{
		//�ӻҶ�ͼƬ�м���½����ÿ������ĸ߶�
		yArray=loadLandforms(r);
		//���������С����½�ص�����������
		COLS=yArray[0].length-1;
		ROWS=yArray.length-1;		
	} 
	  
	//�ӻҶ�ͼƬ�м���½����ÿ������ĸ߶�
	public static float[][] loadLandforms(Resources resources)
	{
		Bitmap bt=BitmapFactory.decodeResource(resources, R.drawable.landform);
		int colsPlusOne=bt.getWidth();
		int rowsPlusOne=bt.getHeight(); 
		float[][] result=new float[rowsPlusOne][colsPlusOne];
		for(int i=0;i<rowsPlusOne;i++)
		{
			for(int j=0;j<colsPlusOne;j++)
			{
				int color=bt.getPixel(j,i);
				int r=Color.red(color);
				int g=Color.green(color); 
				int b=Color.blue(color);
				int h=(r+g+b)/3;
				result[i][j]=h*LAND_HIGHEST/255-LAND_HIGH_ADJUST;  
			}
		}		
		return result;
	}
}
