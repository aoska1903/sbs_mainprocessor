#include "LogWriter.h"
//구조체
//메모리 맵 주고 받을 데이터
typedef struct
{
	INT							Own_Adult_Card;				//어른 카드 개수
	INT							Own_Adolescent_Card;		//청소년 카드 개수
	INT							Own_Season_Ticket;			//정기권 카드 개수
	INT							Own_Coin_500;				//동전 보유 수량(500) 
	INT							Own_Coin_100;				//동전 보유 수량(100)
	INT							Own_Coin_50;				//동전 보유 수량(50)
	INT							Own_Coin_10;				//동전 보유 수량(10)
	INT							Own_Bill_50000;				//지폐 보유 수량(50000)
	INT							Own_Bill_10000;				//지폐 보유 수량(10000)
	INT							Own_Bill_5000;				//지폐 보유 수량(5000)
	INT							Own_Bill_1000;				//지폐 보유 수량(1000)
	INT							Own_Coin_SUM;				//동전 총 보유 수량
	INT							Own_Bill_SUM;				//지폐 총 보유 수량
}MACHINE_AMOUNT;//현재 기기 보유수량 데이터

typedef struct
{
	INT							Number_of_Adult_Card;		//구매할 어른 카드 개수
	INT							Number_of_Adolescent_Card;	//구매할 청소년 카드 개수
	INT							Number_of_Season_Ticket;	//구매할 정기권 카드 개수
}Number_of_Cardsale;//구매할 카드 개수

typedef struct
{
	INT							Kind_of_Card;				//카드 종류
	INT							Number_of_Card;				//카드 번호
	INT							Balance_of_Card;			//카드 잔액
}Infomation_Traffic_Card;//충전할 카드 정보

typedef struct
{
	INT							Insert_Coin_500;			//동전 투입 금액(500) 
	INT							Insert_Coin_100;			//동전 투입 금액(100)
	INT							Insert_Coin_50;				//동전 투입 금액(50)
	INT							Insert_Coin_10;				//동전 투입 금액(10)
	INT							Insert_Coin_SUM;			//동전 총 투입 금액

	INT							Insert_Bill_50000;			//지폐 투입 금액(50000)
	INT							Insert_Bill_10000;			//지폐 투입 금액(10000)
	INT							Insert_Bill_5000;			//지폐 투입 금액(5000)
	INT							Insert_Bill_1000;			//지폐 투입 금액(1000)
	INT							Insert_Bill_SUM;			//지폐 총 투입 금액
}INSERT_AMOUNT;//투입금액 관련 데이터

typedef struct
{
	BOOL						Coin_Shutter_Open;			//동전 장치 셔터 열었는지에 대한 변수//1(셔터열기) 2(셔터닫기)
	BOOL						Bill_Shutter_Open;			//지폐 장치 셔터 열었는지에 대한 변수//1(셔터열기) 2(셔터닫기)
	INSERT_AMOUNT				insert_amount;				//투입 금액 관련 데이터
	MACHINE_AMOUNT				machine_amount;				//기기 보유수량
	Number_of_Cardsale			number_of_cardsale;			//구매할 카드 개수
	Infomation_Traffic_Card		infomation_traffic_card;	//충전할 카드 정보
	INT							Now_State;					//현재상태
	BOOL						Transation_Ready;			//거래상태 1(준비완료) 0(준비미완료)
	INT							Recharge_Fare;				//충전 금액
	INT							Cardsale_Fare;				//카드 판매 (총)금액
}T_RECHARGE_DATA;//MMap 보충 충전 데이터

class CMMap
{
public:
	CMMap();
	~CMMap();

//변수
	HANDLE						hMemoryMap;					//메모리맵 핸들
	LPVOID						pMemoryMap;					//메모리맵 포인터

	CLogWriter *m_logwriter;//로그 기록자

	LPVOID						m_lpData;					// MMF에 사용되는 데이터
	HANDLE						m_hMutex;					// 뮤텍스 핸들
	DWORD						m_dwMapLength;				// Flush() 사용 할 데이터 크기

	T_RECHARGE_DATA *m_pData;//MMap 보충 충전 데이터 변수
//함수
	BOOL CreateMemoryMAP();//공유 메모리 생성 함수

	//----------------------------------------------------------------------//
	// Name : Flush
	// IN	: LPCTSTR lpMapName(맵 이름)
	// OUT	: 뮤텍스 이름
	// DESC	: MMFile을 Flush한다.
	//----------------------------------------------------------------------//
	BOOL Flush()
	{
		// 맵 데이터 유효성 확인
		if (m_lpData == NULL)
		{
			SetLastError(ERROR_INVALID_DATA);
			return FALSE;
		}
		return FlushViewOfFile(m_lpData, m_dwMapLength);
	}

	//----------------------------------------------------------------------//
	// Name : MMLock
	// IN	: DWORD dwTimeout(맵 이름)
	// OUT	: 메모리 맵 데이터
	// DESC	: 공유 데이터 사용을 위해 메모리 맵 lock
	//----------------------------------------------------------------------//
	_When_(return != 0, _Acquires_lock_(this->m_hMutex))
		LPVOID MMOpen(_In_ DWORD dwTimeout = INFINITE)
	{
		// 매개변수 유효성 확인
		if (m_lpData == NULL)
		{
			SetLastError(ERROR_INVALID_DATA);
			return NULL;
		}
		// 매개변수 유효성 확인
		ATLASSUME(m_hMutex != NULL); //Mutex should be valid
		// MMFile 동기화 접속을 위해 네임드 뮤텍스 사용
		return (WaitForSingleObject(m_hMutex, dwTimeout) == WAIT_OBJECT_0) ? m_lpData : NULL;
	}

	//----------------------------------------------------------------------//
	// Name : MMUnlock
	// IN	: 
	// OUT	: TRUE(성공) / FALSE(실패)
	// DESC	: 공유 데이터 사용 후 메모리 맵 해제
	//----------------------------------------------------------------------//
	_Releases_lock_(this->m_hMutex)
		BOOL MMClose()
	{
		// 매개변수 유효성 확인
		ATLASSUME(m_hMutex != NULL); //Mutex should be valid
		// flush 호출 - 20170426
		// 강제 쓰기
		Flush();
		return ReleaseMutex(m_hMutex);
	}

	BOOL WriteMMF(_In_ const T_RECHARGE_DATA *DestData)//메모리 맵 쓰기
	{
		m_pData = static_cast<T_RECHARGE_DATA*>(MMOpen());
		if (m_pData == 0){
			return FALSE;
		}
		CopyMemory(m_pData, DestData, sizeof(T_RECHARGE_DATA));
		return TRUE;
	}

	BOOL ReadMMF(_Inout_ T_RECHARGE_DATA *SrcData){//메모리 맵 읽기
		m_pData = static_cast<T_RECHARGE_DATA*>(MMOpen());
		if (m_pData == 0){
			return FALSE;
		}
		CopyMemory(SrcData, m_pData, sizeof(T_RECHARGE_DATA));
		return TRUE;
	}
};

