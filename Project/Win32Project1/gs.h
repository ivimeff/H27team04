//=====================================================================
//	暫定 3D 学校ライブラリ ヘッダーファイル
//
//	ファイル名	【 gs.h 】	Ver 2.3
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

#ifndef	__GS_H
#define	__GS_H

//---------------------------------------------------------------------
//	■ コンパイラ，リンカへの指示
//---------------------------------------------------------------------

//	ワーニング(警告)エラー表示抑制
#pragma warning(disable:4996)	// sprintf, strcpy などの使用時の警告エラー
#pragma warning(disable:4819)	// 文字コードページに関する警告エラー

// 使用文字列をマルチバイトコード(SJIS)利用にする
#ifdef UNICODE		// UNICODE取り消し
	#undef UNICODE
	#undef _UNICODE
#endif

#ifndef _MBCS		// SJIS使用
	#define _MBCS
#endif

//	ライブラリの参照指示
#pragma comment(lib, "d3d9.lib"	)			// Direct3D ライブラリ
#ifdef _DEBUG
	#pragma comment(lib, "d3dx9d.lib" )		// Direct3D Extension ライブラリ
#else										//  Debug   バージョンと
	#pragma comment(lib, "d3dx9.lib"  )		//  Release バージョンがある
#endif

#pragma comment(lib, "dsound.lib") 
#pragma comment(lib, "dinput8.lib" )		// DirectInput
#pragma comment(lib, "dxguid.lib"  )		// Guid
#pragma comment(lib, "winmm.lib"   )		// マルチメディア
#pragma comment(lib, "dxerr.lib"  )			// DirectX エラー処理ユーティリティ


//---------------------------------------------------------------------
//	■ インクルード
//---------------------------------------------------------------------
#include <windows.h>		// Windows API
#include <d3d9.h>			// Direct3D
#include <d3dx9.h>			// Direct3D Extension（DirectX 拡張）
#define  DIRECTINPUT_VERSION 0x0800
#include <dinput.h>			// DirectInput
#include <dsound.h>
#include <dxerr.h>			// DirectX エラー処理ユーティリティ
#include <mmsystem.h>		// timeGetTime
#include <cstdlib>			// srand, rand


//---------------------------------------------------------------------
//	■ マクロ
//---------------------------------------------------------------------

// π
#define		GSPI				D3DX_PI

// 乱数関係	(実装を XorShift アルゴリズムに変更予定)
#define		gsRandomize()		srand((unsigned)timeGetTime())
#define		gsRandom(n)			(int)( ((long)rand() * (n))/ (RAND_MAX+1) )

// カラー
#define		GSRGB(r,g,b)		D3DCOLOR_XRGB((r),(g),(b))
#define		GSARGB(a,r,g,b)		D3DCOLOR_ARGB((a),(r),(g),(b))

// キー押下状態の取得
#define		gsKeyCheck(vk)		(gsKeyState(vk) == GSKS_PRESS)

// ウィンドウサイズ
#define		GS_WINDOW_WIDTH		64 * 16
#define		GS_WINDOW_HEIGHT		64 * 9

// アプリケーションの強制終了
#define		gsQuitApplication()		PostQuitMessage(0)

// メモリ解放用マクロ
#ifndef		GS_SAFE_RELEASE
	#define GS_SAFE_RELEASE(p)		{ if(p) { (p)->Release(); (p) = NULL; } }
#endif
#ifndef		GS_SAFE_DELETE
	#define GS_SAFE_DELETE(p)		{ if(p) { delete (p);     (p) = NULL; } }
#endif
#ifndef		GS_SAFE_DELETE_ARRAY
	#define	GS_SAFE_DELETE_ARRAY(p)	{ if(p) { delete [] (p);  (p) = NULL; } }
#endif

// デバッグ文字列表示
#define		GS_MAX_DEBUG_STRING		256			// デバック文字列最大文字数
#define		GS_NOT_USE_PARAM(x)		(x) = (x)	// 未使用引数の警告エラーを無視させる



//---------------------------------------------------------------------
//	■ 型宣言
//---------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////
// テクスチャー
typedef		LPDIRECT3DTEXTURE9	gsTexture;

///////////////////////////////////////////////////////////////////////
//	ベクトル
typedef		D3DXVECTOR2			gsVec2;
typedef		D3DXVECTOR3			gsVec3;

///////////////////////////////////////////////////////////////////////
//	カラー
typedef		D3DCOLOR			gsColor;

//---------------------------------------------------------------------
//	■ 頂点フォーマット
//---------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////
//	トランスフォーム済み，ライティング済み 頂点フォーマット
#define	FVF_TLVERTEX	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

struct gsTLVertex
{
    gsVec3		pos;		// 位置(2D座標) (x, y, z)
    float		rhw;		// 1/w
	gsColor		color;		// 頂点カラー(ディフューズ色)
    gsVec2		uv;			// テクスチャー座標 (u, v)
};

///////////////////////////////////////////////////////////////////////
//	ライティング済み 頂点フォーマット
#define	FVF_LVERTEX		( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

struct gsLVertex
{
    gsVec3		pos;		// 位置 (x, y, z)
	gsColor		color;		// 頂点カラー(ディフューズ色)
    gsVec2		uv;			// テクスチャー座標 (u, v)
};

///////////////////////////////////////////////////////////////////////
//	頂点フォーマット
#define	FVF_VERTEX		( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )

struct gsVertex
{
    gsVec3		pos;		// 位置 (x, y, z)
	gsVec3		normal;		// 法線ベクトル
    gsVec2		uv;			// テクスチャー座標 (u, v)
};


//---------------------------------------------------------------------
//	■ enum型
//---------------------------------------------------------------------
// キーの状態
enum	_GSKS
{
	GSKS_RELEASE	= 0,	// 離されている
	GSKS_DOWN		= 1,	// 押下直後
	GSKS_PRESS		= 2,	// 押しっぱなし	
	GSKS_UP			= 3,	// 離した直後
};


//---------------------------------------------------------------------
//	■関数プロトタイプ宣言
//---------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////
// メインシステム固有の関数
INT		WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT );
LRESULT	WINAPI gsMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
void	gsInitD3D( HWND hWnd, bool WindowMode );


///////////////////////////////////////////////////////////////////////
// 共通機能の関数
void	gsLoadTexture(gsTexture *pTexture,  char *str, gsColor colorKey);
void	gsReleaseTexture(gsTexture texture);
void	gsCleanup();
void	gsRender();

void	gsSetNormalColor(void);
void	gsSetAddColor(void);


///////////////////////////////////////////////////////////////////////
// 2D 関係の関数
void	gsDraw2DClear (gsColor cr);

void	gsDraw2D	  (gsTexture texture, 
					   int sx, int sy, 
					   gsColor cr = GSARGB(255,255,255,255) );

void	gsDraw2DEx	  (gsTexture texture,
					   int sx, int sy, int sw, int sh, 
					   gsColor color = GSARGB(255,255,255,255) );

void	gsDraw2DPart  (gsTexture texture, 
					   int sx, int sy, int tx, int ty, int tw, int th,
					   gsColor cr = GSARGB(255,255,255,255) );

void	gsDraw2DPartEx(gsTexture texture, 
					   int sx, int sy, int sw, int sh, int tx, int ty, int tw, int th, 
					   float angle, gsColor color);


int		gsGetTextureWidth (gsTexture texture);
int		gsGetTextureHeight(gsTexture texture);


///////////////////////////////////////////////////////////////////////
// 基本図形の描画

// 直線
void	gsDraw2DLine	 (int x1, int y1, int x2, int y2, gsColor color);

// 長方形
void	gsDraw2DRectangle(int x1, int y1, int x2, int y2, gsColor color,
													bool bFillMode = false);

// 円
void	gsDraw2DCircle	 (int cx, int cy, int r,  gsColor color, 
													bool bFillMode = false);	


///////////////////////////////////////////////////////////////////////
// フォント関係
void	gsInitFont();
void	gsReleaseFont();
void	gsDrawText( int x, int y, char *str );
void	gsDrawNum ( int x, int y, int a );

void	gsSetFont(int size, char *szFontName = "ＭＳ ゴシック" );	
int		gsDrawPrintf	  (int x, int y, gsColor color, char *szFormat, ...);
int		gsDrawPrintfShadow(int x, int y, gsColor color, char *szFormat, ...);


///////////////////////////////////////////////////////////////////////
//	キーの押下状態を調べる関数
int		gsKeyState(UINT vk);


// マウスの位置に関係する関数 <未実装>
//int	gsGetMouseX(void);
//int	gsGetMouseY(void);
//void	gsSetMouseX(int posx);
//void	gsSetMouseY(int posy);


///////////////////////////////////////////////////////////////////////
// 3D 関係の関数
void	gsSetCamera(float x, float y, float z,float dir);

void	gsSetCullOff();
void	gsSetCullOn();

void	gsSetLightOn();
void	gsSetLightOff();
void	gsSetLight(float x, float y, float z, gsColor color);

void	gsSetZBufferOn();
void	gsSetZBufferOff();

void	gsDrawBox(gsTexture texture, float x, float y, float z, float t);
void	gsSetMatrices(float x, float y, float z, float fAngle);
void	gsSetMatrices(float x, float y, float z, float fAngle, float scalex, float scaley);
void	gsDrawBox2(gsTexture texture, float x, float y, float z, float t);
void	gsDrawBoxSize(gsTexture texture, float x, float y, float z, float t, int color, float scalex, float scaley);

///////////////////////////////////////////////////////////////////////
//	フレーム構造体 
//	※合成変換行列を計算するときに便利なように拡張している
struct gsFrame : public D3DXFRAME
{
	// 各フレームに適用する合成済み変換行列
	D3DXMATRIXA16	CombinedTransformMatrix;
};


///////////////////////////////////////////////////////////////////////
//	メッシュコンテナ構造体
//	X File 中の さまざまなデータを保持するための構造体
//	※複数のテクスチャを利用できるように拡張
//	※スキンメッシュを扱えるように拡張
struct gsMeshContainer : public D3DXMESHCONTAINER
{
	///////////////////////////////////////////////////////////////////
	// テクスチャ
	gsTexture	*ppTextures;

	///////////////////////////////////////////////////////////////////
	// スキン情報
	LPD3DXMESH				pOrigMesh;				// オリジナルのメッシュ情報

	LPD3DXATTRIBUTERANGE	pAttributeTable;		// 属性テーブル

	DWORD					NumInfl;				// 影響を受けるボーンの最大数
	DWORD					NumBones;				// ボーン数

	D3DXMATRIX*				pBoneOffsetMatrices;	// ボーンのオフセット行列

	LPD3DXBUFFER			pBoneBuffer;			// ボーンデータ作業用
	D3DXMATRIX**			ppBoneMatrixPtrs;

	DWORD					NumPaletteEntries;		// パレットエントリ数

	// ソフトウェアで対応する場合に利用される(★未実装)
	bool					UseSoftwareVP;
	DWORD					iAttributeSW;
};


///////////////////////////////////////////////////////////////////////
//	gsMesh 型
struct gsMesh
{
	// アニメーションしないメッシュの場合に使用
	LPD3DXMESH		pMesh;				// メッシュ
	D3DMATERIAL9*	pMeshMaterials;		// マテリアル情報
	gsTexture*		pMeshTextures;		// テクスチャ情報
	DWORD			dwNumMaterials;		// マテリアルの数

	// アニメーションするメッシュの場合に使用
	LPD3DXFRAME					pFrameRoot;
	LPD3DXANIMATIONCONTROLLER	pAnimController;

	// コンストラクタ
	gsMesh()
	{
		pMesh			= 0;
		pMeshMaterials	= 0;
		pMeshTextures	= 0;
		dwNumMaterials	= 0;

		pFrameRoot		= 0;
		pAnimController	= 0;
	}
};

// 階層構造のないメッシュで利用する関数
HRESULT	gsLoadX   ( gsMesh *m, char *pXFileName );
void	gsDrawX   ( gsMesh *m, float x, float y, float z, float t );
HRESULT	gsReleaseX( gsMesh* pReleaseMesh );

// 階層構造のあるメッシュで利用する関数
HRESULT	gsLoadXA   ( gsMesh* pMesh, char* pXFileName );
void	gsDrawXA   ( gsMesh *m, float x, float y, float z, float t, double animePastTime );
HRESULT	gsReleaseXA( gsMesh *pReleaseMesh );

///////////////////////////////////////////////////////////////////////
//	サウンド関係
//	※同時再生(MIDIを除く)をする場合には，alias(別名)をつければいい

//	gsSound 型
//struct	gsSound
//{
//	MCI_OPEN_PARMS	m_OpenParam;
//
//	// コンストラクタ
//	gsSound()
//	{
//		m_OpenParam.wDeviceID		 = 0;
//		m_OpenParam.lpstrDeviceType	 = 0;
//		m_OpenParam.lpstrAlias		 = 0;
//		m_OpenParam.lpstrElementName = 0;
//		m_OpenParam.dwCallback		 = 0;
//	}
//};

//	サウンド操作関数
//bool	gsSoundOpen		(gsSound *pSound, char *szFileName);
//bool	gsSoundClose	(gsSound *pSound);
//bool	gsSoundPlay		(gsSound *pSound);
//bool	gsSoundStop		(gsSound *pSound);
//bool	gsSoundisStopped(gsSound *pSound);



///////////////////////////////////////////////////////////////////////
// ＦＰＳ処理
void	gsInitFPS(void);
void	gsSetFPS(void);
void	gsDrawFPS(int x, int y);

///////////////////////////////////////////////////////////////////////
// デバッグ用文字列の表示
int		gsDebugPrintf(char *szFormat, ...);
void	gsErrorMsg(LPCSTR szPreMessage, HRESULT hErrorCode);

void	gsMessage(char str[]);



// ■DirectInput用

// パッド押下状態の取得
#define		gsJoyPadCheck(vk1, vk2)		(gsGetJoyPadState( vk1, vk2 ) == GSKS_PRESS)

int gsGetJoyPadState( int , int );	// ジョイパッド情報取得

// ジョイパッド入力識別用定数
#define JOYPAD_UP		(1 << 9)					// 上(ジョイパッド)
#define JOYPAD_DOWN		(1 << 10)					// 下(ジョイパッド)
#define JOYPAD_LEFT		(1 << 11)					// 左(ジョイパッド)
#define JOYPAD_RIGHT	(1 << 12)					// 右(ジョイパッド)

// ボタン押し情報識別用定数
#define JOYPAD_BUTTON1		(1 << 13)					// ボタン 1
#define JOYPAD_BUTTON2		(1 << 14)					// ボタン 2
#define JOYPAD_BUTTON3		(1 << 15)					// ボタン 3
#define JOYPAD_BUTTON4		(1 << 16)					// ボタン 4
#define JOYPAD_BUTTON5		(1 << 17)					// ボタン 5
#define JOYPAD_BUTTON6		(1 << 18)					// ボタン 6
#define JOYPAD_BUTTON7		(1 << 19)					// ボタン 7
#define JOYPAD_BUTTON8		(1 << 20)					// ボタン 8
#define JOYPAD_BUTTON9		(1 << 21)					// ボタン 9
#define JOYPAD_BUTTON10		(1 << 22)					// ボタン10


// 内部用

// 入力リスト
#define DIDEVICE_BUFFERSIZE	100						// デバイスに設定するバッファ・サイズ
#define KEY_BUFFRSIZE 256

// 十字キー入力識別用定数
#define KEY_UP			(1 << 1)					// 上(十字キー)
#define KEY_DOWN		(1 << 2)					// 下(十字キー)
#define KEY_LEFT		(1 << 3)					// 左(十字キー)
#define KEY_RIGHT		(1 << 4)					// 右(十字キー)
#define KEY_RIGHTUP		(1 << 5)					// 右上(十字キー)
#define KEY_RIGHTDOWN	(1 << 6)					// 右下(十字キー)
#define KEY_LEFTDOWN	(1 << 7)					// 左下(十字キー)
#define KEY_LEFTUP		(1 << 8)					// 左上(十字キー)

// ジョイパッド設定構造体
typedef struct __INPUT{
	LPDIRECTINPUT8       m_pDInp;					// Directinput
	LPDIRECTINPUTDEVICE8 m_pDIDKey;					// DirectInputデバイス（キーボード用）
	LPDIRECTINPUTDEVICE8 m_pDIDJoy[16];				// DirectInputデバイス（ジョイパッド用）
	DIDEVCAPS			 m_diDevCaps;				// ジョイパッドの能力
	BYTE				 m_KeyState[KEY_BUFFRSIZE];	// キーボード情報
	int					 m_InpState[2][16];			// 現在の入力状態
}SYSINPUT;

extern SYSINPUT          g_sysJoy;
extern int				 g_JoyPadCount;
extern int				 g_JoyPadMax;
extern int				 g_NowNum;

// コールバック
BOOL CALLBACK EnumJoyPadsCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

bool gsJoyCheck( int Num, int State );
bool InitJoyPad();		// ジョイパッドの初期化
void Update_JoyPadInfo();	// ジョイパッドの状態制御
void CheckPad_ParallelTranslation();	// キーボード･パッドの入力情報から平行移動行列を作成
void CheckPad_Rotation();	// キーボード･パッドの入力情報から回転行列を作成
bool CheckPad_Reset();	// パッドの座標リセット処理情報を取得




// DirectSound関連
#define  LOOP_ON    1    // 波形データをループ再生する
#define  LOOP_OFF   0    // 波形データをループ再生しない　
typedef		LPDIRECTSOUNDBUFFER8	gsSound;

void gsLoadSound( gsSound *sound, char *str );
void gsReleaseSound( gsSound sound );
void gsPlaySound( gsSound sound, int loop_flag);
void gsStopSound( gsSound sound);


// 内部用関数
bool InitDirectSound();
gsSound LoadWave( char *file );
DWORD GetWaveData( char *file, LPBYTE *lpData, WAVEFORMATEX *lpwf );

#endif		// __GS_H
