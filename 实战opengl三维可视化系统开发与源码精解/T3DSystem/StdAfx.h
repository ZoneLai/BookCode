// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BD8FF39F_D5C6_4316_A31B_EB7ED84348B4__INCLUDED_)
#define AFX_STDAFX_H__BD8FF39F_D5C6_4316_A31B_EB7ED84348B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//�����OpenGLͷ�ļ�������
#include <gl/glew.h>   //OpenGL��չ,ֻҪ����һ��glew.hͷ�ļ�������ʹ��gl,glu,glext,wgl,glx��ȫ������
#include <gl/glut.h>   //glut.hҪ����glew.h�ĺ���
#include <gl/glaux.h> //glaux.h�Ǹ���ͷ�ļ�

//�������������ѧ������,һЩ��ѧ����Ĺ�ʽ�ľ���ʵ���Ƿ���math.h���,
//������Ϳ���ֱ���ù�ʽ,�����ù�������ôʵ�ֹ�ʽ��
#include <math.h> //��ѧ������ͷ�ļ�

#include "SkinPPWTL.h"  //Ƥ���ļ�


//����axftmp1.h���ռ���ģ��(MFCģ����)��ͷ�ļ�,�����ڳ������õ���CArray,
// CObList�����ݽṹʱ,��ô�͵ü��ظ��ļ���
#include  <afxtempl.h> 


//����ADO���ļ�����ʹ����������ȷ����
#import "c:\program files\common files\system\ado\msado15.dll" no_namespace rename("EOF","adoEOF")
#include "icrsint.h"	
#include <adoid.h>		
#include <afxdb.h> 

#include "alCulateF.h"

//�����ȫ�ֱ���theApp�ĵ�����
#include "T3DSystem.h"
extern CT3DSystemApp theApp;

//�����OCI�ĵ�����
#include <oci.h>   
#include "OCIclass.h"
extern COCIclass myOci;//����OCI��ȫ�ֱ���

//ADO���ݿ�
extern _RecordsetPtr m_Recordset; 
extern variant_t RecordsAffected;
extern _variant_t Thevalue;  
extern _ConnectionPtr m_Connection;


#include "DesingScheme.h"
extern CDesingScheme myDesingScheme;

#include "GetDemInsertValue.h"
extern CGetDemInsertValue m_demInsert;

extern int m_currentSchemeIndexs;   

#include <mmsystem.h> //windows�����ý���йصĴ�����ӿڣ�ˢ��Ƶ�ʼ����õ�ʱ����㺯����timeGetTime()��Ҳ��mmsystem.h��

extern CArray<int,int>m_SchemeGrade;   
extern CArray<CString,CString>m_SchemeNames;  
extern CString m_currentSchemeNames;   
extern CString m_PrecurrentSchemeNames;   


extern char g_sAppPath[512];
extern char g_sMediaPath[512];
extern UINT g_Texture[100];

void CreateTexture(UINT textureArray[], LPSTR strFileName, int textureID);
void GetFilePath(char * filename);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BD8FF39F_D5C6_4316_A31B_EB7ED84348B4__INCLUDED_)
