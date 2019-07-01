
// CoinProcessorDlg.h : ��� ����
//

#pragma once

#include "LogWriter.h"
#include "CoinMMap.h"

// CCoinProcessorDlg ��ȭ ����
class CCoinProcessorDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCoinProcessorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COINPROCESSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	afx_msg void OnDestroy();

//����
	CLogWriter *m_logwriter;//�α� �����
	CCoinMMap *m_coinmmap;//���� MMap
	
	CButton m_coin_inset10;//10�� �Է� ��ư
	CButton m_coin_inset50;//50�� �Է� ��ư
	CButton m_coin_inset100;//100�� �Է� ��ư
	CButton m_coin_inset500;//500�� �Է� ��ư

//�Լ�
	int Coin_Shutter_Open(int receive_state);//���� ���� ���� ����
	void Coin_Shutter_Close();//���� ���� �ݱ� ����
	void Coin_Insert_Fare(int fare);//���� ����

	afx_msg void OnBnClickedButtonInsert500();//500���� ���� ��ư ��������
	afx_msg void OnBnClickedButtonInsert100();//100���� ���� ��ư ��������
	afx_msg void OnBnClickedButtonInsert50(); //50���� ���� ��ư ��������
	afx_msg void OnBnClickedButtonInsert10(); //10���� ���� ��ư ��������

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg LRESULT Main_COIN_Message(WPARAM wParam, LPARAM lParam);//���ο��� �������� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
