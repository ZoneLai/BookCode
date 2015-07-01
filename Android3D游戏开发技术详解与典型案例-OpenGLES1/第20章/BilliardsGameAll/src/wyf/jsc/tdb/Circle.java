package wyf.jsc.tdb;

import static wyf.jsc.tdb.Constant.TABLE_UNIT_SIZE;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

public class Circle {


	FloatBuffer mVertexBuffer;
	FloatBuffer mTextureBuffer;	
	int vCount;
	int textureId;
	public Circle(float scaleX,float scaleZ,int textureId)
	{
		this.textureId=textureId;	
		float SPAN=18;
		ArrayList<Float> alVertex=new ArrayList<Float>();
		for(int i=0;i<360/SPAN;i++)
		{
			float x1=0.0f;float y1=0.0f;float z1=0.0f;//������ԭ��
			//���ݵ�λ�Ƕȼ���ڶ���������
			float x2=(float)Math.cos(Math.toRadians(i*SPAN))*scaleX*TABLE_UNIT_SIZE;
			float y2=0.0f;
			float z2=(float)Math.sin(Math.toRadians(i*SPAN))*scaleZ*TABLE_UNIT_SIZE;
			//���������������
			float x3=(float)Math.cos(Math.toRadians((i+1)*SPAN))*scaleX*TABLE_UNIT_SIZE;
			float y3=0.0f;
			float z3=(float)Math.sin(Math.toRadians((i+1)*SPAN))*scaleZ*TABLE_UNIT_SIZE;
			//����ʱ�뷽��ڷŶ��㣬���������
			alVertex.add(x1);
			alVertex.add(y1);
			alVertex.add(z1);	
			alVertex.add(x3);
			alVertex.add(y3);
			alVertex.add(z3);		
			alVertex.add(x2);
			alVertex.add(y2);
			alVertex.add(z2);		
		}
		vCount=alVertex.size()/3;
		float[] verteices=new float[vCount*3];
		for(int i=0;i<vCount*3;i++)
		{
			verteices[i]=alVertex.get(i);
		}	
		ByteBuffer vbb=ByteBuffer.allocateDirect(verteices.length*4);//����������������ݻ���
		vbb.order(ByteOrder.nativeOrder());	//�����ֽ�˳��
		mVertexBuffer=vbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mVertexBuffer.put(verteices);//�򻺳����з��붥����������
		mVertexBuffer.position(0);//���û�������ʼλ�� 
				
		float[] textureCoors=new float[vCount*2];//������������
		for(int i=0;i<vCount/3;i++)
		{
			textureCoors[i*6]=0;
			textureCoors[i*6+1]=0;
			
			textureCoors[i*6+2]=0;
			textureCoors[i*6+3]=1;
			
			textureCoors[i*6+4]=1;
			textureCoors[i*6+5]=0;
		}
		
		ByteBuffer tbb=ByteBuffer.allocateDirect(textureCoors.length*4);//��������������������ݻ���
		tbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
		mTextureBuffer=tbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mTextureBuffer.put(textureCoors);//�򻺳����з��붥����������
		mTextureBuffer.position(0);//���û�������ʼλ��
	}
	public void drawSelf(GL10 gl)
	{
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);//����ʹ�ö�������
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer);//Ϊ����ָ��������������
		
		gl.glEnable(GL10.GL_TEXTURE_2D);//��������
		gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);//����ʹ����������
		gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, mTextureBuffer);//Ϊ����ָ��������������
		gl.glBindTexture(GL10.GL_TEXTURE_2D, textureId);//������ID
		
		gl.glDrawArrays(GL10.GL_TRIANGLES, 0, vCount);//�������η�ʽ���
		
		gl.glDisableClientState(GL10.GL_TEXTURE_COORD_ARRAY);//�ر���������
		gl.glDisable(GL10.GL_TEXTURE_2D);//�ر�����
	}
}
