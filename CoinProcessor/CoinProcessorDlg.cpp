
// CoinProcessorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "CoinProcessor.h"
#include "CoinProcessorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCoinProcessorDlg ��ȭ ����

CCoinProcessorDlg::CCoinProcessorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCoinProcessorDlg::IDD, pParent)
	, m_coinmmap(new CCoinMMap())//������ġ �޸𸮸� ����
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
	ON_MESSAGE(UM_MAIN_COIN_MESSAGE, CCoinProcessorDlg::Main_COIN_Message)//���ο��� �������� �޽��� �۽������� ���� �̺�Ʈó��
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT_500, &CCoinProcessorDlg::OnBnClickedButtonInsert500)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_100, &CCoinProcessorDlg::OnBnClickedButtonInsert100)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_50, &CCoinProcessorDlg::OnBnClickedButtonInsert50)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_10, &CCoinProcessorDlg::OnBnClickedButtonInsert10)
END_MESSAGE_MAP()


// CCoinProcessorDlg �޽��� ó����

BOOL CCoinProcessorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	m_logwriter->Log_Make(_T("CoinProcessor"), _T("04_Coin"));//�ش� ���� �� ���� ����
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCoinProcessorDlg::OnPaint()
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
HCURSOR CCoinProcessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

afx_msg LRESULT CCoinProcessorDlg::Main_COIN_Message(WPARAM wParam, LPARAM lParam)//���ο��� �������� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
{
	switch (wParam)//wParam ���� ����
	{
		case main:
			Coin_Shutter_Close();//���� ���� �ݱ� ����
			break;
		case cardsale_insert : 
		case recharge_insert : 
			Coin_Shutter_Open(wParam);//���� ���� ���� ����
			break;
		default:
			break;
	}
	return 0;
}

int CCoinProcessorDlg::Coin_Shutter_Open(int receive_state)//���� ���� ���� ����
{
	m_logwriter->now_write_log.Format(_T("�������� ���� [%s]�� ���� ���� ���� ��� ����"), Now_State_Contents[receive_state]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	int shuttur_count = 0;//���� �������� 
	if(!m_coin_inset10.EnableWindow() + !m_coin_inset50.EnableWindow() + !m_coin_inset100.EnableWindow() + !m_coin_inset500.EnableWindow() == TRUE ){
		m_logwriter->now_write_log.Format(_T("[%s]�� ���� ���� ���� ����"), Now_State_Contents[receive_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		if(m_logwriter->MAIN_HWND==NULL){//�����ڵ��� �������� �ʴ´ٸ�
			m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
		}
		else{
			m_logwriter->now_write_log.Format(_T("���ο��� [%s]�� ���� ���� ���� ���� �޽��� �۽�"), Now_State_Contents[receive_state]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);
			::SendMessage(m_logwriter->MAIN_HWND, UM_COIN_MAIN_MESSAGE, receive_state, 0);//�������α׷����� �޼���(����->����) ����//Iparm 1(����) 0(����)
		}
		return 0;//��� �� ��ư�̶� ��Ȱ��ȭ �Ǿ����� ��
	}
	m_logwriter->now_write_log.Format(_T("[%s]�� ���� ���� ���� ����"), Now_State_Contents[receive_state]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);
	if(m_logwriter->MAIN_HWND==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->now_write_log.Format(_T("���ο��� [%s]�� ���� ���� ���� �Ϸ� �޽��� �۽�"), Now_State_Contents[receive_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		::SendMessage(m_logwriter->MAIN_HWND, UM_COIN_MAIN_MESSAGE, receive_state, 1);//�������α׷����� �޼���(����->����) ����//Iparm 1(����) 0(����)
	}
	return 1;
}

void CCoinProcessorDlg::Coin_Shutter_Close()//���� ���� �ݱ� ����
{
	m_logwriter->WriteLogFile(_T("Coin_Shutter_Close"));
	if(m_coin_inset10.EnableWindow(FALSE) + m_coin_inset50.EnableWindow(FALSE) + m_coin_inset100.EnableWindow(FALSE) + m_coin_inset500.EnableWindow(FALSE) == TRUE){//�Ѱ��� Ȱ��ȭ�̸�
		m_logwriter->now_write_log.Format(_T("10��, 50��, 100��, 500�� ��Ȱ��ȭ ����"));
	}
	else{
		m_logwriter->now_write_log.Format(_T("10��, 50��, 100��, 500�� ��Ȱ��ȭ ����!"));
	}
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
}

void CCoinProcessorDlg::Coin_Insert_Fare(int fare)//���� ����
{
	if(m_logwriter->MAIN_HWND==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->now_write_log.Format(_T("���� ���� %d��"), fare);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		::SendMessage(m_logwriter->MAIN_HWND, UM_COIN_MAIN_MESSAGE, m_coinmmap->MMap_Now_State(), fare);//�������α׷����� �޼���(����->����) ����//Iparm 1(����) 0(����)
	}
}

void CCoinProcessorDlg::OnBnClickedButtonInsert500()//500���� ���� ��ư ��������
{					
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_logwriter->WriteLogFile(_T("���� 500�� ��ư Ŭ��"));
	Coin_Insert_Fare(500);//���� ����
}


void CCoinProcessorDlg::OnBnClickedButtonInsert100()//100���� ���� ��ư ��������
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_logwriter->WriteLogFile(_T("���� 100�� ��ư Ŭ��"));
	Coin_Insert_Fare(100);//���� ����
}


void CCoinProcessorDlg::OnBnClickedButtonInsert50()//50���� ���� ��ư ��������
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_logwriter->WriteLogFile(_T("���� 50�� ��ư Ŭ��"));
	Coin_Insert_Fare(50);//���� ����
}


void CCoinProcessorDlg::OnBnClickedButtonInsert10()//10���� ���� ��ư ��������
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_logwriter->WriteLogFile(_T("���� 10�� ��ư Ŭ��"));
	Coin_Insert_Fare(10);//���� ����
}
