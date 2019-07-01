#define MAIN_NAME _T("MainProcessor.exe")

#define ADULT_CARD_FARE				2000
#define ADOLESCEMT_CARD_FARE		2000
#define SEASON_TICHET_FARE			2000

enum Now_State_enum{//상태 열거
	  main 					//메인 상태
	, cardsale				//카드 판매 금액 선택 상태
	, cardsale_insert		//카드 판매 금액 투입 상태
	, cardsale_processing   //카드 판매 진행 상태
	, cardsale_lack			//카드 판매 거스름돈 부족 상태
	, cardsale_success		//카드 판매 성공 상태
	, cardsale_failure		//카드 판매 실패 상태
	, card_wait				//카드 장착 대기 상태
	, card_processing		//카드 판독 중   상태
	, recharge				//카드 충전 금액 선택 상태
	, recharge_insert		//카드 충전 금액 투입 상태
	, recharge_processing   //카드 충전 진행 상태
	, recharge_lack			//카드 충전 거스름돈 부족 상태
	, recharge_success		//카드 충전 성공 상태
	, recharge_failure		//카드 충전 실패 상태
	, error					//에러 상태
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

enum Module_Processor_Number{//프로그램 번호할당
	  BillProcessor
	, CoinProcessor
	, RechargeProcessor
	, ImageProcessor
};

// Processor Name Declare
static const LPCSTR Module_Processor_Name[] = {//프로그램 이름
	  _T("BillProcessor")
	, _T("CoinProcessor")
	, _T("RechargeProcessor")
	, _T("ImageProcessor")
};

enum Transation_Number{//거래 종류 번호 할당
	  Transation_None
	, Transation_Cardsale
	, Transation_Recharge
};

static const LPCSTR Transation_Name[] = {//거래 이름
	  _T("None")
	, _T("Cardsale")
	, _T("Recharge")
};

enum Traffic_Card_Number{//충전 교통카드 번호 할당
	  card_none
	, hanaro
	, mybe
	, cashbbe
	, Tmoney
};

static const LPCSTR Traffic_Card_Name[] = {//충전 교통카드 이름
	  _T("none")
	, _T("hanaro")
	, _T("mybe")
	, _T("cashbbe")
	, _T("Tmoney")
};
