package wyf.jsc.rtb;


public class Constant 
{
   
    //��ʾ��ͬ��̬�ĳ���
    public static final int POSTURE_ZERO=0;//��̬0
    public static final int POSTURE_ONE=1;//��̬1
    public static final int POSTURE_TWO=2;//��̬2
    //��ʾ��������ĳ���
    public static final int RIGHT_KEY=0;
    public static final int LEFT_KEY=1;
    public static final int UP_KEY=2;
    public static final int DOWN_KEY=3;    
    //��ʾ��̬״̬ת�ƹ���ľ���
    public static int[][] POSTURE_CHANGE=//�к�-������̬���   �к�-����������
    {
    		{0,0,1,1},
    		{2,2,0,0},
    		{1,1,2,2}
    };
    //��ʾXλ�Ʊ仯����ľ���
    public static float[][] X_OFFSET_CHANGE=//�к�-������̬���   �к�-����������
    {
    	{1,-1,0,0},
    	{1.5f,-1.5f,0,0},	
    	{1.5f,-1.5f,0,0}
    };
    //��ʾZλ�Ʊ仯����ľ���
    public static float[][] Z_OFFSET_CHANGE=//�к�-������̬���   �к�-����������
    {
    	{0,0,-1.5f,1.5f},
    	{0,0,-1.5f,1.5f},
    	{0,0,-1,1}
    }; 
    //��ʾ���Ŷ����������ľ���
    public static int[][] ROTATE_ANMI_ID=//�к�-������̬���   �к�-����������
    {
    	{0,1,2,3},
    	{4,5,6,7},
    	{8,9,0,1}
    };
    //��ͼ����
    //ľ���ʼ����λ��
    public static int INIT_I=2;//���ڵ���  
    public static int INIT_J=8;//���ڵ���
    public static final int[][] MAP=//0 ����ͨ�� 1��ͨ��
    {
    	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    	{0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    	{0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
    	{0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0},
    	{0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
    	{0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
    	{0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0},
    	{0,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
    	{0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
    	{0,0,0,0,0,0,0,1,1,2,1,0,0,1,1,1,1,0,0,0},
    	{0,0,0,0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0},
    	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    
    public static int[][] afterStateIsZero=//��ת��״̬(0)-��ⷭת��λ��0��1
    {
    	{1,0,1,0},
    	{-1,0,-1,0},
    	{0,-2,0,-1},
    	{0,2,0,1}
    };
    public static int[][] afterStateIsOne=//��ת��״̬(1)-��ⷭת��λ��0��1
    {
    	{1,0,2,0},
    	{-2,0,-1,0},
    	{0,-2,0,-1},
    	{0,1,0,2}
    };
    public static int[][] afterStateIsTwo=//��ת��״̬(2)-��ⷭת��λ��0��1
    {
    	{2,0,1,0},
    	{-2,0,-1,0},
    	{0,-1,0,-1},
    	{0,1,0,1}
    }; 
    public static boolean anmiFlag=false;//�����Ƿ񲥷���
	public static final int ENTER_SOUND=0;
    public static final int ENTER_MENU=1;
    public static final int START_GAME=2;//���ز���ʼ��Ϸ��Message���
    public static final int ENTER_SETTING=3;
    public static final int	ENTER_HELP=4;
    public static final int ENTER_WINVIEW=5;//�����ʤҳ��
	//���泣��
	 public static final float UNIT_SIZE=1.0f;
    //һ��ذ�Ķ�������
    public static final int GV_UNIT_NUM=36;
    //�ذ�ĸ߶�
    public static final float UNIT_HIGHT=0.1f;
    public static boolean winSound=false;//�Ƿ񲥷Ż�ʤ����
    public static boolean dropFlag=false;//�Ƿ񲥷ŵ�����������
    public static int targetX=INIT_I;//Ŀ��X����
    public static int targetZ=INIT_J;//Ŀ��Z����
    public static final float distance=6.0f;//����Ŀ���ľ���
    public static final float AngleX=45;//�ڵ���ļн�
    public static final float MOVE_SPAN=0.8f;//��λ�ƶ��ľ���
	public static float tempFlag=MAP[0].length/2;//��ǵ�ͼ�ĳ�ʼλ��
	public static boolean bOver=true;
	public static int level=1;//��¼�ڼ���
	public static boolean soundFlag=false;//�Ƿ���������־
	public static int soundSetFlag=0;//���ý����������Ʊ�־,1 ���ֿ���  2  ���ֹر�
	public static int surfaceId=0;//0������1����
	public static int goSurface=0;//0��������ѡ����档1�������˵�����.2���ڣ���������
	public static boolean threadFlag=true;//����ChoserThred�߳�
	public static float previousX;//downʱ��x
	public static float previousY;//downʱ��y
	public static float laterX;//upʱ��x
	public static float laterY;//upʱ��x
	public static float backWidth;//��¼��Ļ���
	public static float backHeight;//��¼��Ļ�߶�
	public static float ratio;//��¼��Ļ�߿��
	public static int status=-1;//0:startgames,1:setting,2:about,3:help,4:exit
	public static int keyStatus=status;
	public static boolean winFlag=false;//�Ƿ��ʤ
	public static boolean loseFlag=false;//�Ƿ�ʧ��
	public static int winAndLose=-1;//����ѡ���ʤʧ��
	public static boolean settingFlag;//����SettingThred�߳�
}

