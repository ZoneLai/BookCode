// Load3DS.cpp: implementation of the CLoad3DS class.
 
#include "stdafx.h"
#include "Load3DS.h"

static int gBuffer[50000] = {0};					
 

CLoad3DS::CLoad3DS()
{
	m_FilePointer = NULL;
}

CLoad3DS::~CLoad3DS()
{
	m_FilePointer = NULL;
}

 
 
//  ��һ��3ds�ļ����������е����ݣ����ͷ��ڴ�
bool CLoad3DS::Import3DS(CLoad3DS::t3DModel *pModel, char *strFileName)
{
	char strMessage[255] = {0};
	tChunk currentChunk = {0};
	int i=0;

	// ��һ��3ds�ļ�
	m_FilePointer = fopen(strFileName, "rb");

	
	// ȷ������õ��ļ�ָ��Ϸ�
	if(!m_FilePointer) 
	{
		sprintf(strMessage, "�Ҳ����ļ�: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	// ���ļ���֮������Ӧ�ý��ļ��ʼ�����ݿ�������ж��Ƿ���һ��3ds�ļ�
	// �����3ds�ļ��Ļ�����һ����IDӦ����PRIMARY
	
	// ���ļ��ĵ�һ��������ж��Ƿ���3ds�ļ�
	ReadChunk(&currentChunk);

	// ȷ����3ds�ļ�
	if (currentChunk.ID != PRIMARY)
	{
		sprintf(strMessage, "Unable to load PRIMARY chuck from file: %s!", strFileName);
		MessageBox(NULL, strMessage, "Error", MB_OK);
		return false;
	}

	
	// ���ڿ�ʼ�������ݣ�ProcessNextChunk()��һ���ݹ麯��
	
	// ͨ����������ĵݹ麯�������������
	ProcessNextChunk(pModel, &currentChunk);

	
	// �ڶ�������3ds�ļ�֮�󣬼��㶥��ķ���
	ComputeNormals(pModel);

	// �ͷ��ڴ�ռ�
	CleanUp();

	return true;
}


//  ����ĺ����ͷ����е��ڴ�ռ䣬���ر��ļ�
void CLoad3DS::CleanUp()
{
	if (m_FilePointer) 
	{
		fclose(m_FilePointer);		// �رյ�ǰ���ļ�ָ��				
		m_FilePointer = NULL;  //�ļ�ָ��Ϊ��
	}
}

 
//  ����ĺ�������3ds�ļ�����Ҫ����(�Ǹ��ݹ麯��)
void CLoad3DS::ProcessNextChunk(CLoad3DS::t3DModel *pModel, tChunk *pPreviousChunk)
{
	t3DObject newObject = {0};			// ������ӵ���������		
	tMaterialInfo newTexture = {0};		// ������ӵ���������		

	tChunk currentChunk = {0};			// ������ӵ���ǰ������		
	tChunk tempChunk = {0};			// ������ӵ���ʱ������		

	//  ����ÿ��һ���¿飬��Ҫ�ж�һ�¿��ID������ÿ�����Ҫ�Ķ���ģ����������
	//  ����ǲ���Ҫ����Ŀ飬���Թ�

	// ���������ӿ飬ֱ���ﵽԤ���ĳ���
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		
		ReadChunk(&currentChunk);	// ������һ����

		// �жϿ��ID��
		switch (currentChunk.ID)
		{
		case VERSION:		// �ļ��汾��					
			// �ڸÿ�����һ���޷��Ŷ��������������ļ��İ汾
			
			// �����ļ��İ汾�ţ������ֽ�����ӵ�bytesRead������	
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
		
			// ����ļ��汾�Ŵ���3������һ��������Ϣ
			if ((currentChunk.length - currentChunk.bytesRead == 4) && (gBuffer[0] > 0x03)) 
			{
				MessageBox(NULL, "3DS�ļ��汾�Ŵ���3���п��ܶ�ȡ����ȷ��", "����", MB_OK);
			}
			break;

		case OBJECTINFO:		 // ����汾��Ϣ				
				
			ReadChunk(&tempChunk);// ������һ����
			
			// �������İ汾��
			tempChunk.bytesRead += fread(gBuffer, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);

			// ���Ӷ�����ֽ���
			currentChunk.bytesRead += tempChunk.bytesRead;

			// ������һ����
			ProcessNextChunk(pModel, &currentChunk);
			break;
		case MATERIAL:			// ������Ϣ				
	
			// ���ʵ���Ŀ����
			pModel->numOfMaterials++;
			
			// ���������������һ���հ�����ṹ
			pModel->vctMaterials.push_back(newTexture);
		
			// �������װ�뺯��
			ProcessNextMaterialChunk(pModel, &currentChunk);
		
			break;

		case OBJECT:			// ���������			
			// �ÿ��Ƕ�����Ϣ���ͷ���������˶���������
			
			pModel->numOfObjects++;// ����������
		
			// ���һ���µ�tObject�ڵ㵽����������
			pModel->vctObjects.push_back(newObject); 
		
			// ��ʼ������������������ݳ�Ա
			memset(&(pModel->vctObjects[pModel->numOfObjects - 1]), 0, sizeof(t3DObject));

			// ��ò������������ƣ�Ȼ�����Ӷ�����ֽ���
			currentChunk.bytesRead += GetString(pModel->vctObjects[pModel->numOfObjects - 1].strName);
			
			// ��������Ķ�����Ϣ�Ķ���
			ProcessNextObjectChunk(pModel, &(pModel->vctObjects[pModel->numOfObjects - 1]), &currentChunk);
			break;

		case EDITKEYFRAME:
			// �����ؼ�֡��Ķ��룬������Ҫ������ֽ���
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;

		default: 
			//  �������к��ԵĿ�����ݵĶ��룬������Ҫ������ֽ���
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		}
	
		// ���Ӵ����������ֽ���
		pPreviousChunk->bytesRead += currentChunk.bytesRead;
	}

}

//  ����ĺ����������е��ļ��ж������Ϣ
void CLoad3DS::ProcessNextObjectChunk(CLoad3DS::t3DModel *pModel, CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk)
{
	
	tChunk currentChunk = {0};// ������ӵ���ǰ������		
	vector<tMatREF*> vctMatIDS;
	
	// ��������������ֱ�����ӿ����
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// ������һ����
		ReadChunk(&currentChunk);

		// ������������ֿ�
		switch (currentChunk.ID)
		{
		case OBJECT_MESH:	 	// ���������һ���¿�				
		
			// ʹ�õݹ麯�����ã�������¿�
			ProcessNextObjectChunk(pModel, pObject, &currentChunk);
			break;

		case OBJECT_VERTICES:		// �����Ƕ��󶥵�		
			ReadVertices(pObject, &currentChunk);// �����󶥵�
			break;

		case OBJECT_FACES:		// ������Ƕ������			
			ReadVertexIndices(pObject, &currentChunk);// ����������
			break;

		case OBJECT_MATERIAL:			// ������Ƕ���Ĳ�������		
			// �ÿ鱣���˶�����ʵ����ƣ�������һ����ɫ��Ҳ������һ������ӳ�䡣ͬʱ�ڸÿ���Ҳ������
			// ����������������
			
			// ����������Ĳ�������
			ReadObjectMaterial(pModel, pObject, &currentChunk,&vctMatIDS);			
			break;

		case OBJECT_UV:				// ��������UV��������			

			// ��������UV��������
			ReadUVCoordinates(pObject, &currentChunk);
			break;

//		case 0x4111: 
//			
//			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
//			break;
		default:   	// �Թ�����Ҫ����Ŀ�
			
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		}

		// ��Ӵ������ж�����ֽ�����ǰ��Ķ�����ֽ���
		pPreviousChunk->bytesRead += currentChunk.bytesRead;

	}
	if(pPreviousChunk->ID!=OBJECT_MESH) return;
	
	int size=vctMatIDS.size();
	if(size)
	{
		pObject->numOfMaterials=size; //����Ĳ�������
		pObject->pMaterialREFS=new tMatREF[size];
		for(int i=0;i<size;i++)
		{
			pObject->pMaterialREFS[i]=*(vctMatIDS[i]);
		}
		vctMatIDS.clear();
	}
}


//  ����ĺ����������еĲ�����Ϣ
void CLoad3DS::ProcessNextMaterialChunk(CLoad3DS::t3DModel *pModel, CLoad3DS::tChunk *pPreviousChunk)
{
	
	tChunk currentChunk = {0};// ������ӵ���ǰ������	

	// ����������Щ�飬ֱ�����ӿ����
	while (pPreviousChunk->bytesRead < pPreviousChunk->length)
	{
		// ������һ��
		ReadChunk(&currentChunk);

		// �ж϶������ʲô��
		switch (currentChunk.ID)
		{
		case MATNAME:					// ���ʵ�����			
			
			// ������ʵ�����
			currentChunk.bytesRead += fread(pModel->vctMaterials[pModel->numOfMaterials - 1].strName, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
			
		case MAT_AMBIENT:		//���ʵĻ�����
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MAT_AMBIENT);
			break;
		case MAT_SPECULAR:		//���ʵľ����
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MAT_SPECULAR);
			break;
		case MAT_EMISSIVE:		 //���ʵĳ����
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MAT_EMISSIVE);
			break;
		case MATDIFFUSE:		//���ʵ��������				
			ReadColorChunk(&(pModel->vctMaterials[pModel->numOfMaterials - 1]), &currentChunk,MATDIFFUSE);
			break;
		
		case MATMAP:			// ������Ϣ��ͷ��					
			
			// ������һ�����ʿ���Ϣ
			ProcessNextMaterialChunk(pModel, &currentChunk);
			break;

		case MATMAPFILE:	// �����ļ�������					

			// ������ʵ��ļ�����
			currentChunk.bytesRead += fread(pModel->vctMaterials[pModel->numOfMaterials - 1].strFile, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		
		default:  

			// �ӹ�����Ҫ����Ŀ�
			currentChunk.bytesRead += fread(gBuffer, 1, currentChunk.length - currentChunk.bytesRead, m_FilePointer);
			break;
		}

		// ��Ӵ������ж�����ֽ���
		pPreviousChunk->bytesRead += currentChunk.bytesRead;
	}
}

//  ���溯��������ID�ź������ֽڳ���
void CLoad3DS::ReadChunk(CLoad3DS::tChunk *pChunk)
{
	// ������ID�ţ�ռ����2���ֽڡ����ID����OBJECT��MATERIALһ����˵�����ڿ���������������
	pChunk->bytesRead = fread(&pChunk->ID, 1, 2, m_FilePointer);

	// Ȼ������ռ�õĳ��ȣ��������ĸ��ֽ�
	pChunk->bytesRead += fread(&pChunk->length, 1, 4, m_FilePointer);
}


//  ����ĺ�������һ���ַ���
int CLoad3DS::GetString(char *pBuffer)
{
	int index = 0;

	
	// ����һ���ֽڵ�����
	fread(pBuffer, 1, 1, m_FilePointer);

	// ֱ������
	while (*(pBuffer + index++) != 0) 
	{
		// ����һ���ַ�ֱ��NULL
		fread(pBuffer + index, 1, 1, m_FilePointer);
	}

	// �����ַ����ĳ���
	return strlen(pBuffer) + 1;
}


//  ����ĺ�������RGB��ɫ
void CLoad3DS::ReadColorChunk(CLoad3DS::tMaterialInfo *pMaterial, CLoad3DS::tChunk *pChunk,USHORT typeFlag)
{
	tChunk tempChunk = {0};
	BYTE btmp[3];

	// ������ɫ����Ϣ
	ReadChunk(&tempChunk);
	switch(typeFlag)
	{
	case MAT_AMBIENT://���ʵĻ�������ɫ
		tempChunk.bytesRead += fread(btmp, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		Bytes2Floats(btmp,pMaterial->ambient,3,1.0f/256.0f);
		pMaterial->ambient[3]=1.0f;
		break;		
	case MAT_SPECULAR://���ʵľ������ɫ
		tempChunk.bytesRead += fread(btmp, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		Bytes2Floats(btmp,pMaterial->specular,3,1.0f/256.0f);
		pMaterial->specular[3]=1.0f;
		break;
	case MAT_EMISSIVE://���ʵĳ������ɫ
		tempChunk.bytesRead += fread(btmp, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		
		memset(btmp,0,3);
		
		Bytes2Floats(btmp,pMaterial->emissive,3,1.0f/256.0f);
		pMaterial->emissive[3]=1.0f;
		break;
	case MATDIFFUSE://���ʵ����������ɫ
	default:
		
		tempChunk.bytesRead += fread(pMaterial->color, 1, tempChunk.length - tempChunk.bytesRead, m_FilePointer);
		Bytes2Floats(pMaterial->color,pMaterial->diffuse,3,1.0f/256.0f);
		pMaterial->diffuse[3]=1.0f;
		break;
	}

	// ���Ӷ�����ֽ���
	pChunk->bytesRead += tempChunk.bytesRead;
}

//  ����ĺ������붥������
void CLoad3DS::ReadVertexIndices(CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk)
{
	unsigned short index = 0;		// ���ڶ��뵱ǰ�������				

	// ����ö����������Ŀ
	pPreviousChunk->bytesRead += fread(&pObject->numOfFaces, 1, 2, m_FilePointer);

	// ����������Ĵ洢�ռ䣬����ʼ���ṹ
	pObject->pFaces = new tFace [pObject->numOfFaces];
	memset(pObject->pFaces, 0, sizeof(tFace) * pObject->numOfFaces);

	
	// �������������е���
	for(int i = 0; i < pObject->numOfFaces; i++)
	{
		
		
		for(int j = 0; j < 4; j++)
		{
			// ���뵱ǰ��ĵ�һ����
			pPreviousChunk->bytesRead += fread(&index, 1, sizeof(index), m_FilePointer);

			if(j < 3)
			{
				// ��������������Ľṹ��
				pObject->pFaces[i].vertIndex[j] = index;
			}
		}
	}
}


 
//  ����ĺ�����������UV����
void CLoad3DS::ReadUVCoordinates(t3DObject *pObject, tChunk *pPreviousChunk)
{
	
	// Ϊ�˶�������UV���꣬������Ҫ����UV�����������Ȼ��Ŷ�����������
	
	// ����UV���������
	pPreviousChunk->bytesRead += fread(&pObject->numTexVertex, 1, 2, m_FilePointer);

	// ���䱣��UV������ڴ�ռ�
	pObject->pTexVerts = new CVector2 [pObject->numTexVertex];

	// ������������
	pPreviousChunk->bytesRead += fread(pObject->pTexVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);
}


//  �������Ķ�������
void CLoad3DS::ReadVertices(CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk)
{
	
	
	// �ڶ���ʵ�ʵĶ���֮ǰ�����ȱ���ȷ����Ҫ������ٸ����㡣
	
	// ���붥�����Ŀ
	pPreviousChunk->bytesRead += fread(&(pObject->numOfVerts), 1, 2, m_FilePointer);

	// ���䶥��Ĵ洢�ռ䣬Ȼ���ʼ���ṹ��
	pObject->pVerts = new CVector3 [pObject->numOfVerts];
	memset(pObject->pVerts, 0, sizeof(CVector3) * pObject->numOfVerts);

	
	// ���붥������
	pPreviousChunk->bytesRead += fread(pObject->pVerts, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);

	
	
   //��ʼ���������С�����x,y,z����
	pObject->m_minX=999999; pObject->m_maxX=-99999;
	pObject->m_minY=999999; pObject->m_maxY=-99999;
	pObject->m_minZ=999999; pObject->m_maxZ=-99999;

	// �����Ѿ����������еĶ��㡣
	// ��Ϊ3D Studio Max��ģ�͵�Z����ָ���ϵģ������Ҫ��y���z�ᷭת������
	// ����������ǽ�Y���Z�ύ����Ȼ��Z�ᷴ��
	
	// �������еĶ���
	for(int i = 0; i < pObject->numOfVerts; i++)
	{
		
		// ����Y���ֵ
		float fTempY = pObject->pVerts[i].y;

		
		// ����Y���ֵ����Z���ֵ
		pObject->pVerts[i].y = pObject->pVerts[i].z;

		// ����Z���ֵ����-Y���ֵ
		pObject->pVerts[i].z = -fTempY;

		//����������С�����x,y,z����
		if(pObject->m_minX>pObject->pVerts[i].x) pObject->m_minX=pObject->pVerts[i].x;
		if(pObject->m_maxX<pObject->pVerts[i].x) pObject->m_maxX=pObject->pVerts[i].x;
		if(pObject->m_minY>pObject->pVerts[i].y) pObject->m_minY=pObject->pVerts[i].y;
		if(pObject->m_maxY<pObject->pVerts[i].y) pObject->m_maxY=pObject->pVerts[i].y;
		if(pObject->m_minZ>pObject->pVerts[i].z) pObject->m_minZ=pObject->pVerts[i].z;
		if(pObject->m_maxZ<pObject->pVerts[i].z) pObject->m_maxZ=pObject->pVerts[i].z;
		
	}
}

//  ����ĺ����������Ĳ�������
void CLoad3DS::ReadObjectMaterial(CLoad3DS::t3DModel *pModel,CLoad3DS::t3DObject *pObject, CLoad3DS::tChunk *pPreviousChunk,vector<tMatREF*> *pvmatids)
{
	char strMaterial[255] = {0};	// �����������Ĳ�������		
	bool bmaterror=true;

	tMatREF *pMatref;
	pMatref=new tMatREF;
	
	// ���ʻ�������ɫ�������Ƕ��������Ҳ���ܱ������������ȡ�����ȵ���Ϣ��
	
	// ������븳�赱ǰ����Ĳ�������	
	pPreviousChunk->bytesRead += GetString(strMaterial);


	// �������е�����
	for(int i = 0; i < pModel->numOfMaterials; i++)
	{
		//�������������뵱ǰ����������ƥ��
		if(strcmp(strMaterial, pModel->vctMaterials[i].strName) == 0)
		{
			// ���ò���ID
			pObject->materialID = i;
			pMatref->nMaterialID=i;
			
			// �ж��Ƿ�������ӳ�䣬���strFile��һ�����ȴ���1���ַ�������������
			if(strlen(pModel->vctMaterials[i].strFile) > 0) 
			{
				// ���ö��������ӳ���־
				pObject->bHasTexture = true;
				pMatref->bHasTexture=true;
			}	
			bmaterror=false;
			break;
		}
		else
		{
			// ����ö���û�в��ʣ�������IDΪ-1
			pObject->materialID = -1;
			pMatref->nMaterialID=-1;
			bmaterror=true;
		}
	}
 	
	pPreviousChunk->bytesRead += fread(gBuffer, 1, pPreviousChunk->length - pPreviousChunk->bytesRead, m_FilePointer);
	if(!bmaterror)
	{
		pMatref->nFaceNum=gBuffer[0]&0x0000FFFF;
		pMatref->pFaceIndexs=new USHORT[pMatref->nFaceNum];
		memcpy(pMatref->pFaceIndexs,2+(BYTE*)gBuffer,pMatref->nFaceNum*sizeof(USHORT));
		
		pvmatids->push_back(pMatref);
	}
 
}			

 
 
//  ����ĺ������ڼ������ķ�����
void CLoad3DS::ComputeNormals(CLoad3DS::t3DModel *pModel)
{
	CVector3 vVector1, vVector2, vNormal, vPoly[3];

	// ���ģ����û�ж����򷵻�	
	if(pModel->numOfObjects <= 0)
		return;

	
	// ����ģ�������еĶ���
	for(int index = 0; index < pModel->numOfObjects; index++)
	{
		
		// ��õ�ǰ�Ķ���
		t3DObject *pObject = &(pModel->vctObjects[index]);

		// ������Ҫ�Ĵ洢�ռ�
		CVector3 *pNormals		= new CVector3 [pObject->numOfFaces];
		CVector3 *pTempNormals	= new CVector3 [pObject->numOfFaces];
		pObject->pNormals		= new CVector3 [pObject->numOfVerts];

		// ���������������
		for(int i=0; i < pObject->numOfFaces; i++)
		{												
			
			vPoly[0] = pObject->pVerts[pObject->pFaces[i].vertIndex[0]];
			vPoly[1] = pObject->pVerts[pObject->pFaces[i].vertIndex[1]];
			vPoly[2] = pObject->pVerts[pObject->pFaces[i].vertIndex[2]];

			
			// ������ķ�����
			vVector1 = Vector(vPoly[0], vPoly[2]);	// ��ö���ε�ʸ��	
			vVector2 = Vector(vPoly[2], vPoly[1]);// ��ö���εĵڶ���ʸ��		

			vNormal  = Cross(vVector1, vVector2);		// �������ʸ���Ĳ��	
			pTempNormals[i] = vNormal;				// ����ǹ淶��������	
			vNormal  = Normalize(vNormal);		// �淶����õĲ��		

			pNormals[i] = vNormal;				// ����������ӵ��������б���			
		}

		
		//  �����󶥵㷨����
		CVector3 vSum (0.0, 0.0, 0.0);
		CVector3 vZero = vSum;
		int shared=0;

		// �������еĶ���
		for (i = 0; i < pObject->numOfVerts; i++)			
		{
			for (int j = 0; j < pObject->numOfFaces; j++)	// �������е���������
			{												
				// �жϸõ��Ƿ����������湲��
				if (pObject->pFaces[j].vertIndex[0] == i || 
					pObject->pFaces[j].vertIndex[1] == i || 
					pObject->pFaces[j].vertIndex[2] == i)
				{
					vSum =vSum+pTempNormals[j];
					shared++;								
				}
			}      
			
			
			pObject->pNormals[i] = vSum/float(-shared);

			// �淶�����Ķ��㷨��
			pObject->pNormals[i] = Normalize(pObject->pNormals[i]);	

			vSum = vZero;									
			shared = 0;										
		}
	
		// �ͷŴ洢�ռ䣬��ʼ��һ������
		delete [] pTempNormals;
		delete [] pNormals;
	}
}

//�ֽ����鵽����ת�� 
void CLoad3DS::Bytes2Floats(BYTE *pbs, float *pfs, int num, float fsk)
{
	if(num==0||num>100)return;
	for(int i=0;i<num;i++)
	{
		pfs[i]=float(pbs[i])*fsk;
	}
}


/*
ֵ��ע�����OpenGL������ϵ��3DS Max������ϵ�ǲ�ͬ�ģ�3D Studio Max�е�ģ�͵�Z����ָ���ϵģ�
��OpenGL��ģ�͵�Z���Ǵ�ֱ��Ļָ���û��ģ������Ҫ������������y��z��ת������
ʲô�ǿ飿
��ID�Ǳ�ʶ�ÿ����������͵Ķ�һ�޶��Ĵ��룬ͬʱҲ��ʶ�Ƿ�����ӿ顣��ռ���������ֽڡ�
��ĳ��ȱ�ʾ���ǽ����ڸÿ���������ݵĳ��ȡ���ռ�����ĸ��ֽڡ�

*/