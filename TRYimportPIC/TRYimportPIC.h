
// TRYimportPIC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTRYimportPICApp:
// �йش����ʵ�֣������ TRYimportPIC.cpp
//

class CTRYimportPICApp : public CWinApp
{
public:
	CTRYimportPICApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTRYimportPICApp theApp;