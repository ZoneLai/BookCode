package wyf.swq;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.opengl.GLSurfaceView;


public class MySurfaceView extends GLSurfaceView {
	private SceneRenderer myRenderer;//������Ⱦ��
	
	public MySurfaceView(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
		myRenderer=new SceneRenderer();//����������Ⱦ��
		this.setRenderer(myRenderer);//������Ⱦ��
		this.setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ
	}

	private class SceneRenderer  implements GLSurfaceView.Renderer{//�ڲ��࣬ʵ��Renderer�ӿڣ���Ⱦ��
		
		Points p=new Points();
		Lines l=new Lines();
		public SceneRenderer(){
			
		}
		@Override
		public void onDrawFrame(GL10 gl) {
			// TODO Auto-generated method stub
			
			gl.glClear(GL10.GL_COLOR_BUFFER_BIT|GL10.GL_DEPTH_BUFFER_BIT);//�����ɫ�������Ȼ���
			gl.glMatrixMode(GL10.GL_MODELVIEW);//���õ�ǰ����Ϊģʽ����
			gl.glLoadIdentity();//���õ�ǰ����Ϊ��λ����
			
			gl.glTranslatef(0.5f, 0, -2.0f);//
			p.drawSelf(gl);//
			gl.glTranslatef(-1.0f,0,0);
			l.drawSelf(gl);
		}

		@Override
		public void onSurfaceChanged(GL10 gl, int width, int height) {
			// TODO Auto-generated method stub
			 gl.glViewport(0, 0, width, height);
			 gl.glMatrixMode(GL10.GL_PROJECTION);
			 gl.glLoadIdentity();
			 float ratio=(float)width/height;
			 gl.glFrustumf(-ratio, ratio, -1, 1, 1, 10);
		}

		@Override
		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
			// TODO Auto-generated method stub
			gl.glDisable(GL10.GL_DITHER);//�رտ�����
			gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT,GL10.GL_FASTEST);//�����ض�Hint��Ŀ��ģʽ������Ϊ����ʹ�ÿ���ģʽ
			gl.glClearColor(0, 0, 0, 0);//������Ļ����ɫΪ��ɫ
			gl.glEnable(GL10.GL_DEPTH_TEST);//������ȼ��	
		}
	}
}
