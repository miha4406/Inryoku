#include "stdafx.h"
#include "DxLib.h"
#include "mode.h" 
#include "game.h"
#include "menu.h"


static int modeNum = 0;  //mode number (ID+1)
static int inGame = false;  //kakunin!
int modeCtrl( int foo ) 
{
	int ret = FALSE;

	switch ( modeNum ) {
		
		case mode_menuInit:
		{
			ret = menu_init( );
		} break;
		case mode_menuDisp:
		{
			ret = menu_disp( );
			if ( ret == modeseq_st1 ) 
			{
				modeNum = mode_st1Init-1;
				inGame = true;
				ret = menu_finish( );
			}
			if ( ret == modeseq_st2 ) {
				modeNum = mode_st2Init-1;
				inGame = true;
				ret = menu_finish( );
			}
			if (ret == modeseq_st3) {
				modeNum = mode_st3Init-1;
				inGame = true;
				ret = menu_finish();
			}
		} break;
		case mode_menuFinish:
		{
			ret = menu_finish( );
			//modeNum = mode_TitleInit - 1;
		} break;
		case mode_st1Init:
			{
			inGame = false;
			ret = st1_init( );
			} break;
		case mode_st1Disp:
			{
				ret = st1_disp( );
			} break;
		case mode_st1Finish:
			{
				modeNum = mode_menuInit-1;  //go to menu
				ret = st1_finish( );
			} break;
		case mode_st2Init:
		{
			inGame = false;
			ret = st2_init( );
		} break;
		case mode_st2Disp:
		{
			ret = st2_disp( );
		} break;
		case mode_st2Finish:
		{
			modeNum = mode_menuInit - 1;  //go to menu
			ret = st2_finish( );
		} break;
		case mode_st3Init:
		{
			inGame = false;
			ret = st3_init();
		} break;
		case mode_st3Disp:
		{
			ret = st3_disp();
		} break;
		case mode_st3Finish:
		{
			modeNum = mode_menuInit - 1;  //go to menu
			ret = st3_finish( );
		} break;
		
		default:
			{
			  modeNum = mode_menuInit; //starts from menu?
			} break;
	}

#if DEBUG
	DrawFormatString( 0, 0, GetColor( 255, 255, 0 ), ( const TCHAR* )"MODE: %d", modeNum );
#endif

	if( ret > modeseq_Thuru )
	{
		modeNum = modeNum + ret;
		ret = 0;
	}else if( ret < modeseq_Thuru )
	{
		return ret;
	}

	return ret;
}
