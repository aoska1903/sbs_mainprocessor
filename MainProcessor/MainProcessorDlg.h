
// MainProcessorDlg.h : 헤더 파일
//

#pragma once
#include "LogWriter.h"
#include "MainMuduleControl.h"
#include "MainMMap.h"
#include "afxwin.h"

// CMainProcessorDlg 대화 상자
class CMainProcessorDlg : public CDialogEx
{
// 생성입니다.
public:
	CMainProcessorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAINPROCESSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

//변수
	CLogWriter *m_logwriter;//로그 기록자
	CMainMuduleControl *m_mainmudulecontrol;//모듈 관리자
	CMainMMap *m_mainmmap;//맵 관리자
	BOOL Bill_Shutter_Open;//지폐 셔터 열닫 유무
	BOOL Coin_Shutter_Open;//동전 셔터 열닫 유무
//함수
	void Processor_Run();//다른 프로세스 실행시키기
	void Processor_State_Change(int change_state);//다른 프로세서 요청에 따라 프로세서 상태 변경
	void Card_Wait();//RF에게 카드 태그할수있도록 활성화 보내기
	void Shutter_Open(int change_state);//해당 거래 금액 투입을 위한 동전, 지폐에게 셔터 열기 지시
	void Shutter_Clsoe();//동전, 지폐에게 셔터 닫기 지시
	void Card_Disabled();//카드 비활성화 지시
	void Bill_Shutter_Open_Result(int Shutter_Result);//지폐 셔터 열기 결과 
	void Coin_Shutter_Open_Result(int Shutter_Result);//동전 셔터 열기 결과
	INT Insert_Bill(int fare);//지폐투입
	INT Insert_Coin(int fare);//동전투입
	void Trasation_Cancel(int now_image_state);//거래중 취소 눌렀을 시 투입금0 셔터, 거래상태 거래X상태로 변경
	void Write_CardInfo(int kind_of_card);  //RF에게 받은 카드 기록 MM에 남기기
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg LRESULT COIN_Main_Message(WPARAM wParam, LPARAM lParam);//동전에서 메인에게 메시지 송신했을때 수신 이벤트처리 함수
	afx_msg LRESULT BILL_Main_Message(WPARAM wParam, LPARAM lParam);//지폐에서 메인에게 메시지 송신했을때 수신 이벤트처리 함수
	afx_msg LRESULT IMAGE_Main_Message(WPARAM wParam, LPARAM lParam);//이미지프로그램에서 메인에게 메시지 송신했을때 수신 이벤트처리 함수
	afx_msg LRESULT RF_Main_Message(WPARAM wParam, LPARAM lParam);//충전프로그램에서 메인에게 메시지 송신했을때 수신 이벤트처리 함수
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};
