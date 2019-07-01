#pragma once

#include <LogWriter.h>
#include <MMap.h>

class CCoinMMap :
	public CMMap
{
public:
	CCoinMMap(void);
	~CCoinMMap(void);
//변수	
	CLogWriter *m_logwriter;
//함수
	void insert_coin(int Coin);//코인넣은만큼 증가
	BOOL OpenMemoryMAP();//메모리맵 읽는 함수
	void Coin_Shutter_Open();//동전 셔터 열기

	int MMap_Now_State()//현재 상태 확인
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_State시작(Coin)"));//LOG 기록
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//메모리 맵 읽기
		return p_data->Now_State;//현재 상태반환
	}
};

