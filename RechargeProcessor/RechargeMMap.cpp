#include "stdafx.h"
#include "RechargeMMap.h"


CRechargeMMap::CRechargeMMap(void)
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("RechargeMMap"), _T("12_RechargeMMap"));//로그 생성 함수
	Sleep(500);//MainMMap 메모리맵 생성 후
	if(OpenMemoryMAP()==TRUE)//메모리맵 읽는 함수
	{
		m_logwriter->WriteLogFile(_T("OpenMemoryMAP 성공"));//LOG 기록
	}
}

CRechargeMMap::~CRechargeMMap(void)
{
	delete m_logwriter;//소멸
	m_logwriter = NULL;//소멸
	if (m_logwriter == NULL) {
		AfxMessageBox(_T("m_logwriter 소멸 완료(BillMMap)"));
	}
	else{
		AfxMessageBox(_T("m_logwriter 소멸 실패(BillMMap)"));
	}
}

BOOL CRechargeMMap::OpenMemoryMAP()//메모리맵 읽는 함수
{
	m_logwriter->now_write_log.Format(_T("OpenMemoryMAP시작"));
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	// 공유 파일맵의 이름 - Uique 해야한다.
	hMemoryMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, _T("fork_server"));
	if (!hMemoryMap) {
		m_logwriter->now_write_log.Format(_T("공유 메모리를 열 수 없습니다. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		return FALSE;
	}
	else{
		m_logwriter->now_write_log.Format(_T("공유 메모리를 열었습니다. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!pMemoryMap) {
		m_logwriter->now_write_log.Format(_T("공유 메모리를 pMemoryMap에 옮기기 실패. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		return FALSE;
	}
	else{
		m_logwriter->now_write_log.Format(_T("공유 메모리를 pMemoryMap에 옮겼습니다. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
	m_logwriter->now_write_log.Format(_T("OpenMemoryMAP끝"));
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	::UnmapViewOfFile(pMemoryMap);//공유메모리 해제
	return TRUE;
}