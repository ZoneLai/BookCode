package wyf.sj;
import static wyf.sj.Constant.BIGER_FACTER;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import javax.microedition.khronos.opengles.GL10;

import android.util.Log;

public class ZhuiTi extends BNShape{
	private FloatBuffer mVertexBuffer; //�����������ݻ���
	private FloatBuffer mTextureBuffer;// �����������ݻ���
	int textureId;//����ID
	int vCount;//��������

	float mAngleY;
	float[] tempVerteices;//������������
	float minX;//x����Сλ��
	float maxX;//x�����λ��
	float minY;//y����Сλ��
	float maxY;//y�����λ��
	float minZ;//z����Сλ��
	float maxZ;//z�����λ��
	float midX;//���ĵ�����
	float midY;
	float midZ;
	float xOffset;//�������ƶ���λ��
	float yOffset;
	float zOffset;
	public ZhuiTi(int textureId,float length,float hight,float width,float xOffset,float yOffset,float zOffset)
	{
		this.textureId=textureId;
		this.xOffset=xOffset;
		this.yOffset=yOffset;
		this.zOffset=zOffset;
		float UNIT_SIZE=1.4f;
		float WALL_HEIGHT=2.8f;
		float vScale=0.7f;
	    float hScale=0.2f;
		float[] verteices=
		{

				0,WALL_HEIGHT*vScale*hight,0,
	        	UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,UNIT_SIZE*hScale*width,
	        	UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,-UNIT_SIZE*hScale*width,

	        	0,WALL_HEIGHT*vScale*hight,0,
	        	UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,-UNIT_SIZE*hScale*width,
	        	-UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,-UNIT_SIZE*hScale*width,

	            0,WALL_HEIGHT*vScale*hight,0,
	        	-UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,-UNIT_SIZE*hScale*width,
	        	-UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,UNIT_SIZE*hScale*width,

	            0,WALL_HEIGHT*vScale*hight,0,
	        	-UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,UNIT_SIZE*hScale*width,
	        	UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,UNIT_SIZE*hScale*width,

	            0,0,0,
	        	UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,-UNIT_SIZE*hScale*width,
	        	UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,UNIT_SIZE*hScale*width,

	            0,0,0,
	        	-UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,-UNIT_SIZE*hScale*width,
	        	UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,-UNIT_SIZE*hScale*width,

	            0,0,0,
	        	-UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,UNIT_SIZE*hScale*width,
	        	-UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,-UNIT_SIZE*hScale*width,

	            0,0,0,
	        	UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,UNIT_SIZE*hScale*width,
	        	-UNIT_SIZE*hScale*length,WALL_HEIGHT*vScale/2*hight,UNIT_SIZE*hScale*width,
				
				
		};
		vCount=verteices.length/3;//��ȡ��������
		ByteBuffer vbb=ByteBuffer.allocateDirect(verteices.length*4); //���������������ݻ���
		vbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
		mVertexBuffer=vbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mVertexBuffer.put(verteices);//�򻺳����з��붥����������
		mVertexBuffer.position(0);//���û�������ʼλ��
		
		tempVerteices=verteices;
		
		 float textureCoors[]=new float[]
        {
        	0.5f,0f,  0f,1f,  1f,1f,
        	0.5f,0f,  0f,1f,  1f,1f,
        	0.5f,0f,  0f,1f,  1f,1f,
        	0.5f,0f,  0f,1f,  1f,1f,
        	0.5f,0f,  0f,1f,  1f,1f,
        	0.5f,0f,  0f,1f,  1f,1f,
        	0.5f,0f,  0f,1f,  1f,1f,
        	0.5f,0f,  0f,1f,  1f,1f,
        };
		ByteBuffer tbb=ByteBuffer.allocateDirect(textureCoors.length*4);//���������������ݻ���
		tbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
		mTextureBuffer=tbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
		mTextureBuffer.put(textureCoors);//�򻺳����з��붥������
		mTextureBuffer.position(0);//���û�������ʼλ��
		
	}
	@Override
	public void drawSelf(GL10 gl)
	{

		gl.glRotatef(mAngleY, 0, 1, 0);
		gl.glTranslatef(xOffset, yOffset, zOffset);
		if(hiFlag)
		{
			gl.glScalef(BIGER_FACTER, BIGER_FACTER, BIGER_FACTER);
		}	
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
	@Override
	public float[] findMid() {
		// TODO Auto-generated method stub
		midX=(minX+maxX)/2+xOffset;
		midY=(minY+maxY)/2+yOffset;
		midZ=(minZ+maxZ)/2+zOffset;
		Log.d("ZhuiTi midX=",""+midX);
		Log.d("ZhuiTi midY=",""+midY);
		Log.d("ZhuiTi midZ=",""+midZ);
		float[] mid={midX,midY,midZ};
		return mid;
	}
	@Override
	public float[] findMinMax() {
		// TODO Auto-generated method stub
		for(int i=0;i<tempVerteices.length/3;i++)
		{
			//�ж�X�����С�����λ��
			if(tempVerteices[i*3]<minX)
			{
				minX=tempVerteices[i*3];
			}
			if(tempVerteices[i*3]>maxX)
			{
				maxX=tempVerteices[i*3];
			}
			//�ж�Y�����С�����λ��
			if(tempVerteices[i*3+1]<minY)
			{
				minY=tempVerteices[i*3+1];
			}
			if(tempVerteices[i*3+1]>maxY)
			{
				maxY=tempVerteices[i*3+1];
			}
			//�ж�Z�����С�����λ��
			if(tempVerteices[i*3+2]<minZ)
			{
				minZ=tempVerteices[i*3+2];
			}
			if(tempVerteices[i*3+2]>maxZ)
			{
				maxZ=tempVerteices[i*3+2];
			}
		}
		Log.d("ZhuiTi minX=",""+(maxX-minX));
		Log.d("ZhuiTi minY=",""+(maxY-minY));
		Log.d("ZhuiTi minZ=",""+(maxZ-minZ));
		float[] length={maxX-minX,maxZ-minZ,maxY-minY};
		
		return length;
	}
	@Override
	public void setHilight(boolean flag)
	{
		this.hiFlag=flag;
		Log.d("cube",""+this.hiFlag);
	}
}
