#include "stdafx.h"
#include "DxLib.h"
#include "mode.h"
#include "game.h"
#include "time.h"
#include "input.h"
#include "stdio.h"


static clock_t startTm;

int st3_init(void) {
	startTm = clock();

	return modeseq_Increase;
}

//static int num = 0;
int st3_disp(void) {
	clock_t elaps = (clock() - startTm) / CLOCKS_PER_SEC;
#if DEBUG
	DrawFormatString(0, 16, GetColor(255, 255, 255), (const TCHAR*)"STAGE3 DISPLAY MODE (%d)", elaps);

#endif

	DrawFormatString(0, 36, GetColor(255, 255, 255), (const TCHAR*)"PRESS ESC TO MENU");

	if (getKeyboardOnTrigger(KEY_INPUT_ESCAPE)) {
		return mode_menuDisp;
	}

	//return 0;
	//if ( elaps < 5 ) {
	//	return 0;
	//}
	//return mode_AdvertiseDisp; //modeseq_Increase;
}

int st3_finish(void) {

	return mode_menuDisp; // modeseq_Increase;
}

