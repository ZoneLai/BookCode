package wyf.jazz;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.IntBuffer;

import javax.microedition.khronos.opengles.GL10;

//���ڻ��Ƶ������ӵ���
public class ParticleForDraw {
	private FloatBuffer   mVertexBuffer;//�����������ݻ���
	private IntBuffer   mColorBuffer;//������ɫ���ݻ���
    float scale;//���ӳߴ�
    
    public ParticleForDraw(float scale,float r,float g,float b,float a)
    {
    	this.scale=scale;
    	
    	//�����������ݵĳ�ʼ��================begin=======================================       
        float vertices[]=new float[]//��������ֵ����
        {
        	0f,0f,0f	
        };
		
        //���������������ݻ���
        //vertices.length*4����Ϊһ��Float�ĸ��ֽ�
        ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length*4);
        vbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
        mVertexBuffer = vbb.asFloatBuffer();//ת��Ϊint�ͻ���
        mVertexBuffer.put(vertices);//�򻺳����з��붥����������
        mVertexBuffer.position(0);//���û�������ʼλ��
        //�ر���ʾ�����ڲ�ͬƽ̨�ֽ�˳��ͬ���ݵ�Ԫ�����ֽڵ�һ��Ҫ����ByteBuffer
        //ת�����ؼ���Ҫͨ��ByteOrder����nativeOrder()�������п��ܻ������
        //�����������ݵĳ�ʼ��================end============================ 
        
        //������ɫ���ݵĳ�ʼ��================begin============================
        final int one = 65535;
        int colors[]=new int[]//������ɫֵ���飬ÿ������4��ɫ��ֵRGBA
        {
             (int)(one*r),
             (int)(one*g),
             (int)(one*b),
             (int)(one*a),
        };
        
        //����������ɫ���ݻ���
        //vertices.length*4����Ϊһ��int�������ĸ��ֽ�
        ByteBuffer cbb = ByteBuffer.allocateDirect(colors.length*4);
        cbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
        mColorBuffer = cbb.asIntBuffer();//ת��Ϊint�ͻ���
        mColorBuffer.put(colors);//�򻺳����з��붥����ɫ����
        mColorBuffer.position(0);//���û�������ʼλ��
        //�ر���ʾ�����ڲ�ͬƽ̨�ֽ�˳��ͬ���ݵ�Ԫ�����ֽڵ�һ��Ҫ����ByteBuffer
        //ת�����ؼ���Ҫͨ��ByteOrder����nativeOrder()�������п��ܻ������
        //������ɫ���ݵĳ�ʼ��================end============================
    }

    public void drawSelf(GL10 gl)
    {        
        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);//���ö�����������
        gl.glEnableClientState(GL10.GL_COLOR_ARRAY);//���ö�����ɫ����

        gl.glPointSize(scale);//����������ӳߴ�
        
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
        		GL10.GL_FIXED, 	//������ɫֵ������Ϊ GL_FIXED
        		0, 				//����������ɫ����֮��ļ��
        		mColorBuffer	//������ɫ����
        );
		
        //���� ��
        gl.glDrawArrays
        (
        		GL10.GL_POINTS, 		//�Ե㷽ʽ���
        		0, 			 			//��ʼ����
        		1					//���������
        );
        
        gl.glPointSize(1);//�ָ����سߴ�
        gl.glDisableClientState(GL10.GL_COLOR_ARRAY);//���ö�����ɫ����
    }
}
