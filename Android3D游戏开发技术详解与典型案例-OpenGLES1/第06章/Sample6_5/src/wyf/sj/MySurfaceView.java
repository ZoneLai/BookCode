package wyf.sj;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.view.MotionEvent;

public class MySurfaceView extends GLSurfaceView{
	private final float TOUCH_SCALE_FACTOR = 180.0f/320;//�Ƕ����ű���
    private SceneRenderer mRenderer;//������Ⱦ��	

    private float mPreviousX;//�ϴεĴ���λ��X����
	
	public MySurfaceView(Context context) {
        super(context);
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
    }
	
	//�����¼��ص�����
    @Override 
    public boolean onTouchEvent(MotionEvent e) {
        float x = e.getX();
        switch (e.getAction()) {
        case MotionEvent.ACTION_MOVE:
            float dx = x - mPreviousX;//���㴥�ر�Xλ��
            mRenderer.angle += dx * TOUCH_SCALE_FACTOR;//������x����ת�Ƕ�
            
            requestRender();//�ػ滭��
        }   
        mPreviousX = x;//��¼���ر�λ��
        return true;
    }

	private class SceneRenderer implements GLSurfaceView.Renderer 
    {   
    	Cube cube=new Cube();//������
    	float angle=45;//����ת�Ƕ�
    	
        public void onDrawFrame(GL10 gl) {
    		//����Ϊ�򿪱������
    		gl.glEnable(GL10.GL_CULL_FACE);

    		//������ɫģ��Ϊƽ����ɫ   
            gl.glShadeModel(GL10.GL_SMOOTH);
        	
        	//�����ɫ��������Ȼ���
        	gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        	//���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();    
            
            //����cameraλ��=======================
//            GLU.gluLookAt//���ܱ��ε��ӽǡ������ӽ�
//            (
//            		gl, 
//            		0f,   //����λ�õ�X
//            		0f, 	//����λ�õ�Y
//            		2.0f,   //����λ�õ�Z
//            		0, 	//�����򿴵ĵ�X
//            		0f,   //�����򿴵ĵ�Y
//            		0,   //�����򿴵ĵ�Z
//            		0, 
//            		1, 
//            		0
//            );   
            
            GLU.gluLookAt//��̫���ܱ��ε��ӽǡ���С�ӽ�
            (
            		gl, 
            		0f,   //����λ�õ�X
            		10f, 	//����λ�õ�Y
            		15.0f,   //����λ�õ�Z
            		0, 	//�����򿴵ĵ�X
            		0f,   //�����򿴵ĵ�Y
            		0,   //�����򿴵ĵ�Z
            		0, 
            		1, 
            		0
            );  
            
            //��ת������ϵ
            gl.glRotatef(angle, 0, 1, 0);
            
            //������������
            gl.glPushMatrix();
            gl.glTranslatef(0, 0, -2);
            cube.drawSelf(gl);
            gl.glPopMatrix();
            
            //������������
            gl.glPushMatrix();
            gl.glTranslatef(2, 0, 0);
            cube.drawSelf(gl);
            gl.glPopMatrix();
            
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
            //�����Ӵ���С��λ�� 
        	gl.glViewport(0, 0, width, height);
        	//���õ�ǰ����ΪͶӰ����
            gl.glMatrixMode(GL10.GL_PROJECTION);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();
            //����͸��ͶӰ�ı���
            float ratio = (float) height/width ;
            //���ô˷����������͸��ͶӰ����
            //gl.glFrustumf( -1, 1,-ratio, ratio, 1, 100);   //���ܱ��ε��ӽǡ������ӽ�  
            gl.glFrustumf( -1, 1,-ratio, ratio, 8f, 100);     //��̫���ܱ��ε��ӽǡ���С�ӽ�
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            //�رտ����� 
        	gl.glDisable(GL10.GL_DITHER);
        	//�����ض�Hint��Ŀ��ģʽ������Ϊ����Ϊʹ�ÿ���ģʽ
            gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT,GL10.GL_FASTEST);
            //������Ļ����ɫ��ɫRGBA
            gl.glClearColor(0,0,0,0);            
            //������Ȳ���
            gl.glEnable(GL10.GL_DEPTH_TEST);
        }
    }

}
