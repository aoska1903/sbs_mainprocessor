#include "stdafx.h"
#include "Imagemaker.h"

CImageMaker::CImageMaker(void)
{
	m_logwriter = new CLogWriter();
	m_logwriter->Log_Make(_T("ImageMaker"), _T("10_ImageMaker"));//로그 생성 함수
	static_Rect_make();//스태틱 컨트롤 위치 및 크기 생성
	button_Rect_make();//버튼 컨트롤 위치 및 크기 생성
}


CImageMaker::~CImageMaker(void)
{
}

void CImageMaker::background_make()//배경 생성
{
	for(int i = 0; i< sizeof(m_backimgpath)/sizeof(m_backimgpath[0]); i++){//각 경로에 파일 넣기
		m_backimgpath[i] = PICTURE_PATH[i];//경로에 파일 담기
		if(PathFileExists(m_backimgpath[i]) == TRUE){
			m_hBitmap_image[i] = (HBITMAP)LoadImage(NULL, m_backimgpath[i], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			if(m_hBitmap_image[i]==NULL){
				m_logwriter->now_write_log.Format(_T("%s 이미지 넣기 실패! "), Now_State_Contents[i]);
				m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
			}
		}else{
			m_logwriter->now_write_log.Format(_T("%s 이미지 불러오기 실패! "), Now_State_Contents[i]);
			m_logwriter->WriteLogFile(m_logwriter->now_write_log);//LOG 기록
		}
		m_picture_background[i].SetBitmap(m_hBitmap_image[i]);//사진컨트롤변수에 이미지 담기
		m_picture_background[i].SetWindowPos(NULL, 0, 0, (GetSystemMetrics(SM_CXSCREEN)), (GetSystemMetrics(SM_CYSCREEN)), SWP_SHOWWINDOW);//이미지 크기 조정
	}
}

void CImageMaker::static_Rect_make()//스태틱 컨트롤 위치 및 크기 생성
{
	static_Rect[m_static_number_adult] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.29), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.40), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.34));
	static_Rect[m_static_number_adolescent] = 															   			 														
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.42), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.40), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.47));
	static_Rect[m_static_number_season_ticket] = 														   			 														
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.54), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.40), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.59));
	static_Rect[m_static_contents_card] = 																   			 														
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.32), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.57), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.35));
	static_Rect[m_static_cardsale_fare] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.65), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.67), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.85), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.72));
	static_Rect[m_static_cardsale_insert_fare] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.35), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.42), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.50), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.47));
	static_Rect[m_static_cardsale_insert_amount] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.35), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.59), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.50), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.64));
	static_Rect[m_static_recharge_card_kind] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.25), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.50), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.35));
	static_Rect[m_static_recharge_card_number] = 		 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.25), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.41), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.50), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.46));
	static_Rect[m_static_recharge_card_balance] = 		 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.25), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.52), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.50), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.57));
	static_Rect[m_static_recharge_fare] = 				 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.25), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.77), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.50), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.82));
	static_Rect[m_static_recharge_insert_card_kind] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.42));
	static_Rect[m_static_recharge_insert_card_balance] = 																													
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.42), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.54));
	static_Rect[m_static_recharge_insert_fare] = 		 																													
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.67));
	static_Rect[m_static_recharge_insert_amount] = 		 																													
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.67), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.79));
	static_Rect[m_static_version] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.00), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.97), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.15), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 1.00));
}

void CImageMaker::button_Rect_make()//버튼 컨트롤 위치 및 크기 생성
{
	button_Rect[m_button_insert_ok] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.75), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.80), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.82), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.90));
	button_Rect	[m_button_cardsale] = 							  													 														
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.20), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.48), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.95));
	button_Rect	[m_button_recharge] = 							  													 														
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.50), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.30), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.78), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.95));
	button_Rect	[m_button_cardsale_number3] = 					  													 														
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.40), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.61), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.50));
	button_Rect[m_button_cardsale_number2] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.63), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.40), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.69), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.50));
	button_Rect[m_button_cardsale_number1] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.71), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.40), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.77), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.50));
	button_Rect[m_button_cardsale_number0] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.79), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.40), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.85), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.50));
	button_Rect[m_button_kind_adult] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.25), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.63), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.35));
	button_Rect[m_button_kind_adolescent] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.66), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.25), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.74), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.35));
	button_Rect[m_button_kind_season_ticket] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.77), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.25), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.85), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.35)); 
	button_Rect[m_button_fare_5000] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.25), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.73), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.35)); 
	button_Rect[m_button_fare_10000] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.75), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.25), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.93), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.35)); 
	button_Rect	[m_button_fare_20000] = 						  													 														
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.37), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.73), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.47)); 
	button_Rect	[m_button_fare_30000] = 						  													 														
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.75), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.37), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.93), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.47));
	button_Rect	[m_button_fare_40000] = 						  													 														
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.49), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.73), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.59)); 
	button_Rect[m_button_fare_50000] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.75), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.49), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.93), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.59));

	button_Rect[m_button_before] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.80), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.67), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.90));
	button_Rect[m_button_direct] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.61), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.73), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.71));
	button_Rect[m_button_add_0] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.58), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.67), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.68));
	button_Rect[m_button_add_1] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.22), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.67), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.32));
	button_Rect[m_button_add_2] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.68), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.22), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.80), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.32));
	button_Rect[m_button_add_3] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.81), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.22), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.93), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.32));
	button_Rect[m_button_add_4] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.34), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.67), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.44));
	button_Rect[m_button_add_5] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.68), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.34), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.80), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.44));
	button_Rect[m_button_add_6] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.81), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.34), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.93), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.44));
	button_Rect[m_button_add_7] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.55), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.46), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.67), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.56));
	button_Rect[m_button_add_8] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.68), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.46), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.80), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.56));
	button_Rect[m_button_add_9] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.81), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.46), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.93), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.56));
	button_Rect[m_button_add_000] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.68), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.58), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.80), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.68));
	button_Rect[m_button_erase] = 
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.81), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.58), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.93), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.68));
		

	button_Rect[m_button_cancle] = 	
		CRect( (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.85), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.80), (int)((double)GetSystemMetrics(SM_CXSCREEN) * 0.92), (int)((double)GetSystemMetrics(SM_CYSCREEN) * 0.90));					
}