#include "stdafx.h"
#include "MainMMap.h"

CMainMMap::CMainMMap()
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("MainMMap"), _T("03_MainMMap"));//로그 생성 함수
	CreateMemoryMAP();//공유 메모리 생성 함수
	OpenMemoryMAP();//메모리맵 읽는 함수
}

CMainMMap::~CMainMMap()
{
	delete m_logwriter;//소멸
	m_logwriter = NULL;//소멸
	if (m_logwriter != NULL){
		AfxMessageBox(_T("m_logwriter소멸 실패(MainMMap)"));
	}
}

void CMainMMap::Shutter_Open()//셔터 열기 상태 전환
{
	m_logwriter->WriteLogFile(_T("Shutter_Open시작"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->Coin_Shutter_Open = TRUE;//동전셔터열기
	p_data->Bill_Shutter_Open = TRUE;//동전셔터열기
	WriteMMF(p_data);//메모리 맵 쓰기
}

int CMainMMap::state_change(int change_value)//장치에서 올라온 상태요구에 따라 상태 체인지
{
	int change_before_state;//변경 전 상태
	m_logwriter->WriteLogFile(_T("state_change 시작"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	change_before_state = p_data->Now_State;//지금 현재 상태를 바꾸기전변수에 담기
	p_data->Now_State = change_value;//매개변수로 들어온 값으로 현재 상태 변경
	if(p_data->Now_State != change_value){
		return 0;//변경이 안됐을 시 0리턴
	}
	m_logwriter->now_write_log.Format(_T("상태변화 [%s]-> [%s]"), Now_State_Contents[change_before_state], Now_State_Contents[change_value]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	WriteMMF(p_data);//메모리 맵 쓰기
	return 1;
}

int CMainMMap::insert_coin(int fare)//동전 투입했을 때
{
	m_logwriter->WriteLogFile(_T("insert_coin 시작"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	switch (fare)
	{
	case 500:
		p_data->insert_amount.Insert_Coin_500 += 500;
		break;
	case 100:
		p_data->insert_amount.Insert_Coin_100 += 100;
		break;
	case 50:
		p_data->insert_amount.Insert_Coin_50 += 50;
		break;
	case 10:
		p_data->insert_amount.Insert_Coin_10 += 10;
		break;
	default:
		break;
	}
	m_logwriter->now_write_log.Format(_T("동전 투입 %d 현재 지폐 투입[500원 : %d장 100원 %d장 50원 : %d장 10원 %d장]"), fare,
		p_data->insert_amount.Insert_Coin_500/500, p_data->insert_amount.Insert_Coin_100/100,
		p_data->insert_amount.Insert_Coin_50/50, p_data->insert_amount.Insert_Coin_10/10);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	p_data->insert_amount.Insert_Coin_SUM += fare;
	WriteMMF(p_data);//메모리 맵 쓰기
	return fare;
}

int CMainMMap::insert_bill(int fare)//지폐 투입했을 때
{
	m_logwriter->WriteLogFile(_T("insert_bill 시작"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	switch (fare)
	{
	case 50000:
		p_data->insert_amount.Insert_Bill_50000 += 50000;
		break;
	case 10000:
		p_data->insert_amount.Insert_Bill_10000 += 10000;
		break;
	case 5000:
		p_data->insert_amount.Insert_Bill_5000 += 5000;
		break;
	case 1000:
		p_data->insert_amount.Insert_Bill_1000 += 1000;
		break;
	default:
		break;
	}
	m_logwriter->now_write_log.Format(_T("지폐 투입 %d 현재 지폐 투입[50000원 : %d장 10000원 %d장 5000원 : %d장 1000원 %d장]"), fare,
		p_data->insert_amount.Insert_Bill_50000/50000, p_data->insert_amount.Insert_Bill_10000/10000,
		p_data->insert_amount.Insert_Bill_5000/5000, p_data->insert_amount.Insert_Bill_1000/10000);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	p_data->insert_amount.Insert_Bill_SUM += fare;
	WriteMMF(p_data);//메모리 맵 쓰기
	return fare;
}

BOOL CMainMMap::init_insert(int now_image_state)//투입 관련 초기화하는 함수
{
	m_logwriter->WriteLogFile(_T("init_insert 시작"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	m_logwriter->now_write_log.Format(_T("INIT BEFORE : {COIN(500(%d) 100(%d) 50(%d) 10(%d) COIN_SUM(%d)} {BILL(50000(%d) 10000(%d) 5000(%d) 1000(%d) BILL_SUM(%d)}")
		, p_data->insert_amount.Insert_Coin_500/500, p_data->insert_amount.Insert_Coin_100/100
		, p_data->insert_amount.Insert_Coin_50/50, p_data->insert_amount.Insert_Coin_10/10, p_data->insert_amount.Insert_Coin_SUM
		, p_data->insert_amount.Insert_Bill_50000, p_data->insert_amount.Insert_Bill_10000
		, p_data->insert_amount.Insert_Bill_5000, p_data->insert_amount.Insert_Bill_1000, p_data->insert_amount.Insert_Bill_SUM	);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	INSERT_AMOUNT init_insert_amount = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	p_data->insert_amount = init_insert_amount;//모든 값이 0인 INSERT_AMOUNT 넣기
	m_logwriter->now_write_log.Format(_T("INIT AFTER  : {COIN(500(%d) 100(%d) 50(%d) 10(%d) COIN_SUM(%d)} {BILL(50000(%d) 10000(%d) 5000(%d) 1000(%d) BILL_SUM(%d)}")
		, p_data->insert_amount.Insert_Coin_500/500, p_data->insert_amount.Insert_Coin_100/100
		, p_data->insert_amount.Insert_Coin_50/50, p_data->insert_amount.Insert_Coin_10/10, p_data->insert_amount.Insert_Coin_SUM
		, p_data->insert_amount.Insert_Bill_50000, p_data->insert_amount.Insert_Bill_10000
		, p_data->insert_amount.Insert_Bill_5000, p_data->insert_amount.Insert_Bill_1000, p_data->insert_amount.Insert_Bill_SUM	);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록

	if(now_image_state > main && now_image_state < recharge){//판매 거래 진행중 에서 취소한 경우
		m_logwriter->now_write_log.Format(_T("INIT BEFORE : {Number_of_Cardsale (어른 : (%d)장 청소년 : (%d)장 정기권 : (%d)장) }")
			, p_data->number_of_cardsale.Number_of_Adult_Card, p_data->number_of_cardsale.Number_of_Adolescent_Card, p_data->number_of_cardsale.Number_of_Season_Ticket );
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		Number_of_Cardsale init_number_cardsale = {0, 0, 0};
		p_data->number_of_cardsale = init_number_cardsale;//모든 값이 0인 number_of_cardsale 넣기
		m_logwriter->now_write_log.Format(_T("INIT AFTER  : {Number_of_Cardsale (어른 : (%d)장 청소년 : (%d)장 정기권 : (%d)장) }")
			, p_data->number_of_cardsale.Number_of_Adult_Card, p_data->number_of_cardsale.Number_of_Adolescent_Card, p_data->number_of_cardsale.Number_of_Season_Ticket );
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
	if(now_image_state >= recharge && now_image_state < error){//보충 거래 진행중 에서 취소한 경우
		m_logwriter->now_write_log.Format(_T("INIT BEFORE : {infomation_traffic_card (카드종류 : (%s) 카드번호 : (%d) 카드 잔액 : (%d)) }")
			, Traffic_Card_Name[p_data->infomation_traffic_card.Kind_of_Card], p_data->infomation_traffic_card.Number_of_Card, p_data->infomation_traffic_card.Balance_of_Card );
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		Infomation_Traffic_Card init_traffic_card = {0, 0, 0};
		p_data->infomation_traffic_card = init_traffic_card;//모든 값이 0인 infomation_traffic_card 넣기
		m_logwriter->now_write_log.Format(_T("INIT AFTER  : {infomation_traffic_card (카드종류 : (%s) 카드번호 : (%d) 카드 잔액 : (%d)) }")
			, Traffic_Card_Name[p_data->infomation_traffic_card.Kind_of_Card], p_data->infomation_traffic_card.Number_of_Card, p_data->infomation_traffic_card.Balance_of_Card );
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
	WriteMMF(p_data);//메모리 맵 쓰기
	return TRUE;
}

BOOL CMainMMap::MMap_Transtion_Ready_Change(int Ready_Flag)//현재 Transation Ready  상태 바꾸기
{
	m_logwriter->WriteLogFile(_T("MMap_Transtion_Ready_Change 시작"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->Transtion_Ready = Ready_Flag;//지정한 매개변수로 변경
	WriteMMF(p_data);//메모리 맵 쓰기
	return p_data->Transtion_Ready;//변화한 트랜잭션 반환
}

INT CMainMMap::MMap_Write_CardInfo(int kind_of_card)//RF에게 받은 카드 기록 MM에 남기기
{
	m_logwriter->WriteLogFile(_T("MMap_Write_CardInfo 시작"));//LOG 기록
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->infomation_traffic_card.Kind_of_Card = kind_of_card;//지정한 매개변수로 변경
	WriteMMF(p_data);//메모리 맵 쓰기
	return p_data->infomation_traffic_card.Kind_of_Card;//변화한 카드종류 반환
}

BOOL CMainMMap::OpenMemoryMAP()//메모리맵 읽는 함수
{
	m_logwriter->WriteLogFile(_T("OpenMemoryMAP 시작"));//LOG 기록
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

