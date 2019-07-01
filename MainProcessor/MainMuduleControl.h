#pragma once

#include "LogWriter.h"
#include <psapi.h>
#include <tlhelp32.h>

class CMainMuduleControl
{
public:
	CMainMuduleControl();
	~CMainMuduleControl();
//����
	CString Moudlue_File_Path[(ImageProcessor + 1)];		//��� ���� ���
	CString Moudlue_File_Name[(ImageProcessor + 1)];		//��� ���� �̸�
	HANDLE  Module_Handle[(ImageProcessor + 1)];			//�ٸ� ��� �ڵ�

	CLogWriter *m_logwriter;								//�α� �����

	DWORD	module_PID[(ImageProcessor + 1)];				//�� ��� ���μ��� ID
	HWND	module_hwnd[(ImageProcessor + 1)];				//�� ��� �ڵ�

//�Լ�
	int		moduleprocess_run();					//��� ���α׷� ����
	int		moduleprocess_kill();					//��� ���α׷� ����
	CString get_mudule_path();						//���� ���� ��� ���
};

