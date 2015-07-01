package wyf.sj;

import javax.microedition.khronos.opengles.GL10;

public class Bullet {
	Taper taper;//����Բ׶��
	Cylinder cylinder;//����Բ����
	
	int taperId;//Բ׶������ID
	int cylinderId;//Բ��������
	public Bullet(int taperId,int cylinderId)
	{
		this.taperId=taperId;
		this.cylinderId=cylinderId;
		
		taper=new Taper(0.5f,0.2f,9f,10,taperId);//����Բ׶��
		cylinder=new Cylinder(0.5f,0.2f,18f,10,cylinderId);//����Բ����
	}

	public void drawSelf(GL10 gl)
	{
		gl.glPushMatrix();		
		gl.glTranslatef(0.2f, 0, 0);
		gl.glRotatef(-90, 0, 0, 1);
		taper.drawSelf(gl);//����Բ׶��
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		cylinder.drawSelf(gl);//����Բ����
		gl.glPopMatrix();
	}
}
