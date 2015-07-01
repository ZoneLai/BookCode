package wyf.jsl.lb;

import static wyf.jsl.lb.Constant.*;
import javax.microedition.khronos.opengles.GL10;

public class PackageLighthouse
{
	DrawLightCylinder pedestal;	//��������
	DrawLightCylinder body;		//��������
	DrawLightCylinder flatform;	//�����t��̨
	DrawTaper overhead;		//������
	DrawTaper upswell1;		//�t��̨͹�𲿷� 
	DrawTaper upswell2;		//����͹�𲿷�
	
	public float mAngleX;	//��ת
	public float mAngleY;
	public float mAngleZ;
	
	public PackageLighthouse()
	{
		pedestal=new DrawLightCylinder(PEDESTAL_LENGHT,PEDESTAL_R,18,10);
		body=new DrawLightCylinder(BODY_LENGHT,BODY_R,18,10);
		flatform=new DrawLightCylinder(FLOTFORM_LENGHT,FLOTFORM_R,18,10);
		overhead=new DrawTaper(OVERHEAD_HEIGHT,OVERHEAD_R,18,10);
		upswell1=new DrawTaper(UPSWELL_HEIGHT,UPSWELL_R,18,10);
		upswell2=new DrawTaper(UPSWELL_HEIGHT,PEDESTAL_R,18,10);
	}
	
	public void onDraw(GL10 gl)
	{
		gl.glRotatef(mAngleX, 1, 0, 0);//��ת
		gl.glRotatef(mAngleY, 0, 1, 0);
		gl.glRotatef(mAngleZ, 0, 0, 1);
		
		gl.glPushMatrix();//���Ƶ�������
		initMaterial2(gl);							//��ʼ������
		gl.glTranslatef(0, pedestal.length*0.5f, 0);
		gl.glRotatef(90, 0, 0, 1);
		pedestal.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���Ƶ��������ϲ�͹��
		initMaterial2(gl);							//��ʼ������
		gl.glTranslatef(0, pedestal.length, 0);
		upswell2.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���Ƶ�������
		initMaterial2(gl);							//��ʼ������
		gl.glTranslatef(0, pedestal.length+body.length*0.5f, 0);
		gl.glRotatef(90, 0, 0, 1);
		body.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���Ƶ����t��̨
		initMaterial3(gl);							//��ʼ������
		gl.glTranslatef(0, pedestal.length+body.length*FLOTFORM_SCALE, 0);
		gl.glRotatef(90, 0, 0, 1);
		flatform.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���Ƶ�����
		initMaterial1(gl);							//��ʼ������
		gl.glTranslatef(0, pedestal.length+body.length, 0);
		overhead.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���Ƶ����t��̨�ϲ�͹��
		initMaterial1(gl);							//��ʼ������
		gl.glTranslatef(0, pedestal.length+body.length*FLOTFORM_SCALE+flatform.length*0.5f, 0);
		upswell1.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���Ƶ����t��̨�²�͹��
		initMaterial1(gl);							//��ʼ������
		gl.glTranslatef(0, pedestal.length+body.length*FLOTFORM_SCALE-flatform.length*0.5f, 0);
		gl.glRotatef(180, 0, 0, 1);
		upswell1.drawSelf(gl);
		gl.glPopMatrix();
	}
	
	//��ʼ����ɫ����
	private void initMaterial1(GL10 gl)
	{
        //������Ϊ
        float ambientMaterial[] = {144f/255f, 80f/255f, 42f/255f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_AMBIENT, ambientMaterial,0);
        //ɢ���
        float diffuseMaterial[] = {144f/255f, 80f/255f, 42f/255f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_DIFFUSE, diffuseMaterial,0);
        //�߹����
        float specularMaterial[] = {144f/255f, 80f/255f, 42f/255f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_SPECULAR, specularMaterial,0);
        gl.glMaterialf(GL10.GL_FRONT_AND_BACK, GL10.GL_SHININESS, 100.0f);
	}
	 
	//��ʼ����ɫ����
	private void initMaterial2(GL10 gl)
	{
        //������
        float ambientMaterial[] = {196f/255f, 205f/255f, 204f/255f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_AMBIENT, ambientMaterial,0);
        //ɢ���
        float diffuseMaterial[] = {196f/255f, 205f/255f, 204f/255f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_DIFFUSE, diffuseMaterial,0);
        //�߹����
        float specularMaterial[] = {196f/255f, 205f/255f, 204f/255f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_SPECULAR, specularMaterial,0);
        gl.glMaterialf(GL10.GL_FRONT_AND_BACK, GL10.GL_SHININESS, 100.0f);
	}
	
	//��ʼ����ɫ����
	private void initMaterial3(GL10 gl)
	{
        //������
        float ambientMaterial[] = {248f/255f, 242f/255f, 144f/255f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_AMBIENT, ambientMaterial,0);
        //ɢ���
        float diffuseMaterial[] = {248f/255f, 242f/255f, 144f/255f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_DIFFUSE, diffuseMaterial,0);
        //�߹����
        float specularMaterial[] = {248f/255f, 242f/255f, 144f/255f, 1.0f};
        gl.glMaterialfv(GL10.GL_FRONT_AND_BACK, GL10.GL_SPECULAR, specularMaterial,0);
        gl.glMaterialf(GL10.GL_FRONT_AND_BACK, GL10.GL_SHININESS, 100.0f);
	}
}