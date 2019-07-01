
// BillProcessorDlg.h : 헤더 파일
//

#include "LogWriter.h"
#include "BillMMap.h"
#pragma once

// CBillProcessorDlg 대화 상자
class CBillProcessorDlg : public CDialogEx
{
// 생성입니다.
public:
	CBillProcessorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BILLPROCESSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	
//변수
	CLogWriter *m_logwriter;//로그 기록자
	CBillMMap *m_billmmap;//지폐 MMap

	CButton m_bill_inset1000;//1000원 입력 버튼
	CButton m_bill_inset5000;//5000원 입력 버튼
	CButton m_bill_inset10000;//10000원 입력 버튼
	CButton m_bill_inset50000;//50000원 입력 버튼

//함수
	int Bill_Shutter_Open(int receive_state);//지폐 셔터 열기 동작
	void BIll_Shutter_Close();//지폐 셔터 닫기 동작
	void Bill_Insert_Fare(int fare);//지폐 투입

	afx_msg void OnBnClickedButtonInsert1000();//1000지폐 투입 버튼 눌렀을때
	afx_msg void OnBnClickedButtonInsert5000();//5000지폐 투입 버튼 눌렀을때
	afx_msg void OnBnClickedButtonInsert10000();//10000지폐 투입 버튼 눌렀을때
	afx_msg void OnBnClickedButtonInsert50000();//50000지폐 투입 버튼 눌렀을때

// 구현입니다.
protected:

	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg LRESULT Main_BILL_Message(WPARAM wParam, LPARAM lParam);//메인에서 지폐에게 메시지 송신했을때 수신 이벤트처리 함수
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
