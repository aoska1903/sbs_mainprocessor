#include  "stdafx.h"
#include "MMap.h"

CMMap::CMMap()
{
}

CMMap::~CMMap()
{
}

BOOL CMMap::CreateMemoryMAP()//공유 메모리 생성 함수
{
	m_logwriter->WriteLogFile(_T("CreateMemoryMAP시작"));//LOG 기록
	/*****************************************************************/
	/* 서버에서 클라이언트의 접속을 받으면 Wave In Port를 오픈한다. */
	/* 이때 음성을 녹음하여 공유 메모리 맵에 데이터를 쓴다. */
	/* 각각의 클라이언트와 1:1 매치된 fork 들은 이 메모리 맵을 읽어서 */
	/* 각각의 클라이언트에 독립적으로 음성을 전송한다. */
	/****************************************************************/
	hMemoryMap = ::CreateFileMapping(
		(HANDLE)0xffffffff, // 파일 맵의 핸들, 초기에 0xffffffff를 설정한다.
		NULL, // 보안 속성
		PAGE_READWRITE, // 읽고/쓰기 속성
		0, // 64비트 어드레스를 사용한다. 상위 32비트 - 메모리의 크기
		sizeof(BYTE) * 130,// 하위 32비트 - 여기선LPBYTE 타입.
		_T("fork_server"));// 공유 파일맵의 이름 - Uique 해야한다.
	if (!hMemoryMap) {
		m_logwriter->now_write_log.Format(_T("공유 메모리를 생성할 수 없습니다. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		return FALSE;
	}
	else{
		m_logwriter->now_write_log.Format(_T("공유 메모리를 생성하였습니다. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
	pMemoryMap = (BYTE*)::MapViewOfFile(
		hMemoryMap, // 파일맵의 핸들
		FILE_MAP_ALL_ACCESS,		// 액세스 모드 - 현재는 쓰기
		0,							// 메모리 시작번지부터의 이격된 상위 32비트 
		0, // 메모리 시작번지부터의 이격된 하위 32비트
		0); // 사용할 메모리 블록의 크기 - 0이면 설정한 전체 메모리
	if (!pMemoryMap) {
		m_logwriter->now_write_log.Format(_T("공유 메모리를 열 수 없습니다. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		return FALSE;
	}
	else{
		m_logwriter->now_write_log.Format(_T("공유 메모리를 열었습니다. (%sMMap)"), m_logwriter->Writer_Name);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
	m_logwriter->WriteLogFile(_T("CreateMemoryMAP끝"));//LOG 기록
	return TRUE;
}

