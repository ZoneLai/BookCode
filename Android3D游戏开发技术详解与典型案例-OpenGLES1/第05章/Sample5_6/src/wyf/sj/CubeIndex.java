package wyf.sj;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.opengles.GL10;

public class CubeIndex {
	private FloatBuffer mVertexBuffer;//�����������ݻ���
	private FloatBuffer mNormalBuffer;//���������ݻ���
	private ByteBuffer mIndexBuffer;//�������ݻ���
	public float mOffsetX;
	public float mOffsetY;//��Y����ת
	float scale;						//������߶�	
	int iCount;//����������
	public CubeIndex(float scale,float length,float width)
	{
		this.scale=scale;
		float UNIT_SIZE=0.5f;
		float UNIT_HIGHT=0.5f;
		float[] verteices=
		{
				-UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,//0�ŵ�
				UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,//1�ŵ�
				-UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width,//2�ŵ�
				UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width,//3�ŵ�
				
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,//4�ŵ�
				UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,//5�ŵ�
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width,//6�ŵ�
				UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width//7�ŵ�
				
						
		};
		
		ByteBuffer vbb=ByteBuffer.allocateDirect(verteices.length*4); //���������������ݻ���
		vbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
		mVertexBuffer=vbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mVertexBuffer.put(verteices);//�򻺳����з��붥����������
		mVertexBuffer.position(0);//���û�������ʼλ��
		
		byte[] indices=
		{
				//����
				4,0,5,
				5,0,1,
				//ǰ��
				2,6,3,
				3,6,7,
				//����
				0,2,1,
				1,2,3,
				//����
				6,4,7,
				7,4,5,
				//����
				4,6,2,
				2,0,4,
				//����
				1,3,7,
				7,5,1
		};
		//���������ι����������ݻ���
        mIndexBuffer = ByteBuffer.allocateDirect(indices.length);
        mIndexBuffer.put(indices);//�򻺳����з��������ι�����������
        mIndexBuffer.position(0);//���û�������ʼλ��
        iCount=indices.length;
        float[] normals=
		{
				-1,1,-1,//		-1/3,1/3,-1/3,
				1,1,-1,//		1/3,1/3,-1/3,
				-1,1,1,//		-1/3,1/3,1/3,
				1,1,1,//		1/3,1/3,1/3,
				
				-1,-1,-1,//		-1/3,-1/3,-1/3,
				1,-1-1,//		1/3,-1/3,-1/3,
				-1,-1,1,//		-1/3,-1/3,1/3,
				1,-1,1//		1/3,-1/3,1/3
				
		};
		ByteBuffer nbb=ByteBuffer.allocateDirect(normals.length*4);//�����������������ݻ���
		nbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
		mNormalBuffer=nbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mNormalBuffer.put(normals);//�򻺳����з��붥����������
		mNormalBuffer.position(0);//���û�������ʼλ��
	}
	
	public void drawSelf(GL10 gl)
	{
		gl.glRotatef(mOffsetX, 1, 0, 0);
		gl.glRotatef(mOffsetY, 0, 1, 0);
		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);//����ʹ�ö�������
		
		//Ϊ����ָ��������������
        gl.glVertexPointer
        (
        		3,				//ÿ���������������Ϊ3  xyz 
        		GL10.GL_FLOAT,	//��������ֵ������Ϊ GL_FIXED
        		0, 				//����������������֮��ļ��
        		mVertexBuffer	//������������
        );
		gl.glEnableClientState(GL10.GL_NORMAL_ARRAY);//����ʹ�÷���������
		gl.glNormalPointer(GL10.GL_FLOAT, 0, mNormalBuffer);//Ϊ����ָ�����㷨��������
        
  		gl.glDrawElements(GL10.GL_TRIANGLES, iCount, GL10.GL_UNSIGNED_BYTE, mIndexBuffer);//����������ͼ��	
	}

}
