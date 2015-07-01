package wyf.sj;
import java.util.ArrayList;
import javax.microedition.khronos.opengles.GL10;
import static wyf.sj.Constant.*;

public class CactusGroup {

	CactusForDraw cfd;//���ڻ��Ƶ��������ƵĶ�������
    ArrayList<SingleCactus> al=new ArrayList<SingleCactus>();//�������б�
    
    public CactusGroup(int texId)
    {
    	cfd=new CactusForDraw(texId);//��ʼ�����ڻ��Ƶ��������ƵĶ���
    	
    	//ɨ���ͼ���ɸ���λ�õ������ƶ���
    	for(int i=0;i<DESERT_ROWS;i++)
    	{
    		for(int j=0;j<DESERT_COLS;j++)
    		{
    			if(MAP_CACTUS[i][j]==0)
    			{
    				continue;
    			}
    			//������λ�õ������ƶ���
    			SingleCactus tempSc=new SingleCactus
    			(
    					(j+0.5f)*UNIT_SIZE,
    					(i+0.5f)*UNIT_SIZE,
    					0,
    					this
    			);
    			//�������ƶ�������������б�
    			al.add(tempSc);
    		}
    	}
    }
    
    public void calculateBillboardDirection()
    {
    	//�����б���ÿ�������Ƶĳ���
    	for(int i=0;i<al.size();i++)
    	{
    		al.get(i).calculateBillboardDirection();
    	}
    }
    
    public void drawSelf(GL10 gl)
    {//�����б��е�ÿ��������
    	for(int i=0;i<al.size();i++)
    	{
    		al.get(i).drawSelf(gl);
    	}
    }
}
