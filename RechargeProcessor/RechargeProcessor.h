
// RechargeProcessor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CRechargeProcessorApp:
// �� Ŭ������ ������ ���ؼ��� RechargeProcessor.cpp�� �����Ͻʽÿ�.
//

class CRechargeProcessorApp : public CWinApp
{
public:
	CRechargeProcessorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CRechargeProcessorApp theApp;