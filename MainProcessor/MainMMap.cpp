#include "stdafx.h"
#include "MainMMap.h"

CMainMMap::CMainMMap()
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("MainMMap"), _T("03_MainMMap"));//�α� ���� �Լ�
	CreateMemoryMAP();//���� �޸� ���� �Լ�
	OpenMemoryMAP();//�޸𸮸� �д� �Լ�
}

CMainMMap::~CMainMMap()
{
	delete m_logwriter;//�Ҹ�
	m_logwriter = NULL;//�Ҹ�
	if (m_logwriter != NULL){
		AfxMessageBox(_T("m_logwriter�Ҹ� ����(MainMMap)"));
	}
}

void CMainMMap::Shutter_Open()//���� ���� ���� ��ȯ
{
	m_logwriter->WriteLogFile(_T("Shutter_Open����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->Coin_Shutter_Open = TRUE;//�������Ϳ���
	p_data->Bill_Shutter_Open = TRUE;//�������Ϳ���
	WriteMMF(p_data);//�޸� �� ����
}

int CMainMMap::state_change(int change_value)//��ġ���� �ö�� ���¿䱸�� ���� ���� ü����
{
	int change_before_state;//���� �� ����
	m_logwriter->WriteLogFile(_T("state_change ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	change_before_state = p_data->Now_State;//���� ���� ���¸� �ٲٱ��������� ���
	p_data->Now_State = change_value;//�Ű������� ���� ������ ���� ���� ����
	if(p_data->Now_State != change_value){
		return 0;//������ �ȵ��� �� 0����
	}
	m_logwriter->now_write_log.Format(_T("���º�ȭ [%s]-> [%s]"), Now_State_Contents[change_before_state], Now_State_Contents[change_value]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	WriteMMF(p_data);//�޸� �� ����
	return 1;
}

int CMainMMap::insert_coin(int fare)//���� �������� ��
{
	m_logwriter->WriteLogFile(_T("insert_coin ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	switch (fare)
	{
	case 500:
		p_data->insert_amount.Insert_Coin_500 += 500;
		break;
	case 100:
		p_data->insert_amount.Insert_Coin_100 += 100;
		break;
	case 50:
		p_data->insert_amount.Insert_Coin_50 += 50;
		break;
	case 10:
		p_data->insert_amount.Insert_Coin_10 += 10;
		break;
	default:
		break;
	}
	m_logwriter->now_write_log.Format(_T("���� ���� %d ���� ���� ����[500�� : %d�� 100�� %d�� 50�� : %d�� 10�� %d��]"), fare,
		p_data->insert_amount.Insert_Coin_500/500, p_data->insert_amount.Insert_Coin_100/100,
		p_data->insert_amount.Insert_Coin_50/50, p_data->insert_amount.Insert_Coin_10/10);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	p_data->insert_amount.Insert_Coin_SUM += fare;
	WriteMMF(p_data);//�޸� �� ����
	return fare;
}

int CMainMMap::insert_bill(int fare)//���� �������� ��
{
	m_logwriter->WriteLogFile(_T("insert_bill ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	switch (fare)
	{
	case 50000:
		p_data->insert_amount.Insert_Bill_50000 += 50000;
		break;
	case 10000:
		p_data->insert_amount.Insert_Bill_10000 += 10000;
		break;
	case 5000:
		p_data->insert_amount.Insert_Bill_5000 += 5000;
		break;
	case 1000:
		p_data->insert_amount.Insert_Bill_1000 += 1000;
		break;
	default:
		break;
	}
	m_logwriter->now_write_log.Format(_T("���� ���� %d ���� ���� ����[50000�� : %d�� 10000�� %d�� 5000�� : %d�� 1000�� %d��]"), fare,
		p_data->insert_amount.Insert_Bill_50000/50000, p_data->insert_amount.Insert_Bill_10000/10000,
		p_data->insert_amount.Insert_Bill_5000/5000, p_data->insert_amount.Insert_Bill_1000/10000);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	p_data->insert_amount.Insert_Bill_SUM += fare;
	WriteMMF(p_data);//�޸� �� ����
	return fare;
}

BOOL CMainMMap::init_insert(int now_image_state)//���� ���� �ʱ�ȭ�ϴ� �Լ�
{
	m_logwriter->WriteLogFile(_T("init_insert ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	m_logwriter->now_write_log.Format(_T("INIT BEFORE : {COIN(500(%d) 100(%d) 50(%d) 10(%d) COIN_SUM(%d)} {BILL(50000(%d) 10000(%d) 5000(%d) 1000(%d) BILL_SUM(%d)}")
		, p_data->insert_amount.Insert_Coin_500/500, p_data->insert_amount.Insert_Coin_100/100
		, p_data->insert_amount.Insert_Coin_50/50, p_data->insert_amount.Insert_Coin_10/10, p_data->insert_amount.Insert_Coin_SUM
		, p_data->insert_amount.Insert_Bill_50000, p_data->insert_amount.Insert_Bill_10000
		, p_data->insert_amount.Insert_Bill_5000, p_data->insert_amount.Insert_Bill_1000, p_data->insert_amount.Insert_Bill_SUM	);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	INSERT_AMOUNT init_insert_amount = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	p_data->insert_amount = init_insert_amount;//��� ���� 0�� INSERT_AMOUNT �ֱ�
	m_logwriter->now_write_log.Format(_T("INIT AFTER  : {COIN(500(%d) 100(%d) 50(%d) 10(%d) COIN_SUM(%d)} {BILL(50000(%d) 10000(%d) 5000(%d) 1000(%d) BILL_SUM(%d)}")
		, p_data->insert_amount.Insert_Coin_500/500, p_data->insert_amount.Insert_Coin_100/100
		, p_data->insert_amount.Insert_Coin_50/50, p_data->insert_amount.Insert_Coin_10/10, p_data->insert_amount.Insert_Coin_SUM
		, p_data->insert_amount.Insert_Bill_50000, p_data->insert_amount.Insert_Bill_10000
		, p_data->insert_amount.Insert_Bill_5000, p_data->insert_amount.Insert_Bill_1000, p_data->insert_amount.Insert_Bill_SUM	);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���

	if(now_image_state > main && now_image_state < recharge){//�Ǹ� �ŷ� ������ ���� ����� ���
		m_logwriter->now_write_log.Format(_T("INIT BEFORE : {Number_of_Cardsale (� : (%d)�� û�ҳ� : (%d)�� ����� : (%d)��) }")
			, p_data->number_of_cardsale.Number_of_Adult_Card, p_data->number_of_cardsale.Number_of_Adolescent_Card, p_data->number_of_cardsale.Number_of_Season_Ticket );
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		Number_of_Cardsale init_number_cardsale = {0, 0, 0};
		p_data->number_of_cardsale = init_number_cardsale;//��� ���� 0�� number_of_cardsale �ֱ�
		m_logwriter->now_write_log.Format(_T("INIT AFTER  : {Number_of_Cardsale (� : (%d)�� û�ҳ� : (%d)�� ����� : (%d)��) }")
			, p_data->number_of_cardsale.Number_of_Adult_Card, p_data->number_of_cardsale.Number_of_Adolescent_Card, p_data->number_of_cardsale.Number_of_Season_Ticket );
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
	if(now_image_state >= recharge && now_image_state < error){//���� �ŷ� ������ ���� ����� ���
		m_logwriter->now_write_log.Format(_T("INIT BEFORE : {infomation_traffic_card (ī������ : (%s) ī���ȣ : (%d) ī�� �ܾ� : (%d)) }")
			, Traffic_Card_Name[p_data->infomation_traffic_card.Kind_of_Card], p_data->infomation_traffic_card.Number_of_Card, p_data->infomation_traffic_card.Balance_of_Card );
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		Infomation_Traffic_Card init_traffic_card = {0, 0, 0};
		p_data->infomation_traffic_card = init_traffic_card;//��� ���� 0�� infomation_traffic_card �ֱ�
		m_logwriter->now_write_log.Format(_T("INIT AFTER  : {infomation_traffic_card (ī������ : (%s) ī���ȣ : (%d) ī�� �ܾ� : (%d)) }")
			, Traffic_Card_Name[p_data->infomation_traffic_card.Kind_of_Card], p_data->infomation_traffic_card.Number_of_Card, p_data->infomation_traffic_card.Balance_of_Card );
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
	WriteMMF(p_data);//�޸� �� ����
	return TRUE;
}

BOOL CMainMMap::MMap_Transtion_Ready_Change(int Ready_Flag)//���� Transation Ready  ���� �ٲٱ�
{
	m_logwriter->WriteLogFile(_T("MMap_Transtion_Ready_Change ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->Transtion_Ready = Ready_Flag;//������ �Ű������� ����
	WriteMMF(p_data);//�޸� �� ����
	return p_data->Transtion_Ready;//��ȭ�� Ʈ����� ��ȯ
}

INT CMainMMap::MMap_Write_CardInfo(int kind_of_card)//RF���� ���� ī�� ��� MM�� �����
{
	m_logwriter->WriteLogFile(_T("MMap_Write_CardInfo ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->infomation_traffic_card.Kind_of_Card = kind_of_card;//������ �Ű������� ����
	WriteMMF(p_data);//�޸� �� ����
	return p_data->infomation_traffic_card.Kind_of_Card;//��ȭ�� ī������ ��ȯ
}

BOOL CMainMMap::OpenMemoryMAP()//�޸𸮸� �д� �Լ�
{
	m_logwriter->WriteLogFile(_T("OpenMemoryMAP ����"));//LOG ���
	hMemoryMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, _T("fork_server"));
	if (!hMemoryMap) {
		m_logwriter->now_write_log.Format(_T("���� �޸𸮸� �� �� �����ϴ�. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		return FALSE;
	}
	else{
		m_logwriter->now_write_log.Format(_T("���� �޸𸮸� �������ϴ�. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!pMemoryMap) {
		m_logwriter->now_write_log.Format(_T("���� �޸𸮸� pMemoryMap�� �ű�� ����. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		return FALSE;
	}
	else{
		m_logwriter->now_write_log.Format(_T("���� �޸𸮸� pMemoryMap�� �Ű���ϴ�. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
	m_logwriter->WriteLogFile(_T("OpenMemoryMAP��"));//LOG ���
	::UnmapViewOfFile(pMemoryMap);//�����޸� ����
	return TRUE;
}

