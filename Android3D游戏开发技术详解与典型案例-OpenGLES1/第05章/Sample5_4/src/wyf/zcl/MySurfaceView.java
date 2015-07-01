package wyf.zcl;
import android.opengl.GLSurfaceView;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.view.MotionEvent;
class MySurfaceView extends GLSurfaceView {
	private final float TOUCH_SCALE_FACTOR = 180.0f/320;//�Ƕ����ű���
    private SceneRenderer mRenderer;//������Ⱦ��
    private float mPreviousY;//�ϴεĴ���λ��Y����
    private float mPreviousX;//�ϴεĴ���λ��Y����
	private int lightAngleGreen=0;
	private int lightAngleRed=90;
	public MySurfaceView(Context context) {
        super(context);
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
    }
    //�����¼��ص�����
    @Override public boolean onTouchEvent(MotionEvent e) {
        float y = e.getY();
        float x = e.getX();
        switch (e.getAction()) {
        case MotionEvent.ACTION_MOVE:
            float dy = y - mPreviousY;//���㴥�ر�Yλ��
            float dx = x - mPreviousX;//���㴥�ر�Yλ��
            mRenderer.ball.mAngleX += dy * TOUCH_SCALE_FACTOR;//������x����ת�Ƕ�
            mRenderer.ball.mAngleZ += dx * TOUCH_SCALE_FACTOR;//������z����ת�Ƕ�
            requestRender();//�ػ滭��
        }
        mPreviousY = y;//��¼���ر�λ��
        mPreviousX = x;//��¼���ر�λ��
        return true;
    }
	private class SceneRenderer implements GLSurfaceView.Renderer {   
    	Ball ball=new Ball(4);
    	public SceneRenderer()
    	{
            //����һ���߳��Զ���ת����
            new Thread(){
          	  public void run(){
          		try{ Thread.sleep(100);}
          		catch(Exception e){e.printStackTrace();}
          		  while(true){
          			lightAngleGreen+=5;
          			lightAngleRed+=5;
                    requestRender();//�ػ滭��
                    try{ Thread.sleep(50);}
              		catch(Exception e){e.printStackTrace();}
          	}}}.start();
    	}
        public void onDrawFrame(GL10 gl) {            
        		gl.glShadeModel(GL10.GL_SMOOTH);
        	//�趨��ɫ��Դ��λ��
        	float lxGreen=(float)(7*Math.cos(Math.toRadians(lightAngleGreen)));
        	float lzGreen=(float)(7*Math.sin(Math.toRadians(lightAngleGreen)));
        	float[] positionParamsGreen={lxGreen,0,lzGreen,1};//����1��ʾʹ�ö�λ��
            gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_POSITION, positionParamsGreen,0); 
            //�趨��ɫ��Դ��λ��
            float lyRed=(float)(7*Math.cos(Math.toRadians(lightAngleRed)));
        	float lzRed=(float)(7*Math.sin(Math.toRadians(lightAngleRed)));
            float[] positionParamsRed={0,lyRed,lzRed,1};//����1��ʾʹ�ö�λ��
            gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_POSITION, positionParamsRed,0); 
        	//�����ɫ����
        	gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        	//���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();     
            gl.glTranslatef(0, 0f, -1.8f);  
            ball.drawSelf(gl);
        }
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            //�����Ӵ���С��λ�� 
        	gl.glViewport(0, 0, width, height);
        	//���õ�ǰ����ΪͶӰ����
            gl.glMatrixMode(GL10.GL_PROJECTION);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();
            //����͸��ͶӰ�ı���
            float ratio = (float) width / height;
            //���ô˷����������͸��ͶӰ����
            gl.glFrustumf(-ratio, ratio, -1, 1, 1, 10);
        }
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            //�رտ����� 
        	gl.glDisable(GL10.GL_DITHER);
        	//�򿪿����
            gl.glEnable(GL10.GL_MULTISAMPLE);
        	//�����ض�Hint��Ŀ��ģʽ������Ϊ����Ϊʹ�ÿ���ģʽ
            gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT,GL10.GL_FASTEST);
            //������Ļ����ɫ��ɫRGBA
            gl.glClearColor(0,0,0,0);
            //������ɫģ��Ϊƽ����ɫ   
            gl.glShadeModel(GL10.GL_SMOOTH);//GL10.GL_SMOOTH  GL10.GL_FLAT
            //������Ȳ���
            gl.glEnable(GL10.GL_DEPTH_TEST);
            gl.glEnable(GL10.GL_LIGHTING);//�������            
            initGreenLight(gl);//��ʼ����ɫ��
            initRedLight(gl);//��ʼ����ɫ��
            initMaterial(gl);//��ʼ������
    }}
	private void initGreenLight(GL10 gl){
        gl.glEnable(GL10.GL_LIGHT0);//��0�ŵ�  
        //����������
        float[] ambientParams={0.1f,0.1f,0.1f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_AMBIENT, ambientParams,0);            
        //ɢ�������
        float[] diffuseParams={0f,1f,1f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_DIFFUSE, diffuseParams,0); 
        //���������
        float[] specularParams={0.0f,1.0f,0.0f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_SPECULAR, specularParams,0);     
	}
	private void initRedLight(GL10 gl){    
        gl.glEnable(GL10.GL_LIGHT1);//��1�ŵ�  
        //����������
        float[] ambientParams={0.1f,0.1f,0.1f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_AMBIENT, ambientParams,0);            
        //ɢ�������
        float[] diffuseParams={1f,0f,0f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_DIFFUSE, diffuseParams,0); 
        //���������
        float[] specularParams={1f,0f,0f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT1, GL10.GL_SPECULAR, specularParams,0); 
	}
	private void initMaterial(GL10 gl){//����Ϊ��ɫʱʲô��ɫ�Ĺ���������ͽ����ֳ�ʲô��ɫ
        //������Ϊ��ɫ����
        float ambientMaterial[] = {0.4f, 0.4f, 0.4f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_AMBIENT, ambientMaterial,0);
        //ɢ���Ϊ��ɫ����
        float diffuseMaterial[] = {0.8f, 0.8f, 0.8f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_DIFFUSE, diffuseMaterial,0);
        //�߹����Ϊ��ɫ
        float specularMaterial[] = {1.0f, 1.0f, 1.0f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_SPECULAR, specularMaterial,0);
        //�߹ⷴ������,��Խ���������ԽСԽ��
        float shininessMaterial[] = {1.5f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_SHININESS, shininessMaterial,0);
	    //��ɫ�Է���
	    float emission[] = {0.0f, 0.0f, 0.3f, 1.0f};
	    gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_EMISSION, emission,0);
	}
}