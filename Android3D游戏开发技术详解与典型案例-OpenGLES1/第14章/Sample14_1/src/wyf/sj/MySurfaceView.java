package wyf.sj;
import java.util.ArrayList;
import java.util.HashMap;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
public class MySurfaceView extends SurfaceView
implements SurfaceHolder.Callback { //ʵ���������ڻص��ӿ�
	MyActivity mActivity;//activity����
	Paint paint;//��������
	Game game=new Game(this,getHolder());//��������
	final float span=15.7f;//���δ�С
	final int LJCD_COUNT=6;//·������
	int LjcdCount;//·������
	public MySurfaceView(MyActivity mActivity) {
		super(mActivity);
		// TODO Auto-generated constructor stub
		this.mActivity=mActivity;
		this.getHolder().addCallback(this);//�����������ڻص��ӿڵ�ʵ����
		paint = new Paint();//��������
		paint.setAntiAlias(true);//�򿪿����
	}
	public void onDraw(Canvas canvas){
		int map[][]=game.map;//��ȡ��ͼ
		int row=map.length;//��ͼ����
		int col=map[0].length;//��ͼ����
		canvas.drawARGB(255, 128, 128, 128);//���ñ�����ɫ
		int width=(int)span*map.length;//�������
		int hight=(int)span*map[0].length;// ��������
		canvas.setViewport(width, hight);//���û�����С
		for(int i=0;i<row;i++)//���Ƶ�ͼ
		{
			for(int j=0;j<col;j++)
			{
				if(map[i][j]==1)
				{
					paint.setColor(Color.BLACK);	//���û�����ɫΪ��ɫ	
				}
				else if(map[i][j]==0)
				{
					paint.setColor(Color.WHITE);//���û�����ɫΪ��ɫ
				}
				canvas.drawRect(2+j*(span+1),2+i*(span+1),2+j*(span+1)+span,2+i*(span+1)+span, paint);//���ƾ���
			}
		} 
		//����Ѱ�ҹ���
		ArrayList<int[][]> searchProcess=game.searchProcess;
		for(int k=0;k<searchProcess.size();k++)
		{
			int[][] edge=searchProcess.get(k);  
			paint.setColor(Color.BLACK);//���û�����ɫ
			canvas.drawLine
			(
					edge[0][0]*(span+1)+span/2+2, edge[0][1]*(span+1)+span/2+2, 
					edge[1][0]*(span+1)+span/2+2, edge[1][1]*(span+1)+span/2+2, paint
			);
			
		}
		
		//���ƽ��·��
		if(
				mActivity.mySurfaceView.game.algorithmId==0||
				mActivity.mySurfaceView.game.algorithmId==1||
				mActivity.mySurfaceView.game.algorithmId==2
		)
		{//������ȣ�������ȣ��������A*
			if(game.pathFlag)
			{
				HashMap<String,int[][]> hm=game.hm;		
				int[] temp=game.target;
				int count=0;//·�����ȼ�����	
				while(true)
				{
					int[][] tempA=hm.get(temp[0]+":"+temp[1]);//��ȡ���·����¼
					paint.setColor(Color.BLACK);//���û��ʺ�ɫ
					paint.setStrokeWidth(3);//���û��ʿ��		
					canvas.drawLine//�����߶�
				    (
				    	tempA[0][0]*(span+1)+span/2+2,tempA[0][1]*(span+1)+span/2+2,
						tempA[1][0]*(span+1)+span/2+2,tempA[1][1]*(span+1)+span/2+2,paint
				    );

					
					count++;
					//�ж��Ƿ񵽳�����
					if(tempA[1][0]==game.source[0]&&tempA[1][1]==game.source[1])
					{
						break;
					}
					
					temp=tempA[1];			
				}
				LjcdCount=count;//��¼·������
				mActivity.hd.sendEmptyMessage(LJCD_COUNT);//����·������
			}			
		}
		else if(
				mActivity.mySurfaceView.game.algorithmId==3||
				mActivity.mySurfaceView.game.algorithmId==4
		)
		{//Dijkstra·������
		    if(game.pathFlag)
		    {
		    	Log.d(game.pathFlag+"*****************", "dijkst");
		    	HashMap<String,ArrayList<int[][]>> hmPath=game.hmPath;
				ArrayList<int[][]> alPath=hmPath.get(game.target[0]+":"+game.target[1]);
				for(int[][] tempA:alPath)
				{
					paint.setColor(Color.BLACK);	
					paint.setStrokeWidth(3);
					canvas.drawLine
				    (
				    	tempA[0][0]*(span+1)+span/2+2,tempA[0][1]*(span+1)+span/2+2,
						tempA[1][0]*(span+1)+span/2+2,tempA[1][1]*(span+1)+span/2+2,paint
				    );			
				}
				LjcdCount=alPath.size();//��¼·������
				mActivity.hd.sendEmptyMessage(LJCD_COUNT);//����·������
		    }
		}
		
		
		//���Ƴ�����
		Bitmap bitmapTmpS=BitmapFactory.decodeResource(mActivity.getResources(),R.drawable.source);
		canvas.drawBitmap(bitmapTmpS, game.source[0]*(span+1),game.source[1]*(span+1) , paint);
		//����Ŀ���
		Bitmap bitmapTmpT=BitmapFactory.decodeResource(mActivity.getResources(),R.drawable.target);
		canvas.drawBitmap(bitmapTmpT, game.target[0]*(span+1),game.target[1]*(span+1), paint);
	}
	
	public void surfaceChanged(SurfaceHolder arg0, int arg1, int arg2, int arg3) {
		
	}

	public void surfaceCreated(SurfaceHolder holder) {//����ʱ������
		Canvas canvas = holder.lockCanvas();//��ȡ����
		try{
			synchronized(holder){
				onDraw(canvas);//����
			}			
		}
		catch(Exception e){
			e.printStackTrace();
		}
		finally{
			if(canvas != null){
				holder.unlockCanvasAndPost(canvas);
			}
		}
	}
	
	public void repaint(SurfaceHolder holder)
	{
		Canvas canvas = holder.lockCanvas();//��ȡ����
		try{
			synchronized(holder){
				onDraw(canvas);//����
			}			
		}
		catch(Exception e){
			e.printStackTrace();
		}
		finally{
			if(canvas != null){
				holder.unlockCanvasAndPost(canvas);
			}
		}
	}

	public void surfaceDestroyed(SurfaceHolder arg0) {//����ʱ������

	}
	
	
}
