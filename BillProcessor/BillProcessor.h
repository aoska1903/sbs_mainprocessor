
// BillProcessor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CBillProcessorApp:
// �� Ŭ������ ������ ���ؼ��� BillProcessor.cpp�� �����Ͻʽÿ�.
//

class CBillProcessorApp : public CWinApp
{
public:
	CBillProcessorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CBillProcessorApp theApp;