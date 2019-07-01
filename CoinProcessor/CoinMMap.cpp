#include "stdafx.h"
#include "CoinMMap.h"

CCoinMMap::CCoinMMap(void)
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("CoinMMap"), _T("05_CoinMMap"));//�α� ���� �Լ�
	Sleep(500);//MainMMap �޸𸮸� ���� ��
	if(OpenMemoryMAP()==TRUE)//�޸𸮸� �д� �Լ�
	{
		m_logwriter->WriteLogFile(_T("OpenMemoryMAP ����"));//LOG ���
	}
}

CCoinMMap::~CCoinMMap(void)
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

void CCoinMMap::insert_coin(int Coin)//���γ��� ����*�ݾ׸�ŭ ����
{
	m_logwriter->WriteLogFile(_T("insert_coin ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->insert_amount.Insert_Coin_500 += Coin;
	WriteMMF(p_data);//�޸� �� ����
	m_logwriter->WriteLogFile(_T("������"));//LOG ���
}

void CCoinMMap::Coin_Shutter_Open()//���� ���� ����
{
	m_logwriter->WriteLogFile(_T("Coin_Shutter_Open ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->Coin_Shutter_Open = TRUE;//���� ���� ���� ���·� ��ȯ
	WriteMMF(p_data);//�޸� �� ����
	m_logwriter->WriteLogFile(_T("���� ���� ����"));//LOG ���
}

BOOL CCoinMMap::OpenMemoryMAP()//�޸𸮸� �д� �Լ�
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
