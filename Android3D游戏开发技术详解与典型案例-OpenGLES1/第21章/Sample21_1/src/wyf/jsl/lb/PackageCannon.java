package wyf.jsl.lb;

import javax.microedition.khronos.opengles.GL10;

import static wyf.jsl.lb.Constant.*;

public class PackageCannon {
	GLGameView mv;
	
	DrawCylinder wbody;//�����ⲿ
	DrawCylinder nbody;//�����ڲ�
	
	DrawCircle wcover;//�����ⲿ���
	DrawCircle ncover;//�����ڲ����
	
	DrawCylinder gun;//�ڹ�����
	DrawCylinder gunHead;//�ڹ���ͷ
	DrawCircle gunHeadCover;//�ڹ���ͷ���

	DrawCylinder widget;//װ��
	DrawCircle widgetCover;//װ�θ�

	DrawTextureRect tr;//׼��
	
	float angleElevation=0;//�ڹܳ�ʼ����
	float angleDirection=0;//�ڹܳ�ʼ��λ��
	
	public PackageCannon(int cylinderTexId,int circleTexId,GLGameView mv)
	{
		this.mv=mv;
		
		wbody=new DrawCylinder(W_CYLINDER_L,W_CYLINDER_R,45.0f,5,cylinderTexId);//�����ⲿ��8����
		wcover=new DrawCircle(W_CYLINDER_R,45.0f,circleTexId);//�����ⲿ��ڣ�8����
		
		nbody=new DrawCylinder(N_CYLINDER_L,N_CYLINDER_R,45.0f,5,cylinderTexId);//�����ڲ���8����
		ncover=new DrawCircle(N_CYLINDER_R,45.0f,circleTexId);//�����ڲ���ڣ�8����
		
		gun=new DrawCylinder(GUN_CYLINDER_L,GUN_CYLINDER_R,18.0f,10,cylinderTexId);//�ڹ�����Բ��
		gunHead=new DrawCylinder(GUN_HEAD_CYLINDER_L,GUN_HEAD_CYLINDER_R,45.0f,5,cylinderTexId);//�ڹ���ͷ��8����
		gunHeadCover=new DrawCircle(GUN_HEAD_CYLINDER_R,45.0f,circleTexId);//�ڹ���ͷ��ڣ�8����
		
		widget=new DrawCylinder(WIDGET_L,WIDGET_R,18.0f,5,cylinderTexId);//װ��
		widgetCover=new DrawCircle(WIDGET_R,18.0f,circleTexId);
		
		tr=new DrawTextureRect(mv.mRenderer.zhunxingTextureId,CIRCLE_R*3f,CIRCLE_R*3f);//׼��
	} 
	public void drawSelf(GL10 gl)
	{
		gl.glPushMatrix();
		gl.glRotatef(angleDirection, 0, 1, 0);//����̨���շ�λ����ת
		
		gl.glPushMatrix();
		gl.glRotatef(angleElevation, 1, 0, 0);
		gl.glRotatef(90, 0, 1, 0);
		
		//����������
		gl.glPushMatrix();
		gl.glTranslatef(wbody.length*0.5f, wbody.circle_radius, 0);
		wbody.drawSelf(gl);
		gl.glPopMatrix();
		
		//�����������
		gl.glPushMatrix();
		gl.glTranslatef(0, wbody.circle_radius, 0);
		gl.glRotatef(90, 0, 1, 0);
		wcover.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(wbody.length, wbody.circle_radius, 0);
		gl.glRotatef(-90, 0, 1, 0);
		wcover.drawSelf(gl);
		gl.glPopMatrix();
		
		//����������
		gl.glPushMatrix();
		gl.glTranslatef(nbody.length*0.4f, wbody.circle_radius, 0);
		nbody.drawSelf(gl);
		gl.glPopMatrix();
		
		//�����������
		gl.glPushMatrix();
		gl.glTranslatef(-nbody.length*0.1f, wbody.circle_radius, 0);
		gl.glRotatef(90, 0, 1, 0);
		ncover.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(nbody.length*0.9f, wbody.circle_radius, 0);
		gl.glRotatef(-90, 0, 1, 0);
		ncover.drawSelf(gl);
		gl.glPopMatrix();
		
		//�����ڹ�
		gl.glPushMatrix();
		gl.glTranslatef(gun.length*0.5f, wbody.circle_radius, 0);
		gun.drawSelf(gl);
		gl.glPopMatrix();
		
		//�����ڹ�ͷ
		gl.glPushMatrix();
		gl.glTranslatef(gun.length*0.95f, wbody.circle_radius, 0);
		gunHead.drawSelf(gl);
		gl.glPopMatrix();
		
		//�����ڹܸ�
		gl.glPushMatrix();
		gl.glTranslatef(gun.length*0.95f-gunHead.length*0.5f, wbody.circle_radius, 0);
		gl.glRotatef(90, 0, 1, 0);
		gunHeadCover.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(gun.length*0.95f+gunHead.length*0.5f, wbody.circle_radius, 0);
		gl.glRotatef(-90, 0, 1, 0);
		gunHeadCover.drawSelf(gl);
		gl.glPopMatrix();
		 
		//����   
		gl.glPushMatrix();//����
		gl.glTranslatef(widget.length*0.5f, wbody.circle_radius, 0);
		gl.glTranslatef(0, (float)((wbody.circle_radius+widget.circle_radius)*Math.sin(Math.toRadians(45))), (float)((wbody.circle_radius+widget.circle_radius)*Math.cos(Math.toRadians(45))));
		widget.drawSelf(gl);
		gl.glPopMatrix(); 
		
		gl.glPushMatrix();  
		gl.glTranslatef(0, wbody.circle_radius, 0); 
		gl.glTranslatef(0, (float)((wbody.circle_radius+widget.circle_radius)*Math.sin(Math.toRadians(45))), (float)((wbody.circle_radius+widget.circle_radius)*Math.cos(Math.toRadians(45))));
		gl.glRotatef(90, 0, 1, 0);
		widgetCover.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix(); 
		gl.glTranslatef(widget.length, wbody.circle_radius, 0);
		gl.glTranslatef(0, (float)((wbody.circle_radius+widget.circle_radius)*Math.sin(Math.toRadians(45))), (float)((wbody.circle_radius+widget.circle_radius)*Math.cos(Math.toRadians(45))));
		gl.glRotatef(-90, 0, 1, 0);
		widgetCover.drawSelf(gl);
		gl.glPopMatrix(); 
		 	 
		gl.glPushMatrix();//����
		gl.glTranslatef(widget.length*0.5f, wbody.circle_radius, 0);
		gl.glTranslatef(0, (float)((wbody.circle_radius+widget.circle_radius)*Math.sin(Math.toRadians(135))), (float)((wbody.circle_radius+widget.circle_radius)*Math.cos(Math.toRadians(135))));
		widget.drawSelf(gl);
		gl.glPopMatrix();
		 
		gl.glPushMatrix(); 
		gl.glTranslatef(0, wbody.circle_radius, 0); 
		gl.glTranslatef(0, (float)((wbody.circle_radius+widget.circle_radius)*Math.sin(Math.toRadians(135))), (float)((wbody.circle_radius+widget.circle_radius)*Math.cos(Math.toRadians(135))));
		gl.glRotatef(90, 0, 1, 0);
		widgetCover.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(widget.length, wbody.circle_radius, 0);
		gl.glTranslatef(0, (float)((wbody.circle_radius+widget.circle_radius)*Math.sin(Math.toRadians(135))), (float)((wbody.circle_radius+widget.circle_radius)*Math.cos(Math.toRadians(135))));
		gl.glRotatef(-90, 0, 1, 0);
		widgetCover.drawSelf(gl);
		gl.glPopMatrix(); 
		
		//׼�� 
		gl.glPushMatrix();
		gl.glTranslatef(ZHUNXING_LENGTH, wbody.circle_radius, 0);
		gl.glRotatef(-90, 0, 1, 0);
		gl.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
		gl.glEnable(GL10.GL_BLEND);		
		tr.drawSelf(gl);
		gl.glDisable(GL10.GL_BLEND); 
		gl.glPopMatrix();
		
		gl.glPopMatrix();
		
		gl.glPopMatrix();
	}
	

	//�����ڵ��ķ���
	public void fire()
	{
		//�����ڹܷ�λ�������Ǽ����ڵ�����λ��
		float by=FORT_Y+gun.circle_radius+gun.length*(float)Math.sin(Math.toRadians(angleElevation));//�ڵ�Yλ��
		float tempR=gun.length*(float)Math.cos(Math.toRadians(angleElevation));
		float bx=FORT_X-tempR*(float)Math.sin(Math.toRadians(angleDirection));//�ڵ�Xλ��
		float bz=FORT_Z-tempR*(float)Math.cos(Math.toRadians(angleDirection));//�ڵ�Zλ��		
		//�����ڹܷ�λ�������Ǽ����ڵ������ٶ�
		float vy=BULLET_V*(float)Math.sin(Math.toRadians(angleElevation));
		float tempVxz=BULLET_V*(float)Math.cos(Math.toRadians(angleElevation));
		float vx=-tempVxz*(float)Math.sin(Math.toRadians(angleDirection));
		float vz=-tempVxz*(float)Math.cos(Math.toRadians(angleDirection));		
		//���ŷ����ڵ�����Ч
		if(SOUND_FLAG)
		{
			mv.father.playSound(1,0);
		}
		//�����µ��ڵ��������ڵ��б�
		mv.bulletList.add
		(
				new LogicalBullet(mv.mRenderer.btbv,bx,by,bz,vx,vy,vz,mv)
		);
	}
}
