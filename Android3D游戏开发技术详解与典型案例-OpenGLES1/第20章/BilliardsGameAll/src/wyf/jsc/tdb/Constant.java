package wyf.jsc.tdb;

import java.util.ArrayList;

public class Constant
{
	static int screenWidth=480;//��Ļ���
	static int screenHeight=320;//��Ļ�߶�
	static int bigWidth=110;    //ѡ�в˵��Ŀ��      
	static int smallWidth=90;	//ûѡ�в˵��Ŀ��
	static int bigHeight=80;	//ѡ�в˵��ĸ߶�
	static int smallHeight=(int)(((float)smallWidth/bigWidth)*bigHeight);;//δѡ�в˵���ĸ߶�
	
	static int selectX=screenWidth/2-bigWidth/2;//ѡ�в˵����������Ļ�ϵ�Xλ��
	static int selectY=screenHeight/2-bigHeight/2;//ѡ�в˵����ϲ�����Ļ�ϵ�Yλ��
	static int span=10;//�˵���֮��ļ��
	static int slideSpan=30;//������ֵ
	
	static int totalSteps=10;//�������ܲ���
	static float percentStep=1.0f/totalSteps;//ÿһ���Ķ����ٷֱ�
	static int timeSpan=20;//ÿһ�������ļ��ʱ�䣨ms��
	
	 public static final int ENTER_SOUND=0;		//����������ʾ
	 public static final int ENTER_MENU=1;		//���˵�
	 public static final int ENTER_HELP=2;		//����
	 public static final int ENTER_ABOUT=3;		//����
	 public static final int START_GAME=8;		//��ʼ��Ϸ	
	 public static final int ENTER_SETUP=6;		//����
	 public static final int ENTER_WIN=7;		//�����ʤҳ��
	 public static final int START_ONE=4;		//���뿪ʼѡ��ҳ��
	 public static final int START_LOAD=5;		//Loading����
	 public static final int ENTER_WAIT=9;		//�ȴ�����
	 public static final int ENTER_NET=10;		//���������ս����
	 public static final int ENTER_OVER=11;		//����һ�ֽ������棬Ȼ�����ѡ���ǵ��˵����滹�ǿ�ʼ��һ����Ϸ
	 public static final int ENTER_LOSE=12;		//����ʧ�ܽ���
	 public static final int USER_FULL=13;		//��ʾ������
	 
	 public static boolean soundFlag=false;//�Ƿ���������־
	 public static boolean pauseFlag=false;//�Ƿ���ͣ����
	 
	 public static int soundSetFlag=0;//���ý����������Ʊ�־,1 ���ֿ���  2  ���ֹر�
		public final static float TABLE_UNIT_SIZE=0.5f;//���׵�λ����
		public final static float TABLE_UNIT_HIGHT=0.5f;//���׵�λ�߶�
		

		public final static float BOTTOM_HIGHT=2.0f;//���ӵ׸߶�
		public final static float BOTTOM_LENGTH=36.0f;//���ӵ׳���
		public final static float BOTTOM_WIDE=24.0f;//���ӵ׿��
		
		public static final float TOUCH_SCALE_FACTOR = (float)Math.PI/320;//�Ƕ����ű���
		public static final float DEGREE_SPAN=(float)(5.0/180.0f*Math.PI);//ÿ����ת�ĽǶ�
		public static final float ANGLE_SPAN=11.25f;//������е�λ�зֵĽǶ�
		public static final float UNIT_SIZE=0.8f;//��λ�ߴ�
		//���ƶ�ÿһ����ģ��ʱ��������ֵԽСģ��Ч��Խ��ʵ�����������������Ҫ�������ô�ֵ��С��
		public static final float TIME_SPAN=0.04f;
		public static final float BALL_SCALE=0.8f;//������ֵ
		public static final float BALL_R=UNIT_SIZE*BALL_SCALE;//��İ뾶
		public static final float BALL_R_POWER_TWO=BALL_R*BALL_R;//��뾶��ƽ��
		public static final float V_TENUATION=0.995f;//�ٶ�˥��ϵ��	
		public static final float V_THRESHOLD=0.1f;//�ٶ���ֵ��С�ڴ���ֵ���ٶ���ΪΪ0
		public static final int   THREAD_SLEEP=20;//�߳�����ʱ��
		
		public static final float MIDDLE=1.5f*2*BALL_R;//�ж�����
		public static final float EDGE_SMALL=2.5f*BALL_R;//�׶����ݾ��루С�飩
		public static final float EDGE_BIG=3*BALL_R;//�ض����ݾ��루��飩
		public static final float EDGE=EDGE_SMALL+EDGE_BIG;//�ض��ݺ����,���+С��
		
		public static final float UP_DOWN_LENGTH=BOTTOM_LENGTH/2-EDGE-MIDDLE/2;//���±�Ե���ȡ�
		public static final float LEFT_RIGHT_LENGTH=BOTTOM_WIDE-2*EDGE;//���ұ�Ե����
		public static final float UP_DOWN_HIGHT=2.0f;//��Ե�߶ȡ�
		public static final float TABLE_AREA_LENGTH=BOTTOM_LENGTH-2*EDGE_BIG;//���泤��
		public static final float TABLE_AREA_WIDTH=BOTTOM_WIDE-2*EDGE_BIG;//������ 
		public static final float CIRCLE_R=3.0f*BALL_R;//�򶴵Ĵ�С
		public static final float BALL_DISTANCE=5.0f;//ĸ����������ľ���
		public static float vBall;//��¼��������ȴ�С,����
		public static float hitNum;//��¼���������ص�ֵ�ô�С,����
		public static ArrayList<BallForControl> tempBallAl=new ArrayList<BallForControl>();//
		public static boolean cueFlag=true;//�ػ���˵ı�־λ
		public static boolean overFlag=false;//��������ı�־λ
		public static boolean hitFlag=false;//�����Ƿ����
		public static boolean hitSound=false;//����������ײ������
		public static final float ICON_WIDTH=0.05f;//ͼ��ߴ�
		public static final float ICON_HEIGHT=0.1f;
		
		public static int score;//��¼�÷�
		public static int scoreOne=0;//first player score
		public static int scoreTwo=0;//second player score
		public static int scoreNODFlag=1;//�����жϸ���λ��ҽ���ӷ�  1  ��ʾ���1    2 ��ʾ���2
		public static int scoreNOD;//������־������滹�ǵ�����     0  ��ʾ������   1 ��ʾ�����
		public static int scoreTip=1;//������־��һ��˭�л���Ȩ
		
	
		public static boolean sendFlag=false;//���ƿͻ��˷���һ����Ϣ��
		public static int winLoseFlag=0;//����1 ��ʤʧ�ܵ�ҳ��ı�־
		public static boolean exitFlag=false;//���������˳�ʱ
		
		
		public static final float GOT_SCORE_DISTANCE=EDGE_BIG-BALL_R*0.05f;//���������Ե�ľ��룬�����ж��Ƿ����
		public static final float CUE_ROTATE_DEGREE_SPAN=2;//���ÿ��ת���ĽǶ�
		
		public static final float TEXTURE_RECT_Y=-2;//����Y����
		public static final float DELTA=-1f+0.5f;//С���
		public static final float DELTA_BALL=0.5f;//��С���
		public static final float WALL_SIZE=50.0f*TABLE_UNIT_SIZE;//ǽ���С
		public static final float BALL_Y=TEXTURE_RECT_Y+DELTA_BALL;//��ʼ���yλ��
		public static final float BOTTOM_Y=-4;//��������Yλ��
		public static final float FLOOR_J=WALL_SIZE/TABLE_AREA_LENGTH*4*3;//�̵ذ��jֵ
		public static final float FLOOR_I=WALL_SIZE/TABLE_AREA_WIDTH*4*4;//�̵ذ��iֵ
		public static final int x=0;//gl.glRotatef(90, x, y, z);xyz��ֵ
		public static final int y=1;
		public static final int z=0;
		
		
		

		

}