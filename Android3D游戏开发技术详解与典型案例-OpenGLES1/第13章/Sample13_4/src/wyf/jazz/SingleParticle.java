package wyf.jazz;

import javax.microedition.khronos.opengles.GL10;

//��������ϵͳ�е�ĳ������
public class SingleParticle {
	int particleForDrawIndex;//��Ӧ�������ӵı��
	float vx;//x���ٶȷ���
	float vy;//y���ٶȷ���
	float vz;//z���ٶȷ���
	float timeSpan=0;//�ۼ�ʱ��
	
	public SingleParticle(int particleForDrawIndex,float vx,float vy,float vz)
	{
		this.particleForDrawIndex=particleForDrawIndex;
		this.vx=vx;
		this.vy=vy;
		this.vz=vz;		
	}
	
	public void drawSelf(GL10 gl)
	{
		gl.glPushMatrix();		
		//���ݵ�ǰʱ������������λ��
		float x=vx*timeSpan;
		float z=vz*timeSpan;
		float y=vy*timeSpan-0.5f*timeSpan*timeSpan*1.0f;		
		gl.glTranslatef(x, y, z);
		//��������
		FireWorks.pfdArray[particleForDrawIndex].drawSelf(gl);
		gl.glPopMatrix();
	}
}
