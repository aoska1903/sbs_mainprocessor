
// ImageProcessorDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ImageProcessor.h"
#include "ImageProcessorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessorDlg 대화 상자

CImageProcessorDlg::CImageProcessorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageProcessorDlg::IDD, pParent)
	, m_imagemmap(new CImageMMap())//이미지 메모리맵 파일
	, m_logwriter(new CLogWriter())
	, m_imagemaker(new CImageMaker())
	, Now_Image_State(0)
	, Now_Selete_Card(0)
	, cardsale_fare(0)
	, recharge_fare(0)
	, Direct_Screen(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	number_cards[cardsale_adult] = 0;
	number_cards[cardsale_adolescent] = 0;
	number_cards[cardsale_season_ticket] = 0;
}

HBRUSH CImageProcessorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    
    switch(nCtlColor)
    {
		case CTLCOLOR_STATIC://스태틱
        {
			if(pWnd->GetDlgCtrlID() == IDC_STATIC_CARDSALE_INSERT_AMOUNT || pWnd->GetDlgCtrlID() == IDC_STATIC_RECHARGE_INSERT_FARE){
                pDC->SetTextColor(RGB(0, 0, 0));
            }
			else if(pWnd->GetDlgCtrlID() == IDC_STATIC_RECHARGE_FARE){
				pDC->SetTextColor(RGB(255, 255, 0));
			}
			else{
                pDC->SetTextColor(RGB(255, 255, 255));
			}
            pDC->SetBkMode(TRANSPARENT);
            return (HBRUSH)GetStockObject(NULL_BRUSH);
		}
		case CTLCOLOR_BTN://버튼
		{
			if(pWnd->GetDlgCtrlID() == IDC_BUTTON_NUMBER_ADULT){
				pDC->SetDCBrushColor(RGB(255, 0, 0));
				//pDC->SetDCBrushColor(RGB(Now_Selete_Card==cardsale_adult?255:0, 0, 0));
			}
			else if(pWnd->GetDlgCtrlID() == IDC_BUTTON_NUMBER_ADOLESCEMT){
				pDC->SetDCBrushColor(RGB(Now_Selete_Card==cardsale_adolescent?255:0, 0, 0));
			}
			else if(pWnd->GetDlgCtrlID() == IDC_BUTTON_NUMBER_SEASON_TICKET){
				pDC->SetDCBrushColor(RGB(Now_Selete_Card==cardsale_season_ticket?255:0, 0, 0));
			}
            pDC->SetTextColor(RGB(255, 255, 255));
			return (HBRUSH)GetStockObject(NULL_BRUSH);
		}
    }
    // TODO: Return a different brush if the default is not desired
    return hbr;
}

void CImageProcessorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	for(int i = 0; i <= picture_error; i++){
		DDX_Control(pDX, IDC_PICTURE_INITIAL + i, m_imagemaker->m_picture_background[i]);
	}
}

BEGIN_MESSAGE_MAP(CImageProcessorDlg, CDialogEx)
	ON_MESSAGE(UM_MAIN_IMAGE_MESSAGE, CImageProcessorDlg::Main_Image_Message)//메인에서 이미지프로그램에게 메시지 송신했을때 수신 이벤트처리
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT_OK				, &CImageProcessorDlg::OnBnClickedINSERTOK)				//금액 투입 확인 버튼이벤트처리
	ON_BN_CLICKED(IDC_BUTTON_CARDSALE				, &CImageProcessorDlg::OnBnClickedCARDSALE)				//카드판매 이벤트처리
	ON_BN_CLICKED(IDC_BUTTON_RECHARGE				, &CImageProcessorDlg::OnBnClickedRECHARGE)				//카드충전 이벤트처리
	ON_BN_CLICKED(IDC_BUTTON_CARDSALE_NUMBER3		, &CImageProcessorDlg::OnBnClickedCARDSALENUMBER3)		//3매버튼 이벤트처리
	ON_BN_CLICKED(IDC_BUTTON_CARDSALE_NUMBER2		, &CImageProcessorDlg::OnBnClickedCARDSALENUMBER2)		//2매버튼 이벤트처리
	ON_BN_CLICKED(IDC_BUTTON_CARDSALE_NUMBER1		, &CImageProcessorDlg::OnBnClickedCARDSALENUMBER1)		//1매버튼 이벤트처리
	ON_BN_CLICKED(IDC_BUTTON_CARDSALE_NUMBER0		, &CImageProcessorDlg::OnBnClickedCARDSALENUMBER0)		//0매버튼 이벤트처리
	ON_BN_CLICKED(IDC_BUTTON_NUMBER_ADULT			, &CImageProcessorDlg::OnBnClickedNUMBERADULT)			//어른 종류 버튼 이벤트처리
	ON_BN_CLICKED(IDC_BUTTON_NUMBER_ADOLESCEMT		, &CImageProcessorDlg::OnBnClickedNUMBERADOLESCEMT)		//어른 종류 버튼 이벤트처리
	ON_BN_CLICKED(IDC_BUTTON_NUMBER_SEASON_TICKET	, &CImageProcessorDlg::OnBnClickedNUMBERSEASONTICKET)	//어른 종류 버튼 이벤트처리
	ON_BN_CLICKED(IDC_BUTTON_FARE_5000				, &CImageProcessorDlg::OnBnClickedFARE5000)				//충전  5000원 운임 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_FARE_10000				, &CImageProcessorDlg::OnBnClickedFARE10000)			//충전 10000원 운임 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_FARE_20000				, &CImageProcessorDlg::OnBnClickedFARE20000)			//충전 20000원 운임 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_FARE_30000				, &CImageProcessorDlg::OnBnClickedFARE30000)			//충전 30000원 운임 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_FARE_40000				, &CImageProcessorDlg::OnBnClickedFARE40000)			//충전 40000원 운임 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_FARE_50000				, &CImageProcessorDlg::OnBnClickedFARE50000)			//충전 50000원 운임 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_BEFORE					, &CImageProcessorDlg::OnBnClickedBEFORE)				//이전 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_DIRECT					, &CImageProcessorDlg::OnBnClickedDIRECT)				//직접 입력 선택 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_0					, &CImageProcessorDlg::OnBnClickedADD0)					//직접 입력 0	 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_1					, &CImageProcessorDlg::OnBnClickedADD1)					//직접 입력 1	 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_2					, &CImageProcessorDlg::OnBnClickedADD2)					//직접 입력 2	 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_3					, &CImageProcessorDlg::OnBnClickedADD3)					//직접 입력 3	 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_4					, &CImageProcessorDlg::OnBnClickedADD4)					//직접 입력 4	 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_5					, &CImageProcessorDlg::OnBnClickedADD5)					//직접 입력 5	 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_6					, &CImageProcessorDlg::OnBnClickedADD6)					//직접 입력 6	 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_7					, &CImageProcessorDlg::OnBnClickedADD7)					//직접 입력 7	 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_8					, &CImageProcessorDlg::OnBnClickedADD8)					//직접 입력 8	 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_9					, &CImageProcessorDlg::OnBnClickedADD9)					//직접 입력 9	 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ADD_000				, &CImageProcessorDlg::OnBnClickedADD000)				//직접 입력 000  버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_ERASE					, &CImageProcessorDlg::OnBnClickedERASE)				//직접 입력 지움 버튼 눌렀을 경우 이벤트
	ON_BN_CLICKED(IDC_BUTTON_CANCLE					, &CImageProcessorDlg::OnBnClickedCANCLE)				//취소           버튼 눌렀을 경우 이벤트처리					   
END_MESSAGE_MAP()

// CImageProcessorDlg 메시지 처리기

BOOL CImageProcessorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.
	m_logwriter->Log_Make(_T("ImageProcessor"), _T("08_Image"));//해당 폴더 및 파일 생성
	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	control_make();//컨트롤 생성
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}
// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CImageProcessorDlg::OnPaint()
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
HCURSOR CImageProcessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImageProcessorDlg::control_collocate(){//컨트롤 배치
	background_collocate();//배경화면배치
	//스태틱 배치
	m_static[m_static_number_adult].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);								//어른 종류 텍스트는 현재 상태가 카드 판매 금액 선택 화면일 때
	m_static[m_static_number_adolescent].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);						//청소년 종류 텍스트는 현재 상태가 카드 판매 금액 선택 화면일 때
	m_static[m_static_number_season_ticket].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);						//정기권 종류 텍스트는 현재 상태가 카드 판매 금액 선택 화면일 때
	m_static[m_static_contents_card].ShowWindow((Now_Image_State == cardsale_insert) ? TRUE : FALSE);					//요금 내용 현재 상태가 카드 판매 금액 선택일때 
	m_static[m_static_cardsale_fare].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//카드선택요금(운임) 종류 텍스트는 현재 상태가 카드 판매 금액 선택 화면일 때
	m_static[m_static_cardsale_insert_fare].ShowWindow(Now_Image_State == cardsale_insert ? TRUE : FALSE);				//요금(운임)텍스트는 현재 상태가 메인일때 
	m_static[m_static_cardsale_insert_amount].ShowWindow(Now_Image_State == cardsale_insert ? TRUE : FALSE);			//투입금액텍스트는 현재 상태가 메인일때 
	m_static[m_static_recharge_card_kind].ShowWindow(Now_Image_State == recharge ? TRUE : FALSE);						//카드 충전 선택 화면 충전 카드 종류(하나로, 마이비, 캐시비, 티머니)는 카드 충전 금액 선택일 때
	m_static[m_static_recharge_card_number].ShowWindow(Now_Image_State == recharge ? TRUE : FALSE);						//카드 충전 선택 화면 충전 카드 번호는 카드 충전 금액 선택일 때 
	m_static[m_static_recharge_card_balance].ShowWindow(Now_Image_State == recharge ? TRUE : FALSE);					//카드 충전 선택 화면 충전 카드 잔액는 카드 충전 금액 선택일 때
	m_static[m_static_recharge_fare].ShowWindow(Now_Image_State == recharge ? TRUE : FALSE);							//카드 충전 선택 화면 판매 운임 텍스트는 카드 충전 금액 선택일 때
	m_static[m_static_recharge_insert_card_kind].ShowWindow(Now_Image_State == recharge_insert ? TRUE : FALSE);			//카드 충전 투입 화면 충전 카드 종류(하나로, 마이비, 캐시비, 티머니)는 카드 충전 금액 투입일 때
	m_static[m_static_recharge_insert_card_balance].ShowWindow(Now_Image_State == recharge_insert ? TRUE : FALSE);		//카드 충전 투입 화면 충전 카드 잔액는 카드 충전 금액 투입일 때
	m_static[m_static_recharge_insert_fare].ShowWindow(Now_Image_State == recharge_insert ? TRUE : FALSE);				//카드 충전 투입 화면 판매 운임 텍스트는 카드 충전 금액 투입일 때
	m_static[m_static_recharge_insert_amount].ShowWindow(Now_Image_State == recharge_insert ? TRUE : FALSE);			//카드 충전 투입 화면 사용자 직접 투입 금액는 카드 충전 금액 투입일 때
	m_static[m_static_version].ShowWindow(Now_Image_State == main ? TRUE : FALSE);										//버전텍스트는 현재 상태가 메인일때 
	//버튼 배치						
	m_button[m_button_insert_ok].ShowWindow((Now_Image_State == cardsale || (Now_Image_State == recharge && Direct_Screen == TRUE)) ? TRUE : FALSE);//금액확인버튼은 카드판매금액선택화면 또는 충전 직접입력 일때 활성화
	m_button[m_button_cardsale].ShowWindow(Now_Image_State == main ? TRUE : FALSE);										//판매 버튼은 현재 상태가 메인일때 
	m_button[m_button_recharge].ShowWindow(Now_Image_State == main ? TRUE : FALSE);										//충전 버튼은 현재 상태가 메인일때 
	m_button[m_button_cardsale_number3].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//매수3 버튼은 현재 상태가 카드 판매 금액 선택 화면일 때
	m_button[m_button_cardsale_number2].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//매수2 버튼은 현재 상태가 카드 판매 금액 선택 화면일 때
	m_button[m_button_cardsale_number1].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//매수1 버튼은 현재 상태가 카드 판매 금액 선택 화면일 때
	m_button[m_button_cardsale_number0].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//매수0 버튼은 현재 상태가 카드 판매 금액 선택 화면일 때
	m_button[m_button_kind_adult].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);								//어른 종류 버튼은 현재 상태가 카드 판매 금액 선택 화면일 때
	m_button[m_button_kind_adolescent].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//청소년 종류 버튼은 현재 상태가 카드 판매 금액 선택 화면일 때
	m_button[m_button_kind_season_ticket].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);						//정기권 종류 버튼은 현재 상태가 카드 판매 금액 선택 화면일 때
	m_button[m_button_fare_5000]. ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//충전 금액 선택 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 간접 금액 선택
	m_button[m_button_fare_10000].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//충전 금액 선택 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 간접 금액 선택
	m_button[m_button_fare_20000].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//충전 금액 선택 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 간접 금액 선택
	m_button[m_button_fare_30000].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//충전 금액 선택 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 간접 금액 선택
	m_button[m_button_fare_40000].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//충전 금액 선택 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 간접 금액 선택
	m_button[m_button_fare_50000].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//충전 금액 선택 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 간접 금액 선택
	m_button[m_button_before].ShowWindow((Now_Image_State == recharge) ? TRUE : FALSE);									//충전 금액 선택 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접, 간접 상관없이 두 화면 모두 활성화
	m_button[m_button_direct].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);		//직접 금액 선택 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 간접 금액 선택
	m_button[m_button_add_0].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택	
	m_button[m_button_add_1].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택	
	m_button[m_button_add_2].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택	
	m_button[m_button_add_3].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택	
	m_button[m_button_add_4].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택	
	m_button[m_button_add_5].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택	
	m_button[m_button_add_6].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택	
	m_button[m_button_add_7].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택	
	m_button[m_button_add_8].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택
	m_button[m_button_add_9].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택
	m_button[m_button_add_000].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);		//직접 금액 입력 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택	
	m_button[m_button_erase].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//지음 버튼은 현재 상태가 카드 충전 금액 선택 화면일 때, 직접 금액 선택
	m_button[m_button_cancle].ShowWindow((Now_Image_State == cardsale || Now_Image_State == cardsale_insert || Now_Image_State == recharge_insert) ? TRUE : FALSE);//취소버튼은 현재 상태가 보충,판매 금액,선택일때 

}

void CImageProcessorDlg::control_make()																					//컨트롤 생성
{
	background_make();																									//배경 생성
	static_make();																										//텍스트 생성
	button_make();																										//버튼 생성
	control_collocate();																								//컨트롤 배치
}

void CImageProcessorDlg::background_make()//배경 생성
{
	this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), (GetSystemMetrics(SM_CYSCREEN)), SWP_NOREPOSITION);//창크기 설정
	m_imagemaker->background_make();
}

void CImageProcessorDlg::static_make(){//텍스트 생성
	for(int i = 0; i < sizeof(m_static)/sizeof(m_static[0]); i++){//스태틱배열 크기만큼
		if(m_static[i].Create( STATIC_CONTENT[i], WS_CHILD | WS_VISIBLE | WS_EX_WINDOWEDGE | LWS_TRANSPARENT, m_imagemaker->static_Rect[i], this, IDC_STATIC_INITIAL + i) == false ){
			m_logwriter->now_write_log.Format(_T("%s [%d]번째 생성 실패!"), STATIC_CONTENT[i], i);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		}
		if(i==m_static_version){
			m_logwriter->m_font.CreatePointFont(125, _T("맑은 고딕"));//폰트설정
		}
		else if(i==m_static_contents_card){
			m_logwriter->m_font.CreatePointFont(175, _T("맑은 고딕"));//폰트설정
		}
		else{
			m_logwriter->m_font.CreatePointFont(250, _T("맑은 고딕"));//폰트설정
		}
		m_static[i].SetFont(&m_logwriter->m_font, TRUE);//폰트 설정
	}
}

void CImageProcessorDlg::button_make()//버튼 생성
{
	m_logwriter->m_font.CreatePointFont(200, _T("맑은 고딕"));//폰트설정
	for(int i = 0; i < sizeof(m_button)/sizeof(m_button[0]); i++){//스태틱배열 크기만큼
		if(m_button[i].Create( BUTTTON_CONTENT[i], WS_CHILD | WS_VISIBLE | WS_EX_WINDOWEDGE | LWS_TRANSPARENT, m_imagemaker->button_Rect[i], this, IDC_BUTTON_INITIAL + i) == false ){
			m_logwriter->now_write_log.Format(_T("%s 생성 [%d]번째 실패!"), BUTTTON_CONTENT[i], i);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		}
		m_button[i].SetFont(&m_logwriter->m_font, TRUE);//폰트 설정
	}
}

void CImageProcessorDlg::background_collocate()//배경화면배치
{
	for(int i = 0; i< sizeof(m_imagemaker->m_picture_background)/sizeof(m_imagemaker->m_picture_background[0]); i++){	//각 경로에 파일 넣기
		if(i==Now_Image_State){																							//현재 상태의 배경화면이면
			m_imagemaker->m_picture_background[i].ShowWindow(TRUE);
			m_logwriter->now_write_log.Format(_T("현재의 화면 : [%s]"), Now_State_Contents[Now_Image_State]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);														//LOG 기록
		}
		else{
			m_imagemaker->m_picture_background[i].ShowWindow(FALSE);
		}
	}
}

void CImageProcessorDlg::Image_Screen_Change(int change_screen)//화면 변경
{
	int compare = m_imagemmap->check_change_image(change_screen);//화면 변경요구 값과 현재 p_data->now_state 비교 
	if( compare == 100){//일치할 시
		m_logwriter->now_write_log.Format(_T("화면변경 [%s] -> [%s]"), Now_State_Contents[Now_Image_State], Now_State_Contents[change_screen]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		Now_Image_State  = change_screen;//화면 변경
		control_collocate();//컨트롤 배치
	}
	else{//불일치 할시
		m_logwriter->now_write_log.Format(_T("메인 프로세서 화면변경요청 : [%s] p_date->now_state : [%s] 서로 다릅니다."), Now_State_Contents[change_screen], Now_State_Contents[compare]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	}
}

void CImageProcessorDlg::main_return_init()//메인화면 돌아올때 초기화
{
	for(int i = 0; i < sizeof(m_static)/sizeof(m_static[0]); i++){
		m_static[i].SetWindowTextA(STATIC_CONTENT[i]);//스태틱 초기값으로 초기화
	}
	for(int i = 0; i < NUMBER_CARD_FIND; i++){
		number_cards[i] = 0;
	}
	cardsale_fare = 0;
	recharge_fare = 0;
}

void CImageProcessorDlg::update_cardsale(int number)//카드 매수 버튼 눌렀을 때 값 갱신
{
	m_logwriter->now_write_log.Format(_T("%d매 버튼 버튼 클릭"), number);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	number_cards[Now_Selete_Card] = number;//현재 선택된 카드 종류 number장
	for(int i = 0;i <= cardsale_season_ticket;i++){
		static_text.Format(_T("%d 장"), number_cards[i]);
		m_static[m_static_number_adult + i].SetWindowTextA(static_text);
	}
	cardsale_fare = (ADULT_CARD_FARE * number_cards[cardsale_adult]) + (ADOLESCEMT_CARD_FARE * number_cards[cardsale_adolescent]) + (SEASON_TICHET_FARE * number_cards[cardsale_season_ticket]);
	static_text.Format(_T("%d 원"), cardsale_fare);
	m_static[m_static_cardsale_fare].SetWindowTextA(static_text);
	Invalidate(TRUE);
}

void CImageProcessorDlg::cardsale_insert_update()//확인눌렀을시 금액,카드개수 T_RECHARGE_DATA에 갱신 
{
	if(Now_Image_State==cardsale){//카드 판매 금액 선택일경우
		if((number_cards[cardsale_adult] + number_cards[cardsale_adolescent] + number_cards[cardsale_season_ticket]) > 0){//1장이라도 구매의사가 있을 경우	
			static_text.Format(_T("어른 : %d 장, 청소년 : %d, 정기권 : %d"), number_cards[cardsale_adult], number_cards[cardsale_adolescent], number_cards[cardsale_season_ticket]);
			m_static[m_static_contents_card].SetWindowTextA(static_text);
			m_static[m_static_contents_card].GetWindowTextA(m_logwriter->now_write_log);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
			m_logwriter->now_write_log.Format(_T("카드 운임 : [%d]"), m_imagemmap->update_cardsale_insert(number_cards[cardsale_adult], number_cards[cardsale_adolescent], number_cards[cardsale_season_ticket], cardsale_fare));
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
			::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, Now_Image_State + 1, 0);//메인에게 메세지(이미지->메인) 전송//금액선택다음단계인 금액투입
			static_text.Format(_T("%d 원"), cardsale_fare);
			m_static[m_static_cardsale_insert_fare].SetWindowTextA(static_text);
		}
	}
}

void CImageProcessorDlg::select_recharge_fare(int fare)//충전 금액 선택
{
	m_logwriter->now_write_log.Format(_T("충전 %d원 운임 버튼 클릭"), fare);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	if(m_logwriter->MAIN_HWND==NULL){
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않습니다.");//LOG 기록
	}
	else{
		recharge_fare = fare;
		static_text.Format(_T("%d 원"), recharge_fare);
		m_static[m_static_recharge_insert_fare].SetWindowTextA(static_text);
		m_static[m_static_recharge_insert_fare].GetWindowTextA(m_logwriter->now_write_log);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		m_logwriter->WriteLogFile("이미지 -> 메인 메시지 송신완료(금액투입)");//LOG 기록
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, recharge_insert, fare);//메인에게 메세지(이미지->메인) 전송
	}
}

void CImageProcessorDlg::cardsale_insert_renew(int now_insert_money)//카드 판매 투입상태에서 돈(동전 or 지폐) 투입 되었을 때
{
	static_text.Format(_T("%d 원"), now_insert_money);
	m_static[m_static_cardsale_insert_amount].SetWindowTextA(static_text);
	if(now_insert_money > cardsale_fare){
		m_logwriter->now_write_log.Format(_T("투입금액(%d원)이 운임(%d)을 뛰어넘었습니다. 거스름돈은 반환할 수 없습니다."), now_insert_money, cardsale_fare);//LOG 기록//초과 거스름돈 없음
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, cardsale_lack, 0);
	}
	if(m_imagemmap->MMap_Now_InsertMoney() == cardsale_fare){
		m_logwriter->WriteLogFile(_T("투입금액과 운임이 같습니다."));//LOG 기록
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, cardsale_processing, 0);
	}
}

void CImageProcessorDlg::recharge_insert_renew(int now_insert_money)//카드 충전 투입상태에서 돈(동전 or 지폐) 투입 되었을 때
{
	static_text.Format(_T("%d 원"),now_insert_money);
	m_static[m_static_recharge_insert_amount].SetWindowTextA(static_text);
	if(now_insert_money > recharge_fare){
		m_logwriter->now_write_log.Format(_T("투입금액(%d원)이 운임(%d)을 뛰어넘었습니다. 거스름돈은 반환할 수 없습니다."), now_insert_money, recharge_fare);//LOG 기록//초과 거스름돈 없음
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, recharge_lack, 0);
	}
	else if(now_insert_money == recharge_fare){
		m_logwriter->WriteLogFile(_T("투입금액과 운임이 같습니다."));//LOG 기록
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, recharge_processing, 0);
	}
}

void CImageProcessorDlg::change_card_kind()//MMap에서 읽어와 카드종류 표시
{
	static_text.Format(_T("%s"), Traffic_Card_Name[m_imagemmap->MMap_Check_Card_Kind()]);//MMap에서 카드종류 번호읽어와 내용으로 수정
	m_static[m_static_recharge_card_kind].SetWindowTextA(static_text);
	m_static[m_static_recharge_insert_card_kind].SetWindowTextA(static_text);
}

void CImageProcessorDlg::enter_direct(int enter_num)//숫자패드눌러서 직접 입력
{
	m_logwriter->now_write_log.Format(_T("직접 입력 [%d] 버튼 클릭 "), enter_num);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	if(enter_num < 10){
		if(recharge_fare < 10000000){
			recharge_fare = recharge_fare * 10 + enter_num;//현재값 10배로 크게한 후 매개변수 더하기
		}
	}
	else if(enter_num == 10){//000을 누른 경우
		if(recharge_fare < 10000){
			recharge_fare *= 1000;//가격 천배
		}
	}
	else{//enter_num == 11(지움 버튼 누른 경우)
		recharge_fare = 0;
	}
	static_text.Format(_T("%d 원"), recharge_fare);
	m_static[m_static_recharge_fare].SetWindowTextA(static_text);
	Invalidate(TRUE);
}

afx_msg LRESULT CImageProcessorDlg::Main_Image_Message(WPARAM wParam, LPARAM lParam)//메인에서 이미지프로그램에게 메시지 송신했을때 수신 이벤트 함수
{
	if(lParam==0){//금액이 없을 때 화면 변경 요청
		m_logwriter->now_write_log.Format(_T("메인 프로세서에서 [%s] 화면 변경 요청! "), Now_State_Contents[wParam]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		if(wParam == main){
			main_return_init();//메인화면 돌아올때 초기화
		}
		if(wParam == recharge){
			change_card_kind();//MMap에서 읽어와 카드종류 표시
		}
		Image_Screen_Change(wParam);
	}
	else{
		if(m_imagemmap->MMap_Check_Transation_Ready()){//현재 투입 상태 1이라면
			m_logwriter->now_write_log.Format(_T("[%s] 돈 투입 : %d 원"), Now_State_Contents[wParam], lParam);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
			if(Now_Image_State == cardsale_insert){
				cardsale_insert_renew(m_imagemmap->MMap_Now_InsertMoney());//카드 판매 투입상태에서 돈(동전 or 지폐) 투입 되었을 때
			}
			else if(Now_Image_State == recharge_insert){
				recharge_insert_renew(m_imagemmap->MMap_Now_InsertMoney());//카드 충전 투입상태에서 돈(동전 or 지폐) 투입 되었을 때
			}
		}
	}
	Invalidate(TRUE);
	return 0;
}

void CImageProcessorDlg::OnBnClickedINSERTOK()//금액 투입 확인 버튼 눌렀을 경우 이벤트
{
	m_logwriter->WriteLogFile("INSERTOK 버튼 클릭");//LOG 기록
	if(m_logwriter->MAIN_HWND==NULL){
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile("이미지 -> 메인 메시지 송신완료(금액투입준비)");//LOG 기록
		if(Now_Image_State == cardsale){//카드 판매 금액 선택인 경우
			cardsale_insert_update();//확인눌렀을시 금액,카드개수 T_RECHARGE_DATA에 갱신 
		}
		else{//카드 충전 금액 선택인 경우
			if(recharge_fare >= 1000 && (recharge_fare%1000 == 0)){//직접 입력한 값이 천원이상이며 천원보다 작은 단위의 값이 포함되지 않았을 경우
				select_recharge_fare(recharge_fare);//현재설정값으로 금액 투입 진행
			}
		}
	}
	Invalidate(TRUE);
}

void CImageProcessorDlg::OnBnClickedCANCLE()//CANCLE 버튼 눌렀을 경우 이벤트
{
	m_logwriter->WriteLogFile("CANCLE 버튼 클릭");//LOG 기록
	if(m_logwriter->MAIN_HWND==NULL){
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile("이미지 -> 메인 메시지 송신완료(취소)");//LOG 기록
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, main, 0);//메인에게 메세지(이미지->메인) 전송
	}
	Invalidate(TRUE);
}

void CImageProcessorDlg::OnBnClickedCARDSALE()//CARDSALE 버튼 눌렀을 경우 이벤트
{
	m_logwriter->WriteLogFile("CARDSALE 버튼 클릭");//LOG 기록
	if(m_logwriter->MAIN_HWND==NULL){//수신 핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile("이미지 -> 메인 메시지 송신완료(카드판매)");//LOG 기록
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, cardsale, 0);//메인에게 메세지(이미지->메인) 전송 //Wparam : 1 (카드판매)
	}
	Invalidate(TRUE);
}

void CImageProcessorDlg::OnBnClickedRECHARGE()//RECHARGE 버튼 눌렀을 경우 이벤트
{
	m_logwriter->WriteLogFile("RECHARGE 버튼 클릭");//LOG 기록
	if(m_logwriter->MAIN_HWND==NULL){//수신핸들이 존재하지 않는다면
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않아서 메시지 송신을 못했습니다.");//LOG 기록
	}
	else{
		m_logwriter->WriteLogFile("이미지 -> 메인 메시지 송신완료(카드보충_카드대기)");//LOG 기록
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, card_wait, 0);//메인에게 메세지(이미지->메인) 전송 //Wparam : card_wait (카드 장착 대기)
	}
	Invalidate(TRUE);
}

void CImageProcessorDlg::OnBnClickedCARDSALENUMBER3()//CARDSALENUMBER3 버튼 눌렀을 경우 이벤트
{
	update_cardsale(3);//카드 매수 버튼 눌렀을 때 값 갱신
}

void CImageProcessorDlg::OnBnClickedCARDSALENUMBER2()//CARDSALENUMBER2 버튼 눌렀을 경우 이벤트
{
	update_cardsale(2);//카드 매수 버튼 눌렀을 때 값 갱신
}

void CImageProcessorDlg::OnBnClickedCARDSALENUMBER1()//CARDSALENUMBER1 버튼 눌렀을 경우 이벤트
{
	update_cardsale(1);//카드 매수 버튼 눌렀을 때 값 갱신
}

void CImageProcessorDlg::OnBnClickedCARDSALENUMBER0()//CARDSALENUMBER0 버튼 눌렀을 경우 이벤트
{
	update_cardsale(0);//카드 매수 버튼 눌렀을 때 값 갱신
}

void CImageProcessorDlg::OnBnClickedNUMBERADULT()//NUMBERADULT 버튼 눌렀을 경우 이벤트
{
	m_logwriter->WriteLogFile("어른 종류 버튼 버튼 클릭");//LOG 기록
	Now_Selete_Card = cardsale_adult;//현재 고른 카드는 어른
}

void CImageProcessorDlg::OnBnClickedNUMBERADOLESCEMT()//NUMBERADULT 버튼 눌렀을 경우 이벤트
{
	m_logwriter->WriteLogFile("청소년 종류 버튼 버튼 클릭");//LOG 기록
	Now_Selete_Card = cardsale_adolescent;//현재 고른 카드는 청소년
}

void CImageProcessorDlg::OnBnClickedNUMBERSEASONTICKET()//NUMBERADULT 버튼 눌렀을 경우 이벤트
{
	m_logwriter->WriteLogFile("정기권 종류 버튼 버튼 클릭");//LOG 기록
	Now_Selete_Card = cardsale_season_ticket;//현재 고른 카드는 정기권
}

void CImageProcessorDlg::OnBnClickedFARE5000()//충전 5000원 운임 버튼 눌렀을 경우 이벤트
{
	select_recharge_fare(5000);//충전 금액 선택
}

void CImageProcessorDlg::OnBnClickedFARE10000()//충전 10000원 운임 버튼 눌렀을 경우 이벤트
{
	select_recharge_fare(10000);//충전 금액 선택
}

void CImageProcessorDlg::OnBnClickedFARE20000()//충전 20000원 운임 버튼 눌렀을 경우 이벤트
{
	select_recharge_fare(20000);//충전 금액 선택
}

void CImageProcessorDlg::OnBnClickedFARE30000()//충전 30000원 운임 버튼 눌렀을 경우 이벤트
{
	select_recharge_fare(30000);//충전 금액 선택
}

void CImageProcessorDlg::OnBnClickedFARE40000()//충전 40000원 운임 버튼 눌렀을 경우 이벤트
{
	select_recharge_fare(40000);//충전 금액 선택
}

void CImageProcessorDlg::OnBnClickedFARE50000()//충전 50000원 운임 버튼 눌렀을 경우 이벤트
{
	select_recharge_fare(50000);//충전 금액 선택
}

void CImageProcessorDlg::OnBnClickedBEFORE()//이전 버튼 눌렀을 경우 이벤트
{
	m_logwriter->now_write_log.Format(_T("BEFORE 버튼 클릭 현재 Direct_Screen : %d"), Direct_Screen);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
	if(Direct_Screen){//금액 직접 입력일 때 
		Direct_Screen = FALSE;
		control_collocate();//컨트롤 배치
		recharge_fare = 0;
	    m_static[m_static_recharge_fare].SetWindowTextA(_T("0 원"));
        Invalidate(TRUE);
	}
	else{//금액 간접 입력일 때
		if(m_logwriter->MAIN_HWND==NULL){
			m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND 존재하지 않습니다.");//LOG 기록
		}
		else{
			m_logwriter->WriteLogFile("이미지 -> 메인 메시지 송신완료(취소)");//LOG 기록
			::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, main, 0);//메인에게 메세지(이미지->메인) 전송
		}
	}
	Invalidate(TRUE);
}
void CImageProcessorDlg::OnBnClickedDIRECT()	//직접 입력 선택 버튼 눌렀을 경우 이벤트
{
	Direct_Screen = TRUE;
	control_collocate();//컨트롤 배치
}
void CImageProcessorDlg::OnBnClickedADD0()		//직접 입력 0	 버튼 눌렀을 경우 이벤트
{
	enter_direct(0);
}
void CImageProcessorDlg::OnBnClickedADD1()		//직접 입력 1	 버튼 눌렀을 경우 이벤트
{
	enter_direct(1);
}
void CImageProcessorDlg::OnBnClickedADD2()		//직접 입력 2	 버튼 눌렀을 경우 이벤트
{
	enter_direct(2);
}
void CImageProcessorDlg::OnBnClickedADD3()		//직접 입력 3	 버튼 눌렀을 경우 이벤트
{
	enter_direct(3);
}
void CImageProcessorDlg::OnBnClickedADD4()		//직접 입력 4	 버튼 눌렀을 경우 이벤트
{
	enter_direct(4);
}
void CImageProcessorDlg::OnBnClickedADD5()		//직접 입력 5	 버튼 눌렀을 경우 이벤트
{
	enter_direct(5);
}
void CImageProcessorDlg::OnBnClickedADD6()		//직접 입력 6	 버튼 눌렀을 경우 이벤트
{
	enter_direct(6);
}
void CImageProcessorDlg::OnBnClickedADD7()		//직접 입력 7	 버튼 눌렀을 경우 이벤트
{
	enter_direct(7);
}
void CImageProcessorDlg::OnBnClickedADD8()		//직접 입력 8	 버튼 눌렀을 경우 이벤트
{
	enter_direct(8);
}
void CImageProcessorDlg::OnBnClickedADD9()		//직접 입력 9	 버튼 눌렀을 경우 이벤트
{
	enter_direct(9);
}
void CImageProcessorDlg::OnBnClickedADD000()	//직접 입력 000  버튼 눌렀을 경우 이벤트
{
	enter_direct(10);
}
void CImageProcessorDlg::OnBnClickedERASE()		//직접 입력 지움 버튼 눌렀을 경우 이벤트
{
	enter_direct(11);
}