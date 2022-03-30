#include "stdafx.h"
#include "DxLib.h"
#include "mode.h"
#include "game.h"
#include "time.h"
#include "input.h"
#include "stdio.h"
#include "stage.h"


static clock_t startTm;
static clock_t clTm1 = 0;
int clSw1;
static unsigned int colW, colR, colB;
static int mX, mY;
static int mi;
static int play;
static int backHandle;


int st1_init( void ) {
	startTm = clock( );	
	play = 0;
	clSw1 = 0;
	
	SetBackgroundColor(200,200,200);
	colW = GetColor( 5, 5, 5 ); //not so white
	colR = GetColor( 250, 0, 0 );
	colB = GetColor(0, 0, 250);

	bHandle = LoadGraph("media/bWay.png");
	cHandle = LoadGraph("media/cargo.png");
	gHandle = LoadGraph("media/goal.png");
	clHandle = LoadGraph("media/clear.png");
	cl2Handle = LoadGraph("media/clear2.png");
	backHandle = LoadGraph("media/back.png");

	maru.x = sWid/2 -3.5*GRID; 	
	maru.y = sHei/2 +1.5*GRID;
	//maru.x = sWid/2 -0.5*GRID;
	//maru.y = sHei/2 -0.5*GRID;
	maru.col = GetColor( 0, 255, 0 );
	
	p1.x = sWid/2 +5.5*GRID;
	p1.y = sHei/2 -4.5*GRID;
	p1.z = 1;
	p2.x = sWid/2 +5.5*GRID;
	p2.y = sHei/2 -4.5*GRID;
	p2.z = 1;
	m1.x = sWid/2 +5.5*GRID;
	m1.y = sHei/2 -3.5*GRID;
	m1.z = -1;
	m2.x = sWid/2 +5.5*GRID;
	m2.y = sHei/2 -3.5*GRID;
	m2.z = -1;
	m3.x = sWid/2 + 5.5*GRID;
	m3.y = sHei/2 -3.5*GRID;
	m3.z = -1;
	
	return modeseq_Increase;
}


/* only stage1 function */
static int wayR(int x, int y) {
	if (y == sHei/2 +1.5*GRID) {
		if ((int)(x + STEP) <= (int)(sWid/2 -0.5*GRID)) {
			return 1;
		} else return 0;
	}	
	if (y == sHei/2 -0.5*GRID) {
		if ((int)(x + STEP) <= (int)(sWid/2 +3.5*GRID)) {
			return 1;
		}
		else return 0;
	}
	return 0;
}
static int wayL(int x, int y) {
	if (y == sHei/2 +1.5*GRID) {
		if ((int)(x - STEP) >= (int)(sWid/2 -3.5*GRID)) {
			return 1;
		}
		else return 0;
	}
	if (y == sHei/2 -0.5*GRID) {
		if ((int)(x - STEP) >= (int)(sWid/2 -0.5*GRID)) {
			return 1;
		}
		else return 0;
	}
	return 0;
}
static int wayU(int x, int y) {
	if (x == sWid/2 -0.5*GRID) {
		if ((int)(y - STEP) >= (int)( sHei/2 -0.5*GRID)) {
			return 1;
		}
		else return 0;
	}
	return 0;
}
static int wayD(int x, int y) {
	if ( x == sWid/2 -0.5*GRID ) {
		if ( ( int )( y + STEP ) <= ( int )( sHei/2+1.5*GRID ) ) {
			return 1;
		} else return 0;
	}
		return 0;
}


int st1_disp( void ) {
	clock_t elaps = ( clock( ) - startTm ) / CLOCKS_PER_SEC;
#if DEBUG
	DrawFormatString( 0, 16, GetColor( 255, 255, 255 ), ( const TCHAR* )"STAGE1 DISPLAY MODE (%d)", elaps );

#endif
	GetMousePoint( &mX, &mY );
	mi = GetMouseInput( );

	//DrawFormatString( 0, 36, GetColor( 255, 255, 255 ), ( const TCHAR* )"PRESS ESC TO MENU" );
	if (getKeyboardOnTrigger(KEY_INPUT_ESCAPE)) {
		return mode_menuDisp;
	}
	DrawExtendGraph(0 +10, sHei/2 +4*GRID, sWid/2 -5.5*GRID, sHei -10, backHandle, TRUE);
		if ( mX > 0+10 && mX < sWid/2 -5.5*GRID ) {
			if ( mY > sHei/2 +4*GRID && mY < sHei-10 ) {				
				if ( mi ) { return mode_menuDisp; }
			}
		}



	//grid lines	
	/*for ( int y = sHei/2 -5*GRID; y <= sHei/2 +5*GRID; y += GRID ) {
		DrawLine( sWid/2 -5*GRID, y, sWid/2 +5*GRID, y, colW );
	}
	for ( int x = sWid/2 -5*GRID; x <= sWid/2 + 5*GRID; x += GRID ) {
		DrawLine( x, sHei/2 -5*GRID, x, sHei/2 + 5*GRID, colW );
	}
	DrawLine( 0, sHei/2, sWid, sHei/2, colR );
	DrawLine( sWid/2, 0, sWid/2, sHei, colR );*/

	
	//moveability switch
	if ( mi ) {
		if ( mX > p1.x -GRID/2 && mX < p1.x +GRID/2 ) {
			if ( mY > p1.y -GRID/2 && mY < p1.y +GRID/2 ) { p1.m = 1; }  // <--start pos p1
		}
	}
	if ( mi && p1.m == 0) {
		if ( mX > p2.x -GRID/2 && mX < p2.x +GRID/2 ) {
			if ( mY > p2.y -GRID/2 && mY < p2.y +GRID/2 ) { p2.m = 1; }  // <--start pos p1
		}
	}
	if ( mi ) {
		if ( mX > m1.x - GRID/2 && mX < m1.x + GRID/2 ) {
			if ( mY > m1.y -GRID/2 && mY < m1.y +GRID/2 ) { m1.m = 1; }  // <--start pos m1
		}
	}
	if ( mi && m1.m == 0 && m3.m == 0) {
		if ( mX > m2.x - GRID/2 && mX < m2.x + GRID/2 ) {
			if ( mY > m2.y -GRID/2 && mY < m2.y +GRID/2 ) { m2.m = 1; }  // <--start pos m2
		}
	}  
	if ( mi && m1.m == 0 && m2.m == 0 ) {
		if ( mX > m3.x -GRID/2 && mX < m3.x +GRID/2 ) {
			if ( mY > m3.y -GRID/2 && mY < m3.y +GRID/2 ) { m3.m = 1; }  // <--start pos m3
		}
	}


	//grid cells detect
	if ( mX > (sWid/2 -5*GRID) && mX < ( sWid/2 +1*GRID ) ) {
		if (mY > ( sHei/2 +0*GRID ) && mY < ( sHei/2 +3*GRID )) {
			LoadGraphScreen(mX - (mX %GRID)+3, mY - (mY %GRID)+3, "media/cell.bmp", TRUE);
			if ( mi && (p1.m == 1) ) { 
				if ( (gX != m1.x || gY != m1.y) && (gX != m2.x || gY != m2.y) && (gX != m3.x || gY != m3.y) ) {
					p1.x = gX;
					p1.y = gY;
					p1.m = 0;
				}				
			}
			if ( mi && (p2.m == 1) ) { 
				if ( (gX != m1.x || gY != m1.y) && (gX != m2.x || gY != m2.y) && (gX != m3.x || gY != m3.y) ) {
					p2.x = gX;
					p2.y = gY;
					p2.m = 0;
				}				
			}
			if ( mi && ( m1.m == 1 ) ) {
				if ( (gX != p1.x) || (gY != p1.y) && (gX != p2.x) || (gY != p2.y) ) {  //ether one not equal
					m1.x = gX;
					m1.y = gY;
					m1.m = 0;					
				}				
			}
			if ( mi && ( m2.m == 1 ) ) {
				if ( (gX != p1.x || gY != p1.y) && (gX != p2.x || gY != p2.y) ) {
					m2.x = gX;
					m2.y = gY;
					m2.m = 0;					
				}
			}
			if ( mi && ( m3.m == 1 ) ) {
				if ( (gX != p1.x || gY != p1.y) && (gX != p2.x) || (gY != p2.y) ) {
					m3.x = gX;
					m3.y = gY;
					m3.m = 0;
				}
			}
		}
	}
	if ( mX > (sWid/2 -2*GRID) && mX < ( sWid/2 +5*GRID ) ) {
		if ( mY > ( sHei/2 -2*GRID ) && mY < ( sHei/2 + 1*GRID ) ) {
			LoadGraphScreen( mX - ( mX % GRID )+3, mY - ( mY % GRID )+3, "media/cell.bmp", TRUE );
			if ( mi && (p1.m == 1) ) { 
				if ( (gX != m1.x || gY != m1.y) && (gX != m2.x || gY != m2.y) && (gX != m3.x || gY != m3.y) ) {
					p1.x = gX;
					p1.y = gY;
					p1.m = 0;
				}				
			}
			if ( mi && (p2.m == 1) ) { 
				if ( (gX != m1.x || gY != m1.y) && (gX != m2.x || gY != m2.y) && (gX != m3.x || gY != m3.y) ) {
					p2.x = gX;
					p2.y = gY;
					p2.m = 0;
				}				
			}
			if ( mi && ( m1.m == 1 ) ) {
				if ( (gX != p1.x) || (gY != p1.y) && (gX != p2.x) || (gY != p2.y) ) {  //ether one not equal
					m1.x = gX;
					m1.y = gY;
					m1.m = 0;					
				}				
			}
			if ( mi && ( m2.m == 1 ) ) {
				if ( (gX != p1.x || gY != p1.y) && (gX != p2.x || gY != p2.y) ) {
					m2.x = gX;
					m2.y = gY;
					m2.m = 0;					
				}
			}
			if ( mi && ( m3.m == 1 ) ) {
				if ( (gX != p1.x || gY != p1.y) && (gX != p2.x) || (gY != p2.y) ) {
					m3.x = gX;
					m3.y = gY;
					m3.m = 0;
				}
			}
		}
	}	


	//waylines
	//DrawLine( sWid/2 -0.5*GRID, sHei/2 -0.5*GRID, sWid/2 +3.5*GRID, sHei/2 -0.5*GRID, colB ); //upper
	for(int i = sWid/2 -0.5*GRID-STEP; i<= sWid/2 +3.5*GRID-STEP; i+=GRID){ DrawExtendGraph(i, sHei/2 -0.5*GRID-STEP, i+GRID, sHei/2 -0.5*GRID+GRID-STEP, bHandle, TRUE); }
	//DrawLine( sWid/2 -0.5*GRID, sHei/2 -0.5*GRID, sWid/2 -0.5*GRID, sHei/2 +1.5*GRID, colB ); //vertical
	DrawExtendGraph(sWid/2 -GRID, sHei/2, sWid/2, sHei/2 +GRID, bHandle, TRUE); 
	//DrawLine( sWid/2 -3.5*GRID, sHei/2 +1.5*GRID, sWid/2 -0.5*GRID, sHei/2 +1.5*GRID, colB ); //lover
	for(int i = sWid/2 -3.5*GRID-STEP; i<= sWid/2 -0.5*GRID-STEP; i+=GRID){ DrawExtendGraph(i, sHei/2 +1.5*GRID-STEP, i+GRID, sHei/2 +1.5*GRID+GRID-STEP, bHandle, TRUE); }
	DrawExtendGraph(sWid/2 +3*GRID, sHei/2-GRID, sWid/2+4*GRID, sHei/2, gHandle, TRUE); 


	//cargo & clear window
	//DrawCircle( maru.x, maru.y, GRID/2, maru.col, TRUE );
	if ( maru.x==(sWid/2 +3.5*GRID) && maru.y==(sHei/2-0.5*GRID) ) { 
		//maru.col = colR; 
		DrawExtendGraph(sWid/2-3*GRID, sHei/2-2*GRID, sWid/2+3*GRID, sHei/2+2*GRID, clHandle, TRUE); //clear window
		if((mX>sWid/2-2*GRID)&&(mX<sWid/2+2*GRID)&&(mY>sHei/2)&&(mY<sHei/2+GRID) ){
			DrawExtendGraph(sWid/2-3*GRID, sHei/2-2*GRID, sWid/2+3*GRID, sHei/2+2*GRID, cl2Handle, TRUE); //clear2 window
			if(mi){ return mode_menuDisp; }
		}
		DrawFormatString(sWid/2+GRID, sHei/2-GRID, colW, (const TCHAR*)"%d sec", clTm1);

		if(clSw1==0) { clTm1 = elaps; clSw1 = 1; }
	}
	DrawExtendGraph(maru.x-STEP, maru.y-STEP, maru.x+STEP, maru.y+STEP, cHandle, TRUE); 


	//play button--------------------------------------------------------------------------------------------------------------------------------------------
	if ( play == 0 ) {
		LoadGraphScreen( sWid/2 +6*GRID, sHei/2 +4*GRID, "media/play0.png", TRUE );
		if ( mX > sWid/2 +6*GRID && mX < sWid ) {
			if ( mY > sHei/2 +4*GRID && mY < sHei ) {				
				if ( mi ) { play = 1; }
			}
		}
	}
	if ( play == 1 ) {
		LoadGraphScreen( sWid/2 +6*GRID, sHei/2 +4*GRID, "media/play1.png", TRUE );
	//if (getKeyboardOnTrigger(KEY_INPUT_RIGHT)) {} 
	if ( wayR( maru.x, maru.y ) == 1 ) {		
		if ( attrR(maru,p1)==1 && attrR(maru,p2)==1 ) { maru.x += STEP;  WaitTimer(WT); }
		else if ( (attrR(maru, p1)==1 && !attrL(maru,p2)) || (attrR(maru,p2)==1 && !attrL(maru,p1)) ) { //
			if ( !attrU(maru,p1) && !attrU(maru,p2) && !attrD(maru,p1) && !attrD(maru,p2) ) { //
				if ( !( attrU( maru, m1 ) && attrU( maru, m2 ) ) && !( attrD( maru, m1 ) && attrD( maru, m2 ) ) ) {
					if ( !( attrU( maru, m1 ) && attrU( maru, m3 ) ) && !( attrD( maru, m1 ) && attrD( maru, m3 ) ) ) {
						if ( !( attrU( maru, m2 ) && attrU( maru, m3 ) ) && !( attrD( maru, m2 ) && attrD( maru, m3 ) ) ) {
							maru.x += STEP;  WaitTimer( WT );
						} //double minuses vertical check
					}
				}
			}
		}
		if ( ( attrR( maru, m1 ) && attrR( maru, m2 ) ) ||
			( attrR( maru, m1 ) && attrR( maru, m3 ) ) ||
			 ( attrR( maru, m2 ) && attrR( maru, m3 ) ) ) {
			if( !(attrR(maru,p1)&&attrR(maru,p2)) && !(attrL(maru,p1)&&attrL(maru,p2)) && !(attrU(maru,p1)&&attrU(maru,p2)) && !(attrD(maru,p1)&&attrD(maru,p2)) ){ maru.x += STEP;  WaitTimer(WT); }			
		}  //double minus R, no double plus 
		else if ( ( attrR( maru, m1 ) && ( !attrL( maru, m2 ) && !attrL( maru, m3 ) ) ) || ( attrR( maru, m2 ) && ( !attrL( maru, m1 ) && !attrL( maru, m3 ) ) ) || ( attrR( maru, m3 ) && ( !attrL( maru, m1 ) && !attrL( maru, m2 ) ) ) ) {
			if ( !attrU( maru, p1 ) && !attrD( maru, p1 ) && !attrU( maru, p2 ) && !attrD( maru, p2 ) && !attrU( maru, m1 ) && !attrD( maru, m1 ) && !attrU( maru, m2 ) && !attrD( maru, m2 ) && !attrU( maru, m3 ) && !attrD( maru, m3 ) ) {
				maru.x += STEP;  WaitTimer(WT);
			}
		} //pro4ie pomehi			
	}
	//if (getKeyboardOnTrigger(KEY_INPUT_LEFT)) {}
	if ( wayL( maru.x, maru.y ) == 1 ) {
		if ( attrL(maru,p1)==1 && attrL(maru,p2)==1 ){ maru.x -= STEP;  WaitTimer(WT); }
		else if ( (attrL(maru,p1)==1 && !attrR(maru,p2)) || (attrL(maru,p2)==1 && !attrR(maru,p1)) ) { //
			if ( !attrU(maru,p1) && !attrU(maru,p2) && !attrD(maru,p1) && !attrD(maru,p2) ) { //
				if ( !( attrU( maru, m1 ) && attrU( maru, m2 ) ) && !( attrD( maru, m1 ) && attrD( maru, m2 ) ) ) {
					if ( !( attrU( maru, m1 ) && attrU( maru, m3 ) ) && !( attrD( maru, m1 ) && attrD( maru, m3 ) ) ) {
						if ( !( attrU( maru, m2 ) && attrU( maru, m3 ) ) && !( attrD( maru, m2 ) && attrD( maru, m3 ) ) ) {
							maru.x -= STEP;  WaitTimer( WT );
						} //double minuses vertical check
					}
				}
			}
		}
		if ( ( attrL( maru, m1 ) && attrL( maru, m2 ) ) ||
			( attrL( maru, m1 ) && attrL( maru, m3 ) ) ||
			 ( attrL( maru, m2 ) && attrL( maru, m3 ) ) ) {
			if( !(attrR(maru,p1)&&attrR(maru,p2)) && !(attrL(maru,p1)&&attrL(maru,p2)) && !(attrU(maru,p1)&&attrU(maru,p2)) && !(attrD(maru,p1)&&attrD(maru,p2)) ){ maru.x -= STEP;  WaitTimer(WT); }			
		}  //double minus L, no double plus 
		else if ( ( attrL( maru, m1 ) && ( !attrR( maru, m2 ) && !attrR( maru, m3 ) ) ) || ( attrL( maru, m2 ) && ( !attrR( maru, m1 ) && !attrR( maru, m3 ) ) ) || ( attrL( maru, m3 ) && ( !attrR( maru, m1 ) && !attrR( maru, m2 ) ) ) ) {
			if ( !attrU( maru, p1 ) && !attrD( maru, p1 ) && !attrU( maru, p2 ) && !attrD( maru, p2 ) && !attrU( maru, m1 ) && !attrD( maru, m1 ) && !attrU( maru, m2 ) && !attrD( maru, m2 ) && !attrU( maru, m3 ) && !attrD( maru, m3 ) ) {
				maru.x -= STEP;  WaitTimer(WT);
			}
		} //pro4ie pomehi					
	}
	//if (getKeyboardOnTrigger(KEY_INPUT_UP)) {}
	if ( wayU( maru.x, maru.y ) == 1 ) {
		if ( attrU(maru,p1)==1 && attrU(maru,p2)==1 ){ maru.y -= STEP;  WaitTimer(WT); }
		else if ( (attrU(maru,p1)==1 && !attrD(maru,p2)) || (attrU(maru,p2)==1 && !attrD(maru,p1)) ) { //
			if ( !attrR(maru,p1) && !attrR(maru,p2) && !attrL(maru,p1) && !attrL(maru,p2) ) { //
				if ( !( attrR( maru, m1 ) && attrR( maru, m2 ) ) && !( attrL( maru, m1 ) && attrL( maru, m2 ) ) ) {
					if ( !( attrR( maru, m1 ) && attrR( maru, m3 ) ) && !( attrL( maru, m1 ) && attrL( maru, m3 ) ) ) {
						if ( !( attrR( maru, m2 ) && attrR( maru, m3 ) ) && !( attrL( maru, m2 ) && attrL( maru, m3 ) ) ) {
							maru.y -= STEP;  WaitTimer( WT );
						} //double minuses lateral check
					}
				}
			}
		}
		if ( ( attrU( maru, m1 ) && attrU( maru, m2 ) ) ||
			( attrU( maru, m1 ) && attrU( maru, m3 ) ) ||
			 ( attrU( maru, m2 ) && attrU( maru, m3 ) ) ) {
			if( !(attrR(maru,p1)&&attrR(maru,p2)) && !(attrL(maru,p1)&&attrL(maru,p2)) && !(attrU(maru,p1)&&attrU(maru,p2)) && !(attrD(maru,p1)&&attrD(maru,p2)) ){ maru.y -= STEP;  WaitTimer(WT); }			
		}  //double minus U, no double plus
		else if ( ( attrU( maru, m1 ) && ( !attrD( maru, m2 ) && !attrD( maru, m3 ) ) ) || ( attrU( maru, m2 ) && ( !attrD( maru, m1 ) && !attrD( maru, m3 ) ) ) || ( attrU( maru, m3 ) && ( !attrD( maru, m1 ) && !attrD( maru, m2 ) ) ) ) {
			if ( !attrR( maru, p1 ) && !attrL( maru, p1 ) && !attrR( maru, p2 ) && !attrL( maru, p2 ) && !attrR( maru, m1 ) && !attrL( maru, m1 ) && !attrR( maru, m2 ) && !attrL( maru, m2 ) && !attrR( maru, m3 ) && !attrL( maru, m3 ) ) {
				maru.y -= STEP;  WaitTimer(WT);
			}
		} //pro4ie pomehi						   			 		  		  					
	}
	//if (getKeyboardOnTrigger(KEY_INPUT_DOWN)) {}
	if ( wayD( maru.x, maru.y ) == 1 ) {
		if ( attrD(maru,p1)==1 && attrD(maru,p2)==1 ){ maru.y += STEP;  WaitTimer(WT); }
		else if ( (attrD(maru,p1)==1 && !attrU(maru,p2)) || (attrD(maru,p2)==1 && !attrU(maru,p1)) ) { //
			if ( !attrR(maru,p1) && !attrR(maru,p2) && !attrL(maru,p1) && !attrL(maru,p2) ) { //
				if ( !( attrR( maru, m1 ) && attrR( maru, m2 ) ) && !( attrL( maru, m1 ) && attrL( maru, m2 ) ) ) {
					if ( !( attrR( maru, m1 ) && attrR( maru, m3 ) ) && !( attrL( maru, m1 ) && attrL( maru, m3 ) ) ) {
						if ( !( attrR( maru, m2 ) && attrR( maru, m3 ) ) && !( attrL( maru, m2 ) && attrL( maru, m3 ) ) ) {
							maru.y += STEP;  WaitTimer( WT );
						} //double minuses lateral check
					}
				}
			}
		}
		if ( ( attrD( maru, m1 ) && attrD( maru, m2 ) ) ||
			( attrD( maru, m1 ) && attrD( maru, m3 ) ) ||
			 ( attrD( maru, m2 ) && attrD( maru, m3 ) ) ) {
			if( !(attrR(maru,p1)&&attrR(maru,p2)) && !(attrL(maru,p1)&&attrL(maru,p2)) && !(attrU(maru,p1)&&attrU(maru,p2)) && !(attrD(maru,p1)&&attrD(maru,p2)) ){ maru.y -= STEP;  WaitTimer(WT);}			
		}  //double minus D, no double plus
		else if ( ( attrD( maru, m1 ) && ( !attrU( maru, m2 ) && !attrU( maru, m3 ) ) ) || ( attrD( maru, m2 ) && ( !attrU( maru, m1 ) && !attrU( maru, m3 ) ) ) || ( attrD( maru, m3 ) && ( !attrU( maru, m1 ) && !attrU( maru, m2 ) ) ) ) {
			if ( !attrR( maru, p1 ) && !attrL( maru, p1 ) && !attrR( maru, p2 ) && !attrL( maru, p2 ) && !attrR( maru, m1 ) && !attrL( maru, m1 ) && !attrR( maru, m2 ) && !attrL( maru, m2 ) && !attrR( maru, m3 ) && !attrL( maru, m3 ) ) {
				maru.y += STEP;  WaitTimer(WT);
			}
		} //pro4ie pomehi			
	}	
	}
	//play = 0; if cargo stopped?----------------------------------------------------------------------------------------------------------------------------------
	

	//magnets
	//DrawCircle( p1.x, p1.y, GRID/2-1, colR, FALSE, 2 );
	LoadGraphScreen( p1.x-STEP+1, p1.y-STEP+1, "media/bPlus.png", TRUE );
	//DrawCircle( p2.x, p2.y, GRID/2-2, colR, FALSE, 2 );
	LoadGraphScreen( p2.x-STEP+1, p2.y-STEP+1, "media/bPlus.png", TRUE );
	//DrawCircle( m1.x, m1.y, GRID/2-1, colB, FALSE, 2 );
	LoadGraphScreen( m1.x-STEP+1, m1.y-STEP+1, "media/bMinus.png", TRUE );
	//DrawCircle( m2.x, m2.y, GRID/2-2, colB, FALSE, 2 );
	LoadGraphScreen( m2.x-STEP+1, m2.y-STEP+1, "media/bMinus.png", TRUE );
	//DrawCircle( m3.x, m3.y, GRID/2-3, colB, FALSE, 2 );
	LoadGraphScreen( m3.x-STEP+1, m3.y-STEP+1, "media/bMinus.png", TRUE );
	if( p1.x==p2.x && p1.y==p2.y){ DrawFormatString( p1.x+STEP/2-3, p2.y+STEP/2-3, colW, ( const TCHAR* )"x2"); }
	if( (m1.x==m2.x&&m1.y==m2.y) && (m1.x==m3.x&&m1.y==m3.y) && (m2.x==m3.x&&m2.y==m3.y) ){DrawFormatString( m1.x+STEP/2-3, m3.y+STEP/2-3, colW, ( const TCHAR* )"x3"); }
	else if (m1.x==m2.x&&m1.y==m2.y) { DrawFormatString( m1.x+STEP/2-3, m2.y+STEP/2-3, colW, ( const TCHAR* )"x2"); }
	else if (m1.x==m3.x&&m1.y==m3.y) { DrawFormatString( m1.x+STEP/2-3, m3.y+STEP/2-3, colW, ( const TCHAR* )"x2"); }
	else if (m2.x==m3.x&&m2.y==m3.y) { DrawFormatString( m2.x+STEP/2-3, m3.y+STEP/2-3, colW, ( const TCHAR* )"x2"); }		


	return 0;
}


clock_t getClTm1( ) {
	return clTm1;
}

static int noTitle = 0;
int getTitle1( ) {	
	return noTitle;
}


int st1_finish( void ) {	
	noTitle = 1;
	return mode_menuDisp; // ok
}

