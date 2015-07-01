package wyf.jc;

import android.graphics.Canvas;
import android.view.SurfaceHolder;

//��ʱ���»��ƻ�����߳�
public class GameViewDrawThread extends Thread{
	boolean flag = true;
	boolean pauseFlag=false;
	int sleepSpan = 100;
	MyGameView gameView;
	SurfaceHolder surfaceHolder;
	public GameViewDrawThread(MyGameView gameView){
		this.gameView = gameView;
		this.surfaceHolder = gameView.getHolder();
	}
	public void run(){
		Canvas c;
        while (this.flag) {
            c = null;
            if(!pauseFlag)
            {
            	try {
	            	// �����������������ڴ�Ҫ��Ƚϸߵ�����£����������ҪΪnull
	                c = this.surfaceHolder.lockCanvas(null);
	                synchronized (this.surfaceHolder) {
	                	gameView.onDraw(c);//����
	                }
	            } finally {
	                if (c != null) {
	                	//���ͷ���
	                    this.surfaceHolder.unlockCanvasAndPost(c);
	                }
	            }
            }
	            
            try{
            	Thread.sleep(sleepSpan);//˯��ָ��������
            }
            catch(Exception e){
            	e.printStackTrace();//��ӡ��ջ��Ϣ
            }
        }
	}
}
