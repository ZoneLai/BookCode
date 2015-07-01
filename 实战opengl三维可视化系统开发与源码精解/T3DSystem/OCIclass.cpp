// OCIclass.cpp: implementation of the COCIclass class.
 
 

#include "stdafx.h"
 
#include "OCIclass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

 
// Construction/Destruction
 

FILE *fp_OCI;	//FILEָ��,�������ⲿ�ļ�
ub4 Filelength_OCI; //�洢���ⲿ�ļ��ĳ���

/*
Ϊ�˲�һ��д��������ݣ����ȶ���һ����������СLOB_BUF_LEN������涨Ϊ8192�� 
���д�����ݴ�С��size����LOB_BUF_LEN��Χ�ڣ����һ��д�ꡣ 
*/
#define LOB_BUF_LEN  131072  
 
#define MAXLENGTH    4294967296 //һ��LOB�ֶ����洢���ֽ���

 
//�Իص���ʽд������
sb4 callback_writes_OCI(dvoid *ctxp,dvoid *bufxp,ub4 *lenp, ub1 *piece)
{
	ub4 piecelen;	
	static ub4 len=LOB_BUF_LEN;
	
	if((Filelength_OCI-len)>LOB_BUF_LEN) //����ļ��ĳ���-ÿ�ζ�д�ĳ���>LOB_BUF_LEN
		piecelen=LOB_BUF_LEN;	//��ʱ��д�ĳ���=LOB_BUF_LEN
	else  //���ļ��ĳ���<ÿ�ζ�д�ĳ���
		piecelen=Filelength_OCI-len; //��ʱ��д�ĳ���=�ļ��ĳ���-LOB_BUF_LEN
	
	*lenp=piecelen;
	
	//��ʼ���ļ�
	if(fread((void*)bufxp,(size_t)piecelen,1,fp_OCI)!=1)
	{
		AfxMessageBox("�������ļ���������!");
		*piece=OCI_LAST_PIECE;
		len=LOB_BUF_LEN;
		return OCI_CONTINUE;
		
	}
	len+=piecelen;//�Ѷ����ļ������ۼ�
	
	if(len==Filelength_OCI)  //����Ѷ����ļ�����=�ļ��ܳ���,�������ļ��Ķ�����
	{
		*piece=OCI_LAST_PIECE;//��ǰ��Ϊ���һ���־����ʾд���һ������ 
		len=LOB_BUF_LEN;
	}
	else
		*piece=OCI_NEXT_PIECE;//����,��ǰ��Ϊ��һ���־,��ʾ����д������д���һ�� 
	
	return OCI_CONTINUE;
}

 
//�Իص���ʽ��������
sb4 callback_Read_OCI(dvoid *ctxp,CONST dvoid *bufxp,ub4 len,ub1 piece)
{
	static ub4 piece_count=0;
	piece_count++;
	switch(piece)
	{
	case OCI_LAST_PIECE://��ʾд���һ������ 
		fwrite((void*)bufxp,(size_t)len,1,fp_OCI);
		piece_count=0;
		return OCI_CONTINUE;
	case OCI_FIRST_PIECE://��ʾд��һ��
	case OCI_NEXT_PIECE://��ʾ����д������д���һ��
		fwrite((void*)bufxp,(size_t)len,1,fp_OCI);
		break;
	default:
		return OCI_ERROR;
	}
	
	return OCI_CONTINUE;
	
}

COCIclass::COCIclass()
{

}

COCIclass::~COCIclass()
{

}


//��ʼ��OCI
void COCIclass::Init_OCI()
{
	//����OCI����,�������ͳ�ʼ��OCI����������������OCI������ҪOCI��������ִ�С�
	if(status=OCIEnvCreate(&envhp,OCI_DEFAULT,(dvoid *)0, 
		(dvoid* (*)(dvoid*,size_t))0,(dvoid* (*)(dvoid*,dvoid*,size_t))0,
		(void (*)(dvoid *, dvoid *)) 0, (size_t) 0,(dvoid **) 0 ))
	{
		MessageBox(NULL,"����OCI����ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}
	/*
	1������OCI���� 
	sword OCIEnvCreate(   
	OCIEnv **envhpp,  //OCI�������ָ�� 
	ub4 mode, //��ʼ��ģʽ��OCI_DEFAULT/OCI_THREADED �� 
	CONST dvoid *ctxp, 
	CONST dvoid *(*malicfp)(dvoid *ctxp,size_t size), 
	CONST dvoid *(ralocfp)(dvoid *ctxp,dvoid *memptr,size_t newsize), 
	CONST void *(*mfreefp)(dvoid *ctxp,dvoid *memptr), 
	Size_t xstramemsz, 
	Dvoid **usrmempp 
	) 

OCI�������õ�ģʽ�У� 
	OCI_DEFUALT:ʹ��OCIĬ�ϵĻ��� 
	OCI_THREADED���̻߳�����ʹ��OCI 
	OCI_OBJECT������ģʽ 
	OCI_SHARED������ģʽ 
	OCI_EVENTS 
	OCI_NO_UCB 
	OCI_ENV_NO_MUTEX���ǻ������ģʽ 
	����ģʽ�������߼���������е��ӣ����������óɶ����ģʽ����mode=OCI_SHREADED| OCI_OBJECT 

	*/

	//���������
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&errhp,(ub4)OCI_HTYPE_ERROR,
		(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"���������ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}

	//������������
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&srvhp,
		(ub4)OCI_HTYPE_SERVER,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"������������ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}
	
	//������񻷾����
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&svchp,
		(ub4)OCI_HTYPE_SVCCTX,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"������񻷾����ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}
	
	//����Ự���
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&authp,
		(ub4)OCI_HTYPE_SESSION,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"����Ự���ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);		
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}
	
	//���������
	if(status=OCIHandleAlloc((dvoid*)envhp,(dvoid**)&stmthp,
		(ub4)OCI_HTYPE_STMT,(size_t)0,(dvoid**)0))
	{
		MessageBox(NULL,"���������ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}
	
	/*
	2������/�ͷž�� 
	sword OCIHandleAlloc( 
		CONST dvoid *parenth,  //���������ĸ������һ��ΪOCI������� 
		Dvoid **hndlpp,   //������¾�� 
		Ub4 type, type,  //������� 
		Size_t xtramem_sz,   //������ڴ��� 
		Dvoid **usrmempp  //���뵽���ڴ��ָ�� 
	) 
	ע�� 
	һ����Ҫ����ľ���У� 
	���������OCIServer, �������OCI_HTYPE_SERVER 
	������OCIError�����ڲ���OCI������Ϣ, �������OCI_HTYPE_ERROR 
	������OCISession, �������OCI_HTYPE_SESSION 
	�����ľ��OCISvcCtx, �������OCI_HTYPE_SVCCTX 
	SQL�����OCIStmt, �������OCI_HTYPE_STMT 
	*/

	/*
	�ͷž�� 
	sword OCIHandleFree( 
	dvoid *hndlp,  //Ҫ�ͷŵľ�� 
	ub4 type   //������� 
	) 
	*/

	//����2��LOBռλ��,���ڶ�BLOB��������д����ȡ�������ò���OCI_DTYPE_LOB�����һ��LOB�ľ��
	for(int i=0;i<2;i++)
	{
		if(status=OCIDescriptorAlloc((dvoid*)envhp,(dvoid**)&lob_loc[i],(ub4)OCI_DTYPE_LOB,
			(size_t)0,(dvoid**)0))
		{
			MessageBox(NULL,"����LOBռλ��ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
			Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
			return ;		
		}
 	}

	/*
	12�� ���ռλ����ָʾ�������� 
	ռλ�����ڳ����У�һЩSQL�����Ҫ�ڳ�������ʱ����ȷ������������ݣ������ʱ
	����һ��ռλ�������棬����������ʱ������׼�������󣬱���Ϊÿ��ռλ��ָ��һ��������
	����ռλ������������ַ��ϣ�ִ��ʱ��Oracle�ʹ���Щ�����ж�ȡ���ݣ���������
	��SQL���һ�𴫵ݸ�Oracle������ִ�С�OCI���ռλ��ʱ������ռλ�������
	����������������ͬʱҪָ������������������ͺ����ݳ��ȡ� 
	�磺select * from test where name=:p1 and age>:p2 
	��p1�ͣ�p2Ϊռλ�� 
	
	  ָʾ��������������Oracle�У���ֵ����ΪNULL������C������û��NULLֵ��
	  Ϊ����ʹOCI������NULL��ֵ��OCI�����������Ϊ��ִ������еĽ�ϱ���ͬʱ
	  ����һ��ָʾ��������ָʾ���������飬��˵������ϵ�ռλ���Ƿ�ΪNULL����
	  ��ȡ����ֵ�Ƿ�ΪNULL���Լ�����ȡ����ֵ�Ƿ񱻽�ȡ�� 
	  ��SQLT��NTY��SQL Named DataType���⣬ָʾ��������ָʾ�������������������Ϊsb2,��ֵ˵���� 
	  ��Ϊ�������ʱ������insert ,update����У� 
	  ��=-1��OCI����NULL����Oracle����У�����ռλ����ϵĳ������ֵ 
	  >=0��Ӧ�ó��򽫳������ֵ����ָ���� 
	  ��Ϊ�������ʱ������select����У� 
	  ��-2������ȡ�������ݳ��ȴ��ڳ�������ĳ��ȣ��򱻽�ȡ�� 
	  =-1������ȡ��ֵΪNULL,���������ֵ���ᱻ�ı䡣 
	  =0�����ݱ��������뵽ָ���ĳ�������� 
	  ��0������ȡ�������ݳ��ȴ��ڳ�������ĳ��ȣ��򱻽�ȡ��ָʾ������ֵΪ����ȡ���ݱ���ȡǰ��ʵ�ʳ��� 
	  
	*/
// 	theApp.m_servername="";//�����ȫ��oracle���ݿ��������

	//�������ݿ�
	if(status=OCIServerAttach(srvhp,errhp,(text*)(LPCSTR)theApp.m_servername,strlen(theApp.m_servername),OCI_DEFAULT))
		{
		MessageBox(NULL,"�������ݿ�ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}
/*
	4������/�Ͽ������� 
	���û���ʽ���ӣ� 
	sword  OCIServerAttach( 
	OCIServer     *srvhp,//δ��ʼ���ķ�������� 
	OCIError      *errhp, //������
	CONST text    *dblink,//������SID 
	sb4           dblink_len, //������������
	ub4           mode //=OCI_DEFAULT,ϵͳ��������Ϊ������ʽ 
	); 

	  OCI�����ж��ַ�ʽ��Blocking(������ʽ)��non_Blocking(��������ʽ)��������ʽ����
	  ������ OCI����ʱ������ȵ���OCI������ɺ�������ŷ��ؿͻ�����Ӧ����Ϣ������
	  �ǳɹ�����ʧ�ܡ���������ʽ�ǵ��ͻ����ύOCI�������������󣬷���������
	  ����OCI_STILL_EXECUTING��Ϣ���������ȴ�����˵Ĳ�����ɡ� 
	����non-blocking��ʽ��Ӧ�ó������յ�һ��OCI�����ķ���ֵΪ OCI_STILL_EXECUTINGʱ
	�����ٴζ�ÿһ��OCI�����ķ���ֵ�����жϣ��ж���ɹ���� 
	��ͨ�����÷���������ΪOCI_ATTR_NONBLOCKING_MODE��ʵ�֡�ϵͳĬ�Ϸ�ʽΪ����ģʽ. 
	  
*/


	//���÷��񻷾��ķ���������(��oracle���ݿ�ķ�������)	
	if(status= OCIAttrSet ((dvoid*)svchp, (ub4) OCI_HTYPE_SVCCTX, 
		(dvoid*)srvhp, (ub4) 0,OCI_ATTR_SERVER, errhp))
	{
		MessageBox(NULL,"���÷��񻷾��ķ���������ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}

	//���ûỰ��ʹ�õ��û�����(��oracle���ݿ��û���)
	if(status= OCIAttrSet((dvoid*)authp,OCI_HTYPE_SESSION,
		(text*)(LPCSTR)theApp.m_username,(ub4)strlen(theApp.m_username),OCI_ATTR_USERNAME,errhp))
	{
		MessageBox(NULL,"���ûỰ��ʹ�õ��û��ʺ�ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}	
	
	//���ûỰ��ʹ�õ��û�����(��oracle���ݿ�����)
	if(status= OCIAttrSet((dvoid*)authp,OCI_HTYPE_SESSION,
		(text*)(LPCSTR)theApp.m_userpassword,(ub4)strlen(theApp.m_userpassword),OCI_ATTR_PASSWORD,errhp))
	{
		MessageBox(NULL,"���ûỰ��ʹ�õ��û�����ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}

	/*
	5����ȡ/���þ������ 
	sword OCIAttrSet( 
	dvoid *trgthndlp,  //�����õľ���� 
	ub4  trghndltyp, //������� 
	dvoid *attributep, //���õ������� 
	ub4 size, //����ֵ���� 
	ub4 attrtype,     //�������� 
	OCIError *errhp   //������ 
	) 
	ע��һ��Ҫ���õ������У� 
	������ʵ���� 
	�������OCI_HTYPE_SVCCTX����������OCI_ATTR_SERVER 
	�������ݵ��û����� 
	�������OCI_HTYPE_SESSION����������OCI_ATTR_USERNAME 
	�û����� 
    �������OCI_HTYPE_SESSION����������OCI_ATTR_PASSWORD 
	����   
	�������OCI_HTYPE_SVCCTX����������OCI_ATTR_SESSION 
	
	
	*/
	
	//��ʼһ���Ự(��ͨ�����õ�oracle���ݿ��û���������\)
	if(status= OCISessionBegin(svchp,errhp,authp,OCI_CRED_RDBMS,OCI_DEFAULT))
	{
		MessageBox(NULL,"���ûỰ��ʹ�õ��û��ʺ�ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}
	/*
	6����ʼ/����һ���Ự
	����֤�û��ٽ���һ���Ự����
    sword OCISessionBegin ( 
	OCISvcCtx     *svchp,   //���񻷾����
	OCIError    *errhp,	//������
	OCISession *usrhp, //�û��Ự���
	ub4           credt, //��֤����
	ub4           mode //����ģʽ
	);
	
      *��֤���ͣ� 
	  OCI_CRED_RDBMS:�����ݿ��û��������������֤������Ҫ����OCI_ATTR_USERNAME��OCI_ATTR_PASSWORD����
	  OCI_CRED_EXT:�ⲿ��֤������Ҫ�����û�������
	  OCI_DEFAULT���û��Ự����ֻ�ܱ�ָ���ķ������������������
	  OCI_SYSDBA���û�Ҫ����sysdbaȨ��
	  OCI_SYSOPER���û�Ҫ����sysoperȨ��
	  
	*/
	
	if(status= OCIAttrSet(svchp, OCI_HTYPE_SVCCTX,(dvoid*)authp, 0, 
		OCI_ATTR_SESSION, errhp))
	{
		MessageBox(NULL,"���ûỰ��ʹ�õ��û��ʺ�ʧ��!","��ʼ��OIC",MB_ICONINFORMATION);		
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return ;		
	}
}


/*
 OCI��������ֵ�� 
OCI_SUCCESS �C����ִ�гɹ� (=0) 
OCI_SUCCESS_WITH_INFO �Cִ�гɹ������������Ϣ���أ������Ǿ�����Ϣ 
OCI_NO_DATA������ִ����ɣ���û���������� 
OCI_ERROR������ִ�д��� 
OCI_INVALID_HANDLE�����ݸ������Ĳ���Ϊ��Ч������򴫻صľ����Ч 
OCI_NEED_DATA����ҪӦ�ó����ṩ����ʱ�̵����� 
OCI_CONTINUE���ص��������ش��룬˵���ص�������ҪOCI��ָ��������Ĵ������ 
OCI_STILL_EXECUTING�����񻷾������ڷ�����ģʽ��OCI������������ִ���С� 

  */
//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
void COCIclass::Error_proc(dvoid *errhp, sword status)
{
	text errbuf[512];
	sb4 errcode;
	CString errinfor;
	
	switch(status)
	{
	case OCI_SUCCESS://����ִ�гɹ�
		break;
	case OCI_SUCCESS_WITH_INFO:
		MessageBox(NULL,"ִ�гɹ������������Ϣ���أ������Ǿ�����Ϣ","������",MB_ICONINFORMATION);
		break;
	case OCI_NEED_DATA:
		MessageBox(NULL,"��ҪӦ�ó����ṩ����ʱ�̵�����","������",MB_ICONINFORMATION);
		break;
	case OCI_NO_DATA:
		MessageBox(NULL,"����ִ����ɣ���û����������","������",MB_ICONINFORMATION);
		break;
	case OCI_ERROR://����ִ�д���
		OCIErrorGet ((dvoid *) errhp, (ub4) 1, (text *) NULL, 
			&errcode, errbuf, (ub4) sizeof(errbuf), (ub4) OCI_HTYPE_ERROR);
		errinfor.Format ("OCI �����: %d\n������Ϣ:%s",errcode,errbuf);
		MessageBox(NULL,errinfor,"������",MB_ICONINFORMATION);
		break;
	case OCI_INVALID_HANDLE: 
		MessageBox(NULL,"���ݸ������Ĳ���Ϊ��Ч������򴫻صľ����Ч","������",MB_ICONINFORMATION);
		break;
	case OCI_STILL_EXECUTING:
		MessageBox(NULL,"���񻷾������ڷ�����ģʽ��OCI������������ִ����","������",MB_ICONINFORMATION);
		break;
	default:
		break;
	}
}
/*
sword OCIErrorGet ( 
	dvoid      *hndlp, //������ 
	ub4        recordno,//�������ȡ�����¼����1��ʼ 
	text       *sqlstate,//��ȡ����=NULL 
	sb4        *errcodep, //����� 
	text       *bufp,  //�������� 
	ub4        bufsiz,  //bufp���� 
	ub4        type //���ݵĴ��������� 
	=OCI_HTYPE_ERROR:������ 
	=OCI_HTYPE_ENV��������� 
); 

*/
 
//�Իص���ʽ��LOB����д��Oracle���ݿ���
int COCIclass::CallbackWriteToLob()
{
	ub4 offset=1,loblength=0;
	ub4 bufp[LOB_BUF_LEN];
	
	ub4 piecelen;
	ub1 *piece=0;
	ub4 *lenp=0;
	
	CString tempstr;
	
	OCILobGetLength(svchp,errhp,lob_loc[0],&loblength);//���LOB�����ݳ���,�洢��loblength������
	
	fseek(fp_OCI,0,SEEK_SET);//��fp_OCIָ��ָ����ļ�
	
	if(Filelength_OCI>LOB_BUF_LEN) //����ļ����ȴ���LOB_BUF_LEN
		piecelen=LOB_BUF_LEN;  //���ļ���ĳ���=LOB_BUF_LEN
	else  //����ļ�����С��LOB_BUF_LEN
		piecelen=Filelength_OCI; //���ļ���ĳ��Ⱦ�ֱ�ӵ����ļ�����
	
	if(fread((dvoid*)bufp,(size_t)piecelen,1,fp_OCI)!=1)//���������
	{
		MessageBox(NULL,"�������ݷ�������!","�ص�ģʽд������",MB_ICONINFORMATION);
		return -1;
	}
	if(Filelength_OCI<LOB_BUF_LEN)   //����ļ�����С��LOB_BUF_LEN
	{		
		if(status=OCILobWrite(svchp,errhp,lob_loc[0],&Filelength_OCI,offset,(dvoid*)bufp,(ub4)piecelen,
			OCI_ONE_PIECE,(dvoid*)0,(sb4(*)(dvoid*,dvoid*,ub4*,ub1*))0,(ub2)0,
			(ub1)SQLCS_IMPLICIT)!=OCI_SUCCESS)
		{
			Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
			return -1;
		}
		
	}
	else   //����ļ����ȴ���LOB_BUF_LEN
	{
		if(status=OCILobWrite(svchp,errhp,lob_loc[0],&Filelength_OCI,offset,(dvoid*)bufp,
			(ub4)piecelen,OCI_FIRST_PIECE,(dvoid*)0,callback_writes_OCI,(ub2)0,SQLCS_IMPLICIT))
		{
			Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
			return -1;			
		}
	}
	
	return 0;
}
/*
OCILobGetLength(
	handle_service,//���񻷾����
	handle_error,//������
	p_blob, //LOB��λ��
	 &size //�洢LOB�����ݳ���
	 ) 

OCILobWrite()�����ǵķ�ʽ������д��ָ��ƫ������������OCI_NEED_DATA��ʾδ
д��LOB���ݵ�ȫ������Ӧ�����ô˺�������д����ʹ��ORACLE�������ƣ���졢ʹ�ø��õĿռ��REDO��

*/
 
BOOL COCIclass::AddNormalDataToDB(CString strSQL)
{	
	//׼��SQL���
	if (status =OCIStmtPrepare(stmthp, errhp,(const unsigned char*)(LPCSTR)strSQL, strlen((char*)(LPCSTR)strSQL),OCI_NTV_SYNTAX,OCI_DEFAULT))
	{
		Error_proc(errhp, status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return FALSE;
	}
	/*
	7��׼��SQL��� 
	sword OCIStmtPrepare ( 
		OCIStmt       *stmtp,//�����   
		OCIError      *errhp, //������
		CONST text    *stmt,  //SQL��� 
		ub4           stmt_len,   //��䳤�� 
		ub4           language,  //�����﷨��ʽ=OCI_NTV_SYNTAX 
		ub4           mode //=OCI_DEFAULT 
		); 
	*/
	
	if (status =OCIStmtExecute(svchp, stmthp, errhp, (ub4 )1,0, NULL, NULL, OCI_DEFAULT))
	{
		Error_proc(errhp, status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return FALSE;
	}
	
	if (status =OCITransCommit(svchp, errhp, (ub4)0))
	{
		Error_proc(errhp, status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return FALSE;
	}

	return  TRUE;
}

 /*
 lob ��������OCI������Ҫ�б�
 
           OCILobOpen()���ڲ����ⲿLOB
           OCILobFileOpen()���ⲿLOB���ļ�
           OCILobClose()�ر�LOB
           OCILobFileClose()����ⲿLOB���ļ�
           OCILobFileCloseAll()�ر������ⲿLOB���ļ�
           OCILobGetLength()���LOB�����ݳ���
           OCILobRead()��ȡLOB���ݣ���ָ����ȡָ��ƫ�������ĸ�����С��LOB���ݵ��ڴ棬
		              ����OCI_NEED_DATA��ʾδ����LOB���ݵ�ȫ������Ӧ�����ô˺�����������
           OCILobWrite()�Ը��ǵķ�ʽ������д��ָ��ƫ������������OCI_NEED_DATA
		              ��ʾδд��LOB���ݵ�ȫ������Ӧ�����ô˺�������д��
           OCILobWriteAppend()��׷�ӵķ�ʽдLOB����
           OCILobTrim()��LOB�Ĵ�С�ض�Ϊָ��ֵ��ֻ�ܲ����ڲ�LOB
           OCILobErase()ɾ��LOBָ��ƫ������ָ����С�����ݡ�
*/
 
//��BLOB������������д��oralce���ݿ���
BOOL COCIclass::AddBOLBDataToDB(CString strFilename, CString strSQL,int m_ID)
{
	text *selectlocator;

	fp_OCI=fopen((const char*)(LPCSTR)strFilename,(const char *)"rb");
	fseek(fp_OCI,0,SEEK_END);
	Filelength_OCI=ftell(fp_OCI);
	if(Filelength_OCI<=0)
	{
		MessageBox(NULL,"�ļ�����Ϊ0,����д��!","д������",MB_ICONSTOP);
		return FALSE;
	}
	selectlocator=(text*)(LPCTSTR)strSQL;
	
	
	//׼��SQL���
	if(status= OCIStmtPrepare(stmthp,errhp,selectlocator,
		(ub4)strlen((char*)selectlocator),(ub4)OCI_NTV_SYNTAX,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"׼��SQL���ʧ��!","д��LOB����",MB_ICONSTOP);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return  FALSE;		
	}
	
	//��λ�ð�,����һ�㰴�˷�ʽ��
	if(status= OCIBindByPos(stmthp,&bndhp,errhp,(ub4)1,(dvoid*)&m_ID,
		(sb4)sizeof(m_ID),SQLT_INT,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)0,(ub4*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"��λ�ð�ʧ��!","д��LOB����",MB_ICONSTOP);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return FALSE ;		
	}
	/*
	sword OCIBindByPos ( 
	OCIStmt      *stmtp, //SQL�����OCIStmt
	OCIBind      **bindpp, //��Ͼ�� 
	OCIError     *errhp, //������
	ub4          position,// �󶨵�λ�� 
	dvoid        *valuep, //�󶨵ı�����
	sb4          value_sz,  //�󶨵ı��������� 	
	ub2          dty, //�󶨵�����
	dvoid        *indp, //ָʾ������ָ��(sb2����),������ʱΪNULL, 	
	ub2          *alenp, //˵��ִ��ǰ�󱻽�ϵ���������и�Ԫ������ʵ�ʵĳ��ȣ�������ʱΪNULL 	
	ub2          *rcodep, //�м�����������ָ�룬������ʱΪNULL 	
	ub4          maxarr_len, //���ļ�¼��,����ǵ����󶨣���Ϊ0 	
	ub4          *curelep, //�м�����������ָ�룬������ʱΪNULL 	
	ub4          mode	//=OCI_DEFAULT 
	); 
	*/


	//��λ�ð�,����һ�㰴�˷�ʽ��
	if(status= OCIDefineByPos(stmthp,&defhp,errhp,(ub4)1,(dvoid*)&lob_loc[0],
		(sb4)-1,(ub2)SQLT_BLOB,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"��λ�ö���ʧ��!","д��LOB����",MB_ICONSTOP);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return  FALSE;		
	}
	
	//ִ��SQL��� 
	if(status= OCIStmtExecute(svchp,stmthp,errhp,(ub4)1,(ub4)0,
		(CONST OCISnapshot*)0,(OCISnapshot*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"ִ��SQL���ʧ��!","д��LOB����",MB_ICONSTOP);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return  FALSE;		
	}
	
	/*
	sword OCIStmtExecute ( 
	OCISvcCtx           *svchp,  //���񻷾���� 
	OCIStmt             *stmtp,  //����� 
	OCIError            *errhp, //������
	ub4                 iters, // ** 
	ub4                 rowoff, //** 
	CONST OCISnapshot   *snap_in, 
	OCISnapshot         *snap_out, 
	ub4                 mode //** 
	); 
	**ע�� 
	1. iters:����select��䣬��˵��һ��ִ�ж�ȡ��buffer�еļ�¼�������������ȷ��
	select��������ص��������ɽ�iters����Ϊ0,��������������䣬iters��ʾ��Щ���
	��ִ�д�������ʱiters����Ϊ0�� 
	2. rowoff:�ڶ���ִ��ʱ���ò�����ʾ������ϵ����ݱ����еĵڼ�����¼��ʼִ��(����¼ƫ����)�� 
	3. mode��=OCI_DEFAULT:defaultģʽ 
	=OCI_DESCRIBE_ONLY������ģʽ��ֻ����ѡ���б��������Ϣ������ִ����� 
	=OCI_COMMIT_ON_SUCCESS���Զ��ύģʽ����ִ�гɹ����Զ��ύ�� 
	=OCI_EXACT_FETCH:��ȷ��ȡģʽ�� 
	=OCI_BATCH_ERRORS��������ִ��ģʽ������ִ�����鷽ʽ�Ĳ������ڴ�ģʽ�£�	����insert ,
	update,deleteʱ��ִ�й������κ�һ����¼���󲻻ᵼ������insert ,update,deleteʧ�ܣ�
	ϵͳ�Զ����ռ�������Ϣ�����ڷ�������ʽ�£����е��κ�һ����¼���󣬽��ᵼ����������ʧ�ܡ� 
	����: 
	ִ��һ�� 
	swResult = OCIStmtExecute(svchp, stmtp,  errhp, 1, 0, NULL, NULL, OCI_DEFAULT); 
	����ִ��100�Σ� 
	swResult = OCIStmtExecute(svchp, stmtp,  errhp,100, 0, NULL, NULL, OCI_DEFAULT); 
	
	*/


	CallbackWriteToLob(); 

	/*��Ӧ�ý�����������Ͽ�����ʱ������û��ʹ��OCITransCommit()���������
	�ύ�������л��������Զ��ع���*/
	if (status =OCITransCommit(svchp,errhp, (ub4)0))
	{
		Error_proc(errhp, status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return FALSE;
	}
	fclose(fp_OCI);

	return TRUE;
}

 
//�����ݿ��ж�ȡBLOB����
BOOL COCIclass::ReadBOLBDataFromDB(CString strFilename, CString strSQL, int m_ID)
{
	text *cp=NULL;
	text *selectlocator;
	
	selectlocator=(text*)(LPCTSTR)strSQL;
	

	//׼��SQL���
	if(status= OCIStmtPrepare(stmthp,errhp,selectlocator,
		(ub4)strlen((char*)selectlocator),(ub4)OCI_NTV_SYNTAX,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"׼��SQL���ʧ��!","��ȡ����",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return  FALSE;		
	}
		
	
	//��λ�ð�,����һ�㰴�˷�ʽ��
	if(status= OCIBindByPos(stmthp,&bndhp,errhp,(ub4)1,(dvoid*)&m_ID,
		(sb4)sizeof(m_ID),SQLT_INT,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)0,(ub4*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"��λ�ð�ʧ��!","��ȡ����",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return FALSE;		
	}
	
	
	//����������� 
	if(status= OCIDefineByPos(stmthp,&defhp,errhp,(ub4)1,(dvoid*)&lob_loc[0],
		(sb4)-1,(ub2)SQLT_BLOB,(dvoid*)0,(ub2*)0,(ub2*)0,(ub4)OCI_DEFAULT))
	{
			MessageBox(NULL,"��λ�ö���ʧ��!","��ȡ����",MB_ICONINFORMATION);
			Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return FALSE;		
	}
	/*
	sword OCIDefineByPos ( 
		OCIStmt     *stmtp, //����� 
		OCIDefine   **defnpp,//������������������� 
		OCIError    *errhp, //������
		ub4         position,//λ�����(��1 ��ʼ) 
		dvoid       *valuep, //����ı����� 
		sb4         value_sz, //�������� 
		ub2         dty,  //�������� 
		dvoid       *indp, //ָʾ������/ָʾ���������飬������ֶο��ܴ��ڿ�ֵ����Ҫָʾ������������������ʱΪNULL 
		ub2         *rlenp, //��ȡ�����ݳ��� 
		ub2         *rcodep, //�м�����������ָ�� 
		ub4         mode //OCI_DEFAULT 
	); 
	*/
	
	//ִ��SQL���
	if(status= OCIStmtExecute(svchp,stmthp,errhp,(ub4)1,(ub4)0,
		(CONST OCISnapshot*)0,(OCISnapshot*)0,(ub4)OCI_DEFAULT))
	{
		MessageBox(NULL,"ִ��SQL���ʧ��!","��ȡ����",MB_ICONINFORMATION);
		Error_proc(errhp,status);//��COI��������ֵ���д����жϲ�������ʾ��Ϣ
		return FALSE;		
	}

	//��Ӧ�ý�����������Ͽ�����ʱ,����û��ʹ��OCITransCommit()
	//����������ύ,�����л��������Զ��ع�
	OCITransCommit(svchp,errhp,(ub4)OCI_DEFAULT);//�ύһ������
	/*
	sword OCITransCommit ( 
	OCISvcCtx    *svchp,  //���񻷾���� 
	OCIError     *errhp, //������
	ub4          flags ); //OCI_DEFAULT 	
		*/


	fp_OCI=fopen(strFilename,"wb"); //���ⲿ�ļ�
	BOOL tb=TRUE;
	if(fp_OCI)
	{
		tb=CallbackReadLob();
	} 
	fclose(fp_OCI);	//�ر��ļ�
	return tb;

	
}

BOOL COCIclass::CallbackReadLob()
{
	ub4 offset=1,amtp=0;
	ub1 bufp[LOB_BUF_LEN];
	sword status;
	CString tt;
	ub4 loblengtht=0;	

	//���LOB�����ݳ���,�洢��loblength������
	OCILobGetLength(svchp,errhp,lob_loc[0],&loblengtht);

	if(loblengtht<=0) //���LOB�����ݳ���<=0�����ش���
		return FALSE;

	amtp=loblengtht;
	//��ȡLOB����
	if(status=OCILobRead(svchp,errhp,lob_loc[0],&amtp,offset,(dvoid*)bufp,
		(ub4)LOB_BUF_LEN,(dvoid*)0,callback_Read_OCI,(ub2)0,(ub1)SQLCS_IMPLICIT))
	{
		return FALSE;
		MessageBox(NULL,"��������!","��ȡLOB����",MB_ICONSTOP);
	}	
	return TRUE;
}
/*
OCILobRead(handle_service,handle_error,p_blob,&amt,1,read_buf+offset-1, (ub4)LOB_BUF_LEN,NULL,NULL ��); 
//������1��ʾ��һ�ζ���λ�ƣ�����ģʽ�£��˲�����amtһ����ֻ���ڵ�һ�ζ�ʱ��Ч 
//������NULL��ʾ�ص�����Ϊ�գ�������ģʽʹ����ѯ��polling�����������ǻص���callback������ 
//��ѯ�����£����û�ж���blobĩβ����������OCI_NEED_DATA����ȡ��ϣ�����OCI_SUCCESS 
�����ȡ��ϣ�OCI_NEED_DATA��������ѭ�� 

*/