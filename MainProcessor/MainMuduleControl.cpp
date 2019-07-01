#include "stdafx.h"
#include "MainMuduleControl.h"

CMainMuduleControl::CMainMuduleControl()
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("MainModuleControl"), _T("02_MainModuleControl"));//해당 폴더 및 파일 생성
}

CMainMuduleControl::~CMainMuduleControl()
{
	delete m_logwriter;//소멸
	m_logwriter = NULL;//소멸
}

int CMainMuduleControl::moduleprocess_run()//모듈 프로그램 실행
{
	m_logwriter->WriteLogFile(_T("moduleprocess_run 실행"));//LOG 기록
	int i;//탐색변수
	for (i = 0; i <= ImageProcessor; i++){//프로세서 개수만큼 실행
		Moudlue_File_Name[i].Format(_T("%s.exe"), Module_Processor_Name[i]);//해당 프로세서 이름 부여 1.BillProcessor 2.CoinProcessor 3.ImageProcessor 4.RechargeProcessor
		Moudlue_File_Path[i].Format(_T("C:/SBS/%s.exe"), Module_Processor_Name[i]);//해당 프로세서 경로 부여 1.BillProcessor 2.CoinProcessor 3.ImageProcessor 4.RechargeProcessor
		Module_Handle[i] = ShellExecute(NULL, "open", Moudlue_File_Path[i], "release", NULL, SW_SHOW);
		if (Module_Handle[i] == NULL){
			m_logwriter->now_write_log.Format(_T("%s.EXE 실행 실패"), Module_Processor_Name[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
			return i;//현재까지 성공한 프로세서 개수 반환
			//실패
		}
		else{
			m_logwriter->now_write_log.Format(_T("%s.exe 실행 성공"), Module_Processor_Name[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록//성공

			module_PID[i] = m_logwriter->FindProcessID(Moudlue_File_Name[i]);//실행성공 후 모듈이름으로 모듈 프로세스 ID찾기
			m_logwriter->now_write_log.Format(_T("%s PID : %d "), Moudlue_File_Name[i], module_PID[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		}
	}
	Sleep((ImageProcessor + 1)*200);//(모듈개수 * 0.2)초뒤 핸들 찾기
	for (i = 0; i <= ImageProcessor; i++){//프로세서 개수만큼 실행
		module_hwnd[i] = m_logwriter->GetWinHandle(module_PID[i]);//모듈PID로 핸들 찾은 후 담기

		if(module_hwnd[i] == NULL){
			m_logwriter->now_write_log.Format(_T("%s 핸들 변수 담기 실패"), Module_Processor_Name[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		}
		else{
			m_logwriter->now_write_log.Format(_T("%s 핸들 변수 담기 성공"), Module_Processor_Name[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		}
	}

	m_logwriter->now_write_log.Format(_T("프로세서 %d개 실행 성공"), i);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	return (ImageProcessor + 1);//모든 프로세서 실행시켰으면 모듈 개수 반환
}

int CMainMuduleControl::moduleprocess_kill()//모듈 프로그램 종료
{
	DWORD dwSize = 250;
	HANDLE hSnapShot;
	PROCESSENTRY32 pEntry;
	BOOL bCrrent = FALSE;
	int end_count = 0;//종료시킨 프로세스 개수
	int i;//탐색 변수

	m_logwriter->now_write_log.Format(_T("moduleprocess_kill 실행"));
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//log 기록

	// TH32CS_SNAPALL 옵션으로 모든 프로세스의 정보를 얻어냅니다.
	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);

	pEntry.dwSize = sizeof(pEntry);
	// Process32First 함수를 통해서 SnapShot에 들어 있는 첫번째 프로세스를 받아옵니다.
	Process32First(hSnapShot, &pEntry);
	// Tool이 실행중인지 확인
	while (1)
	{
		// Process32Next 함수를 통해서 pEntry 의 다음 프로세스를 스냅샷에서 받아 옵니다.
		BOOL hRes = Process32Next(hSnapShot, &pEntry);

		if (hRes == FALSE){
			break;
		}

		for (i = 0; i <= ImageProcessor; i++){//프로세서 개수만큼 실행
			if (!strncmp(pEntry.szExeFile, Moudlue_File_Name[i], 50))
			{
				m_logwriter->now_write_log.Format(_T("실행프로세서 중 %s 발견"), Moudlue_File_Name[i]);
				m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
				bCrrent = TRUE;
				break;
			}
		}

		if (bCrrent)
		{
			m_logwriter->now_write_log.Format(_T("%s 종료 진행"), Moudlue_File_Name[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
			HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pEntry.th32ProcessID);
			if (hProcess)
			{
				if (TerminateProcess(hProcess, 0))
				{
					unsigned long nCode; //프로세스 종료 상태
					GetExitCodeProcess(hProcess, &nCode);
				}
				if (CloseHandle(hProcess) == 1){
					end_count++;;//종료카운트 증가
					m_logwriter->now_write_log.Format(_T("%s 종료 완료 (프로세스 개수 : %d 개)"), Moudlue_File_Name[i], end_count);
					m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
				}
			}
			if (end_count == (ImageProcessor + 1)){//모든 프로세서 종료시켰으면 종료
				break;
			}
		}

	}
	m_logwriter->now_write_log.Format(_T("프로세서 %d개 종료 성공"), end_count);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	return end_count;//프로세서 종료시켰으면 종료시킨 모듈 개수 반환
}

CString CMainMuduleControl::get_mudule_path()//실행 파일 경로 얻기
{
	TCHAR path[_MAX_PATH];
	GetModuleFileName(NULL, path, sizeof path);

	CString strPath = path;
	int i = strPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.
	strPath = strPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.
	return(strPath);
}