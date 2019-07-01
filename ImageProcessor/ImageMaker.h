#pragma once

#include "LogWriter.h"
#include <psapi.h>
#include <tlhelp32.h>

#define VERSION _T("version : 2019062501")

enum Image_Name_enum{//���� ��Ʈ�� ���Ź�ȣ Resource1000~
	  picture_main																			//���� ȭ��
	, picture_cardsale																		//ī�� �Ǹ� �ݾ� ���� ȭ��
	, picture_cardsale_insert																//ī�� �Ǹ� �ݾ� ���� ȭ��
	, picture_cardsale_processing															//ī�� �Ǹ� ���� ȭ��
	, picture_cardsale_lack																	//ī�� �Ǹ� �Ž��� ���� ȭ��
	, picture_cardsale_success																//ī�� �Ǹ� ���� ȭ��
	, picture_cardsale_failure																//ī�� �Ǹ� ���� ȭ��
	, picture_card_wait																		//ī�� ���� ��� ȭ��
	, picture_card_processing																//ī�� �ǵ� �� ȭ��
	, picture_recharge																		//ī�� ���� �ݾ� ���� ȭ��
	, picture_recharge_insert																//ī�� ���� �ݾ� ���� ȭ��
	, picture_recharge_processing															//ī�� ����	���� ȭ��
	, picture_recharge_lack																	//ī�� ���� �Ž��� ���� ȭ��
	, picture_recharge_success																//ī�� ����	���� ȭ��
	, picture_recharge_failure																//ī�� ����	���� ȭ��
	, picture_error																			//���� ȭ��
};

static const LPCSTR PICTURE_PATH[] = {//���� ��Ʈ�� ���
	  _T("C:\\SBS\\UI\\Passenger\\01_Menu\\KOR\\image\\bg.bmp")								//���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_select_1600.bmp")			//ī�� �Ǹ� �ݾ� ���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_insert_1600.bmp")			//ī�� �Ǹ� �ݾ� ���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_process_1600.bmp")			//ī�� �Ǹ� ���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_unchange_1600.bmp")			//ī�� �Ǹ� �Ž��� ���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_result_1600.bmp")			//ī�� �Ǹ� ���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\02_CardSaler\\KOR\\image\\bg_result_error_1600.bmp")		//ī�� �Ǹ� ���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_cardon_1600.bmp")			//ī�� ���� ��� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_scanning_1600.bmp")		//ī�� �ǵ� �� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_select_1600.bmp")			//ī�� ���� �ݾ� ���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_insert.bmp")				//ī�� ���� �ݾ� ���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_charging.bmp")			//ī�� ����	���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_unchange_1600.bmp")		//ī�� ���� �Ž��� ���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_result.bmp")				//ī�� ����	���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\03_CardRecharge\\KOR\\image\\bg_charge_fail.bmp")			//ī�� ����	���� ȭ��
	, _T("C:\\SBS\\UI\\Passenger\\04_Common\\KOR\\image\\bg_ready.bmp")						//���� ȭ��
};

enum STATIC_NUMBER{//����ƽ ��Ʈ�� ���Ź�ȣ Resource1100~
	  m_static_number_adult																	//� ī�� ����
	, m_static_number_adolescent															//û�ҳ� ī�� ����
	, m_static_number_season_ticket															//����� ī�� ����
	, m_static_contents_card																//ī�� ���� ����(ex � : A �� û�ҳ� : B �� ����� : C ��)
	, m_static_cardsale_fare																//ī�� �Ǹ� ���� ȭ�� �Ǹ� ���� �ؽ�Ʈ
	, m_static_cardsale_insert_fare															//ī�� �Ǹ� ���� ȭ�� ���� �ݾ�(����)
	, m_static_cardsale_insert_amount														//ī�� �Ǹ� ���� �ݾ� ����� ���� ���� �ݾ�
	, m_static_recharge_card_kind															//ī�� ���� ���� ȭ�� ���� ī�� ����(�ϳ���, ���̺�, ĳ�ú�, Ƽ�Ӵ�)
	, m_static_recharge_card_number															//ī�� ���� ���� ȭ�� ���� ī�� ��ȣ
	, m_static_recharge_card_balance														//ī�� ���� ���� ȭ�� ���� ī�� �ܾ�
	, m_static_recharge_fare																//ī�� ���� ���� ȭ�� �Ǹ� ���� �ؽ�Ʈ
	, m_static_recharge_insert_card_kind													//ī�� ���� ���� ȭ�� ���� ī�� ����(�ϳ���, ���̺�, ĳ�ú�, Ƽ�Ӵ�)
	, m_static_recharge_insert_card_balance													//ī�� ���� ���� ȭ�� ���� ī�� �ܾ�
	, m_static_recharge_insert_fare															//ī�� ���� ���� ȭ�� �Ǹ� ���� �ؽ�Ʈ
	, m_static_recharge_insert_amount														//ī�� ���� ���� ȭ�� ����� ���� ���� �ݾ�
	, m_static_version																		//���� �ؽ�Ʈ
};

static const LPCSTR STATIC_CONTENT[] = {//����ƽ ����
	  _T("0 ��")																			//� ī�� ����
	, _T("0 ��")																			//û�ҳ� ī�� ����
	, _T("0 ��")																			//����� ī�� ����
	, _T("� : 0 ��, û�ҳ� : 0 ��, ����� : 0��")										//ī�� ���� ����(ex � : A �� û�ҳ� : B �� ����� : C ��)
	, _T("0 ��")																			//ī�� �Ǹ� ���� ȭ�� �Ǹ� ���� �ؽ�Ʈ
	, _T("0 ��") 																			//ī�� �Ǹ� ���� ȭ�� ���� �ݾ�(����)
	, _T("0 ��")																			//ī�� �Ǹ� ���� �ݾ� ����� ���� ���� �ݾ�
	, _T("Ƽ�Ӵ�")																			//ī�� ���� ���� ȭ�� ���� ī�� ����(�ϳ���, ���̺�, ĳ�ú�, Ƽ�Ӵ�)
	, _T("1010009011443190")																//ī�� ���� ���� ȭ�� ���� ī�� ��ȣ
	, _T("0 ��")																			//ī�� ���� ���� ȭ�� ���� ī�� �ܾ�
	, _T("0 ��")																			//ī�� ���� ���� ȭ�� �Ǹ� ���� �ؽ�Ʈ
	, _T("Ƽ�Ӵ�")																			//ī�� ���� ���� ȭ�� ���� ī�� ����(�ϳ���, ���̺�, ĳ�ú�, Ƽ�Ӵ�)
	, _T("0 ��")																			//ī�� ���� ���� ȭ�� ���� ī�� �ܾ�
	, _T("0 ��")																			//ī�� ���� ���� ȭ�� �Ǹ� ���� �ؽ�Ʈ
	, _T("0 ��")																			//ī�� ���� ���� ȭ�� ����� ���� ���� �ݾ�
	, VERSION																				//���� �ؽ�Ʈ
};

enum BUTTON_NUMBER{//��ư ��Ʈ�� ���Ź�ȣ Resource1500~
	  m_button_insert_ok = 0																//�ݾ� ���� Ȯ�� ��ư
	, m_button_cardsale 																	//�ǸŹ�ư
	, m_button_recharge																		//������ư
	, m_button_cardsale_number3																//3��
	, m_button_cardsale_number2																//2��
	, m_button_cardsale_number1																//1��
	, m_button_cardsale_number0																//0��
	, m_button_kind_adult																	//� ���� ��ư
	, m_button_kind_adolescent																//û�ҳ� ���� ��ư
	, m_button_kind_season_ticket															//����� ���� ��ư
	, m_button_fare_5000																	// 5000�� ���� ��ư
	, m_button_fare_10000																	//10000�� ���� ��ư
	, m_button_fare_20000																	//20000�� ���� ��ư
	, m_button_fare_30000																	//30000�� ���� ��ư
	, m_button_fare_40000																	//40000�� ���� ��ư
	, m_button_fare_50000																	//50000�� ���� ��ư
	, m_button_before																		//����(����or�ݾװ�������)���� ����
	, m_button_direct																		//�����Է����� �ٲٱ�
	, m_button_add_0																		//�����Է� 0(�Է°� ����)
	, m_button_add_1																		//�����Է� 1
	, m_button_add_2																		//�����Է� 2
	, m_button_add_3																		//�����Է� 3
	, m_button_add_4																		//�����Է� 4
	, m_button_add_5																		//�����Է� 5
	, m_button_add_6																		//�����Է� 6
	, m_button_add_7																		//�����Է� 7
	, m_button_add_8																		//�����Է� 8
	, m_button_add_9																		//�����Է� 9
	, m_button_add_000																		//�����Է� 000(�Է°� õ��)
	, m_button_erase																		//���簪 0���� ����
	, m_button_cancle																		//��ҹ�ư
};

static const LPCSTR BUTTTON_CONTENT[] = {//��ư ����
	  _T("�ݾ� Ȯ��")																		//�ݾ� ���� Ȯ�� ��ư						
	, _T("ī�� �Ǹ�")																		//�ǸŹ�ư									
	, ("ī�� ����")																			//������ư									
	, _T("3��")																				//3��										
	, _T("2��")																				//2��										
	, _T("1��")																				//1��										
	, _T("����")																			//0��									
	, _T("�")																			//� ���� ��ư						   
	, _T("û�ҳ�")																			//û�ҳ� ���� ��ư						
	, _T("�����")																			//����� ���� ��ư						
	, _T("5,000��")																			// 5000�� ���� ��ư							
	, _T("10,000��")																		//10000�� ���� ��ư						
	, _T("20,000��")																		//20000�� ���� ��ư						
	, _T("30,000��")																		//30000�� ���� ��ư						
	, _T("40,000��")																		//40000�� ���� ��ư						
	, _T("50,000��")																		//50000�� ���� ��ư						
	, _T("����")																			//����(����or�ݾװ�������)���� ����	   
	, _T("�����Է�")																		//�����Է����� �ٲٱ�						
	, _T("0")																				//�����Է� 0(�Է°� ����)					
	, _T("1")																				//�����Է� 1								
	, _T("2")																				//�����Է� 2								
	, _T("3")																				//�����Է� 3								
	, _T("4")																				//�����Է� 4								
	, _T("5")																				//�����Է� 5								
	, _T("6")																				//�����Է� 6								
	, _T("7")																				//�����Է� 7								
	, _T("8")																				//�����Է� 8								
	, _T("9")																				//�����Է� 9								
	, _T("000")																				//�����Է� 000(�Է°� õ��)				
	, _T("����")																			//���簪 0���� ����						
	, _T("���")																			//��ҹ�ư								
};

class CImageMaker
{				 
public:			 
	CImageMaker(void);
	~CImageMaker(void);
//����
	
	HBITMAP			m_hBitmap_image[ (error + 1) ];											// Dialog�� ����̹��� ������ ���� ����.//(recharge_failure + 1) : ȭ�鰳��
	CString			m_backimgpath[(error + 1)];												// ����̹��� ���
	CStatic			m_picture_background[(error + 1)];										//��� ȭ�� ������Ʈ��
	CRect			static_Rect[(m_static_version + 1)];									//����ƽ ��ġ �� ũ��
	CRect			button_Rect[(m_button_cancle + 1)];										//��ư ��ġ �� ũ��
	CLogWriter		*m_logwriter;															//�α� �����
	
//�Լ�
	void background_make();																	//��� ����
	void static_Rect_make();																//����ƽ ��Ʈ�� ��ġ �� ũ�� ����
	void button_Rect_make();																//��ư ��Ʈ�� ��ġ �� ũ�� ����
};

