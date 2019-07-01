#include  "stdafx.h"
#include "MMap.h"

CMMap::CMMap()
{
}

CMMap::~CMMap()
{
}

BOOL CMMap::CreateMemoryMAP()//���� �޸� ���� �Լ�
{
	m_logwriter->WriteLogFile(_T("CreateMemoryMAP����"));//LOG ���
	/*****************************************************************/
	/* �������� Ŭ���̾�Ʈ�� ������ ������ Wave In Port�� �����Ѵ�. */
	/* �̶� ������ �����Ͽ� ���� �޸� �ʿ� �����͸� ����. */
	/* ������ Ŭ���̾�Ʈ�� 1:1 ��ġ�� fork ���� �� �޸� ���� �о */
	/* ������ Ŭ���̾�Ʈ�� ���������� ������ �����Ѵ�. */
	/****************************************************************/
	hMemoryMap = ::CreateFileMapping(
		(HANDLE)0xffffffff, // ���� ���� �ڵ�, �ʱ⿡ 0xffffffff�� �����Ѵ�.
		NULL, // ���� �Ӽ�
		PAGE_READWRITE, // �а�/���� �Ӽ�
		0, // 64��Ʈ ��巹���� ����Ѵ�. ���� 32��Ʈ - �޸��� ũ��
		sizeof(BYTE) * 130,// ���� 32��Ʈ - ���⼱LPBYTE Ÿ��.
		_T("fork_server"));// ���� ���ϸ��� �̸� - Uique �ؾ��Ѵ�.
	if (!hMemoryMap) {
		m_logwriter->now_write_log.Format(_T("���� �޸𸮸� ������ �� �����ϴ�. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		return FALSE;
	}
	else{
		m_logwriter->now_write_log.Format(_T("���� �޸𸮸� �����Ͽ����ϴ�. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
	pMemoryMap = (BYTE*)::MapViewOfFile(
		hMemoryMap, // ���ϸ��� �ڵ�
		FILE_MAP_ALL_ACCESS,		// �׼��� ��� - ����� ����
		0,							// �޸� ���۹��������� �̰ݵ� ���� 32��Ʈ 
		0, // �޸� ���۹��������� �̰ݵ� ���� 32��Ʈ
		0); // ����� �޸� ����� ũ�� - 0�̸� ������ ��ü �޸�
	if (!pMemoryMap) {
		m_logwriter->now_write_log.Format(_T("���� �޸𸮸� �� �� �����ϴ�. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		return FALSE;
	}
	else{
		m_logwriter->now_write_log.Format(_T("���� �޸𸮸� �������ϴ�. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
	m_logwriter->WriteLogFile(_T("CreateMemoryMAP��"));//LOG ���
	return TRUE;
}

