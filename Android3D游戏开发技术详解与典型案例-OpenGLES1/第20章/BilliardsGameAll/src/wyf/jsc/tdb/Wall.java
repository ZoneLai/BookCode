package wyf.jsc.tdb;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import javax.microedition.khronos.opengles.GL10;
import static wyf.jsc.tdb.Constant.*;

public class Wall {

	private FloatBuffer mVertexBuffer;
	private FloatBuffer mTextureBuffer;  //�����������ݻ���
	int vCount=0;
	float xOffset;    
    int textureId;	
	public Wall(int textureId)
	{
		this.textureId=textureId;
		//final float UNIT_SIZE=8f;
		float vertices[]=new float[]
		{
			-WALL_SIZE,WALL_SIZE,-WALL_SIZE,
			-WALL_SIZE,0,-WALL_SIZE,
			WALL_SIZE,0,-WALL_SIZE,
			
			-WALL_SIZE,WALL_SIZE,-WALL_SIZE,
			WALL_SIZE,0,-WALL_SIZE,
			WALL_SIZE,WALL_SIZE,-WALL_SIZE,//����
			
			-WALL_SIZE,0,WALL_SIZE,
			-WALL_SIZE,WALL_SIZE,WALL_SIZE,
			WALL_SIZE,WALL_SIZE,WALL_SIZE,
			
			-WALL_SIZE,0,WALL_SIZE,
			WALL_SIZE,WALL_SIZE,WALL_SIZE,
			WALL_SIZE,0,WALL_SIZE,//ǰ��
			
			-WALL_SIZE,WALL_SIZE,-WALL_SIZE,
			-WALL_SIZE,WALL_SIZE,WALL_SIZE,
			-WALL_SIZE,0,WALL_SIZE,
			
			-WALL_SIZE,WALL_SIZE,-WALL_SIZE,
			-WALL_SIZE,0,WALL_SIZE,
			-WALL_SIZE,0,-WALL_SIZE,//����
			
			WALL_SIZE,0,-WALL_SIZE,
			WALL_SIZE,0,WALL_SIZE,
			WALL_SIZE,WALL_SIZE,WALL_SIZE,
			
			WALL_SIZE,0,-WALL_SIZE,
			WALL_SIZE,WALL_SIZE,WALL_SIZE,
			WALL_SIZE,WALL_SIZE,-WALL_SIZE
			
			
				
				
		
		};
		 //���������������ݻ���
        //vertices.length*4����Ϊһ�������ĸ��ֽ�
		vCount=vertices.length/3;
        ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length*4);
        vbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
        mVertexBuffer = vbb.asFloatBuffer();//ת��Ϊint�ͻ���
        mVertexBuffer.put(vertices);//�򻺳����з��붥����������
        mVertexBuffer.position(0);//���û�������ʼλ��
        //�ر���ʾ�����ڲ�ͬƽ̨�ֽ�˳��ͬ���ݵ�Ԫ�����ֽڵ�һ��Ҫ����ByteBuffer
        //ת�����ؼ���Ҫͨ��ByteOrder����nativeOrder()�������п��ܻ������
        
  
         float textureCoors[]=new float[vCount*2];
         for(int i=0;i<vCount/6;i++)
         {
        	 textureCoors[i*12]=0;
        	 textureCoors[i*12+1]=0;
        	 
        	 textureCoors[i*12+2]=0;
        	 textureCoors[i*12+3]=1;
        	 
        	 textureCoors[i*12+4]=1;
        	 textureCoors[i*12+5]=1;
        	 
        	 textureCoors[i*12+6]=0;
        	 textureCoors[i*12+7]=0;
        	 
        	 textureCoors[i*12+8]=1;
        	 textureCoors[i*12+9]=1;
        	 
        	 textureCoors[i*12+10]=1;
        	 textureCoors[i*12+11]=0;
        	 
         }
          //���������������ݻ���
	        //textureCoors.length��4����Ϊһ��float�������ĸ��ֽ�
	        ByteBuffer cbb = ByteBuffer.allocateDirect(textureCoors.length*4);
	        cbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
	        mTextureBuffer = cbb.asFloatBuffer();//ת��Ϊint�ͻ���
	        mTextureBuffer.put(textureCoors);//�򻺳����з��붥����ɫ����
	        mTextureBuffer.position(0);//���û�������ʼλ��
	        //�ر���ʾ�����ڲ�ͬƽ̨�ֽ�˳��ͬ���ݵ�Ԫ�����ֽڵ�һ��Ҫ����ByteBuffer
	        //ת�����ؼ���Ҫͨ��ByteOrder����nativeOrder()�������п��ܻ������
	        //�����������ݵĳ�ʼ��================end============================*/        
       
	}
	public void drawSelf(GL10 gl)
	{
		gl.glRotatef(xOffset, 1, 0, 0);
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);//���ö�����������
		gl.glVertexPointer//Ϊ����ָ��������������
		(
				3, 
				GL10.GL_FLOAT,
				0,
				mVertexBuffer
		);			
		gl.glEnable(GL10.GL_TEXTURE_2D); //��������
		gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);	//����ʹ������ST���껺��	
		gl.glBindTexture(GL10.GL_TEXTURE_2D, textureId); //�󶨵�ǰ����
		gl.glTexCoordPointer//Ϊ����ָ������ST���껺��
		(
				2, 
				GL10.GL_FLOAT, 
				0,
				mTextureBuffer
		);                                       
		gl.glDrawArrays//����ͼ��
		(
				GL10.GL_TRIANGLES, 
				0, 
				vCount
		);	
	}
}

