
// BillProcessorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "BillProcessor.h"
#include "BillProcessorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBillProcessorDlg ��ȭ ����

CBillProcessorDlg::CBillProcessorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBillProcessorDlg::IDD, pParent)
	, m_billmmap(new CBillMMap())//������ġ �޸𸮸� ����
	, m_logwriter(new CLogWriter())
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBillProcessorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_INSERT_1000 , m_bill_inset1000);
	DDX_Control(pDX, IDC_BUTTON_INSERT_5000 , m_bill_inset5000);
	DDX_Control(pDX, IDC_BUTTON_INSERT_10000, m_bill_inset10000);
	DDX_Control(pDX, IDC_BUTTON_INSERT_50000, m_bill_inset50000);
}

BEGIN_MESSAGE_MAP(CBillProcessorDlg, CDialogEx)
	ON_MESSAGE(UM_MAIN_BILL_MESSAGE, CBillProcessorDlg::Main_BILL_Message)//���ο��� ���󿡰� �޽��� �۽������� ���� �̺�Ʈó��
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSERT_1000, &CBillProcessorDlg::OnBnClickedButtonInsert1000)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_5000, &CBillProcessorDlg::OnBnClickedButtonInsert5000)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_10000, &CBillProcessorDlg::OnBnClickedButtonInsert10000)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_50000, &CBillProcessorDlg::OnBnClickedButtonInsert50000)
END_MESSAGE_MAP()


// CBillProcessorDlg �޽��� ó����

BOOL CBillProcessorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	m_logwriter->Log_Make(_T("BillProcessor"), _T("06_Bill"));//�ش� ���� �� ���� ����
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CBillProcessorDlg::OnPaint()
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
HCURSOR CBillProcessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

afx_msg LRESULT CBillProcessorDlg::Main_BILL_Message(WPARAM wParam, LPARAM lParam)//���ο��� ���󿡰� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
{
	switch (wParam)//wParam ���� ����
	{
		case main:
			BIll_Shutter_Close();//���� ���� �ݱ� ����
			break;
		case cardsale_insert : 
		case recharge_insert : 
			Bill_Shutter_Open(wParam);//���� ���� ���� ����
			break;
		default:
			break;
	}
	return 0;
}

int CBillProcessorDlg::Bill_Shutter_Open(int receive_state)//���� ���� ���� ����
{
	m_logwriter->now_write_log.Format(_T("�������� ���� [%s]�� ���� ���� ���� ��� ����"), Now_State_Contents[receive_state]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	int shuttur_count = 0;//���� �������� 
	if(!m_bill_inset1000.EnableWindow() + !m_bill_inset5000.EnableWindow() + !m_bill_inset10000.EnableWindow() + !m_bill_inset50000.EnableWindow() == TRUE ){//���� �� Ȱ��ȭ ������ ���
		m_logwriter->now_write_log.Format(_T("[%s]�� ���� ���� ���� ����"), Now_State_Contents[receive_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		if(m_logwriter->MAIN_HWND==NULL){//�����ڵ��� �������� �ʴ´ٸ�
			m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
		}
		else{
			m_logwriter->now_write_log.Format(_T("���ο��� [%s]�� ���� ���� ���� ���� �޽��� �۽�"), Now_State_Contents[receive_state]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);
			::SendMessage(m_logwriter->MAIN_HWND, UM_BILL_MAIN_MESSAGE, receive_state, 0);//�������α׷����� �޼���(����->����) ����//Iparm 1(����) 0(����)
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
		::SendMessage(m_logwriter->MAIN_HWND, UM_BILL_MAIN_MESSAGE, receive_state, 1);//�������α׷����� �޼���(����->����) ����//Iparm 1(����) 0(����)
	}
	return 1;
}

void CBillProcessorDlg::BIll_Shutter_Close()//���� ���� �ݱ� ����
{
	m_logwriter->WriteLogFile(_T("BIll_Shutter_Close"));
	if(m_bill_inset1000.EnableWindow(FALSE) + m_bill_inset5000.EnableWindow(FALSE) + m_bill_inset10000.EnableWindow(FALSE) + m_bill_inset50000.EnableWindow(FALSE) == TRUE){//�Ѱ��� Ȱ��ȭ�̸�
		m_logwriter->now_write_log.Format(_T("1000��, 5000��, 10000��, 50000�� ��Ȱ��ȭ ����"));
	}
	else{
		m_logwriter->now_write_log.Format(_T("1000��, 5000��, 10000��, 50000�� ��Ȱ��ȭ ����!"));
	}
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
}

void CBillProcessorDlg::Bill_Insert_Fare(int fare)//���� ����
{
	if(m_logwriter->MAIN_HWND==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_logwriter->MAIN_HWND �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->now_write_log.Format(_T("���� ���� %d��"), fare);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);
		::SendMessage(m_logwriter->MAIN_HWND, UM_BILL_MAIN_MESSAGE, m_billmmap->MMap_Now_State(), fare);//�������α׷����� �޼���(����->����) ����//Iparm 1(����) 0(����)
	}
}

void CBillProcessorDlg::OnBnClickedButtonInsert1000()//1000���� ���� ��ư ��������
{
	m_logwriter->WriteLogFile(_T("���� 1000�� ��ư Ŭ��"));
	Bill_Insert_Fare(1000);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CBillProcessorDlg::OnBnClickedButtonInsert5000()//5000���� ���� ��ư ��������
{
	m_logwriter->WriteLogFile(_T("���� 5000�� ��ư Ŭ��"));
	Bill_Insert_Fare(5000);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CBillProcessorDlg::OnBnClickedButtonInsert10000()//10000���� ���� ��ư ��������
{
	m_logwriter->WriteLogFile(_T("���� 10000�� ��ư Ŭ��"));
	Bill_Insert_Fare(10000);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CBillProcessorDlg::OnBnClickedButtonInsert50000()//50000���� ���� ��ư ��������
{
	m_logwriter->WriteLogFile(_T("���� 50000�� ��ư Ŭ��"));
	Bill_Insert_Fare(50000);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
