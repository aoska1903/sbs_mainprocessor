#pragma once

#include <LogWriter.h>
#include <MMap.h>

class CCoinMMap :
	public CMMap
{
public:
	CCoinMMap(void);
	~CCoinMMap(void);
//����	
	CLogWriter *m_logwriter;
//�Լ�
	void insert_coin(int Coin);//���γ�����ŭ ����
	BOOL OpenMemoryMAP();//�޸𸮸� �д� �Լ�
	void Coin_Shutter_Open();//���� ���� ����

	int MMap_Now_State()//���� ���� Ȯ��
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_State����(Coin)"));//LOG ���
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//�޸� �� �б�
		return p_data->Now_State;//���� ���¹�ȯ
	}
};

