package wyf.jsc.tdb;
import javax.microedition.khronos.opengles.GL10;
import static wyf.jsc.tdb.Constant.*;
public class Score {

	MySurfaceView mv;
	TextureRect[] numbers=new TextureRect[10];
	
	public Score(int texId,MySurfaceView mv)
	{
		this.mv=mv;
		
		//����0-9ʮ�����ֵ��������
		for(int i=0;i<10;i++)
		{
			numbers[i]=new TextureRect
            (
            		
            		0.6f,0.6f,0,
            		texId,
           		 new float[]//�趨��������
		             {
		           	  0.1f*i,0, 0.1f*i,1, 0.1f*(i+1),1,
		           	  0.1f*(i+1),1, 0.1f*(i+1),0,  0.1f*i,0
		             }
             ); 
		}
	}
	
	public void drawSelf(GL10 gl)//��ϰģʽ
	{		
		String scoreStr=score+"";
		for(int i=0;i<scoreStr.length();i++)
		{//���÷��е�ÿ�������ַ�����
			char c=scoreStr.charAt(i);
			gl.glPushMatrix();
			gl.glTranslatef(i*ICON_WIDTH*0.7f, 0, 0);
			numbers[c-'0'].drawSelf(gl);
			gl.glPopMatrix();
		}
	}
	public void drawSelfNet(GL10 gl,int temp)//��սģʽ
	{
		switch(temp)
		{
		case 1://1����ҵ÷�
				String scoreOneStr=scoreOne+"";
				for(int i=0;i<scoreOneStr.length();i++)
				{
					char c=scoreOneStr.charAt(i);
					gl.glPushMatrix();
					gl.glTranslatef(i*ICON_WIDTH*0.7f, 0, 0);
					numbers[c-'0'].drawSelf(gl);
					gl.glPopMatrix();
				}
			break;
		case 2://2����ҵ÷�
				String scoreTwoStr=scoreTwo+"";
				for(int i=0;i<scoreTwoStr.length();i++)
				{
					char c=scoreTwoStr.charAt(i);
					gl.glPushMatrix();
					gl.glTranslatef(i*ICON_WIDTH*0.7f, 0, 0);
					numbers[c-'0'].drawSelf(gl);
					gl.glPopMatrix();
				}	
			break;
		}
		
	}
}
