#pragma once

#include <LogWriter.h>
#include <MMap.h>

enum Cardsale_Kind{//�ݾ׼���ȭ�� ī�� ����
	cardsale_adult = 0,    //�ݾ׼���ȭ�鿡���� ������ � ī�� ��
	cardsale_adolescent,   //�ݾ׼���ȭ�鿡���� ������ û�ҳ� ī�� ��
	cardsale_season_ticket //�ݾ׼���ȭ�鿡���� ������ ����� ī�� ��
};

static const LPCSTR Cardsale_KindL[] = {
	_T("Adult"),
	_T("Adolescent"),
	_T("Season_Ticket")
};

class CImageMMap :
	public CMMap
{
public:
	CImageMMap(void);
	~CImageMMap(void);
//����
	CLogWriter *m_logwriter;
//�Լ�
	int check_change_image(int change_image);//ȭ�� ��ȯ �ϱ��� Ȯ��
	int update_cardsale_insert(int count_adult, int count_adolescent, int count_season_ticket, int fare);//�̹������� ������ ī�尳��, ī�� ������ ����
	BOOL OpenMemoryMAP();//�޸𸮸� �д� �Լ�

	int MMap_Now_State()//���� ���� Ȯ��
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_State����(image)"));//LOG ���
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//�޸� �� �б�
		return p_data->Now_State;//���� ���¹�ȯ
	}

	int MMap_Check_Transation_Ready()//���� Transation Ready ���� Ȯ��
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_Transation����"));//LOG ���
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//�޸� �� �б�
		return p_data->Transtion_Ready;//������ Ʈ����� ��ȯ
	}

	int MMap_Now_InsertMoney()//���� ���Ա� Ȯ��
	{
		m_logwriter->WriteLogFile(_T("MMap_Now_InsertMoney(image)"));//LOG ���
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//�޸� �� �б�
		return p_data->insert_amount.Insert_Bill_SUM + p_data->insert_amount.Insert_Coin_SUM;//���� ���¹�ȯ
	}

	int MMap_Check_Card_Kind()//���� Card_Kind ���� Ȯ��
	{
		m_logwriter->WriteLogFile(_T("MMap_Check_Card_Kind ����"));//LOG ���
		pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
		T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
		ReadMMF(p_data);//�޸� �� �б�
		return p_data->infomation_traffic_card.Kind_of_Card;//������ Ʈ����� ��ȯ
	}
};

