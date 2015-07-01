package wyf.jsc.tdb;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.GLUtils;
import android.view.KeyEvent;
import android.view.MotionEvent;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import static wyf.jsc.tdb.Constant.*;

class MySurfaceView extends GLSurfaceView {

	//boolean needCreateFlag=true;
	
	float mPreviousX;
	float mPreviousY;
	MyActivity activity=(MyActivity)this.getContext();
	//�������λ��
	
	float cx=0;//�����xλ��
	float cy=50;//75;//�����yλ��
	float cz=50;//�����zλ��
	
	float tx=0;//BOTTOM_LENGTH/2;//Ŀ���xλ��
	float ty=0;//Ŀ���yλ��
	float tz=0;//BOTTOM_WIDE/2;//Ŀ���zλ��
	
	static float yAngle=0;		//�������Y����ת�ĽǶ�
	static float xAngle=0;		//�������X����ת�ĽǶ�
	static float angle=0;
	
	float direction=0.0f;  //���ð�����������
	final float MOVE_SPAN=0.8f;
	final float DISTANCE_CAMERA_YACHT=50.0f;
	final float DISTANCE_CAMERA_TARGET=2.0f;
	final float DEGREE_SPAN=(float)(5.0/180.0f*Math.PI);
	
    private SceneRenderer mRenderer;//������Ⱦ��
    BallForControl bfd;

    BallGoThread bgt;//������˶��߳�
    ArrayList<BallForControl> ballAl;//������б�
   
    public static boolean turnFlag=true;//�ӽ���תһ�ܵı�־λ
    public static int ballGoOver=1;//�����������˶�������Ϣ
    
    int size;//��¼��ĸ���
    final float UNIT_D=-0.2f;//������ľ���΢��
    float tempAngleZ;//��ʱ��¼ת���ĽǶ�
    static int id;//1 �������1    2 �������2
	public MySurfaceView(Context context) {
        super(context);
        mRenderer = new SceneRenderer();	//����������Ⱦ��
        setRenderer(mRenderer);				//������Ⱦ��		
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);//������ȾģʽΪ������Ⱦ   
        ballAl=new ArrayList<BallForControl>();//������б�
    }
	
	@Override
    public boolean onTouchEvent(MotionEvent e) {
		float y = e.getY();
        float x = e.getX();
        switch (e.getAction()) {
        case MotionEvent.ACTION_MOVE:
        	float dy = y - mPreviousY;//���㴥�ر�Yλ��
            float dx = x - mPreviousX;//���㴥�ر�Yλ��
            float r=(float)(Math.sqrt(dx*dx+dy*dy));
            if(dy>0&&dx!=0)
			{
				float tempA=(float)Math.toDegrees(Math.acos(dx/r));
				if(tempA>=0&&tempA<45)
				{//right
					direction=direction+DEGREE_SPAN;
		            cx=(float)(tx+Math.sin(direction)*DISTANCE_CAMERA_YACHT);//�����x����
					cz=(float)(tz+Math.cos(direction)*DISTANCE_CAMERA_YACHT);//�����z����
				}
				if(tempA>=45&&tempA<135)
				{//down
					if(cy>=20)					
					{
						cy-=0.5f;
					}
				}
				if(tempA>=135&&tempA<180)
				{//left
					direction=direction-DEGREE_SPAN;
				    //�����µ������XZ����
			    	cx=(float)(tx+Math.sin(direction)*DISTANCE_CAMERA_YACHT);//�����x����
			        cz=(float)(tz+Math.cos(direction)*DISTANCE_CAMERA_YACHT);//�����z����
				}
			}
			if(dy<0&&dx!=0)
			{
				float tempB=(float)Math.toDegrees(Math.asin(dy/r));
				if(dx>0)
				{
					if(tempB>=-45&&tempB<0)
					{//right
						direction=direction+DEGREE_SPAN;
					    //�����µ������XZ����
				    	cx=(float)(tx+Math.sin(direction)*DISTANCE_CAMERA_YACHT);//�����x����
				        cz=(float)(tz+Math.cos(direction)*DISTANCE_CAMERA_YACHT);//�����z����
					}
					if(tempB>=-90&&tempB<-45)
					{//up
						if(cy<=65)
						{
							cy+=0.5f;
						}
					}
				}
				if(dx<0)
				{
					tempB=tempB-90;
					if(tempB>=-135&&tempB<-90)
					{//left
						direction=direction-DEGREE_SPAN;
					    //�����µ������XZ����
				    	cx=(float)(tx+Math.sin(direction)*DISTANCE_CAMERA_YACHT);//�����x����
				        cz=(float)(tz+Math.cos(direction)*DISTANCE_CAMERA_YACHT);//�����z����
					}
					if(tempB>=-180&&tempB<-135)
					{//up
						if(cy<=65)
						{
							cy+=0.5f;
						}
					}
				}
			}
			if(dx==0)
			{
				if(dy>0){//down
					if(cy>=20){
						cy-=0.5f;
					}
				}
				if(dy<0){//up
					if(cy<=65){
						cy+=0.5f;
					}
				}
			}
			if(dy==0)
			{
				if(dx>0)
				{//right
					direction=direction+DEGREE_SPAN;
				    //�����µ������XZ����
			    	cx=(float)(tx+Math.sin(direction)*DISTANCE_CAMERA_YACHT);//�����x����
			        cz=(float)(tz+Math.cos(direction)*DISTANCE_CAMERA_YACHT);//�����z����
				}
				if(dx<0)
				{//left
					direction=direction-DEGREE_SPAN;
				    //�����µ������XZ����
			    	cx=(float)(tx+Math.sin(direction)*DISTANCE_CAMERA_YACHT);//�����x����
			        cz=(float)(tz+Math.cos(direction)*DISTANCE_CAMERA_YACHT);//�����z����
				}
			}
        }
        mPreviousY = y;//��¼���ر�λ��
        mPreviousX = x;//��¼���ر�λ��
        return true;
    }
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent e)
	{
		if(keyCode==4)
		{
			cueFlag=true;//�ػ���˵ı�־λ
			overFlag=false;//��������ı�־λ
			hitFlag=false;//�����Ƿ����
			hitSound=false;//����������־λ
			score=0;//��¼�÷�
			scoreOne=0;//first player score
			scoreTwo=0;//second player score
			scoreNODFlag=1;//�����жϸ���λ��ҽ���ӷ�  1  ��ʾ���1    2 ��ʾ���2
			scoreNOD=0;//������־������滹�ǵ�����     0  ��ʾ������   1 ��ʾ�����
			scoreTip=1;//������־��һ��˭�л���Ȩ
			sendFlag=false;//���ƿͻ��˷���һ����Ϣ��
			winLoseFlag=0;
			bgt.flag=false;
			Cue.angleZ=0;//��ʼ����˽Ƕ�
			if(activity.netFlag)
			{
				try {
					activity.ct.dout.writeUTF("<#EXIT_MAN#>");//�����˳���Ϣ
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
			activity.toAnotherView(ENTER_MENU);//����˵�����
			return true;
		}
		switch(keyCode)
		{
		case 19:
			direction=direction+DEGREE_SPAN;			    
			    //�����µ������XZ����
		    	cx=(float)(tx+Math.sin(direction)*DISTANCE_CAMERA_YACHT);//�����x����
		        cz=(float)(tz+Math.cos(direction)*DISTANCE_CAMERA_YACHT);//�����z����
				break;
		case 20:
			direction=direction-DEGREE_SPAN;
			    
			    //�����µ������XZ����
		    	cx=(float)(tx+Math.sin(direction)*DISTANCE_CAMERA_YACHT);//�����x����
		        cz=(float)(tz+Math.cos(direction)*DISTANCE_CAMERA_YACHT);//�����z����
				break;
			case 21:
					if(hitFlag&&cueFlag)
					{
						if(activity.netFlag)//����
						{
							tempAngleZ=Cue.angleZ+CUE_ROTATE_DEGREE_SPAN;
							try
							{
								activity.ct.dout.writeUTF("<#CUE_ANGLE#>"+tempAngleZ);//�������ת���Ƕ�
							}catch(Exception ea)
							{
								ea.printStackTrace();
							}
						}
						else//����
						{
							Cue.angleZ=Cue.angleZ+CUE_ROTATE_DEGREE_SPAN;//�������ת���Ƕ�
						}
					}
					break;
			case 22:
					if(hitFlag&&cueFlag)
					{
						if(activity.netFlag)//����
						{
							tempAngleZ=Cue.angleZ-CUE_ROTATE_DEGREE_SPAN;
							try
							{
								activity.ct.dout.writeUTF("<#CUE_ANGLE#>"+tempAngleZ);//�������ת���Ƕ�
							}catch(Exception ea)
							{
								ea.printStackTrace();
							}	
						}
						else//����
						{
							Cue.angleZ=Cue.angleZ-CUE_ROTATE_DEGREE_SPAN;//�������ת���Ƕ�
						}
					}
					break;
			case 62:
					if(hitFlag&&cueFlag)
					{
						mRenderer.cue.yOffset+=4;//��˳�ʼλ��
						vBall=(float)(Math.random()+1.5)*5;
						if(activity.netFlag)
						{
							try {								
								activity.ct.dout.writeUTF("<#BALL_HIT#>"+vBall+"|"+Cue.angleZ);//���ͻ�����Ϣ �ٶ�+�Ƕ�
								activity.ct.dout.flush();//ˢ����Ϣ
							} catch (IOException e1) {								
								e1.printStackTrace();
							}
							hitFlag=false;//����Ȩ��Ϊfalse
						}else
						{
							ballAl.get(0).vx=(float)(vBall*Math.sin(Math.toRadians(Cue.angleZ)));//�ֽ�ĸ���ٶ�
							ballAl.get(0).vz=(float)(-1*vBall*Math.cos(Math.toRadians(Cue.angleZ)));
							cueFlag=false;//�����־λ��Ϊfalse
						}		
						activity.playSound(1, 0);//���ſ�������
						mRenderer.cue.yOffset=0;//���λ����0
					}					
					break;				
		}		
		return true;
	}
	

	private class SceneRenderer implements GLSurfaceView.Renderer 
    {   
		Cue cue;
		int cueId;
		int[] ballTexId=new int[16];//��������id����
		public int groundId;//�����ID
		public int wallId;//ǽ��Id
		int tableBottomId;//��������ID		
		int tableAreaId;//��������ID
		int tableRoundUDId;//�������±�ԵID
		int tableRoundLRId;//�������ұ�ԵID
		int circleId;//��ID
		int baffleId;//����ID
		
		public int iconId;//�Ʊ��Id
		public int iconIdFirst;//һ����ҵ�����ID
		public int iconIdSecond;//������ҵ�����ID
		public int numberId;//����Id
		public int tipIdOne;//��ʾһ����ҵ�����Id
		public int tipIdTwo;//��ʾ�����ʼ۵�����Id
		public int numberIdFirst;//һ����ҵĵ÷�����ID
		public int numberIdSecond;//������ҵĵ÷�����ID
		public int vsId;//vsId
		public int tipId;//��ʾID

		
		
		TextureRect floor;//�ذ�
		Wall wall;//ǽ��
    	BallTextureByVertex btbv;//���ڻ��Ƶ���    	
  
    	DrawTable drawTable;//����
    	TextureRect icon;//�Ǳ��
    	TextureRect iconFirst;//һ����ҵ��Ǳ��
    	TextureRect iconSecond;//������ҵ��Ǳ��
    	TextureRect tipOne;//һ�������ʾ
    	TextureRect tipTwo;//������ҵ���ʾ
    	TextureRect vs;//VSͼƬ
    	Score score;//�Ʒ�
    	Score scoreFirst;//һ����ҵ÷�
    	Score scoreSecond;//������ҵ÷�
    	TextureRect tipO;//ָʾ�����Ȩ
        public void onDrawFrame(GL10 gl) {
    		//����Ϊ�򿪱������
    		gl.glEnable(GL10.GL_CULL_FACE);
    		//������Ȳ���
            gl.glEnable(GL10.GL_DEPTH_TEST);
    		//������ɫģ��Ϊƽ����ɫ   
            gl.glShadeModel(GL10.GL_SMOOTH);        	
        	//�����ɫ��������Ȼ���
        	gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
        	//���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();   
            
            
            //����cameraλ��
            GLU.gluLookAt
            (
            		gl, 
            		cx,   //����λ�õ�X
            		cy, 	//����λ�õ�Y
            		cz,   //����λ�õ�Z
            		tx, 	//�����򿴵ĵ�X
            		ty,   //�����򿴵ĵ�Y
            		tz,   //�����򿴵ĵ�Z
            		0, 	//upλ��
            		1, 
            		0
            ); 
            //���Ƴ���
            gl.glPushMatrix();
            wall.drawSelf(gl);//����ǽ��
            gl.glPopMatrix();
            
            gl.glPushMatrix();//�ذ�
            gl.glTranslatef(-1.5f*WALL_SIZE, BOTTOM_Y, -1.8f*WALL_SIZE);
            for(int i=0;i<FLOOR_I;i++)
            {
            	gl.glPushMatrix();
            	gl.glTranslatef(0, BOTTOM_Y, i*TABLE_AREA_WIDTH/4);
            	for(int j=0;j<FLOOR_J;j++)
            	{
            		gl.glPushMatrix();
            		gl.glTranslatef(j*TABLE_AREA_LENGTH/4, BOTTOM_Y,0);
            		floor.drawSelf(gl);//���Ƶذ�
            		gl.glPopMatrix();
            	}
            	gl.glPopMatrix();
            }
            gl.glPopMatrix();
            
            gl.glPushMatrix();
            drawTable.drawSelf(gl);//��������
            gl.glPopMatrix();
            
            gl.glRotatef(-90, 0, 1, 0);
            gl.glEnable(GL10.GL_LIGHTING);//�������==����Ч����Ҫ����һ�£����������                
            size=ballAl.size();//�����ĸ���
           
            
            try 
            {
            	for(int i=1;i<size;i++)
                {
                	ballAl.get(i).drawSelf(gl);//����������
                }
    	    	for(int i=0;i<1;i++)
    	    	{
    	    		 ballAl.get(i).drawSelf(gl); //����ĸ��
    	    		 
    	    		 if(cueFlag)
    	    		 { 
    	    			//������Ȳ���
    	    	        gl.glDisable(GL10.GL_DEPTH_TEST);
    	    			gl.glTranslatef(ballAl.get(i).xOffset, BALL_Y, ballAl.get(i).zOffset);
    	    			gl.glRotatef(90, 1, 0, 0);
    	    			cue.drawSelf(gl);//�������
    	    			gl.glEnable(GL10.GL_DEPTH_TEST);
    	    		 }
    	    		 
    	    		 if(overFlag)
    	   			 {
    	   				 if(soundFlag)
    	   				 {
    	   					 activity.mpBack.pause();//��ͣ��������
    	   				 }	 
    	   				 backMenu();//���÷���
    	   				 overFlag=false;//��־λ�跴
    	   			 }
    	    	}
            }catch(Exception e)
            {
            	e.printStackTrace();
            }   
            gl.glDisable(GL10.GL_LIGHTING);//�رչ���   
            //�ָ��ɳ�ʼ״̬���ƾ���ͼ��������
            //���õ�ǰ����Ϊģʽ����
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            //���õ�ǰ����Ϊ��λ����
            gl.glLoadIdentity();  
            gl.glDisable(GL10.GL_LIGHTING);//��ֹ����
            gl.glEnable(GL10.GL_BLEND);//�������   
            gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);//����Դ���������Ŀ��������
            switch(scoreNOD)
            {
	            case 0://����
	            		gl.glTranslatef(-2.5f, 2, -9f);
			            icon.drawSelf(gl);//������ϰͼ��
			            gl.glTranslatef(-1.6f, 2.05f, -9);
			            score.drawSelf(gl);//���Ƶ÷�
			            break;
	            case 1://����
	            		gl.glPushMatrix();
	            		gl.glTranslatef(-2.7f, 2,-9);
	            		iconFirst.drawSelf(gl);//�������1ͼ��
	            		gl.glTranslatef(-0.5f, 2, -9);
	            		scoreFirst.drawSelfNet(gl,1);//�������1�÷�
	            		gl.glPopMatrix();
	            		 
	            		//��ұ�־����
	            		if(id==1)
	            		{
	            			gl.glPushMatrix();
	            			gl.glTranslatef(-2.7f, -1.95f, -9);
	            			tipOne.drawSelf(gl);//�������1��ʾ
	            			gl.glPopMatrix();
	            		}
	            		
	            		if(id==2)
	            		{
	            			gl.glPushMatrix();
	            			gl.glTranslatef(-2.7f, -1.95f, -9);
	            			tipTwo.drawSelf(gl);//�������2��ʾ
	            			gl.glPopMatrix();
	            		}
	            		
	            		
	            		gl.glPushMatrix();
	            		gl.glTranslatef(0, 2, -9);
	            		vs.drawSelf(gl);//����VS
	            		gl.glPopMatrix();

	            		gl.glPushMatrix();
	            		gl.glTranslatef(2.7f, 2, -9);
	            		iconSecond.drawSelf(gl);//�������2ͼ��
	            		gl.glTranslatef(0.5f, 2, -9);
	            		scoreSecond.drawSelfNet(gl,2);//�������2�÷�
	            		gl.glPopMatrix();
	            		
	            		//��Ȩ����
	            		if(scoreTip==1)
	            		{
	            			gl.glPushMatrix();
		            		gl.glTranslatef(-2.2f, 1.5f, -8);
		            		tipO.drawSelf(gl);//������Ȩ��ʾ
		            		gl.glPopMatrix();
	            		}
	            		if(scoreTip==2)
	            		{
	            			gl.glPushMatrix();//��ʾ�������
		            		gl.glTranslatef(2.2f, 1.5f, -8);
		            		tipO.drawSelf(gl);//������Ȩ��ʾ
		            		gl.glPopMatrix();
	            		}
	            		break;
            }
            gl.glDisable(GL10.GL_BLEND);//�رջ��
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
            gl.glFrustumf(-ratio, ratio, -1, 1, 4, 200);  
            
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
//        	if(needCreateFlag)
//    		{
//    			needCreateFlag=false;
//    		}
//    		else
//    		{
//    			return;
//    		}
        	
            //�رտ����� 
        	gl.glDisable(GL10.GL_DITHER);
        	//�����ض�Hint��Ŀ��ģʽ������Ϊ����Ϊʹ�ÿ���ģʽ
            gl.glHint(GL10.GL_PERSPECTIVE_CORRECTION_HINT,GL10.GL_FASTEST);
            //������Ļ����ɫ��ɫRGBA
            gl.glClearColor(0,0,0,0);            
            //������Ȳ���
            gl.glEnable(GL10.GL_DEPTH_TEST);
            //������ɫģ��Ϊƽ����ɫ   
            gl.glShadeModel(GL10.GL_SMOOTH);  
           
            cueId=initTexture(gl,R.drawable.snooker14);//��ʼ�����ID
            cue=new Cue(0.05f,0.05f,5f,3,cueId,0);//������˶���
            
            //��ʼ������            
            ballTexId[0]=initTexture(gl,R.drawable.snooker0);
            ballTexId[1]=initTexture(gl,R.drawable.snooker1);
            ballTexId[2]=initTexture(gl,R.drawable.snooker2);
            ballTexId[3]=initTexture(gl,R.drawable.snooker3);
            ballTexId[4]=initTexture(gl,R.drawable.snooker4);
            ballTexId[5]=initTexture(gl,R.drawable.snooker5);
            ballTexId[6]=initTexture(gl,R.drawable.snooker6);
            ballTexId[7]=initTexture(gl,R.drawable.snooker7);
            ballTexId[8]=initTexture(gl,R.drawable.snooker8);
            ballTexId[9]=initTexture(gl,R.drawable.snooker9);
            ballTexId[10]=initTexture(gl,R.drawable.snooker10);
            ballTexId[11]=initTexture(gl,R.drawable.snooker11);
            ballTexId[12]=initTexture(gl,R.drawable.snooker12);
            ballTexId[13]=initTexture(gl,R.drawable.snooker13);
            ballTexId[14]=initTexture(gl,R.drawable.snooker14);
            ballTexId[15]=initTexture(gl,R.drawable.snooker15);
           
            //��ʼ������ ���������ID
			wallId=initTexture(gl,R.drawable.wall);
			groundId=initTexture(gl,R.drawable.ground3); 
            tableBottomId=initTexture(gl,R.drawable.bottom);//��������ID
            tableAreaId=initTexture(gl,R.drawable.area);//��������ID
            tableRoundUDId=initTexture(gl,R.drawable.round);//�������±�ԵID
            tableRoundLRId=initTexture(gl,R.drawable.roundlr);//�������ұ�ԵID
            circleId=initTexture(gl,R.drawable.circle);//��ID
            baffleId=initTexture(gl,R.drawable.baffle);
			 
			iconId=initTexture(gl,R.drawable.icon);
			iconIdFirst=initTexture(gl,R.drawable.play1);
			iconIdSecond=initTexture(gl,R.drawable.play2);
			numberId=initTexture(gl,R.drawable.number);
			numberIdFirst=initTexture(gl,R.drawable.number);
			numberIdSecond=initTexture(gl,R.drawable.number);
			tipIdOne=initTexture(gl,R.drawable.tip1);
			tipIdTwo=initTexture(gl,R.drawable.tip2);
			vsId=initTexture(gl,R.drawable.vs);
			tipId=initTexture(gl,R.drawable.tip);
            //��ʼ�����ղ���
            initSunLight(gl);
            initMaterial(gl);
            
            drawTable=new DrawTable(tableBottomId,tableAreaId,tableRoundUDId,tableRoundLRId,circleId,baffleId);//�������Ӷ���
            wall=new Wall(wallId);
            floor=new TextureRect//�����ذ�
            (
            		TABLE_AREA_LENGTH/4,0,TABLE_AREA_WIDTH/4,groundId,
            		new float[]
			          {
            				0,0,0,1,1,1,
            				1,1,1,0,0,0
			          }
            );
            
            
            icon=new TextureRect//��ϰ ͼ�����
            (
            		0.3f,0.3f,0,iconId,
            		new float[] 
			        {
			        	0,0,0,1,1,1,
			        	1,1,1,0,0,0
			        }
            );
            iconFirst=new TextureRect//һ����ҵ��Ǳ��
            (
            		1.2f,0.6f,0,iconIdFirst,
            		new float[] 
			        {
			        	0,0,0,1,1,1,
			        	1,1,1,0,0,0
			        }	
            );
            iconSecond=new TextureRect//������ҵ��Ǳ��
            (
            		1.2f,0.6f,0,iconIdSecond,
            		new float[] 
			        {
			        	0,0,0,1,1,1,
			        	1,1,1,0,0,0
			        }	
            );
            tipOne=new TextureRect//һ�������ʾ
            (
            	1.2f,0.48f,0,tipIdOne,
            	new float[]
		          {
            			0,0,0,0.5f,0.625f,0.5f,
			        	0.625f,0.5f,0.625f,0,0,0
		          }
            );
            tipTwo=new TextureRect//���������ʾ
            (
            	1.2f,0.48f,0,tipIdTwo,
            	new float[]
		          {
            			0,0,0,0.5f,0.625f,0.5f,
			        	0.625f,0.5f,0.625f,0,0,0
		          }
            );
            vs=new TextureRect//vsͼƬ
            (
            		0.8f,0.4f,0,vsId, 
                	new float[]
    		          {
                			0,0,0,1,1,1,
    			        	1,1,1,0,0,0
    		          }	
            );
            
            
            tipO=new TextureRect//��ʾ��ȨͼƬ
            (
            	0.6f,0.3f,0,tipId,
            	new float[]
	          {
				0,0,0,1,1,1,
	        	1,1,1,0,0,0
	          }
            );
                        
            score=new Score(numberId,MySurfaceView.this);//�÷�
            scoreFirst=new Score(numberIdFirst,MySurfaceView.this);//���1�÷�
            scoreSecond=new Score(numberIdSecond,MySurfaceView.this);//���2�÷�
    
            //�������ڻ��Ƶ���
            btbv=new BallTextureByVertex(BALL_SCALE);
            
            //�������ڿ��Ƶ���
            //0����--ĸ��
            bfd=new BallForControl(btbv,0,9,ballTexId[0]);
            ballAl.add(bfd);
            //1-15����,ȫ����Ч
            bfd=new BallForControl(btbv,0,1-BALL_DISTANCE,ballTexId[1]);
            ballAl.add(bfd);
          	bfd=new BallForControl(btbv,-BALL_R-0.1f,0-BALL_DISTANCE+UNIT_D,ballTexId[2]);
            ballAl.add(bfd);  
            bfd=new BallForControl(btbv,BALL_R+0.1f,0-BALL_DISTANCE+UNIT_D,ballTexId[3]);
            ballAl.add(bfd);            
            bfd=new BallForControl(btbv,-2*BALL_R-0.1f,-1-BALL_DISTANCE+2*UNIT_D,ballTexId[4]);
            ballAl.add(bfd);
            bfd=new BallForControl(btbv,0,-1-BALL_DISTANCE+2*UNIT_D,ballTexId[5]);
            ballAl.add(bfd);
            bfd=new BallForControl(btbv,2*BALL_R+0.1f,-1-BALL_DISTANCE+2*UNIT_D,ballTexId[6]);
            ballAl.add(bfd);
            bfd=new BallForControl(btbv,-3*BALL_R-0.1f,-2-BALL_DISTANCE+3*UNIT_D,ballTexId[7]);
            ballAl.add(bfd);
            bfd=new BallForControl(btbv,-1f*BALL_R,-2-BALL_DISTANCE+3*UNIT_D,ballTexId[8]);
            ballAl.add(bfd);
            bfd=new BallForControl(btbv,1*BALL_R+0.1f,-2-BALL_DISTANCE+3*UNIT_D,ballTexId[9]);
            ballAl.add(bfd);            
            bfd=new BallForControl(btbv,3*BALL_R+0.2f,-2-BALL_DISTANCE+3*UNIT_D,ballTexId[10]);
            ballAl.add(bfd);
            bfd=new BallForControl(btbv,-4*BALL_R-0.2f,-3-BALL_DISTANCE+4*UNIT_D,ballTexId[11]);
            ballAl.add(bfd);
            bfd=new BallForControl(btbv,-2*BALL_R-0.1f,-3-BALL_DISTANCE+4*UNIT_D,ballTexId[12]);
            ballAl.add(bfd);
            bfd=new BallForControl(btbv,0,-3-BALL_DISTANCE+4*UNIT_D,ballTexId[13]);
            ballAl.add(bfd);
            bfd=new BallForControl(btbv,2*BALL_R+0.1f,-3-BALL_DISTANCE+4*UNIT_D,ballTexId[14]);
            ballAl.add(bfd);
            bfd=new BallForControl(btbv,4*BALL_R+0.2f,-3-BALL_DISTANCE+4*UNIT_D,ballTexId[15]);
            ballAl.add(bfd);   /*   */         
            tempBallAl=ballAl;
            //����������˶��߳�
            bgt=new BallGoThread(ballAl,MySurfaceView.this);
            bgt.start();
          
            new Thread()//ת�������
			{
				public void run()
				{
					try
					{
						sleep(100);
					}catch(Exception e)
					{
						e.printStackTrace();
					}
					if(turnFlag)
					{
						while(angle<6.3f)
						{
							cx=(float)(tx+Math.sin(angle)*DISTANCE_CAMERA_YACHT);//�����x����
			  		        cz=(float)(tz+Math.cos(angle)*DISTANCE_CAMERA_YACHT);//�����z����
							angle=direction+angle+DEGREE_SPAN;
							try{
								sleep(50);
							}catch(Exception e)
							{
								e.printStackTrace();
							}
						}
						turnFlag=false;
						angle=0.0f;
					}
					
				}	
			}.start();
            
         
        }
    }
	
	//��ʼ������
	public int initTexture(GL10 gl,int drawableId)//textureId
	{
		//��������ID
		int[] textures = new int[1];
		gl.glGenTextures(1, textures, 0);    //�ṩδʹ�õ������������
		int currTextureId=textures[0];    
		gl.glBindTexture(GL10.GL_TEXTURE_2D, currTextureId);//������ʹ���������
		gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_MIN_FILTER,GL10.GL_NEAREST);//ָ���Ŵ���С���˷���
        gl.glTexParameterf(GL10.GL_TEXTURE_2D,GL10.GL_TEXTURE_MAG_FILTER,GL10.GL_LINEAR);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_S,GL10.GL_REPEAT);
        gl.glTexParameterf(GL10.GL_TEXTURE_2D, GL10.GL_TEXTURE_WRAP_T,GL10.GL_REPEAT);
        
        InputStream is = this.getResources().openRawResource(drawableId);
        Bitmap bitmapTmp; 
        try 
        {
        	bitmapTmp = BitmapFactory.decodeStream(is);
        } 
        finally 
        {
            try 
            {
                is.close();
            } 
            catch(IOException e) 
            {
                e.printStackTrace();
            }
        }
        GLUtils.texImage2D(GL10.GL_TEXTURE_2D, 0, bitmapTmp, 0);//�����ά����
        bitmapTmp.recycle(); 
        
        return currTextureId;
	}
	
	//��ʼ����Դ
	private void initSunLight(GL10 gl)
	{
        gl.glEnable(GL10.GL_LIGHT0);//��0�ŵ�  
        
        //����������
        float[] ambientParams={0.85f,0.85f,0.85f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_AMBIENT, ambientParams,0);            
        
        //ɢ�������
        float[] diffuseParams={0.05f,0.05f,0.05f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_DIFFUSE, diffuseParams,0); 
        
        //���������
        float[] specularParams={0f,0f,0.0f,1.0f};//����� RGBA
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_SPECULAR, specularParams,0);  
        
        //�趨��Դ��λ��
    	float[] positionParamsGreen={0,15f,0f,1};//����1��ʾʹ�ö�λ��
        gl.glLightfv(GL10.GL_LIGHT0, GL10.GL_POSITION, positionParamsGreen,0); 
	}

	
	//��ʼ������
	private void initMaterial(GL10 gl)
	{//����Ϊ��ɫʱʲô��ɫ�Ĺ���������ͽ����ֳ�ʲô��ɫ
        //������Ϊ��ɫ����
        float ambientMaterial[] = {0.9f, 0.9f, 0.9f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_AMBIENT, ambientMaterial,0);
        //ɢ���Ϊ��ɫ����
        float diffuseMaterial[] = {0.01f, 0.01f, 0.01f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_DIFFUSE, diffuseMaterial,0);
        //�߹����Ϊ��ɫ
        float specularMaterial[] = {0.0f, 0.0f, 0.0f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_SPECULAR, specularMaterial,0);  
        //�߹ⷴ������,��Խ���������ԽСԽ��
        float shininessMaterial[] = {5.5f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_SHININESS, shininessMaterial,0);
	}
	public void backMenu()
	{
		if(activity.netFlag) //��սģʽ��
		{
				switch(winLoseFlag)
				{
					case 1:		
						activity.toAnotherView(ENTER_WIN);	//�����ʤ����
						break;
		
					case 2:		
						activity.toAnotherView(ENTER_LOSE);//����ʧ�ܽ���
						break;		
				}			
			cueFlag=true;//ת����˱�־λ��Ϊtrue
		}
		else//��ϰģʽ
		{
			activity.toAnotherView(ENTER_OVER);//��ͼ��������
			cueFlag=true;
		}
		bgt.flag=false;//�̱߳�־λ��false
		try
		{
			ballAl.clear();//������б�
		}catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	public void ballhit()//������ײ������
    {
		activity.playSound(2, 0);
    }
}

