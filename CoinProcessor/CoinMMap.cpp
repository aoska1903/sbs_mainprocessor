#include "stdafx.h"
#include "CoinMMap.h"

CCoinMMap::CCoinMMap(void)
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("CoinMMap"), _T("05_CoinMMap"));//로그 생성 함수
	Sleep(500);//MainMMap 메모리맵 생성 후
	if(OpenMemoryMAP()==TRUE)//메모리맵 읽는 함수
	{
		m_logwriter->WriteLogFile(_T("OpenMemoryMAP 성공"));//LOG 기록
	}
}

CCoinMMap::~CCoinMMap(void)
{
	delete m_logwriter;//소멸
	m_logwriter = NULL;//소멸
	if (m_logwriter == NULL) {
		AfxMessageBox(_T("m_logwriter 소멸 완료(CoinMMap)"));
	}
	else{
		AfxMessageBox(_T("m_logwriter 소멸 실패(CoinMMap)"));
	}
}

void CCoinMMap::insert_coin(int Coin)//코인넣은 개수*금액만큼 증가
{
	m_logwriter->WriteLogFile(_T("insert_coin 실행"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->insert_amount.Insert_Coin_500 += Coin;
	WriteMMF(p_data);//메모리 맵 쓰기
	m_logwriter->WriteLogFile(_T("값증가"));//LOG 기록
}

void CCoinMMap::Coin_Shutter_Open()//동전 셔터 열기
{
	m_logwriter->WriteLogFile(_T("Coin_Shutter_Open 실행"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->Coin_Shutter_Open = TRUE;//동전 셔터 열기 상태로 전환
	WriteMMF(p_data);//메모리 맵 쓰기
	m_logwriter->WriteLogFile(_T("동전 셔터 열기"));//LOG 기록
}

BOOL CCoinMMap::OpenMemoryMAP()//메모리맵 읽는 함수
{
	m_logwriter->WriteLogFile(_T("OpenMemoryMAP시작"));//LOG 기록
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
	m_logwriter->WriteLogFile(_T("OpenMemoryMAP끝"));//LOG 기록
	::UnmapViewOfFile(pMemoryMap);//공유메모리 해제
	return TRUE;
}
