package wyf.jsl.lb;

import javax.microedition.khronos.opengles.GL10;

public class PackageLandTankWheel
{
	//��Ա����
	private DrawCube cube;
	private DrawCylinder cylinder;
	private DrawCircle circle;
	
	float cubelength;//��С
	float cubewidth;
	float cubeheight;
	int cubeTexture;//����
	int cylinderTexture;
	int circleTexture;
		
	//������
	public PackageLandTankWheel(
			float cubelength,
			float cubewidth,
			float cubeheight,
			int cubeTexture,
			int cylinderTexture,
			int circleTexture
			)
	{	
		this.cubelength=cubelength;
		this.cubewidth=cubewidth;
		this.cubeheight=cubeheight;
		this.cubeTexture=cubeTexture;
		this.cylinderTexture=cylinderTexture;
		this.circleTexture=circleTexture;
		
		cube=new DrawCube(cubelength,cubewidth,cubeheight,cubeTexture);
		cylinder=new DrawCylinder(cubelength,0.5f*cubeheight,18f,5,cylinderTexture);
		circle=new DrawCircle(0.5f*cubeheight,18f,circleTexture);
	}

	public void drawSelf(GL10 gl)//�������������Ϊ����ԭ�㣬����Ϊ����ˮƽ���á�
	{	
		gl.glPushMatrix();
		cube.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(-0.5f*this.cubewidth, 0, 0);
		gl.glRotatef(90, 0, 1, 0);
		cylinder.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(0.5f*this.cubewidth, 0, 0);
		gl.glRotatef(90, 0, 1, 0);
		cylinder.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(-0.5f*this.cubewidth, 0, -0.5f*cubelength);
		circle.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(-0.5f*this.cubewidth, 0, 0.5f*cubelength);
		circle.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(0.5f*this.cubewidth, 0, -0.5f*cubelength);
		circle.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(0.5f*this.cubewidth, 0, 0.5f*cubelength);
		circle.drawSelf(gl);
		gl.glPopMatrix();
	}
}