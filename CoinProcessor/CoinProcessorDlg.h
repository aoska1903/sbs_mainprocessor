
// CoinProcessorDlg.h : 헤더 파일
//

#pragma once

#include "LogWriter.h"
#include "CoinMMap.h"

// CCoinProcessorDlg 대화 상자
class CCoinProcessorDlg : public CDialogEx
{
// 생성입니다.
public:
	CCoinProcessorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_COINPROCESSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	afx_msg void OnDestroy();

//변수
	CLogWriter *m_logwriter;//로그 기록자
	CCoinMMap *m_coinmmap;//동전 MMap
	
	CButton m_coin_inset10;//10원 입력 버튼
	CButton m_coin_inset50;//50원 입력 버튼
	CButton m_coin_inset100;//100원 입력 버튼
	CButton m_coin_inset500;//500원 입력 버튼

//함수
	int Coin_Shutter_Open(int receive_state);//동전 셔터 열기 동작
	void Coin_Shutter_Close();//동전 셔터 닫기 동작
	void Coin_Insert_Fare(int fare);//동전 투입

	afx_msg void OnBnClickedButtonInsert500();//500동전 투입 버튼 눌렀을때
	afx_msg void OnBnClickedButtonInsert100();//100동전 투입 버튼 눌렀을때
	afx_msg void OnBnClickedButtonInsert50(); //50동전 투입 버튼 눌렀을때
	afx_msg void OnBnClickedButtonInsert10(); //10동전 투입 버튼 눌렀을때

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg LRESULT Main_COIN_Message(WPARAM wParam, LPARAM lParam);//메인에서 동전에게 메시지 송신했을때 수신 이벤트처리 함수
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
