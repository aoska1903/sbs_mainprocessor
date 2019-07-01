
// ImageProcessorDlg.h : 헤더 파일
//

#pragma once

#define IDC_PICTURE_INITIAL 1000
#define IDC_STATIC_INITIAL	1100
#define IDC_BUTTON_INITIAL	1500

#include "LogWriter.h"
#include "ImageMMap.h"
#include "ImageMaker.h"

// CImageProcessorDlg 대화 상자
class CImageProcessorDlg : public CDialogEx
{
// 생성입니다.
public:
	CImageProcessorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	
// 대화 상자 데이터입니다.
	enum { IDD = IDD_IMAGEPROCESSOR_DIALOG };

#define NUMBER_CARD_FIND 3

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

public:
//변수
	INT				Now_Image_State;									//현재 상태
	INT				Now_Selete_Card;									//금액 선택 화면에서 현재 선택된 카드 종류
	INT				number_cards[NUMBER_CARD_FIND];						//버튼으로 입력한 카드 개수 ( 0 : 어른, 1 : 청소년, 2 : 정기권 )
	INT				cardsale_fare;										//카드선택화면에서 현재 선택한 카드들 총합 값
	INT				recharge_fare;										//충전 운임
	CString			static_text;										//스태틱 문구 업데이트용 텍스트
	BOOL			Direct_Screen;										//충전 금액 선택 직접금액선택인지(1.직접 금액 선택 2.간접 금액 선택(5000,10000) )
	CLogWriter		*m_logwriter;										//로그 기록자
	CImageMMap		*m_imagemmap;										//이미지 MMap
	CImageMaker		*m_imagemaker;										//이미지 컨트롤 생성 객체
//스태틱 컨트롤
	CStatic			m_static[(m_static_version + 1)];					//스태틱 배열
//버튼 컨트롤
	CButton			m_button[(m_button_cancle + 1)];					//버튼 배열
//함수
	void			control_make();										//컨트롤 생성
	void			background_make();									//배경 생성
	void			static_make();										//텍스트 생성
	void			button_make();										//버튼 생성
	void			control_collocate();								//컨트롤 배치
	void			background_collocate();								//배경화면배치
	void			Image_Screen_Change(int change_screen);				//화면 변경
	void			main_return_init();									//메인화면 돌아올때 초기화
	void			update_cardsale(int number);						//카드 매수 버튼 눌렀을 때 값 갱신
	void			cardsale_insert_update();							//확인눌렀을시 금액,카드개수 T_RECHARGE_DATA에 갱신
	void			select_recharge_fare(int fare);						//충전 금액 선택
	void			cardsale_insert_renew(int now_insert_money);		//카드 판매 투입상태에서 돈(동전 or 지폐) 투입 되었을 때
	void			recharge_insert_renew(int now_insert_money);		//카드 충전 투입상태에서 돈(동전 or 지폐)
	void			change_card_kind();									//MMap에서 읽어와 카드종류 표시
	void			enter_direct(int enter_num);						//숫자패드눌러서 직접 입력
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	//스태틱 투명하게
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT Main_Image_Message(WPARAM wParam, LPARAM lParam);	//메인에서 이미지프로그램에게 메시지 송신했을때 수신 이벤트 함수
	afx_msg void OnBnClickedINSERTOK();									//금액 투입 확인 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedCANCLE();									//CANCLE 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedCARDSALE();									//CARDSALE 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedRECHARGE();									//RECHARGE 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedCARDSALENUMBER3();							//CARDSALENUMBER3 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedCARDSALENUMBER2();							//CARDSALENUMBER2 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedCARDSALENUMBER1();							//CARDSALENUMBER1 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedCARDSALENUMBER0();							//CARDSALENUMBER0 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedNUMBERADULT();								//NUMBERADULT 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedNUMBERADOLESCEMT();							//NUMBERADULT 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedNUMBERSEASONTICKET();						//NUMBERADULT 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedFARE5000();									//충전 5000원 운임 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedFARE10000();								//충전 10000원 운임 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedFARE20000();								//충전 20000원 운임 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedFARE30000();								//충전 30000원 운임 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedFARE40000();								//충전 40000원 운임 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedFARE50000();								//충전 50000원 운임 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedBEFORE();									//이전 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedDIRECT();									//직접 입력 선택 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD0();										//직접 입력 0	 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD1();										//직접 입력 1	 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD2();										//직접 입력 2	 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD3();										//직접 입력 3	 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD4();										//직접 입력 4	 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD5();										//직접 입력 5	 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD6();										//직접 입력 6	 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD7();										//직접 입력 7	 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD8();										//직접 입력 8	 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD9();										//직접 입력 9	 버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedADD000();									//직접 입력 000  버튼 눌렀을 경우 이벤트
	afx_msg void OnBnClickedERASE();									//직접 입력 지움 버튼 눌렀을 경우 이벤트
	DECLARE_MESSAGE_MAP()
};
