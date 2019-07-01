#include "stdafx.h"
#include "BillMMap.h"

CBillMMap::CBillMMap(void)
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("BillMMap"), _T("07_BillMMap"));//�α� ���� �Լ�
	Sleep(500);//MainMMap �޸𸮸� ���� ��
	if(OpenMemoryMAP()==TRUE)//�޸𸮸� �д� �Լ�
	{
		m_logwriter->WriteLogFile(_T("OpenMemoryMAP ����"));//LOG ���
	}
}

CBillMMap::~CBillMMap(void)
{
	delete m_logwriter;//�Ҹ�
	m_logwriter = NULL;//�Ҹ�
	if (m_logwriter == NULL) {
		AfxMessageBox(_T("m_logwriter �Ҹ� �Ϸ�(BillMMap)"));
	}
	else{
		AfxMessageBox(_T("m_logwriter �Ҹ� ����(BillMMap)"));
	}
}

void CBillMMap::insert_bill(int Bill)//������� ���*�ݾ׸�ŭ ����
{
	m_logwriter->WriteLogFile(_T("insert_bill ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->insert_amount.Insert_Bill_1000 += Bill;
	WriteMMF(p_data);//�޸� �� ����
	m_logwriter->WriteLogFile(_T("������"));//LOG ���
}

BOOL CBillMMap::OpenMemoryMAP()//�޸𸮸� �д� �Լ�
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

void CBillMMap::Bill_Shutter_Open()//���� ���� ����
{
	m_logwriter->WriteLogFile(_T("Bill_Shutter_Open ����"));//LOG ���
	pMemoryMap = ::MapViewOfFile(hMemoryMap, FILE_MAP_WRITE, 0, 0, 0);
	T_RECHARGE_DATA *p_data = static_cast<T_RECHARGE_DATA*>(pMemoryMap);
	p_data->Bill_Shutter_Open = TRUE;//���� ���� ���� ���·� ��ȯ
	WriteMMF(p_data);//�޸� �� ����
	m_logwriter->WriteLogFile(_T("���� ���� ����"));//LOG ���
}