package wyf.lgz;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

public class DrawParaboloid
{
	private FloatBuffer myVertexBuffer;//�������껺�� 
	
	int vCount;//��������
	
	float height;//������߶�
	float a;//������Բ�����
	float b;
	float col;//������߶��и����
	float angleSpan;//�����зֽǶ�
	
	public float mAngleX;
	public float mAngleY;
	public float mAngleZ;
	
	public DrawParaboloid(float height,float a,float b,int col,float angleSpan)
	{
		this.height=height;
		this.a=a;
		this.b=b;
		this.col=col;
		this.angleSpan=angleSpan;
		
		float heightSpan=height/col;//������ÿ����ռ�ĸ߶�
		
		ArrayList<Float> val=new ArrayList<Float>();//�������б�
		
		for(float h=height;h>0;h-=heightSpan)//ѭ����
		{
			for(float angle=360;angle>0;angle-=angleSpan)//ѭ����
			{
				float x1=(float) (a*Math.sqrt(2*h)*Math.cos(Math.toRadians(angle)));
				float y1=h;
				float z1=(float) (b*Math.sqrt(2*h)*Math.sin(Math.toRadians(angle)));
				
				float x2=(float) (a*Math.sqrt(2*(h-heightSpan))*Math.cos(Math.toRadians(angle)));
				float y2=h-heightSpan;
				float z2=(float) (b*Math.sqrt(2*(h-heightSpan))*Math.sin(Math.toRadians(angle)));
				
				float x3=(float) (a*Math.sqrt(2*(h-heightSpan))*Math.cos(Math.toRadians(angle-angleSpan)));
				float y3=h-heightSpan;
				float z3=(float) (b*Math.sqrt(2*(h-heightSpan))*Math.sin(Math.toRadians(angle-angleSpan)));
				
				float x4=(float) (a*Math.sqrt(2*h)*Math.cos(Math.toRadians(angle-angleSpan)));
				float y4=h;
				float z4=(float) (b*Math.sqrt(2*h)*Math.sin(Math.toRadians(angle-angleSpan)));
				
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
		 
		vCount=val.size()/3;//ȷ����������
		
		//����
		float[] vertexs=new float[vCount*3];
		for(int i=0;i<vCount*3;i++)
		{
			vertexs[i]=val.get(i);
		}
		ByteBuffer vbb=ByteBuffer.allocateDirect(vertexs.length*4);
		vbb.order(ByteOrder.nativeOrder());
		myVertexBuffer=vbb.asFloatBuffer();
		myVertexBuffer.put(vertexs);
		myVertexBuffer.position(0);
	}
	
	public void drawSelf(GL10 gl) 
	{
		gl.glRotatef(mAngleX, 1, 0, 0);//��ת
		gl.glRotatef(mAngleY, 0, 1, 0);
		gl.glRotatef(mAngleZ, 0, 0, 1);
		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, myVertexBuffer);
		
		gl.glColor4f(0, 0, 0, 0);
		gl.glDrawArrays(GL10.GL_LINES, 0, vCount);
		
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
	}
}