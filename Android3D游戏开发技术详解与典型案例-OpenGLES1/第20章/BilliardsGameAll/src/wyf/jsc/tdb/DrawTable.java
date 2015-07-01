package wyf.jsc.tdb;

import static wyf.jsc.tdb.Constant.*;

import javax.microedition.khronos.opengles.GL10;

public class DrawTable {

	TableBottom tableBottom;//���ӵ�
	TextureRect tableRect;//����
	TableBottom tableRoundUD;//�������±�Ե
	TableBottom tableRoundLR;//�������ұ�Ե
	Circle circle;//��
	
	TextureRect tableRoundRect;//���ӽǵ���

	public DrawTable(int tableBottomId,int tableRectId,int tableRoundUDId,int tableRoundLRId,int circleId,int baffleId)
	{
		tableBottom=new TableBottom(tableBottomId,BOTTOM_HIGHT,BOTTOM_LENGTH,BOTTOM_WIDE);//��������
		tableRoundUD=new TableBottom(tableRoundUDId,UP_DOWN_HIGHT,UP_DOWN_LENGTH,EDGE_BIG);//�����������£�ǰ�󣩱�Ե
		tableRoundLR=new TableBottom(tableRoundLRId,UP_DOWN_HIGHT,EDGE_BIG,LEFT_RIGHT_LENGTH);//�����������ұ�Ե
		circle=new Circle(CIRCLE_R,CIRCLE_R,circleId);//������
		
		tableRect=new TextureRect//��������
		(
				TABLE_AREA_LENGTH,0,TABLE_AREA_WIDTH,tableRectId,
				new float[] 
		        {
		        	0,0,0,1,1,1,
		        	1,1,1,0,0,0
		        }
		);
		
		tableRoundRect=new TextureRect//���ӽǵ���
		(
				EDGE,UP_DOWN_HIGHT,0,baffleId,
				new float[]
		          {
						0,0,0,1,1,1,
						1,1,1,0,0,0
		          }
		);
		
	}
	
	public void drawSelf(GL10 gl)
	{
		//l.glTranslatef(0, 0, -10);
		gl.glPushMatrix();
		gl.glTranslatef(0, BOTTOM_Y, 0);
		tableBottom.drawSelf(gl);//����������
		gl.glPopMatrix();
		
		gl.glPushMatrix();
		gl.glTranslatef(0, TEXTURE_RECT_Y, 0);
		tableRect.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//�������±�Ե������
		gl.glTranslatef(UP_DOWN_LENGTH/2+MIDDLE/2, TEXTURE_RECT_Y, -BOTTOM_WIDE/2+EDGE_BIG/2);
		tableRoundUD.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//�������±�Ե������
		gl.glTranslatef(-UP_DOWN_LENGTH/2-MIDDLE/2, TEXTURE_RECT_Y, -BOTTOM_WIDE/2+EDGE_BIG/2);
		tableRoundUD.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���ӵ����±�Ե������
		gl.glTranslatef(UP_DOWN_LENGTH/2+MIDDLE/2, TEXTURE_RECT_Y, BOTTOM_WIDE/2-EDGE_BIG/2);
		gl.glRotatef(180, 0, 1, 0);
		tableRoundUD.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//�������±�Ե������
		gl.glTranslatef(-UP_DOWN_LENGTH/2-MIDDLE/2, TEXTURE_RECT_Y, BOTTOM_WIDE/2-EDGE_BIG/2);
		gl.glRotatef(180, 0, 1, 0);
		tableRoundUD.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//�������Ե
		gl.glTranslatef(-BOTTOM_LENGTH/2+EDGE_BIG/2, TEXTURE_RECT_Y, 0);
		//gl.glRotatef(90, 0, 1, 0);
		tableRoundLR.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//�����ұ�Ե
		gl.glTranslatef(BOTTOM_LENGTH/2-EDGE_BIG/2, TEXTURE_RECT_Y, 0);
		gl.glRotatef(180, 0, 1, 0);
		tableRoundLR.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���¶�
		gl.glTranslatef(0, TEXTURE_RECT_Y+DELTA, BOTTOM_WIDE/2-CIRCLE_R/2);
		circle.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���϶�
		gl.glTranslatef(0, TEXTURE_RECT_Y+DELTA, -BOTTOM_WIDE/2+CIRCLE_R/2);
		circle.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//�Ҳ��¶�
		gl.glTranslatef(TABLE_AREA_LENGTH/2+CIRCLE_R/2, TEXTURE_RECT_Y+DELTA, TABLE_AREA_WIDTH/2+CIRCLE_R/2);
		circle.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//�Ҳ��϶�
		gl.glTranslatef(TABLE_AREA_LENGTH/2+CIRCLE_R/2, TEXTURE_RECT_Y+DELTA, -TABLE_AREA_WIDTH/2-CIRCLE_R/2);
		circle.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//����¶�
		gl.glTranslatef(-TABLE_AREA_LENGTH/2-CIRCLE_R/2, TEXTURE_RECT_Y+DELTA, TABLE_AREA_WIDTH/2+CIRCLE_R/2);
		circle.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//����϶�
		gl.glTranslatef(-TABLE_AREA_LENGTH/2-CIRCLE_R/2, TEXTURE_RECT_Y+DELTA, -TABLE_AREA_WIDTH/2-CIRCLE_R/2);
		circle.drawSelf(gl);
		gl.glPopMatrix();
		
		
	
		gl.glPushMatrix();//����D����
		gl.glTranslatef(BOTTOM_LENGTH/2-EDGE/2, TEXTURE_RECT_Y, -BOTTOM_WIDE/2);
		tableRoundRect.drawSelf(gl);
		gl.glRotatef(180, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//����E����
		gl.glTranslatef(BOTTOM_LENGTH/2, TEXTURE_RECT_Y, -BOTTOM_WIDE/2+EDGE/2);
		gl.glRotatef(90, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glRotatef(180, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//����F����
		gl.glTranslatef(BOTTOM_LENGTH/2, TEXTURE_RECT_Y, BOTTOM_WIDE/2-EDGE/2);
		gl.glRotatef(90, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glRotatef(180, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//����G����
		gl.glTranslatef(BOTTOM_LENGTH/2-EDGE/2, TEXTURE_RECT_Y, BOTTOM_WIDE/2);
		tableRoundRect.drawSelf(gl);
		gl.glRotatef(180, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���µ���
		gl.glTranslatef(0, TEXTURE_RECT_Y, BOTTOM_WIDE/2);
		tableRoundRect.drawSelf(gl);
		gl.glRotatef(180, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//����J����
		gl.glTranslatef(-BOTTOM_LENGTH/2+EDGE/2, TEXTURE_RECT_Y, BOTTOM_WIDE/2);
		tableRoundRect.drawSelf(gl);
		gl.glRotatef(180, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//����K����
		gl.glTranslatef(-BOTTOM_LENGTH/2, TEXTURE_RECT_Y, BOTTOM_WIDE/2-EDGE/2);
		gl.glRotatef(90, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glRotatef(180, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//����L����
		gl.glTranslatef(-BOTTOM_LENGTH/2, TEXTURE_RECT_Y, -BOTTOM_WIDE/2+EDGE/2);
		gl.glRotatef(90, 0, 1, 0);
		tableRoundRect.drawSelf(gl);
		gl.glRotatef(180, x, y, z);
		tableRoundRect.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//����A����
		gl.glTranslatef(-BOTTOM_LENGTH/2+EDGE/2, TEXTURE_RECT_Y, -BOTTOM_WIDE/2);
		tableRoundRect.drawSelf(gl);
		gl.glRotatef(180, x, y, z);
		tableRoundRect.drawSelf(gl);
		gl.glPopMatrix();
		
		gl.glPushMatrix();//���е���
		gl.glTranslatef(0, TEXTURE_RECT_Y, -BOTTOM_WIDE/2);
		tableRoundRect.drawSelf(gl);
		gl.glRotatef(180, x, y, z);
		tableRoundRect.drawSelf(gl);
		gl.glPopMatrix();
		
		
	}
}
