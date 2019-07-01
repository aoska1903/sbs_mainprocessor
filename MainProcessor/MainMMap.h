#pragma once

#include"MMap.h"

class CMainMMap : 
	public CMMap
{
public:
	CMainMMap();
	~CMainMMap();

	void Shutter_Open();//셔터 열기 상태 전환
	int state_change(int change_value);//장치에서 올라온 상태요구에 따라 상태 체인지
	int insert_coin(int fare);//동전 투입했을 때
	int insert_bill(int fare);//지폐 투입했을 때
	BOOL init_insert(int now_image_state);//투입금 초기화하는 함수
	BOOL MMap_Transtion_Ready_Change(int Ready_Flag);//현재 Transation Ready 상태 바꾸기
	INT MMap_Write_CardInfo(int kind_of_card);//RF에게 받은 카드 기록 MM에 남기기
	BOOL OpenMemoryMAP();//메모리맵 읽는 함수
	
	int MMap_Now_State()//현재 상태 확인
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_State시작"));//LOG 기록
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//메모리 맵 읽기
		return p_data->Now_State;//현재 상태반환
	}

	BOOL MMap_Check_Transtion_Ready()//현재 Transation Ready 상태 확인
	{
		m_logwriter->WriteLogFile(_T("MMap_Check_Transtion_Ready 시작"));//LOG 기록
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//메모리 맵 읽기
		return p_data->Transtion_Ready;//현재의 트랜잭션 반환
	}
};

