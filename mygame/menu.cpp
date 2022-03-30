#include "stdafx.h"
#include "DxLib.h"
#include "mode.h"
#include "game.h"
#include "time.h"
#include "input.h"

#define StX 102
#define StY 237


static clock_t startTm;
static int sw;

int menu_init( void ) {
	startTm = clock( );
	sw = (getTitle1()>0 || getTitle2()>0)? 1 : 0;

	return modeseq_Increase;
}

static int mX, mY;

clock_t getClTm1();
clock_t getClTm2();


int menu_disp( void ) {
	clock_t elaps = (clock() -startTm)/CLOCKS_PER_SEC;
#if DEBUG
	DrawFormatString( 0, 16, GetColor( 255, 255, 255 ), ( const TCHAR* )"MENU DISPLAY MODE (%d)", elaps );
	
#endif

	if ( getKeyboardOnTrigger( KEY_INPUT_TAB ) ) {
		DrawFormatString( 0, 36, GetColor( 255, 255, 255 ), ( const TCHAR* )"PRESS ESC TO EXIT" );
		DrawFormatString( 0, 56, GetColor( 255, 255, 255 ), ( const TCHAR* )"PRESS 1 TO STAGE1" );
		DrawFormatString( 0, 76, GetColor( 255, 255, 255 ), ( const TCHAR* )"PRESS 2 TO STAGE2" );
		DrawFormatString( 0, 96, GetColor( 255, 255, 255 ), ( const TCHAR* )"PRESS 3 TO STAGE3" );
	}	

	GetMousePoint( &mX, &mY );
	int mi = GetMouseInput( );

	//title +button
	if ( sw == 0 ) {
		LoadGraphScreen( 0, 0, "media/title.png", TRUE );
		if ( mX > 318 && mX < 660 ) {
			if ( mY > 331 && mY < 422 ) {
				LoadGraphScreen( 318, 331, "media/sframe.png", TRUE );
				if ( mi ) { sw = 1; }
			}			
		}
	}


	//main menu +mouse	
	if ( sw == 1 ) { 
		LoadGraphScreen( 0, 0, "media/menu.png", TRUE );
		DrawFormatString( 0, 26, GetColor( 5, 5, 255 ), ( const TCHAR* )"STAGE1 CLEAR TIME: %d sec", getClTm1( ) );
		//DrawFormatString( 0, 36, GetColor( 5, 5, 255 ), ( const TCHAR* )"STAGE2 CLEAR TIME: %d sec", getClTm2( ) );
		if ((int)getClTm1() != 0) {
			if((int)getClTm1()>=25){ LoadGraphScreen(StX, StY, "media/star1.png", TRUE); }
			else if ((int)getClTm1()<=15){ LoadGraphScreen(StX, StY, "media/star3.png", TRUE); }
			else { LoadGraphScreen(StX, StY, "media/star2.png", TRUE); }
		}
		if ((int)getClTm2() != 0) {
			if((int)getClTm2()>=25){ LoadGraphScreen(StX+224, StY, "media/star1.png", TRUE); }
			else if ((int)getClTm2()<=15){ LoadGraphScreen(StX+224, StY, "media/star3.png", TRUE); }
			else { LoadGraphScreen(StX+224, StY, "media/star2.png", TRUE); }
		}

		if ( mY > 106 && mY < 106+190 ) {
			if ( mX > 71 && mX < 71+190 ) { 
				LoadGraphScreen( 71, 106, "media/frame.bmp", TRUE );
				if ( mi ) { return modeseq_st1; }

			}
			if ( mX > 295 && mX < 295+190 ) {
				LoadGraphScreen( 295, 106, "media/frame.bmp", TRUE );
				if ( mi ) { return modeseq_st2; }
			}
		}		
	}

	
	//main menu keyboard
	if( getKeyboardOnTrigger( KEY_INPUT_ESCAPE ) )
	{
		return modeseq_Exit;
	}
	if ( getKeyboardOnTrigger( KEY_INPUT_1 ) ) {
		return modeseq_st1;
	}
	if ( getKeyboardOnTrigger( KEY_INPUT_2 ) ) {
		return modeseq_st2;
	}
	if (getKeyboardOnTrigger(KEY_INPUT_3)) {
		return modeseq_st3;
	}	

	//if ( elaps < 5 ) {		return 0;	}	return modeseq_Increase;
}

int menu_finish( void ) {
	return modeseq_Increase;
}

