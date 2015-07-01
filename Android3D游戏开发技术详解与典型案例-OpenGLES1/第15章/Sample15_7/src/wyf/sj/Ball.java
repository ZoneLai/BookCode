package wyf.sj;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

import android.util.Log;
import static wyf.sj.Constant.*;
public class Ball extends BNShape{
	private FloatBuffer   mVertexBuffer;//�����������ݻ���
    private FloatBuffer mTextureBuffer;//�����������ݻ���
    int vCount=0;//��������
    float scale;//�ߴ�
    float mAngleY;//ת���Ƕ�
    int texId;//����ID
    float[] tempVerteices;
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

    public Ball(float scale,int texId,float xOffset,float yOffset,float zOffset) 
    {
    	this.scale=scale;    	
    	this.texId=texId;
    	this.xOffset=xOffset;
    	this.yOffset=yOffset;
    	this.zOffset=zOffset;
    	//��ȡ�з���ͼ����������
    	float[] texCoorArray= 
         generateTexCoor
    	 (
    			 (int)(360/ANGLE_SPAN), //����ͼ�зֵ�����
    			 (int)(180/ANGLE_SPAN)  //����ͼ�зֵ�����
    	);
        int tc=0;//�������������
        int ts=texCoorArray.length;//�������鳤��
    	
    	ArrayList<Float> alVertix=new ArrayList<Float>();//��Ŷ��������ArrayList
    	ArrayList<Float> alTexture=new ArrayList<Float>();//������������ArrayList
    	
        for(float vAngle=90;vAngle>-90;vAngle=vAngle-ANGLE_SPAN)//��ֱ����angleSpan��һ��
        {
        	for(float hAngle=360;hAngle>0;hAngle=hAngle-ANGLE_SPAN)//ˮƽ����angleSpan��һ��
        	{
        		//����������һ���ǶȺ�����Ӧ�Ĵ˵��������ϵ��ı��ζ�������
        		//��������������ı��ε�������
        		
        		double xozLength=scale*UNIT_SIZE*Math.cos(Math.toRadians(vAngle));
        		float x1=(float)(xozLength*Math.cos(Math.toRadians(hAngle)));
        		float z1=(float)(xozLength*Math.sin(Math.toRadians(hAngle)));
        		float y1=(float)(scale*UNIT_SIZE*Math.sin(Math.toRadians(vAngle)));
        		
        		xozLength=scale*UNIT_SIZE*Math.cos(Math.toRadians(vAngle-ANGLE_SPAN));
        		float x2=(float)(xozLength*Math.cos(Math.toRadians(hAngle)));
        		float z2=(float)(xozLength*Math.sin(Math.toRadians(hAngle)));
        		float y2=(float)(scale*UNIT_SIZE*Math.sin(Math.toRadians(vAngle-ANGLE_SPAN)));
        		
        		xozLength=scale*UNIT_SIZE*Math.cos(Math.toRadians(vAngle-ANGLE_SPAN));
        		float x3=(float)(xozLength*Math.cos(Math.toRadians(hAngle-ANGLE_SPAN)));
        		float z3=(float)(xozLength*Math.sin(Math.toRadians(hAngle-ANGLE_SPAN)));
        		float y3=(float)(scale*UNIT_SIZE*Math.sin(Math.toRadians(vAngle-ANGLE_SPAN)));
        		
        		xozLength=scale*UNIT_SIZE*Math.cos(Math.toRadians(vAngle));
        		float x4=(float)(xozLength*Math.cos(Math.toRadians(hAngle-ANGLE_SPAN)));
        		float z4=(float)(xozLength*Math.sin(Math.toRadians(hAngle-ANGLE_SPAN)));
        		float y4=(float)(scale*UNIT_SIZE*Math.sin(Math.toRadians(vAngle)));   
        		
        		//������һ������
        		alVertix.add(x1);alVertix.add(y1);alVertix.add(z1);
        		alVertix.add(x2);alVertix.add(y2);alVertix.add(z2);
        		alVertix.add(x4);alVertix.add(y4);alVertix.add(z4);        		
        		//�����ڶ�������
        		alVertix.add(x4);alVertix.add(y4);alVertix.add(z4);
        		alVertix.add(x2);alVertix.add(y2);alVertix.add(z2);
        		alVertix.add(x3);alVertix.add(y3);alVertix.add(z3); 
        		
        		//��һ������3�������6����������
        		alTexture.add(texCoorArray[tc++%ts]);
        		alTexture.add(texCoorArray[tc++%ts]);
        		alTexture.add(texCoorArray[tc++%ts]);        		
        		alTexture.add(texCoorArray[tc++%ts]);
        		alTexture.add(texCoorArray[tc++%ts]);
        		alTexture.add(texCoorArray[tc++%ts]);
        		//�ڶ�������3�������6����������
        		alTexture.add(texCoorArray[tc++%ts]);
        		alTexture.add(texCoorArray[tc++%ts]);
        		alTexture.add(texCoorArray[tc++%ts]);        		
        		alTexture.add(texCoorArray[tc++%ts]);
        		alTexture.add(texCoorArray[tc++%ts]);
        		alTexture.add(texCoorArray[tc++%ts]);       		
        	}
        } 	
        
        vCount=alVertix.size()/3;//���������Ϊ����ֵ������1/3����Ϊһ��������3������
    	
        //��alVertix�е�����ֵת�浽һ��float������
        float vertices[]=new float[vCount*3];
    	for(int i=0;i<alVertix.size();i++)
    	{
    		vertices[i]=alVertix.get(i);
    	}
        tempVerteices=vertices;
        //�������ƶ������ݻ���
        ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length*4);
        vbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
        mVertexBuffer = vbb.asFloatBuffer();//ת��Ϊfloat�ͻ���
        mVertexBuffer.put(vertices);//�򻺳����з��붥����������
        mVertexBuffer.position(0);//���û�������ʼλ��     
        
       
                
        //�����������껺��
        float textureCoors[]=new float[alTexture.size()];//��������ֵ����
        for(int i=0;i<alTexture.size();i++) 
        {
        	textureCoors[i]=alTexture.get(i);
        }
        
        ByteBuffer tbb = ByteBuffer.allocateDirect(textureCoors.length*4);
        tbb.order(ByteOrder.nativeOrder());//�����ֽ�˳��
        mTextureBuffer = tbb.asFloatBuffer();//ת��Ϊint�ͻ���
        mTextureBuffer.put(textureCoors);//�򻺳����з��붥����ɫ����
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
        //����ʹ�ö�������
        gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		//Ϊ����ָ��������������
        gl.glVertexPointer
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
        gl.glTexCoordPointer(2, GL10.GL_FLOAT, 0, mTextureBuffer);
        //�󶨵�ǰ����
        gl.glBindTexture(GL10.GL_TEXTURE_2D, texId);
        //����ͼ��
        gl.glDrawArrays
        (
        		GL10.GL_TRIANGLES, 		//�������η�ʽ���
        		0, 			 			//��ʼ����
        		vCount					//��������
        );        
        gl.glDisableClientState(GL10.GL_TEXTURE_COORD_ARRAY);//������������
        gl.glDisable(GL10.GL_TEXTURE_2D);//�ر�����
    }
    
    //�Զ��з����������������ķ���
    public float[] generateTexCoor(int bw,int bh)
    {
    	float[] result=new float[bw*bh*6*2]; 
    	float sizew=1.0f/bw;//����
    	float sizeh=1.0f/bh;//����
    	int c=0;
    	for(int i=0;i<bh;i++)
    	{
    		for(int j=0;j<bw;j++)
    		{
    			//ÿ����һ�����Σ������������ι��ɣ��������㣬12����������
    			float s=j*sizew;
    			float t=i*sizeh;
    			
    			result[c++]=s;
    			result[c++]=t;
    			
    			result[c++]=s;
    			result[c++]=t+sizeh;
    			
    			result[c++]=s+sizew;
    			result[c++]=t;
    			
    			
    			result[c++]=s+sizew;
    			result[c++]=t;
    			
    			result[c++]=s;
    			result[c++]=t+sizeh;
    			
    			result[c++]=s+sizew;
    			result[c++]=t+sizeh;    			
    		}
    	}
    	return result;
    }

	@Override
	public float[] findMid() {
		// TODO Auto-generated method stub
		midX=(minX+maxX)/2+xOffset;
		midY=(minY+maxY)/2+yOffset;
		midZ=(minZ+maxZ)/2+zOffset;
		Log.d("Ball midX=",""+midX);
		Log.d("Ball midY=",""+midY);
		Log.d("Ball midZ=",""+midZ);
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
		Log.d("Ball minX="+minX,"maxX="+(maxX-minX));
		Log.d("Ball minY="+minY,"maxY="+(maxY-minY));
		Log.d("Ball minZ="+minZ,"maxZ="+(maxZ-minZ));
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
