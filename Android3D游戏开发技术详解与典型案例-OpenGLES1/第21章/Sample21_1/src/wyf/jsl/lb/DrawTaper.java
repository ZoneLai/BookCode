package wyf.jsl.lb;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

public class DrawTaper
{
	private FloatBuffer myVertexBuffer;//�������껺�� 
	private FloatBuffer myNormalBuffer;//����������
	
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
		this.degreespan=degreespan;
		this.col=col;
		
		float spanHeight=(float)height/col;//Բ׶ÿ����ռ�ĸ߶�
		float spanR=circle_radius/col;//�뾶��λ����
		
		float normalHeight=(height*circle_radius*circle_radius)/(height*height+circle_radius*circle_radius);//������������Բ����ĸ߶�
		float normalR=(height*height*circle_radius)/(height*height+circle_radius*circle_radius);//������������Բ����İ뾶
		
		ArrayList<Float> val=new ArrayList<Float>();//�������б�
		ArrayList<Float> ial=new ArrayList<Float>();//����������б�
		
		for(float circle_degree=360.0f;circle_degree>0.0f;circle_degree-=degreespan)//ѭ����
		{
			for(int j=0;j<col;j++)//ѭ����
			{
				float currentR=j*spanR;//��ǰ�����Բ�뾶
				float currentHeight=height-j*spanHeight;//��ǰ����ĸ߶�
				
				float x1=(float) (currentR*Math.cos(Math.toRadians(circle_degree)));
				float y1=currentHeight;
				float z1=(float) (currentR*Math.sin(Math.toRadians(circle_degree)));
				
				float a1=(float) (normalR*Math.cos(Math.toRadians(circle_degree)));
				float b1=normalHeight;
				float c1=(float) (normalR*Math.sin(Math.toRadians(circle_degree)));
				float l1=CollectionUtil.getVectorLength(a1, b1, c1);//ģ��
				a1=a1/l1;//���������
				b1=b1/l1;
				c1=c1/l1;
				
				float x2=(float) ((currentR+spanR)*Math.cos(Math.toRadians(circle_degree)));
				float y2=currentHeight-spanHeight;
				float z2=(float) ((currentR+spanR)*Math.sin(Math.toRadians(circle_degree)));
				
				float a2=(float) (normalR*Math.cos(Math.toRadians(circle_degree)));
				float b2=normalHeight;
				float c2=(float) (normalR*Math.sin(Math.toRadians(circle_degree)));
				float l2=CollectionUtil.getVectorLength(a2, b2, c2);//ģ��
				a2=a2/l2;//���������
				b2=b2/l2;
				c2=c2/l2;
				
				float x3=(float) ((currentR+spanR)*Math.cos(Math.toRadians(circle_degree-degreespan)));
				float y3=currentHeight-spanHeight;
				float z3=(float) ((currentR+spanR)*Math.sin(Math.toRadians(circle_degree-degreespan)));
				
				float a3=(float) (normalR*Math.cos(Math.toRadians(circle_degree-degreespan)));
				float b3=normalHeight;
				float c3=(float) (normalR*Math.sin(Math.toRadians(circle_degree-degreespan)));
				float l3=CollectionUtil.getVectorLength(a3, b3, c3);//ģ��
				a3=a3/l3;//���������
				b3=b3/l3;
				c3=c3/l3;
				
				float x4=(float) ((currentR)*Math.cos(Math.toRadians(circle_degree-degreespan)));
				float y4=currentHeight;
				float z4=(float) ((currentR)*Math.sin(Math.toRadians(circle_degree-degreespan)));
				
				float a4=(float) (normalR*Math.cos(Math.toRadians(circle_degree-degreespan)));
				float b4=normalHeight;
				float c4=(float) (normalR*Math.sin(Math.toRadians(circle_degree-degreespan)));
				float l4=CollectionUtil.getVectorLength(a4, b4, c4);//ģ��
				a4=a4/l4;//���������
				b4=b4/l4;
				c4=c4/l4;
				
				val.add(x1);val.add(y1);val.add(z1);//���������Σ���6�����������
				val.add(x2);val.add(y2);val.add(z2);
				val.add(x4);val.add(y4);val.add(z4);
				
				val.add(x2);val.add(y2);val.add(z2);
				val.add(x3);val.add(y3);val.add(z3);
				val.add(x4);val.add(y4);val.add(z4);
				
				ial.add(a1);ial.add(b1);ial.add(c1);//�����Ӧ�ķ�����
				ial.add(a2);ial.add(b2);ial.add(c2);
				ial.add(a4);ial.add(b4);ial.add(c4);
				
				ial.add(a2);ial.add(b2);ial.add(c2);
				ial.add(a3);ial.add(b3);ial.add(c3);
				ial.add(a4);ial.add(b4);ial.add(c4);
			}
		}
		
		vCount=val.size()/3;//ȷ����������
		
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
		
		float[] normals=new float[vCount*3];
		for(int i=0;i<vCount*3;i++)
		{
			normals[i]=ial.get(i);
		}
		ByteBuffer ibb=ByteBuffer.allocateDirect(normals.length*4);
		ibb.order(ByteOrder.nativeOrder());
		myNormalBuffer=ibb.asFloatBuffer();
		myNormalBuffer.put(normals);
		myNormalBuffer.position(0);
	}
	
	public void drawSelf(GL10 gl)
	{
		gl.glRotatef(mAngleX, 1, 0, 0);//��ת
		gl.glRotatef(mAngleY, 0, 1, 0);
		gl.glRotatef(mAngleZ, 0, 0, 1);
		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);//�򿪶��㻺��
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, myVertexBuffer);//ָ�����㻺��
		
		gl.glEnableClientState(GL10.GL_NORMAL_ARRAY);//�򿪷���������
		gl.glNormalPointer(GL10.GL_FLOAT, 0, myNormalBuffer);//ָ������������
		
		gl.glDrawArrays(GL10.GL_TRIANGLES, 0, vCount);//����ͼ��
	}
}