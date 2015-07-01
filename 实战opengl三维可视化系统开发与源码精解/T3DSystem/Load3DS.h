 
 

#if !defined(AFX_LOAD3DS_H__69E7E7AC_7A07_4479_9687_AC19CED0E3CF__INCLUDED_)
#define AFX_LOAD3DS_H__69E7E7AC_7A07_4479_9687_AC19CED0E3CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vector.h"
 
#include <vector>
using namespace std;


 
//  ������(Primary Chunk)��λ���ļ��Ŀ�ʼ
#define PRIMARY       0x4D4D

//  ����(Main Chunks)
#define OBJECTINFO    0x3D3D				// �������İ汾��
#define VERSION       0x0002				// .3ds�ļ��İ汾
#define EDITKEYFRAME  0xB000				// ���йؼ�֡��Ϣ��ͷ��

 
//  ����Ĵμ�����(��������Ĳ��ʺͶ���
#define MATERIAL	  0xAFFF				// ����������Ϣ
#define OBJECT		  0x4000				// ���������桢�������Ϣ

 
//  ���ʵĴμ�����
#define MATNAME       0xA000				// �����������
#define MATDIFFUSE    0xA020				// ����/���ʵ���ɫ
#define MATMAP        0xA200				// �²��ʵ�ͷ��
#define MATMAPFILE    0xA300				// ����������ļ���
 
//  ���ʵĹ��ն���
#define  MAT_AMBIENT  0xA010
#define  MAT_SPECULAR 0xA030
#define  MAT_EMISSIVE 0xA040
 
#define OBJECT_MESH   0x4100			// �µ��������	
 
//  OBJECT_MESH�Ĵμ�����
#define OBJECT_VERTICES     0x4110			// ���󶥵�
#define OBJECT_FACES		0x4120			// �������
#define OBJECT_MATERIAL		0x4130			// ����Ĳ���
#define OBJECT_UV			0x4140			// �����UV��������


 

// CLoad3DS�ദ�����е�װ�����
class CLoad3DS
{
 
public:
	
	
	struct tIndices {							

		unsigned short a, b, c, bVisible;		
	};

	// �������Ϣ�Ľṹ
	struct tChunk
	{
		unsigned short int ID;					// ���ID		
		unsigned int length;					// ��ĳ���
		unsigned int bytesRead;					// ��Ҫ���Ŀ����ݵ��ֽ���
	};

	// ��������Ϣ�Ľṹ
	struct tFace
	{
		int vertIndex[3];			// ��������
		int coordIndex[3];			// ������������
	};

	// ���������Ϣ�Ľṹ��
	struct tMaterialInfo
	{
		char  strName[255];		// ��������	
		char  strFile[255];		// �����������ӳ�䣬���ʾ�����ļ�����	
		
		BYTE  color[3];			// �����RGB��ɫ	
		
		float  ambient[4];		//���ʵĻ�����		
		float  diffuse[4];		//���ʵĳ����		
		float  specular[4];		//���ʵľ����		
		float  emissive[4];		//���ʵ��������		
		
		int   texureId;			// ����ID	
		float uTile;			// u �ظ�	
		float vTile;			// v �ظ�	
		float uOffset;			// u ����ƫ��   
		float vOffset;			// v ����ƫ��	
	} ;
						
	
	class tMatREF
	{
	public:
		int nMaterialID;
		USHORT *pFaceIndexs;
		int nFaceNum;
		bool bHasTexture;
	public:
		tMatREF()
		{
			nMaterialID=-1;
			nFaceNum=0;
			pFaceIndexs=NULL;
			bHasTexture=false;
		}
	};

	
	
	// ������Ϣ�Ľṹ
	struct t3DObject 
	{
		int  numOfVerts;			// ģ���ж������Ŀ
		int  numOfFaces;			// ģ���������Ŀ
		int  numTexVertex;			// ģ���������������Ŀ
		int  numOfMaterials;         // ģ���в��ʵ���Ŀ
		int  materialID;			// ����ID
		bool bHasTexture;			// �Ƿ��������ӳ��
		char strName[255];			// ���������
		CVector3  *pVerts;			// ����Ķ���
		CVector3  *pNormals;		// ����ķ�����
		CVector2  *pTexVerts;		// ����UV����
		tFace *pFaces;				// ���������Ϣ
		tMatREF	      *pMaterialREFS;
		double m_minX;  //�������Сx����
		double m_maxX;	//��������x����
		double m_minY;	//�������Сy����
		double m_maxY;	//��������y����
		double m_minZ;	//�������Сz����
		double m_maxZ;	//��������z����
	};

	//  ģ����Ϣ�ṹ��
	struct t3DModel 
	{
		int numOfObjects;			// ģ���ж������Ŀ		
		int numOfMaterials;			// ģ���в��ʵ���Ŀ		
		vector<tMaterialInfo> vctMaterials;	// ����������Ϣ
		vector<t3DObject> vctObjects;		// ģ���ж���������Ϣ
	};

public:
	void Bytes2Floats(BYTE *pbs,float *pfs,int num,float fsk);//�ֽ����鵽����ת�� 	
	
	CLoad3DS();			// ��ʼ�����ݳ�Ա						
	
	~CLoad3DS();
	bool Import3DS(t3DModel *pModel, char *strFileName);// װ��3ds�ļ���ģ�ͽṹ��
private:
	int GetString(char *);//����һ���ַ���
	void ReadChunk(tChunk *);//������ID�ź������ֽڳ���
	void ProcessNextChunk(t3DModel *pModel, tChunk *);//����3ds�ļ�����Ҫ����(�Ǹ��ݹ麯��)
	void ProcessNextObjectChunk(t3DModel *pModel, t3DObject *pObject, tChunk *);//�������е��ļ��ж������Ϣ
	void ProcessNextMaterialChunk(t3DModel *pModel, tChunk *);//�������еĲ�����Ϣ
	void ReadColorChunk(tMaterialInfo *pMaterial, tChunk *pChunk,USHORT typeFlag=0);// ��������ɫ��RGBֵ
	void ReadVertices(t3DObject *pObject, tChunk *);	// ������Ķ���
	void ReadVertexIndices(t3DObject *pObject, tChunk *);// �����������Ϣ
	void ReadUVCoordinates(t3DObject *pObject, tChunk *);	// ���������������
	void ReadObjectMaterial(t3DModel *pModel, t3DObject *pObject, tChunk *pPreviousChunk,vector<tMatREF*> *pvmatids);	// ���������Ĳ�������
	void ComputeNormals(t3DModel *pModel);// ������󶥵�ķ�����
	void CleanUp();// �ر��ļ����ͷ��ڴ�ռ�
	
	FILE *m_FilePointer;// �ļ�ָ��
};


#endif // !defined(AFX_LOAD3DS_H__69E7E7AC_7A07_4479_9687_AC19CED0E3CF__INCLUDED_)
