#pragma once

#include "mmap.h"

class CBillMMap :
	public CMMap
{
public:
	CBillMMap(void);
	~CBillMMap(void);
//����	
	CLogWriter *m_logwriter;
//�Լ�
	void insert_bill(int Bill);//���������ŭ ����
	BOOL OpenMemoryMAP();//�޸𸮸� �д� �Լ�
	void Bill_Shutter_Open();//���� ���� ����

	int MMap_Now_State()//���� ���� Ȯ��
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_State����"));//LOG ���
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//�޸� �� �б�
		return p_data->Now_State;//���� ���¹�ȯ
	}

};

