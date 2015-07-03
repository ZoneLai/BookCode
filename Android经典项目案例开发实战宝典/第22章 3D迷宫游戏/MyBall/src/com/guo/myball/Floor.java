package com.guo.myball;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import javax.microedition.khronos.opengles.GL10;

import static com.guo.myball.Constant.*;
//��ʾ�ذ����
public class Floor {
	//�����������ݻ���
	private FloatBuffer   mVertexBuffer;
	//�����������ݻ���
    private FloatBuffer mTextureBuffer;
    //���㷨����������
    private FloatBuffer mNormalBuffer;
    //��������
    int vCount=0;
    //�ذ����width����λ
    int width;
    //�ذ�����height����λ
    int height;
    //���캯��
    public Floor(int width,int height)
    {
    	this.width=width;
    	this.height=height;
    	//�����������ݵĳ�ʼ��-------begin
    	//ÿ���ذ��6������
        vCount=6;
    	float []vertices=new float[]
    	{
    			-width*UNIT_SIZE/2,0,-height*UNIT_SIZE/2,
    			-width*UNIT_SIZE/2,0,height*UNIT_SIZE/2,
    			width*UNIT_SIZE/2,0,height*UNIT_SIZE/2,
    		
    			width*UNIT_SIZE/2,0,height*UNIT_SIZE/2,
    			width*UNIT_SIZE/2,0,-height*UNIT_SIZE/2,
    			-width*UNIT_SIZE/2,0,-height*UNIT_SIZE/2
    	};  
    	//����ռ�
    	ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length*4);
    	//�����ֽ�˳��
        vbb.order(ByteOrder.nativeOrder());
        //ת��Ϊfloat�ͻ���
        mVertexBuffer = vbb.asFloatBuffer();
        //�򻺳����з��붥����������
        mVertexBuffer.put(vertices);
        //���û�������ʼλ��    
        mVertexBuffer.position(0);   
        float textures[]=new float[]
        {
        		0,0,
        		0,2,
        		2,2,
        		
        		2,2,
        		2,0,
        		0,0
        };
        //�������ݵĳ�ʼ��------end
        //�����������ݵĳ�ʼ��-------begin
        //����ռ�
        ByteBuffer tbb = ByteBuffer.allocateDirect(textures.length*4);
        //�����ֽ�˳��
        tbb.order(ByteOrder.nativeOrder());
        //ת��ΪFloat�ͻ���
        mTextureBuffer= tbb.asFloatBuffer();
        //�򻺳����з��붥����������
        mTextureBuffer.put(textures);
        //���û�������ʼλ��
        mTextureBuffer.position(0);
        //���ڲ�ͬƽ̨�ֽ�˳��ͬ���ݵ�Ԫ�����ֽڵ�һ��Ҫ����ByteBuffer
        //ת�����ؼ���Ҫͨ��ByteOrder����nativeOrder()�������п��ܻ������
        //�����������ݵĳ�ʼ��--------end
        
        //����ĳ�ʼ��------begin
        float normals[]=new float[vCount*3];
        for(int i=0;i<vCount;i++)
        {
        	normals[i*3]=0;
        	normals[i*3+1]=1;
        	normals[i*3+2]=0;
        }
        //����ռ�
        ByteBuffer nbb = ByteBuffer.allocateDirect(normals.length*4);
        //�����ֽ�˳��
        nbb.order(ByteOrder.nativeOrder());
        //ת��Ϊfloat�ͻ���
        mNormalBuffer = nbb.asFloatBuffer();
        //�򻺳����з��붥�㷨��������
        mNormalBuffer.put(normals);
        //���û�������ʼλ��
        mNormalBuffer.position(0);
        //���㷨�������ݵĳ�ʼ��-------------end              
    }
    //���Ƶذ�
    public void drawSelf(GL10 gl,int texId)
    {              
		//Ϊ����ָ��������������
        gl.glVertexPointer
        (
        		3,				//ÿ���������������Ϊ3�� xyz 
        		GL10.GL_FLOAT,	//��������ֵ������Ϊ GL_FLOAT
        		0, 				//����������������֮��ļ��
        		mVertexBuffer	//������������
        );      
        
        //Ϊ����ָ������ST���껺��
        gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, mTextureBuffer);
        //�󶨵�ǰ����
        gl.glBindTexture(GL10.GL_TEXTURE_2D, texId);
        //���÷�����
        gl.glNormalPointer(GL10.GL_FLOAT, 0, mNormalBuffer);
        //����ͼ��
        gl.glDrawArrays
        (
        		GL10.GL_TRIANGLES, 		//�������η�ʽ���
        		0, 			 			//��ʼ����
        		vCount					//���������
        );
    }
}