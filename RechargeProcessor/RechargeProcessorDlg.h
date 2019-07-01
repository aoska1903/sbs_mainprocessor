
// RechargeProcessorDlg.h : 헤더 파일
//

#include "LogWriter.h"
#include "RechargeMMap.h"
#pragma once


// CRechargeProcessorDlg 대화 상자
class CRechargeProcessorDlg : public CDialogEx
{
// 생성입니다.
public:
	CRechargeProcessorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_RECHARGEPROCESSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

//변수
	CButton m_button_cardtag;//카드 태그 버튼
	CButton m_button_no_cognize;//미인식 카드 태그 버튼
	CButton m_button_hanaro;//하나로 카드 태그 버튼
	CButton m_button_mybi;//마이비 카드 태그 버튼
	CButton m_button_cashbee;//캐시비 카드 태그 버튼
	CButton m_button_Tmoney;//티머니 카드 태그 버튼

	CLogWriter *m_logwriter;//로그 기록자
	CRechargeMMap *m_rechargemmap;//거래관련 MMap

//함수	
	void send_card_tag();				  //메인에게 카드 태그 보내기
	void send_card_result(int CardNum);			  //메인에게 카드 결과 보내기
	void card_disbled();					//메인에서 카드비활성화
	afx_msg void OnBnClickedButtonCardtag();  //카드 태그 버튼 눌렀을 때
	afx_msg void OnBnClickedButtonNoCognize();//태그한 카드가 미인식 카드일 때
	afx_msg void OnBnClickedButtonHanaro();   //태그한 카드가 하나로 카드일 때
	afx_msg void OnBnClickedButtonMybi();     //태그한 카드가 마이비 카드일 때
	afx_msg void OnBnClickedButtonCashbee();  //태그한 카드가 캐시비 카드일 때
	afx_msg void OnBnClickedButtonTmoney();   //태그한 카드가 티머니 카드일 때
	
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT Main_RF_Message(WPARAM wParam, LPARAM lParam);//메인에서 RF에게 메시지 송신했을때 수신 이벤트처리 함수
	DECLARE_MESSAGE_MAP()
};
