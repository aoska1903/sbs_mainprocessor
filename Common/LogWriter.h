#pragma once

#include "State.h"

class CLogWriter
{
public:
	CLogWriter();
	~CLogWriter();

public:
//����
	CStdioFile file;//����
	CString strLogPath;//�α� ���
	CString strTemp;//�α׿� ���� ����(�ð� : ����)
	CFont m_font;//��Ʈ
	DWORD	MAIN_ID;//���� ���μ��� ID
	HWND	MAIN_HWND;//���� �ڵ�
	SYSTEMTIME cur_time;//����ð�
	int Now_Date;//���� ��¥
	CString Writer_Name;//Log ����� �̸�
	CString Date_Folder_Name;//Log ���� ����
	CString Module_Log_FolderName;//�ش� �α� �ٷ� ���� ���� �̸�
	CString now_write_log;//�α׿� ����� ����
//�Լ�
	void Log_Make(CString WriterName, CString FolderName);//�α� ���� �Լ�
	void CreateLogFolder();	//�α� ���� ����
	void CreateLogFile();	//�α� ���� ����
	void WriteLogFile(CString strContents);//�α׳� ���
	void CreateFolder(CString csPath);//���� ���� �Լ�
	void Find_Main_HWND();//���� �ڵ�ã��

	DWORD	FindProcessID(LPCTSTR szProcessName);	// ���μ��� �̸����� ���μ��� ID ���
	ULONG	ProcIDFromWnd(HWND hwnd);				// ������ �ڵ�� ���μ��� ���̵� ���  
	HWND	GetWinHandle(ULONG pid);				// ���μ��� ���̵�� ������ �ڵ� ���
};

