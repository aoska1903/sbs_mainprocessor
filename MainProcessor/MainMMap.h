#pragma once

#include"MMap.h"

class CMainMMap : 
	public CMMap
{
public:
	CMainMMap();
	~CMainMMap();

	void Shutter_Open();//���� ���� ���� ��ȯ
	int state_change(int change_value);//��ġ���� �ö�� ���¿䱸�� ���� ���� ü����
	int insert_coin(int fare);//���� �������� ��
	int insert_bill(int fare);//���� �������� ��
	BOOL init_insert(int now_image_state);//���Ա� �ʱ�ȭ�ϴ� �Լ�
	BOOL MMap_Transtion_Ready_Change(int Ready_Flag);//���� Transation Ready ���� �ٲٱ�
	INT MMap_Write_CardInfo(int kind_of_card);//RF���� ���� ī�� ��� MM�� �����
	BOOL OpenMemoryMAP();//�޸𸮸� �д� �Լ�
	
	int MMap_Now_State()//���� ���� Ȯ��
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_State����"));//LOG ���
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//�޸� �� �б�
		return p_data->Now_State;//���� ���¹�ȯ
	}

	BOOL MMap_Check_Transtion_Ready()//���� Transation Ready ���� Ȯ��
	{
		m_logwriter->WriteLogFile(_T("MMap_Check_Transtion_Ready ����"));//LOG ���
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//�޸� �� �б�
		return p_data->Transtion_Ready;//������ Ʈ����� ��ȯ
	}
};

