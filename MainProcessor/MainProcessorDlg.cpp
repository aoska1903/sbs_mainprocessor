
// MainProcessorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MainProcessor.h"
#include "MainProcessorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainProcessorDlg 대화 상자

CMainProcessorDlg::CMainProcessorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainProcessorDlg::IDD, pParent)
	, m_logwriter(new CLogWriter())
	, m_mainmudulecontrol(new CMainMuduleControl())
	, m_mainmmap(new CMainMMap())
	, Bill_Shutter_Open(FALSE)
	, Coin_Shutter_Open(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMainProcessorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainProcessorDlg, CDialogEx)
	ON_MESSAGE(UM_COIN_MAIN_MESSAGE, CMainProcessorDlg::COIN_Main_Message)//동전에서 메인에게 메시지 송신했을때 수신 이벤트처리
	ON_MESSAGE(UM_BILL_MAIN_MESSAGE, CMainProcessorDlg::BILL_Main_Message)//지폐에서 메인에게 메시지 송신했을때 수신 이벤트처리
	ON_MESSAGE(UM_IMAGE_MAIN_MESSAGE, CMainProcessorDlg::IMAGE_Main_Message)//이미지프로그램에서 메인에게 메시지 송신했을때 수신 이벤트처리
	ON_MESSAGE(UM_RF_MAIN_MESSAGE, CMainProcessorDlg::RF_Main_Message)//충전프로그램에서 메인에게 메시지 송신했을때 수신 이벤트처리
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMainProcessorDlg 메시지 처리기

BOOL CMainProcessorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_logwriter->Log_Make(_T("MainProcessor"), _T("01_Main"));//해당 폴더 및 파일 생성

	Processor_Run();//다른 프로세스 실행시키기
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMainProcessorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMainProcessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainProcessorDlg::Processor_Run()//다른 프로세스 실행시키기
{
	m_mainmudulecontrol->moduleprocess_run();//다른 모듈 프로세서 실행
}

void CMainProcessorDlg::Processor_State_Change(int change_state)//다른 프로세서 요청에 따라 프로세서 상태 변경
{
	if(m_mainmmap->state_change(change_state) == 1){//p_Data now_state를 매개변수값으로 변경 성공한 경우
		m_logwriter->now_write_log.Format(_T("T_RECHARGE_DATA [%s] 상태 변경 성공"), Now_State_Contents[change_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
	else{
		m_logwriter->now_write_log.Format(_T("T_RECHARGE_DATA [%s] 상태 변경 실패..."), Now_State_Contents[change_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
	if(m_mainmudulecontrol->module_hwnd[ImageProcessor]==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[ImageProcessor] 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->now_write_log.Format(_T("이미지 프로세서에게 T_RECHARGE_DATA [%s] 상태 변경 완료 및 화면 변경 요청 메시지 송신 완료"), Now_State_Contents[change_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		::SendMessage(m_mainmudulecontrol->module_hwnd[ImageProcessor], UM_MAIN_IMAGE_MESSAGE, change_state, 0);//이미지프로그램에게 메세지(메인->이미지) 전송
	}
}

void CMainProcessorDlg::Card_Wait()//RF에게 카드 태그할수있도록 활성화 보내기
{
	if(m_mainmudulecontrol->module_hwnd[RechargeProcessor]==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[RechargeProcessor] 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile(_T("RF 프로세서에게 활성화 송신 완료"));//LOG 기록
		::SendMessage(m_mainmudulecontrol->module_hwnd[RechargeProcessor], UM_MAIN_RF_MESSAGE, card_wait, 0);//RF 프로그램에게 메세지(메인->RF) 전송
	}
}

void CMainProcessorDlg::Shutter_Open(int change_state)//금액 투입을 위한 동전, 지폐에게 셔터 열기 지시
{
	if(m_mainmudulecontrol->module_hwnd[BillProcessor]==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[BillProcessor] 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile(_T("지폐 프로세서에게 셧터 열기 명령 송신 완료"));//LOG 기록
		::SendMessage(m_mainmudulecontrol->module_hwnd[BillProcessor], UM_MAIN_BILL_MESSAGE, change_state, 0);//지폐 프로그램에게 메세지(메인->지폐) 전송
	}
	if(m_mainmudulecontrol->module_hwnd[CoinProcessor]==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[CoinProcessor] 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile(_T("동전 프로세서에게 셧터 열기 명령 송신 완료"));//LOG 기록
		::SendMessage(m_mainmudulecontrol->module_hwnd[CoinProcessor], UM_MAIN_COIN_MESSAGE, change_state, 0);//동전 프로그램에게 메세지(메인->동전) 전송
	}
}

void CMainProcessorDlg::Shutter_Clsoe()//동전, 지폐에게 셔터 닫기 지시
{
	if(m_mainmudulecontrol->module_hwnd[BillProcessor]==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[BillProcessor] 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile(_T("지폐 프로세서에게 셧터 닫기 명령 송신 완료"));//LOG 기록
		::SendMessage(m_mainmudulecontrol->module_hwnd[BillProcessor], UM_MAIN_BILL_MESSAGE, main, 0);//지폐 프로그램에게 메세지(메인->지폐) 전송
	}
	if(m_mainmudulecontrol->module_hwnd[CoinProcessor]==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[CoinProcessor] 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile(_T("동전 프로세서에게 셧터 닫기 명령 송신 완료"));//LOG 기록
		::SendMessage(m_mainmudulecontrol->module_hwnd[CoinProcessor], UM_MAIN_COIN_MESSAGE, main, 0);//동전 프로그램에게 메세지(메인->동전) 전송
	}
}

void CMainProcessorDlg::Card_Disabled()//카드 비활성화 지시
{
	if(m_mainmudulecontrol->module_hwnd[RechargeProcessor]==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[RechargeProcessor] 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile(_T("RF 프로세서에게 비활성화 명령 송신 완료"));//LOG 기록
		::SendMessage(m_mainmudulecontrol->module_hwnd[RechargeProcessor], UM_MAIN_RF_MESSAGE, main, 0);//RF 프로그램에게 메세지(메인->RF) 전송
	}
}

void CMainProcessorDlg::Bill_Shutter_Open_Result(int Shutter_Result)//지폐 셔터 열기 결과 
{
	Bill_Shutter_Open = Shutter_Result;//셔터 열기 성공 여부에 따라 셔터 플래그 변경
	m_logwriter->now_write_log.Format(_T("지폐 프로세서에게 셧터 열기 결과 수신 완료 (결과 : %d)"), Bill_Shutter_Open);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	if(Coin_Shutter_Open&&Bill_Shutter_Open){//코인도 열기 성공시
		m_logwriter->now_write_log.Format(_T("p_data->Transtion_Ready : %d (1.준비완료 0.준비미완료)"), m_mainmmap->MMap_Transtion_Ready_Change(TRUE));//MMAp투입을 TRUE로
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
}

void CMainProcessorDlg::Coin_Shutter_Open_Result(int Shutter_Result)//동전 셔터 열기 결과
{
	Coin_Shutter_Open = Shutter_Result;//셔터 열기 성공 여부에 따라 셔터 플래그 변경
	m_logwriter->now_write_log.Format(_T("동전 프로세서에게 셧터 열기 결과 수신 완료 (결과 : %d)"), Coin_Shutter_Open);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	if(Coin_Shutter_Open&&Bill_Shutter_Open){//지폐도 열기 성공시
		m_logwriter->now_write_log.Format(_T("p_data->Transtion_Ready : %d (1.준비완료 0.준비미완료)"), m_mainmmap->MMap_Transtion_Ready_Change(TRUE));//MMAp투입을 TRUE로
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
}

INT CMainProcessorDlg::Insert_Bill(int fare)//지폐투입
{
	m_mainmmap->insert_bill(fare);//T_RECHARGE_DATA 수정
	int now_image_state = m_mainmmap->MMap_Now_State();//현재상태값
	if(m_mainmudulecontrol->module_hwnd[ImageProcessor]==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[ImageProcessor] 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->now_write_log.Format(_T("이미지 프로세서에게 T_RECHARGE_DATA 지폐 투입 [%d] 송신 완료"), fare);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		::SendMessage(m_mainmudulecontrol->module_hwnd[ImageProcessor], UM_MAIN_IMAGE_MESSAGE, now_image_state, fare);//이미지프로그램에게 메세지(메인->이미지) 전송
	}
	return 0;
}

INT CMainProcessorDlg::Insert_Coin(int fare)//동전투입
{
	m_mainmmap->insert_coin(fare);//T_RECHARGE_DATA 수정

	int now_image_state = m_mainmmap->MMap_Now_State();//현재상태값
	if(m_mainmudulecontrol->module_hwnd[ImageProcessor]==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[ImageProcessor] 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->now_write_log.Format(_T("이미지 프로세서에게 T_RECHARGE_DATA 동전 투입 [%d] 송신 완료"), fare);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		::SendMessage(m_mainmudulecontrol->module_hwnd[ImageProcessor], UM_MAIN_IMAGE_MESSAGE, now_image_state, fare);//이미지프로그램에게 메세지(메인->이미지) 전송
	}
	return 0;
}

void CMainProcessorDlg::Trasation_Cancel(int now_image_state)//거래중 취소 눌렀을 시 투입금0 셔터, 거래상태 거래X상태로 변경
{
	if(now_image_state >= recharge){//현재상태가 보충 진행중일때	
		Card_Disabled();//카드 비활성화 지시
	}
	Shutter_Clsoe();//해당 거래 금액 투입을 위한 동전, 지폐에게 셔터 닫기 지시
	m_mainmmap->init_insert(now_image_state);//투입금 초기화 함수
	m_logwriter->now_write_log.Format(_T("금액 투입 상태 : %d (1.준비완료 2.준비미완료)"), m_mainmmap->MMap_Transtion_Ready_Change(Transation_None));//MMAp거래상태 Transation_None로
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	Coin_Shutter_Open = 0;
	Bill_Shutter_Open = 0; 
}

void CMainProcessorDlg::Write_CardInfo(int kind_of_card)//RF에게 받은 카드 기록 MM에 남기기
{
	m_logwriter->now_write_log.Format(_T("%s 카드 인식"), Traffic_Card_Name[m_mainmmap->MMap_Write_CardInfo(kind_of_card)]);//MMAp 카드 종류 쓰기
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
}

void CMainProcessorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_mainmudulecontrol->moduleprocess_kill();//모듈 프로그램 종료
	m_logwriter->WriteLogFile(_T("Main 종료"));//LOG 기록
	delete m_mainmmap;//소멸
	m_mainmmap = NULL;//소멸
	delete m_mainmudulecontrol;//소멸
	m_mainmudulecontrol = NULL;//소멸
	if ((m_mainmudulecontrol == NULL) &&
		(m_mainmmap == NULL)){
		m_logwriter->WriteLogFile(_T("m_mainmudulecontrol, m_mainmmap 소멸 완료 곧 m_logwriter도 소멸예정"));
	}
	else{
		m_logwriter->WriteLogFile(_T("m_mainmudulecontrol, m_mainmmap 소멸 실패 곧 m_logwriter 소멸 시도 "));
	}
	delete m_logwriter;//소멸
	m_logwriter = NULL;//소멸
	if(m_logwriter!=NULL){
		AfxMessageBox(_T("m_logwriter소멸 실패(Main)"));
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

afx_msg LRESULT CMainProcessorDlg::COIN_Main_Message(WPARAM wParam, LPARAM lParam)//동전에서 메인에게 메시지 송신했을때 수신 이벤트처리 함수
{
	switch (wParam)//현재 상태값에따라
	{
		case cardsale_insert :
		case recharge_insert :
			if(m_mainmmap->MMap_Check_Transtion_Ready() == TRUE){//거래 준비 상태일 때
				Insert_Coin(lParam);//지폐투입//lParam 투입 금액
			}
			else{//거래 준비 상태 아닐 때
				Coin_Shutter_Open_Result(lParam);//셔터 열기 성공 여부에 따라 셔터 플래그 변경
			}
			break;
		default:
			break;
	}
	return 0;
}

afx_msg LRESULT CMainProcessorDlg::BILL_Main_Message(WPARAM wParam, LPARAM lParam)//지폐에서 메인에게 메시지 송신했을때 수신 이벤트처리 함수
{
	switch (wParam)//현재 상태값에따라
	{
		case cardsale_insert :
		case recharge_insert :
			if(m_mainmmap->MMap_Check_Transtion_Ready() == TRUE){//거래 준비 상태일 때
				Insert_Bill(lParam);//지폐투입//lParam 투입 금액
			}
			else{//거래 준비 상태 아닐 때
				Bill_Shutter_Open_Result(lParam);//셔터 열기 성공 여부에 따라 셔터 플래그 변경
			}
			break;
		default:
			break;
	}
	return 0;
}

afx_msg LRESULT CMainProcessorDlg::IMAGE_Main_Message(WPARAM wParam, LPARAM lParam)//이미지프로그램에서 메인에게 메시지 송신했을때 수신 이벤트처리 함수
{
	m_logwriter->now_write_log.Format(_T("이미지 프로세서에서 T_RECHARGE_DATA [%s] 상태 변경 요청!"), Now_State_Contents[wParam]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록

	int image_state = m_mainmmap->MMap_Now_State();//이미지에서 송신할때 상태값
	m_logwriter->now_write_log.Format(_T("현 T_RECHARGE_DATA [%s] 상태(p_data->Now_State)"), Now_State_Contents[image_state]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	switch (wParam)//현재 상태값에따라
	{
		case main://메인 아닌 상태에서 취소 버튼을 선택하였을때
			Trasation_Cancel(image_state);//거래중 취소 눌렀을 시 투입금0 셔터, 거래상태 거래X상태로 변경
			//투입금액 초기화하는함수
			Processor_State_Change(main);
			break;
		case cardsale :
			Processor_State_Change(cardsale);
			break;
		case card_wait ://카드 대기 상태
			Processor_State_Change(card_wait);
			Card_Wait();//RF에게 카드 태그할수있도록 활성화 보내기
			break;
		case cardsale_insert :
			Processor_State_Change(cardsale_insert);
			Shutter_Open(cardsale_insert);
			break;
		case cardsale_processing :
			Processor_State_Change(cardsale_processing);
			break;
		case cardsale_lack :
			Processor_State_Change(cardsale_lack);
			break;
		case cardsale_success :
			Processor_State_Change(cardsale_success);
			break;
		case cardsale_failure :
			Processor_State_Change(cardsale_failure);
			break;
		case recharge_insert :
			Processor_State_Change(recharge_insert);
			Shutter_Open(recharge_insert);
			break;
		case recharge_processing : 
			Processor_State_Change(recharge_processing);
			break;
		case recharge_lack :
			Processor_State_Change(recharge_lack);
			break;
		case recharge_success :
			Processor_State_Change(recharge_success);
			break;
		case recharge_failure :
			Processor_State_Change(recharge_failure);
			break;
		default:
			break;
	}
	return 0;
}

afx_msg LRESULT CMainProcessorDlg::RF_Main_Message(WPARAM wParam, LPARAM lParam)//충전프로그램에서 메인에게 메시지 송신했을때 수신 이벤트처리 함수
{
	m_logwriter->now_write_log.Format(_T("RF 프로세서에서 T_RECHARGE_DATA [%s] 상태 변경 요청!"), Now_State_Contents[wParam]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록

	int image_state = m_mainmmap->MMap_Now_State();//이미지에서 송신할때 상태값
	m_logwriter->now_write_log.Format(_T("현 T_RECHARGE_DATA [%s] 상태(p_data->Now_State)"), Now_State_Contents[image_state]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록

	switch (wParam)//현재 상태값에따라
	{
		case card_processing ://카드 인식 상태
			Processor_State_Change(card_processing);
			break;
		case recharge ://카드 충전 금액 선택
			Write_CardInfo(lParam);//RF에게 받은 카드 기록 MM에 남기기
			Processor_State_Change(recharge);
			break;
		default:
			break;
	}
	return 0;
}