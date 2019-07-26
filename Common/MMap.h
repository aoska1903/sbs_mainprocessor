#include "LogWriter.h"
//����ü
//�޸� �� �ְ� ���� ������
typedef struct
{
	INT							Own_Adult_Card;				//� ī�� ����
	INT							Own_Adolescent_Card;		//û�ҳ� ī�� ����
	INT							Own_Season_Ticket;			//����� ī�� ����
	INT							Own_Coin_500;				//���� ���� ����(500) 
	INT							Own_Coin_100;				//���� ���� ����(100)
	INT							Own_Coin_50;				//���� ���� ����(50)
	INT							Own_Coin_10;				//���� ���� ����(10)
	INT							Own_Bill_50000;				//���� ���� ����(50000)
	INT							Own_Bill_10000;				//���� ���� ����(10000)
	INT							Own_Bill_5000;				//���� ���� ����(5000)
	INT							Own_Bill_1000;				//���� ���� ����(1000)
	INT							Own_Coin_SUM;				//���� �� ���� ����
	INT							Own_Bill_SUM;				//���� �� ���� ����
}MACHINE_AMOUNT;//���� ��� �������� ������

typedef struct
{
	INT							Number_of_Adult_Card;		//������ � ī�� ����
	INT							Number_of_Adolescent_Card;	//������ û�ҳ� ī�� ����
	INT							Number_of_Season_Ticket;	//������ ����� ī�� ����
}Number_of_Cardsale;//������ ī�� ����

typedef struct
{
	INT							Kind_of_Card;				//ī�� ����
	INT							Number_of_Card;				//ī�� ��ȣ
	INT							Balance_of_Card;			//ī�� �ܾ�
}Infomation_Traffic_Card;//������ ī�� ����

typedef struct
{
	INT							Insert_Coin_500;			//���� ���� �ݾ�(500) 
	INT							Insert_Coin_100;			//���� ���� �ݾ�(100)
	INT							Insert_Coin_50;				//���� ���� �ݾ�(50)
	INT							Insert_Coin_10;				//���� ���� �ݾ�(10)
	INT							Insert_Coin_SUM;			//���� �� ���� �ݾ�

	INT							Insert_Bill_50000;			//���� ���� �ݾ�(50000)
	INT							Insert_Bill_10000;			//���� ���� �ݾ�(10000)
	INT							Insert_Bill_5000;			//���� ���� �ݾ�(5000)
	INT							Insert_Bill_1000;			//���� ���� �ݾ�(1000)
	INT							Insert_Bill_SUM;			//���� �� ���� �ݾ�
}INSERT_AMOUNT;//���Աݾ� ���� ������

typedef struct
{
	BOOL						Coin_Shutter_Open;			//���� ��ġ ���� ���������� ���� ����//1(���Ϳ���) 2(���ʹݱ�)
	BOOL						Bill_Shutter_Open;			//���� ��ġ ���� ���������� ���� ����//1(���Ϳ���) 2(���ʹݱ�)
	INSERT_AMOUNT				insert_amount;				//���� �ݾ� ���� ������
	MACHINE_AMOUNT				machine_amount;				//��� ��������
	Number_of_Cardsale			number_of_cardsale;			//������ ī�� ����
	Infomation_Traffic_Card		infomation_traffic_card;	//������ ī�� ����
	INT							Now_State;					//�������
	BOOL						Transation_Ready;			//�ŷ����� 1(�غ�Ϸ�) 0(�غ�̿Ϸ�)
	INT							Recharge_Fare;				//���� �ݾ�
	INT							Cardsale_Fare;				//ī�� �Ǹ� (��)�ݾ�
}T_RECHARGE_DATA;//MMap ���� ���� ������

class CMMap
{
public:
	CMMap();
	~CMMap();

//����
	HANDLE						hMemoryMap;					//�޸𸮸� �ڵ�
	LPVOID						pMemoryMap;					//�޸𸮸� ������

	CLogWriter *m_logwriter;//�α� �����

	LPVOID						m_lpData;					// MMF�� ���Ǵ� ������
	HANDLE						m_hMutex;					// ���ؽ� �ڵ�
	DWORD						m_dwMapLength;				// Flush() ��� �� ������ ũ��

	T_RECHARGE_DATA *m_pData;//MMap ���� ���� ������ ����
//�Լ�
	BOOL CreateMemoryMAP();//���� �޸� ���� �Լ�

	//----------------------------------------------------------------------//
	// Name : Flush
	// IN	: LPCTSTR lpMapName(�� �̸�)
	// OUT	: ���ؽ� �̸�
	// DESC	: MMFile�� Flush�Ѵ�.
	//----------------------------------------------------------------------//
	BOOL Flush()
	{
		// �� ������ ��ȿ�� Ȯ��
		if (m_lpData == NULL)
		{
			SetLastError(ERROR_INVALID_DATA);
			return FALSE;
		}
		return FlushViewOfFile(m_lpData, m_dwMapLength);
	}

	//----------------------------------------------------------------------//
	// Name : MMLock
	// IN	: DWORD dwTimeout(�� �̸�)
	// OUT	: �޸� �� ������
	// DESC	: ���� ������ ����� ���� �޸� �� lock
	//----------------------------------------------------------------------//
	_When_(return != 0, _Acquires_lock_(this->m_hMutex))
		LPVOID MMOpen(_In_ DWORD dwTimeout = INFINITE)
	{
		// �Ű����� ��ȿ�� Ȯ��
		if (m_lpData == NULL)
		{
			SetLastError(ERROR_INVALID_DATA);
			return NULL;
		}
		// �Ű����� ��ȿ�� Ȯ��
		ATLASSUME(m_hMutex != NULL); //Mutex should be valid
		// MMFile ����ȭ ������ ���� ���ӵ� ���ؽ� ���
		return (WaitForSingleObject(m_hMutex, dwTimeout) == WAIT_OBJECT_0) ? m_lpData : NULL;
	}

	//----------------------------------------------------------------------//
	// Name : MMUnlock
	// IN	: 
	// OUT	: TRUE(����) / FALSE(����)
	// DESC	: ���� ������ ��� �� �޸� �� ����
	//----------------------------------------------------------------------//
	_Releases_lock_(this->m_hMutex)
		BOOL MMClose()
	{
		// �Ű����� ��ȿ�� Ȯ��
		ATLASSUME(m_hMutex != NULL); //Mutex should be valid
		// flush ȣ�� - 20170426
		// ���� ����
		Flush();
		return ReleaseMutex(m_hMutex);
	}

	BOOL WriteMMF(_In_ const T_RECHARGE_DATA *DestData)//�޸� �� ����
	{
		m_pData = static_cast<T_RECHARGE_DATA*>(MMOpen());
		if (m_pData == 0){
			return FALSE;
		}
		CopyMemory(m_pData, DestData, sizeof(T_RECHARGE_DATA));
		return TRUE;
	}

	BOOL ReadMMF(_Inout_ T_RECHARGE_DATA *SrcData){//�޸� �� �б�
		m_pData = static_cast<T_RECHARGE_DATA*>(MMOpen());
		if (m_pData == 0){
			return FALSE;
		}
		CopyMemory(SrcData, m_pData, sizeof(T_RECHARGE_DATA));
		return TRUE;
	}
};

