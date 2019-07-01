
// MainProcessorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MainProcessor.h"
#include "MainProcessorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainProcessorDlg ��ȭ ����

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
	ON_MESSAGE(UM_COIN_MAIN_MESSAGE, CMainProcessorDlg::COIN_Main_Message)//�������� ���ο��� �޽��� �۽������� ���� �̺�Ʈó��
	ON_MESSAGE(UM_BILL_MAIN_MESSAGE, CMainProcessorDlg::BILL_Main_Message)//���󿡼� ���ο��� �޽��� �۽������� ���� �̺�Ʈó��
	ON_MESSAGE(UM_IMAGE_MAIN_MESSAGE, CMainProcessorDlg::IMAGE_Main_Message)//�̹������α׷����� ���ο��� �޽��� �۽������� ���� �̺�Ʈó��
	ON_MESSAGE(UM_RF_MAIN_MESSAGE, CMainProcessorDlg::RF_Main_Message)//�������α׷����� ���ο��� �޽��� �۽������� ���� �̺�Ʈó��
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMainProcessorDlg �޽��� ó����

BOOL CMainProcessorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_logwriter->Log_Make(_T("MainProcessor"), _T("01_Main"));//�ش� ���� �� ���� ����

	Processor_Run();//�ٸ� ���μ��� �����Ű��
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMainProcessorDlg::OnPaint()
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
HCURSOR CMainProcessorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMainProcessorDlg::Processor_Run()//�ٸ� ���μ��� �����Ű��
{
	m_mainmudulecontrol->moduleprocess_run();//�ٸ� ��� ���μ��� ����
}

void CMainProcessorDlg::Processor_State_Change(int change_state)//�ٸ� ���μ��� ��û�� ���� ���μ��� ���� ����
{
	if(m_mainmmap->state_change(change_state) == 1){//p_Data now_state�� �Ű����������� ���� ������ ���
		m_logwriter->now_write_log.Format(_T("T_RECHARGE_DATA [%s] ���� ���� ����"), Now_State_Contents[change_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
	else{
		m_logwriter->now_write_log.Format(_T("T_RECHARGE_DATA [%s] ���� ���� ����..."), Now_State_Contents[change_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
	if(m_mainmudulecontrol->module_hwnd[ImageProcessor]==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[ImageProcessor] �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->now_write_log.Format(_T("�̹��� ���μ������� T_RECHARGE_DATA [%s] ���� ���� �Ϸ� �� ȭ�� ���� ��û �޽��� �۽� �Ϸ�"), Now_State_Contents[change_state]);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		::SendMessage(m_mainmudulecontrol->module_hwnd[ImageProcessor], UM_MAIN_IMAGE_MESSAGE, change_state, 0);//�̹������α׷����� �޼���(����->�̹���) ����
	}
}

void CMainProcessorDlg::Card_Wait()//RF���� ī�� �±��Ҽ��ֵ��� Ȱ��ȭ ������
{
	if(m_mainmudulecontrol->module_hwnd[RechargeProcessor]==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[RechargeProcessor] �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile(_T("RF ���μ������� Ȱ��ȭ �۽� �Ϸ�"));//LOG ���
		::SendMessage(m_mainmudulecontrol->module_hwnd[RechargeProcessor], UM_MAIN_RF_MESSAGE, card_wait, 0);//RF ���α׷����� �޼���(����->RF) ����
	}
}

void CMainProcessorDlg::Shutter_Open(int change_state)//�ݾ� ������ ���� ����, ���󿡰� ���� ���� ����
{
	if(m_mainmudulecontrol->module_hwnd[BillProcessor]==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[BillProcessor] �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile(_T("���� ���μ������� ���� ���� ��� �۽� �Ϸ�"));//LOG ���
		::SendMessage(m_mainmudulecontrol->module_hwnd[BillProcessor], UM_MAIN_BILL_MESSAGE, change_state, 0);//���� ���α׷����� �޼���(����->����) ����
	}
	if(m_mainmudulecontrol->module_hwnd[CoinProcessor]==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[CoinProcessor] �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile(_T("���� ���μ������� ���� ���� ��� �۽� �Ϸ�"));//LOG ���
		::SendMessage(m_mainmudulecontrol->module_hwnd[CoinProcessor], UM_MAIN_COIN_MESSAGE, change_state, 0);//���� ���α׷����� �޼���(����->����) ����
	}
}

void CMainProcessorDlg::Shutter_Clsoe()//����, ���󿡰� ���� �ݱ� ����
{
	if(m_mainmudulecontrol->module_hwnd[BillProcessor]==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[BillProcessor] �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile(_T("���� ���μ������� ���� �ݱ� ��� �۽� �Ϸ�"));//LOG ���
		::SendMessage(m_mainmudulecontrol->module_hwnd[BillProcessor], UM_MAIN_BILL_MESSAGE, main, 0);//���� ���α׷����� �޼���(����->����) ����
	}
	if(m_mainmudulecontrol->module_hwnd[CoinProcessor]==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[CoinProcessor] �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile(_T("���� ���μ������� ���� �ݱ� ��� �۽� �Ϸ�"));//LOG ���
		::SendMessage(m_mainmudulecontrol->module_hwnd[CoinProcessor], UM_MAIN_COIN_MESSAGE, main, 0);//���� ���α׷����� �޼���(����->����) ����
	}
}

void CMainProcessorDlg::Card_Disabled()//ī�� ��Ȱ��ȭ ����
{
	if(m_mainmudulecontrol->module_hwnd[RechargeProcessor]==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[RechargeProcessor] �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->WriteLogFile(_T("RF ���μ������� ��Ȱ��ȭ ��� �۽� �Ϸ�"));//LOG ���
		::SendMessage(m_mainmudulecontrol->module_hwnd[RechargeProcessor], UM_MAIN_RF_MESSAGE, main, 0);//RF ���α׷����� �޼���(����->RF) ����
	}
}

void CMainProcessorDlg::Bill_Shutter_Open_Result(int Shutter_Result)//���� ���� ���� ��� 
{
	Bill_Shutter_Open = Shutter_Result;//���� ���� ���� ���ο� ���� ���� �÷��� ����
	m_logwriter->now_write_log.Format(_T("���� ���μ������� ���� ���� ��� ���� �Ϸ� (��� : %d)"), Bill_Shutter_Open);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	if(Coin_Shutter_Open&&Bill_Shutter_Open){//���ε� ���� ������
		m_logwriter->now_write_log.Format(_T("p_data->Transtion_Ready : %d (1.�غ�Ϸ� 0.�غ�̿Ϸ�)"), m_mainmmap->MMap_Transtion_Ready_Change(TRUE));//MMAp������ TRUE��
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
}

void CMainProcessorDlg::Coin_Shutter_Open_Result(int Shutter_Result)//���� ���� ���� ���
{
	Coin_Shutter_Open = Shutter_Result;//���� ���� ���� ���ο� ���� ���� �÷��� ����
	m_logwriter->now_write_log.Format(_T("���� ���μ������� ���� ���� ��� ���� �Ϸ� (��� : %d)"), Coin_Shutter_Open);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	if(Coin_Shutter_Open&&Bill_Shutter_Open){//���� ���� ������
		m_logwriter->now_write_log.Format(_T("p_data->Transtion_Ready : %d (1.�غ�Ϸ� 0.�غ�̿Ϸ�)"), m_mainmmap->MMap_Transtion_Ready_Change(TRUE));//MMAp������ TRUE��
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	}
}

INT CMainProcessorDlg::Insert_Bill(int fare)//��������
{
	m_mainmmap->insert_bill(fare);//T_RECHARGE_DATA ����
	int now_image_state = m_mainmmap->MMap_Now_State();//������°�
	if(m_mainmudulecontrol->module_hwnd[ImageProcessor]==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[ImageProcessor] �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->now_write_log.Format(_T("�̹��� ���μ������� T_RECHARGE_DATA ���� ���� [%d] �۽� �Ϸ�"), fare);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		::SendMessage(m_mainmudulecontrol->module_hwnd[ImageProcessor], UM_MAIN_IMAGE_MESSAGE, now_image_state, fare);//�̹������α׷����� �޼���(����->�̹���) ����
	}
	return 0;
}

INT CMainProcessorDlg::Insert_Coin(int fare)//��������
{
	m_mainmmap->insert_coin(fare);//T_RECHARGE_DATA ����

	int now_image_state = m_mainmmap->MMap_Now_State();//������°�
	if(m_mainmudulecontrol->module_hwnd[ImageProcessor]==NULL){//�����ڵ��� �������� �ʴ´ٸ�
		m_logwriter->WriteLogFile("m_mainmudulecontrol->module_hwnd[ImageProcessor] �������� �ʾƼ� �޽��� �۽��� ���߽��ϴ�.");//LOG ���
	}
	else{
		m_logwriter->now_write_log.Format(_T("�̹��� ���μ������� T_RECHARGE_DATA ���� ���� [%d] �۽� �Ϸ�"), fare);
		m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
		::SendMessage(m_mainmudulecontrol->module_hwnd[ImageProcessor], UM_MAIN_IMAGE_MESSAGE, now_image_state, fare);//�̹������α׷����� �޼���(����->�̹���) ����
	}
	return 0;
}

void CMainProcessorDlg::Trasation_Cancel(int now_image_state)//�ŷ��� ��� ������ �� ���Ա�0 ����, �ŷ����� �ŷ�X���·� ����
{
	if(now_image_state >= recharge){//������°� ���� �������϶�	
		Card_Disabled();//ī�� ��Ȱ��ȭ ����
	}
	Shutter_Clsoe();//�ش� �ŷ� �ݾ� ������ ���� ����, ���󿡰� ���� �ݱ� ����
	m_mainmmap->init_insert(now_image_state);//���Ա� �ʱ�ȭ �Լ�
	m_logwriter->now_write_log.Format(_T("�ݾ� ���� ���� : %d (1.�غ�Ϸ� 2.�غ�̿Ϸ�)"), m_mainmmap->MMap_Transtion_Ready_Change(Transation_None));//MMAp�ŷ����� Transation_None��
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	Coin_Shutter_Open = 0;
	Bill_Shutter_Open = 0; 
}

void CMainProcessorDlg::Write_CardInfo(int kind_of_card)//RF���� ���� ī�� ��� MM�� �����
{
	m_logwriter->now_write_log.Format(_T("%s ī�� �ν�"), Traffic_Card_Name[m_mainmmap->MMap_Write_CardInfo(kind_of_card)]);//MMAp ī�� ���� ����
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
}

void CMainProcessorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_mainmudulecontrol->moduleprocess_kill();//��� ���α׷� ����
	m_logwriter->WriteLogFile(_T("Main ����"));//LOG ���
	delete m_mainmmap;//�Ҹ�
	m_mainmmap = NULL;//�Ҹ�
	delete m_mainmudulecontrol;//�Ҹ�
	m_mainmudulecontrol = NULL;//�Ҹ�
	if ((m_mainmudulecontrol == NULL) &&
		(m_mainmmap == NULL)){
		m_logwriter->WriteLogFile(_T("m_mainmudulecontrol, m_mainmmap �Ҹ� �Ϸ� �� m_logwriter�� �Ҹ꿹��"));
	}
	else{
		m_logwriter->WriteLogFile(_T("m_mainmudulecontrol, m_mainmmap �Ҹ� ���� �� m_logwriter �Ҹ� �õ� "));
	}
	delete m_logwriter;//�Ҹ�
	m_logwriter = NULL;//�Ҹ�
	if(m_logwriter!=NULL){
		AfxMessageBox(_T("m_logwriter�Ҹ� ����(Main)"));
	}
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

afx_msg LRESULT CMainProcessorDlg::COIN_Main_Message(WPARAM wParam, LPARAM lParam)//�������� ���ο��� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
{
	switch (wParam)//���� ���°�������
	{
		case cardsale_insert :
		case recharge_insert :
			if(m_mainmmap->MMap_Check_Transtion_Ready() == TRUE){//�ŷ� �غ� ������ ��
				Insert_Coin(lParam);//��������//lParam ���� �ݾ�
			}
			else{//�ŷ� �غ� ���� �ƴ� ��
				Coin_Shutter_Open_Result(lParam);//���� ���� ���� ���ο� ���� ���� �÷��� ����
			}
			break;
		default:
			break;
	}
	return 0;
}

afx_msg LRESULT CMainProcessorDlg::BILL_Main_Message(WPARAM wParam, LPARAM lParam)//���󿡼� ���ο��� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
{
	switch (wParam)//���� ���°�������
	{
		case cardsale_insert :
		case recharge_insert :
			if(m_mainmmap->MMap_Check_Transtion_Ready() == TRUE){//�ŷ� �غ� ������ ��
				Insert_Bill(lParam);//��������//lParam ���� �ݾ�
			}
			else{//�ŷ� �غ� ���� �ƴ� ��
				Bill_Shutter_Open_Result(lParam);//���� ���� ���� ���ο� ���� ���� �÷��� ����
			}
			break;
		default:
			break;
	}
	return 0;
}

afx_msg LRESULT CMainProcessorDlg::IMAGE_Main_Message(WPARAM wParam, LPARAM lParam)//�̹������α׷����� ���ο��� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
{
	m_logwriter->now_write_log.Format(_T("�̹��� ���μ������� T_RECHARGE_DATA [%s] ���� ���� ��û!"), Now_State_Contents[wParam]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���

	int image_state = m_mainmmap->MMap_Now_State();//�̹������� �۽��Ҷ� ���°�
	m_logwriter->now_write_log.Format(_T("�� T_RECHARGE_DATA [%s] ����(p_data->Now_State)"), Now_State_Contents[image_state]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���
	switch (wParam)//���� ���°�������
	{
		case main://���� �ƴ� ���¿��� ��� ��ư�� �����Ͽ�����
			Trasation_Cancel(image_state);//�ŷ��� ��� ������ �� ���Ա�0 ����, �ŷ����� �ŷ�X���·� ����
			//���Աݾ� �ʱ�ȭ�ϴ��Լ�
			Processor_State_Change(main);
			break;
		case cardsale :
			Processor_State_Change(cardsale);
			break;
		case card_wait ://ī�� ��� ����
			Processor_State_Change(card_wait);
			Card_Wait();//RF���� ī�� �±��Ҽ��ֵ��� Ȱ��ȭ ������
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

afx_msg LRESULT CMainProcessorDlg::RF_Main_Message(WPARAM wParam, LPARAM lParam)//�������α׷����� ���ο��� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
{
	m_logwriter->now_write_log.Format(_T("RF ���μ������� T_RECHARGE_DATA [%s] ���� ���� ��û!"), Now_State_Contents[wParam]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���

	int image_state = m_mainmmap->MMap_Now_State();//�̹������� �۽��Ҷ� ���°�
	m_logwriter->now_write_log.Format(_T("�� T_RECHARGE_DATA [%s] ����(p_data->Now_State)"), Now_State_Contents[image_state]);
	m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG ���

	switch (wParam)//���� ���°�������
	{
		case card_processing ://ī�� �ν� ����
			Processor_State_Change(card_processing);
			break;
		case recharge ://ī�� ���� �ݾ� ����
			Write_CardInfo(lParam);//RF���� ���� ī�� ��� MM�� �����
			Processor_State_Change(recharge);
			break;
		default:
			break;
	}
	return 0;
}