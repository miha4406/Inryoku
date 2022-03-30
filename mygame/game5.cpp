// miniWinGame1.cpp : アプリケーションのエントリ ポイントを定義します。
//
// Project -> Property -> 全般 -> 文字セット -> マルチバイト文字セットを使用する


#include "stdafx.h"
#include "DxLib.h"
#include "mode.h" //モード設定
#include "input.h"//入力ペリフェラル

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[ MAX_LOADSTRING ];                  // タイトル バーのテキスト
WCHAR szWindowClass[ MAX_LOADSTRING ];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass( HINSTANCE hInstance );
BOOL                InitInstance( HINSTANCE, int );
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
INT_PTR CALLBACK    About( HWND, UINT, WPARAM, LPARAM );


int count = 0;
int mouseX = 0;//マウス座標
int mouseY = 0;//マウス座標

int APIENTRY wWinMain( _In_ HINSTANCE hInstance,
					   _In_opt_ HINSTANCE hPrevInstance,
					   _In_ LPWSTR    lpCmdLine,
					   _In_ int       nCmdShow ) {
	UNREFERENCED_PARAMETER( hPrevInstance );
	UNREFERENCED_PARAMETER( lpCmdLine );


	// TODO: ここにコードを挿入してください。
	ChangeWindowMode( TRUE );//非全画面にセット
	SetGraphMode( sWid, sHei, 32 );//画面サイズ指定
	SetOutApplicationLogValidFlag( FALSE );//Log.txtを生成しないように設定

	SetUseCharCodeFormat( DX_CHARCODEFORMAT_UTF8 );
	if ( DxLib_Init( ) == 1 ) { return -1; }//初期化に失敗時にエラーを吐かせて終了


	// メイン ループ:
	int ext;
	while ( ProcessMessage( ) == 0 ) {
		ClearDrawScreen( );//裏画面消す
		SetDrawScreen( DX_SCREEN_BACK );//描画先を裏画面に
		inputPeripheralUpdate( );  //on pressed state?
		//
		//ここに毎フレーム呼ぶ処理を書く
		//

		ext = modeCtrl( 0 );

#if 0		
		DrawCircle( 100, 100, 30, GetColor( 255, 0, 0 ), 0 );
		DrawCircle( 300, 100, 30, GetColor( 0, 255, 0 ), 1 );
		DrawBox( 50, 300, 100, 400, GetColor( 0, 0, 255 ), 1 );
		DrawLine( 200, 300, 300, 400, GetColor( 255, 255, 255 ), 1 );


		count++;

		DrawFormatString( 100, 100, GetColor( 255, 255, 255 ), ( const TCHAR* )"frame %d", count );
		if ( count & 1 ) {
			DrawFormatString( 100, 120, GetColor( 255, 255, 255 ), ( const TCHAR* )"sec %d", count / 60 );
		}

		GetMousePoint( &mouseX, &mouseY ); //マウス座標更新

		//左上に文字（マウスの座標）を描画
		TCHAR* fmt3 = ( TCHAR* )"MX:%3d MY:%3d";
		DrawFormatString( 20, 50, GetColor( 255, 255, 255 ), fmt3, mouseX, mouseY );
#endif

		ScreenFlip( );//裏画面を表画面にコピー    
		if ( ext ) { break; }
	}

	DxLib_End( );
	return ( int )FALSE;
}




LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {
	switch ( message ) {
	case WM_COMMAND:
	{
	}
	break;
	case WM_PAINT:
	{
	}
	break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return 0;
}

