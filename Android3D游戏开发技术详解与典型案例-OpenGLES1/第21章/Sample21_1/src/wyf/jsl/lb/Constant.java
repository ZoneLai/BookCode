package wyf.jsl.lb;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;

public class Constant {
	//2D��������
	public static final int SCREEN_WIDTH=480;//��Ļ����
	public static final int SCREEN_HEIGHT=320;
	public static boolean SOUND_FLAG=false;	//��Ϸ�������޵ı�־λ
	public static boolean pauseFlag=false;
	public static boolean inGame=false;
	public static boolean BACK_SOUND_FLAG=false;//��������־λ
	public static int BIGWIDTH=150;//ѡ�в˵���Ŀ���, �������Ͻ�����
	public static int BIGHEIGHT=140; 
	public static int SELECT_X=SCREEN_WIDTH/2-BIGWIDTH/2;
	public static float SELECT_Y=SCREEN_HEIGHT/1.5f-BIGHEIGHT/2;
	public static int SMALLWIDTH=120;//δѡ�в˵���Ŀ���
	public static int SMALLHEIGHT=(int)(((float)SMALLWIDTH/BIGWIDTH)*BIGHEIGHT);//��עϸ��
	public static final int MENU_SPAN=15;//�˵���ļ��
	public static final int MENU_SLIDESPAN=30;//������ֵ
	public static final int TOTAL_STEPS=10;//�����ܲ���
	public static final float PERCENT_STEP=1.0f/TOTAL_STEPS;//ÿһ���Ķ����ٷֱ�
	public static final int ANMI_TIMESPAN=20;//ÿһ�������ļ��ʱ��
	
	//��Ϣ����������Ϣ���
	public static final int GAME_SOUND=1;
	public static final int GAME_MENU=2;
	public static final int GAME_LOAD=3;
	public static final int GAME_START=4;
	public static final int GAME_OVER=5;
	public static final int GAME_HELP=6;
	public static final int GAME_ABOUT=7;
	
	public static final float UNIT_SIZE=3f;//ɽ��ÿ��ĵ�λ����
	
	public static final float CAMERA_START_ANGLE=-270;//�������ת�ĳ�ʼ�Ƕȡ�������Ϸ�����߳̿�����������������
	public static final float DEGREE_SPAN=2;//�����ÿ��ת���ĽǶ�
	public static final float CARERA_R=UNIT_SIZE;			//������ƶ��ĳ�ʼ�뾶�ĵ�λ�ߴ�
	public static final float DIRECTION_INI=0.0f;//��ʼ���߷��� ��Z�Ḻ��Ϊ0�ȣ���Y��������ת
	public static final float DISTANCE=60.0f;//�����λ�þ���۲�Ŀ���ľ���
	
	public static final float LAND_HIGH_ADJUST=0f;//½�صĸ߶ȵ���ֵ
	public static final float WATER_HIGH_ADJUST=0f;//ˮ��ĸ߶ȵ���ֵ
	public static final float LAND_HIGHEST=50f;//½�����߲�
	
	public static float[][] yArray;//½����ÿ������ĸ߶�����
	public static int COLS;//½������
	public static int ROWS;//½������
	
	public static int FORT_ROW=68;//��̨������ 
	public static int FORT_COL=84;//��̨������
	 
	public static float FORT_X;//��̨X����
	public static float FORT_Y;//��̨Y����
	public static float FORT_Z;//��̨Z����
	
	//��̨
	public static final float CANNON_EMPLACEMENT_UNIT_SIZE=3f;				//��̨��С��λ
	
	public static final float CANNON_PEDESTAL_LENGHT=CANNON_EMPLACEMENT_UNIT_SIZE*0.6f;		//��̨������
	public static final float CANNON_PEDESTAL_R=CANNON_EMPLACEMENT_UNIT_SIZE*1.5f;			//��̨�����뾶
	
	public static final float CANNON_BODY_LENGHT=CANNON_EMPLACEMENT_UNIT_SIZE*1.4f;			//��̨���ɸ�
	public static final float CANNON_BODY_R=CANNON_EMPLACEMENT_UNIT_SIZE*1.2f;				//��̨���ɰ뾶
	
	public static final float PEDESTAL_COVER_R=CANNON_PEDESTAL_R;							//��̨�׸ǰ뾶
	
	public static final float BODY_COVER_R=CANNON_BODY_R;									//��̨���ǰ뾶
	
	public static float CANNON_FORT_Y;														//��̨��λ�ø߶� 
	public static float CANNON_FORT_Z;														//��̨��λ�ø߶� 
	 
	//����λ�� 
	public static int LIGHT_ROW=4;//���������� 
	public static int LIGHT_COL=30;
	 
	public static float LIGHT_X;//����λ�� 
	public static float LIGHT_Z; 
	public static float LIGHT_Y;

	
	//�ڵ�
	public static float BULLET_V=20f;//�ڵ��������ٶ�
	public static float G=0;//�������ٶ�1.0
	public static float TIME_SPAN=0.1f;//�ڵ�����ʱ������ֵ
	public static final float BULLET_SIZE=0.2f;//�ӵ���λ�ߴ�
	
	//ˮ��
	public static int WCOLS=16;//ˮ������
	public static int WROWS=16;//ˮ������
	public static double WATER_RADIS=Math.PI*4;//ˮ���ܹ��Ļ��ȿ��
	public static float HIGH_DYNAMIC=0.6f;//ˮ�����߶��Ŷ�ֵ
	public static int WATER_FRAMES=16;//ˮ���֡��
	public static float WATER_UNIT_SIZE;//ˮ��ĵ�Ԫ��ߴ�
	public static float WATER_HEIGHT=42*(LAND_HIGHEST/255)+LAND_HIGH_ADJUST-2.5f;//ˮ��߶�42�Ҷ�ֵ����½�ظ߶�ƫ��
	
	//��ʼ����̨������λ��
	public static void initConstant(Resources r)
	{
		yArray=loadLandforms(r);
		
		COLS=yArray[0].length-1;//���������С����½�ص�����������
		ROWS=yArray.length-1;	
		
		FORT_X=-UNIT_SIZE*COLS/2+FORT_COL*UNIT_SIZE;//������̨����������
		FORT_Z=-UNIT_SIZE*ROWS/2+FORT_ROW*UNIT_SIZE;
		FORT_Y=yArray[FORT_ROW][FORT_COL]+6.0f; 
		
		CANNON_FORT_Y=yArray[FORT_ROW][FORT_COL]; 
		CANNON_FORT_Z=-UNIT_SIZE*ROWS/2+FORT_ROW*UNIT_SIZE; 
		
//		LIGHT_X=-UNIT_SIZE*COLS/2+LIGHT_COL*UNIT_SIZE;//�����������
//		LIGHT_Z=-UNIT_SIZE*COLS/2+LIGHT_ROW*UNIT_SIZE;
//		LIGHT_Y=yArray[LIGHT_ROW][LIGHT_COL];
		 
		LIGHT_Z=-65f;//����λ�� 
		LIGHT_X=-175f; 
		LIGHT_Y=CollectionUtil.getLandHeight(LIGHT_X, LIGHT_Z);
		
		WATER_UNIT_SIZE=COLS/WCOLS*UNIT_SIZE;//����½�ص�������ˮ�����ı�����ϵ�����ˮ����ӵĴ�С
	}
	
	//�ӻҶ�ͼƬ�м���½����ÿ������ĸ߶�
	public static float[][] loadLandforms(Resources resources)
	{
		Bitmap bt=BitmapFactory.decodeResource(resources, R.drawable.map01);
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
				if(r==g&&g==b&&b==0)//�Ҷ�Ϊ���������
				{
					result[i][j]=-1000;
				}
			}
		}		
		return result;
	}
	
	//����	
	public static final float SPAN=0.6f;//���ڴ�С����
	
	public static final float W_CYLINDER_L=SPAN*6f;//������
	public static final float W_CYLINDER_R=SPAN*3f;

	public static final float N_CYLINDER_L=SPAN*8f;//������
	public static final float N_CYLINDER_R=SPAN*2f;
	
	public static final float GUN_CYLINDER_L=SPAN*15f;//�ڹ�
	public static final float GUN_CYLINDER_R=SPAN*1.25f;
	
	public static final float GUN_HEAD_CYLINDER_L=SPAN*1.5f;//��ͷ
	public static final float GUN_HEAD_CYLINDER_R=SPAN*1.6f;
	
	public static final float WIDGET_L=W_CYLINDER_L;//װ��
	public static final float WIDGET_R=SPAN*0.8f; 
	
	public static final float ZHUNXING_LENGTH=SPAN*70f;//׼�Ǿ���
	
	//ˮ��̹��
	public static final float WATERTANK_UNIT_SPAN=5f;		//ˮ��̹�˵�λ��С
	public static boolean PRODUCT_WATERTANK_FLAG=true;		//����̹�������߳�	
	public static final float W_START_Y=42*(LAND_HIGHEST/255)+LAND_HIGH_ADJUST+1.0f;					//ˮ��̹�˵���ʼλ��	
	public static final float W_V=-0.5f;						//ˮ��̹�˵��ٶ�
	public static final float PRODUCT_WATERTANK_RADIUS=200;	//����ˮ��̹�˵ľ���Բ�뾶
	public static final int WATERTANK_COUNT=3;				//ˮ��̹�˵�����
	public static final float WT=WATERTANK_UNIT_SPAN;		//����ڵ����ˮ��̹��ʱ��ˮ��̹�˵�����ǰ뾶
	
	//½��̹��	
	public static final float UNIT_SPAN=1.5f;					//½��̹�˵�λ��С
	public static final float L_START_Y=42*(LAND_HIGHEST/255)+LAND_HIGH_ADJUST+5f;					//½��̹�˵���ʼλ��	
	public static final float L_V=2f;;						//½��̹�˵��ٶ�		
	public static final float T=3+UNIT_SPAN;				//����ڵ����½��̹��ʱ��½��̹�˵�����ǰ뾶
	public static final float WW=0.5f;						//½��̹��������ֵ������һ��̹������ֵ��������ֵʱ̹����ʧ��
	public static final float WW_SPAN=0.1f;					//̹��ÿ��̧�ߵĸ߶ȡ�
	
	//����̹������
	public static int Count=0;			//����̹�˵ĳ�ʼ����	
	public static final int MAX_COUNT=15;//����̹�˵��������

	//�Ǳ���е������ֵĴ�С
	public static final float SCORE_NUMBER_SPAN_X=0.15f;
	public static final float SCORE_NUMBER_SPAN_Y=0.15f;	
	public static final float ICON_DIS=3f;//ͼ�����ӵ�ľ���3
	
	//��ըͼƬ�����εı߳���1/2
	public static final float CIRCLE_R=0.5f;//��ըͼƬ��С��λ
	public static final float LAND_BAOZHA=5f;//�ӵ���������ˮ��
	public static final float TANK_BAOZHA=15f;//�ӵ����̹�� 
	
	//���� 
	public static final float LIGHTHOUSE_UNIT_SIZE=5f;//�����Ĵ�С��λ
	
	public static final float PEDESTAL_LENGHT=LIGHTHOUSE_UNIT_SIZE*0.3f;	//����������
	public static final float PEDESTAL_R=LIGHTHOUSE_UNIT_SIZE*1.4f;			//���������뾶
	
	public static final float BODY_LENGHT=LIGHTHOUSE_UNIT_SIZE*7.4f;		//�������ɸ�
	public static final float BODY_R=LIGHTHOUSE_UNIT_SIZE*0.65f;			//�������ɰ뾶
	
	public static final float FLOTFORM_LENGHT=LIGHTHOUSE_UNIT_SIZE*1f;		//�����t��̨��
	public static final float FLOTFORM_R=LIGHTHOUSE_UNIT_SIZE*1.5f;			//�����t��̨�뾶
	
	public static final float OVERHEAD_HEIGHT=LIGHTHOUSE_UNIT_SIZE*0.75f;	//��������
	public static final float OVERHEAD_R=LIGHTHOUSE_UNIT_SIZE*0.65f;		//�������뾶
	
	public static final float UPSWELL_HEIGHT=LIGHTHOUSE_UNIT_SIZE*0.7f;		//�t��̨͹�𲿷ָ�
	public static final float UPSWELL_R=LIGHTHOUSE_UNIT_SIZE*1.5f;			//�t��̨͹�𲿷ְ뾶
	
	public static final float FLOTFORM_SCALE=5.7f/7.4f;						//�����t��̨�ڵ������ɵ�λ�ñ���
	public static final float OVERHEAD_SCALE=6.9f/7.4f;						//�������ڵ������ɵ�λ�ñ���
	
	public static final float LIGHT_R=7f;									//��Դ�Ƶ�����ת�뾶
	  
	//�ǿհ뾶    
	public static final float XINGKONG_R=350f;      
	   
	//�����뾶
	public static final float MOON_SCALE=10f;//�����뾶  
	public static final float MOON_R=220f;//�����˶��뾶  
	public static final float MOON_ANGLE_Y=20f;//�������ڸ߶ȵĽ�ֵ
	public static final float MOON_LIGHT_ANGLE=10f;//����Ķ��� �Ĺ�Ƕ�    
}
