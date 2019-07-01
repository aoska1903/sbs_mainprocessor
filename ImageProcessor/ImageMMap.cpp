#include "stdafx.h"
#include "ImageMMap.h"

CImageMMap::CImageMMap(void)
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("ImageMMap"), _T("09_ImageMMap"));//�α� ���� �Լ�
	Sleep(500);//MainMMap �޸𸮸� ���� ��
	if(OpenMemoryMAP()==TRUE)//�޸𸮸� �д� �Լ�
	{
		m_logwriter->WriteLogFile(_T("OpenMemoryMAP ����"));//LOG ���
	}
}

CImageMMap::~CImageMMap(void)
{
	delete m_logwriter;//�Ҹ�
	m_logwriter = NULL;//�Ҹ�
	if (m_logwriter == NULL) {
		AfxMessageBox(_T("m_logwriter �Ҹ� �Ϸ�(CoinMMap)"));
	}
	else{
		AfxMessageBox(_T("m_logwriter �Ҹ� ����(CoinMMap)"));
	}
}

int CImageMMap::check_change_image(int change_image)//ȭ�� ��ȯ �ϱ��� Ȯ��
{
	int compare;//�񱳰�
	m_logwriter->WriteLogFile(_T("check_change_image ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_READ, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	ReadMMF(p_data);
	compare = (change_image == p_data->Now_State ? 100 : p_data->Now_State);//���� ������ ȭ��� p_data->now_state ��ġ�ϴ� �� Ȯ��(������ 100 �ٸ��� p_data->Now_State)
	return compare;//�񱳰� ��ȯ
}

int CImageMMap::update_cardsale_insert(int count_adult, int count_adolescent, int count_season_ticket, int fare)//�̹������� ������ ī�尳��, ī�� ������ ����
{
	m_logwriter->WriteLogFile(_T("check_change_image ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->Cardsale_Fare = fare;
	p_data->number_of_cardsale.Number_of_Adult_Card = count_adult;
	p_data->number_of_cardsale.Number_of_Adolescent_Card = count_adolescent;
	p_data->number_of_cardsale.Number_of_Season_Ticket = count_season_ticket;
	WriteMMF(p_data);
	return p_data->Cardsale_Fare;//ī�� �� ��ȯ
}

BOOL CImageMMap::OpenMemoryMAP()//�޸𸮸� �д� �Լ�
{
	m_logwriter->WriteLogFile(_T("OpenMemoryMAP����"));//LOG ���
	// ���� ���ϸ��� �̸� - Uique �ؾ��Ѵ�.
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