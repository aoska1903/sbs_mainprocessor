#include  "stdafx.h"
#include  <tlhelp32.h>
#include "LogWriter.h"

CLogWriter::CLogWriter()
{
	Find_Main_HWND();//���� �ڵ�ã��
	m_font.CreatePointFont(100, _T("���� ���"));//��Ʈ����
}


CLogWriter::~CLogWriter()
{

}

void CLogWriter::Log_Make(CString WriterName, CString FolderName)//�α� ���� �Լ�
{
	Writer_Name = WriterName;//�ش� �α� ����� �̸� ����
	Module_Log_FolderName = FolderName;//�ش� �α� �ٷ� ���� ���� �̸� ����
	CreateLogFolder();//�α� ���� ����
	CreateLogFile();//�α� ���� ����
}

void CLogWriter::CreateLogFolder(){//�α� ���� ����
	GetLocalTime(&cur_time);//����ð� ��������
	Now_Date = (cur_time.wYear * 10000) + (cur_time.wMonth * 100) + cur_time.wDay;//���� �ð� ����

	Date_Folder_Name.Format(_T("%04d%02d%02d")
		, cur_time.wYear, cur_time.wMonth, cur_time.wDay);//��¥ �̸� ����
	Date_Folder_Name.Format(_T("C:\\SBS\\Log\\%s\\%s"), Date_Folder_Name, Module_Log_FolderName);//Log/��¥�̸����� ����
	CreateFolder(Date_Folder_Name);
}

void CLogWriter::CreateLogFile()//�α� ���� ����
{
	GetLocalTime(&cur_time);//����ð� ��������
	strLogPath.Format(_T("%s\\%04d%02d%02d.txt")//���� ��� ����
		, Date_Folder_Name, cur_time.wYear, cur_time.wMonth, cur_time.wDay);
	if (file.Open(strLogPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText) != FALSE){
		strTemp.Format("\r\n\r\n============ %s Log Start %02d��%02d��%02d��============\r\n\r\n", Writer_Name, cur_time.wHour, cur_time.wMinute, cur_time.wSecond);
		file.SeekToEnd();
		file.Write(strTemp, strTemp.GetLength());
		file.Close();
	}
}

void CLogWriter::WriteLogFile(CString strContents)//�α׳� ���
{
	GetLocalTime(&cur_time);//����ð� ��������
	strLogPath.Format(_T("%s\\%04d%02d%02d.txt")//���� ��� ����
		, Date_Folder_Name, cur_time.wYear, cur_time.wMonth, cur_time.wDay);
	if (file.Open(strLogPath, CFile::modeWrite | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText) != FALSE){//������ �����ٸ�
		file.SeekToEnd();
		strTemp.Format(_T("[%04d/%02d/%02d %02d:%02d:%02d.%03ld] %s\r\n"), cur_time.wYear, cur_time.wMonth, cur_time.wDay, cur_time.wHour, cur_time.wMinute, cur_time.wSecond, cur_time.wMilliseconds, strContents);
		file.Write(strTemp, strTemp.GetLength());
		file.Close();
	}
	else{//������ �ʴ´ٸ�
		int write_time = (cur_time.wYear * 10000) + (cur_time.wMonth * 100) + cur_time.wDay;;//��� �ð�
		if (write_time > Now_Date){//��¥�� ��������
			Now_Date = write_time;//��¥ ������ ��¥ ����
			CreateLogFile();	//�α����� ���� ����
			WriteLogFile(_T("��¥ ����"));//��¥����
			WriteLogFile(strContents);//����
		}
	}
}

void CLogWriter::CreateFolder(CString csPath)//���� ���� ����� �Լ�
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

void CLogWriter::Find_Main_HWND()//���� �ڵ�ã��
{
	MAIN_ID = FindProcessID(MAIN_NAME);//���� ���μ��� ID
	MAIN_HWND = GetWinHandle(MAIN_ID);//���� �ڵ�
}

DWORD CLogWriter::FindProcessID(LPCTSTR szProcessName)//<���μ��� �̸����� ���μ��� ID ���>
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

ULONG CLogWriter::ProcIDFromWnd(HWND hwnd) // ������ �ڵ�� ���μ��� ���̵� ���   
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