package wyf.jsc.crtb;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
public class MapColRowDialog extends JFrame implements  ActionListener{
	
	JLabel jlRow=new JLabel("��ͼ������");
	JLabel jlCol=new JLabel("��ͼ������");
	JTextField jtfRow=new JTextField("20");
	JTextField jtfCol=new JTextField("20");
	JButton jbOk=new JButton("ȷ��");
	
	public MapColRowDialog ()
	{
		
		this.setTitle("��ͼ�����");
		this.setBounds(100,200,300,100);
		this.setLayout(null);
		this.add(jlRow);
		this.add(jlCol);
		this.add(jtfRow);
		this.add(jtfCol);
		jlRow.setBounds(10,5,80,20);
		jtfRow.setBounds(90,5,100,20);
		jlCol.setBounds(10,30,80,20);
		jtfCol.setBounds(90,30,100,20);
		this.add(jbOk);
		jbOk.setBounds(210,5,60,20);
		jbOk.addActionListener(this);
		this.setVisible(true);
	}
	public void actionPerformed(ActionEvent e)
	{
		int row=Integer.parseInt(jtfRow.getText().trim());
		int col=Integer.parseInt(jtfCol.getText().trim());
		new MapDesigner(row,col);
		this.dispose();
	}
	public static void main(String[]args)
	{
		new MapColRowDialog ();
	}
}
