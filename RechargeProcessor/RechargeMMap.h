#pragma once

#include "mmap.h"

class CRechargeMMap :
	public CMMap
{
public:
	CRechargeMMap(void);
	~CRechargeMMap(void);
//변수
	CLogWriter *m_logwriter;
//함수
	BOOL OpenMemoryMAP();//메모리맵 읽는 함수
};

