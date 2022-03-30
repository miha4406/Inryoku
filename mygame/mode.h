#pragma once

enum {
	mode_menuInit, //0
	mode_menuDisp,
	mode_menuFinish,

	mode_st1Init, //4-1
	mode_st1Disp,
	mode_st1Finish,

	mode_st2Init, //7-1
	mode_st2Disp,
	mode_st2Finish,

	mode_st3Init, //10-1
	mode_st3Disp,
	mode_st3Finish,
};


enum {
	modeseq_Thuru = 0,    //dont change?
	modeseq_Exit = -1,    //to quit
	modeseq_Increase = 1, //to next mode
	modeseq_st1 = 2,
	modeseq_st2 = 3,
	modeseq_st3 = 4,
};

int modeCtrl( int foo );

#define sWid 1024
#define sHei 768



#include "time.h"

clock_t getClTm1();
clock_t getClTm2();


int getTitle1();
int getTitle2();
