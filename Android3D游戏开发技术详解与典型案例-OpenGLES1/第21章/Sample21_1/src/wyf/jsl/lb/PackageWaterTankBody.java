package wyf.jsl.lb;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.opengles.GL10;

public class PackageWaterTankBody {
	private FloatBuffer   mVertexBuffer;//�����������ݻ���
    private FloatBuffer   mTexBuffer;//������ɫ���ݻ���
    int vCount=0;//��������    
    float yAngle=0;//��y����ת�ĽǶ�
    float xAngle=0;//��z����ת�ĽǶ�    
    int texId;//����ID
    
    float hWidth;
    float hLength;
    float lWidth;
    float lLength;
    float height;
	
	public PackageWaterTankBody(float hWidth,float hLength,float lWidth,float lLength,float height,int texId)
	{
		this.height=height;
		this.hLength=hLength;
		this.hWidth=hWidth;
		this.lLength=lLength;
		this.lWidth=lWidth;
		this.texId=texId;//hWidth/2   hLength/2      lWidth/2     lLength/2
		
		//����
		vCount=36;
		float vertices[]=new float[]{
			-hWidth/2,height/2,-hLength/2,
			lWidth/2,-height/2,-lLength/2,
			-lWidth/2,-height/2,-lLength/2,
			
			-hWidth/2,height/2,-hLength/2,
			hWidth/2,height/2,-hLength/2,
			lWidth/2,-height/2,-lLength/2,
			
			-lWidth/2,-height/2,-lLength/2,
			-lWidth/2,-height/2,lLength/2,
			-hWidth/2,height/2,hLength/2,
			
			-lWidth/2,-height/2,-lLength/2,
			-hWidth/2,height/2,hLength/2,
			-hWidth/2,height/2,-hLength/2,
			
			-hWidth/2,height/2,-hLength/2,
			-hWidth/2,height/2,hLength/2,
			hWidth/2,height/2,hLength/2,
			
			-hWidth/2,height/2,-hLength/2,
			hWidth/2,height/2,hLength/2,
			hWidth/2,height/2,-hLength/2,
			
			hWidth/2,height/2,-hLength/2,
			hWidth/2,height/2,hLength/2,
			lWidth/2,-height/2,lLength/2,
			
			hWidth/2,height/2,-hLength/2,
			lWidth/2,-height/2,lLength/2,
			lWidth/2,-height/2,-lLength/2,
			
			-hWidth/2,height/2,hLength/2,
			-lWidth/2,-height/2,lLength/2,
			lWidth/2,-height/2,lLength/2,
			
			-hWidth/2,height/2,hLength/2,
			lWidth/2,-height/2,lLength/2,
			hWidth/2,height/2,hLength/2,
			
			-lWidth/2,-height/2,lLength/2,
			-lWidth/2,-height/2,-lLength/2,
			lWidth/2,-height/2,lLength/2,
			
			-lWidth/2,-height/2,-lLength/2,
			lWidth/2,-height/2,-lLength/2,
			lWidth/2,-height/2,lLength/2
		};		
        ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length*4);
        vbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
        mVertexBuffer = vbb.asFloatBuffer();//ת��Ϊint�ͻ���
        mVertexBuffer.put(vertices);//�򻺳����з��붥����������
        mVertexBuffer.position(0);//���û�������ʼλ��

        //��������
        float[] texCoor=new float[]{
        	1,0,
        	0,1,
        	1,1,
        	
        	1,0,
        	0,0,
        	0,1,
        	
        	0,1,
        	1,1,
        	1,0,
        	
        	0,1,
        	1,0,
        	0,0,
        	
        	0,0,
        	0,1,
        	1,1,
        	
        	0,0,
        	1,1,
        	1,0,
        	
        	1,0,
        	0,0,
        	0,1,
        	
        	1,0,
        	0,1,
        	1,1,
        	
        	0,0,
        	0,1,
        	1,1,
        	
        	0,0,
        	1,1,
        	1,0,
        	
        	0,0,
        	0,1,
        	1,0,
        	
        	0,1,
        	1,1,
        	1,0
        };
        //���������������ݻ���
        ByteBuffer cbb = ByteBuffer.allocateDirect(texCoor.length*4);
        cbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
        mTexBuffer = cbb.asFloatBuffer();//ת��Ϊint�ͻ���
        mTexBuffer.put(texCoor);//�򻺳����з��붥����ɫ����
        mTexBuffer.position(0);//���û�������ʼλ��
	}
	
	public void drawSelf(GL10 gl)
	{		
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);//���ö�����������       		
        gl.glVertexPointer//Ϊ����ָ��������������
        (
        		3,				//ÿ���������������Ϊ3  xyz 
        		GL10.GL_FLOAT,	//��������ֵ������Ϊ GL_FIXED
        		0, 				//����������������֮��ļ��
        		mVertexBuffer	//������������
        );
		
        //��������
        gl.glEnable(GL10.GL_TEXTURE_2D);   
        //����ʹ������ST���껺��
        gl.glEnableClientState(GL10.GL_TEXTURE_COORD_ARRAY);
        //Ϊ����ָ������ST���껺��
        gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, mTexBuffer);
        //�󶨵�ǰ����
        gl.glBindTexture(GL10.GL_TEXTURE_2D, texId);
		
        //����ͼ��
        gl.glDrawArrays
        (
        		GL10.GL_TRIANGLES, 		//�������η�ʽ���
        		0, 			 			//��ʼ����
        		vCount					//���������
        );
	}
}
