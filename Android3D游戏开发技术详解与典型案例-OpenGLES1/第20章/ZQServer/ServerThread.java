package wyf.jsc;

import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.net.*;

public class ServerThread extends Thread
{
	ServerSocket ss;
	boolean flag=true;//ѭ�����Ʊ�־λ
    int ucount=0;//������� 0-û�� 1-1����� 2-�������
    ServerAgentThread[] userList=new ServerAgentThread[2];
    int[] scores=new int[2];//�����û��ĵ÷�
    int hitId=0;//0���û� 1-1���û� 2-2���û�
    int stopCount=0;//��ͣ������ 
    int inCount=0;//����������� 
    boolean inFlag=false;//�����־
    int overCount=0;//��������������
	
	public static void main(String args[])
	{
		new ServerThread().start();
	}
	
	public void initState()//�������س�ʼ״̬
	{
	    ucount=0;//������� 0-û�� 1-1����� 2-�������
	    userList=new ServerAgentThread[2];
	    scores=new int[2];//�����û��ĵ÷�
	    hitId=0;//0���û� 1-1���û� 2-2���û�
	    stopCount=0;//��ͣ������ 
	    inCount=0;//����������� 
	    inFlag=false;//�����־
	    overCount=0;//��������������
	}
	
	public ServerThread()
	{
		try
		{
			ss=new ServerSocket(9999);
			System.out.println("������9999�˿�.....");
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
			try
			{			    			
				Socket sc=ss.accept();
				
				//�ӵ�һ���û�����������
				System.out.println("�ӵ�һ���û����������� "+sc.getInetAddress().toString());
				ucount++;
				ServerAgentThread sat=new ServerAgentThread(this,sc,ucount);
				sat.start();
			}catch(Exception e)
			{
				e.printStackTrace();
			}
		}
	}
	

}