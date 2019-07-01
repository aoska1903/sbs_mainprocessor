#pragma once

#include "mmap.h"

class CBillMMap :
	public CMMap
{
public:
	CBillMMap(void);
	~CBillMMap(void);
//변수	
	CLogWriter *m_logwriter;
//함수
	void insert_bill(int Bill);//지폐넣은만큼 증가
	BOOL OpenMemoryMAP();//메모리맵 읽는 함수
	void Bill_Shutter_Open();//지폐 셔터 열기

	int MMap_Now_State()//현재 상태 확인
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_State시작"));//LOG 기록
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//메모리 맵 읽기
		return p_data->Now_State;//현재 상태반환
	}

};

