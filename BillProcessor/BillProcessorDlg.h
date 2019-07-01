
// BillProcessorDlg.h : ��� ����
//

#include "LogWriter.h"
#include "BillMMap.h"
#pragma once

// CBillProcessorDlg ��ȭ ����
class CBillProcessorDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CBillProcessorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BILLPROCESSOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	
//����
	CLogWriter *m_logwriter;//�α� �����
	CBillMMap *m_billmmap;//���� MMap

	CButton m_bill_inset1000;//1000�� �Է� ��ư
	CButton m_bill_inset5000;//5000�� �Է� ��ư
	CButton m_bill_inset10000;//10000�� �Է� ��ư
	CButton m_bill_inset50000;//50000�� �Է� ��ư

//�Լ�
	int Bill_Shutter_Open(int receive_state);//���� ���� ���� ����
	void BIll_Shutter_Close();//���� ���� �ݱ� ����
	void Bill_Insert_Fare(int fare);//���� ����

	afx_msg void OnBnClickedButtonInsert1000();//1000���� ���� ��ư ��������
	afx_msg void OnBnClickedButtonInsert5000();//5000���� ���� ��ư ��������
	afx_msg void OnBnClickedButtonInsert10000();//10000���� ���� ��ư ��������
	afx_msg void OnBnClickedButtonInsert50000();//50000���� ���� ��ư ��������

// �����Դϴ�.
protected:

	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg LRESULT Main_BILL_Message(WPARAM wParam, LPARAM lParam);//���ο��� ���󿡰� �޽��� �۽������� ���� �̺�Ʈó�� �Լ�
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
