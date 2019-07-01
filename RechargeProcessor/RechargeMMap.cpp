#include "stdafx.h"
#include "RechargeMMap.h"


CRechargeMMap::CRechargeMMap(void)
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("RechargeMMap"), _T("12_RechargeMMap"));//�α� ���� �Լ�
	Sleep(500);//MainMMap �޸𸮸� ���� ��
	if(OpenMemoryMAP()==TRUE)//�޸𸮸� �д� �Լ�
	{
		m_logwriter->WriteLogFile(_T("OpenMemoryMAP ����"));//LOG ���
	}
}

CRechargeMMap::~CRechargeMMap(void)
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

BOOL CRechargeMMap::OpenMemoryMAP()//�޸𸮸� �д� �Լ�
{
	m_logwriter->now_write_log.Format(_T("OpenMemoryMAP����"));
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
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
	m_logwriter->now_write_log.Format(_T("OpenMemoryMAP��"));
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	::UnmapViewOfFile(pMemoryMap);//�����޸� ����
	return TRUE;
}