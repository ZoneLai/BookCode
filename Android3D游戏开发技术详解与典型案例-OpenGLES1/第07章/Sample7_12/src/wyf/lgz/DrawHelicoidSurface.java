package wyf.lgz;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

public class DrawHelicoidSurface
{
	private FloatBuffer myVertex;//���㻺��
	
	int vcount;
	
	float circle_small_R;		//�����ʼ�뾶
	float Hedicoid_small_R;		//��������ʼ�뾶
	
	public float mAngleX;
	public float mAngleY;
	public float mAngleZ;
	
	final static float MAX_ANGLE=360*3f;//�����Ƕ�
	final static float HEDICOID_ANGLE_SPAN=10f;//�����Ƕȱ仯��
	final static float CIRCLE_ANGLE_SPAN=180f;//����Ƕȱ仯��
	final static float CIRCLE_R_SPAN=0f;//����뾶�仯��0.01f
	final static float HEDICOID_R_SPAN=0f;//������뾶�仯��0.2f
	final static float LENGTH_SPAN=0.2f;//�����߶ȱ仯
	final static float CIECLE_ANGLE_BEGIN=0f;//���濪ʼ���ƽǶ�
	final static float CIECLE_ANGLE_OVER=180f;//����������ƽǶ�
	 
	public DrawHelicoidSurface
			(		float circle_small_R,	//����뾶
					float Hedicoid_small_R	//������뾶
			)
	{     
		this.circle_small_R=circle_small_R;
		this.Hedicoid_small_R=Hedicoid_small_R;
		
		ArrayList<Float> val=new ArrayList<Float>();//�����б�
		
		for(float h_angle=0,c_r=circle_small_R,h_r=Hedicoid_small_R,length=0;h_angle<MAX_ANGLE;h_angle+=HEDICOID_ANGLE_SPAN,c_r+=CIRCLE_R_SPAN,h_r+=HEDICOID_R_SPAN,length+=LENGTH_SPAN)
		{
			for(float c_angle=CIECLE_ANGLE_BEGIN;c_angle<CIECLE_ANGLE_OVER;c_angle+=CIRCLE_ANGLE_SPAN)
			{
				float x1=(float) ((h_r+c_r*Math.cos(Math.toRadians(c_angle)))*Math.cos(Math.toRadians(h_angle)));
				float y1=(float) (c_r*Math.sin(Math.toRadians(c_angle))+length);
				float z1=(float) ((h_r+c_r*Math.cos(Math.toRadians(c_angle)))*Math.sin(Math.toRadians(h_angle)));
				
				float x2=(float) ((h_r+c_r*Math.cos(Math.toRadians(c_angle+CIRCLE_ANGLE_SPAN)))*Math.cos(Math.toRadians(h_angle)));
				float y2=(float) (c_r*Math.sin(Math.toRadians(c_angle+CIRCLE_ANGLE_SPAN))+length);
				float z2=(float) ((h_r+c_r*Math.cos(Math.toRadians(c_angle+CIRCLE_ANGLE_SPAN)))*Math.sin(Math.toRadians(h_angle)));
				
				float x3=(float) (((h_r+HEDICOID_R_SPAN)+(c_r+CIRCLE_R_SPAN)*Math.cos(Math.toRadians(c_angle+CIRCLE_ANGLE_SPAN)))*Math.cos(Math.toRadians(h_angle+HEDICOID_ANGLE_SPAN)));
				float y3=(float) ((c_r+CIRCLE_R_SPAN)*Math.sin(Math.toRadians(c_angle+CIRCLE_ANGLE_SPAN))+(length+LENGTH_SPAN));
				float z3=(float) (((h_r+HEDICOID_R_SPAN)+(c_r+CIRCLE_R_SPAN)*Math.cos(Math.toRadians(c_angle+CIRCLE_ANGLE_SPAN)))*Math.sin(Math.toRadians(h_angle+HEDICOID_ANGLE_SPAN)));
				
				float x4=(float) (((h_r+HEDICOID_R_SPAN)+(c_r+CIRCLE_R_SPAN)*Math.cos(Math.toRadians(c_angle)))*Math.cos(Math.toRadians(h_angle+HEDICOID_ANGLE_SPAN)));
				float y4=(float) ((c_r+CIRCLE_R_SPAN)*Math.sin(Math.toRadians(c_angle))+(length+LENGTH_SPAN));
				float z4=(float) (((h_r+HEDICOID_R_SPAN)+(c_r+CIRCLE_R_SPAN)*Math.cos(Math.toRadians(c_angle)))*Math.sin(Math.toRadians(h_angle+HEDICOID_ANGLE_SPAN)));
				
				val.add(x1);val.add(y1);val.add(z1);//���������Σ���6�����������
				val.add(x2);val.add(y2);val.add(z2);
				
				val.add(x2);val.add(y2);val.add(z2);
				val.add(x4);val.add(y4);val.add(z4);
				
				val.add(x4);val.add(y4);val.add(z4);
				val.add(x1);val.add(y1);val.add(z1);
				
				val.add(x2);val.add(y2);val.add(z2);
				val.add(x3);val.add(y3);val.add(z3);
				
				val.add(x3);val.add(y3);val.add(z3);
				val.add(x4);val.add(y4);val.add(z4);
				
				val.add(x4);val.add(y4);val.add(z4);
				val.add(x2);val.add(y2);val.add(z2);
			}
		}
		vcount=val.size()/3;
		float[] vertexs=new float[vcount*3];
		for(int i=0;i<vcount*3;i++)
		{
			vertexs[i]=val.get(i);
		}
		ByteBuffer vbb=ByteBuffer.allocateDirect(vertexs.length*4);
		vbb.order(ByteOrder.nativeOrder());
		myVertex=vbb.asFloatBuffer();
		myVertex.put(vertexs);
		myVertex.position(0);
	}
	
	public void drawSelf(GL10 gl)
	{	
		gl.glRotatef(mAngleX, 1, 0, 0);//��ת
		gl.glRotatef(mAngleY, 0, 1, 0);
		gl.glRotatef(mAngleZ, 0, 0, 1);
		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, myVertex);
		
		gl.glColor4f(0, 0, 0, 0);
		gl.glDrawArrays(GL10.GL_LINES, 0, vcount);

		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
	}
}
