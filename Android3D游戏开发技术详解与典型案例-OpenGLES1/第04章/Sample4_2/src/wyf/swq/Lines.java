package wyf.swq;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.IntBuffer;

import javax.microedition.khronos.opengles.GL10;

public class Lines {
	private IntBuffer myVertexBuffer;			//�����������ݻ���
	private IntBuffer myColorBuffer;			//������ɫ���ݻ���
	private ByteBuffer myIndexBuffer;		//���㹹�����������ݻ���
	
	int vCount=0;						//�����������
	int iCount=0;						//������������

	public Lines(){
		vCount=4;						//��������
		final int UNIT_SIZE=10000;			//���ű���
		int []vertices=new int[]
	       {
				-2*UNIT_SIZE,3*UNIT_SIZE,0,
				1*UNIT_SIZE,1*UNIT_SIZE,0,
				-1*UNIT_SIZE,-2*UNIT_SIZE,0,
				2*UNIT_SIZE,-3*UNIT_SIZE,0
	       };
		//���������������ݻ��棬���ڲ�ͬƽ̨�ֽ�˳��ͬ�����ݵ�Ԫ�����ֽڵģ�����������͵Ļ��棩��һ��Ҫ����ByteBufferת�����ؼ���ͨ��ByteOrder����nativeOrder()
		ByteBuffer vbb=ByteBuffer.allocateDirect(vertices.length*4);//һ�������ĸ��ֽڣ��������·�����ڴ��������һ��������ֽڻ���
		vbb.order(ByteOrder.nativeOrder());//��������ֽڻ�����ֽ�˳��Ϊ����ƽ̨���ֽ�˳��
		myVertexBuffer=vbb.asIntBuffer();//ת��Ϊint�ͻ���
		myVertexBuffer.put(vertices);//�򻺳����з��붥����������
		myVertexBuffer.position(0);//���û���������ʼλ��
		
		final int one=65535;//֧��65535ɫɫ��ͨ��
		int []colors=new int[]//������ɫֵ���飬ÿ������4��ɫ��ֵRGBA
		{
			one,one,one,0,
			one,one,one,0,
			one,one,one,0,
			one,one,one,0
		};
		ByteBuffer cbb=ByteBuffer.allocateDirect(colors.length*4);
		cbb.order(ByteOrder.nativeOrder());
		myColorBuffer=cbb.asIntBuffer();
		myColorBuffer.put(colors);
		myColorBuffer.position(0);
		//Ϊ�����ι����������ݳ�ʼ��
		iCount=4;
		byte []indices=new byte[]
            {
				0,3,2,1
            };
		//���������ι����������ݻ���
		myIndexBuffer=ByteBuffer.allocateDirect(indices.length);
		myIndexBuffer.put(indices);
		myIndexBuffer.position(0);
	}
	public void drawSelf(GL10 gl)
	{
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);//���ö�����������
		gl.glEnableClientState(GL10.GL_COLOR_ARRAY);//���ö�����ɫ����	
		gl.glVertexPointer(				//Ϊ����ָ��������������
				3,					//ÿ������������������
				GL10.GL_FIXED,		//��������ֵ������
				0,					//����������������֮��ļ��
				myVertexBuffer		//������������
		);
		gl.glColorPointer(				//Ϊ����ָ������ ��ɫ����
			4,							//ÿ���������ɫֵ�������
			GL10.GL_FIXED,			//������ɫֵ������
			0,						//������ɫ����֮��ļ��
			myColorBuffer			//������ɫ����
		);
		gl.glDrawElements( //����������ͼ��
			GL10.GL_LINES,          //���߷�ʽ���
			iCount,					//��������
			GL10.GL_UNSIGNED_BYTE,	//����ֵ������
			myIndexBuffer			//����ֵ����
		);
	}}

