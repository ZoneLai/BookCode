package wyf.zs;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MapDesigner extends JFrame
implements ActionListener
{
	int row;
	int col;
	
	MapDesignPanel mdp;
	JScrollPane jsp;
	JButton jbGenerate=new JButton("���ɵ�ͼ");
	JButton jbGenerateD=new JButton("���ɾ���λ��");
	JButton jbGenerateC=new JButton("���������λ��");
	JRadioButton jrBlack=new JRadioButton("��ɫ",null,true);
	JRadioButton jrWhite=new JRadioButton("��ɫ",null,false);
	JRadioButton jrCrystal=new JRadioButton("����",null,false);
	JRadioButton jrCamera=new JRadioButton("�����",null,false);
	ButtonGroup bg=new ButtonGroup();
	
	Image icrystal;
	Image iCamera;
	
	JPanel jp=new JPanel();
	
	public MapDesigner(int row,int col)
	{
		this.row=row;
		this.col=col;		
		this.setTitle("�򵥵ĵ�ͼ�����");
		
		icrystal=new ImageIcon("img/Diamond.png").getImage();
		iCamera=new ImageIcon("img/camera.png").getImage();
		
		
		mdp=new MapDesignPanel(row,col,this);
		jsp=new JScrollPane(mdp);
		
		this.add(jsp);
		
		jp.add(jbGenerate);jp.add(jbGenerateD);jp.add(jbGenerateC);
		jp.add(jrBlack);bg.add(jrBlack);
		jp.add(jrWhite);bg.add(jrWhite);
		jp.add(jrCrystal);bg.add(jrCrystal);
		jp.add(jrCamera);bg.add(jrCamera);		
		this.add(jp,BorderLayout.NORTH);
		jbGenerate.addActionListener(this);
		jbGenerateD.addActionListener(this);
		jbGenerateC.addActionListener(this);
		
		this.setBounds(10,10,800,600);
		this.setVisible(true);
		this.mdp.requestFocus(true);	
	}
	
	public void actionPerformed(ActionEvent e)
	{		
	    if(e.getSource()==this.jbGenerate)
	    {//���ɵ�ͼ����
	    	String s="public static final int[][] MAP=//0 ����ͨ�� 1��ͨ��\n{";
			for(int i=0;i<mdp.row;i++)
			{
				s=s+"\n\t{";
				for(int j=0;j<mdp.col;j++)
				{
					s=s+mdp.mapData[i][j]+",";
				}
				s=s.substring(0,s.length()-1)+"},";
			}
			s=s.substring(0,s.length()-1)+"\n};";
			
			new CodeFrame(s,"�Թ���ͼ����");			
	    }
	    else if(e.getSource()==this.jbGenerateD)
	    {//���ɾ������
	    	String s="public static final int[][] MAP_OBJECT=//��ʾ��������λ�õľ���\n{";
			
			int ccount=0;
			
			for(int i=0;i<mdp.row;i++)
			{
				s=s+"\n\t{";
				for(int j=0;j<mdp.col;j++)
				{
					s=s+mdp.diamondMap[i][j]+",";
					if(mdp.diamondMap[i][j]==1)
					{
						ccount++;
					}
				}
				s=s.substring(0,s.length()-1)+"},";
			}
			s=s.substring(0,s.length()-1)+"\n};";
			s=s+"\npublic static final int OBJECT_COUNT="
			  +ccount+";//�������������";
			
			
			new CodeFrame(s,"����ֲ�ͼ����");
	    }
		else if(e.getSource()==this.jbGenerateC)
		{//���������λ��
			String s="public static final int CAMERA_COL="
			+this.mdp.cameraCol+";//��ʼʱCameraλ��\n"
			+"public static final int CAMERA_ROW="+this.mdp.cameraRow+";";			
			new CodeFrame(s,"�������ʼλ�ô���");
		}
	}
	
	public static void main(String args[])
	{
		new MapColRowDialog();
	}
}
