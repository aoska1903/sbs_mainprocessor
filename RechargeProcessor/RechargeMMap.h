#pragma once

#include "mmap.h"

class CRechargeMMap :
	public CMMap
{
public:
	CRechargeMMap(void);
	~CRechargeMMap(void);
//����
	CLogWriter *m_logwriter;
//�Լ�
	BOOL OpenMemoryMAP();//�޸𸮸� �д� �Լ�
};

