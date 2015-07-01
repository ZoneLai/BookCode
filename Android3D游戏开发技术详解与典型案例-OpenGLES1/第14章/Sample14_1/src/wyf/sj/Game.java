package wyf.sj;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.LinkedList;
import java.util.Stack;

import android.util.Log;
import android.view.SurfaceHolder;

public class Game{
	MySurfaceView mSurfaceView;//��������������
	int[][] map=MapList.map[0];//��Ҫ�����ĵ�ͼ
	int[] source=MapList.source;//����������
	int[] target=MapList.targetA[0];//Ŀ���col,row
	int algorithmId=0;//�㷨���ţ�0--��Ȳ���
	
	ArrayList<int[][]> searchProcess=new ArrayList<int[][]>();//��������
	Stack<int[][]> stack=new Stack<int[][]>();//�����������ջ
	LinkedList<int[][]> queue=new LinkedList<int[][]>();//����������ö���
	PriorityQueue<int[][]> astarQueue=new PriorityQueue<int[][]>(100,new AStarComparator(this));//A*���ȼ�����
	HashMap<String,int[][]> hm=new HashMap<String,int[][]>();//���·����¼
	int[][] visited=new int[19][19];//0 δȥ�� 1 ��ȥ��
	int[][] length=new int[19][19];//��¼·������ for Dijkstra
	// ��¼��ÿ��������·��for Dijkstra
	HashMap<String,ArrayList<int[][]>> hmPath=new HashMap<String,ArrayList<int[][]>>();
	
	boolean pathFlag=false;//true �ҵ�·��
	int timeSpan=10;//ʱ����
	SurfaceHolder holder;
	int[][] sequence=
	{
		{0,1},{0,-1},
		{-1,0},{1,0},
		{-1,1},{-1,-1},
		{1,-1},{1,1}
	};
	
	int tempCount;//��¼�������������ò���
	final int DFS_COUNT=1;//�������ʹ�ò�����־
	final int BFS_COUNT=2;//�������ʹ�ò�����־
	final int BFSASTAR_COUNT=3;//�������ʹ�ò�����־
	final int DIJKSTRA_COUNT=4;//Dijkstraʹ�ò�����־
	final int DIJKSTRASTAR_COUNT=5;//DijkstraA*ʹ�ò�����־
	public Game(MySurfaceView mSurfaceView,SurfaceHolder holder)
	{
		this.mSurfaceView=mSurfaceView;
		this.holder=holder;
	}
	public void clearState()//��ʼ��������
	{
		searchProcess.clear();//������������б�
		stack.clear();//��������������ջ
		queue.clear();//��չ���������ö���
		astarQueue.clear();//���A*���ȼ�����
		hm.clear();//��ս��·����¼
		visited=new int[19][19];//��ʼ������
		pathFlag=false;	//Ѱ��·����־λ
		hmPath.clear();//���Dijkstra�м�¼��ÿ��������·��
		mSurfaceView.paint.setStrokeWidth(0);//��ʼ������
		for(int i=0;i<length.length;i++)
		{
			for(int j=0;j<length[0].length;j++)
			{
				length[i][j]=9999;//���ó�ʼ·���ĳ��ȣ���������ô��
			}
		}	
	}
	public void runAlgorithm()
	{
		clearState();//���ó�ʼ������
		switch(algorithmId)
		{
			case 0://��������㷨
			  DFS();
			break;
			case 1://��������㷨			
			  BFS();
			break;
			case 2://�������A*�㷨
			  BFSAStar();
			break;
			case 3://Dijkstra�㷨
			  Dijkstra();
			  Log.d("Dijkstra", "algorithmId="+algorithmId);
			break;
			case 4://DijkstraA*�㷨
			  DijkstraAStar();
			break;
		}		
	}
	
	public void DFS()//�������
	{
		new Thread()
		{
			public void run()
			{
				boolean flag=true;//�̱߳�־λ
				int[][] start=//��ʼ������������
				{
					{source[0],source[1]},
					{source[0],source[1]}
				};
				stack.push(start);//��ջ
				int count=0;//ʹ�ò���������
				while(flag)
				{
					
					int[][] currentEdge=stack.pop();//��ջ��ȡ����
					int[] tempTarget=currentEdge[1];//ȡ���˱ߵ�Ŀ�ĵ�
					
					//�ж�Ŀ�ĵ��Ƿ�ȥ������ȥ������ֱ�ӽ����´�ѭ��
					if(visited[tempTarget[1]][tempTarget[0]]==1)
					{
						continue;
					}
					count++;//�������Լ�
					//��ʾĿ�ĵ㱻���ʹ�
					visited[tempTarget[1]][tempTarget[0]]=1;
					
					//����ʱĿ����������������
					searchProcess.add(currentEdge);
					//��¼����ʱ�ڵ�ĸ��ڵ�
					hm.put(tempTarget[0]+":"+tempTarget[1],new int[][]{currentEdge[1],currentEdge[0]});
					//�ػ滭��
					mSurfaceView.repaint(holder);
					//�߳�˯��һ��ʱ��
					try{Thread.sleep(timeSpan);}catch(Exception e){e.printStackTrace();}
					
					//�ж��Ƿ񵽴�Ŀ�ĵ�
					if(tempTarget[0]==target[0]&&tempTarget[1]==target[1])
					{
						break;
					}
					
					//�����п��ܵı���ջ
					int currCol=tempTarget[0];//ȡ�߽ڵ�
					int currRow=tempTarget[1];
					
					for(int[] rc:sequence)//ɨ��õ㸽�����п��ܵı�
					{
						int i=rc[1];
						int j=rc[0];
						if(i==0&&j==0){continue;}//��Ϊ0��0�����ô�ѭ��
						if(currRow+i>=0&&currRow+i<19&&currCol+j>=0&&currCol+j<19&&
						map[currRow+i][currCol+j]!=1)//���ڵ�ͼ��
						{
							int[][] tempEdge=
							{
								{tempTarget[0],tempTarget[1]},
								{currCol+j,currRow+i}
							};
							stack.push(tempEdge);//��ջ
						}
					}
				}
				pathFlag=true;	//��־λ��Ϊtrue
				mSurfaceView.repaint(holder);//�ػ滭��
				tempCount=count;//�������ʹ�ò���
				mSurfaceView.mActivity.hd.sendEmptyMessage(DFS_COUNT);//������Ϣ����ʹ�ò�������
				mSurfaceView.mActivity.button.setClickable(true);	//����button���Ե��
			}
		}.start();		
	}
	
	
	public void BFS()//�������
	{
		new Thread()
		{
			public void run()
			{
				int count=0;//������
				boolean flag=true;//ѭ����־λ
				int[][] start=//��ʼ״̬
				{
					{source[0],source[1]},
					{source[0],source[1]}
				};
				queue.offer(start);//����ʼ�����ö��е�ĩβ
				
				while(flag)
				{					
					int[][] currentEdge=queue.poll();//��ȡ���Ƴ���ͷ
					int[] tempTarget=currentEdge[1];//ȡ���˱ߵ�Ŀ�ĵ�
					
					//�ж��Ƿ�ȥ������ȥ����ֱ�ӽ����´�ѭ��
					if(visited[tempTarget[1]][tempTarget[0]]==1)
					{
						continue;
					}
					count++;//�������Լ�
					//��ȥ���ĵ���Ϊ1
					visited[tempTarget[1]][tempTarget[0]]=1;
					
					//����ʱĿ��������������
					searchProcess.add(currentEdge);
					//��¼����ʱ�ڵ�ĸ��ڵ�
					hm.put(tempTarget[0]+":"+tempTarget[1],new int[][]{currentEdge[1],currentEdge[0]});
					//�ػ滭��
					mSurfaceView.repaint(holder);
					//�߳�˯��һ��ʱ��
					try{Thread.sleep(timeSpan);}catch(Exception e){e.printStackTrace();}
					
					//�ж��Ƿ�ΪĿ�ĵ�
					if(tempTarget[0]==target[0]&&tempTarget[1]==target[1])
					{
						break;
					}
					
					//�����п��ܵı������
					int currCol=tempTarget[0];
					int currRow=tempTarget[1];
					
					for(int[] rc:sequence)
					{
						int i=rc[1];
						int j=rc[0];
						
						if(i==0&&j==0){continue;}//���ڵ�ͼ���棬������һ��ѭ��
						if(currRow+i>=0&&currRow+i<19&&currCol+j>=0&&currCol+j<19&&
						map[currRow+i][currCol+j]!=1)//��Ϊ��ͼ�ڵĵ�
						{
							int[][] tempEdge=
							{
								{tempTarget[0],tempTarget[1]},
								{currCol+j,currRow+i}
							};
							queue.offer(tempEdge);//���ĵ�������ĩβ
						}
					}
				}
				pathFlag=true;	//��־λ��Ϊtrue
				mSurfaceView.repaint(holder);//�ػ滭��
				tempCount=count;//�������ʹ�ò���
				mSurfaceView.mActivity.hd.sendEmptyMessage(BFS_COUNT);	//������Ϣ����ʹ�ò�������
				mSurfaceView.mActivity.button.setClickable(true);//����button�����Ե��
			}
		}.start();			
	}
	
	
	public void BFSAStar()//�������A*
	{
		new Thread()
		{
			public void run()
			{
				boolean flag=true;
				int[][] start=//��ʼ״̬
				{
					{source[0],source[1]},
					{source[0],source[1]}
				};
				astarQueue.offer(start);//����ʼ��������ĩβ
				int count=0;//������
				while(flag)
				{					
					int[][] currentEdge=astarQueue.poll();//��ȡ��ͷ��������ͷ�Ƴ�
					int[] tempTarget=currentEdge[1];//ȡ�˱ߵ�Ŀ���
					
					//�ж��Ƿ�ȥ������ȥ����ֱ�ӽ����´�ѭ��
					if(visited[tempTarget[1]][tempTarget[0]]!=0)
					{
						continue;
					}
					count++;
					//��ʾĿ���Ϊ���ʹ�
					visited[tempTarget[1]][tempTarget[0]]=visited[currentEdge[0][1]][currentEdge[0][0]]+1;				
					//����ʱĿ����������������
					searchProcess.add(currentEdge);
					//��¼����ʱ�ڵ�ĸ��ڵ�
					hm.put(tempTarget[0]+":"+tempTarget[1],new int[][]{currentEdge[1],currentEdge[0]});
					//�ػ滭��
					mSurfaceView.repaint(holder);
					
					try{Thread.sleep(timeSpan);}catch(Exception e){e.printStackTrace();}
					
					//�ж��Ƿ�ΪĿ���
					if(tempTarget[0]==target[0]&&tempTarget[1]==target[1])
					{
						break;
					}
					
					//�����п��ܵı߼������
					int currCol=tempTarget[0];
					int currRow=tempTarget[1];
					
					for(int[] rc:sequence)
					{
						int i=rc[1];
						int j=rc[0];
						if(i==0&&j==0){continue;}
						if(currRow+i>=0&&currRow+i<19&&currCol+j>=0&&currCol+j<19&&
						map[currRow+i][currCol+j]!=1)
						{
							int[][] tempEdge=
							{
								{tempTarget[0],tempTarget[1]},
								{currCol+j,currRow+i}
							};
							astarQueue.offer(tempEdge);//�������ĩβ
						}						
					}
				}
				pathFlag=true;	
				mSurfaceView.repaint(holder);
				tempCount=count;//�������A*ʹ�ò���
				mSurfaceView.mActivity.hd.sendEmptyMessage(BFSASTAR_COUNT);//������Ϣ����ʹ�ò�������
				mSurfaceView.mActivity.button.setClickable(true);	//����buttonΪ�ɵ�				
			}
		}.start();				
	}
	
	
	public void Dijkstra()//Dijkstra
	{
		new Thread()
		{
			public void run()
			{
				int count=0;//���������
				boolean flag=true;//����ѭ������
				//��ʼ��
				int[] start={source[0],source[1]};//col,row	
				visited[source[1]][source[0]]=1;
				//����˵����п��Ե�����·��������
				for(int[] rowcol:sequence)
				{					
					int trow=start[1]+rowcol[1];
					int tcol=start[0]+rowcol[0];
					if(trow<0||trow>18||tcol<0||tcol>18)continue;
					if(map[trow][tcol]!=0)continue;
					
					//��¼·������
					length[trow][tcol]=1;
					
					//����·��					
					String key=tcol+":"+trow;
					ArrayList<int[][]> al=new ArrayList<int[][]>();
					al.add(new int[][]{{start[0],start[1]},{tcol,trow}});
					hmPath.put(key,al);	
					
					//��ȥ���ĵ��¼		
					searchProcess.add(new int[][]{{start[0],start[1]},{tcol,trow}});
					count++;			
				}	
				mSurfaceView.repaint(holder);//�ػ�
				outer:while(flag)
				{					
					//�ҵ���ǰ��չ��K Ҫ����չ��KΪ�ӿ�ʼ�㵽�˵�Ŀǰ·����̣��Ҵ˵�δ�����
					int[] k=new int[2];
					int minLen=9999;
					for(int i=0;i<visited.length;i++)
					{
						for(int j=0;j<visited[0].length;j++)
						{
							if(visited[i][j]==0)
							{
								if(minLen>length[i][j])
								{
									minLen=length[i][j];
									k[0]=j;//col
									k[1]=i;//row
								}
							}
						}
					}
					
					//����ȥ���ĵ�
					visited[k[1]][k[0]]=1;					
					
					//	�ػ�				
					mSurfaceView.repaint(holder);
					
					//ȡ����ʼ�㵽K��·������
					int dk=length[k[1]][k[0]];
					//ȡ����ʼ�㵽K��·��
					ArrayList<int[][]> al=hmPath.get(k[0]+":"+k[1]);
					
					//ѭ����������K����ֱ�ӵ��ĵ㵽��ʼ���·������
					for(int[] rowcol:sequence)
					{
						//������µ�Ҫ����ĵ������
						int trow=k[1]+rowcol[1];
						int tcol=k[0]+rowcol[0];
						
						//��Ҫ����ĵ㳬����ͼ�߽���ͼ�ϴ�λ��Ϊ�ϰ�������������˵�
						if(trow<0||trow>18||tcol<0||tcol>18)continue;
						if(map[trow][tcol]!=0)continue;
						
						//ȡ����ʼ�㵽�˵��·������
						int dj=length[trow][tcol];
						//���㾭K�㵽�˵��·������				
						int dkPluskj=dk+1;
						
						//����K�㵽�˵��·�����ȱ�ԭ����С���޸ĵ��˵��·��
						if(dj>dkPluskj)
						{
							String key=tcol+":"+trow;
							//��¡��ʼ�㵽K��·��
							ArrayList<int[][]> tempal=(ArrayList<int[][]>)al.clone();
							//��·���м���һ����K���˵�
							tempal.add(new int[][]{{k[0],k[1]},{tcol,trow}});
							//����·������Ϊ�ӿ�ʼ�㵽�˵��·��
							hmPath.put(key,tempal);
							//�޸ĵ��ӿ�ʼ�㵽�˵��·������						
							length[trow][tcol]=dkPluskj;
							
							//���˵��δ�����·�������򽫴˵���뿼����̼�¼
							if(dj==9999)
							{
								//��ȥ���ĵ��¼		
								searchProcess.add(new int[][]{{k[0],k[1]},{tcol,trow}});
								count++;
							}
						}
						
						//���Ƿ��ҵ�Ŀ�ĵ�
						if(tcol==target[0]&&trow==target[1])
						{
							pathFlag=true;
							tempCount=count;//Dijkstraʹ�ò���
							mSurfaceView.mActivity.hd.sendEmptyMessage(DIJKSTRA_COUNT);	//������Ϣ����ʹ�ò���
							mSurfaceView.mActivity.button.setClickable(true);
							mSurfaceView.repaint(holder);
							break outer;
						}
					}										
					try{Thread.sleep(timeSpan);}catch(Exception e){e.printStackTrace();}				
				}								
			}
		}.start();	
		
	}
	public void DijkstraAStar()//Dijkstra A*�㷨
	{
		new Thread()
		{
			public void run()
			{
				int count=0;//����������
				boolean flag=true;//����ѭ������
				//��ʼ��
				int[] start={source[0],source[1]};//col,row	
				visited[source[1]][source[0]]=1;
				//����˵����п��Ե�����·��
				for(int[] rowcol:sequence)
				{					
					int trow=start[1]+rowcol[1];
					int tcol=start[0]+rowcol[0];
					if(trow<0||trow>18||tcol<0||tcol>18)continue;
					if(map[trow][tcol]!=0)continue;
					
					//��¼·������
					length[trow][tcol]=1;
					
					//����·��				
					String key=tcol+":"+trow;
					ArrayList<int[][]> al=new ArrayList<int[][]>();
					al.add(new int[][]{{start[0],start[1]},{tcol,trow}});
					hmPath.put(key,al);	
					
					//��ȥ���ĵ��¼			
					searchProcess.add(new int[][]{{start[0],start[1]},{tcol,trow}});					
					count++;			
				}				
				mSurfaceView.repaint(holder);
				outer:while(flag)
				{					
					int[] k=new int[2];
					int minLen=9999;
					boolean iniFlag=true;
					for(int i=0;i<visited.length;i++)
					{
						for(int j=0;j<visited[0].length;j++)
						{
							if(visited[i][j]==0)
							{
								//����ͨDijkstra�㷨�����𲿷�
								if(length[i][j]!=9999)
								{
									if(iniFlag)
									{//��һ���ҵ��Ŀ��ܵ�
										minLen=length[i][j]+
										(int)Math.sqrt((j-target[0])*(j-target[0])+(i-target[1])*(i-target[1]));
										k[0]=j;//col
										k[1]=i;//row
										iniFlag=!iniFlag;
									}
									else
									{
										int tempLen=length[i][j]+
										(int)Math.sqrt((j-target[0])*(j-target[0])+(i-target[1])*(i-target[1]));
										if(minLen>tempLen)
										{
											minLen=tempLen;
											k[0]=j;//col
											k[1]=i;//row
										}
									}
								}
								//����ͨDijkstra�㷨���𲿷�
							}
						}
					}
					//����ȥ���ĵ�
					visited[k[1]][k[0]]=1;					
					
					//�ػ�					
					mSurfaceView.repaint(holder);
					
					int dk=length[k[1]][k[0]];
					ArrayList<int[][]> al=hmPath.get(k[0]+":"+k[1]);
					//ѭ����������K����ֱ�ӵ��ĵ㵽��ʼ���·������
					for(int[] rowcol:sequence)
					{
						//������µ�Ҫ����ĵ������
						int trow=k[1]+rowcol[1];
						int tcol=k[0]+rowcol[0];
						//��Ҫ����ĵ㳬����ͼ�߽���ͼ�ϴ�λ��Ϊ�ϰ�������������˵�
						if(trow<0||trow>18||tcol<0||tcol>18)continue;
						if(map[trow][tcol]!=0)continue;
						//ȡ����ʼ�㵽�˵��·������
						int dj=length[trow][tcol];	
						//���㾭K�㵽�˵��·������
						int dkPluskj=dk+1;
						//����K�㵽�˵��·�����ȱ�ԭ����С���޸ĵ��˵��·��
						if(dj>dkPluskj)
						{
							String key=tcol+":"+trow;
							ArrayList<int[][]> tempal=(ArrayList<int[][]>)al.clone();
							tempal.add(new int[][]{{k[0],k[1]},{tcol,trow}});
							hmPath.put(key,tempal);							
							length[trow][tcol]=dkPluskj;
							
							if(dj==9999)
							{
								//��ȥ���ĵ��¼		
								searchProcess.add(new int[][]{{k[0],k[1]},{tcol,trow}});								
								count++;
							}
						}
						
						//���Ƿ��ҵ�Ŀ�ĵ�
						if(tcol==target[0]&&trow==target[1])
						{
							Log.d("target[0]="+target[0], "target[1]="+target[1]);
							pathFlag=true;	
							tempCount=count;//DijkstraA*ʹ�ò���
							mSurfaceView.mActivity.hd.sendEmptyMessage(DIJKSTRASTAR_COUNT);	//����ʹ�ò�������
							mSurfaceView.mActivity.button.setClickable(true);	
							mSurfaceView.repaint(holder);
							break outer;
						}
					}										
					try{Thread.sleep(timeSpan);}catch(Exception e){e.printStackTrace();}				
				}								
			}
		}.start();					
	}
	
}
