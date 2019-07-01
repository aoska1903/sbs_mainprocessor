
// RechargeProcessorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "RechargeProcessor.h"
#include "RechargeProcessorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRechargeProcessorDlg ��ȭ ����

CRechargeProcessorDlg::CRechargeProcessorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRechargeProcessorDlg::IDD, pParent)
	, m_rechargemmap(new CRechargeMMap())//�ŷ� ���� �޸𸮸� ����
	, m_logwriter(new CLogWriter())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRechargeProcessorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CARDTAG , m_button_cardtag); //ī�� �±� ��ư
	DDX_Control(pDX, IDC_BUTTON_NO_COGNIZE , m_button_no_cognize); //���ν� ī�� �±� ��ư
	DDX_Control(pDX, IDC_BUTTON_HANARO, m_button_hanaro);//�ϳ��� ī�� �±� ��ư
	DDX_Control(pDX, IDC_BUTTON_MYBI, m_button_mybi);//���̺� ī�� �±� ��ư
	DDX_Control(pDX, IDC_BUTTON_CASHBEE, m_button_cashbee);//ĳ�ú� ī�� �±� ��ư
	DDX_Control(pDX, IDC_BUTTON_TMONEY, m_button_Tmoney);//Ƽ�Ӵ� ī�� �±� ��ư
}

BEGIN_MESSAGE_MAP(CRechargeProcessorDlg, CDialogEx)
	ON_MESSAGE(UM_MAIN_RF_MESSAGE, CRechargeProcessorDlg::Main_RF_Message)//���ο��� RF���� �޽��� �۽������� ���� �̺�Ʈó��
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CARDTAG, &CRechargeProcessorDlg::OnBnClickedButtonCardtag)
	ON_BN_CLICKED(IDC_BUTTON_NO_COGNIZE, &CRechargeProcessorDlg::OnBnClickedButtonNoCognize)
	ON_BN_CLICKED(IDC_BUTTON_HANARO, &CRechargeProcessorDlg::OnBnClickedButtonHanaro)
	ON_BN_CLICKED(IDC_BUTTON_MYBI, &CRechargeProcessorDlg::OnBnClickedButtonMybi)
	ON_BN_CLICKED(IDC_BUTTON_CASHBEE, &CRechargeProcessorDlg::OnBnClickedButtonCashbee)
	ON_BN_CLICKED(IDC_BUTTON_TMONEY, &CRechargeProcessorDlg::OnBnClickedButtonTmoney)
END_MESSAGE_MAP()

// CRechargeProcessorDlg �޽��� ó����

BOOL CRechargeProcessorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
	
	m_logwriter->Log_Make(_T("RechargeProcessor"), _T("11_Recharge"));//�ش� ���� �� ���� ����
	
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CRechargeProcessorDlg::OnPaint()
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
HCURSOR CRechargeProcessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

afx_msg LRESULT CRechargeProcessorDlg::Main_RF_Message(WPARAM wParam, LPARAM lParam)//���ο��� RF���� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
{
	switch (wParam)//wParam ���� ����
	{
		case main : //ī�� ���λ���
			card_disbled();//���ο��� ī�� ��Ȱ��ȭ
			break;
		case card_wait : //ī�� ������
			m_button_cardtag.EnableWindow();//ī�� �±� Ȱ��ȭ
			break;
		case card_processing : 
			break;
		default:
			break;
	}
	return 0;
}

void CRechargeProcessorDlg::send_card_tag()//���ο��� ī�� �±� ������
{
	if(m_logwriter->MAIN_HWND==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile("RF -> ���� �޽��� �۽ſϷ�(ī�庸��_�ǵ���)");//LOG ���
		::SendMessage(m_logwriter->MAIN_HWND, UM_RF_MAIN_MESSAGE, card_processing, 0);//���ο��� �޼���(�̹���->����) ���� //Wparam : 2 (ī�� ����)
	}
}

void CRechargeProcessorDlg::send_card_result(int CardNum)//���ο��� ī�� ��� ������
{
	if(m_logwriter->MAIN_HWND==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile("RF -> ���� �޽��� �۽ſϷ�(ī�庸��_�ݾ׼���)");//LOG ���
		::SendMessage(m_logwriter->MAIN_HWND, UM_RF_MAIN_MESSAGE, recharge, CardNum);//���ο��� �޼���(�̹���->����) ���� //Iparam : 1(�ϳ���) 2(���̺�) 3(ĳ�ú�) 4(Ƽ�Ӵ�)
	}
}

void CRechargeProcessorDlg::card_disbled()//���ο��� ī�� ��Ȱ��ȭ
{
	m_logwriter->WriteLogFile(_T("card_disbled"));
	if(m_button_cardtag.EnableWindow(FALSE) + m_button_no_cognize.EnableWindow(FALSE) + m_button_hanaro.EnableWindow(FALSE) +
	   m_button_mybi.EnableWindow(FALSE) + m_button_cashbee.EnableWindow(FALSE) + m_button_Tmoney.EnableWindow(FALSE) == TRUE){//�Ѱ��� Ȱ��ȭ�̸�
		m_logwriter->now_write_log.Format(_T("���ν�, �ϳ���, ���̺�, ĳ�ú�, Ƽ�Ӵ� ��Ȱ��ȭ ����"));
	}
	else{
		m_logwriter->now_write_log.Format(_T("���ν�, �ϳ���, ���̺�, ĳ�ú�, Ƽ�Ӵ� ��Ȱ��ȭ ����!"));
	}
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
}

void CRechargeProcessorDlg::OnBnClickedButtonCardtag()//ī�� �±� ��ư ������ ��
{
	m_logwriter->WriteLogFile(_T("Cardtag ��ư Ŭ��"));
	if(!m_button_no_cognize.EnableWindow() + !m_button_hanaro.EnableWindow() + !m_button_mybi.EnableWindow() + !m_button_cashbee.EnableWindow() + !m_button_Tmoney.EnableWindow() == TRUE){//�Ѱ��� ��Ȱ��ȭ�̸�
		m_logwriter->now_write_log.Format(_T("���ν�, �ϳ���, ���̺�, ĳ�ú�, Ƽ�Ӵ� Ȱ��ȭ ����"));
	}
	else{
		m_logwriter->now_write_log.Format(_T("���ν�, �ϳ���, ���̺�, ĳ�ú�, Ƽ�Ӵ� Ȱ��ȭ ����!"));
		send_card_tag();
	}
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CRechargeProcessorDlg::OnBnClickedButtonNoCognize()//�±��� ī�尡 ���ν� ī���� ��
{
	send_card_result(card_none);//���ο��� ī�� ��� ������
	m_logwriter->WriteLogFile(_T("NoCognize ��ư Ŭ��"));
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CRechargeProcessorDlg::OnBnClickedButtonHanaro()//�±��� ī�尡 �ϳ��� ī���� ��
{
	send_card_result(hanaro);//���ο��� ī�� ��� ������
	m_logwriter->WriteLogFile(_T("Hanaro ��ư Ŭ��"));
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CRechargeProcessorDlg::OnBnClickedButtonMybi()//�±��� ī�尡 ���̺� ī���� ��
{
	send_card_result(mybe);//���ο��� ī�� ��� ������
	m_logwriter->WriteLogFile(_T("Mybi ��ư Ŭ��"));
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CRechargeProcessorDlg::OnBnClickedButtonCashbee()//�±��� ī�尡 ĳ�ú� ī���� ��
{
	send_card_result(cashbbe);//���ο��� ī�� ��� ������
	m_logwriter->WriteLogFile(_T("Cashbee ��ư Ŭ��"));
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CRechargeProcessorDlg::OnBnClickedButtonTmoney()//�±��� ī�尡 Ƽ�Ӵ� ī���� ��
{
	send_card_result(Tmoney);//���ο��� ī�� ��� ������
	m_logwriter->WriteLogFile(_T("Tmoney ��ư Ŭ��"));
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
