
// MainProcessor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMainProcessorApp:
// �� Ŭ������ ������ ���ؼ��� MainProcessor.cpp�� �����Ͻʽÿ�.
//

class CMainProcessorApp : public CWinApp
{
public:
	CMainProcessorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMainProcessorApp theApp;