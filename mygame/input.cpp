/*
	入力ペリフェラル関係
*/

//#include "stdafx.h"
#include "framework.h"

#include "DxLib.h"
#include "input.h" /*入力ペリフェラル*/

#define KEYBOARD_BUFFER_SIZE 256
static char keybufNew[ KEYBOARD_BUFFER_SIZE ];/* Recent Keyboard Status */
static char keybufOld[ KEYBOARD_BUFFER_SIZE ];/* Keyboard Status for before loop */

static char keybufOnState[ KEYBOARD_BUFFER_SIZE ];
static char keybufOffState[ KEYBOARD_BUFFER_SIZE ];

/*
*
* 入力デバイス(キーボード)からの入力を処理する
* メインループの最初に呼ぶ
* 
*/
void inputPeripheralUpdate( void )
{
	int i;
	char state;

	/* keyboard process */
	/* copy buffer to OLD */
	memcpy( keybufOld , keybufNew , sizeof(char)*KEYBOARD_BUFFER_SIZE );
	/* Re-load keyboard status */
	GetHitKeyStateAll( keybufNew );

	/*

		old new	old^new	press	release
		0	0	0		0		0
		0	1	1		1		0
		1	0	1		0		1
		1	1	0		0		0
	*/

	for(i=0;i< KEYBOARD_BUFFER_SIZE;i++)
	{
		state = keybufNew[ i ] ^ keybufOld[ i ];/* keyboard press or release status */
		keybufOnState[ i ] = keybufNew[ i ] & state;/* get keyboard press trigger */
		keybufOffState[ i ] = keybufOld[ i ] & state;/* get keyboard release trigger */
	}

	/*	mice process */
}

/*
* 与えたkeycodeに対応するキーが押された瞬間なら、0以外を返す。
* On Trigger
* Press Trigger
*/
char getKeyboardOnTrigger( int keycode )
{
	if ( keycode < 0 || keycode >= KEYBOARD_BUFFER_SIZE ) {return 0;}
	return keybufOnState[ keycode ];
}

/*
* 与えたkeycodeに対応するキーが離された瞬間なら、0以外を返す。
* Off Trigger
* Release Trigger
*/
char getKeyboardOffTrigger( int keycode )
{
	if ( keycode < 0 || keycode >= KEYBOARD_BUFFER_SIZE ) { return 0; }
	return keybufOffState[ keycode ];
}

/*
* 与えたkeycodeに対応するキーの状態を返す。
* 押されていれば、0以外を返す。
* 
*/
char getKeyboardState( int keycode )
{
	if ( keycode < 0 || keycode >= KEYBOARD_BUFFER_SIZE ) { return 0; }
	return keybufNew[ keycode ];
}
