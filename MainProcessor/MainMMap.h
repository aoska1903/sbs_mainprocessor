#pragma once

#include"MMap.h"
#include "sqlite3.h"

class CMainMMap : 
	public CMMap
{
public:
	CMainMMap();
	~CMainMMap();
//변수
	sqlite3 *db;										// db handle
	CString db_path;									// db 경로
	int rc;												// sqlite함수 결과값 실패,성공 
	CString sql_query;									// sql 실행문	
	char *zErrMsg;										// sql 실행후 에러문
//함수
	INT DB_Table_Create();								//DB 및 table 생성 함수
	void Shutter_Open();								//셔터 열기 상태 전환
	int state_change(int change_value);					//장치에서 올라온 상태요구에 따라 상태 체인지
	int insert_coin(int fare);							//동전 투입했을 때
	int insert_bill(int fare);							//지폐 투입했을 때
	BOOL init_insert(int now_image_state);				//투입금 초기화하는 함수
	BOOL MMap_Transation_Ready_Change(int Ready_Flag);	//현재 Transation Ready 상태 바꾸기
	INT MMap_Write_CardInfo(int kind_of_card);			//RF에게 받은 카드 기록 MM에 남기기
	INT MMap_Transation_Create();						//거래 생성 함수
	BOOL OpenMemoryMAP();								//메모리맵 읽는 함수
	static int callback(void *NotUsed, int argc, char **argv, char **azColName);//콜백함수
	int MMap_Now_State()//현재 상태 확인
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_State시작"));//LOG 기록
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//메모리 맵 읽기
		return p_data->Now_State;//현재 상태반환
	}

	BOOL MMap_Check_Transation_Ready()//현재 Transation Ready 상태 확인
	{
		m_logwriter->WriteLogFile(_T("MMap_Check_Transation_Ready 시작"));//LOG 기록
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//메모리 맵 읽기
		return p_data->Transation_Ready;//현재의 트랜잭션 반환
	}
};

