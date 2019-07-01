
// ImageProcessorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ImageProcessor.h"
#include "ImageProcessorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessorDlg ��ȭ ����

CImageProcessorDlg::CImageProcessorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CImageProcessorDlg::IDD, pParent)
	, m_imagemmap(new CImageMMap())//�̹��� �޸𸮸� ����
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
		case CTLCOLOR_STATIC://����ƽ
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
		case CTLCOLOR_BTN://��ư
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
	ON_MESSAGE(UM_MAIN_IMAGE_MESSAGE, CImageProcessorDlg::Main_Image_Message)//���ο��� �̹������α׷����� �޽��� �۽������� ���� �̺�Ʈó��
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT_OK				, &CImageProcessorDlg::OnBnClickedINSERTOK)				//�ݾ� ���� Ȯ�� ��ư�̺�Ʈó��
	ON_BN_CLICKED(IDC_BUTTON_CARDSALE				, &CImageProcessorDlg::OnBnClickedCARDSALE)				//ī���Ǹ� �̺�Ʈó��
	ON_BN_CLICKED(IDC_BUTTON_RECHARGE				, &CImageProcessorDlg::OnBnClickedRECHARGE)				//ī������ �̺�Ʈó��
	ON_BN_CLICKED(IDC_BUTTON_CARDSALE_NUMBER3		, &CImageProcessorDlg::OnBnClickedCARDSALENUMBER3)		//3�Ź�ư �̺�Ʈó��
	ON_BN_CLICKED(IDC_BUTTON_CARDSALE_NUMBER2		, &CImageProcessorDlg::OnBnClickedCARDSALENUMBER2)		//2�Ź�ư �̺�Ʈó��
	ON_BN_CLICKED(IDC_BUTTON_CARDSALE_NUMBER1		, &CImageProcessorDlg::OnBnClickedCARDSALENUMBER1)		//1�Ź�ư �̺�Ʈó��
	ON_BN_CLICKED(IDC_BUTTON_CARDSALE_NUMBER0		, &CImageProcessorDlg::OnBnClickedCARDSALENUMBER0)		//0�Ź�ư �̺�Ʈó��
	ON_BN_CLICKED(IDC_BUTTON_NUMBER_ADULT			, &CImageProcessorDlg::OnBnClickedNUMBERADULT)			//� ���� ��ư �̺�Ʈó��
	ON_BN_CLICKED(IDC_BUTTON_NUMBER_ADOLESCEMT		, &CImageProcessorDlg::OnBnClickedNUMBERADOLESCEMT)		//� ���� ��ư �̺�Ʈó��
	ON_BN_CLICKED(IDC_BUTTON_NUMBER_SEASON_TICKET	, &CImageProcessorDlg::OnBnClickedNUMBERSEASONTICKET)	//� ���� ��ư �̺�Ʈó��
	ON_BN_CLICKED(IDC_BUTTON_FARE_5000				, &CImageProcessorDlg::OnBnClickedFARE5000)				//����  5000�� ���� ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_FARE_10000				, &CImageProcessorDlg::OnBnClickedFARE10000)			//���� 10000�� ���� ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_FARE_20000				, &CImageProcessorDlg::OnBnClickedFARE20000)			//���� 20000�� ���� ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_FARE_30000				, &CImageProcessorDlg::OnBnClickedFARE30000)			//���� 30000�� ���� ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_FARE_40000				, &CImageProcessorDlg::OnBnClickedFARE40000)			//���� 40000�� ���� ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_FARE_50000				, &CImageProcessorDlg::OnBnClickedFARE50000)			//���� 50000�� ���� ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_BEFORE					, &CImageProcessorDlg::OnBnClickedBEFORE)				//���� ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_DIRECT					, &CImageProcessorDlg::OnBnClickedDIRECT)				//���� �Է� ���� ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_0					, &CImageProcessorDlg::OnBnClickedADD0)					//���� �Է� 0	 ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_1					, &CImageProcessorDlg::OnBnClickedADD1)					//���� �Է� 1	 ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_2					, &CImageProcessorDlg::OnBnClickedADD2)					//���� �Է� 2	 ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_3					, &CImageProcessorDlg::OnBnClickedADD3)					//���� �Է� 3	 ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_4					, &CImageProcessorDlg::OnBnClickedADD4)					//���� �Է� 4	 ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_5					, &CImageProcessorDlg::OnBnClickedADD5)					//���� �Է� 5	 ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_6					, &CImageProcessorDlg::OnBnClickedADD6)					//���� �Է� 6	 ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_7					, &CImageProcessorDlg::OnBnClickedADD7)					//���� �Է� 7	 ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_8					, &CImageProcessorDlg::OnBnClickedADD8)					//���� �Է� 8	 ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_9					, &CImageProcessorDlg::OnBnClickedADD9)					//���� �Է� 9	 ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ADD_000				, &CImageProcessorDlg::OnBnClickedADD000)				//���� �Է� 000  ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_ERASE					, &CImageProcessorDlg::OnBnClickedERASE)				//���� �Է� ���� ��ư ������ ��� �̺�Ʈ
	ON_BN_CLICKED(IDC_BUTTON_CANCLE					, &CImageProcessorDlg::OnBnClickedCANCLE)				//���           ��ư ������ ��� �̺�Ʈó��					   
END_MESSAGE_MAP()

// CImageProcessorDlg �޽��� ó����

BOOL CImageProcessorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
	m_logwriter->Log_Make(_T("ImageProcessor"), _T("08_Image"));//�ش� ���� �� ���� ����
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	control_make();//��Ʈ�� ����
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}
// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CImageProcessorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CImageProcessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImageProcessorDlg::control_collocate(){//��Ʈ�� ��ġ
	background_collocate();//���ȭ���ġ
	//����ƽ ��ġ
	m_static[m_static_number_adult].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);								//� ���� �ؽ�Ʈ�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_static[m_static_number_adolescent].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);						//û�ҳ� ���� �ؽ�Ʈ�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_static[m_static_number_season_ticket].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);						//����� ���� �ؽ�Ʈ�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_static[m_static_contents_card].ShowWindow((Now_Image_State == cardsale_insert) ? TRUE : FALSE);					//��� ���� ���� ���°� ī�� �Ǹ� �ݾ� �����϶� 
	m_static[m_static_cardsale_fare].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//ī�弱�ÿ��(����) ���� �ؽ�Ʈ�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_static[m_static_cardsale_insert_fare].ShowWindow(Now_Image_State == cardsale_insert ? TRUE : FALSE);				//���(����)�ؽ�Ʈ�� ���� ���°� �����϶� 
	m_static[m_static_cardsale_insert_amount].ShowWindow(Now_Image_State == cardsale_insert ? TRUE : FALSE);			//���Աݾ��ؽ�Ʈ�� ���� ���°� �����϶� 
	m_static[m_static_recharge_card_kind].ShowWindow(Now_Image_State == recharge ? TRUE : FALSE);						//ī�� ���� ���� ȭ�� ���� ī�� ����(�ϳ���, ���̺�, ĳ�ú�, Ƽ�Ӵ�)�� ī�� ���� �ݾ� ������ ��
	m_static[m_static_recharge_card_number].ShowWindow(Now_Image_State == recharge ? TRUE : FALSE);						//ī�� ���� ���� ȭ�� ���� ī�� ��ȣ�� ī�� ���� �ݾ� ������ �� 
	m_static[m_static_recharge_card_balance].ShowWindow(Now_Image_State == recharge ? TRUE : FALSE);					//ī�� ���� ���� ȭ�� ���� ī�� �ܾ״� ī�� ���� �ݾ� ������ ��
	m_static[m_static_recharge_fare].ShowWindow(Now_Image_State == recharge ? TRUE : FALSE);							//ī�� ���� ���� ȭ�� �Ǹ� ���� �ؽ�Ʈ�� ī�� ���� �ݾ� ������ ��
	m_static[m_static_recharge_insert_card_kind].ShowWindow(Now_Image_State == recharge_insert ? TRUE : FALSE);			//ī�� ���� ���� ȭ�� ���� ī�� ����(�ϳ���, ���̺�, ĳ�ú�, Ƽ�Ӵ�)�� ī�� ���� �ݾ� ������ ��
	m_static[m_static_recharge_insert_card_balance].ShowWindow(Now_Image_State == recharge_insert ? TRUE : FALSE);		//ī�� ���� ���� ȭ�� ���� ī�� �ܾ״� ī�� ���� �ݾ� ������ ��
	m_static[m_static_recharge_insert_fare].ShowWindow(Now_Image_State == recharge_insert ? TRUE : FALSE);				//ī�� ���� ���� ȭ�� �Ǹ� ���� �ؽ�Ʈ�� ī�� ���� �ݾ� ������ ��
	m_static[m_static_recharge_insert_amount].ShowWindow(Now_Image_State == recharge_insert ? TRUE : FALSE);			//ī�� ���� ���� ȭ�� ����� ���� ���� �ݾ״� ī�� ���� �ݾ� ������ ��
	m_static[m_static_version].ShowWindow(Now_Image_State == main ? TRUE : FALSE);										//�����ؽ�Ʈ�� ���� ���°� �����϶� 
	//��ư ��ġ						
	m_button[m_button_insert_ok].ShowWindow((Now_Image_State == cardsale || (Now_Image_State == recharge && Direct_Screen == TRUE)) ? TRUE : FALSE);//�ݾ�Ȯ�ι�ư�� ī���Ǹűݾ׼���ȭ�� �Ǵ� ���� �����Է� �϶� Ȱ��ȭ
	m_button[m_button_cardsale].ShowWindow(Now_Image_State == main ? TRUE : FALSE);										//�Ǹ� ��ư�� ���� ���°� �����϶� 
	m_button[m_button_recharge].ShowWindow(Now_Image_State == main ? TRUE : FALSE);										//���� ��ư�� ���� ���°� �����϶� 
	m_button[m_button_cardsale_number3].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//�ż�3 ��ư�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_button[m_button_cardsale_number2].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//�ż�2 ��ư�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_button[m_button_cardsale_number1].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//�ż�1 ��ư�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_button[m_button_cardsale_number0].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//�ż�0 ��ư�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_button[m_button_kind_adult].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);								//� ���� ��ư�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_button[m_button_kind_adolescent].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);							//û�ҳ� ���� ��ư�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_button[m_button_kind_season_ticket].ShowWindow(Now_Image_State == cardsale ? TRUE : FALSE);						//����� ���� ��ư�� ���� ���°� ī�� �Ǹ� �ݾ� ���� ȭ���� ��
	m_button[m_button_fare_5000]. ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//���� �ݾ� ���� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����
	m_button[m_button_fare_10000].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//���� �ݾ� ���� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����
	m_button[m_button_fare_20000].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//���� �ݾ� ���� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����
	m_button[m_button_fare_30000].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//���� �ݾ� ���� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����
	m_button[m_button_fare_40000].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//���� �ݾ� ���� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����
	m_button[m_button_fare_50000].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);	//���� �ݾ� ���� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����
	m_button[m_button_before].ShowWindow((Now_Image_State == recharge) ? TRUE : FALSE);									//���� �ݾ� ���� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ����, ���� ������� �� ȭ�� ��� Ȱ��ȭ
	m_button[m_button_direct].ShowWindow((Now_Image_State == recharge && Direct_Screen == FALSE) ? TRUE : FALSE);		//���� �ݾ� ���� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����
	m_button[m_button_add_0].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����	
	m_button[m_button_add_1].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����	
	m_button[m_button_add_2].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����	
	m_button[m_button_add_3].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����	
	m_button[m_button_add_4].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����	
	m_button[m_button_add_5].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����	
	m_button[m_button_add_6].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����	
	m_button[m_button_add_7].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����	
	m_button[m_button_add_8].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����
	m_button[m_button_add_9].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����
	m_button[m_button_add_000].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);		//���� �ݾ� �Է� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����	
	m_button[m_button_erase].ShowWindow((Now_Image_State == recharge && Direct_Screen == TRUE) ? TRUE : FALSE);			//���� ��ư�� ���� ���°� ī�� ���� �ݾ� ���� ȭ���� ��, ���� �ݾ� ����
	m_button[m_button_cancle].ShowWindow((Now_Image_State == cardsale || Now_Image_State == cardsale_insert || Now_Image_State == recharge_insert) ? TRUE : FALSE);//��ҹ�ư�� ���� ���°� ����,�Ǹ� �ݾ�,�����϶� 

}

void CImageProcessorDlg::control_make()																					//��Ʈ�� ����
{
	background_make();																									//��� ����
	static_make();																										//�ؽ�Ʈ ����
	button_make();																										//��ư ����
	control_collocate();																								//��Ʈ�� ��ġ
}

void CImageProcessorDlg::background_make()//��� ����
{
	this->SetWindowPos(NULL, 0, 0, GetSystemMetrics(SM_CXSCREEN), (GetSystemMetrics(SM_CYSCREEN)), SWP_NOREPOSITION);//âũ�� ����
	m_imagemaker->background_make();
}

void CImageProcessorDlg::static_make(){//�ؽ�Ʈ ����
	for(int i = 0; i < sizeof(m_static)/sizeof(m_static[0]); i++){//����ƽ�迭 ũ�⸸ŭ
		if(m_static[i].Create( STATIC_CONTENT[i], WS_CHILD | WS_VISIBLE | WS_EX_WINDOWEDGE | LWS_TRANSPARENT, m_imagemaker->static_Rect[i], this, IDC_STATIC_INITIAL + i) == false ){
			m_logwriter->now_write_log.Format(_T("%s [%d]��° ���� ����!"), STATIC_CONTENT[i], i);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		}
		if(i==m_static_version){
			m_logwriter->m_font.CreatePointFont(125, _T("���� ���"));//��Ʈ����
		}
		else if(i==m_static_contents_card){
			m_logwriter->m_font.CreatePointFont(175, _T("���� ���"));//��Ʈ����
		}
		else{
			m_logwriter->m_font.CreatePointFont(250, _T("���� ���"));//��Ʈ����
		}
		m_static[i].SetFont(&m_logwriter->m_font, TRUE);//��Ʈ ����
	}
}

void CImageProcessorDlg::button_make()//��ư ����
{
	m_logwriter->m_font.CreatePointFont(200, _T("���� ���"));//��Ʈ����
	for(int i = 0; i < sizeof(m_button)/sizeof(m_button[0]); i++){//����ƽ�迭 ũ�⸸ŭ
		if(m_button[i].Create( BUTTTON_CONTENT[i], WS_CHILD | WS_VISIBLE | WS_EX_WINDOWEDGE | LWS_TRANSPARENT, m_imagemaker->button_Rect[i], this, IDC_BUTTON_INITIAL + i) == false ){
			m_logwriter->now_write_log.Format(_T("%s ���� [%d]��° ����!"), BUTTTON_CONTENT[i], i);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		}
		m_button[i].SetFont(&m_logwriter->m_font, TRUE);//��Ʈ ����
	}
}

void CImageProcessorDlg::background_collocate()//���ȭ���ġ
{
	for(int i = 0; i< sizeof(m_imagemaker->m_picture_background)/sizeof(m_imagemaker->m_picture_background[0]); i++){	//�� ��ο� ���� �ֱ�
		if(i==Now_Image_State){																							//���� ������ ���ȭ���̸�
			m_imagemaker->m_picture_background[i].ShowWindow(TRUE);
			m_logwriter->now_write_log.Format(_T("������ ȭ�� : [%s]"), Now_State_Contents[Now_Image_State]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);														//LOG ���
		}
		else{
			m_imagemaker->m_picture_background[i].ShowWindow(FALSE);
		}
	}
}

void CImageProcessorDlg::Image_Screen_Change(int change_screen)//ȭ�� ����
{
	int compare = m_imagemmap->check_change_image(change_screen);//ȭ�� ����䱸 ���� ���� p_data->now_state �� 
	if( compare == 100){//��ġ�� ��
		m_logwriter->now_write_log.Format(_T("ȭ�麯�� [%s] -> [%s]"), Now_State_Contents[Now_Image_State], Now_State_Contents[change_screen]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		Now_Image_State  = change_screen;//ȭ�� ����
		control_collocate();//��Ʈ�� ��ġ
	}
	else{//����ġ �ҽ�
		m_logwriter->now_write_log.Format(_T("���� ���μ��� ȭ�麯���û : [%s] p_date->now_state : [%s] ���� �ٸ��ϴ�."), Now_State_Contents[change_screen], Now_State_Contents[compare]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
}

void CImageProcessorDlg::main_return_init()//����ȭ�� ���ƿö� �ʱ�ȭ
{
	for(int i = 0; i < sizeof(m_static)/sizeof(m_static[0]); i++){
		m_static[i].SetWindowTextA(STATIC_CONTENT[i]);//����ƽ �ʱⰪ���� �ʱ�ȭ
	}
	for(int i = 0; i < NUMBER_CARD_FIND; i++){
		number_cards[i] = 0;
	}
	cardsale_fare = 0;
	recharge_fare = 0;
}

void CImageProcessorDlg::update_cardsale(int number)//ī�� �ż� ��ư ������ �� �� ����
{
	m_logwriter->now_write_log.Format(_T("%d�� ��ư ��ư Ŭ��"), number);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	number_cards[Now_Selete_Card] = number;//���� ���õ� ī�� ���� number��
	for(int i = 0;i <= cardsale_season_ticket;i++){
		static_text.Format(_T("%d ��"), number_cards[i]);
		m_static[m_static_number_adult + i].SetWindowTextA(static_text);
	}
	cardsale_fare = (ADULT_CARD_FARE * number_cards[cardsale_adult]) + (ADOLESCEMT_CARD_FARE * number_cards[cardsale_adolescent]) + (SEASON_TICHET_FARE * number_cards[cardsale_season_ticket]);
	static_text.Format(_T("%d ��"), cardsale_fare);
	m_static[m_static_cardsale_fare].SetWindowTextA(static_text);
	Invalidate(TRUE);
}

void CImageProcessorDlg::cardsale_insert_update()//Ȯ�δ������� �ݾ�,ī�尳�� T_RECHARGE_DATA�� ���� 
{
	if(Now_Image_State==cardsale){//ī�� �Ǹ� �ݾ� �����ϰ��
		if((number_cards[cardsale_adult] + number_cards[cardsale_adolescent] + number_cards[cardsale_season_ticket]) > 0){//1���̶� �����ǻ簡 ���� ���	
			static_text.Format(_T("� : %d ��, û�ҳ� : %d, ����� : %d"), number_cards[cardsale_adult], number_cards[cardsale_adolescent], number_cards[cardsale_season_ticket]);
			m_static[m_static_contents_card].SetWindowTextA(static_text);
			m_static[m_static_contents_card].GetWindowTextA(m_logwriter->now_write_log);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
			m_logwriter->now_write_log.Format(_T("ī�� ���� : [%d]"), m_imagemmap->update_cardsale_insert(number_cards[cardsale_adult], number_cards[cardsale_adolescent], number_cards[cardsale_season_ticket], cardsale_fare));
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
			::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, Now_Image_State + 1, 0);//���ο��� �޼���(�̹���->����) ����//�ݾ׼��ô����ܰ��� �ݾ�����
			static_text.Format(_T("%d ��"), cardsale_fare);
			m_static[m_static_cardsale_insert_fare].SetWindowTextA(static_text);
		}
	}
}

void CImageProcessorDlg::select_recharge_fare(int fare)//���� �ݾ� ����
{
	m_logwriter->now_write_log.Format(_T("���� %d�� ���� ��ư Ŭ��"), fare);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	if(m_logwriter->MAIN_HWND==NULL){
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʽ��ϴ�.");//LOG ���
	}
	else{
		recharge_fare = fare;
		static_text.Format(_T("%d ��"), recharge_fare);
		m_static[m_static_recharge_insert_fare].SetWindowTextA(static_text);
		m_static[m_static_recharge_insert_fare].GetWindowTextA(m_logwriter->now_write_log);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		m_logwriter->WriteLogFile("�̹��� -> ���� �޽��� �۽ſϷ�(�ݾ�����)");//LOG ���
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, recharge_insert, fare);//���ο��� �޼���(�̹���->����) ����
	}
}

void CImageProcessorDlg::cardsale_insert_renew(int now_insert_money)//ī�� �Ǹ� ���Ի��¿��� ��(���� or ����) ���� �Ǿ��� ��
{
	static_text.Format(_T("%d ��"), now_insert_money);
	m_static[m_static_cardsale_insert_amount].SetWindowTextA(static_text);
	if(now_insert_money > cardsale_fare){
		m_logwriter->now_write_log.Format(_T("���Աݾ�(%d��)�� ����(%d)�� �پ�Ѿ����ϴ�. �Ž������� ��ȯ�� �� �����ϴ�."), now_insert_money, cardsale_fare);//LOG ���//�ʰ� �Ž����� ����
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, cardsale_lack, 0);
	}
	if(m_imagemmap->MMap_Now_InsertMoney() == cardsale_fare){
		m_logwriter->WriteLogFile(_T("���Աݾװ� ������ �����ϴ�."));//LOG ���
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, cardsale_processing, 0);
	}
}

void CImageProcessorDlg::recharge_insert_renew(int now_insert_money)//ī�� ���� ���Ի��¿��� ��(���� or ����) ���� �Ǿ��� ��
{
	static_text.Format(_T("%d ��"),now_insert_money);
	m_static[m_static_recharge_insert_amount].SetWindowTextA(static_text);
	if(now_insert_money > recharge_fare){
		m_logwriter->now_write_log.Format(_T("���Աݾ�(%d��)�� ����(%d)�� �پ�Ѿ����ϴ�. �Ž������� ��ȯ�� �� �����ϴ�."), now_insert_money, recharge_fare);//LOG ���//�ʰ� �Ž����� ����
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, recharge_lack, 0);
	}
	else if(now_insert_money == recharge_fare){
		m_logwriter->WriteLogFile(_T("���Աݾװ� ������ �����ϴ�."));//LOG ���
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, recharge_processing, 0);
	}
}

void CImageProcessorDlg::change_card_kind()//MMap���� �о�� ī������ ǥ��
{
	static_text.Format(_T("%s"), Traffic_Card_Name[m_imagemmap->MMap_Check_Card_Kind()]);//MMap���� ī������ ��ȣ�о�� �������� ����
	m_static[m_static_recharge_card_kind].SetWindowTextA(static_text);
	m_static[m_static_recharge_insert_card_kind].SetWindowTextA(static_text);
}

void CImageProcessorDlg::enter_direct(int enter_num)//�����е崭���� ���� �Է�
{
	m_logwriter->now_write_log.Format(_T("���� �Է� [%d] ��ư Ŭ�� "), enter_num);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	if(enter_num < 10){
		if(recharge_fare < 10000000){
			recharge_fare = recharge_fare * 10 + enter_num;//���簪 10��� ũ���� �� �Ű����� ���ϱ�
		}
	}
	else if(enter_num == 10){//000�� ���� ���
		if(recharge_fare < 10000){
			recharge_fare *= 1000;//���� õ��
		}
	}
	else{//enter_num == 11(���� ��ư ���� ���)
		recharge_fare = 0;
	}
	static_text.Format(_T("%d ��"), recharge_fare);
	m_static[m_static_recharge_fare].SetWindowTextA(static_text);
	Invalidate(TRUE);
}

afx_msg LRESULT CImageProcessorDlg::Main_Image_Message(WPARAM wParam, LPARAM lParam)//���ο��� �̹������α׷����� �޽��� �۽������� ���� �̺�Ʈ �Լ�
{
	if(lParam==0){//�ݾ��� ���� �� ȭ�� ���� ��û
		m_logwriter->now_write_log.Format(_T("���� ���μ������� [%s] ȭ�� ���� ��û! "), Now_State_Contents[wParam]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		if(wParam == main){
			main_return_init();//����ȭ�� ���ƿö� �ʱ�ȭ
		}
		if(wParam == recharge){
			change_card_kind();//MMap���� �о�� ī������ ǥ��
		}
		Image_Screen_Change(wParam);
	}
	else{
		if(m_imagemmap->MMap_Check_Transation_Ready()){//���� ���� ���� 1�̶��
			m_logwriter->now_write_log.Format(_T("[%s] �� ���� : %d ��"), Now_State_Contents[wParam], lParam);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
			if(Now_Image_State == cardsale_insert){
				cardsale_insert_renew(m_imagemmap->MMap_Now_InsertMoney());//ī�� �Ǹ� ���Ի��¿��� ��(���� or ����) ���� �Ǿ��� ��
			}
			else if(Now_Image_State == recharge_insert){
				recharge_insert_renew(m_imagemmap->MMap_Now_InsertMoney());//ī�� ���� ���Ի��¿��� ��(���� or ����) ���� �Ǿ��� ��
			}
		}
	}
	Invalidate(TRUE);
	return 0;
}

void CImageProcessorDlg::OnBnClickedINSERTOK()//�ݾ� ���� Ȯ�� ��ư ������ ��� �̺�Ʈ
{
	m_logwriter->WriteLogFile("INSERTOK ��ư Ŭ��");//LOG ���
	if(m_logwriter->MAIN_HWND==NULL){
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʽ��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile("�̹��� -> ���� �޽��� �۽ſϷ�(�ݾ������غ�)");//LOG ���
		if(Now_Image_State == cardsale){//ī�� �Ǹ� �ݾ� ������ ���
			cardsale_insert_update();//Ȯ�δ������� �ݾ�,ī�尳�� T_RECHARGE_DATA�� ���� 
		}
		else{//ī�� ���� �ݾ� ������ ���
			if(recharge_fare >= 1000 && (recharge_fare%1000 == 0)){//���� �Է��� ���� õ���̻��̸� õ������ ���� ������ ���� ���Ե��� �ʾ��� ���
				select_recharge_fare(recharge_fare);//���缳�������� �ݾ� ���� ����
			}
		}
	}
	Invalidate(TRUE);
}

void CImageProcessorDlg::OnBnClickedCANCLE()//CANCLE ��ư ������ ��� �̺�Ʈ
{
	m_logwriter->WriteLogFile("CANCLE ��ư Ŭ��");//LOG ���
	if(m_logwriter->MAIN_HWND==NULL){
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʽ��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile("�̹��� -> ���� �޽��� �۽ſϷ�(���)");//LOG ���
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, main, 0);//���ο��� �޼���(�̹���->����) ����
	}
	Invalidate(TRUE);
}

void CImageProcessorDlg::OnBnClickedCARDSALE()//CARDSALE ��ư ������ ��� �̺�Ʈ
{
	m_logwriter->WriteLogFile("CARDSALE ��ư Ŭ��");//LOG ���
	if(m_logwriter->MAIN_HWND==NULL){//���� �ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile("�̹��� -> ���� �޽��� �۽ſϷ�(ī���Ǹ�)");//LOG ���
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, cardsale, 0);//���ο��� �޼���(�̹���->����) ���� //Wparam : 1 (ī���Ǹ�)
	}
	Invalidate(TRUE);
}

void CImageProcessorDlg::OnBnClickedRECHARGE()//RECHARGE ��ư ������ ��� �̺�Ʈ
{
	m_logwriter->WriteLogFile("RECHARGE ��ư Ŭ��");//LOG ���
	if(m_logwriter->MAIN_HWND==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile("�̹��� -> ���� �޽��� �۽ſϷ�(ī�庸��_ī����)");//LOG ���
		::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, card_wait, 0);//���ο��� �޼���(�̹���->����) ���� //Wparam : card_wait (ī�� ���� ���)
	}
	Invalidate(TRUE);
}

void CImageProcessorDlg::OnBnClickedCARDSALENUMBER3()//CARDSALENUMBER3 ��ư ������ ��� �̺�Ʈ
{
	update_cardsale(3);//ī�� �ż� ��ư ������ �� �� ����
}

void CImageProcessorDlg::OnBnClickedCARDSALENUMBER2()//CARDSALENUMBER2 ��ư ������ ��� �̺�Ʈ
{
	update_cardsale(2);//ī�� �ż� ��ư ������ �� �� ����
}

void CImageProcessorDlg::OnBnClickedCARDSALENUMBER1()//CARDSALENUMBER1 ��ư ������ ��� �̺�Ʈ
{
	update_cardsale(1);//ī�� �ż� ��ư ������ �� �� ����
}

void CImageProcessorDlg::OnBnClickedCARDSALENUMBER0()//CARDSALENUMBER0 ��ư ������ ��� �̺�Ʈ
{
	update_cardsale(0);//ī�� �ż� ��ư ������ �� �� ����
}

void CImageProcessorDlg::OnBnClickedNUMBERADULT()//NUMBERADULT ��ư ������ ��� �̺�Ʈ
{
	m_logwriter->WriteLogFile("� ���� ��ư ��ư Ŭ��");//LOG ���
	Now_Selete_Card = cardsale_adult;//���� �� ī��� �
}

void CImageProcessorDlg::OnBnClickedNUMBERADOLESCEMT()//NUMBERADULT ��ư ������ ��� �̺�Ʈ
{
	m_logwriter->WriteLogFile("û�ҳ� ���� ��ư ��ư Ŭ��");//LOG ���
	Now_Selete_Card = cardsale_adolescent;//���� �� ī��� û�ҳ�
}

void CImageProcessorDlg::OnBnClickedNUMBERSEASONTICKET()//NUMBERADULT ��ư ������ ��� �̺�Ʈ
{
	m_logwriter->WriteLogFile("����� ���� ��ư ��ư Ŭ��");//LOG ���
	Now_Selete_Card = cardsale_season_ticket;//���� �� ī��� �����
}

void CImageProcessorDlg::OnBnClickedFARE5000()//���� 5000�� ���� ��ư ������ ��� �̺�Ʈ
{
	select_recharge_fare(5000);//���� �ݾ� ����
}

void CImageProcessorDlg::OnBnClickedFARE10000()//���� 10000�� ���� ��ư ������ ��� �̺�Ʈ
{
	select_recharge_fare(10000);//���� �ݾ� ����
}

void CImageProcessorDlg::OnBnClickedFARE20000()//���� 20000�� ���� ��ư ������ ��� �̺�Ʈ
{
	select_recharge_fare(20000);//���� �ݾ� ����
}

void CImageProcessorDlg::OnBnClickedFARE30000()//���� 30000�� ���� ��ư ������ ��� �̺�Ʈ
{
	select_recharge_fare(30000);//���� �ݾ� ����
}

void CImageProcessorDlg::OnBnClickedFARE40000()//���� 40000�� ���� ��ư ������ ��� �̺�Ʈ
{
	select_recharge_fare(40000);//���� �ݾ� ����
}

void CImageProcessorDlg::OnBnClickedFARE50000()//���� 50000�� ���� ��ư ������ ��� �̺�Ʈ
{
	select_recharge_fare(50000);//���� �ݾ� ����
}

void CImageProcessorDlg::OnBnClickedBEFORE()//���� ��ư ������ ��� �̺�Ʈ
{
	m_logwriter->now_write_log.Format(_T("BEFORE ��ư Ŭ�� ���� Direct_Screen : %d"), Direct_Screen);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	if(Direct_Screen){//�ݾ� ���� �Է��� �� 
		Direct_Screen = FALSE;
		control_collocate();//��Ʈ�� ��ġ
		recharge_fare = 0;
	    m_static[m_static_recharge_fare].SetWindowTextA(_T("0 ��"));
        Invalidate(TRUE);
	}
	else{//�ݾ� ���� �Է��� ��
		if(m_logwriter->MAIN_HWND==NULL){
			m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʽ��ϴ�.");//LOG ���
		}
		else{
			m_logwriter->WriteLogFile("�̹��� -> ���� �޽��� �۽ſϷ�(���)");//LOG ���
			::SendMessage(m_logwriter->MAIN_HWND, UM_IMAGE_MAIN_MESSAGE, main, 0);//���ο��� �޼���(�̹���->����) ����
		}
	}
	Invalidate(TRUE);
}
void CImageProcessorDlg::OnBnClickedDIRECT()	//���� �Է� ���� ��ư ������ ��� �̺�Ʈ
{
	Direct_Screen = TRUE;
	control_collocate();//��Ʈ�� ��ġ
}
void CImageProcessorDlg::OnBnClickedADD0()		//���� �Է� 0	 ��ư ������ ��� �̺�Ʈ
{
	enter_direct(0);
}
void CImageProcessorDlg::OnBnClickedADD1()		//���� �Է� 1	 ��ư ������ ��� �̺�Ʈ
{
	enter_direct(1);
}
void CImageProcessorDlg::OnBnClickedADD2()		//���� �Է� 2	 ��ư ������ ��� �̺�Ʈ
{
	enter_direct(2);
}
void CImageProcessorDlg::OnBnClickedADD3()		//���� �Է� 3	 ��ư ������ ��� �̺�Ʈ
{
	enter_direct(3);
}
void CImageProcessorDlg::OnBnClickedADD4()		//���� �Է� 4	 ��ư ������ ��� �̺�Ʈ
{
	enter_direct(4);
}
void CImageProcessorDlg::OnBnClickedADD5()		//���� �Է� 5	 ��ư ������ ��� �̺�Ʈ
{
	enter_direct(5);
}
void CImageProcessorDlg::OnBnClickedADD6()		//���� �Է� 6	 ��ư ������ ��� �̺�Ʈ
{
	enter_direct(6);
}
void CImageProcessorDlg::OnBnClickedADD7()		//���� �Է� 7	 ��ư ������ ��� �̺�Ʈ
{
	enter_direct(7);
}
void CImageProcessorDlg::OnBnClickedADD8()		//���� �Է� 8	 ��ư ������ ��� �̺�Ʈ
{
	enter_direct(8);
}
void CImageProcessorDlg::OnBnClickedADD9()		//���� �Է� 9	 ��ư ������ ��� �̺�Ʈ
{
	enter_direct(9);
}
void CImageProcessorDlg::OnBnClickedADD000()	//���� �Է� 000  ��ư ������ ��� �̺�Ʈ
{
	enter_direct(10);
}
void CImageProcessorDlg::OnBnClickedERASE()		//���� �Է� ���� ��ư ������ ��� �̺�Ʈ
{
	enter_direct(11);
}