package wyf.lgz;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

public class DrawTaper
{
	private FloatBuffer myVertexBuffer;//�������껺�� 
	
	int vCount;//��������
	
	float height;//Բ������
	float circle_radius;//Բ׶����뾶
	float degreespan;  //Բ�ػ�ÿһ�ݵĶ�����С
	int col;//Բ׶ƽ���зֵĿ��� 
	
	public float mAngleX;
	public float mAngleY;
	public float mAngleZ;
	
	public DrawTaper(float height,float circle_radius,float degreespan,int col)
	{
		this.height=height;
		this.circle_radius=circle_radius;
		this.degreespan=degreespan;	//��ʾ���ٶ��и�һ��
		this.col=col;				//��ʾheight�ּ����и�
		
		float spanHeight=(float)height/col;//Բ׶ÿ����ռ�ĸ߶�
		float spanR=circle_radius/col;//�뾶��λ����
		
		ArrayList<Float> val=new ArrayList<Float>();//�������б�
		
		for(float circle_degree=360.0f;circle_degree>0.0f;circle_degree-=degreespan)//ѭ����
		{
			for(int j=0;j<col;j++)//ѭ����
			{
				float currentR=j*spanR;//��ǰ�����Բ�뾶
				float currentHeight=height-j*spanHeight;//��ǰ����ĸ߶�
				
				float x1=(float) (currentR*Math.cos(Math.toRadians(circle_degree)));
				float y1=currentHeight;
				float z1=(float) (currentR*Math.sin(Math.toRadians(circle_degree)));
				
				float x2=(float) ((currentR+spanR)*Math.cos(Math.toRadians(circle_degree)));
				float y2=currentHeight-spanHeight;
				float z2=(float) ((currentR+spanR)*Math.sin(Math.toRadians(circle_degree)));
				
				float x3=(float) ((currentR+spanR)*Math.cos(Math.toRadians(circle_degree-degreespan)));
				float y3=currentHeight-spanHeight;
				float z3=(float) ((currentR+spanR)*Math.sin(Math.toRadians(circle_degree-degreespan)));
				
				float x4=(float) ((currentR)*Math.cos(Math.toRadians(circle_degree-degreespan)));
				float y4=currentHeight;
				float z4=(float) ((currentR)*Math.sin(Math.toRadians(circle_degree-degreespan)));
				
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
		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);//�򿪶��㻺��
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, myVertexBuffer);//ָ�����㻺��
		
		gl.glColor4f(0, 0, 0, 0);
		gl.glDrawArrays(GL10.GL_LINES, 0, vCount);//����ͼ��

		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
	}
}