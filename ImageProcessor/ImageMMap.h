#pragma once

#include <LogWriter.h>
#include <MMap.h>

enum Cardsale_Kind{//금액선택화면 카드 종류
	cardsale_adult = 0,    //금액선택화면에서의 구매할 어른 카드 수
	cardsale_adolescent,   //금액선택화면에서의 구매할 청소년 카드 수
	cardsale_season_ticket //금액선택화면에서의 구매할 정기권 카드 수
};

static const LPCSTR Cardsale_KindL[] = {
	_T("Adult"),
	_T("Adolescent"),
	_T("Season_Ticket")
};

class CImageMMap :
	public CMMap
{
public:
	CImageMMap(void);
	~CImageMMap(void);
//변수
	CLogWriter *m_logwriter;
//함수
	int check_change_image(int change_image);//화면 전환 하기전 확인
	int update_cardsale_insert(int count_adult, int count_adolescent, int count_season_ticket, int fare);//이미지에서 보내준 카드개수, 카드 값으로 갱신
	BOOL OpenMemoryMAP();//메모리맵 읽는 함수

	int MMap_Now_State()//현재 상태 확인
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_State시작(image)"));//LOG 기록
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//메모리 맵 읽기
		return p_data->Now_State;//현재 상태반환
	}

	int MMap_Check_Transation_Ready()//현재 Transation Ready 상태 확인
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_Transation시작"));//LOG 기록
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//메모리 맵 읽기
		return p_data->Transtion_Ready;//현재의 트랜잭션 반환
	}

	int MMap_Now_InsertMoney()//현재 투입금 확인
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_InsertMoney(image)"));//LOG 기록
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//메모리 맵 읽기
		return p_data->insert_amount.Insert_Bill_SUM + p_data->insert_amount.Insert_Coin_SUM;//현재 상태반환
	}

	int MMap_Check_Card_Kind()//현재 Card_Kind 상태 확인
	{
		m_logwriter->WriteLogFile(_T("MMap_Check_Card_Kind 시작"));//LOG 기록
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//메모리 맵 읽기
		return p_data->infomation_traffic_card.Kind_of_Card;//현재의 트랜잭션 반환
	}
};

