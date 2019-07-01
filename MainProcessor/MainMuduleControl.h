#pragma once

#include "LogWriter.h"
#include <psapi.h>
#include <tlhelp32.h>

class CMainMuduleControl
{
public:
	CMainMuduleControl();
	~CMainMuduleControl();
//변수
	CString Moudlue_File_Path[(ImageProcessor + 1)];		//모듈 파일 경로
	CString Moudlue_File_Name[(ImageProcessor + 1)];		//모듈 파일 이름
	HANDLE  Module_Handle[(ImageProcessor + 1)];			//다른 모듈 핸들

	CLogWriter *m_logwriter;								//로그 기록자

	DWORD	module_PID[(ImageProcessor + 1)];				//각 모듈 프로세스 ID
	HWND	module_hwnd[(ImageProcessor + 1)];				//각 모듈 핸들

//함수
	int		moduleprocess_run();					//모듈 프로그램 실행
	int		moduleprocess_kill();					//모듈 프로그램 종료
	CString get_mudule_path();						//실행 파일 경로 얻기
};

