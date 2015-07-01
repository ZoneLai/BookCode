package wyf.jsl.lb;

import javax.microedition.khronos.opengles.GL10;
import static wyf.jsl.lb.Constant.*;
//��ʾ����̹����������
public class Score 
{
	GLGameView mv;
	DrawPanel[] numbers=new DrawPanel[10];
	
	public Score(int texId,GLGameView mv)
	{
		this.mv=mv;
		
		//����0-9ʮ�����ֵ��������
		for(int i=0;i<10;i++)
		{
			numbers[i]=new DrawPanel
            (
            	SCORE_NUMBER_SPAN_X,
            	SCORE_NUMBER_SPAN_Y,
            	 texId,
            	 new float[]
		             {
		           	  0.1f*i,0, 0.1f*i,1, 0.1f*(i+1),0,
		           	  0.1f*(i+1),0, 0.1f*i,1,  0.1f*(i+1),1
		             }
             ); 
		}
	}
	
	public void drawSelf(GL10 gl)
	{		
		String scoreStr=Count+"";
		for(int i=0;i<scoreStr.length();i++)
		{//���÷��е�ÿ�������ַ�����
			char c=scoreStr.charAt(i);
			gl.glPushMatrix();
			gl.glTranslatef(i*SCORE_NUMBER_SPAN_X, 0, 0);
			numbers[c-'0'].drawSelf(gl);
			gl.glPopMatrix();
		}
	}
}