package wyf.jazz;

import java.util.ArrayList;

import javax.microedition.khronos.opengles.GL10;

//�����������ϵͳ����
public class FireWorks {
	 //���ڻ��Ƶĸ�����ɫ������ɵ�����
     static ParticleForDraw[] pfdArray=new ParticleForDraw[]
     {
    	 new ParticleForDraw(2,0.9882f,0.9882f,0.8784f,0),
    	 new ParticleForDraw(2,0.9216f,0.2784f,0.2392f,0),
    	 new ParticleForDraw(2,1.0f,0.3686f,0.2824f,0),
    	 new ParticleForDraw(2,0.8157f,0.9882f,0.6863f,0),
    	 new ParticleForDraw(2,0.9922f,0.7843f,0.9882f,0),
    	 new ParticleForDraw(2,0.1f,1,0.3f,0)    	 
     };
     
     //����������ӵ��б�
     ArrayList<SingleParticle> al=new ArrayList<SingleParticle>();
     //��ʱ�˶�����������ӵ��߳� 
     FireWorksThread fwt;
     public FireWorks()
     {
    	 //��ʼ����ʱ�˶�����������ӵ��̲߳�����
    	 fwt=new FireWorksThread(this);
    	 fwt.start();
     }
     
     public void drawSelf(GL10 gl)
     {
		 int size=al.size();
		 //ѭ��ɨ������������ӵ��б����Ƹ�������
		 for(int i=0;i<size;i++)
    	 {
			 try
	    	 {
    		   al.get(i).drawSelf(gl);
	    	 }
			 catch(Exception e)
	    	 {
				e.printStackTrace();
	    	 }
    	 } 
     }
}
