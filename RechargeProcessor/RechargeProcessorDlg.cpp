
// RechargeProcessorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "RechargeProcessor.h"
#include "RechargeProcessorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRechargeProcessorDlg 대화 상자

CRechargeProcessorDlg::CRechargeProcessorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRechargeProcessorDlg::IDD, pParent)
	, m_rechargemmap(new CRechargeMMap())//거래 관련 메모리맵 파일
	, m_logwriter(new CLogWriter())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRechargeProcessorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CARDTAG , m_button_cardtag); //카드 태그 버튼
	DDX_Control(pDX, IDC_BUTTON_NO_COGNIZE , m_button_no_cognize); //미인식 카드 태그 버튼
	DDX_Control(pDX, IDC_BUTTON_HANARO, m_button_hanaro);//하나로 카드 태그 버튼
	DDX_Control(pDX, IDC_BUTTON_MYBI, m_button_mybi);//마이비 카드 태그 버튼
	DDX_Control(pDX, IDC_BUTTON_CASHBEE, m_button_cashbee);//캐시비 카드 태그 버튼
	DDX_Control(pDX, IDC_BUTTON_TMONEY, m_button_Tmoney);//티머니 카드 태그 버튼
}

BEGIN_MESSAGE_MAP(CRechargeProcessorDlg, CDialogEx)
	ON_MESSAGE(UM_MAIN_RF_MESSAGE, CRechargeProcessorDlg::Main_RF_Message)//메인에서 RF에게 메시지 송신했을때 수신 이벤트처리
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CARDTAG, &CRechargeProcessorDlg::OnBnClickedButtonCardtag)
	ON_BN_CLICKED(IDC_BUTTON_NO_COGNIZE, &CRechargeProcessorDlg::OnBnClickedButtonNoCognize)
	ON_BN_CLICKED(IDC_BUTTON_HANARO, &CRechargeProcessorDlg::OnBnClickedButtonHanaro)
	ON_BN_CLICKED(IDC_BUTTON_MYBI, &CRechargeProcessorDlg::OnBnClickedButtonMybi)
	ON_BN_CLICKED(IDC_BUTTON_CASHBEE, &CRechargeProcessorDlg::OnBnClickedButtonCashbee)
	ON_BN_CLICKED(IDC_BUTTON_TMONEY, &CRechargeProcessorDlg::OnBnClickedButtonTmoney)
END_MESSAGE_MAP()

// CRechargeProcessorDlg 메시지 처리기

BOOL CRechargeProcessorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	
	m_logwriter->Log_Make(_T("RechargeProcessor"), _T("11_Recharge"));//해당 폴더 및 파일 생성
	
	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRechargeProcessorDlg::OnPaint()
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
HCURSOR CRechargeProcessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

afx_msg LRESULT CRechargeProcessorDlg::Main_RF_Message(WPARAM wParam, LPARAM lParam)//메인에서 RF에게 메시지 송신했을때 수신 이벤트처리 함수
{
	switch (wParam)//wParam 값에 따라
	{
		case main : //카드 메인상태
			card_disbled();//메인에서 카드 비활성화
			break;
		case card_wait : //카드 대기상태
			m_button_cardtag.EnableWindow();//카드 태그 활성화
			break;
		case card_processing : 
			break;
		default:
			break;
	}
	return 0;
}

void CRechargeProcessorDlg::send_card_tag()//메인에게 카드 태그 보내기
{
	if(m_logwriter->MAIN_HWND==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile("RF -> 메인 메시지 송신완료(카드보충_판독중)");//LOG 기록
		::SendMessage(m_logwriter->MAIN_HWND, UM_RF_MAIN_MESSAGE, card_processing, 0);//메인에게 메세지(이미지->메인) 전송 //Wparam : 2 (카드 보충)
	}
}

void CRechargeProcessorDlg::send_card_result(int CardNum)//메인에게 카드 결과 보내기
{
	if(m_logwriter->MAIN_HWND==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile("RF -> 메인 메시지 송신완료(카드보충_금액선택)");//LOG 기록
		::SendMessage(m_logwriter->MAIN_HWND, UM_RF_MAIN_MESSAGE, recharge, CardNum);//메인에게 메세지(이미지->메인) 전송 //Iparam : 1(하나로) 2(마이비) 3(캐시비) 4(티머니)
	}
}

void CRechargeProcessorDlg::card_disbled()//메인에서 카드 비활성화
{
	m_logwriter->WriteLogFile(_T("card_disbled"));
	if(m_button_cardtag.EnableWindow(FALSE) + m_button_no_cognize.EnableWindow(FALSE) + m_button_hanaro.EnableWindow(FALSE) +
	   m_button_mybi.EnableWindow(FALSE) + m_button_cashbee.EnableWindow(FALSE) + m_button_Tmoney.EnableWindow(FALSE) == TRUE){//한개라도 활성화이면
		m_logwriter->now_write_log.Format(_T("미인식, 하나로, 마이비, 캐시비, 티머니 비활성화 실패"));
	}
	else{
		m_logwriter->now_write_log.Format(_T("미인식, 하나로, 마이비, 캐시비, 티머니 비활성화 성공!"));
	}
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
}

void CRechargeProcessorDlg::OnBnClickedButtonCardtag()//카드 태그 버튼 눌렀을 때
{
	m_logwriter->WriteLogFile(_T("Cardtag 버튼 클릭"));
	if(!m_button_no_cognize.EnableWindow() + !m_button_hanaro.EnableWindow() + !m_button_mybi.EnableWindow() + !m_button_cashbee.EnableWindow() + !m_button_Tmoney.EnableWindow() == TRUE){//한개라도 비활성화이면
		m_logwriter->now_write_log.Format(_T("미인식, 하나로, 마이비, 캐시비, 티머니 활성화 실패"));
	}
	else{
		m_logwriter->now_write_log.Format(_T("미인식, 하나로, 마이비, 캐시비, 티머니 활성화 성공!"));
		send_card_tag();
	}
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRechargeProcessorDlg::OnBnClickedButtonNoCognize()//태그한 카드가 미인식 카드일 때
{
	send_card_result(card_none);//메인에게 카드 결과 보내기
	m_logwriter->WriteLogFile(_T("NoCognize 버튼 클릭"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRechargeProcessorDlg::OnBnClickedButtonHanaro()//태그한 카드가 하나로 카드일 때
{
	send_card_result(hanaro);//메인에게 카드 결과 보내기
	m_logwriter->WriteLogFile(_T("Hanaro 버튼 클릭"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRechargeProcessorDlg::OnBnClickedButtonMybi()//태그한 카드가 마이비 카드일 때
{
	send_card_result(mybe);//메인에게 카드 결과 보내기
	m_logwriter->WriteLogFile(_T("Mybi 버튼 클릭"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRechargeProcessorDlg::OnBnClickedButtonCashbee()//태그한 카드가 캐시비 카드일 때
{
	send_card_result(cashbbe);//메인에게 카드 결과 보내기
	m_logwriter->WriteLogFile(_T("Cashbee 버튼 클릭"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CRechargeProcessorDlg::OnBnClickedButtonTmoney()//태그한 카드가 티머니 카드일 때
{
	send_card_result(Tmoney);//메인에게 카드 결과 보내기
	m_logwriter->WriteLogFile(_T("Tmoney 버튼 클릭"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
