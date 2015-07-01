package wyf.jsc.crtb;
import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.event.*;
public class MapDesigner extends JFrame implements ActionListener{
	
	int row;
	int col;
	
	MapDesignPanel mdp;
	JScrollPane jsp;
	JButton jbGenerate=new JButton("���ɵ�ͼ");
	JButton jbGenerateB=new JButton("���ɰ�ťλ��");
	JButton jbGenerateS=new JButton("���ɿ�ʼλ��");
	JButton jbGenerateO=new JButton("���ɽ���λ��");
	JRadioButton jrBlack=new JRadioButton("��ɫ",null,true);
	JRadioButton jrWhite=new JRadioButton("��ɫ",null,false);
	JRadioButton jrButton=new JRadioButton("��ť",null,false);
	JRadioButton jrStart=new JRadioButton("���",null,false);
	JRadioButton jrOver=new JRadioButton("�յ�",null,false);
	ButtonGroup bg=new ButtonGroup();
	
	Image Start;
	Image Over;
	Image Red;
	JPanel jp=new JPanel();
	public MapDesigner(int row,int col)
	{
		this.row=row;
		this.col=col;
		this.setTitle("��ͼ�����");
		
		Start=new ImageIcon("img/start.jpg").getImage();
		Over=new ImageIcon("img/over.jpg").getImage();
		Red=new ImageIcon("img/red.png").getImage();
		
		mdp=new MapDesignPanel(row,col,this);
		jsp=new JScrollPane(mdp);
		this.add(jsp);
		
		jp.add(jbGenerate);jp.add(jbGenerateB);jp.add(jbGenerateS);jp.add(jbGenerateO);
		jp.add(jrBlack);bg.add(jrBlack);
		jp.add(jrWhite);bg.add(jrWhite);
		jp.add(jrButton);bg.add(jrButton);
		jp.add(jrStart);bg.add(jrStart);
		jp.add(jrOver);bg.add(jrOver);
		this.add(jp,BorderLayout.NORTH);
		this.setBounds(10,10,800,800);
		
		jbGenerate.addActionListener(this);
		jbGenerateB.addActionListener(this);
		jbGenerateS.addActionListener(this);
		jbGenerateO.addActionListener(this);
		this.setVisible(true);
		this.mdp.requestFocus(true);
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		 if(e.getSource()==this.jbGenerate)
		    {//���ɵ�ͼ����
		    	String s="public static final int[][] MAP=//0 ����ͨ�� 1��ͨ��\n{";
				for(int i=0;i<mdp.row;i++)
				{
					s=s+"\n\t{";
					for(int j=0;j<mdp.col;j++)
					{
						s=s+mdp.mapDate[i][j]+",";
					}
					s=s.substring(0,s.length()-1)+"},";
				}
				s=s.substring(0,s.length()-1)+"\n};";
				
				new CodeFrame(s,"�Թ���ͼ����");
		    }
		  else if(e.getSource()==this.jbGenerateB)
		    {//���ɰ�ť����
		    	String s="public static final int[][] MAP_OBJECT=//��ʾ��������λ�õľ���\n{";
				
				int ccount=0;
				
				for(int i=0;i<mdp.row;i++)
				{
					s=s+"\n\t{";
					for(int j=0;j<mdp.col;j++)
					{
						s=s+mdp.redButton[i][j]+",";
						if(mdp.redButton[i][j]==1)
						{
							ccount++;
						}
					}
					s=s.substring(0,s.length()-1)+"},";
				}
				s=s.substring(0,s.length()-1)+"\n};";
				s=s+"\npublic static final int OBJECT_COUNT="
				  +ccount+";//������ť������";
				
				
				new CodeFrame(s,"��ť�ֲ�ͼ����");
		    }
			else if(e.getSource()==this.jbGenerateS)
			{
				String s="public static final int START_COL="
				+this.mdp.StartCol+";//��ʼλ��\n"
				+"public static final int START_ROW="+this.mdp.StartRow+";";			
				new CodeFrame(s,"��ʼ��ʼλ�ô���");
			}
			else if(e.getSource()==this.jbGenerateO)
			{
				String s="public static final int OVER_COL="
				+this.mdp.OverCol+";//�յ�λ��\n"
				+"public static final int OVER_ROW="+this.mdp.OverRow+";";			
				new CodeFrame(s,"�յ��ʼλ�ô���");
			}
	}
	public static void main(String[]args)
	{
		new MapColRowDialog();
	}
}
