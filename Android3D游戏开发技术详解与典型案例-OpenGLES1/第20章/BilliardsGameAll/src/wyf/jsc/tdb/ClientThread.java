package wyf.jsc.tdb;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;

import android.util.Log;

import static wyf.jsc.tdb.Constant.*;


public class ClientThread extends Thread
{
	MyActivity father;
	Socket sc;
	DataInputStream din;
	DataOutputStream dout;
	boolean flag=true;

	public ClientThread(MyActivity father,Socket sc) throws Exception
	{
		
		this.father=father;
		this.sc=sc;
		din=new DataInputStream(sc.getInputStream());//����������
		dout=new DataOutputStream(sc.getOutputStream());//���������
		Log.d("","���������");
	}
	
	public void run()
	{
		try
		{//���ͽ�����Ϸ����
			dout.writeUTF("<#ENTER_REQUEST#>");
			Log.d("","����<#ENTER_REQUEST#>���");
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		while(flag)
		{
			try
			{
				String msg=din.readUTF();
				if(msg.startsWith("<#YOU_ID#>")){//��ұ�־���Ƶı�־λ
					String temps=msg.substring(10);
					MySurfaceView.id=Integer.parseInt(temps);
				}
				if(msg.startsWith("<#USER_FULL#>"))//�������
				{
					flag=false;
					din.close();
					dout.close();
					sc.close();									
					father.mButtonOk.setClickable(true);//��������ٴε��					
					father.hd.sendEmptyMessage(USER_FULL);
				}
				else if(msg.startsWith("<#ALLOW_ENTER#>"))//����ȴ�����
				{
					father.hd.sendEmptyMessage(ENTER_WAIT);
				}
				else if(msg.startsWith("<#GAME_START#>"))//��ʼ��Ϸ
				{
					father.hd.sendEmptyMessage(START_GAME);
				}
				else if(msg.startsWith("<#HIT_FLAG#>"))//������������Ȩ
				{
					hitFlag=true;
				}
				else if(msg.startsWith("<#CUE_ANGLE_PUBLISH#>"))//���ת���Ƕ�Э��
				{
					msg=msg.substring(21);
					Cue.angleZ=Float.parseFloat(msg);
				}
				else if(msg.startsWith("<#BALL_HIT_PUBLISH#>"))//�������ȡ��Ƕȵ�Э��
				{
					int i=0;
					msg=msg.substring(20);
					String tempStr[]=msg.split("\\|");//����ַ�
					String tempStr2[]=new String[tempStr.length];
					for(String ss:tempStr)
					{	
						tempStr2[i++]=ss;
					}
					hitNum=Float.parseFloat(tempStr2[0]);//��ȡ�ٶ�
					float tempAngle=Float.parseFloat(tempStr2[1]);//��ȡ�Ƕ�
					tempBallAl.get(0).vx=(float)(hitNum*Math.sin(Math.toRadians(tempAngle)));//����ĸ����ٶ�
					tempBallAl.get(0).vz=(float)(-1*hitNum*Math.cos(Math.toRadians(tempAngle)));
					cueFlag=false;
					sendFlag=true;
				}
				else if(msg.startsWith("<#GAME_CONTINUE#>"))//����ҷ��ͼ�����Ϸ��Ϣ
				{
					cueFlag=true;
				}
				else if(msg.startsWith("<#CURRENT_HIT_USER#>"))//����ҷ����л���Ȩ��Ϣ
				{
					String tempMsg=msg.substring(20);
					scoreTip=Integer.parseInt(tempMsg);//�����Ȩ��־λ
				}
				else if(msg.startsWith("<#SCORE_UP#>"))//�÷�Э��
				{
					msg=msg.substring(12);
					scoreNODFlag=Integer.parseInt(msg);//1--һ����Ҽӷ�  2--������Ҽӷ� 
					switch(scoreNODFlag)
					{
					case 1:
							scoreOne++;
							//�����1����ҽ���1�żӷ�
							break;
					case 2:
							scoreTwo++;
							//�����2����ҽ���2�żӷ�
							break;
					}
				}
				else if(msg.startsWith("<#YOU_WIN#>"))//��һ�ʤЭ��
				{
					dout.writeUTF("<#OVER_OK#>");//��������������Ϣ
					flag=false;//�̱߳�־λ�跴
					din.close();//�ر�������
					dout.close();//�ر������
					sc.close();//�ر�ServerSocket
					father.ct=null;//�߳�����ָ���
					winLoseFlag=1;//Ӯ��ʧ�ܱ�־λ
					overFlag=true;//������־λ
					sendFlag=false;//���Ʒ��ͽ�����Ϣ��־λ
				}
				else if(msg.startsWith("<#YOU_LOST#>"))//���ʧ��Э��
				{
					dout.writeUTF("<#OVER_OK#>");//��������������Ϣ
					flag=false;//�̱߳�־λ�跴
					din.close();//�ر�������
					dout.close();//�ر������
					sc.close();//�ر�ServerSocket
					father.ct=null;//�߳�����ָ���
					winLoseFlag=2;//Ӯ��ʧ�ܱ�־λ
					overFlag=true;	//������־λ	
					sendFlag=false;//���Ʒ��ͽ�����Ϣ��־λ
				}
				else if(msg.startsWith("<#ALLOW_EXIT#>"))//�˳�������Э��
				{
					dout.writeUTF("<#OVER_OK#>");//��������������Ϣ
					flag=false;//�̱߳�־λ�跴
					din.close();//�ر�������
					dout.close();//�ر������
					sc.close();//�ر�ServerSocket
					father.ct=null;//�߳�����ָ���
					overFlag=true;	//������־λ		
					sendFlag=false;//���Ʒ��ͽ�����Ϣ��־λ
					father.toAnotherView(ENTER_MENU);//���ؽ�������
					Cue.angleZ=0;//���ת���Ƕ���Ϊ0
				}
			}catch(Exception e)
			{
				e.printStackTrace();//��ӡ�쳣
			}
		}
	}
}