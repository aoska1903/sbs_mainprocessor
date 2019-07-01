
// CoinProcessorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "CoinProcessor.h"
#include "CoinProcessorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCoinProcessorDlg 대화 상자

CCoinProcessorDlg::CCoinProcessorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCoinProcessorDlg::IDD, pParent)
	, m_coinmmap(new CCoinMMap())//동전장치 메모리맵 파일
	, m_logwriter(new CLogWriter())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCoinProcessorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_INSERT_10 , m_coin_inset10);
	DDX_Control(pDX, IDC_BUTTON_INSERT_50 , m_coin_inset50);
	DDX_Control(pDX, IDC_BUTTON_INSERT_100, m_coin_inset100);
	DDX_Control(pDX, IDC_BUTTON_INSERT_500, m_coin_inset500);
}

BEGIN_MESSAGE_MAP(CCoinProcessorDlg, CDialogEx)
	ON_MESSAGE(UM_MAIN_COIN_MESSAGE, CCoinProcessorDlg::Main_COIN_Message)//메인에서 동전에게 메시지 송신했을때 수신 이벤트처리
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT_500, &CCoinProcessorDlg::OnBnClickedButtonInsert500)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_100, &CCoinProcessorDlg::OnBnClickedButtonInsert100)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_50, &CCoinProcessorDlg::OnBnClickedButtonInsert50)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_10, &CCoinProcessorDlg::OnBnClickedButtonInsert10)
END_MESSAGE_MAP()


// CCoinProcessorDlg 메시지 처리기

BOOL CCoinProcessorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_logwriter->Log_Make(_T("CoinProcessor"), _T("04_Coin"));//해당 폴더 및 파일 생성
	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCoinProcessorDlg::OnPaint()
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
HCURSOR CCoinProcessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

afx_msg LRESULT CCoinProcessorDlg::Main_COIN_Message(WPARAM wParam, LPARAM lParam)//메인에서 동전에게 메시지 송신했을때 수신 이벤트처리 함수
{
	switch (wParam)//wParam 값에 따라
	{
		case main:
			Coin_Shutter_Close();//동전 셔터 닫기 동작
			break;
		case cardsale_insert : 
		case recharge_insert : 
			Coin_Shutter_Open(wParam);//동전 셔터 열기 동작
			break;
		default:
			break;
	}
	return 0;
}

int CCoinProcessorDlg::Coin_Shutter_Open(int receive_state)//동전 셔터 열기 동작
{
	m_logwriter->now_write_log.Format(_T("메인으로 부터 [%s]을 위한 셔텨 열기 명령 수신"), Now_State_Contents[receive_state]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	int shuttur_count = 0;//셔터 열린개수 
	if(!m_coin_inset10.EnableWindow() + !m_coin_inset50.EnableWindow() + !m_coin_inset100.EnableWindow() + !m_coin_inset500.EnableWindow() == TRUE ){
		m_logwriter->now_write_log.Format(_T("[%s]을 위한 셔텨 열기 실패"), Now_State_Contents[receive_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		if(m_logwriter->MAIN_HWND==NULL){//수신핸들이 존재하지 않는다면
			m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
		}
		else{
			m_logwriter->now_write_log.Format(_T("메인에게 [%s]을 위한 셔텨 열기 실패 메시지 송신"), Now_State_Contents[receive_state]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);
			::SendMessage(m_logwriter->MAIN_HWND, UM_COIN_MAIN_MESSAGE, receive_state, 0);//메인프로그램에게 메세지(동전->메인) 전송//Iparm 1(성공) 0(실패)
		}
		return 0;//어느 한 버튼이라도 비활성화 되어있을 시
	}
	m_logwriter->now_write_log.Format(_T("[%s]을 위한 셔텨 열기 성공"), Now_State_Contents[receive_state]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);
	if(m_logwriter->MAIN_HWND==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->now_write_log.Format(_T("메인에게 [%s]을 위한 셔텨 열기 완료 메시지 송신"), Now_State_Contents[receive_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		::SendMessage(m_logwriter->MAIN_HWND, UM_COIN_MAIN_MESSAGE, receive_state, 1);//메인프로그램에게 메세지(동전->메인) 전송//Iparm 1(성공) 0(실패)
	}
	return 1;
}

void CCoinProcessorDlg::Coin_Shutter_Close()//동전 셔터 닫기 동작
{
	m_logwriter->WriteLogFile(_T("Coin_Shutter_Close"));
	if(m_coin_inset10.EnableWindow(FALSE) + m_coin_inset50.EnableWindow(FALSE) + m_coin_inset100.EnableWindow(FALSE) + m_coin_inset500.EnableWindow(FALSE) == TRUE){//한개라도 활성화이면
		m_logwriter->now_write_log.Format(_T("10원, 50원, 100원, 500원 비활성화 실패"));
	}
	else{
		m_logwriter->now_write_log.Format(_T("10원, 50원, 100원, 500원 비활성화 성공!"));
	}
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
}

void CCoinProcessorDlg::Coin_Insert_Fare(int fare)//동전 투입
{
	if(m_logwriter->MAIN_HWND==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->now_write_log.Format(_T("동전 투입 %d원"), fare);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		::SendMessage(m_logwriter->MAIN_HWND, UM_COIN_MAIN_MESSAGE, m_coinmmap->MMap_Now_State(), fare);//메인프로그램에게 메세지(동전->메인) 전송//Iparm 1(성공) 0(실패)
	}
}

void CCoinProcessorDlg::OnBnClickedButtonInsert500()//500동전 투입 버튼 눌렀을때
{					
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_logwriter->WriteLogFile(_T("동전 500원 버튼 클릭"));
	Coin_Insert_Fare(500);//동전 투입
}


void CCoinProcessorDlg::OnBnClickedButtonInsert100()//100동전 투입 버튼 눌렀을때
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_logwriter->WriteLogFile(_T("동전 100원 버튼 클릭"));
	Coin_Insert_Fare(100);//동전 투입
}


void CCoinProcessorDlg::OnBnClickedButtonInsert50()//50동전 투입 버튼 눌렀을때
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_logwriter->WriteLogFile(_T("동전 50원 버튼 클릭"));
	Coin_Insert_Fare(50);//동전 투입
}


void CCoinProcessorDlg::OnBnClickedButtonInsert10()//10동전 투입 버튼 눌렀을때
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_logwriter->WriteLogFile(_T("동전 10원 버튼 클릭"));
	Coin_Insert_Fare(10);//동전 투입
}
