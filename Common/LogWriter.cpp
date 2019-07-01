#include  "stdafx.h"
#include  <tlhelp32.h>
#include "LogWriter.h"

CLogWriter::CLogWriter()
{
	Find_Main_HWND();//메인 핸들찾기
	m_font.CreatePointFont(100, _T("맑은 고딕"));//폰트설정
}


CLogWriter::~CLogWriter()
{

}

void CLogWriter::Log_Make(CString WriterName, CString FolderName)//로그 생성 함수
{
	Writer_Name = WriterName;//해당 로그 기록자 이름 변경
	Module_Log_FolderName = FolderName;//해당 로그 바로 상위 폴더 이름 변경
	CreateLogFolder();//로그 폴더 생성
	CreateLogFile();//로그 파일 생성
}

void CLogWriter::CreateLogFolder(){//로그 폴더 생성
	GetLocalTime(&cur_time);//현재시간 가져오기
	Now_Date = (cur_time.wYear * 10000) + (cur_time.wMonth * 100) + cur_time.wDay;//시작 시간 변경

	Date_Folder_Name.Format(_T("%04d%02d%02d")
		, cur_time.wYear, cur_time.wMonth, cur_time.wDay);//날짜 이름 폴더
	Date_Folder_Name.Format(_T("C:\\SBS\\Log\\%s\\%s"), Date_Folder_Name, Module_Log_FolderName);//Log/날짜이름폴더 생성
	CreateFolder(Date_Folder_Name);
}

void CLogWriter::CreateLogFile()//로그 파일 생성
{
	GetLocalTime(&cur_time);//현재시간 가져오기
	strLogPath.Format(_T("%s\\%04d%02d%02d.txt")//파일 경로 지정
		, Date_Folder_Name, cur_time.wYear, cur_time.wMonth, cur_time.wDay);
	if (file.Open(strLogPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText) != FALSE){
		strTemp.Format("\r\n\r\n============ %s Log Start %02d시%02d분%02d초============\r\n\r\n", Writer_Name, cur_time.wHour, cur_time.wMinute, cur_time.wSecond);
		file.SeekToEnd();
		file.Write(strTemp, strTemp.GetLength());
		file.Close();
	}
}

void CLogWriter::WriteLogFile(CString strContents)//로그내 기록
{
	GetLocalTime(&cur_time);//현재시간 가져오기
	strLogPath.Format(_T("%s\\%04d%02d%02d.txt")//파일 경로 지정
		, Date_Folder_Name, cur_time.wYear, cur_time.wMonth, cur_time.wDay);
	if (file.Open(strLogPath, CFile::modeWrite | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText) != FALSE){//파일이 열린다면
		file.SeekToEnd();
		strTemp.Format(_T("[%04d/%02d/%02d %02d:%02d:%02d.%03ld] %s\r\n"), cur_time.wYear, cur_time.wMonth, cur_time.wDay, cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds, strContents);
		file.Write(strTemp, strTemp.GetLength());
		file.Close();
	}
	else{//열리지 않는다면
		int write_time = (cur_time.wYear * 10000) + (cur_time.wMonth * 100) + cur_time.wDay;;//기록 시간
		if (write_time > Now_Date){//날짜가 지났으면
			Now_Date = write_time;//날짜 지나면 날짜 수정
			CreateLogFile();	//로그파일 새로 생성
			WriteLogFile(_T("날짜 변경"));//날짜변경
			WriteLogFile(strContents);//재기록
		}
	}
}

void CLogWriter::CreateFolder(CString csPath)//서브 폴더 만드는 함수
{
	CString csPrefix(_T("")), csToken(_T(""));
	int nStart = 0, nEnd;
	while ((nEnd = csPath.Find('\\', nStart)) >= 0)
	{
		CString csToken = csPath.Mid(nStart, nEnd - nStart);
		CreateDirectory(csPrefix + csToken, NULL);

		csPrefix += csToken;
		csPrefix += _T("\\");
		nStart = nEnd + 1;
	}
	csToken = csPath.Mid(nStart);
	CreateDirectory(csPrefix + csToken, NULL);
}

void CLogWriter::Find_Main_HWND()//메인 핸들찾기
{
	MAIN_ID = FindProcessID(MAIN_NAME);//메인 프로세서 ID
	MAIN_HWND = GetWinHandle(MAIN_ID);//메인 핸들
}

DWORD CLogWriter::FindProcessID(LPCTSTR szProcessName)//<프로세스 이름으로 프로세스 ID 얻기>
{
    DWORD dwPID = 0xFFFFFFFF;
    HANDLE hSnapShot = INVALID_HANDLE_VALUE;
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof( PROCESSENTRY32 );
    hSnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPALL, NULL );
    Process32First(hSnapShot, &pe);
    do
    {
        if(!_stricmp(szProcessName, pe.szExeFile))
        {
            dwPID = pe.th32ProcessID;
            break;
        }
    }
    while(Process32Next(hSnapShot, &pe));
    CloseHandle(hSnapShot);
    return dwPID;
}

ULONG CLogWriter::ProcIDFromWnd(HWND hwnd) // 윈도우 핸들로 프로세스 아이디 얻기   
{   
	ULONG idProc;
	::GetWindowThreadProcessId( hwnd, &idProc );   
	return idProc;   
}

HWND CLogWriter::GetWinHandle(DWORD dwPID)
{
	HWND hWnd = FindWindow(NULL, NULL);
	while (hWnd != NULL)
	{
		if (GetParent(hWnd) == NULL){
			DWORD dwProcId;
			GetWindowThreadProcessId(hWnd, &dwProcId);
			if (dwPID == dwProcId){
				return hWnd;
			}
		}
		hWnd = GetWindow(hWnd, GW_HWNDNEXT);
	}
	return NULL;
}