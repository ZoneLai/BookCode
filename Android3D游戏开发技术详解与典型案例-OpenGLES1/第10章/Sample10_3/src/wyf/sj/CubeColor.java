package wyf.sj;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.opengles.GL10;

public class CubeColor {

	private FloatBuffer mVertexBuffer;//�����������ݻ���
	private FloatBuffer mColorBuffer;	//�����������ݻ���
	public float mOffsetX;
	public float mOffsetY;
	float scale;						//������߶�			
	int vCount;//��������
	public CubeColor(float scale,float length,float width)
	{
		this.scale=scale;
		vCount=36;
		float TABLE_UNIT_SIZE=0.5f;
		float TABLE_UNIT_HIGHT=0.5f;
		float[] verteices=
		{
				
				//����
				-TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				
				TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				
				//����
				-TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				
				TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				
				//ǰ��
				-TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				
				TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				
				//����
				-TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				
				TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				
				//����
				-TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				
				-TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				-TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				
				//����
				TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				
				TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,-TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width,
				TABLE_UNIT_SIZE*length,-TABLE_UNIT_HIGHT*scale,TABLE_UNIT_SIZE*width
						
		};
		
		ByteBuffer vbb=ByteBuffer.allocateDirect(verteices.length*4); //���������������ݻ���
		vbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
		mVertexBuffer=vbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mVertexBuffer.put(verteices);//�򻺳����з��붥����������
		mVertexBuffer.position(0);//���û�������ʼλ��
		
		float[] colors=new float[vCount*4];//������ɫ����
		for(int i=0;i<vCount;i++)
		{
			colors[i*4]=(float)Math.random();
			colors[i*4+1]=(float)Math.random();
			colors[i*4+2]=(float)Math.random();
			colors[i*4+3]=(float)Math.random();
		}
		
		
		ByteBuffer tbb=ByteBuffer.allocateDirect(colors.length*4); //������ɫ�������ݻ���
		tbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
		mColorBuffer=tbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mColorBuffer.put(colors);//�򻺳����з��붥����������
		mColorBuffer.position(0);//���û�������ʼλ��
	}
	
	public void drawSelf(GL10 gl)
	{
		gl.glRotatef(mOffsetX, 1, 0, 0);
		gl.glRotatef(mOffsetY, 0, 1, 0);
		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glEnableClientState(GL10.GL_COLOR_ARRAY);
		
		//Ϊ����ָ��������������
        gl.glVertexPointer
        (
        		3,				//ÿ���������������Ϊ3  xyz 
        		GL10.GL_FLOAT,	//��������ֵ������Ϊ GL_FIXED
        		0, 				//����������������֮��ļ��
        		mVertexBuffer	//������������
        );
		
        //Ϊ����ָ��������ɫ����
        gl.glColorPointer
        (
        		4, 				//������ɫ����ɳɷ֣�����Ϊ4��RGBA
        		GL10.GL_FLOAT, 	//������ɫֵ������Ϊ GL_FIXED
        		0, 				//����������ɫ����֮��ļ��
        		mColorBuffer	//������ɫ����
        );
		gl.glDrawArrays(GL10.GL_TRIANGLES, 0, vCount);//����ͼ��
		gl.glDisableClientState(GL10.GL_COLOR_ARRAY);//���ö�����ɫ����		
	}

}
