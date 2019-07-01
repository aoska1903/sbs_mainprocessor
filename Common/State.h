#define MAIN_NAME _T("MainProcessor.exe")

#define ADULT_CARD_FARE				2000
#define ADOLESCEMT_CARD_FARE		2000
#define SEASON_TICHET_FARE			2000

enum Now_State_enum{//���� ����
	  main 					//���� ����
	, cardsale				//ī�� �Ǹ� �ݾ� ���� ����
	, cardsale_insert		//ī�� �Ǹ� �ݾ� ���� ����
	, cardsale_processing   //ī�� �Ǹ� ���� ����
	, cardsale_lack			//ī�� �Ǹ� �Ž����� ���� ����
	, cardsale_success		//ī�� �Ǹ� ���� ����
	, cardsale_failure		//ī�� �Ǹ� ���� ����
	, card_wait				//ī�� ���� ��� ����
	, card_processing		//ī�� �ǵ� ��   ����
	, recharge				//ī�� ���� �ݾ� ���� ����
	, recharge_insert		//ī�� ���� �ݾ� ���� ����
	, recharge_processing   //ī�� ���� ���� ����
	, recharge_lack			//ī�� ���� �Ž����� ���� ����
	, recharge_success		//ī�� ���� ���� ����
	, recharge_failure		//ī�� ���� ���� ����
	, error					//���� ����
};

static const LPCSTR Now_State_Contents[] = {
	  _T("main")
	, _T("cardsale")
	, _T("cardsale_insert")
	, _T("cardsale_processing")
	, _T("cardsale_lack")
	, _T("cardsale_success")
	, _T("cardsale_failure")
	, _T("card_wait")
	, _T("card_processing")
	, _T("recharge")
	, _T("recharge_insert")
	, _T("recharge_processing")
	, _T("recharge_lack")
	, _T("recharge_success")
	, _T("recharge_failure")
	, _T("error_screen")
};

enum Module_Processor_Number{//���α׷� ��ȣ�Ҵ�
	  BillProcessor
	, CoinProcessor
	, RechargeProcessor
	, ImageProcessor
};

// Processor Name Declare
static const LPCSTR Module_Processor_Name[] = {//���α׷� �̸�
	  _T("BillProcessor")
	, _T("CoinProcessor")
	, _T("RechargeProcessor")
	, _T("ImageProcessor")
};

enum Transation_Number{//�ŷ� ���� ��ȣ �Ҵ�
	  Transation_None
	, Transation_Cardsale
	, Transation_Recharge
};

static const LPCSTR Transation_Name[] = {//�ŷ� �̸�
	  _T("None")
	, _T("Cardsale")
	, _T("Recharge")
};

enum Traffic_Card_Number{//���� ����ī�� ��ȣ �Ҵ�
	  card_none
	, hanaro
	, mybe
	, cashbbe
	, Tmoney
};

static const LPCSTR Traffic_Card_Name[] = {//���� ����ī�� �̸�
	  _T("none")
	, _T("hanaro")
	, _T("mybe")
	, _T("cashbbe")
	, _T("Tmoney")
};
