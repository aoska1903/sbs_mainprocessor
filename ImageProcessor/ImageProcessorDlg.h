
// ImageProcessorDlg.h : ��� ����
//

#pragma once

#define IDC_PICTURE_INITIAL 1000
#define IDC_STATIC_INITIAL	1100
#define IDC_BUTTON_INITIAL	1500

#include "LogWriter.h"
#include "ImageMMap.h"
#include "ImageMaker.h"

// CImageProcessorDlg ��ȭ ����
class CImageProcessorDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CImageProcessorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_IMAGEPROCESSOR_DIALOG };

#define NUMBER_CARD_FIND 3

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

public:
//����
	INT				Now_Image_State;									//���� ����
	INT				Now_Selete_Card;									//�ݾ� ���� ȭ�鿡�� ���� ���õ� ī�� ����
	INT				number_cards[NUMBER_CARD_FIND];						//��ư���� �Է��� ī�� ���� ( 0 : �, 1 : û�ҳ�, 2 : ����� )
	INT				cardsale_fare;										//ī�弱��ȭ�鿡�� ���� ������ ī��� ���� ��
	INT				recharge_fare;										//���� ����
	CString			static_text;										//����ƽ ���� ������Ʈ�� �ؽ�Ʈ
	BOOL			Direct_Screen;										//���� �ݾ� ���� �����ݾ׼�������(1.���� �ݾ� ���� 2.���� �ݾ� ����(5000,10000) )
	CLogWriter		*m_logwriter;										//�α� �����
	CImageMMap		*m_imagemmap;										//�̹��� MMap
	CImageMaker		*m_imagemaker;										//�̹��� ��Ʈ�� ���� ��ü
//����ƽ ��Ʈ��
	CStatic			m_static[(m_static_version + 1)];					//����ƽ �迭
//��ư ��Ʈ��
	CButton			m_button[(m_button_cancle + 1)];					//��ư �迭
//�Լ�
	void			control_make();										//��Ʈ�� ����
	void			background_make();									//��� ����
	void			static_make();										//�ؽ�Ʈ ����
	void			button_make();										//��ư ����
	void			control_collocate();								//��Ʈ�� ��ġ
	void			background_collocate();								//���ȭ���ġ
	void			Image_Screen_Change(int change_screen);				//ȭ�� ����
	void			main_return_init();									//����ȭ�� ���ƿö� �ʱ�ȭ
	void			update_cardsale(int number);						//ī�� �ż� ��ư ������ �� �� ����
	void			cardsale_insert_update();							//Ȯ�δ������� �ݾ�,ī�尳�� T_RECHARGE_DATA�� ����
	void			select_recharge_fare(int fare);						//���� �ݾ� ����
	void			cardsale_insert_renew(int now_insert_money);		//ī�� �Ǹ� ���Ի��¿��� ��(���� or ����) ���� �Ǿ��� ��
	void			recharge_insert_renew(int now_insert_money);		//ī�� ���� ���Ի��¿��� ��(���� or ����)
	void			change_card_kind();									//MMap���� �о�� ī������ ǥ��
	void			enter_direct(int enter_num);						//�����е崭���� ���� �Է�
// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);	//����ƽ �����ϰ�
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT Main_Image_Message(WPARAM wParam, LPARAM lParam);	//���ο��� �̹������α׷����� �޽��� �۽������� ���� �̺�Ʈ �Լ�
	afx_msg void OnBnClickedINSERTOK();									//�ݾ� ���� Ȯ�� ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedCANCLE();									//CANCLE ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedCARDSALE();									//CARDSALE ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedRECHARGE();									//RECHARGE ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedCARDSALENUMBER3();							//CARDSALENUMBER3 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedCARDSALENUMBER2();							//CARDSALENUMBER2 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedCARDSALENUMBER1();							//CARDSALENUMBER1 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedCARDSALENUMBER0();							//CARDSALENUMBER0 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedNUMBERADULT();								//NUMBERADULT ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedNUMBERADOLESCEMT();							//NUMBERADULT ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedNUMBERSEASONTICKET();						//NUMBERADULT ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedFARE5000();									//���� 5000�� ���� ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedFARE10000();								//���� 10000�� ���� ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedFARE20000();								//���� 20000�� ���� ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedFARE30000();								//���� 30000�� ���� ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedFARE40000();								//���� 40000�� ���� ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedFARE50000();								//���� 50000�� ���� ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedBEFORE();									//���� ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedDIRECT();									//���� �Է� ���� ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD0();										//���� �Է� 0	 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD1();										//���� �Է� 1	 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD2();										//���� �Է� 2	 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD3();										//���� �Է� 3	 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD4();										//���� �Է� 4	 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD5();										//���� �Է� 5	 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD6();										//���� �Է� 6	 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD7();										//���� �Է� 7	 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD8();										//���� �Է� 8	 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD9();										//���� �Է� 9	 ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedADD000();									//���� �Է� 000  ��ư ������ ��� �̺�Ʈ
	afx_msg void OnBnClickedERASE();									//���� �Է� ���� ��ư ������ ��� �̺�Ʈ
	DECLARE_MESSAGE_MAP()
};
