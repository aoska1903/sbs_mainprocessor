#pragma once

#include "State.h"

class CLogWriter
{
public:
	CLogWriter();
	~CLogWriter();

public:
//변수
	CStdioFile file;//파일
	CString strLogPath;//로그 경로
	CString strTemp;//로그에 적을 내용(시간 : 내용)
	CFont m_font;//폰트
	DWORD	MAIN_ID;//메인 프로세서 ID
	HWND	MAIN_HWND;//메인 핸들
	SYSTEMTIME cur_time;//현재시간
	int Now_Date;//오늘 날짜
	CString Writer_Name;//Log 기록자 이름
	CString Date_Folder_Name;//Log 하위 폴더
	CString Module_Log_FolderName;//해당 로그 바로 상위 폴더 이름
	CString now_write_log;//로그에 기록할 내용
//함수
	void Log_Make(CString WriterName, CString FolderName);//로그 생성 함수
	void CreateLogFolder();	//로그 폴더 생성
	void CreateLogFile();	//로그 파일 생성
	void WriteLogFile(CString strContents);//로그내 기록
	void CreateFolder(CString csPath);//폴더 생성 함수
	void Find_Main_HWND();//메인 핸들찾기

	DWORD	FindProcessID(LPCTSTR szProcessName);	// 프로세스 이름으로 프로세스 ID 얻기
	ULONG	ProcIDFromWnd(HWND hwnd);				// 윈도우 핸들로 프로세스 아이디 얻기  
	HWND	GetWinHandle(ULONG pid);				// 프로세스 아이디로 윈도우 핸들 얻기
};

