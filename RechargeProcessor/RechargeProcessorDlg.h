
// RechargeProcessorDlg.h : ��� ����
//

#include "LogWriter.h"
#include "RechargeMMap.h"
#pragma once


// CRechargeProcessorDlg ��ȭ ����
class CRechargeProcessorDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CRechargeProcessorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_RECHARGEPROCESSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

//����
	CButton m_button_cardtag;//ī�� �±� ��ư
	CButton m_button_no_cognize;//���ν� ī�� �±� ��ư
	CButton m_button_hanaro;//�ϳ��� ī�� �±� ��ư
	CButton m_button_mybi;//���̺� ī�� �±� ��ư
	CButton m_button_cashbee;//ĳ�ú� ī�� �±� ��ư
	CButton m_button_Tmoney;//Ƽ�Ӵ� ī�� �±� ��ư

	CLogWriter *m_logwriter;//�α� �����
	CRechargeMMap *m_rechargemmap;//�ŷ����� MMap

//�Լ�	
	void send_card_tag();				  //���ο��� ī�� �±� ������
	void send_card_result(int CardNum);			  //���ο��� ī�� ��� ������
	void card_disbled();					//���ο��� ī���Ȱ��ȭ
	afx_msg void OnBnClickedButtonCardtag();  //ī�� �±� ��ư ������ ��
	afx_msg void OnBnClickedButtonNoCognize();//�±��� ī�尡 ���ν� ī���� ��
	afx_msg void OnBnClickedButtonHanaro();   //�±��� ī�尡 �ϳ��� ī���� ��
	afx_msg void OnBnClickedButtonMybi();     //�±��� ī�尡 ���̺� ī���� ��
	afx_msg void OnBnClickedButtonCashbee();  //�±��� ī�尡 ĳ�ú� ī���� ��
	afx_msg void OnBnClickedButtonTmoney();   //�±��� ī�尡 Ƽ�Ӵ� ī���� ��
	
// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT Main_RF_Message(WPARAM wParam, LPARAM lParam);//���ο��� RF���� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
	DECLARE_MESSAGE_MAP()
};
