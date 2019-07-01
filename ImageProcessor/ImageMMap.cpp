#include "stdafx.h"
#include "ImageMMap.h"

CImageMMap::CImageMMap(void)
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("ImageMMap"), _T("09_ImageMMap"));//로그 생성 함수
	Sleep(500);//MainMMap 메모리맵 생성 후
	if(OpenMemoryMAP()==TRUE)//메모리맵 읽는 함수
	{
		m_logwriter->WriteLogFile(_T("OpenMemoryMAP 성공"));//LOG 기록
	}
}

CImageMMap::~CImageMMap(void)
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

int CImageMMap::check_change_image(int change_image)//화면 전환 하기전 확인
{
	int compare;//비교값
	m_logwriter->WriteLogFile(_T("check_change_image 실행"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	ReadMMF(p_data);
	compare = (change_image == p_data->Now_State ? 100 : p_data->Now_State);//현재 변경할 화면과 p_data->now_state 일치하는 지 확인(같으면 100 다르면 p_data->Now_State)
	return compare;//비교값 반환
}

int CImageMMap::update_cardsale_insert(int count_adult, int count_adolescent, int count_season_ticket, int fare)//이미지에서 보내준 카드개수, 카드 값으로 갱신
{
	m_logwriter->WriteLogFile(_T("check_change_image 실행"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->Cardsale_Fare = fare;
	p_data->number_of_cardsale.Number_of_Adult_Card = count_adult;
	p_data->number_of_cardsale.Number_of_Adolescent_Card = count_adolescent;
	p_data->number_of_cardsale.Number_of_Season_Ticket = count_season_ticket;
	WriteMMF(p_data);
	return p_data->Cardsale_Fare;//카드 값 반환
}

BOOL CImageMMap::OpenMemoryMAP()//메모리맵 읽는 함수
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