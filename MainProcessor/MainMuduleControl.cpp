#include "stdafx.h"
#include "MainMuduleControl.h"

CMainMuduleControl::CMainMuduleControl()
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("MainModuleControl"), _T("02_MainModuleControl"));//�ش� ���� �� ���� ����
}

CMainMuduleControl::~CMainMuduleControl()
{
	delete m_logwriter;//�Ҹ�
	m_logwriter = NULL;//�Ҹ�
}

int CMainMuduleControl::moduleprocess_run()//��� ���α׷� ����
{
	m_logwriter->WriteLogFile(_T("moduleprocess_run ����"));//LOG ���
	int i;//Ž������
	for (i = 0; i <= ImageProcessor; i++){//���μ��� ������ŭ ����
		Moudlue_File_Name[i].Format(_T("%s.exe"), Module_Processor_Name[i]);//�ش� ���μ��� �̸� �ο� 1.BillProcessor 2.CoinProcessor 3.ImageProcessor 4.RechargeProcessor
		Moudlue_File_Path[i].Format(_T("C:/SBS/%s.exe"), Module_Processor_Name[i]);//�ش� ���μ��� ��� �ο� 1.BillProcessor 2.CoinProcessor 3.ImageProcessor 4.RechargeProcessor
		Module_Handle[i] = ShellExecute(NULL, "open", Moudlue_File_Path[i], "release", NULL, SW_SHOW);
		if (Module_Handle[i] == NULL){
			m_logwriter->now_write_log.Format(_T("%s.EXE ���� ����"), Module_Processor_Name[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
			return i;//������� ������ ���μ��� ���� ��ȯ
			//����
		}
		else{
			m_logwriter->now_write_log.Format(_T("%s.exe ���� ����"), Module_Processor_Name[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���//����

			module_PID[i] = m_logwriter->FindProcessID(Moudlue_File_Name[i]);//���༺�� �� ����̸����� ��� ���μ��� IDã��
			m_logwriter->now_write_log.Format(_T("%s PID : %d "), Moudlue_File_Name[i], module_PID[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		}
	}
	Sleep((ImageProcessor + 1)*200);//(��ⰳ�� * 0.2)�ʵ� �ڵ� ã��
	for (i = 0; i <= ImageProcessor; i++){//���μ��� ������ŭ ����
		module_hwnd[i] = m_logwriter->GetWinHandle(module_PID[i]);//���PID�� �ڵ� ã�� �� ���

		if(module_hwnd[i] == NULL){
			m_logwriter->now_write_log.Format(_T("%s �ڵ� ���� ��� ����"), Module_Processor_Name[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		}
		else{
			m_logwriter->now_write_log.Format(_T("%s �ڵ� ���� ��� ����"), Module_Processor_Name[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		}
	}

	m_logwriter->now_write_log.Format(_T("���μ��� %d�� ���� ����"), i);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	return (ImageProcessor + 1);//��� ���μ��� ����������� ��� ���� ��ȯ
}

int CMainMuduleControl::moduleprocess_kill()//��� ���α׷� ����
{
	DWORD dwSize = 250;
	HANDLE hSnapShot;
	PROCESSENTRY32 pEntry;
	BOOL bCrrent = FALSE;
	int end_count = 0;//�����Ų ���μ��� ����
	int i;//Ž�� ����

	m_logwriter->now_write_log.Format(_T("moduleprocess_kill ����"));
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//log ���

	// TH32CS_SNAPALL �ɼ����� ��� ���μ����� ������ �����ϴ�.
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

	pEntry.dwSize = sizeof(pEntry);
	// Process32First �Լ��� ���ؼ� SnapShot�� ��� �ִ� ù��° ���μ����� �޾ƿɴϴ�.
	Process32First(hSnapShot, &pEntry);
	// Tool�� ���������� Ȯ��
	while (1)
	{
		// Process32Next �Լ��� ���ؼ� pEntry �� ���� ���μ����� ���������� �޾� �ɴϴ�.
		BOOL hRes = Process32Next(hSnapShot, &pEntry);

		if (hRes == FALSE){
			break;
		}

		for (i = 0; i <= ImageProcessor; i++){//���μ��� ������ŭ ����
			if (!strncmp(pEntry.szExeFile, Moudlue_File_Name[i], 50))
			{
				m_logwriter->now_write_log.Format(_T("�������μ��� �� %s �߰�"), Moudlue_File_Name[i]);
				m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
				bCrrent = TRUE;
				break;
			}
		}

		if (bCrrent)
		{
			m_logwriter->now_write_log.Format(_T("%s ���� ����"), Moudlue_File_Name[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pEntry.th32ProcessID);
			if (hProcess)
			{
				if (TerminateProcess(hProcess, 0))
				{
					unsigned long nCode; //���μ��� ���� ����
					GetExitCodeProcess(hProcess, &nCode);
				}
				if (CloseHandle(hProcess) == 1){
					end_count++;;//����ī��Ʈ ����
					m_logwriter->now_write_log.Format(_T("%s ���� �Ϸ� (���μ��� ���� : %d ��)"), Moudlue_File_Name[i], end_count);
					m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
				}
			}
			if (end_count == (ImageProcessor + 1)){//��� ���μ��� ����������� ����
				break;
			}
		}

	}
	m_logwriter->now_write_log.Format(_T("���μ��� %d�� ���� ����"), end_count);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	return end_count;//���μ��� ����������� �����Ų ��� ���� ��ȯ
}

CString CMainMuduleControl::get_mudule_path()//���� ���� ��� ���
{
	TCHAR path[_MAX_PATH];
	GetModuleFileName(NULL, path, sizeof path);

	CString strPath = path;
	int i = strPath.ReverseFind('\\');//���� ���� �̸��� ����� ���ؼ� ���ʿ� �ִ� '/'�� ã�´�.
	strPath = strPath.Left(i);//�ڿ� �ִ� ���� ���� ���� �̸��� �����.
	return(strPath);
}