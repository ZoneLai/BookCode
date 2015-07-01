package wyf.jsc.tdb;

import static wyf.jsc.tdb.Constant.TABLE_UNIT_HIGHT;
import static wyf.jsc.tdb.Constant.TABLE_UNIT_SIZE;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.opengles.GL10;

public class TableBottom {

	private FloatBuffer mVertexBuffer;
	private FloatBuffer mTextureBuffer;	
	public float mOffsetX;
	public float mOffsetY;
	float scale;
	int textureId;
	int vCount;
	public TableBottom(int textureId,float scale,float length,float width)
	{
		this.scale=scale;
		this.textureId=textureId;
		vCount=36;
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
		
		ByteBuffer vbb=ByteBuffer.allocateDirect(verteices.length*4);//���������������ݻ���
		vbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
		mVertexBuffer=vbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mVertexBuffer.put(verteices);//�򻺳����з��붥����������
		mVertexBuffer.position(0);//���û�������ʼλ��
		
		float[] textureCoors=new float[vCount*2];//������������
		for(int i=0;i<vCount/6;i++)
		{
			textureCoors[i*12]=0;
			textureCoors[(i*12)+1]=0;
			
			textureCoors[(i*12)+2]=0;
			textureCoors[(i*12)+3]=1;
			
			textureCoors[(i*12)+4]=1;
			textureCoors[(i*12)+5]=0;
			
			textureCoors[(i*12)+6]=1;
			textureCoors[(i*12)+7]=0;
			
			textureCoors[(i*12)+8]=0;
			textureCoors[(i*12)+9]=1;
			
			textureCoors[(i*12)+10]=1;
			textureCoors[(i*12)+11]=1;		

		}
		
		
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
		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);//����ʹ�ö�������
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer);//Ϊ����ָ����������
		
		gl.glEnable(GL10.GL_TEXTURE_2D);//��������
		gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);//����ʹ����������
		gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, mTextureBuffer);//Ϊ����ָ����������
		gl.glBindTexture(GL10.GL_TEXTURE_2D, textureId);//������ID
		gl.glDrawArrays(GL10.GL_TRIANGLES, 0, vCount);//�������η�ʽ���
		
		gl.glDisableClientState(GL10.GL_TEXTURE_COORD_ARRAY);//��ֹʹ����������
		gl.glDisable(GL10.GL_TEXTURE_2D);//�ر�����
		
	}
}
