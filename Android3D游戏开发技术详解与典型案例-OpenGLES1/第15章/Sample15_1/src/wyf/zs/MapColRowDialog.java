package wyf.zs;

import java.awt.event.*;
import javax.swing.*;

public class MapColRowDialog extends JFrame
implements ActionListener
{
	JLabel jlRow=new JLabel("��ͼ����");
	JLabel jlCol=new JLabel("��ͼ����");
	JTextField jtfRow=new JTextField("20");
	JTextField jtfCol=new JTextField("20");
	
	JButton jbOk=new JButton("ȷ��");
	
	public MapColRowDialog()
	{
		this.setTitle("�򵥵ĵ�ͼ�����");
		
		this.setLayout(null);
		jlRow.setBounds(10,5,60,20);
		this.add(jlRow);
		jtfRow.setBounds(70,5,100,20);
		this.add(jtfRow);
		
		jlCol.setBounds(10,30,60,20);
		this.add(jlCol);
		jtfCol.setBounds(70,30,100,20);
		this.add(jtfCol);
		
		jbOk.setBounds(180,5,60,20);
		this.add(jbOk);
		jbOk.addActionListener(this);
		
		this.setBounds(440,320,300,100);
		this.setVisible(true);		
		
	}
	
	public void actionPerformed(ActionEvent e)
	{
		int row=Integer.parseInt(jtfRow.getText().trim());
		int col=Integer.parseInt(jtfCol.getText().trim());
		
		new MapDesigner(row,col);
		this.dispose();
	}
	
	public static void main(String args[])
	{
		new MapColRowDialog();
	}
}
