package wyf.tzz.path;

import java.util.*;

public class Path {

	static float xBoundary = 3f;		//��Ļ����߽�
	static float yBoundary = 2f;		//��Ļ����߽�
	
	static int totalPath=10;			//��Ҫ��·�ߵ�������
	static int totalPoint=4;			//ÿ��·�ߵĵ���
	
	static float lastValue=0;

	static float [][] myPath=new float[2][totalPath*totalPoint];		//�洢·�ߵ�����


    public Path() {
    }
    
    public static float getInnerPoint(float boudary,float span)		//�����Ļ�ڵĵ�ķ���
    {
		float result=0;
		while(true)
		{
			result=(int)((boudary*2*Math.random()-boudary)*1000)/1000.0f;	//��������������Ļ�ڵĵ�����
			if(Math.abs(lastValue-result)>span)					//����һ�εõ��ĵ�Ƚϣ�������̫С�����¼���
			{
				lastValue=result;								
				break;
			}
		}
		
		return result;
    }
    
   
    
    static public float getOuterPoint(float boudary)			//�����Ļ��ĵ�ķ���
    {	
    	float result=0;
    	result=(int)(Math.signum((Math.random()-0.5f))*1.05f*boudary*1000)/1000.0f;	//��������������Ļ��ĵ�����
    	return  result;
    }
    
    public static void main(String[] args)
    {
    
    	int index=0;	//·����������
    	
    	
    	for(int j=0;j<totalPath;j++)//���·�����е��x����
		{
    		myPath[0][index++]=getOuterPoint(xBoundary*2);//��һ��������Ļ��
    		myPath[0][index++]=getInnerPoint(xBoundary,1.5f);//�ڶ���������Ļ��
    		myPath[0][index++]=getInnerPoint(xBoundary,1.5f);//������������Ļ��
    		myPath[0][index++]=getOuterPoint(xBoundary*2);   //���ĸ�������Ļ�� 	
    	}
    
    	for(int i=0;i<myPath[0].length;i++)		//���·�����е��x����
    	{
    			myPath[1][i]=getInnerPoint(yBoundary,2f);//·�����е��y��������Ļ��
    	
    	}
	
    	
    	System.out.println("public final static float[][] path={");
    	for(int j=0;j<myPath.length;j++)
    	{
    		System.out.print("{");
    		for(int i=0;i<myPath[j].length;i++)
	    	{ 
	    		System.out.print(myPath[j][i]+"f,");	//��ӡ·������
	    	}
	    	System.out.println("},");
    	}
    	System.out.print("};");
    }
    
}