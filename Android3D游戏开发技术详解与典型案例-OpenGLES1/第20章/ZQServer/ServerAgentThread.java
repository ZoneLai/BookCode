package wyf.jsc;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.net.*;
public class ServerAgentThread extends Thread
{
	Socket sc;
	DataInputStream din;
	DataOutputStream dout;
	boolean flag=true;//ѭ�����Ʊ�־λ
	int id=0;//�ڼ���ұ�־λ 0-��ʼ 1-��һ��� 2-�ڶ����
	ServerThread father;
	
	public ServerAgentThread(ServerThread father,Socket sc,int id)
	{
		this.father=father;
		this.sc=sc;
		this.id=id;
		try
		{
			din=new DataInputStream(sc.getInputStream());
			dout=new DataOutputStream(sc.getOutputStream());
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
	}
	
	public void run()
	{
		while(flag)
		{
			try{
				String msg=din.readUTF();
				System.out.println(msg);
				
				if(msg.startsWith("<#ENTER_REQUEST#>"))
				{//�������������Ϸ
					if(id<=2)
					{
						System.out.println("id="+id);
						//�������
						dout.writeUTF("<#ALLOW_ENTER#>");						
						father.userList[id-1]=this;
						if(id==2)
						{//�������û�����Ϸ��ʼ��Ϣ
							sendMsgTo2Users("<#GAME_START#>");
							//��1���û�����Ȩ��Ϣ
							sendHitFlag(1);
							//���û���Id��Ϣ
						    sendMsgTo1User("<#YOU_ID#>1",1);
						    sendMsgTo1User("<#YOU_ID#>2",2);
						}							
					}
					else
					{//�����������ý�
						dout.writeUTF("<#USER_FULL#>");					
						flag=false;
						sc.close();
						din.close();
						dout.close();
					}					
				}
				else if(msg.startsWith("<#CUE_ANGLE#>"))
				{//�յ�����Ȩ����ת�������Ϣ
					String temps=msg.trim().substring(13);
					//��ת�������Ϣת�����������
					sendMsgTo2Users("<#CUE_ANGLE_PUBLISH#>"+temps);
				}
				else if(msg.startsWith("<#BALL_HIT#>"))
				{//�յ�ĳ�˻������Ϣ��ת�����������
					String temps=msg.trim().substring(12);
					sendMsgTo2Users("<#BALL_HIT_PUBLISH#>"+temps);
				}
				else if(msg.startsWith("<#BALL_GO_OVER#>"))
				{//�յ���ͣ��Ϣ
				   father.stopCount++;
				   if(father.stopCount==2)
				   {//���յ�������ͣ��Ϣ����������ҷ���Ϸ������Ϣ
				   	  father.stopCount=0;
				   	  sendMsgTo2Users("<#GAME_CONTINUE#>");
				   	  //����һ����ҷ�����Ȩ��Ϣ
				   	  if(!father.inFlag)
				   	  {
				   	  	father.hitId=(father.hitId==1)?2:1;				   	  	
				   	  }
				   	  father.inFlag=false;
				   	  
				   	  sendHitFlag(father.hitId);
				   }
					
				}
				else if(msg.startsWith("<#BALL_IN_HOLE#>"))
				{//�յ��������Ϣ
					father.inCount++;
					if(father.inCount==2)
					{//���յ����������Ϣ���ͼӷ���Ϣ��������ң����ı����
					    father.inCount=0;
					    father.inFlag=true;
					    
						sendMsgTo2Users("<#SCORE_UP#>"+father.hitId);
						addScore(father.hitId);
						
						//��ȡ������
						int total=Integer.parseInt(msg.substring(16));
						//��������Ϊ1֪ͨ��Ӯ
						if(total==1)
						{
							if(father.scores[0]>father.scores[1])
							{//1����һ�ʤ
								sendMsgTo1User("<#YOU_WIN#>",1);
								sendMsgTo1User("<#YOU_LOST#>",2);
							}
							else
							{//2����һ�ʤ
								sendMsgTo1User("<#YOU_WIN#>",2);
								sendMsgTo1User("<#YOU_LOST#>",1);
							}
						}
					}
				}
				else if(msg.startsWith("<#OVER_OK#>"))
				{//������������˳�
					father.overCount++;
					if(father.overCount==2)
					{
						father.initState();
					}
					flag=false;
					din.close();
					dout.close();
					sc.close();
				}
				else if(msg.startsWith("<#EXIT_MAN#>"))
				{//�յ�ĳ�����ǿ���˳���Ϣ
					sendMsgTo2Users("<#ALLOW_EXIT#>");
				}
				
			}catch(Exception e)
			{
				System.out.println("���˵�����");				
				try
				{
						sendMsgTo1User("<#ALLOW_EXIT#>",2);	
				}
				catch(Exception ea)
				{
					ea.printStackTrace();
				}
				try
				{						
						sendMsgTo1User("<#ALLOW_EXIT#>",1);
				}
				catch(Exception ea)
				{
					ea.printStackTrace();
				}
				father.initState();
				break;
			}
		}
	}
	
	//��Id�ſͻ�����Ȩ��Ϣ
	public void sendHitFlag(int id) throws Exception 
	{
			father.hitId=id;			
			father.userList[id-1].dout.writeUTF("<#HIT_FLAG#>");	
			System.out.println("������Ȩ "+id);
			sendMsgTo2Users("<#CURRENT_HIT_USER#>"+id);
			System.out.println("�л���� "+"<#CURRENT_HIT_USER#>"+id);
	}
	
	//��������ҷ�ͬ������Ϣ
	public void sendMsgTo2Users(String msg) throws Exception 
	{
		System.out.println("��������ҷ���Ϣ"+msg);
		for(ServerAgentThread sat:father.userList)
		{
			sat.dout.writeUTF(msg);
		}
	}
	
	//��ָ��ID��ҷ�����Ϣ
	public void sendMsgTo1User(String msg,int id) throws Exception 
	{
		father.userList[id-1].dout.writeUTF(msg);
	}
	
	//��ָ���û��ӷ�
	public void addScore(int id)
	{
		father.scores[id-1]++;
	}
}