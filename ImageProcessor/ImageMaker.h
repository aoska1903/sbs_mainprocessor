#pragma once

#include "LogWriter.h"
#include <psapi.h>
#include <tlhelp32.h>

#define VERSION _T("version : 2019062501")

enum Image_Name_enum{//사진 컨트롤 열거번호 Resource1000~
	  picture_main																			//메인 화면
	, picture_cardsale																		//카드 판매 금액 선택 화면
	, picture_cardsale_insert																//카드 판매 금액 투입 화면
	, picture_cardsale_processing															//카드 판매 진행 화면
	, picture_cardsale_lack																	//카드 판매 거스름 부족 화면
	, picture_cardsale_success																//카드 판매 성공 화면
	, picture_cardsale_failure																//카드 판매 실패 화면
	, picture_card_wait																		//카드 장착 대기 화면
	, picture_card_processing																//카드 판독 중 화면
	, picture_recharge																		//카드 충전 금액 선택 화면
	, picture_recharge_insert																//카드 충전 금액 투입 화면
	, picture_recharge_processing															//카드 충전	진행 화면
	, picture_recharge_lack																	//카드 충전 거스름 부족 화면
	, picture_recharge_success																//카드 충전	성공 화면
	, picture_recharge_failure																//카드 충전	실패 화면
	, picture_error																			//에러 화면
};

static const LPCSTR PICTURE_PATH[] = {//사진 컨트롤 경로
	  _T("C:\\SBS\\UI\\Passenger\\01_Menu\\KOR\\image\\bg.bmp")								//메인 화면
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_select_1600.bmp")			//카드 판매 금액 선택 화면
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_insert_1600.bmp")			//카드 판매 금액 투입 화면
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_process_1600.bmp")			//카드 판매 진행 화면
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_unchange_1600.bmp")			//카드 판매 거스름 부족 화면
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_result_1600.bmp")			//카드 판매 성공 화면
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_result_error_1600.bmp")		//카드 판매 실패 화면
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_cardon_1600.bmp")			//카드 장착 대기 화면
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_scanning_1600.bmp")		//카드 판독 중 화면
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_select_1600.bmp")			//카드 충전 금액 선택 화면
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_insert.bmp")				//카드 충전 금액 투입 화면
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_charging.bmp")			//카드 충전	진행 화면
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_unchange_1600.bmp")		//카드 충전 거스름 부족 화면
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_result.bmp")				//카드 충전	성공 화면
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_charge_fail.bmp")			//카드 충전	실패 화면
	, _T("C:\\SBS\\UI\\Passenger\\04_Common\\KOR\\image\\bg_ready.bmp")						//에러 화면
};

enum STATIC_NUMBER{//스태틱 컨트롤 열거번호 Resource1100~
	  m_static_number_adult																	//어른 카드 개수
	, m_static_number_adolescent															//청소년 카드 개수
	, m_static_number_season_ticket															//정기권 카드 개수
	, m_static_contents_card																//카드 구매 내용(ex 어른 : A 장 청소년 : B 장 정기권 : C 장)
	, m_static_cardsale_fare																//카드 판매 선택 화면 판매 운임 텍스트
	, m_static_cardsale_insert_fare															//카드 판매 투입 화면 투입 금액(운임)
	, m_static_cardsale_insert_amount														//카드 판매 투입 금액 사용자 직접 투입 금액
	, m_static_recharge_card_kind															//카드 충전 선택 화면 충전 카드 종류(하나로, 마이비, 캐시비, 티머니)
	, m_static_recharge_card_number															//카드 충전 선택 화면 충전 카드 번호
	, m_static_recharge_card_balance														//카드 충전 선택 화면 충전 카드 잔액
	, m_static_recharge_fare																//카드 충전 선택 화면 판매 운임 텍스트
	, m_static_recharge_insert_card_kind													//카드 충전 투입 화면 충전 카드 종류(하나로, 마이비, 캐시비, 티머니)
	, m_static_recharge_insert_card_balance													//카드 충전 투입 화면 충전 카드 잔액
	, m_static_recharge_insert_fare															//카드 충전 투입 화면 판매 운임 텍스트
	, m_static_recharge_insert_amount														//카드 충전 투입 화면 사용자 직접 투입 금액
	, m_static_version																		//버전 텍스트
};

static const LPCSTR STATIC_CONTENT[] = {//스태틱 내용
	  _T("0 장")																			//어른 카드 개수
	, _T("0 장")																			//청소년 카드 개수
	, _T("0 장")																			//정기권 카드 개수
	, _T("어른 : 0 장, 청소년 : 0 장, 정기권 : 0장")										//카드 구매 내용(ex 어른 : A 장 청소년 : B 장 정기권 : C 장)
	, _T("0 원")																			//카드 판매 선택 화면 판매 운임 텍스트
	, _T("0 원") 																			//카드 판매 투입 화면 투입 금액(운임)
	, _T("0 원")																			//카드 판매 투입 금액 사용자 직접 투입 금액
	, _T("티머니")																			//카드 충전 선택 화면 충전 카드 종류(하나로, 마이비, 캐시비, 티머니)
	, _T("1010009011443190")																//카드 충전 선택 화면 충전 카드 번호
	, _T("0 원")																			//카드 충전 선택 화면 충전 카드 잔액
	, _T("0 원")																			//카드 충전 선택 화면 판매 운임 텍스트
	, _T("티머니")																			//카드 충전 투입 화면 충전 카드 종류(하나로, 마이비, 캐시비, 티머니)
	, _T("0 원")																			//카드 충전 투입 화면 충전 카드 잔액
	, _T("0 원")																			//카드 충전 투입 화면 판매 운임 텍스트
	, _T("0 원")																			//카드 충전 투입 화면 사용자 직접 투입 금액
	, VERSION																				//버전 텍스트
};

enum BUTTON_NUMBER{//버튼 컨트롤 열거번호 Resource1500~
	  m_button_insert_ok = 0																//금액 투입 확인 버튼
	, m_button_cardsale 																	//판매버튼
	, m_button_recharge																		//충전버튼
	, m_button_cardsale_number3																//3매
	, m_button_cardsale_number2																//2매
	, m_button_cardsale_number1																//1매
	, m_button_cardsale_number0																//0매
	, m_button_kind_adult																	//어른 선택 버튼
	, m_button_kind_adolescent																//청소년 선택 버튼
	, m_button_kind_season_ticket															//정기권 선택 버튼
	, m_button_fare_5000																	// 5000원 운임 버튼
	, m_button_fare_10000																	//10000원 운임 버튼
	, m_button_fare_20000																	//20000원 운임 버튼
	, m_button_fare_30000																	//30000원 운임 버튼
	, m_button_fare_40000																	//40000원 운임 버튼
	, m_button_fare_50000																	//50000원 운임 버튼
	, m_button_before																		//이전(메인or금액간접선택)으로 가기
	, m_button_direct																		//직접입력으로 바꾸기
	, m_button_add_0																		//직접입력 0(입력값 열배)
	, m_button_add_1																		//직접입력 1
	, m_button_add_2																		//직접입력 2
	, m_button_add_3																		//직접입력 3
	, m_button_add_4																		//직접입력 4
	, m_button_add_5																		//직접입력 5
	, m_button_add_6																		//직접입력 6
	, m_button_add_7																		//직접입력 7
	, m_button_add_8																		//직접입력 8
	, m_button_add_9																		//직접입력 9
	, m_button_add_000																		//직접입력 000(입력값 천배)
	, m_button_erase																		//현재값 0으로 변경
	, m_button_cancle																		//취소버튼
};

static const LPCSTR BUTTTON_CONTENT[] = {//버튼 내용
	  _T("금액 확인")																		//금액 투입 확인 버튼						
	, _T("카드 판매")																		//판매버튼									
	, ("카드 충전")																			//충전버튼									
	, _T("3매")																				//3매										
	, _T("2매")																				//2매										
	, _T("1매")																				//1매										
	, _T("지움")																			//0매									
	, _T("어른")																			//어른 선택 버튼						   
	, _T("청소년")																			//청소년 선택 버튼						
	, _T("정기권")																			//정기권 선택 버튼						
	, _T("5,000원")																			// 5000원 운임 버튼							
	, _T("10,000원")																		//10000원 운임 버튼						
	, _T("20,000원")																		//20000원 운임 버튼						
	, _T("30,000원")																		//30000원 운임 버튼						
	, _T("40,000원")																		//40000원 운임 버튼						
	, _T("50,000원")																		//50000원 운임 버튼						
	, _T("이전")																			//이전(메인or금액간접선택)으로 가기	   
	, _T("직접입력")																		//직접입력으로 바꾸기						
	, _T("0")																				//직접입력 0(입력값 열배)					
	, _T("1")																				//직접입력 1								
	, _T("2")																				//직접입력 2								
	, _T("3")																				//직접입력 3								
	, _T("4")																				//직접입력 4								
	, _T("5")																				//직접입력 5								
	, _T("6")																				//직접입력 6								
	, _T("7")																				//직접입력 7								
	, _T("8")																				//직접입력 8								
	, _T("9")																				//직접입력 9								
	, _T("000")																				//직접입력 000(입력값 천배)				
	, _T("지움")																			//현재값 0으로 변경						
	, _T("취소")																			//취소버튼								
};

class CImageMaker
{				 
public:			 
	CImageMaker(void);
	~CImageMaker(void);
//변수
	
	HBITMAP			m_hBitmap_image[ (error + 1) ];											// Dialog에 배경이미지 입히기 위한 변수.//(recharge_failure + 1) : 화면개수
	CString			m_backimgpath[(error + 1)];												// 배경이미지 경로
	CStatic			m_picture_background[(error + 1)];										//배경 화면 사진컨트롤
	CRect			static_Rect[(m_static_version + 1)];									//스태틱 위치 및 크기
	CRect			button_Rect[(m_button_cancle + 1)];										//버튼 위치 및 크기
	CLogWriter		*m_logwriter;															//로그 기록자
	
//함수
	void background_make();																	//배경 생성
	void static_Rect_make();																//스태틱 컨트롤 위치 및 크기 생성
	void button_Rect_make();																//버튼 컨트롤 위치 및 크기 생성
};

