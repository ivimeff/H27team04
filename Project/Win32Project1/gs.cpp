//=====================================================================
//	暫定 3Dライブラリ
//
//	ファイル名	【 gs.cpp 】	Ver 2.3
//
//	□ 履歴
//		----------- Ver  2.3 ------------------------------------------
//		2012.4.8	GsMessageを追加。Start+Sellectで終了
//		----------- Ver  2.2 ------------------------------------------
//		2011.11.10	gs.hにC++を使用した時の不備があったので変更しました。
//		----------- Ver  2.1 ------------------------------------------
//		2011.09.21	gsGetJoyPadStateの関数名を変更しました。
//		----------- Ver  2.0 ------------------------------------------
//		2011.09.17	サウンド（WAVのみ）とパッド入力を追加した。
//		----------- Ver  1.8.1 ------------------------------------------
//		2011.06.21	gsDraw2DExを作成
//		----------- Ver  1.8 --------------------------------------------
//		2011.05.03	いくつかの関数が名前がD3だったのでgsへ修正した
//		----------- Ver  1.7.1 ------------------------------------------
//		2010.05.28	画像の回転方向を左回りとした
//					gsDraw2DEx()  gsDraw2DPartEx()
//		2010.05.09	D3DCOLOR型 を gsColor型 とした
//		2010.05.09	学校ライブラリのファイル名を変更した
//					main.h ⇒ gs.h		main.cpp ⇒ gs.cpp
//					関数名で，D3～ を gs～ と変更し，統一感をもたせた
//		2010.05.09	dxerr9.h, dxerr9.libを dxerr.h, dxerr.libに変更した
//		----------- Ver  1.7 ------------------------------------------
//		2009.12.21	画像の2D描画の際，画像がずれるバグを修正した
//		2009.12.21	画像の2D描画の際，頂点カラーを指定できるようにした
//					D3Draw2D, D3Draw2DPart の最後の引数が頂点カラーとなる
//		2009.09.09	mciコマンドによるサウンド再生処理を追加した
//					gsSound 型の追加
//					gsSoundOpen(), gsSoundClose()
//					gsSoundPlay(), gsSoundStop()
//					gsSoundisPlaying()
//		2009.08.22	ボーンつき Xファイルに対応した(α版:調査中)
//		2009.07.30	デバッグ用文字列を出力ウィンドウに表示する
//					gsDebugPrintf() の追加 (Debugバージョンのみ有効)
//		2009.07.30	円の描画関数	D3Draw2DCircle() の追加
//					グローバル変数 g_Sinf[360], g_Cosf[360] の追加
//		2009.07.28	長方形描画関数	D3Draw2DRectangle() の追加
//		2009.07.28	直線描画関数	D3Draw2DLine() の追加
//		2009.07.23	gsDrawPrintfShadow() の追加
//					通常の文字列表示では，背景の色により，見づらい場合
//					に使用する．※黒い影をつける
//		2009.06.23	テキスト表示の際のフォントサイズ，フォントを
//					変更できる関数 gsSetFont() を追加した
//		2009.06.11	キーの状態を調べる関数 gsKeyState() を追加した
//					enum型 GSKC_ → GSKS_ に変更した
//		2009.06.10	gsKeyCheck マクロを追加した
//					GSKEYCHECK は, 削除した
//		2009.06.10	LPDIRECT3DTEXTURE9型を gsTexture型とした
//		2009.06.10	D3Draw2D() の引数で, z座標を デフォルトで 0 とした
//					同時に,　Zバッファを無効化, 自動化を行うようにした
//		2009.06.07	gsDrawPrintf() の追加
//		2009.06.07	ウィンドウの大きさをマクロ化
//					幅:GS_WINDOW_WIDTH  高さ:GS_WINDOW_HEIGHT
//
//=====================================================================

//---------------------------------------------------------------------
//	■インクルード
//---------------------------------------------------------------------
#include "gs.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include <cstdio>

//---------------------------------------------------------------------
//	■マクロ
//---------------------------------------------------------------------
#define APP_NAME "MAIN"

//---------------------------------------------------------------------
//	■関数プロトタイプ宣言
//---------------------------------------------------------------------

// ゲーム側の関数の宣言
void	GameInit(void);
void	GameLoop(void);
void	GameTerm(void);

void	ShowConsole();//★ デバッグ用宣言(削除可)

// static 関数の宣言
static	void	_gsKeyStateUpdate();
static	void	_gsDraw2DPart(gsTexture texture, float x, float y, float z, float x1, float y1, int xsize, int ysize);
static	void	_GameAppInit();

///////////////////////////////////////////////////////////////////////
// アニメーション付きメッシュ関係

// ボーン変換行列の設定
static	HRESULT	_gsInitBoneMatrics(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrame);
static	HRESULT	_gsInitBoneMatricsOnMesh(LPD3DXFRAME pFrameRoot,LPD3DXMESHCONTAINER pMeshContainerBase);

// ボーン変換行列の更新
static	void	_gsUpdateBoneMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
static	void	_gsDrawFrame( LPD3DXFRAME pFrame );
static	void	_gsDrawMeshContainer( LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase );


//---------------------------------------------------------------------
//	■グローバル変数
//---------------------------------------------------------------------
static	LPDIRECT3D9			g_pD3D        = NULL;	// Direct3D
static	LPDIRECT3DDEVICE9	g_pd3dDevice  = NULL;	// Direct3D Device
static	D3DCAPS9			g_d3dcaps;				// Direct3D Device 性能
static	bool				g_bActive = false;		// アプリが利用可能か?

static HINSTANCE g_hInst;
static HWND      g_hWnd;

int gMsgMode;
char gMsgStr[100];

// DirectInput情報
SYSINPUT            g_sysJoy;
int					g_JoystickCount;
int					g_JoystickMax;
int					g_NowNum;

// キーボードの押下状態
static	BYTE	_KeyBuffer[2][256];
static	int		_KeyBuffNo = 0;

// DirectSound関連
LPDIRECTSOUND8		 g_lpDirectSound    = NULL;
LPDIRECTSOUNDBUFFER	 g_lpPrimaryBuffer  = NULL;


// 時間制御
static	DWORD	g_oldTime;

// sin cos 
float	g_Sinf[360];		// sin 0°～ cos 359°の値を保持
float	g_Cosf[360];		// cos 0°～ cos 359°の値を保持


//=====================================================================
//	メイン処理
//=====================================================================

//---------------------------------------------------------------------
//	■Windows メイン
//---------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
#if defined(DEBUG) | defined(_DEBUG)
  //  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

#ifdef	_DEBUG					// _DEBUG モード ⇒ ウィンドウモード
	bool WindowMode = true;
#else							// _RELESEモード ⇒ フルスクリーンモード
	bool WindowMode = false;
#endif

	// メッセージ用
	gMsgMode=0;

    // ウィンドウの設定
    WNDCLASSEX wc = 
	{
		sizeof(WNDCLASSEX), 
		CS_CLASSDC, 
		gsMsgProc, // コールバック関数の指定
		0L, 0L,
		GetModuleHandle(NULL), NULL, 
		LoadCursor(NULL, IDC_ARROW), // カーソルの指定
		NULL, NULL,
		APP_NAME, NULL
	};

    RegisterClassEx( &wc );

	ShowConsole();//★ デバッグ用宣言(削除可)

	g_hInst = hInst;

    // ウィンドウの作成
    g_hWnd = CreateWindow( 
		APP_NAME, "ゲーム教材　日本工学院",
		WS_POPUP | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, 
        //WS_OVERLAPPEDWINDOW, 
		100, 100,						// ウィンドウの表示位置
		GS_WINDOW_WIDTH, GS_WINDOW_HEIGHT,	// ウィンドウの大きさ
		GetDesktopWindow(), NULL, wc.hInstance, NULL );

	// しかし、外枠などを含めたサイズなので、
	// ウィンドウサイズを再設定する
	RECT	rect;
	int		ww, wh;
	int		cw , ch;
	 
	// クライアント領域の外の幅を計算
	GetClientRect( g_hWnd , &rect );
	cw = rect.right  - rect.left;
	ch = rect.bottom - rect.top;
	
	// ウィンドウ全体の横幅の幅を計算
	GetWindowRect( g_hWnd , &rect );
	ww = rect.right  - rect.left;
	wh = rect.bottom - rect.top;
	ww = ww - cw;
	wh = wh - ch;
	 
	// ウィンドウサイズの再計算
	ww = GS_WINDOW_WIDTH  + ww;
	wh = GS_WINDOW_HEIGHT + wh;
	 
	// ウィンドウサイズの再設定
	SetWindowPos(g_hWnd, HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE);

	// フルスクリーンモードであれば，マウスカーソルを消去する	// 2009.06.23 追加
	if ( !WindowMode )
	{
		while ( ShowCursor(false) > 0 );
	}

	// ゲームアプリケーション 初期化
	_GameAppInit();

    // Direct3D初期化
	gsInitD3D( g_hWnd, WindowMode );

	// DirectSound初期化
	InitDirectSound();

    // デフォルトフォント初期化
	gsInitFont();

	// DirectInput初期化
	InitJoyPad();

	// ウィンドウの表示
	ShowWindow( g_hWnd, SW_SHOWDEFAULT );
	UpdateWindow( g_hWnd );

	g_bActive = true;

	// ゲーム初期化
	GameInit();

    // メッセージループ
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
    while( msg.message!=WM_QUIT )
    {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
		}
        else
		{
			if (g_bActive)
			{
				_gsKeyStateUpdate();	// キーの押下状態の更新
				gsRender();
			}
		}

		if  (gsGetJoyPadState(0,JOYPAD_BUTTON10)==GSKS_PRESS &&
				gsGetJoyPadState(0,JOYPAD_BUTTON9)==GSKS_PRESS)
		{
			break;
		}
    }

	// ゲーム終了
	GameTerm();

	g_bActive = false;

	// フォントの解放
	gsReleaseFont();

	// システムの解放
    gsCleanup();

	// 登録の解除
    UnregisterClass( APP_NAME, wc.hInstance );

    return 0;
}


//---------------------------------------------------------------------
//	コールバック関数
//---------------------------------------------------------------------
LRESULT WINAPI gsMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	// メッセージにより処理
    switch( msg )
    {
	case WM_DESTROY:				// 右上の×で終了なら、解放を呼び出して終了する。
		g_bActive = false;
		PostQuitMessage( 0 );
        return 0;
			
	case WM_KEYDOWN:				// キーが押された
		if ( wParam == VK_ESCAPE )	// ESC キーが押されたらゲームアプリを終了する
		{
			g_bActive = false;
			PostQuitMessage(0);
		}
		return 0;
    }

	// それ以外の処理はシステムに任せる
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

//---------------------------------------------------------------------
//	■ゲームアプリケーション初期化
//---------------------------------------------------------------------
void	_GameAppInit()
{
	// sin, cos の値をあらかじめ算出しておく
	// (円の描画 (gsDraw2DCircle)で利用している)
	for (int i=0; i<360; i++)
	{
		g_Sinf[i] = sinf( D3DXToRadian(i) );
		g_Cosf[i] = cosf( D3DXToRadian(i) );
	}
}



//---------------------------------------------------------------------
//	メッセージ表示
//---------------------------------------------------------------------
void	gsMessage(char str[])
{
	int i;

	gMsgMode=1;

	i=0;
	while(str[i]!='\0')
	{
		gMsgStr[i] = str[i];
		i++;
	}
	gMsgStr[i]='\0';
}


//---------------------------------------------------------------------
//	Direct3Dの初期化
//---------------------------------------------------------------------
void gsInitD3D( HWND hWnd, bool WindowMode )
{
	HRESULT		rc;		// リターンコード

    // Direct3D オブジュクト生成
    g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

    // 構造体の設定
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferCount  = 1;
	
	D3DDISPLAYMODE d3ddm;
    g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

	// ウィンドウモードかどうか によりパラメ－タを変える
	if ( WindowMode )
	{
		d3dpp.Windowed = TRUE;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	}
	else
	{
		d3dpp.Windowed = FALSE;
  		d3dpp.BackBufferWidth  = GS_WINDOW_WIDTH;
		d3dpp.BackBufferHeight = GS_WINDOW_HEIGHT;  
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;	// vsync を待つ
//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	// ３Ｄ用
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	///////////////////////////////////////////////////////////////////////
	// Direct3D デバイス生成

	// 描画:HAL,  頂点処理:HARDWARE で生成
	rc =	g_pD3D->CreateDevice(  D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
								   D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice );
	if ( SUCCEEDED(rc) )
			gsDebugPrintf( "☆gsInitD3D : Direct3D デバイス ⇒ 描画:HAL 頂点処理:HARDWARE で生成\n" );

	// 上記が失敗なら，描画:HAL，頂点処理:SOFTWARE
	if ( FAILED( rc ) )
	{
		rc = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
								   D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice );
		if ( SUCCEEDED(rc) )
			gsDebugPrintf( "☆gsInitD3D : Direct3D デバイス ⇒ 描画:HAL 頂点処理:SOFTWARE で生成\n" );
	}

	// 上記が失敗なら，描画:REF，頂点処理:HARDWARE
	if ( FAILED( rc ) )
	{
		rc = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
								   D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice );
		if ( SUCCEEDED(rc) )
			gsDebugPrintf( "☆gsInitD3D : Direct3D デバイス ⇒ 描画:REF 頂点処理:HARDWARE で生成\n" );
	}

	// 上記が失敗なら，描画:REF，頂点処理:SOFTWARE
	if ( FAILED( rc ) )
	{
		rc = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
								   D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice );
		if ( SUCCEEDED(rc) )
			gsDebugPrintf( "☆gsInitD3D : Direct3D デバイス ⇒ 描画:REF 頂点処理:SOFTWARE で生成\n" );
	}

	// ライティングモードを OFF にする
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// 標準的な色の設定
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState( D3DRS_BLENDOP,	D3DBLENDOP_ADD );
	g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,	D3DBLEND_SRCALPHA );
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,	D3DBLEND_INVSRCALPHA );

	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,	 D3DTOP_MODULATE);
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE	);	// 1つめの引数をテクスチャとする
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE	);	// 2つめの引数を補間ディフューズ色とする

	// Zバッファをオンにする
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	// デバイスの性能を取っておく
	g_pd3dDevice->GetDeviceCaps( &g_d3dcaps );
}


//---------------------------------------------------------------------
// 使用したオブジェクトの解放
//---------------------------------------------------------------------
void gsCleanup()
{
    GS_SAFE_RELEASE( g_pd3dDevice );	// Direct3D デバイス
    GS_SAFE_RELEASE( g_pD3D	);			// Direct3D
}


//---------------------------------------------------------------------
//	レンダリング（描画）とゲーム処理呼び出し
//---------------------------------------------------------------------
void gsRender()
{
    // バックバッファとＺバッファを黒でクリア
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

    // シーン開始
    g_pd3dDevice->BeginScene();

	// ジョイパッド情報を更新
	Update_JoyPadInfo();

	if (gMsgMode==0)
	{
		// ゲームループを呼び出す(ユーザーが定義)
		GameLoop();
	}
	else
	{
		// メッセージ表示
		gsDrawText(10,10,gMsgStr);
	}

	// シーン終了
    g_pd3dDevice->EndScene();

    // バックバッファをディスプレイに表示
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}


//=====================================================================
//	共通処理
//=====================================================================

//---------------------------------------------------------------------
//	■キーの状態取得
//		int gsKeyState( UINT vk );
//
//		引数 [in]	vk	: 調べるキーの仮想キーコード ( 範囲 0 ～ 255 )
//
//		戻り値		GSKS_RELEASE	: 離されている	= 0
//					GSKS_DOWN		: 押下直後		= 1
//					GSKS_PRESS		: 押しっぱなし	= 2
//					GSKS_UP			: 離した直後	= 3
//---------------------------------------------------------------------
int gsKeyState( UINT vk )
{
	// 仮想キーコードが　0～255 の範囲外なら, GSKC_RELEASE を返す
	if ( vk < 0 || vk > 255 )
	{
		return GSKS_RELEASE;
	}

	bool	bOldStat = ((_KeyBuffer[ 1 - _KeyBuffNo ][ vk ] & 0x80) != 0);
	bool	bNowStat = ((_KeyBuffer[     _KeyBuffNo ][ vk ] & 0x80) != 0);

	if ( !bOldStat &&  !bNowStat ) return GSKS_RELEASE;
	if ( !bOldStat &&   bNowStat ) return GSKS_DOWN;
	if (  bOldStat &&   bNowStat ) return GSKS_PRESS;
	if (  bOldStat &&  !bNowStat ) return GSKS_UP;

	return GSKS_RELEASE;	// (起こりえない)
}


//---------------------------------------------------------------------
//	■キーの状態を更新する
//		static	void _gsKeyStateUpdate();
//
//		引数	なし
//		戻り値	なし
//
//		解説)	キー状態を更新する. 以下のバッファを更新する．
//				static	BYTE	_KeyBuffer[2][256];
//				static	int		_KeyBuffNo = 0;
//---------------------------------------------------------------------
static	void _gsKeyStateUpdate()
{
	_KeyBuffNo = 1 - _KeyBuffNo;
	GetKeyboardState( _KeyBuffer[_KeyBuffNo] );
}

//---------------------------------------------------------------------
//	■テクスチャを読み込む
//		void gsLoadTexture(gsTexture *texture,  char *str, UINT colorKey)
//
//		引数 [out]	texture		: テクスチャを管理する変数へのポインタ
//		引数 [in]	str			: テクスチャのファイル名
//		引数 [in]	colorKey	: 透過させる色 (0xaarrggbb)
//
//		戻り値	なし
//---------------------------------------------------------------------
void gsLoadTexture(gsTexture *pTexture,  char *str, gsColor colorKey)
{
	// テクスチャがすでに割り当てられているなら，解放する
	// ローカル変数の場合，NULL が設定されていない可能性あり ※危険！
	//if ( *texture != NULL )
	//{
	//	D3ReleaseTexture( *texture );
	//	*texture = NULL;
	//	OutputDebugString( "以前のテクスチャを解放した\n" );
	//}

	//	D3DXGetImageInfoFromFile 関数で，ファイル中の画像解像度を得ることができる．
	//	このことにより，画像サイズが 2のべき乗である必要がなくなる．
	//	より柔軟性のある，画像の読み込みが可能となる．

	// テクスチャの読み込み
	if ( FAILED( D3DXCreateTextureFromFileEx(
		g_pd3dDevice,				// Direct3D デバイス
		str,						// ファイル名
		D3DX_DEFAULT, D3DX_DEFAULT,	// 生成したいテクスチャの幅と高さ
		1,							// ミップレベルの数
		0,							// テクスチャの使用方法
		D3DFMT_UNKNOWN,				// テクスチャフォーマット
		D3DPOOL_MANAGED,			// テクスチャのメモリ管理方法
		D3DX_FILTER_NONE,			// イメージをフィルタリングする方法
		D3DX_DEFAULT,				// ミップマップレベルをフィルタリングする方法
		colorKey,					// 透過する色、（0:カラーキーを無効とする）
		0,							// ファイル内データの取得 (0:必要なし)
		0,							// パレット情報 (0:必要なし)
		pTexture)))					// テクスチャ用ポインタへのポインタ
	{
		MessageBox(NULL, "テクスチャファイルがありません\n終了します", str, MB_OK);
		PostQuitMessage(0);
	}	
}

//---------------------------------------------------------------------
//	■テクスチャを解放する
//		void D3ReleaseTexture(gsTexture texture);
//		
//		引数 [in]	texture	: 解放するテクスチャ
//		戻り値		なし
//---------------------------------------------------------------------
void	gsReleaseTexture(gsTexture texture)
{
	GS_SAFE_RELEASE( texture );
}


//---------------------------------------------------------------------
//	■標準的な色の合成の設定
//		void D3SetNormalColor(void);
//
//		引数		なし
//		戻り値		なし
//---------------------------------------------------------------------
void	gsSetNormalColor()
{
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,	D3DBLEND_INVSRCALPHA );
}

//---------------------------------------------------------------------
//	加算的な色の合成の設定（爆発マークなど）
//---------------------------------------------------------------------
void	gsSetAddColor()
{
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,	D3DBLEND_ONE );
}


//=====================================================================
//	2D処理
//=====================================================================

//---------------------------------------------------------------------
//	■2D画面のクリア
//		void	gsDraw2DClear (gsColor color);
//
//		引数 [in]	color	: クリアする色
//
//		戻り値		なし
//	
//		解説）	Z バッファもクリアされることに注意されたい
//---------------------------------------------------------------------
void	gsDraw2DClear(gsColor color)
{

    // バックバッファとＺバッファを青でクリア
    g_pd3dDevice->Clear(	0, NULL, 
							D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
							color, 1.0f, 0 );
}

//---------------------------------------------------------------------
//	■2D画像の描画
//		void gsDraw2D(gsTexture texture, int sx, int sy,
//								gsColor cr= GSARGB(255,255,255,255) );
//
//		引数 [in]	texture : テクスチャ
//		引数 [in]	sx, sy	: 表示位置(スクリーン座標)
//					※ 画像の左上のピクセルが (x, y)に対応づけられる
//		引数 [in]	cr		: 頂点カラー
//					※ デフォルト値 GSARGB(255,255,255,255)
//
//		戻り値		なし
//---------------------------------------------------------------------
void	gsDraw2D(gsTexture texture, int sx, int sy, gsColor cr)
{
	// テクスチャのサイズ取得用
	D3DSURFACE_DESC	sd;
	float			xs;
	float			ys;

	// 型変換
	float fx = (float)sx;
	float fy = (float)sy;

	// 絵の大きさの取得
	texture->GetLevelDesc(0, &sd);
	xs = (float)sd.Width;
	ys = (float)sd.Height;

	// 頂点データの準備
	gsTLVertex vertices[] =
	{
		//	    ( x,	 y,		z )	    rhw	  頂点カラー	テクスチャ座標
		{ gsVec3( fx,    fy,    0.0f ), 1.0f, cr,			gsVec2(0.0f, 0.0f) },
		{ gsVec3( fx+xs, fy,    0.0f ), 1.0f, cr,			gsVec2(1.0f, 0.0f) },
		{ gsVec3( fx,    fy+ys, 0.0f ), 1.0f, cr,			gsVec2(0.0f, 1.0f) },
		{ gsVec3( fx+xs, fy+ys, 0.0f ), 1.0f, cr,			gsVec2(1.0f, 1.0f) },
	};

	// 悪影響が出るので中止	2011.5.3
	// 画像を適確に描画するためのスクリーン座標の補正	2009.12.21
	//for (int i=0; i<4; i++)
	//{
	//	vertices[i].pos.x -= 0.5f;
	//	vertices[i].pos.y -= 0.5f;
	//}

	// 描画
	gsSetZBufferOff();	// Z バッファへの書き込みはしない
	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,		// プリミティブのタイプ
		2,							// プリミティブの数
		vertices,					// 頂点データへのポインタ
		sizeof(gsTLVertex) );		// 各頂点データへのストライド(バイト単位)
	gsSetZBufferOn();	// Z バッファへの書き込みをする
}

//---------------------------------------------------------------------------------------
//	■ 絵の描画
//		void	gsDraw2DPartEx(gsTexture texture, int sx, int sy, int sw, int sh,
//							int tx, int ty, int tw, int th, float angle, gsColor cr );
//
//		引数 [in]	texture : テクスチャ
//		引数 [in]	sx, sy	: 表示位置(スクリーン座標)
//		引数 [in]	sw, sh	: テクスチャの縦横のサイズ
//						※ 0のときは画像のサイズ
//		引数 [in]	tx, ty	: 切り取るテクスチャ部分の左上の座標
//		引数 [in]	tw, th	: 切り取るテクスチャの横幅と高さ
//		引数 [in]	color	: 頂点カラー
//		引数 [in]	angle	: 回転角、ラジアン						
//
//		戻り値		なし
//---------------------------------------------------------------------------------------
void	gsDraw2DPartEx(gsTexture texture, int sx, int sy, int sw, int sh, 
					   int tx, int ty, int tw, int th, float angle, gsColor cr)
{
	float			sw2, sh2;
	D3DSURFACE_DESC	sd;
	float xs, ys;
	float nx1, ny1, nx2, ny2;
	int i;

	// テクスチャのサイズの取得
	texture->GetLevelDesc(0, &sd);
	xs = (float)sd.Width;
	ys = (float)sd.Height;

	// 頂点データの作成
	gsTLVertex vertices[4];

	// 半透明とzの設定
	for ( i =0; i < 4; i++ )
	{
		vertices[i].rhw		= 1.0f;
		vertices[i].color	= cr;
		vertices[i].pos.z	= 0.0f;
	}

	// 絵の大きさの取得
	if ( sw == 0 )
	{
		sw = tw;
	}
	if ( sh == 0 )
	{
		sh = th;
	}

	// 拡大・縮小と回転処理
	sw2 = sw / 2.0f;
	sh2 = sh / 2.0f;

	float xcosf = sw2 * cosf( angle );
	float xsinf = sw2 * sinf( angle );
	float ysinf = sh2 * sinf( angle );
	float ycosf = sh2 * cosf( angle );

	vertices[0].pos.x = (float)( sx +  ( -xcosf ) - (  ysinf ));
	vertices[0].pos.y = (float)( sy - (( -xsinf ) + (  ycosf )));
	vertices[1].pos.x = (float)( sx +  (  xcosf ) - (  ysinf ));
	vertices[1].pos.y = (float)( sy - ((  xsinf ) + (  ycosf )));	
	vertices[2].pos.x = (float)( sx +  ( -xcosf ) - ( -ysinf ));
	vertices[2].pos.y = (float)( sy - (( -xsinf ) + ( -ycosf )));
	vertices[3].pos.x = (float)( sx +  (  xcosf ) - ( -ysinf ));
	vertices[3].pos.y = (float)( sy - ((  xsinf ) + ( -ycosf )));

	// 悪影響が出るので中止	2011.5.3
	// 画像を適確に描画するためのスクリーン座標の補正	2009.12.21
	//for (i=0; i<4; i++)
	//{
	//	vertices[i].pos.x -= 0.5f;
	//	vertices[i].pos.y -= 0.5f;
	//}

	// テクスチャ座標の設定
	nx1 = (float) tx	   / xs;
	ny1 = (float) ty	   / ys;
	nx2 = (float)(tx + tw) / xs;
	ny2 = (float)(ty + th) / ys;

	vertices[0].uv = gsVec2(nx1, ny1);
	vertices[1].uv = gsVec2(nx2, ny1);
	vertices[2].uv = gsVec2(nx1, ny2);
	vertices[3].uv = gsVec2(nx2, ny2);

	// 描画
	gsSetZBufferOff();	// Z バッファへの書き込みはしない	2009.07.23 追加

	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,			// プリミティブのタイプ
		2,								// プリミティブの数
		vertices,						// 頂点データへのポインタ
		sizeof(gsTLVertex) );		// 各頂点データへのストライド（バイト単位）

	gsSetZBufferOn();	// Z バッファへの書き込みをする		2009.07.23 追加
}

//---------------------------------------------------------------------
//	■ 絵の描画
//		void gsDraw2D(gsTexture texture, int sx, int sy,
//							int tx, int ty, int tw, int th,
//							gsColor cr= GSARGB(255,255,255,255) );
//
//		引数 [in]	texture : テクスチャ
//		引数 [in]	sx, sy	: 表示位置(スクリーン座標)
//						※ 画像の左上のピクセルが (x, y)に対応づけられる
//		引数 [in]	tx, ty	: 切り取るテクスチャ部分の左上の座標
//		引数 [in]	tw, th	: 切り取るテクスチャの横幅と高さ
//		引数 [in]	cr		: 頂点カラー
//						※ デフォルト値 GSARGB(255,255,255,255)
//
//		戻り値		なし
//---------------------------------------------------------------------
void	gsDraw2DPart(gsTexture texture, int sx, int sy,
					 int tx, int ty, int tw, int th, gsColor cr )
{
	D3DSURFACE_DESC	sd;
	float xs, ys;
	float nx1, ny1, nx2, ny2;
	int i;

	// テクスチャのサイズの取得
	texture->GetLevelDesc(0, &sd);
	xs = (float)sd.Width;
	ys = (float)sd.Height;

	// 頂点データの作成
	gsTLVertex vertices[4];

	// 半透明とzの設定
	for ( i =0; i < 4; i++ )
	{
		vertices[i].rhw		= 1.0f;
		vertices[i].color	= cr;
		vertices[i].pos.z	= 0.0f;
	}
	
	// 描画位置の設定
	vertices[0].pos.x = (float)sx;			vertices[0].pos.y = (float)sy;
	vertices[1].pos.x = (float)sx + tw;		vertices[1].pos.y = (float)sy;
	vertices[2].pos.x = (float)sx;			vertices[2].pos.y = (float)sy + th;
	vertices[3].pos.x = (float)sx + tw;		vertices[3].pos.y = (float)sy + th;

	// 悪影響が出るので中止	2011.5.3
	// 画像を適確に描画するためのスクリーン座標の補正	2009.12.21
	//for (i=0; i<4; i++)
	//{
	//	vertices[i].pos.x -= 0.5f;
	//	vertices[i].pos.y -= 0.5f;
	//}

	// テクスチャ座標の設定
	nx1 = (float) tx	   / xs;
	ny1 = (float) ty	   / ys;
	nx2 = (float)(tx + tw) / xs;
	ny2 = (float)(ty + th) / ys;

	vertices[0].uv = gsVec2(nx1, ny1);
	vertices[1].uv = gsVec2(nx2, ny1);
	vertices[2].uv = gsVec2(nx1, ny2);
	vertices[3].uv = gsVec2(nx2, ny2);

	// 描画
	gsSetZBufferOff();	// Z バッファへの書き込みはしない	2009.07.23 追加

	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,			// プリミティブのタイプ
		2,								// プリミティブの数
		vertices,						// 頂点データへのポインタ
		sizeof(gsTLVertex) );		// 各頂点データへのストライド（バイト単位）

	gsSetZBufferOn();	// Z バッファへの書き込みをする		2009.07.23 追加
}


//---------------------------------------------------------------------
//	■テクスチャの幅（ピクセル）を取得する
//		int	 gsGetTextureWidth (gsTexture Texture);
//
//		引数 [in]	texture : 調べるテクスチャ
//		戻り値		幅を返す
//					※ texture が無効(=NULL)なら、0を返す
//---------------------------------------------------------------------
int	 gsGetTextureWidth (gsTexture texture)
{
	D3DSURFACE_DESC	sd;
	int				size;

	if ( texture )
	{
		// テクスチャのサイズの取得
		texture->GetLevelDesc(0, &sd);
		size = (int)sd.Width;

		return size;
	}

	return 0;
}


//---------------------------------------------------------------------
//	■テクスチャの高さ（ピクセル）を取得する
//		int	 gsGetTextureHeight(gsTexture texture);
//
//		引数 [in]	texture : 調べるテクスチャ
//		戻り値		高さを返す
//					※ texture が無効(=NULL)なら、0を返す
//---------------------------------------------------------------------
int	 gsGetTextureHeight(gsTexture texture)
{
	D3DSURFACE_DESC	sd;
	int				size;

	if ( texture )
	{
		// テクスチャのサイズの取得
		texture->GetLevelDesc(0, &sd);
		size = (int)sd.Height;

		return size;
	}

	return 0;
}

//---------------------------------------------------------------------
//	■ 指定された 2点間を結ぶ 直線を描画する
//		void	gsDraw2DLine( int x1, int y1, int x2, int y2, gsColor color);
//
//		引数 [in]	x1, y1	: 直線の始点座標 (スクリーン座標)
//		引数 [in]	x2, y2	: 直線の終点座標 (スクリーン座標)
//		引数 [in]	color	: 直線の色
//		戻り値		なし
//---------------------------------------------------------------------
void	gsDraw2DLine( int x1, int y1, int x2, int y2, gsColor color)
{
	//	頂点データの作成
	gsTLVertex	vertices[2] = {
		//			( x,		y,		z  )	rhw		頂点色	テクスチャ座標
		{ gsVec3((float)x1, (float)y1, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
		{ gsVec3((float)x2, (float)y2, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
	};

	gsSetZBufferOff();	// Z バッファへの書き込みはしない
	g_pd3dDevice->SetTexture( 0, NULL );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_LINELIST,			// プリミティブのタイプ
		1,						// プリミティブの数
		vertices,				// 頂点データへのポインタ
		sizeof(gsTLVertex) );	// 各頂点データへのストライド（バイト単位）
	gsSetZBufferOn();	// Z バッファへの書き込みをする
}

//---------------------------------------------------------------------
//	■ 指定された 2点を対角線とする 長方形を描画する
//		void	gsDraw2DRectangle(
//					int x1, int y1, int x2, int y2,
//					gsColor color, bool bFillMode = false );
//
//		引数 [in]	x1, y1		: 直線の始点座標 (スクリーン座標)
//		引数 [in]	x2, y2		: 直線の終点座標 (スクリーン座標)
//		引数 [in]	color		: 直線の色
//		引数 [in]	bFillMode	: 塗りつぶしモード
//									true:塗りつぶす false:塗りつぶさない
//		戻り値		なし
//---------------------------------------------------------------------
void	gsDraw2DRectangle(int x1, int y1, int x2, int y2, gsColor color, bool bFillMode)
{
	//	頂点データの作成
	gsTLVertex	vertices[5] = {
		//			( x,		y,		z  )	rhw		頂点色	テクスチャ座標
		{ gsVec3((float)x1, (float)y1, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
		{ gsVec3((float)x2, (float)y1, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
		{ gsVec3((float)x2, (float)y2, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
		{ gsVec3((float)x1, (float)y2, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
		{ gsVec3((float)x1, (float)y1, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
	};

	gsSetZBufferOff();	// Z バッファへの書き込みはしない
	g_pd3dDevice->SetTexture( 0, NULL );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );

	if ( bFillMode )
		g_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, vertices, sizeof(gsTLVertex) );
	else
		g_pd3dDevice->DrawPrimitiveUP( D3DPT_LINESTRIP,	  4, vertices, sizeof(gsTLVertex) );

	gsSetZBufferOn();	// Z バッファへの書き込みをする
}

//---------------------------------------------------------------------
//	■ 円を描画する (正 n 角形 のポリゴン版)
//		void	gsDraw2DCircle(int cx, int cy, int r,
//								  gsColor color, bool bFillMode = false);
//
//		引数 [in]	cx, cy		: 円の中心始点座標 (スクリーン座標)
//		引数 [in]	r			: 円の半径 (ピクセル)
//		引数 [in]	color		: 線の色
//		引数 [in]	bFillMode	: 塗りつぶしモード
//									true:塗りつぶす false:塗りつぶさない
//		戻り値		なし
//---------------------------------------------------------------------
void	gsDraw2DCircle(int cx, int cy, int r,  gsColor color, bool bFillMode)
{
	//	頂点データの作成
	gsTLVertex	v[362];
	
	v[0].pos	= gsVec3( (float)cx, (float)cy, 0.0f );
	v[0].rhw	= 1.0f;
	v[0].color	= color;
	v[0].uv		= gsVec2( 0.0f, 0.0f );

	for ( int i=0; i<360; i++ )
	{
		v[i+1].pos	 = gsVec3( cx+g_Cosf[i] * r, (float)cy + g_Sinf[i] * r, 0.0f);
		v[i+1].rhw	 = 1.0f;
		v[i+1].color = color;
		v[i+1].uv	 = gsVec2(0.0f, 0.0f);
	}
	v[361] = v[1];

	// 360角形 の描画
	gsSetZBufferOff();	// Z バッファへの書き込みはしない
	g_pd3dDevice->SetTexture( 0, NULL );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );

	if ( bFillMode )
		g_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 360, &v[0], sizeof(gsTLVertex) );
	else
		g_pd3dDevice->DrawPrimitiveUP( D3DPT_LINESTRIP,	  360, &v[1], sizeof(gsTLVertex) );

	gsSetZBufferOn();	// Z バッファへの書き込みをする
}


//=====================================================================
// 文字フォント処理
//=====================================================================

// フォント関係のグローバル変数
static		LPD3DXFONT		g_pD3DXFont;		// D3DXフォント
static		int				g_nFontSize;		// フォントサイズ
static		char			g_szFontName[32];	// フォント名

//---------------------------------------------------------------------
// フォントの初期化
//---------------------------------------------------------------------
void gsInitFont(void)
{
	// 16ピクセルの高さ，デフォルトフォントの設定
	gsSetFont( 16, "ＭＳ ゴシック" );
}


//---------------------------------------------------------------------
// ■デフォルトフォントのサイズとフォントの設定
//		void gsSetFont(int size, char *szFontName = "ＭＳ ゴシック" );
//
//	引数 [in]	size		: 文字のサイズ (ピクセル単位)
//	引数 [in]	szFontName	: フォント名
//
//	戻り値		なし
//
//	※ フォント名を省略すると "ＭＳ ゴシック" が，選択される
//---------------------------------------------------------------------
void gsSetFont(int size, char *szFontName )
{
	// フォントサイズ, フォント名を取得できるようにとっておく．
	g_nFontSize = size;
	strcpy( g_szFontName, szFontName );

	// フォントの解放
	GS_SAFE_RELEASE( g_pD3DXFont );

	//	D3DXフォント作成
	D3DXFONT_DESC fd;

	fd.Height			= size;
	fd.Width			= 0;
	fd.Weight			= 0;
	fd.MipLevels		= 0;
	fd.Italic			= FALSE;
	fd.CharSet			= SHIFTJIS_CHARSET;
	fd.OutputPrecision	= 0;
	fd.Quality			= 0;
	fd.PitchAndFamily	= FIXED_PITCH;
	strcpy(fd.FaceName, szFontName );
	
	D3DXCreateFontIndirect( g_pd3dDevice, &fd, &g_pD3DXFont);
}


//---------------------------------------------------------------------
//	■2D画像の描画
//		void gsDraw2DEx(gsTexture texture, int sx, int sy,int sw, int sh,
//								gsColor cr= GSARGB(255,255,255,255) );
//
//		引数 [in]	texture : テクスチャ
//		引数 [in]	sx, sy	: 表示位置(スクリーン座標)
//					※ 画像の左上のピクセルが (x, y)に対応づけられる
//		引数 [in]	sw, sh	: テクスチャの縦横のサイズ
//		引数 [in]	cr		: 頂点カラー
//					※ デフォルト値 GSARGB(255,255,255,255)
//
//		戻り値		なし
//---------------------------------------------------------------------
void	gsDraw2DEx(gsTexture texture, int sx, int sy, int sw, int sh, gsColor cr)
{
	float			xs;
	float			ys;

	// 型変換
	float fx = (float)sx;
	float fy = (float)sy;

	// 指定されたサイズを使用
	xs = (float)sw;
	ys = (float)sh;

	// 頂点データの準備
	gsTLVertex vertices[] =
	{
		//	    ( x,	 y,		z )	    rhw	  頂点カラー	テクスチャ座標
		{ gsVec3( fx,    fy,    0.0f ), 1.0f, cr,			gsVec2(0.0f, 0.0f) },
		{ gsVec3( fx+xs, fy,    0.0f ), 1.0f, cr,			gsVec2(1.0f, 0.0f) },
		{ gsVec3( fx,    fy+ys, 0.0f ), 1.0f, cr,			gsVec2(0.0f, 1.0f) },
		{ gsVec3( fx+xs, fy+ys, 0.0f ), 1.0f, cr,			gsVec2(1.0f, 1.0f) },
	};

	// 悪影響が出るので中止	2011.5.3
	// 画像を適確に描画するためのスクリーン座標の補正	2009.12.21
//	for (int i=0; i<4; i++)
//	{
//		vertices[i].pos.x -= 0.5f;
//		vertices[i].pos.y -= 0.5f;
//	}

	// 描画
	gsSetZBufferOff();	// Z バッファへの書き込みはしない
	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,		// プリミティブのタイプ
		2,							// プリミティブの数
		vertices,					// 頂点データへのポインタ
		sizeof(gsTLVertex) );		// 各頂点データへのストライド(バイト単位)
	gsSetZBufferOn();	// Z バッファへの書き込みをする
}



//---------------------------------------------------------------------
// フォントの解放
//---------------------------------------------------------------------
void gsReleaseFont(void)
{
	GS_SAFE_RELEASE( g_pD3DXFont );
}


//---------------------------------------------------------------------
// テキスト（文章）の描画
//---------------------------------------------------------------------
void gsDrawText( int x, int y, char *str )
{
	gsDrawPrintf( x, y, GSRGB(255,255,255), str );
}

//---------------------------------------------------------------------
// 数字の描画
//---------------------------------------------------------------------
void gsDrawNum( int x, int y, int a )
{
	gsDrawPrintf( x, y, GSRGB(255,255,255), "%d", a );	
}

//---------------------------------------------------------------------
//	■出力フォーマット指定可能な文字列の描画	// 2009.06.07 追加
//	　※表示位置，文字色の指定あり．変数の値を表示することができる．
//
//		宣　言)
//			bool gsDrawPrintf(int x, int y, gsColor color, char *szFormat, ...);
//
//		引　数)	x, y		: 表示位置
//				color		: 文字列の色
//				szFormat	: 出力書式
//				...			: 変数の並び
//
//		戻り値)	生成された文字数(終端の null 文字は含まれません)
//				(エラー時:負の値)
//---------------------------------------------------------------------
int	gsDrawPrintf(int x, int y, gsColor color, char *szFormat, ...)
{
	char	szText[1024];	// 描画文字列
	RECT	rect;			// 矩形	
	int		nLength;		// 文字数

	// 文字列の生成
	va_list		va;

	va_start( va, szFormat );
	nLength = vsprintf( szText, szFormat, va);
	va_end( va );

	// 文字列の描画
	SetRect( &rect, x, y, GS_WINDOW_WIDTH, GS_WINDOW_HEIGHT );
	g_pD3DXFont->DrawText( NULL, szText, -1, &rect, DT_LEFT, color );

	return nLength;
}


//---------------------------------------------------------------------
//	■出力フォーマット指定可能な文字列の描画	// 2009.07.23 追加
//	　※表示位置，文字色の指定あり．変数の値を表示することができる．
//	　※まず，フォントサイズにより，適当な大きさの影を描画してから，目的の文字列を描画する．
//
//		宣　言)
//			bool gsDrawPrintfShadow(int x, int y, gsColor color, char *szFormat, ...);
//
//		引　数)	x, y		: 表示位置
//				color		: 文字列の色
//				szFormat	: 出力書式
//				...			: 変数の並び
//
//		戻り値)	生成された文字数(終端の null 文字は含まれません)
//				(エラー時:負の値)
//---------------------------------------------------------------------
int	gsDrawPrintfShadow(int x, int y, gsColor color, char *szFormat, ...)
{
	char		szText[1024];	// 描画文字列
	RECT		rect;			// 矩形	
	int			nLength;		// 文字数
	gsColor		cShadow;		// 影の色

	// 影の色の算出
//	cShadow = ~(color & 0x00ffffff) | 0xff000000;
	cShadow = 0xff000000;

	// 文字列の生成
	va_list		va;

	va_start( va, szFormat );
	nLength = vsprintf( szText, szFormat, va);
	va_end( va );

	// 文字列の描画
	SetRect( &rect, x + g_nFontSize/16, y + g_nFontSize/16, GS_WINDOW_WIDTH, GS_WINDOW_HEIGHT );
	g_pD3DXFont->DrawText( NULL, szText, -1, &rect, DT_LEFT, cShadow );

	SetRect( &rect, x, y, GS_WINDOW_WIDTH, GS_WINDOW_HEIGHT );
	g_pD3DXFont->DrawText( NULL, szText, -1, &rect, DT_LEFT, color	 );

	return nLength;
}


//=====================================================================
//	３Ｄ処理
//=====================================================================

// ３Ｄのカスタム頂点データの構造体		★ 変更必
struct CUSTOMVERTEX3D
{
    FLOAT x, y, z;		// 頂点の座標
    DWORD color;        // 頂点の色
    FLOAT tu, tv;   	// テクスチャ座標
};

// ３ＤのＦＶＦ定義
#define D3DFVF_CUSTOMVERTEX3D (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//---------------------------------------------------------------------
// カメラ位置の設定
// 地面と水平に立つ、目線はＹ軸で回転する
//---------------------------------------------------------------------
void gsSetCamera(float x, float y, float z,float dir)
{

	// カメラの座標設定
	D3DXVECTOR3 vEyePt( x, y, z );

	// カメラの向きの設定
	D3DXVECTOR3 vLookatPt( x+cos(dir), y, z+sin(dir) );

	// カメラの頭の設定（常に頭は上向き）
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );

	// カメラの行列変換を設定する
	D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

	// 視野角、前後のクリッピングを指定する
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 200.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

//---------------------------------------------------------------------
// カリングモードをオフに設定
// カリングモード（ポリゴンの裏面を表示しないモード）をオフにする。
// これにより裏面も表示される。
//---------------------------------------------------------------------
void gsSetCullOff()
{
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
}

//---------------------------------------------------------------------
// カリングモードを左回りのオンに設定
// これにより右回りの表面のみ表示される。
//---------------------------------------------------------------------
void gsSetCullOn()
{
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
}

//---------------------------------------------------------------------
// ライトをオンに設定
// 法線のあるモデルに光を当てて表示する
//---------------------------------------------------------------------
void gsSetLightOn()
{
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}

//---------------------------------------------------------------------
// ライトをオフに設定
// 法線のないポリゴンをテクスチャの色で表示する
//---------------------------------------------------------------------
void gsSetLightOff()
{
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
}

//---------------------------------------------------------------------
// ライトの設定
// x y z 光の方向　（光源の位置ではなく、光の進む方向を指定）
// color rgbで光の色と強さを指定
//---------------------------------------------------------------------
void gsSetLight(float x, float y, float z, gsColor color)
{
	gsSetLightOn();

    D3DXVECTOR3 vecDir;
    D3DLIGHT9	light;
    ZeroMemory( &light, sizeof(D3DLIGHT9) );
    light.Type       = D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r  = 1.0f;
    light.Diffuse.g  = 1.0f;
    light.Diffuse.b  = 1.0f;
    
	vecDir = D3DXVECTOR3( x, y, z );

    D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );
    light.Range       = 1000.0f;
    g_pd3dDevice->SetLight( 0, &light );
    g_pd3dDevice->LightEnable( 0, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

    // 指定した設定したアンビエントカラーをセットする
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, color );
}


//---------------------------------------------------------------------
// zバッファをオンにする
// 通常の表示は、このモード
//---------------------------------------------------------------------
void gsSetZBufferOn()
{
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
}

//---------------------------------------------------------------------
// zバッファをオフにする
// 通常の表示は、このモード
//---------------------------------------------------------------------
void gsSetZBufferOff()
{
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
}


//---------------------------------------------------------------------
// 行列変換の設定
// ＸＹＺの位置とＹ軸で回転を指定
//---------------------------------------------------------------------
void gsSetMatrices(float x, float y, float z, float fAngle)
{
    D3DXMATRIXA16 matWorld;
    D3DXMATRIXA16 mat1;
    D3DXMATRIXA16 mat2;

    D3DXMatrixRotationY( &mat1, fAngle );

	D3DXMatrixTranslation( &mat2, x, y, z );

	matWorld = mat1 * mat2;

	g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
}
//---------------------------------------------------------------------
// 行列変換の設定
// ＸＹＺの位置とＹ軸で回転を指定
// 拡大変換も行う
//---------------------------------------------------------------------
void gsSetMatrices(float x, float y, float z, float fAngle, float scalex, float scaley )
{
    D3DXMATRIXA16 matWorld;
    D3DXMATRIXA16 mat1;
    D3DXMATRIXA16 mat2;
    D3DXMATRIXA16 mat3;

    D3DXMatrixRotationY( &mat1, fAngle );

	D3DXMatrixScaling( &mat2, scalex ,scaley, 1.0 );

	D3DXMatrixTranslation( &mat3, x, y, z );

	matWorld = mat2 * mat1 * mat3;

	g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
}


//---------------------------------------------------------------------
//　４角ポリゴンの表示、地面用
//---------------------------------------------------------------------
void gsDrawBox(gsTexture texture, float x, float y, float z, float t)
{
    CUSTOMVERTEX3D vertices[] =
    {
        { -1.0f, 0.0f,  1.0f, 0xffffffff, 0.0, 0.0 },
        {  1.0f, 0.0f,  1.0f, 0xffffffff, 1.0, 0.0 },
        { -1.0f, 0.0f, -1.0f, 0xffffffff, 0.0, 1.0 },
        {  1.0f, 0.0f, -1.0f, 0xffffffff, 1.0, 1.0 },
    };

	gsSetMatrices( x, y, z, t );

	// 描画
	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX3D );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,			// プリミティブのタイプ
		2,								// プリミティブの数
		vertices,						// 頂点データへのポインタ
		sizeof(CUSTOMVERTEX3D) );		// 各頂点データへのストライド（バイト単位）

}

//---------------------------------------------------------------------
//　４角ポリゴンの表示、立っている物体
//---------------------------------------------------------------------
void gsDrawBox2(gsTexture texture, float x, float y, float z, float ty)
{
    CUSTOMVERTEX3D vertices[] =
    {
        { -1.0f,   1.0f, 0.0f,0xffffffff, 0.0, 0.0 },
        {  1.0f,   1.0f, 0.0f,0xffffffff, 1.0, 0.0 },
        { -1.0f,  -1.0f, 0.0f,0xffffffff, 0.0, 1.0 },
        {  1.0f,  -1.0f, 0.0f,0xffffffff, 1.0, 1.0 },
    };

	gsSetMatrices( x, y, z, ty );

	// 描画
	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX3D );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,			// プリミティブのタイプ
		2,								// プリミティブの数
		vertices,						// 頂点データへのポインタ
		sizeof(CUSTOMVERTEX3D) );		// 各頂点データへのストライド（バイト単位）
}

//---------------------------------------------------------------------
//　特殊な４角ポリゴンの表示、エフェクト表示
//---------------------------------------------------------------------
void gsDrawBoxSize(gsTexture texture, float x, float y, float z, float ty, int color, float scalex, float scaley)
{
	int i;

    CUSTOMVERTEX3D vertices[] =
    {
        { -1.0f,   1.0f, 0.0f,0xffffffff, 0.0, 0.0 },
        {  1.0f,   1.0f, 0.0f,0xffffffff, 1.0, 0.0 },
        { -1.0f,  -1.0f, 0.0f,0xffffffff, 0.0, 1.0 },
        {  1.0f,  -1.0f, 0.0f,0xffffffff, 1.0, 1.0 },
    };

	if (color<0) color=0;
	if (color>255) color=255;
	color = color << 24;
	for ( i =0; i < 4; i++ )
	{
		vertices[i].color = color + 0x00ffffff;
	}

	gsSetMatrices( x, y, z, ty, scalex, scaley);

	// 描画
	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX3D );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,			// プリミティブのタイプ
		2,								// プリミティブの数
		vertices,						// 頂点データへのポインタ
		sizeof(CUSTOMVERTEX3D) );		// 各頂点データへのストライド（バイト単位）
}



//=============================================================================
//	X モデル関連
//=============================================================================

//=====================================================================
//	gsCAllocateHierarchy クラス
//	---------------------------
//	X File の階層構造を解析，その情報を生成するために利用されるクラス．
//	利用者は，ID3DXAllocateHierarchy クラスを派生させたクラスを
//	作成する必要がある．
//=====================================================================
class gsCAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	///////////////////////////////////////////////////////////////////
	// メソッド

	// フレームの生成時に呼ばれるメソッド
	STDMETHOD(CreateFrame)(THIS_
		LPCSTR						Name, 
		LPD3DXFRAME*				ppNewFrame);

	// メッシュコンテナの生成時に呼ばれるメソッド
    STDMETHOD(CreateMeshContainer)(THIS_ 
        LPCSTR						Name, 
        CONST D3DXMESHDATA*			pMeshData, 
        CONST D3DXMATERIAL*			pMaterials, 
        CONST D3DXEFFECTINSTANCE*	pEffectInstances, 
        DWORD						NumMaterials, 
        CONST DWORD*				pAdjacency, 
        LPD3DXSKININFO				pSkinInfo, 
        LPD3DXMESHCONTAINER*		ppNewMeshContainer);

	// フレームの削除時に呼ばれるメソッド
	STDMETHOD(DestroyFrame)(THIS_
		LPD3DXFRAME					pFrameToFree); 

	// メッシュコンテナの削除時に呼ばれるメソッド
	STDMETHOD(DestroyMeshContainer)(THIS_ 
		LPD3DXMESHCONTAINER			pMeshContainerToFree); 


	//////////////////////////////////////////////////////////////////////
	// コンストラクタ
	gsCAllocateHierarchy(){}
};

// 階層構造付きのメッシュを操作する際に利用するオブジェクト
gsCAllocateHierarchy	AllocHierarchy;


//=====================================================================
//	gsCAllocateHierarchy::CreateFrame
//	---------------------------------
//	フレーム生成時に呼ばれるメソッド
//		[in]	Name		: フレーム名
//		[out]	ppNewFrame	: 生成されたフレームオブジェクト
//=====================================================================
HRESULT gsCAllocateHierarchy::CreateFrame(
	LPCTSTR		Name,
	LPD3DXFRAME	*ppNewFrame)
{
	gsFrame	*pTmpFrame = NULL;	
	HRESULT	rc;			// リターンコード

	*ppNewFrame = NULL;

	// フレームオブジェクトの生成
	pTmpFrame = new gsFrame;
	if ( pTmpFrame == NULL ) 
	{
		rc = E_OUTOFMEMORY;
		goto e_Exit;
	}

	// フレーム名の保存
	pTmpFrame->Name = new TCHAR[lstrlen(Name) + 1];
	if ( pTmpFrame->Name == NULL)
	{
		rc = E_OUTOFMEMORY;
		goto e_Exit;
	}
	lstrcpy(pTmpFrame->Name, Name);
	gsDebugPrintf("CreateFrame:Name[%s]\n", Name);	// Debug


	// フレームオブジェクトの初期値の設定
	D3DXMatrixIdentity(&pTmpFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pTmpFrame->CombinedTransformMatrix);
	
	pTmpFrame->pMeshContainer	= NULL;	// メッシュコンテナ
	pTmpFrame->pFrameSibling	= NULL;	// 兄弟フレーム
	pTmpFrame->pFrameFirstChild	= NULL;	// 子フレーム
	
	// フレームオブジェクトのポインタの格納
	*ppNewFrame = pTmpFrame;
	pTmpFrame	= NULL;

	rc = S_OK;

e_Exit:
	delete	pTmpFrame;
	return	rc;
}


//=====================================================================
//	gsCAllocateHierarchy::CreateMeshContainer
//	-----------------------------------------
//	メッシュコンテナ生成時に呼ばれるメソッド
//		[in]	Name				: メッシュコンテナ名 
//		[in]	pMeshData			: メッシュデータ
//		[in]	pMaterials			: マテリアル情報
//		[in]	pEffectInstances	: エフェクトインスタンス(?)
//		[in]	NumMaterials		: マテリアル数
//		[in]	pAdjacency			: 隣接性情報
//		[in]	pSkinInfo			: スキン情報
//		[out]	ppNewMeshContainer	: 生成されたメッシュコンテナ
//=====================================================================
HRESULT gsCAllocateHierarchy::CreateMeshContainer (
	LPCTSTR						Name,
	CONST D3DXMESHDATA*			pMeshData,
	CONST D3DXMATERIAL*			pMaterials,
	CONST D3DXEFFECTINSTANCE*	pEffectInstances,
	DWORD						NumMaterials, 
	CONST DWORD*				pAdjacency,
	LPD3DXSKININFO				pSkinInfo,
	LPD3DXMESHCONTAINER*		ppNewMeshContainer)
{
	
	gsMeshContainer*	pTmpMeshContainer = NULL;	// メッシュコンテナ
	LPD3DXMESH			pMesh	= NULL;

	UINT	nFaces;		// フェイス数
	UINT	nBones;		// ボーン数

	UINT	iMaterial;
    UINT	iBone;

	HRESULT	rc;			// リターンコード

    LPDIRECT3DDEVICE9 pDevice = NULL;


	// 初期設定
	*ppNewMeshContainer = NULL;

	// 通常メッシュのみサポート
	//(プログレッシブメッシュ，パッチメッシュは未対応)
	if ( pMeshData->Type != D3DXMESHTYPE_MESH)
	{
		rc = E_FAIL;
		goto e_Exit;
	}

	// コードの可読性を高めるため
	pMesh = pMeshData->pMesh;


 
	// 新規にメッシュコンテナを生成する
	pTmpMeshContainer = new gsMeshContainer;
	if ( pTmpMeshContainer == NULL )
	{
		rc =  E_OUTOFMEMORY;
		goto e_Exit;
	}
	ZeroMemory(pTmpMeshContainer, sizeof(gsMeshContainer));

	// メッシュコンテナ名の保存
	gsDebugPrintf("CreateMeshContainer:Name[%s]\n", Name);	// Debug
	pTmpMeshContainer->Name = new TCHAR[lstrlen(Name) + 1];
	if ( !pTmpMeshContainer->Name )
	{
		rc =  E_OUTOFMEMORY;
		goto e_Exit;
	}
	lstrcpy(pTmpMeshContainer->Name, Name);


	pMesh->GetDevice(&pDevice);


	// メッシュデータの設定
	// ※メッシュデータに法線情報が存在しない場合には，生成し差し替える．

	if ( !(pMesh->GetFVF() & D3DFVF_NORMAL) )
	{
		pTmpMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		rc = pMesh->CloneMeshFVF(
						pMesh->GetOptions(),
						pMesh->GetFVF() | D3DFVF_NORMAL,
						pDevice, 
//						g_pd3dDevice, 
						&pTmpMeshContainer->MeshData.pMesh);

		if ( FAILED(rc) )
		{
			goto e_Exit;
		}

		pMesh = pTmpMeshContainer->MeshData.pMesh;
		D3DXComputeNormals(pMesh, NULL);
	}
	else
	{
		pTmpMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
		pTmpMeshContainer->MeshData.pMesh = pMesh;

		pMesh->AddRef();
	}


	///////////////////////////////////////////////////////////////////
	// マテリアル情報，隣接性情報，テクスチャ情報の設定

	nFaces = pMesh->GetNumFaces();	// フェイス数の取得

	// 必要なメモリの確保
	pTmpMeshContainer->NumMaterials	= max(1, NumMaterials);
	pTmpMeshContainer->pMaterials	= new D3DXMATERIAL[pTmpMeshContainer->NumMaterials];
	pTmpMeshContainer->ppTextures	= new gsTexture[pTmpMeshContainer->NumMaterials];
	pTmpMeshContainer->pAdjacency	= new DWORD[nFaces*3];
	
	// メモリエラーのチェック
	if ( (pTmpMeshContainer->pMaterials == NULL) ||
		 (pTmpMeshContainer->ppTextures == NULL) ||
		 (pTmpMeshContainer->pAdjacency == NULL)	)
	{
		rc = E_OUTOFMEMORY;
		goto e_Exit;
	}

	// 隣接性情報の設定
	memcpy(pTmpMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * nFaces*3);

	// テクスチャ情報の初期化
	ZeroMemory(pTmpMeshContainer->ppTextures, sizeof(gsTexture) * pTmpMeshContainer->NumMaterials);

	// X File 中にマテリアル情報が存在する場合
	if ( NumMaterials > 0 )
	{
		// マテリアル情報の設定
		memcpy(pTmpMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

		// テクスチャ情報の設定（テクスチャファイルの読み込みと設定）
		for ( iMaterial = 0;  iMaterial < NumMaterials;  iMaterial++ )
		{
			// テクスチャのファイル名が存在し，かつ，ファイル名が空でないなら
			if ( pTmpMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL &&
				 lstrlen(pTmpMeshContainer->pMaterials[iMaterial].pTextureFilename) > 0 )
			{
				// ファイル名の取り込み
				TCHAR strTexturePath[MAX_PATH];
				lstrcpy(strTexturePath, pTmpMeshContainer->pMaterials[iMaterial].pTextureFilename);

				// テクスチャの読み込みと設定
				// ※エラー時でも処理は中断しないようにしている
				if ( FAILED(D3DXCreateTextureFromFile(
					pDevice,
//					g_pd3dDevice,
					strTexturePath,
					&pTmpMeshContainer->ppTextures[iMaterial])))
				{
					gsDebugPrintf("★CreateMeshContainer : テクスチャ[%s]の読み込みエラー\n", strTexturePath );
					pTmpMeshContainer->ppTextures[iMaterial] = NULL;
				}
				pTmpMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
			}
		}
	}
	else	// マテリアル情報が存在しない場合 ⇒ デフォルト値を準備する
	{
		pTmpMeshContainer->pMaterials[0].pTextureFilename = NULL;
		ZeroMemory(&pTmpMeshContainer->pMaterials[0].MatD3D, sizeof(D3DMATERIAL9));

																//	  r     g     b     a
		pTmpMeshContainer->pMaterials[0].MatD3D.Diffuse  = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pTmpMeshContainer->pMaterials[0].MatD3D.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	}

	// スキン情報が存在する場合
	if ( pSkinInfo != NULL )
	{
		// スキン情報の設定
		pTmpMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		pTmpMeshContainer->pOrigMesh = pMesh;
        pMesh->AddRef();

		// ボーン変換行列用領域の確保
		nBones = pSkinInfo->GetNumBones();
		pTmpMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[nBones];
		if ( pTmpMeshContainer->pBoneOffsetMatrices == NULL )
		{
			rc = E_OUTOFMEMORY;
			goto e_Exit;
		}

		// スキン情報から，ボーンのオフセット行列を取り出しておく．
		// (後で，何度も読み込む必要がないようにするため)
		for ( iBone = 0; iBone < nBones; iBone++ )
		{
			pTmpMeshContainer->pBoneOffsetMatrices[iBone] =
				*(pTmpMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
		}

		GS_SAFE_RELEASE( pTmpMeshContainer->MeshData.pMesh );
		GS_SAFE_RELEASE( pTmpMeshContainer->pBoneBuffer    );

		// 頂点ブレンドに利用するための メッシュデータに変換する
		rc = pTmpMeshContainer->pSkinInfo->ConvertToBlendedMesh(
				pTmpMeshContainer->pOrigMesh,			// メッシュ
				NULL,									 
				pTmpMeshContainer->pAdjacency,			// 隣接性情報
				NULL, NULL, NULL, 
				&pTmpMeshContainer->NumInfl,			// 影響を受けるボーンの最大数
				&pTmpMeshContainer->NumBones,			// ボーン数
				&pTmpMeshContainer->pBoneBuffer,		// ボーンデータ作業用
				&pTmpMeshContainer->MeshData.pMesh	);	// 新しいメッシュ

		if (FAILED(rc))
			goto e_Exit;
    }

	// 準備が完了した．作業用のメッシュコンテナのポインタを設定する．
	*ppNewMeshContainer = pTmpMeshContainer;
	pTmpMeshContainer = NULL;

	rc = S_OK;

e_Exit:
    GS_SAFE_RELEASE(pDevice);

	// 処理中，エラーが発生したとき，作業用に作成したメッシュコンテナを解放する．
	if( pTmpMeshContainer != NULL )
	{
		DestroyMeshContainer(pTmpMeshContainer);
	}

	return	rc;
}


//=====================================================================
//	gsCAllocateHierarchy::DestroyFrame
//	----------------------------------
//	フレーム削除時に呼ばれるメソッド
//	D3DXFrameDestroy 関数は，再帰的に兄弟フレーム，子フレームを削除する．
//	各々のフレームを削除するときに，この関数が呼ばれる．
//		[in]	pFrameToFree	: 解放するフレーム 
//=====================================================================
HRESULT gsCAllocateHierarchy::DestroyFrame(
	LPD3DXFRAME pFrameToFree )
{
	gsDebugPrintf( "★ DestroyFrame [%s]\n", pFrameToFree->Name );
	GS_SAFE_DELETE_ARRAY(pFrameToFree->Name);	// フレーム名の解放
	GS_SAFE_DELETE(pFrameToFree);				// フレームの解放

	return	S_OK;
}


//=====================================================================
//	gsCAllocateHierarchy::DestroyMeshContainer
//	------------------------------------------
//	メッシュコンテナ削除時に呼ばれるメソッド
//		[in]	pMeshContainerBase	: 解放するメッシュコンテナ
//=====================================================================
HRESULT gsCAllocateHierarchy::DestroyMeshContainer(
	LPD3DXMESHCONTAINER pMeshContainerBase )
{
	gsMeshContainer *pMeshContainer = (gsMeshContainer*)pMeshContainerBase;
	UINT	iMaterial;

	GS_SAFE_DELETE_ARRAY( pMeshContainer->Name );					// メッシュコンテナ名の解放
	GS_SAFE_DELETE_ARRAY( pMeshContainer->pAdjacency );			// 隣接性情報の解放

	for ( UINT i=0; i<pMeshContainer->NumMaterials; i++)		// マテリアル情報の解放
		GS_SAFE_DELETE_ARRAY( pMeshContainer->pMaterials->pTextureFilename );
	GS_SAFE_DELETE_ARRAY( pMeshContainer->pMaterials );			

	GS_SAFE_DELETE_ARRAY( pMeshContainer->pBoneOffsetMatrices );	// ボーンオフセット行列の解放
	
	// テクスチャの解放
	if( pMeshContainer->ppTextures != NULL )
	{
		for(iMaterial = 0;  iMaterial < pMeshContainer->NumMaterials;  iMaterial++)
		{
			GS_SAFE_RELEASE( pMeshContainer->ppTextures[iMaterial] );
		}
	}
	GS_SAFE_DELETE_ARRAY( pMeshContainer->ppTextures );			// テクスチャ配列の解放

	// ボーンを含むメッシュ情報の解放
    GS_SAFE_DELETE_ARRAY( pMeshContainer->ppBoneMatrixPtrs );		// ボーン変換行列群の解放 
    GS_SAFE_RELEASE( pMeshContainer->pBoneBuffer );				// ボーン合成行列バッファの解放
    GS_SAFE_RELEASE( pMeshContainer->pOrigMesh );					// オリジナルメッシュデータの解放
	GS_SAFE_RELEASE( pMeshContainer->MeshData.pMesh );				// メッシュデータの解放
    GS_SAFE_RELEASE( pMeshContainer->pSkinInfo );					// スキン情報の解放

	// メッシュコンテナの解放
	GS_SAFE_DELETE( pMeshContainer );							

	return	S_OK;
}

//---------------------------------------------------------------------
//	X モデル読み込み	非アニメーション版
//---------------------------------------------------------------------
HRESULT gsLoadX( gsMesh *m, char *pXFileName )
{
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

	m->pMesh			= NULL;
	m->pMeshMaterials	= NULL;
	m->pMeshTextures	= NULL;
	m->dwNumMaterials	= 0L;
	
	if( FAILED( D3DXLoadMeshFromX( pXFileName, D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL, 
                                   &pD3DXMtrlBuffer, NULL, &m->dwNumMaterials, 
                                   &m->pMesh )))
	{
		gsDebugPrintf("★ D3LoadXA : X File が存在しない[%s]\n", pXFileName);

		MessageBox(NULL, "Ｘファイルがありません\n終了します", pXFileName, MB_OK);

		PostQuitMessage(0);

		return E_FAIL;
	}
	

	D3DXMATERIAL* d3dxMaterials =
				 (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

    m->pMeshMaterials = new D3DMATERIAL9[m->dwNumMaterials];

    m->pMeshTextures  = new gsTexture[m->dwNumMaterials];
    for( DWORD i=0; i<m->dwNumMaterials; i++ )
    {
        // マテリアルのコピー
        m->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        m->pMeshMaterials[i].Ambient = m->pMeshMaterials[i].Diffuse;
        m->pMeshTextures[i] = NULL;

        if( d3dxMaterials[i].pTextureFilename != NULL && 
            lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
        {
			// テクスチャの読み込みと設定
			// ※エラー時でも処理は中断しないようにしている
			if( FAILED( D3DXCreateTextureFromFile( 
						g_pd3dDevice, d3dxMaterials[i].pTextureFilename, &m->pMeshTextures[i] ) ) )
			{
				gsDebugPrintf("★D3LoadX : テクスチャ[%s]の読み込みエラー\n",
													d3dxMaterials[i].pTextureFilename );
			}
        }
    }

	// 適切な順番にメッシュデータをソートして，高速に描画されるようにする
	m->pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT,NULL,NULL,NULL,NULL);

	// マテリアルバッファの解放
	GS_SAFE_RELEASE( pD3DXMtrlBuffer );

	return S_OK;
}



//=====================================================================
//	D3LoadXA
//	--------
//	階層構造を持ったメッシュの読み込み
//	アニメーション情報の読み込みにも対応している
//		[out]	pMesh		: 生成されるメッシュ
//		[in]	pXFileName	: X ファイル名
//=====================================================================
HRESULT	gsLoadXA( gsMesh* pMesh, char* pXFileName )
{
	// 階層構造付きのメッシュを操作する際に利用するオブジェクト
//	gsCAllocateHierarchy	AllocHierarchy;

//	LPD3DXFRAME	pFrameRoot;
	HRESULT	rc;

	// 階層構造を持った X File の読み込み
	rc = D3DXLoadMeshHierarchyFromX( 
			pXFileName,					// X ファイル名
			D3DXMESH_MANAGED,			// メッシュの作成オプション
										//	D3DXMESH_VB_MANAGED | D3DXMESH_IB_MANAGED 
			g_pd3dDevice,				// Direct3D Device
			&AllocHierarchy,			// 階層構造を生成するインターフェイス
			NULL,						// ユーザー固有データは利用しない(NULL)

			&pMesh->pFrameRoot,			// ロードされるフレーム階層へのポインタ
			&pMesh->pAnimController );	// アニメーションコントローラへのポインタ

	if( FAILED( rc ) )
	{
		gsDebugPrintf("★ D3LoadXA : X File が存在しない[%s]\n", pXFileName);
		MessageBox(NULL, "Ｘファイルがありません\n終了します", pXFileName, MB_OK);

		PostQuitMessage(0);

		return	E_FAIL;
	}

	// ボーン変換行列の生成と設定
	_gsInitBoneMatrics(pMesh->pFrameRoot, pMesh->pFrameRoot);

	return	S_OK;
}


//=====================================================================
//	_gsInitBoneMatrics
//	------------------
//	ボーン変換行列を，再帰的に生成し，設定する
//		[in]	pFrame	: ボーン変換行列を設定するフレーム
//=====================================================================
static	HRESULT	_gsInitBoneMatrics(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrame)
{
    HRESULT hr;

	// フレームのポインタが有効なら，ボーン変換行列を生成，設定する
    if (pFrame->pMeshContainer != NULL)
    {
        hr = _gsInitBoneMatricsOnMesh(pFrameRoot, pFrame->pMeshContainer);
        if (FAILED(hr))
            return hr;
    }

	// 兄弟フレームがあるなら，兄弟フレーム下のフレームも処理する
    if (pFrame->pFrameSibling != NULL)
    {
        hr = _gsInitBoneMatrics(pFrameRoot, pFrame->pFrameSibling);
        if (FAILED(hr))
            return hr;
    }

	// 子フレームがあるなら，子フレーム下のフレームも処理する
    if (pFrame->pFrameFirstChild != NULL)
    {
        hr = _gsInitBoneMatrics(pFrameRoot, pFrame->pFrameFirstChild);
        if (FAILED(hr))
            return hr;
    }

    return	S_OK;
}


//=====================================================================
//	_gsInitBoneMatricsOnMesh
//	------------------------
//	ボーン変換行列を生成し，メッシュコンテナに設定する
//		[in]	pFrameRoot			: このフレームを起点として
//									  対象フレームを捜す
//		[in]	pMeshContinerBase	: 適用するメッシュコンテナ
//=====================================================================
static	HRESULT	_gsInitBoneMatricsOnMesh(
			LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase)
{
	gsFrame *pFrame;
	UINT	nBones;		// ボーン数
	UINT	iBone;

	// 派生させたメッシュコンテナに，基底クラスのボーン変換行列を設定する
	gsMeshContainer *pMeshContainer = (gsMeshContainer*)pMeshContainerBase;

	// スキンメッシュであれば，ボーン変換行列を設定する
	if ( pMeshContainer->pSkinInfo )
	{
		nBones = pMeshContainer->pSkinInfo->GetNumBones();

		pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[nBones];
		if (pMeshContainer->ppBoneMatrixPtrs == NULL)
			return E_OUTOFMEMORY;

		for (iBone = 0;  iBone < nBones;  iBone++)
		{
			gsDebugPrintf( "★_gsInitBoneMatricsOnMesh : ボーン名[%s]\n", pMeshContainer->pSkinInfo->GetBoneName(iBone) );

			pFrame = (gsFrame*)D3DXFrameFind( pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(iBone) );

			if (pFrame == NULL)
				return E_FAIL;

			pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformMatrix;
		}
	}

	return S_OK;
}


//---------------------------------------------------------------------
//	X モデル解放	※階層構造のないメッシュ用
//---------------------------------------------------------------------
HRESULT	gsReleaseX( gsMesh* pReleaseMesh )
{
	// マテリアル情報の解放
	GS_SAFE_DELETE_ARRAY( pReleaseMesh->pMeshMaterials );		// マテリアル情報の解放

	// テクスチャの解放
    if( pReleaseMesh->pMeshTextures )
    {
        for( UINT i = 0;  i < pReleaseMesh->dwNumMaterials;  i++ )
        {
            GS_SAFE_RELEASE( pReleaseMesh->pMeshTextures[i] );	// テクスチャインターフェイスの解放
        }
        GS_SAFE_DELETE_ARRAY( pReleaseMesh->pMeshTextures );	// テクスチャ配列の解放
    }

	// メッシュの解放
	GS_SAFE_RELEASE( pReleaseMesh->pMesh );

	return	S_OK;
}


//---------------------------------------------------------------------
//	X モデル解放	※階層構造のあるメッシュ用（アニメーション情報含む）
//---------------------------------------------------------------------
HRESULT	D3ReleaseXA( gsMesh* pReleaseMesh )
{
	if( pReleaseMesh->pFrameRoot != NULL )
	{
//		gsCAllocateHierarchy AllocHierarchy;	// 階層構造付メッシュ操作

		D3DXFrameDestroy( pReleaseMesh->pFrameRoot, &AllocHierarchy );

		pReleaseMesh->pFrameRoot = NULL;
	}

	GS_SAFE_RELEASE(pReleaseMesh->pAnimController);
	

	return	S_OK;
}


//---------------------------------------------------------------------
// xモデル描画		※階層構造のないメッシュ用
//---------------------------------------------------------------------
void gsDrawX( gsMesh *m, float x, float y, float z, float t )
{
	gsSetMatrices( x, y, z, t );

	for( DWORD i=0; i<m->dwNumMaterials; i++ )
	{
		g_pd3dDevice->SetMaterial( &m->pMeshMaterials[i] );
		g_pd3dDevice->SetTexture( 0, m->pMeshTextures[i] );
		m->pMesh->DrawSubset( i );
    }
}


//---------------------------------------------------------------------
// xモデル描画		※階層構造のあるメッシュ用
//---------------------------------------------------------------------
void gsDrawXA( gsMesh *m, float x, float y, float z, float t, double animePastTime )
{
	LPD3DXANIMATIONSET	pAnimSet;
	m->pAnimController->GetAnimationSet(0, &pAnimSet);

	gsSetMatrices( x, y, z, t );

	D3DXMATRIXA16 matWorld;
	g_pd3dDevice->GetTransform( D3DTS_WORLD, &matWorld );

	m->pAnimController->AdvanceTime( animePastTime, NULL );

	// ボーンの合成行列を更新する
	_gsUpdateBoneMatrices( m->pFrameRoot, &matWorld );

	// フレーム全体を描画する
	_gsDrawFrame( m->pFrameRoot );						
}


//=====================================================================
//	_gsUpdateBoneMatrices
//	---------------------
//	ボーンの合成行列を算出，設定する
//		[in]	pFrameBase		: 注目しているフレーム
//		[in]	pParentMatrix	: 親の変換行列
//=====================================================================
static	void	_gsUpdateBoneMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	// ボーンの合成行列を利用するため，派生クラスのポインタとして利用する 
	gsFrame *pFrame = (gsFrame*)pFrameBase;

	///////////////////////////////////////////////////////////////////
	// ボーンの合成行列を生成する
	
	// 親の変換行列を使って，現在のフレームの合成行列を算出する
	if(pParentMatrix != NULL)
	{
		pFrame->CombinedTransformMatrix = pFrame->TransformationMatrix * *pParentMatrix;
	}
	// 親がなければ，X File 中の 元の行列を合成行列とする
	else
	{
		pFrame->CombinedTransformMatrix = pFrame->TransformationMatrix;
	}

	// 兄弟フレームがあるなら，親の変換行列を引数として渡し
	// 兄弟フレームのボーン変換行列を算出させる
	if(pFrame->pFrameSibling != NULL)
	{
		_gsUpdateBoneMatrices(pFrame->pFrameSibling, pParentMatrix);
	}

	// 子フレームがあるなら，現在のフレームの合成行列を引数として渡し
	// 子フレームのボーン変換行列を算出させる
	if(pFrame->pFrameFirstChild != NULL)
	{
		_gsUpdateBoneMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformMatrix);
	}
}


//=====================================================================
//	_gsDrawFrame
//	------------
//	フレームの情報を元に，描画する
//		[in]	pFrame	: 注目しているフレーム
//=====================================================================
static	void	_gsDrawFrame( LPD3DXFRAME pFrame )
{
	// メッシュコンテナ
	LPD3DXMESHCONTAINER pMeshContainer;

	// フレームに対応づけられているメッシュコンテナを取り出す
	pMeshContainer = pFrame->pMeshContainer;

	// メッシュコンテナは リスト構造となっているので
	// それらをたどりながら，描画していく
	while ( pMeshContainer != NULL )
	{
		// メッシュコンテナを元に描画する
		_gsDrawMeshContainer( pMeshContainer, pFrame );

		// 次のメッシュコンテナに移る
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	// 兄弟フレームが存在するなら，それを描画する
	if ( pFrame->pFrameSibling != NULL )
	{
		_gsDrawFrame( pFrame->pFrameSibling );
	}

	// 子フレームが存在するなら，それを描画する
	if ( pFrame->pFrameFirstChild != NULL )
	{
		_gsDrawFrame( pFrame->pFrameFirstChild );
	}
}


//=====================================================================
//	_gsDrawMeshContainer
//	--------------------
//	メッシュコンテナの内容を元に描画する
//		[in]	pMeshContainerBase	: 描画するメッシュコンテナ
//		[in]	pFrameBase			: 合成行列を取り出すフレーム
//=====================================================================
static	void	_gsDrawMeshContainer(
		LPD3DXMESHCONTAINER	pMeshContainerBase,
		LPD3DXFRAME			pFrameBase )
{
	// 描画対象のメッシュコンテナとフレーム
	gsMeshContainer*	pMeshContainer	= (gsMeshContainer*)pMeshContainerBase;
	gsFrame*			pFrame			= (gsFrame*)pFrameBase;

	// ボーンの合成に利用する
    LPD3DXBONECOMBINATION	pBoneComb;
	UINT					AttribIdPrev;
	D3DXMATRIXA16			matTmp;
	D3DXMATRIXA16			matOffset;
	D3DXMATRIXA16			matBoneInfl;

	// スキン情報があるなら，ボーンの重みを反映させるため
	// 各頂点に適用する合成行列を算出してから描画する
	if ( pMeshContainer->pSkinInfo )
	{
		AttribIdPrev = UNUSED32; 
		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>
						(pMeshContainer->pBoneBuffer->GetBufferPointer());

		// 属性グループごとに描画を行う
		for (UINT iAttrib = 0; iAttrib < pMeshContainer->NumBones; iAttrib++)
		{
			// 属性グループ内の最大ボーン数を調べる
			UINT NumBlend = 0;
			for ( UINT i = 0;  i < pMeshContainer->NumInfl;  i++ )
			{
				if ( pBoneComb[iAttrib].BoneId[i] != UINT_MAX )
				{
					NumBlend = i;
				}
			}
	
			// 頂点ブレンド処理が，ハードウェアで実行可能なら描画する
			if( g_d3dcaps.MaxVertexBlendMatrices >= NumBlend + 1 )
			{
				// ボーンのオフセット行列とを反映してからボーンをワールド変換行列に設定します。
				for ( UINT i = 0;  i < pMeshContainer->NumInfl;  i++ )
				{
					UINT iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
					if (iMatrixIndex != UINT_MAX)
					{
						matOffset	= pMeshContainer->pBoneOffsetMatrices[iMatrixIndex];
						matBoneInfl = *(pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);

						// 行列の合成
						matTmp =  matOffset * matBoneInfl;

						// ワールド変換行列の設定
						g_pd3dDevice->SetTransform( D3DTS_WORLDMATRIX( i ), &matTmp );
					}
				}

				// 描画条件(レンダーステート)の設定
				g_pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND, NumBlend );

				// マテリアルとテクスチャの適用
				if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
				{
					g_pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
					g_pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );
					AttribIdPrev = pBoneComb[iAttrib].AttribId;
				}

				// メッシュの描画
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
			}
		}

		// 描画条件(レンダーステート)の復帰
		g_pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND, 0 );
	}

	// スキン情報が存在しないなら，単に描画する
	else
	{
		// ワールド変換行列の設定
		g_pd3dDevice->SetTransform( D3DTS_WORLD, &pFrame->CombinedTransformMatrix );

		// マテリアルグループに分けて描画する
		for ( UINT iMaterial=0;  iMaterial < pMeshContainer->NumMaterials;  iMaterial++ )
		{
			// マテリアルの設定
			g_pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[iMaterial].MatD3D );

			// テクスチャの設定
			g_pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[iMaterial] );

			// メッシュの描画
			pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial);
		}
	}
}


//=============================================================================
// DirectInput関連
//=============================================================================

// ジョイパッド情報取得 (ジョイパッドNo, 取得したいキー情報)
bool gsJoyCheck( int Num, int State )
{
	bool bNowStat = g_sysJoy.m_InpState[1][Num] & State ? true : false;

	return bNowStat;
}


// ジョイパッド情報取得 (ジョイパッドNo, 取得したいキー情報)
int gsGetJoyPadState( int Num, int State )
{

	bool bOldStat = g_sysJoy.m_InpState[0][Num] & State ? true : false;
	bool bNowStat = g_sysJoy.m_InpState[1][Num] & State ? true : false;


	if ( !bOldStat && !bNowStat ) return GSKS_RELEASE;  // 離されている
	if ( !bOldStat &&  bNowStat ) return GSKS_DOWN;	    // 押下直後
	if (  bOldStat &&  bNowStat ) return GSKS_PRESS;	// 押しっぱなし
	if (  bOldStat && !bNowStat ) return GSKS_UP;		// 離した直後

	return GSKS_RELEASE;	// (起こりえない)
}


// ジョイパッドの初期化
bool InitJoyPad( void )
{
	int      i;
	HRESULT  hr;



	for( i=0 ; i<16 ; i++ )g_sysJoy.m_pDIDJoy[i] = NULL;

	// ジョイパッドを使用できる最大数を設定
	int JoystickMax = joyGetNumDevs();

	// 普通は１６個
	if( JoystickMax >= 16 ) 
		JoystickMax = 16;

	// 接続されているジョイパッド数をクリア
	g_JoystickCount = 0;

	// DirectInput8オブジェクトが作成されているか？
	if( g_sysJoy.m_pDInp == NULL ){
		// DirectInput8オブジェクトの作成
		hr = DirectInput8Create( g_hInst, DIRECTINPUT_VERSION, 
								IID_IDirectInput8, (void**)&g_sysJoy.m_pDInp, NULL); 
		if (FAILED(hr)) 
		{
			MessageBox( NULL, "DirectInput8オブジェクト作成失敗", "Error", MB_OK | MB_ICONSTOP );
			return false;
		}
	}

	// デバイスを列挙して作成
	hr = g_sysJoy.m_pDInp->EnumDevices(DI8DEVCLASS_GAMECTRL,
									 EnumJoyPadsCallback,
									 NULL,
									 DIEDFL_ATTACHEDONLY);

	if(FAILED(hr) || (g_sysJoy.m_pDIDJoy[0] == NULL))
	{
		// ジョイパッドないなら
		for ( i=0 ; i<16 ; i++ )
		{
			if( g_sysJoy.m_pDIDJoy[i] != NULL ){
				g_sysJoy.m_pDIDJoy[i]->Release();
				g_sysJoy.m_pDIDJoy[i] = NULL;
			}
		}
		return false;
	}
 
	for ( i=0 ; i<g_JoystickCount ; i++ )
	{
		// データ形式を設定
		hr = g_sysJoy.m_pDIDJoy[i]->SetDataFormat(&c_dfDIJoystick2);

		if (FAILED(hr))
		{
			MessageBox( NULL, "ジョイパッド用データフォーマット設定失敗", "Error", MB_OK | MB_ICONSTOP );
			return false;
		}

		// コールバック関数を使って各軸のモードを設定
		g_NowNum = i;

		hr = g_sysJoy.m_pDIDJoy[i]->EnumObjects(EnumAxesCallback, g_hWnd, DIDFT_ALL);

		if (FAILED(hr))
		{
			MessageBox( NULL, "軸モード設定失敗", "Error", MB_OK | MB_ICONSTOP );
			return false;
		}

		// 軸モードを設定（絶対値モードに設定。デフォルトなので必ずしも設定は必要ない）
		DIPROPDWORD diprop;

		diprop.diph.dwSize			= sizeof(diprop); 
		diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
		diprop.diph.dwObj			= 0;
		diprop.diph.dwHow			= DIPH_DEVICE;
		diprop.dwData				= DIPROPAXISMODE_ABS;
	//	diprop.dwData				= DIPROPAXISMODE_REL;	// 相対値モードの場合
		hr = g_sysJoy.m_pDIDJoy[i]->SetProperty(DIPROP_AXISMODE, &diprop.diph);

		if (FAILED(hr))
		{
			MessageBox( NULL, "軸モードの設定に失敗！", "Error", MB_OK | MB_ICONSTOP );
			return false;
		}

		// バッファリング・データを取得するため、バッファ・サイズを設定
		diprop.dwData = DIDEVICE_BUFFERSIZE;

		hr = g_sysJoy.m_pDIDJoy[i]->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);

		if (FAILED(hr))
		{
			MessageBox( NULL, "バッファサイズの設定に失敗！", "Error", MB_OK | MB_ICONSTOP );
			return false;
		}

		// ジョイパッドの入力制御開始
		g_sysJoy.m_pDIDJoy[i]->Acquire();
	}

	return true;
}


// ジョイパッド列挙関数
BOOL CALLBACK EnumJoyPadsCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	HRESULT hr;


	// 列挙されたジョイパッドへのインターフェイスを取得する
	hr = g_sysJoy.m_pDInp->CreateDevice(pdidInstance->guidInstance, &g_sysJoy.m_pDIDJoy[g_JoystickCount], NULL);

	if (FAILED(hr)) return DIENUM_CONTINUE;

	// ジョイパッドの能力を調べる
	g_sysJoy.m_diDevCaps.dwSize = sizeof(DIDEVCAPS);

	hr = g_sysJoy.m_pDIDJoy[g_JoystickCount]->GetCapabilities(&g_sysJoy.m_diDevCaps);

	if (FAILED(hr))
	{
		// ジョイパッド能力の取得に失敗
		g_sysJoy.m_pDIDJoy[g_JoystickCount]->Release();
		return DIENUM_CONTINUE;
	}

	return ( ++g_JoystickCount == g_JoystickMax ) ? ( DIENUM_STOP ) : ( DIENUM_CONTINUE );
}


// ジョイパッドの軸を列挙する関数
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{

	HRESULT hr;
	int     i = g_NowNum;


	// 軸の値の範囲を設定（-1000～1000）
	DIPROPRANGE diprg;

	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize	    = sizeof(diprg); 
	diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
	diprg.diph.dwObj	    = lpddoi->dwType;
	diprg.diph.dwHow	    = DIPH_BYID;
	diprg.lMin	            = -1000;
	diprg.lMax	            = +1000;

	hr = g_sysJoy.m_pDIDJoy[i++]->SetProperty(DIPROP_RANGE, &diprg.diph);

	if (FAILED(hr))	return DIENUM_STOP;

	return DIENUM_CONTINUE;
}


// ジョイパッドの状態制御
void Update_JoyPadInfo(void)
{
	int			 i;
	HRESULT		 hr;
	DIJOYSTATE2  dijs;	// 現在のジョイパッドの状態



	// 1ループ前の入力情報を退避 (押し始めを検出するため)
	memcpy(&g_sysJoy.m_InpState[0], &g_sysJoy.m_InpState[1], sizeof(int)*16);


	// 入力情報初期化
	for( i=0 ; i<16 ; i++ ){
		g_sysJoy.m_InpState[1][i] = 0;
	}

	for( i=0 ; i<g_JoystickCount ; i++ ){
		// ジョイパッド接続？
		if (g_sysJoy.m_pDIDJoy[i] != NULL)
		{
			// デバイスからデータをポーリング
			if (FAILED(hr = g_sysJoy.m_pDIDJoy[i]->Poll()))
			{
				hr = g_sysJoy.m_pDIDJoy[i]->Acquire();
				while(hr == DIERR_INPUTLOST)
				{
					// ジョイパッドの入力制御開始
					hr = g_sysJoy.m_pDIDJoy[i]->Acquire();
				}
			}

			if(FAILED(hr = g_sysJoy.m_pDIDJoy[i]->GetDeviceState(sizeof(dijs), &dijs)))
			{
				if(hr == DIERR_INPUTLOST)
					g_sysJoy.m_pDIDJoy[i]->Acquire();
				else
					return;
			}


			// ジョイパッド入力情報セット
			if ( dijs.rgdwPOV[0] == 0)      g_sysJoy.m_InpState[1][i] |= KEY_UP;		// 上  (十字キー)
			if ( dijs.rgdwPOV[0] == 4500)   g_sysJoy.m_InpState[1][i] |= KEY_RIGHTUP;	// 右上(十字キー)
			if ( dijs.rgdwPOV[0] == 9000)   g_sysJoy.m_InpState[1][i] |= KEY_RIGHT;		// 右  (十字キー)
			if ( dijs.rgdwPOV[0] == 13500)  g_sysJoy.m_InpState[1][i] |= KEY_RIGHTDOWN; // 右下(十字キー)
			if ( dijs.rgdwPOV[0] == 18000)  g_sysJoy.m_InpState[1][i] |= KEY_DOWN;		// 下  (十字キー)
			if ( dijs.rgdwPOV[0] == 22500)  g_sysJoy.m_InpState[1][i] |= KEY_LEFTDOWN;	// 左下(十字キー)
			if ( dijs.rgdwPOV[0] == 27000)  g_sysJoy.m_InpState[1][i] |= KEY_LEFT;		// 左  (十字キー)
			if ( dijs.rgdwPOV[0] == 31500)  g_sysJoy.m_InpState[1][i] |= KEY_LEFTUP;	// 左上(十字キー)

			if ( dijs.lY < -500)			g_sysJoy.m_InpState[1][i] |= JOYPAD_UP;		// 上(ジョイパッド)
			if ( dijs.lY >  500)			g_sysJoy.m_InpState[1][i] |= JOYPAD_DOWN;	// 下(ジョイパッド)
			if ( dijs.lX < -500)			g_sysJoy.m_InpState[1][i] |= JOYPAD_LEFT;	// 左(ジョイパッド)
			if ( dijs.lX >  500)			g_sysJoy.m_InpState[1][i] |= JOYPAD_RIGHT;	// 右(ジョイパッド)

			if ( dijs.rgbButtons[0])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON1;	// ボタン１
			if ( dijs.rgbButtons[1])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON2;	// ボタン２
			if ( dijs.rgbButtons[2])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON3;	// ボタン３
			if ( dijs.rgbButtons[3])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON4;	// ボタン４
			if ( dijs.rgbButtons[4])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON5;	// ボタン５
			if ( dijs.rgbButtons[5])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON6;	// ボタン６
			if ( dijs.rgbButtons[6])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON7;	// ボタン７
			if ( dijs.rgbButtons[7])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON8;	// ボタン８
			if ( dijs.rgbButtons[8])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON9;	// ボタン９
			if ( dijs.rgbButtons[9])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON10;	// ボタン１０
		}
	}
}


//=============================================================================
//	サウンド関係
//=============================================================================

//=================================================================
// 機能：DirectSound初期化
// 引数：なし
// 返り値：成功true、失敗false
//=================================================================
bool InitDirectSound()
{
	HRESULT   hr;


	//=================================================
	// DirectSound生成
	//=================================================
	hr = DirectSoundCreate8(NULL, &g_lpDirectSound, NULL);
	if FAILED( hr ) return false;


	// 協調レベルの設定
	// (協調レベルとは他のアプリケーションと同じデバイスを同時利用するときの優先度)
	// (第2引数にはDSSCL_PRIORITY(標準協調よりもハードウェアに近い処理が行える)の他に
	// DSSCL_NORMAL(プライマリバッファをデフォルト設定で使う)、
	// DSSCL_WRITEPRIMARY(プライマリバッファにアクセスできるがセカンダリバッファ使用不可)がある。)
	hr = g_lpDirectSound->SetCooperativeLevel( g_hWnd, DSSCL_PRIORITY );

	if FAILED( hr )
	{
		hr = g_lpDirectSound->SetCooperativeLevel( g_hWnd, DSSCL_NORMAL );
		if FAILED( hr ) return false;
	}


	//=================================================
	// プライマリサウンドバッファ生成
	//=================================================
//	DSBUFFERDESC desc = { sizeof(DSBUFFERDESC) };

//	LPDIRECTSOUNDBUFFER pSBPrimary = NULL;
	DSBUFFERDESC dsbdesk;
	memset(&dsbdesk, 0, sizeof(DSBUFFERDESC));
	dsbdesk.dwSize = sizeof(DSBUFFERDESC);
	dsbdesk.dwFlags = DSBCAPS_PRIMARYBUFFER		// プライマリバッファを作る
						| DSBCAPS_CTRLVOLUME	// ボリュームの変更を有効にする
					    | DSBCAPS_CTRLPAN;		// パンを有効にする

	// プライマリサウンドバッファの作成
	g_lpDirectSound->CreateSoundBuffer(&dsbdesk, &g_lpPrimaryBuffer, NULL);

	// プライマリバッファのフォーマットを指定
	WAVEFORMATEX wfx;

	memset(&wfx, 0, sizeof(wfx)); 
	wfx.wFormatTag = WAVE_FORMAT_PCM; // PCM形式
	wfx.nChannels = 2;				  // チャンネル(ステレオ)
	wfx.nSamplesPerSec = 44100;		  // サンプリングレート(44.1kHz)
	wfx.wBitsPerSample = 16;		  // 量子化ビット(16bit)
	wfx.nBlockAlign = 4;			  // 1サンプリングあたりのバイト数(16bit×2ch)
	wfx.nAvgBytesPerSec = 176400;	  // 1秒あたりのバイト数(16bit×2ch×44100Hz)

	g_lpPrimaryBuffer->SetFormat(&wfx);


	if FAILED( hr ) return false;

	return true;
}



//---------------------------------------------------------------------
//	■サウンドを読み込む
//		void gsLoadSound(gsSound *sound,  char *str )
//
//		引数 [out]	sound		: サウンドを管理する変数へのポインタ
//		引数 [in]	str			: サウンドのファイル名
//
//		戻り値	なし
//---------------------------------------------------------------------
void gsLoadSound( gsSound *sound, char *str )
{
	char *str2;
	int err;

	err = 0;
	str2 = str;
	while ( *str2 != '\0')
	{
		// 拡張子がwavか調べる
		if ( *str2 == '.' )
		{
			str2++;
			if ( *str2!='W' && *str2!='w') break;
			str2++;
			if ( *str2!='A' && *str2!='a') break;
			str2++;
			if ( *str2!='V' && *str2!='v') break;
			err=1;
			break;
		}
		str2++;
	}

	// wav形式でない場合（この命令はwavのみ対応）
	if ( err == 0 )
	{
		MessageBox( NULL, "サウンドファイルがwav形式ではありません\n終了します", str, MB_OK );
		PostQuitMessage(0);
	}

	*sound = LoadWave(str);

	// ロード失敗
	if ( *sound == NULL )
	{
		MessageBox( NULL, "サウンドファイルがありません\n終了します", str, MB_OK );
		PostQuitMessage(0);
	}
}

//---------------------------------------------------------------------
//	■サウンドを解放する
//		void gsReleaseSound( gsSound sound )
//
//		引数 [out]	sound		: サウンドを管理する変数
//
//		戻り値	なし
//---------------------------------------------------------------------
void gsReleaseSound( gsSound sound )
{
	GS_SAFE_RELEASE( sound );
}


//---------------------------------------------------------------------
//	■サウンドをプレイする
//		void gsPlaySound( gsSound sound )
//
//		引数　なし
//
//		戻り値	なし
//---------------------------------------------------------------------
void gsPlaySound( gsSound sound, int loop_flag)
{

	sound->SetCurrentPosition(0);

	if ( loop_flag == LOOP_ON )
	{
		sound->Play( 0, 0, DSBPLAY_LOOPING );
	}
	else
	{
	   sound->Play( 0, 0, 0 );
	}
}


//---------------------------------------------------------------------
//	■サウンドを止める
//		void gsStopSound( gsSound sound )
//
//		引数　なし
//
//		戻り値	なし
//---------------------------------------------------------------------
void gsStopSound( gsSound sound)
{
	sound->Stop();
}


//=================================================================
// 機能：解放処理
// 引数：なし
// 返り値：なし
//=================================================================
void ReleaseDirectSound( void )
{
	if ( g_lpPrimaryBuffer != NULL ) g_lpPrimaryBuffer->Release();
	if ( g_lpDirectSound   != NULL ) g_lpDirectSound->Release();
}


//=================================================================
// 機能：セカンダリバッファを作成してWaveファイルを読み込む
// 引数：wavファイル名
// 返り値：波形データを読み込んだサウンドバッファポインタ
//=================================================================
gsSound LoadWave( char *file )
{
	DSBUFFERDESC          desc       = { sizeof(DSBUFFERDESC) };
	LPDIRECTSOUNDBUFFER   lpTempBuff = NULL;
	gsSound  lpBuffer   = NULL;
	gsSound  result     = NULL;
	LPBYTE                lpWavData  = NULL;
	WAVEFORMATEX          wf;
	DWORD                 szWavData;
	HRESULT               hr;


	//=====================================================
	// Waveファイルフォーマット情報とデータサイズを取得
	//=====================================================
	szWavData = GetWaveData( file, &lpWavData, &wf );
	if ( szWavData == 0 ) goto EXIT;

	//=====================================================
	// DirectSoundBuffer設定
	//=====================================================
	desc.dwFlags       = DSBCAPS_LOCDEFER;
	desc.dwBufferBytes = szWavData;
	desc.lpwfxFormat   = &wf;

	//=====================================================
	// DirectSoundBuffer生成
	//=====================================================
	hr = g_lpDirectSound->CreateSoundBuffer( &desc, &lpTempBuff, NULL );
	if FAILED( hr ) goto EXIT;

	//=====================================================
	// DirectSoundBuffer から DirectSoundBuffer8インタフェースの取得
	//=====================================================
	hr = lpTempBuff->QueryInterface( IID_IDirectSoundBuffer8, (void **)&lpBuffer );
	lpTempBuff->Release();

	if FAILED( hr ) goto EXIT;


	//=====================================================
	// バッファロック
	//=====================================================
	LPVOID lpSoundData1, lpSoundData2;
	DWORD  size1, size2;
	hr = lpBuffer->Lock(
					0, szWavData,
					&lpSoundData1, &size1,
					&lpSoundData2, &size2,
					DSBLOCK_ENTIREBUFFER
				);
	if FAILED( hr ) goto EXIT;

	// サウンドデータ読み込み
	memcpy( lpSoundData1, lpWavData, szWavData );

	// ロック解除
	lpBuffer->Unlock( lpSoundData1, size1, lpSoundData2, size2 );

	result = lpBuffer;

// 終了
EXIT:
	if ( lpWavData != NULL ) delete [] lpWavData;

	return result;
}


//=================================================================
// 機能  ：Waveデータ読み込み
// 引数  ：ファイル名、波形格納ポインタ、Waveヘッダ
// 返り値：波形データサイズ
//=================================================================
DWORD GetWaveData( char *file, LPBYTE *lpData, WAVEFORMATEX *lpwf )
{
	FILE *fp = NULL;
	DWORD result = 0;
	long RiffDataSize;
	long fmtDataSize;
	long DataSize;
	long FormatSize;
	char Chunk[5] = "";

	*lpData = NULL;

	//--------------------------------------------------------
	// ファイルオープン
	//--------------------------------------------------------
	fp = fopen( file, "rb" );
	if ( fp == NULL ) goto EXIT;

	//--------------------------------------------------------
	// "RIFF"の文字列
	//--------------------------------------------------------
	fread( Chunk, sizeof(char), 4, fp );
	if ( strcmp( "RIFF", Chunk ) ) goto EXIT;

	//--------------------------------------------------------
	// RIFFデータサイズ
	//--------------------------------------------------------
	fread( &RiffDataSize, sizeof(long), 1, fp );

	//--------------------------------------------------------
	// "WAVE"の文字列
	//--------------------------------------------------------
	fread( Chunk, sizeof(char), 4, fp );
	if ( strcmp( "WAVE", Chunk ) ) goto EXIT;

	//========================================================
	// Foramt チャンク
	//========================================================
	// "fmt "の文字列
	fread( Chunk, sizeof(char), 4, fp );
	if ( strcmp( "fmt ", Chunk ) ) goto EXIT;

	//--------------------------------------------------------
	// fmtデータサイズ
	//--------------------------------------------------------
	fread( &fmtDataSize, sizeof(long), 1, fp );

	//--------------------------------------------------------
	// フォーマット情報取得
	//--------------------------------------------------------
	FormatSize = sizeof(WAVEFORMATEX);
	fread( lpwf, FormatSize, 1, fp );

	// PCMの時は･･･
	if ( lpwf->wFormatTag == 1 )
	{
		// 追加データはありません
		lpwf->cbSize = 0;
	}

	fseek( fp, fmtDataSize-sizeof(WAVEFORMATEX), SEEK_CUR );

	//========================================================
	// Dataチャンク検索
	//========================================================
	while ( true )
	{
		// チャンクチェック
		fread( Chunk, sizeof(char), 4, fp );
		// 空ファイル？
		if ( feof( fp ) ) goto EXIT;
		// データチャンク？
		if ( strcmp( "data", Chunk ) == 0 )
		{
			break;
		}
		else
		{
			// データチャンクで無ければ次のチャンクへ
			DWORD size;

			fread( &size, sizeof(DWORD), 1, fp );
			fseek( fp, size, SEEK_CUR );
		}
	}

	// データチャンクのサイズを取得
	fread( &DataSize, sizeof(long), 1, fp );

	// データ本体を取得
	*lpData = new BYTE [ DataSize ];
	fread( *lpData, sizeof(BYTE), DataSize, fp );

	result = DataSize;

	// 終了
EXIT:
	if ( fp != NULL ) fclose( fp );

	return result;
}

/*

ＭＣＩを使用したサウンド、現在は未使用

// サウンドをオープンする
bool	gsSoundOpen(gsSound *pSound, char *szFileName)
{
	// ファイル名の退避用
	char *pName;

	// パラメータの設定
	pSound->m_OpenParam.dwCallback		= 0;
	pSound->m_OpenParam.lpstrDeviceType = 0;

	// ファイル名の退避
	pName = new char[lstrlen(szFileName)+1];
	lstrcpy(pName, szFileName);
	pSound->m_OpenParam.lpstrElementName = pName;
	
	// ファイルオープン
	MCIERROR mcirc;
	char strErr[1024];

	mcirc = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&pSound->m_OpenParam);

	if (mcirc)
	{	
		mciGetErrorString(mcirc , strErr , 1024);
		gsDebugPrintf("オープンエラー[%s]\n", strErr);
	}

	return	true;
}

// サウンドをクローズする
bool	gsSoundClose(gsSound *pSound)
{
	mciSendCommand(pSound->m_OpenParam.wDeviceID, MCI_CLOSE, 0, 0);
	delete [] pSound->m_OpenParam.lpstrElementName;

	pSound->m_OpenParam.lpstrElementName = 0;

	return	true;
}

// サウンドを最初から再生する
bool	gsSoundPlay(gsSound *pSound)
{
	static MCI_PLAY_PARMS mpp;
	MCIERROR mcirc;
	char strErr[1024];

	mcirc = mciSendCommand(pSound->m_OpenParam.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START,	0);
	if (mcirc)
	{	
		mciGetErrorString(mcirc , strErr , 1024);
		gsDebugPrintf("シークエラー[%s]\n", strErr);
	}
	mcirc = mciSendCommand(pSound->m_OpenParam.wDeviceID, MCI_PLAY, 0, (DWORD_PTR)&mpp);
	if (mcirc)
	{	
		mciGetErrorString(mcirc , strErr , 1024);
		gsDebugPrintf("再生エラー[%s]\n", strErr);
	}

	return	true;
}

// サウンドの停止
bool	gsSoundStop(gsSound *pSound)
{
	mciSendCommand(pSound->m_OpenParam.wDeviceID, MCI_STOP, 0, 0);

	return	true;
}

// サウンドが止まっているかどうかをテストする
bool	gsSoundisStopped(gsSound *pSound)
{
	MCI_STATUS_PARMS mciStatus;

	mciStatus.dwItem = MCI_STATUS_MODE;
	mciSendCommand(pSound->m_OpenParam.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&mciStatus);

	return (mciStatus.dwReturn != MCI_MODE_PLAY);
}
*/

//=====================================================================
//	FPS 表示処理
//=====================================================================

int gFPS1,gFPS2;
int gFPSTime1,gFPSTime2;

//---------------------------------------------------------------------
// FPS初期化
// 最初に呼び出す
//---------------------------------------------------------------------
void gsInitFPS(void)
{
	gFPS1=0; gFPS2=0;
	gFPSTime1=0;	gFPSTime2=0;
}

//---------------------------------------------------------------------
// FPS処理
// １ループに１回呼び出す
//---------------------------------------------------------------------
void gsSetFPS(void)
{
	gFPSTime2 = GetTickCount();
	gFPS1++;
	if (gFPSTime2 >= gFPSTime1+1000)
	{
		gFPSTime1 = gFPSTime2;
		gFPS2 = gFPS1;
		gFPS1 = 0;
	}
}

//---------------------------------------------------------------------
// FPS表示
//---------------------------------------------------------------------
void gsDrawFPS( int x, int y )
{
	gsDrawNum( x, y, gFPS2);
}


//---------------------------------------------------------------------------------------
//	■デバッグ用文字列のアウトプットウィンドウへの出力
//		デバッグに用いる関数。変数の値を表示することもできる。
//
//		int		gsDebugPrintf(char *szFormat, ...);
//
//		引数 [in]		szFormat	: 表示フォーマット
//			 [in]		...			: ０個以上の引数の指定
//				
//		戻り値			出力文字数
//
//		※表示できる最大文字数は、GS_MAX_DEBUG_STRING である。
//		※デバッグ時のみ表示される。
//---------------------------------------------------------------------------------------
int		gsDebugPrintf(char *szFormat, ...)
{
	
#ifdef	_DEBUG
	
	static char	szBuffer[GS_MAX_DEBUG_STRING];
	va_list		va;

	va_start( va, szFormat );
	vsprintf( szBuffer, szFormat, va);
	va_end( va );

	OutputDebugString( szBuffer );

	return lstrlen( szBuffer );

#else
	
	GS_NOT_USE_PARAM( szFormat );
	return 0;

#endif

}


//---------------------------------------------------------------------------------------
//	■エラーメッセージのアウトプットウィンドウへの表示
//		エラーコードに対応したエラーメッセージをアウトプットウィンドウに表示する．
//
//		void	gsErrorMsg(LPCSTR szPreMessage, HRESULT hErrorCode);
//
//		引数 [in]	szPreMessage	: エラー個所などを示す文字列
//		引数 [in]	hErrorCode		: エラーコード
//
//		戻り値		なし
//---------------------------------------------------------------------------------------
void	gsErrorMsg(LPCSTR szPreMessage, HRESULT hErrorCode)
{
	gsDebugPrintf("%s[%s]\n", szPreMessage, DXGetErrorString(hErrorCode));
}

void ShowConsole()//★ デバッグ用宣言(削除可)
{
	/*コンソールウィンドウを作成*/
	AllocConsole();
	freopen(
		"CONIN$",						//新しいファイルのパス
		"r",							//アクセス許可の種類
		stdin							//FILE構造体へのポインタ
		);
	freopen(
		"CONOUT$",
		"w",
		stdout
		);
}