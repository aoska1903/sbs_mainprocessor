
// MainProcessorDlg.h : ��� ����
//

#pragma once
#include "LogWriter.h"
#include "MainMuduleControl.h"
#include "MainMMap.h"
#include "afxwin.h"

// CMainProcessorDlg ��ȭ ����
class CMainProcessorDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMainProcessorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAINPROCESSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

//����
	CLogWriter *m_logwriter;//�α� �����
	CMainMuduleControl *m_mainmudulecontrol;//��� ������
	CMainMMap *m_mainmmap;//�� ������
	BOOL Bill_Shutter_Open;//���� ���� ���� ����
	BOOL Coin_Shutter_Open;//���� ���� ���� ����
//�Լ�
	void Processor_Run();//�ٸ� ���μ��� �����Ű��
	void Processor_State_Change(int change_state);//�ٸ� ���μ��� ��û�� ���� ���μ��� ���� ����
	void Card_Wait();//RF���� ī�� �±��Ҽ��ֵ��� Ȱ��ȭ ������
	void Shutter_Open(int change_state);//�ش� �ŷ� �ݾ� ������ ���� ����, ���󿡰� ���� ���� ����
	void Shutter_Clsoe();//����, ���󿡰� ���� �ݱ� ����
	void Card_Disabled();//ī�� ��Ȱ��ȭ ����
	void Bill_Shutter_Open_Result(int Shutter_Result);//���� ���� ���� ��� 
	void Coin_Shutter_Open_Result(int Shutter_Result);//���� ���� ���� ���
	INT Insert_Bill(int fare);//��������
	INT Insert_Coin(int fare);//��������
	void Trasation_Cancel(int now_image_state);//�ŷ��� ��� ������ �� ���Ա�0 ����, �ŷ����� �ŷ�X���·� ����
	void Write_CardInfo(int kind_of_card);  //RF���� ���� ī�� ��� MM�� �����
// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg LRESULT COIN_Main_Message(WPARAM wParam, LPARAM lParam);//�������� ���ο��� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
	afx_msg LRESULT BILL_Main_Message(WPARAM wParam, LPARAM lParam);//���󿡼� ���ο��� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
	afx_msg LRESULT IMAGE_Main_Message(WPARAM wParam, LPARAM lParam);//�̹������α׷����� ���ο��� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
	afx_msg LRESULT RF_Main_Message(WPARAM wParam, LPARAM lParam);//�������α׷����� ���ο��� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};
