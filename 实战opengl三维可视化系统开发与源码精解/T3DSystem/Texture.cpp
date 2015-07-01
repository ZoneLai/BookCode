#include "stdafx.h"
#include  "texture.h"

//��BMP�ļ���������,����������ID��
int CTexture::LoadGLTextures(char *Filename)									
{
	AUX_RGBImageRec *pImage = NULL;
	FILE *pFile = NULL; // �ļ����

	if (!Filename) // ȷ���ļ������ṩ��
	{
		return false; // ���û�ṩ������ false
	}
	
	if((pFile = fopen(Filename, "rb")) == NULL) //���Դ��ļ�
	{
		
		MessageBox(NULL, "���ܹ���BMP�����ļ�!", "��BMP�����ļ�ʧ��", MB_OK);
		MessageBox(NULL, Filename, "Error", MB_OK);
		return NULL;//���ļ�ʧ��,���� false
	}
	

	pImage = auxDIBImageLoad(Filename);	//��ȡͼ�����ݲ����䷵��(ʹ��glaux�����⺯��auxDIBImageLoad������λͼ)			
	if(pImage == NULL)	//�����ȡʧ��,����							
		return false;
	
	glGenTextures(1, &m_nTxt); // ��������,����OpenGL����������һ����������(������������������Ӵ�����)��
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, m_nTxt);// ʹ������λͼ�������� �ĵ�������
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, pImage->sizeX, 
					  pImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
	//pImage->data:����OpenGL�������ݵ���Դ������ָ������pImage->data�е����ݡ�
	//gluBuild2DMipmaps()����glTexImage2D(),�����������������С��ͼƬ
	/*
	gluBuild2DMipmaps()��glTexImage2D()��ʹ�÷���������2008��08��02�� ������ ���� 10:53glTexImage2D()���÷�����
	
	  glTexImage2D(GL_TEXTURE_2D, //��������һ��2D����
	  0,                                         //����ͼ�����ϸ�̶�, Ĭ��Ϊ0���� 
	  3,                                         //��ɫ�ɷ�R(��ɫ����)��G(��ɫ����)��B(��ɫ����)�����֣���Ϊ4����R(��ɫ����)��G(��ɫ����)��B(��ɫ����)��Alpha
	  TextureImage[0]->sizeX,          //����Ŀ��
	  TextureImage[0]->sizeY,          //����ĸ߶�
	  0,                                         //�߿��ֵ
	  GL_RGB,                               //����OpenGLͼ�������ɺ졢�̡�����ɫ�������
	  GL_UNSIGNED_BYTE,                //���ͼ����������޷����ֽ�����
	  TextureImage[0]->data);          //����OpenGL�������ݵ���Դ,������ָ������TextureImage[0]��¼�е�����
	  
		
		  gluBuild2DMipmaps()���÷�����
		  
			gluBuild2DMipmaps(GL_TEXTURE_2D,//��������һ��2D����
			3,                                             //��ɫ�ɷ�R(��ɫ����)��G(��ɫ����)��B(��ɫ����)�����֣���Ϊ4����R(��ɫ����)��G(��ɫ����)��B(��ɫ����)��Alpha
			TextureImage[0]->sizeX,               //����Ŀ��
			TextureImage[0]->sizeY,               //����ĸ߶�
			GL_RGB,                                      //����OpenGLͼ�������ɺ졢�̡�����ɫ�������
			GL_UNSIGNED_BYTE,                     //���ͼ����������޷����ֽ�����
			TextureImage[0]->data);             //����OpenGL�������ݵ���Դ,������ָ������TextureImage[0]��¼�е�����
			
			  
				ʹ��ע������
				
				  ʹ��glTexImage2D()ʱ�����õ�λͼ�ļ��ֱ��ʱ���Ϊ��64��64��128��128��256��256���ָ�ʽ�����������С�����ֻ��Ʋ�������
					
	*/
	// ��������ģʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);// ˫�߹���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);// ˫�߹���
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);//��Ե��ȡ,���Ǻ��Ա߽�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);//��Ե��ȡ,���Ǻ��Ա߽�
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);	
	if (pImage)		// �����Ƿ����							
	{
		if (pImage->data)	 // ����ͼ���Ƿ����						
		{
			free(pImage->data);	 // �ͷ�����ͼ��ռ�õ��ڴ�					
		}

		free(pImage);	// �ͷ�ͼ��ṹ							
	}
	fclose(pFile);// �ر��ļ�
	return m_nTxt;//��������ID��

}
bool CTexture::MakeTextureBind(char* TextureFileName,bool bLinear,bool bMip)
{
	bool status=true;			
	AUX_RGBImageRec *Image=NULL;	

     
	if (Image=auxDIBImageLoad(TextureFileName))
	{					
		glGenTextures(1, &m_nTxt);		
   		glBindTexture(GL_TEXTURE_2D, m_nTxt);
        if(bLinear)
		{
			if(bMip)
			{
 
 
 	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	    	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, Image->sizeX, Image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, Image->data);
			}
			else
			{
                glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
                glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, Image->sizeX, Image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Image->data);				
			}
		}
		else
		{
			if(bMip)
			{
 	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	    	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, Image->sizeX, Image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, Image->data);
			}
			else
			{
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, Image->sizeX, Image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Image->data);				
			}
		}
	}
	else status=false;
	if (Image) {											
		if (Image->data) delete Image->data;				
		delete Image;
	}
	return status;				
}



bool CTexture::MakeSkinTextureBind(char* TextureFileName,
							   bool bLinear,bool bMip)
{
	bool state=true;			
	unsigned char *Image=new unsigned char [256*256*3];	
	FILE* file;
    if((file= fopen(TextureFileName, "rb"))==NULL)
	{
	    state=false;
		return state;
	}
	char id[10],version;
	fread(id,     sizeof(char),10,  file);
	fread(&version,sizeof(char),1,  file);
	if ( strncmp( id, "Hunter3D00", 10 ) != 0 )
	{
		    fclose(file);
		    return false; 
	}
	if ( version !=1 )
	{
	    fclose(file);
	    return false; 
	}	

	fread(Image,sizeof(unsigned char),256*256*3,file);

    fclose(file);
    file=NULL;
				
	glGenTextures(1, &m_nTxt);		
	glBindTexture(GL_TEXTURE_2D, m_nTxt);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    if(bLinear)
	{
		if(bMip)
			{
 	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	    	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, Image);
			}
			else
			{
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8,256,256, 0, GL_RGB, GL_UNSIGNED_BYTE, Image);				
			}
	}
	else
	{
			if(bMip)
			{
 	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST);
	    	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB8, 256, 256, GL_RGB, GL_UNSIGNED_BYTE, Image);
			}
			else
			{
                glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	    		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    	        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 256,256, 0, GL_RGB, GL_UNSIGNED_BYTE, Image);				
			}
	}

    delete [] Image;				
	return state;				
}
 
bool CTexture::MakeAlphaTextureBind(char* TextureFileName)
{
	bool status=true;												
	AUX_RGBImageRec *Image=NULL;									
	unsigned char *alpha=NULL;

	
	if (Image=auxDIBImageLoad(TextureFileName)) 
	{							
		alpha=new unsigned char[4*Image->sizeX*Image->sizeY];		
		for (int a=0; a<Image->sizeX*Image->sizeY; a++)
		{
			alpha[4*a]=Image->data[a*3];					
			alpha[4*a+1]=Image->data[a*3+1];				
			alpha[4*a+2]=Image->data[a*3+2];				
            
            alpha[4*a+3]=(alpha[4*a+0]<alpha[4*a+1])?alpha[4*a+0]:alpha[4*a+1];
            if(alpha[4*a+2]<alpha[4*a+3])alpha[4*a+3]=alpha[4*a+2];


		}

		
		glGenTextures(1, &m_nTxt);							

		
		glBindTexture(GL_TEXTURE_2D, m_nTxt);
   	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, Image->sizeX, Image->sizeY, GL_RGBA, GL_UNSIGNED_BYTE, alpha);
		delete [] alpha;
	}
	else status=false;
	if (Image) {											
		if (Image->data) delete Image->data;				
		delete Image;
		Image=NULL;
	}	
	
    return status;
}
bool CTexture::MakeAlphaTextureBind(char* TextureFileName,char *AlphaFileName)
{
	bool status=true;												
	AUX_RGBImageRec *Image=NULL;									
	unsigned char *alpha=NULL;

	
	if (Image=auxDIBImageLoad(TextureFileName)) 
	{							
		alpha=new unsigned char[4*Image->sizeX*Image->sizeY];		
		for (int a=0; a<Image->sizeX*Image->sizeY; a++)
		{
			alpha[4*a]=Image->data[a*3];					
			alpha[4*a+1]=Image->data[a*3+1];				
			alpha[4*a+2]=Image->data[a*3+2];				
		}
		
        if(AlphaFileName==NULL)return false;
	    FILE* file;
        if((file= fopen(AlphaFileName, "rb"))==NULL)
	      	return false;
		fseek(file,54,SEEK_SET);
		unsigned char temp[3];
		for ( a=0; a<Image->sizeX*Image->sizeY; a++)
		{
			fread(temp,sizeof(unsigned char),3,file);
            alpha[4*a+3]=(temp[0]>temp[1])?temp[0]:temp[1];
            if(temp[2]>alpha[4*a+3])alpha[4*a+3]=temp[2];
 
			if(alpha[4*a+3]>50)alpha[4*a+3]=255;
		}
		fclose(file);
		
		glGenTextures(1, &m_nTxt);							
		
		glBindTexture(GL_TEXTURE_2D, m_nTxt);
   	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA8, Image->sizeX, Image->sizeY, GL_RGBA, GL_UNSIGNED_BYTE, alpha);
		delete [] alpha;
	}
	else status=false;
	if (Image) {											
		if (Image->data) delete Image->data;				
		delete Image;
		Image=NULL;
	}	
	
    return status;
}




bool  CTexture::MakeScreenTextureBind()
{
 
	if(glIsTexture(m_nTxt)==GL_TRUE)
	{
 
 
	}
	else
	{
		GLint Viewport[4];
        glGetIntegerv(GL_VIEWPORT, Viewport);
		int newWidth=128;

        unsigned char *pData=new unsigned char[newWidth*newWidth*3+6]; 
		
		int sx,sy;  
        unsigned char temp[6];
		for(int y=0;y<newWidth;y++)
			for(int x=0;x<newWidth;x++)
			{
			    sx=int(float(x*Viewport[2])/newWidth);
			    sy=int(float(y*Viewport[3])/newWidth);

	        	glReadPixels(sx,sy,1,1,
			                 GL_RGB,GL_UNSIGNED_BYTE,temp);

                pData[y*newWidth*3+x*3+0]=unsigned char(temp[0]*0.8f);
                pData[y*newWidth*3+x*3+1]=unsigned char(temp[1]*0.8f);
                pData[y*newWidth*3+x*3+2]=unsigned char(temp[2]*0.8f);
			}

        
		glGenTextures(1, &m_nTxt);		
   		glBindTexture(GL_TEXTURE_2D, m_nTxt);

        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	 	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, newWidth,newWidth, 0, GL_RGB, GL_UNSIGNED_BYTE,pData);				

		delete [] pData;
	}
    return true;
}

typedef struct													
{
	GLubyte	*imageData;											
	GLuint	bpp;												
	GLuint	width;												
	GLuint	height;												
	GLuint	texID;												
} TextureImage;	
bool CTexture::LoadTGA(char *filename)				
{    
	TextureImage Texture;
	TextureImage *texture = &Texture;
	GLubyte		TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};		
	GLubyte		TGAcompare[12];									
	GLubyte		header[6];										
	GLuint		bytesPerPixel;									
	GLuint		imageSize;										
	GLuint		temp;											
	GLuint		type=GL_RGBA;									

	FILE *file = fopen(filename, "rb");							

	if(	file==NULL ||											
		fread(TGAcompare,1,sizeof(TGAcompare),file)!=sizeof(TGAcompare) ||	
		memcmp(TGAheader,TGAcompare,sizeof(TGAheader))!=0				||	
		fread(header,1,sizeof(header),file)!=sizeof(header))				
	{
		if (file == NULL)										
			return FALSE;										
		else													
		{
			fclose(file);										
			return FALSE;										
		}
	}

	texture->width  = header[1] * 256 + header[0];				
	texture->height = header[3] * 256 + header[2];				
    
 	if(	texture->width	<=0	||									
		texture->height	<=0	||									
		(header[4]!=24 && header[4]!=32))						
	{
		fclose(file);											
		return FALSE;											
	}

	texture->bpp	= header[4];								
	bytesPerPixel	= texture->bpp/8;							
	imageSize		= texture->width*texture->height*bytesPerPixel;	

	texture->imageData=(GLubyte *)malloc(imageSize);			

	if(	texture->imageData==NULL ||								
		fread(texture->imageData, 1, imageSize, file)!=imageSize)	
	{
		if(texture->imageData!=NULL)							
			free(texture->imageData);							

		fclose(file);											
		return FALSE;											
	}

	for(GLuint i=0; i<int(imageSize); i+=bytesPerPixel)			
	{															
		temp=texture->imageData[i];								
		texture->imageData[i] = texture->imageData[i + 2];		
		texture->imageData[i + 2] = temp;						
	}

	fclose (file);												

	
	glGenTextures(1, &texture[0].texID);						

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);				
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	
	if (texture[0].bpp==24)										
	{
		type=GL_RGB;											
	}
	m_nTxt = texture[0].texID;
	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);
	free(texture[0].imageData);
	return true;												
}





















