
// ImageProcessor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CImageProcessorApp:
// �� Ŭ������ ������ ���ؼ��� ImageProcessor.cpp�� �����Ͻʽÿ�.
//

class CImageProcessorApp : public CWinApp
{
public:
	CImageProcessorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()

};

extern CImageProcessorApp theApp;