package wyf.zs;

import javax.microedition.khronos.opengles.GL10;
import static wyf.zs.Constant.*;

//��ʾ������ľ�����
public class Cube 
{
	TextureRect trSmall;//С���������
	TextureRect trBig;//�����������
	float scale;//�ߴ�����ϵ��
	float unitLocalSize;//ʵ�ʵ�λ�ߴ硪��С��İ�߳�
    float xOffset=0;//xλ��
    float zOffset=0;//Zλ��
	
	public Cube(float scale,int cubeSmallTexId,int cubeBigTexId)
	{
		this.scale=scale;		
		//������С��������ζ���
		trSmall=new TextureRect(scale,scale,cubeSmallTexId);
		trBig=new TextureRect(scale,2*scale,cubeBigTexId);
		//С��İ�߳�
		unitLocalSize=UNIT_SIZE*scale;
	}
	
	public void drawSelf(GL10 gl)
	{
		gl.glPushMatrix();
		//�ƶ���ָ����XZλ�û���Cube
		gl.glTranslatef(xOffset, 0, zOffset);
		
		//����ǰС��
		gl.glPushMatrix();
		gl.glTranslatef(0, 0, 2*UNIT_SIZE*scale);
		trSmall.drawSelf(gl);		
		gl.glPopMatrix();
		
		//���ƺ�С��
		gl.glPushMatrix();		
		gl.glTranslatef(0, 0, -2*UNIT_SIZE*scale);
		gl.glRotatef(180, 0, 1, 0);
		trSmall.drawSelf(gl);		
		gl.glPopMatrix();
		
		//�����ϴ���
		gl.glPushMatrix();			
		gl.glTranslatef(0,UNIT_SIZE*scale,0);
		gl.glRotatef(-90, 1, 0, 0);
		trBig.drawSelf(gl);
		gl.glPopMatrix();
		
		//�����´���
		gl.glPushMatrix();			
		gl.glTranslatef(0,-UNIT_SIZE*scale,0);
		gl.glRotatef(90, 1, 0, 0);
		trBig.drawSelf(gl);
		gl.glPopMatrix();
		
		//���������
		gl.glPushMatrix();			
		gl.glTranslatef(UNIT_SIZE*scale,0,0);		
		gl.glRotatef(-90, 1, 0, 0);
		gl.glRotatef(90, 0, 1, 0);
		trBig.drawSelf(gl);
		gl.glPopMatrix();
		
		//�����Ҵ���
		gl.glPushMatrix();			
		gl.glTranslatef(-UNIT_SIZE*scale,0,0);		
		gl.glRotatef(90, 1, 0, 0);
		gl.glRotatef(-90, 0, 1, 0);
		trBig.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPopMatrix();
	}
}
