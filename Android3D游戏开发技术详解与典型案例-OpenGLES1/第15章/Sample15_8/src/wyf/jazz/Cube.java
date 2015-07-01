package wyf.jazz;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.opengles.GL10;

public class Cube {

	private FloatBuffer mVertexBuffer;//�����������ݻ���
	private FloatBuffer mTextureBuffer;//�����������ݻ���
	public float mOffsetX;
	public float mOffsetY;//��Y����ת
	float scale;						//������߶�			
	int vCount;//��������
	int textureId;//����ID
	float[] tempVerteices;
	public Cube(int textureId,float scale,float length,float width)
	{
		this.scale=scale;
		this.textureId=textureId;
		vCount=36;
		float UNIT_SIZE=1f;
		float UNIT_HIGHT=1f;
		float[] verteices=
		{
				
				//����
				-UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,
				UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,
				-UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width,
				
				UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,
				UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width,
				-UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width,
				
				//����
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,
				UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,
				-UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,
				
				UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,
				UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,
				-UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,
				
				//ǰ��
				-UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width,
				UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width,
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width,
				
				UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width,
				UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width,
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width,
				
				//����
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width,
				UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width,
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,
				
				UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width,
				UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,
				
				//����
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,
				-UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width,
								
				-UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,
				-UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width,
				-UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width,
				
				
				//����
				UNIT_SIZE*length,UNIT_HIGHT*scale,-UNIT_SIZE*width,
				UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,
				UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width,
				
				UNIT_SIZE*length,-UNIT_HIGHT*scale,-UNIT_SIZE*width,
				UNIT_SIZE*length,-UNIT_HIGHT*scale,UNIT_SIZE*width,
				UNIT_SIZE*length,UNIT_HIGHT*scale,UNIT_SIZE*width
						  
		};
		tempVerteices=verteices;
		ByteBuffer vbb=ByteBuffer.allocateDirect(verteices.length*4); //���������������ݻ���
		vbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
		mVertexBuffer=vbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mVertexBuffer.put(verteices);//�򻺳����з��붥����������
		mVertexBuffer.position(0);//���û�������ʼλ��
		float[] textureCoors={
		
				0.250f,0.000f,0.482f,0.000f,0.250f,0.244f,
				0.482f,0.000f,0.482f,0.244f,0.250f,0.244f,
				
				0.246f,0.482f,0.490f,0.482f,0.246f,0.241f,
				0.490f,0.482f,0.490f,0.241f,0.246f,0.241f,
				
				0.734f,0.241f,0.976f,0.241f,0.734f,0.482f,
				0.976f,0.241f,0.976f,0.482f,0.734f,0.482f,
				
				0.246f,0.723f,0.488f,0.723f,0.246f,0.482f,
				0.488f,0.723f,0.488f,0.482f,0.246f,0.482f,
				
				0.250f,0.480f,0.250f,0.240f,0.004f,0.480f,
				0.250f,0.240f,0.004f,0.240f,0.004f,0.480f,
				
				0.482f,0.240f,0.482f,0.480f,0.734f,0.240f,
				0.482f,0.480f,0.734f,0.480f,0.734f,0.240f
		};
		
		
		
		ByteBuffer tbb=ByteBuffer.allocateDirect(textureCoors.length*4);//���������������ݻ���
		tbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
		mTextureBuffer=tbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mTextureBuffer.put(textureCoors);//�򻺳����з��붥����������
		mTextureBuffer.position(0);//���û�������ʼλ��
	}
	public void drawSelf(GL10 gl)
	{
		gl.glRotatef(mOffsetX, 1, 0, 0);
		gl.glRotatef(mOffsetY, 0, 1, 0);
		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer);
		
		gl.glEnable(GL10.GL_TEXTURE_2D);//��������
		gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);//����ʹ����������
		gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, mTextureBuffer);//ָ����������
		gl.glBindTexture(GL10.GL_TEXTURE_2D, textureId);//������
		

		gl.glDrawArrays(GL10.GL_TRIANGLES, 0, vCount);//����

		
		gl.glDisableClientState(GL10.GL_TEXTURE_COORD_ARRAY);//�ر���������
		gl.glDisable(GL10.GL_TEXTURE_2D);//�ر�����
	}
}
