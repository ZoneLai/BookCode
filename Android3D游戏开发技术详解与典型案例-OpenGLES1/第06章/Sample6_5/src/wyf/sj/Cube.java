package wyf.sj;

import javax.microedition.khronos.opengles.GL10;
import static wyf.sj.Constant.*;


public class Cube {
	//���ڻ��Ƹ��������ɫ����
	ColorRect cr=new ColorRect(SCALE,SCALE);
	
	public void drawSelf(GL10 gl)
	{
		//�ܻ���˼�룺ͨ����һ����ɫ������ת��λ��������ÿ�����λ��
		//�����������ÿ����
		
		gl.glPushMatrix();
		
		//����ǰС��
		gl.glPushMatrix();
		gl.glTranslatef(0, 0, UNIT_SIZE*SCALE);
		cr.drawSelf(gl);		
		gl.glPopMatrix();
		
		//���ƺ�С��
		gl.glPushMatrix();		
		gl.glTranslatef(0, 0, -UNIT_SIZE*SCALE);
		gl.glRotatef(180, 0, 1, 0);
		cr.drawSelf(gl);		
		gl.glPopMatrix();
		
		//�����ϴ���
		gl.glPushMatrix();			
		gl.glTranslatef(0,UNIT_SIZE*SCALE,0);
		gl.glRotatef(-90, 1, 0, 0);
		cr.drawSelf(gl);
		gl.glPopMatrix();
		
		//�����´���
		gl.glPushMatrix();			
		gl.glTranslatef(0,-UNIT_SIZE*SCALE,0);
		gl.glRotatef(90, 1, 0, 0);
		cr.drawSelf(gl);
		gl.glPopMatrix();
		
		//���������
		gl.glPushMatrix();			
		gl.glTranslatef(UNIT_SIZE*SCALE,0,0);		
		gl.glRotatef(-90, 1, 0, 0);
		gl.glRotatef(90, 0, 1, 0);
		cr.drawSelf(gl);
		gl.glPopMatrix();
		
		//�����Ҵ���
		gl.glPushMatrix();			
		gl.glTranslatef(-UNIT_SIZE*SCALE,0,0);		
		gl.glRotatef(90, 1, 0, 0);
		gl.glRotatef(-90, 0, 1, 0);
		cr.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPopMatrix();
	}
	

}
