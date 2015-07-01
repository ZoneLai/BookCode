package wyf.jsl.lb;

import static wyf.jsl.lb.Constant.*;

//����ɽ�ص�����ײ���Ĺ�����
public class CollectionUtil 
{
	//�ж�һ�����Ƿ����������ڵķ���
	//�����㷨˼����������Ҫ���жϵĵ㵽���������������ʸ��1��2��3
	//Ȼ������ʸ�����������������ͬ�����λ���������ڣ�����λ����������
	public static boolean isInTriangle
	(
			//�����ε�һ�����XY����
			float x1,
			float y1,
			//�����εڶ������XY����
			float x2,
			float y2,
			//�����ε��������XY����
			float x3,
			float y3,
			//���жϵ��XY����
			float dx,
			float dy
	)
	{
		//���жϵ㵽�����ε�һ�����ʸ��
		float vector1x=dx-x1;
		float vector1y=dy-y1;
		
		//���жϵ㵽�����εڶ������ʸ��
		float vector2x=dx-x2;
		float vector2y=dy-y2;
		
		//���жϵ㵽�����ε��������ʸ��
		float vector3x=dx-x3;
		float vector3y=dy-y3;
		
		//�����1��2ʸ�������
		float crossProduct1=vector1x*vector2y-vector1y*vector2x;
		
		//�����2��3ʸ�������
		float crossProduct2=vector2x*vector3y-vector2y*vector3x;
		
		//�����3��1ʸ�������
		float crossProduct3=vector3x*vector1y-vector3y*vector1x;
		
		if(crossProduct1<0&&crossProduct2<0&&crossProduct3<0)
		{//���������ͬ�ŷ���true
			return true;
		}
		
		if(crossProduct1>0&&crossProduct2>0&&crossProduct3>0)
		{//���������ͬ�ŷ���true
			return true;
		}
		
		return false;
	}
	
	//������������0��1��2ȷ����ƽ����ָ��XZ���괦�ĸ߶�
	//�����㷨˼�룬�������0�ŵ㵽1��2�ŵ��ʸ��
	//Ȼ��������ʸ�������õ�������ƽ��ķ�ʸ��{A,B,C}
	//����ͨ����ʸ����0�ŵ��������д��������ƽ��ķ���
	// A(x-x0)+B(y-y0)+c(z-z0)=0
	//Ȼ������Ƶ���ָ��xz���괦y����ֵ��ʽ
	//y=(C(z0-z)+A(x0-x))/B+y0;
	//���ͨ����ֵ��ʽ���ָ��xz���괦y��ֵ
	public static float fromXZToY
	(
		float tx0,float ty0,float tz0,//ȷ��ƽ��ĵ�0
		float tx1,float ty1,float tz1,//ȷ��ƽ��ĵ�1
		float tx2,float ty2,float tz2,//ȷ��ƽ��ĵ�2
		float ctx,float ctz//���ĵ�XZ����
	)
	{
		//���0�ŵ㵽1�ŵ��ʸ��
        float x1=tx1-tx0;
        float y1=ty1-ty0;
        float z1=tz1-tz0;
        //���0�ŵ㵽2�ŵ��ʸ��
        float x2=tx2-tx0;
        float y2=ty2-ty0;
        float z2=tz2-tz0;
        //�������ʸ�����ʸ����XYZ��ķ���ABC
        float A=y1*z2-y2*z1;
        float B=z1*x2-z2*x1;
        float C=x1*y2-x2*y1;
        //ͨ����ֵ��ʽ��ָ��xz����yֵ
		float yResult=(C*(tz0-ctz)+A*(tx0-ctx))/B+ty0;
		//���ؽ��
		return yResult;
	}
	
	//�жϵ�ǰ���壨���ӵ����ڹ�ͷ�ȣ�����λ�õ�Y�����Ƿ���ڵ�ǰ�����Ӧ��Ŀ�����壨��ɽ�أ���ˮ�ȣ���Y����
	public static boolean isBulletCollectionsWithLand
	(
			float tempbx,//��ǰ����X����
			float tempby,//��ǰ����Y����
			float tempbz//��ǰ����Z����
	)
	{		
	    //�����ڵ���XZ����
	    float ctx=tempbx;
	    float ctz=tempbz;
	    //�����ڵ���Ӧ��½�ظ��ӵ��С���
	    int tempCol=(int)((ctx+(UNIT_SIZE*COLS/2))/UNIT_SIZE);
	    int tempRow=(int)((ctz+(UNIT_SIZE*ROWS/2))/UNIT_SIZE);
	    if(tempCol<0||tempCol>128||tempRow<0||tempRow>100)//�ڵ�����½��
	    {
	    	return false;
	    }
	    //�����ڵ���Ӧ��½�ظ��ӵ��ĸ��������
	    float x0=-UNIT_SIZE*COLS/2+tempCol*UNIT_SIZE;
	    float z0=-UNIT_SIZE*ROWS/2+tempRow*UNIT_SIZE; 
	    float y0=yArray[tempRow][tempCol];
	    
	    float x1=x0+UNIT_SIZE;
	    float z1=z0;
	    float y1=yArray[tempRow][tempCol+1];
	    
	    float x2=x0+UNIT_SIZE;
        float z2=z0+UNIT_SIZE;
        float y2=yArray[tempRow+1][tempCol+1];
    
	    float x3=x0;
	    float z3=z0+UNIT_SIZE;
	    float y3=yArray[tempRow+1][tempCol];
    
	    //�ڵ�����½�ظ߶�
	    float cty=0;
	    
	    if(isInTriangle(x0,z0,x1,z1,x3,z3,ctx,ctz))
	    {//�ж��ڵ��Ƿ�λ��0-1-3������
	    	//��0-1-3�����ڵ���½�صĸ߶�
	    	cty=fromXZToY
		    (
			    	x0,y0,z0,
			    	x1,y1,z1,
			    	x3,y3,z3,
			    	ctx,ctz
			 );
	    }
	    else
	    {
	    	//��1-2-3�����ڵ���½�صĸ߶�
	    	cty=fromXZToY
		    (
			    	x1,y1,z1,
			    	x2,y2,z2,
			    	x3,y3,z3,
			    	ctx,ctz
			);
	    }	    
	    if(cty>tempby)
	    {//���ڵ�����½�ظ����ڵ��򷵻�true
	    	return true;
	    }	    
	    return false;//����ǰ�����Ӧ��½�ظ߶ȵ���ˮ��߶ȣ�����FALSE
	}
	
	//���ص�ǰ�����Ӧ½�صĸ߶�
	public static float getLandHeight(float tempbx,float tempbz)
	{
		//�����ڵ���XZ����
	    float ctx=tempbx;
	    float ctz=tempbz;
	    //�����ڵ���Ӧ��½�ظ��ӵ��С���
	    int tempCol=(int)((ctx+(UNIT_SIZE*COLS/2))/UNIT_SIZE);
	    int tempRow=(int)((ctz+(UNIT_SIZE*ROWS/2))/UNIT_SIZE);
	  //�����ڵ���Ӧ��½�ظ��ӵ��ĸ��������
	    float x0=-UNIT_SIZE*COLS/2+tempCol*UNIT_SIZE;
	    float z0=-UNIT_SIZE*ROWS/2+tempRow*UNIT_SIZE; 
	    float y0=yArray[tempRow][tempCol];
	    
	    float x1=x0+UNIT_SIZE;
	    float z1=z0;
	    float y1=yArray[tempRow][tempCol+1];
	    
	    float x2=x0+UNIT_SIZE;
        float z2=z0+UNIT_SIZE;
        float y2=yArray[tempRow+1][tempCol+1];
    
	    float x3=x0;
	    float z3=z0+UNIT_SIZE;
	    float y3=yArray[tempRow+1][tempCol];
    
	    //�ڵ�����½�ظ߶�
	    float cty=0;
	    
	    if(isInTriangle(x0,z0,x1,z1,x3,z3,ctx,ctz))
	    {//�ж��ڵ��Ƿ�λ��0-1-3������
	    	//��0-1-3�����ڵ���½�صĸ߶�
	    	cty=fromXZToY
		    (
			    	x0,y0,z0,
			    	x1,y1,z1,
			    	x3,y3,z3,
			    	ctx,ctz
			 );
	    }
	    else
	    {
	    	//��1-2-3�����ڵ���½�صĸ߶�
	    	cty=fromXZToY
		    (
			    	x1,y1,z1,
			    	x2,y2,z2,
			    	x3,y3,z3,
			    	ctx,ctz
			);
	    }
	    return cty;
	}
	
	//��������񻯣��󳤶�
	public static float getVectorLength(float x,float y,float z)
	{
		float pingfang=x*x+y*y+z*z;
		float length=(float) Math.sqrt(pingfang);
		return length;
	}
	
}
