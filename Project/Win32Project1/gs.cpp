//=====================================================================
//	�b�� 3D���C�u����
//
//	�t�@�C����	�y gs.cpp �z	Ver 2.3
//
//	�� ����
//		----------- Ver  2.3 ------------------------------------------
//		2012.4.8	GsMessage��ǉ��BStart+Sellect�ŏI��
//		----------- Ver  2.2 ------------------------------------------
//		2011.11.10	gs.h��C++���g�p�������̕s�����������̂ŕύX���܂����B
//		----------- Ver  2.1 ------------------------------------------
//		2011.09.21	gsGetJoyPadState�̊֐�����ύX���܂����B
//		----------- Ver  2.0 ------------------------------------------
//		2011.09.17	�T�E���h�iWAV�̂݁j�ƃp�b�h���͂�ǉ������B
//		----------- Ver  1.8.1 ------------------------------------------
//		2011.06.21	gsDraw2DEx���쐬
//		----------- Ver  1.8 --------------------------------------------
//		2011.05.03	�������̊֐������O��D3�������̂�gs�֏C������
//		----------- Ver  1.7.1 ------------------------------------------
//		2010.05.28	�摜�̉�]�����������Ƃ���
//					gsDraw2DEx()  gsDraw2DPartEx()
//		2010.05.09	D3DCOLOR�^ �� gsColor�^ �Ƃ���
//		2010.05.09	�w�Z���C�u�����̃t�@�C������ύX����
//					main.h �� gs.h		main.cpp �� gs.cpp
//					�֐����ŁCD3�` �� gs�` �ƕύX���C���ꊴ����������
//		2010.05.09	dxerr9.h, dxerr9.lib�� dxerr.h, dxerr.lib�ɕύX����
//		----------- Ver  1.7 ------------------------------------------
//		2009.12.21	�摜��2D�`��̍ہC�摜�������o�O���C������
//		2009.12.21	�摜��2D�`��̍ہC���_�J���[���w��ł���悤�ɂ���
//					D3Draw2D, D3Draw2DPart �̍Ō�̈��������_�J���[�ƂȂ�
//		2009.09.09	mci�R�}���h�ɂ��T�E���h�Đ�������ǉ�����
//					gsSound �^�̒ǉ�
//					gsSoundOpen(), gsSoundClose()
//					gsSoundPlay(), gsSoundStop()
//					gsSoundisPlaying()
//		2009.08.22	�{�[���� X�t�@�C���ɑΉ�����(����:������)
//		2009.07.30	�f�o�b�O�p��������o�̓E�B���h�E�ɕ\������
//					gsDebugPrintf() �̒ǉ� (Debug�o�[�W�����̂ݗL��)
//		2009.07.30	�~�̕`��֐�	D3Draw2DCircle() �̒ǉ�
//					�O���[�o���ϐ� g_Sinf[360], g_Cosf[360] �̒ǉ�
//		2009.07.28	�����`�`��֐�	D3Draw2DRectangle() �̒ǉ�
//		2009.07.28	�����`��֐�	D3Draw2DLine() �̒ǉ�
//		2009.07.23	gsDrawPrintfShadow() �̒ǉ�
//					�ʏ�̕�����\���ł́C�w�i�̐F�ɂ��C���Â炢�ꍇ
//					�Ɏg�p����D�������e������
//		2009.06.23	�e�L�X�g�\���̍ۂ̃t�H���g�T�C�Y�C�t�H���g��
//					�ύX�ł���֐� gsSetFont() ��ǉ�����
//		2009.06.11	�L�[�̏�Ԃ𒲂ׂ�֐� gsKeyState() ��ǉ�����
//					enum�^ GSKC_ �� GSKS_ �ɕύX����
//		2009.06.10	gsKeyCheck �}�N����ǉ�����
//					GSKEYCHECK ��, �폜����
//		2009.06.10	LPDIRECT3DTEXTURE9�^�� gsTexture�^�Ƃ���
//		2009.06.10	D3Draw2D() �̈�����, z���W�� �f�t�H���g�� 0 �Ƃ���
//					������,�@Z�o�b�t�@�𖳌���, ���������s���悤�ɂ���
//		2009.06.07	gsDrawPrintf() �̒ǉ�
//		2009.06.07	�E�B���h�E�̑傫�����}�N����
//					��:GS_WINDOW_WIDTH  ����:GS_WINDOW_HEIGHT
//
//=====================================================================

//---------------------------------------------------------------------
//	���C���N���[�h
//---------------------------------------------------------------------
#include "gs.h"

#include <d3d9.h>
#include <d3dx9.h>
#include <mmsystem.h>
#include <cstdio>

//---------------------------------------------------------------------
//	���}�N��
//---------------------------------------------------------------------
#define APP_NAME "MAIN"

//---------------------------------------------------------------------
//	���֐��v���g�^�C�v�錾
//---------------------------------------------------------------------

// �Q�[�����̊֐��̐錾
void	GameInit(void);
void	GameLoop(void);
void	GameTerm(void);

void	ShowConsole();//�� �f�o�b�O�p�錾(�폜��)

// static �֐��̐錾
static	void	_gsKeyStateUpdate();
static	void	_gsDraw2DPart(gsTexture texture, float x, float y, float z, float x1, float y1, int xsize, int ysize);
static	void	_GameAppInit();

///////////////////////////////////////////////////////////////////////
// �A�j���[�V�����t�����b�V���֌W

// �{�[���ϊ��s��̐ݒ�
static	HRESULT	_gsInitBoneMatrics(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrame);
static	HRESULT	_gsInitBoneMatricsOnMesh(LPD3DXFRAME pFrameRoot,LPD3DXMESHCONTAINER pMeshContainerBase);

// �{�[���ϊ��s��̍X�V
static	void	_gsUpdateBoneMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix);
static	void	_gsDrawFrame( LPD3DXFRAME pFrame );
static	void	_gsDrawMeshContainer( LPD3DXMESHCONTAINER pMeshContainerBase, LPD3DXFRAME pFrameBase );


//---------------------------------------------------------------------
//	���O���[�o���ϐ�
//---------------------------------------------------------------------
static	LPDIRECT3D9			g_pD3D        = NULL;	// Direct3D
static	LPDIRECT3DDEVICE9	g_pd3dDevice  = NULL;	// Direct3D Device
static	D3DCAPS9			g_d3dcaps;				// Direct3D Device ���\
static	bool				g_bActive = false;		// �A�v�������p�\��?

static HINSTANCE g_hInst;
static HWND      g_hWnd;

int gMsgMode;
char gMsgStr[100];

// DirectInput���
SYSINPUT            g_sysJoy;
int					g_JoystickCount;
int					g_JoystickMax;
int					g_NowNum;

// �L�[�{�[�h�̉������
static	BYTE	_KeyBuffer[2][256];
static	int		_KeyBuffNo = 0;

// DirectSound�֘A
LPDIRECTSOUND8		 g_lpDirectSound    = NULL;
LPDIRECTSOUNDBUFFER	 g_lpPrimaryBuffer  = NULL;


// ���Ԑ���
static	DWORD	g_oldTime;

// sin cos 
float	g_Sinf[360];		// sin 0���` cos 359���̒l��ێ�
float	g_Cosf[360];		// cos 0���` cos 359���̒l��ێ�


//=====================================================================
//	���C������
//=====================================================================

//---------------------------------------------------------------------
//	��Windows ���C��
//---------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
#if defined(DEBUG) | defined(_DEBUG)
  //  _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

#ifdef	_DEBUG					// _DEBUG ���[�h �� �E�B���h�E���[�h
	bool WindowMode = true;
#else							// _RELESE���[�h �� �t���X�N���[�����[�h
	bool WindowMode = false;
#endif

	// ���b�Z�[�W�p
	gMsgMode=0;

    // �E�B���h�E�̐ݒ�
    WNDCLASSEX wc = 
	{
		sizeof(WNDCLASSEX), 
		CS_CLASSDC, 
		gsMsgProc, // �R�[���o�b�N�֐��̎w��
		0L, 0L,
		GetModuleHandle(NULL), NULL, 
		LoadCursor(NULL, IDC_ARROW), // �J�[�\���̎w��
		NULL, NULL,
		APP_NAME, NULL
	};

    RegisterClassEx( &wc );

	ShowConsole();//�� �f�o�b�O�p�錾(�폜��)

	g_hInst = hInst;

    // �E�B���h�E�̍쐬
    g_hWnd = CreateWindow( 
		APP_NAME, "�Q�[�����ށ@���{�H�w�@",
		WS_POPUP | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX, 
        //WS_OVERLAPPEDWINDOW, 
		100, 100,						// �E�B���h�E�̕\���ʒu
		GS_WINDOW_WIDTH, GS_WINDOW_HEIGHT,	// �E�B���h�E�̑傫��
		GetDesktopWindow(), NULL, wc.hInstance, NULL );

	// �������A�O�g�Ȃǂ��܂߂��T�C�Y�Ȃ̂ŁA
	// �E�B���h�E�T�C�Y���Đݒ肷��
	RECT	rect;
	int		ww, wh;
	int		cw , ch;
	 
	// �N���C�A���g�̈�̊O�̕����v�Z
	GetClientRect( g_hWnd , &rect );
	cw = rect.right  - rect.left;
	ch = rect.bottom - rect.top;
	
	// �E�B���h�E�S�̂̉����̕����v�Z
	GetWindowRect( g_hWnd , &rect );
	ww = rect.right  - rect.left;
	wh = rect.bottom - rect.top;
	ww = ww - cw;
	wh = wh - ch;
	 
	// �E�B���h�E�T�C�Y�̍Čv�Z
	ww = GS_WINDOW_WIDTH  + ww;
	wh = GS_WINDOW_HEIGHT + wh;
	 
	// �E�B���h�E�T�C�Y�̍Đݒ�
	SetWindowPos(g_hWnd, HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE);

	// �t���X�N���[�����[�h�ł���΁C�}�E�X�J�[�\������������	// 2009.06.23 �ǉ�
	if ( !WindowMode )
	{
		while ( ShowCursor(false) > 0 );
	}

	// �Q�[���A�v���P�[�V���� ������
	_GameAppInit();

    // Direct3D������
	gsInitD3D( g_hWnd, WindowMode );

	// DirectSound������
	InitDirectSound();

    // �f�t�H���g�t�H���g������
	gsInitFont();

	// DirectInput������
	InitJoyPad();

	// �E�B���h�E�̕\��
	ShowWindow( g_hWnd, SW_SHOWDEFAULT );
	UpdateWindow( g_hWnd );

	g_bActive = true;

	// �Q�[��������
	GameInit();

    // ���b�Z�[�W���[�v
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
				_gsKeyStateUpdate();	// �L�[�̉�����Ԃ̍X�V
				gsRender();
			}
		}

		if  (gsGetJoyPadState(0,JOYPAD_BUTTON10)==GSKS_PRESS &&
				gsGetJoyPadState(0,JOYPAD_BUTTON9)==GSKS_PRESS)
		{
			break;
		}
    }

	// �Q�[���I��
	GameTerm();

	g_bActive = false;

	// �t�H���g�̉��
	gsReleaseFont();

	// �V�X�e���̉��
    gsCleanup();

	// �o�^�̉���
    UnregisterClass( APP_NAME, wc.hInstance );

    return 0;
}


//---------------------------------------------------------------------
//	�R�[���o�b�N�֐�
//---------------------------------------------------------------------
LRESULT WINAPI gsMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	// ���b�Z�[�W�ɂ�菈��
    switch( msg )
    {
	case WM_DESTROY:				// �E��́~�ŏI���Ȃ�A������Ăяo���ďI������B
		g_bActive = false;
		PostQuitMessage( 0 );
        return 0;
			
	case WM_KEYDOWN:				// �L�[�������ꂽ
		if ( wParam == VK_ESCAPE )	// ESC �L�[�������ꂽ��Q�[���A�v�����I������
		{
			g_bActive = false;
			PostQuitMessage(0);
		}
		return 0;
    }

	// ����ȊO�̏����̓V�X�e���ɔC����
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

//---------------------------------------------------------------------
//	���Q�[���A�v���P�[�V����������
//---------------------------------------------------------------------
void	_GameAppInit()
{
	// sin, cos �̒l�����炩���ߎZ�o���Ă���
	// (�~�̕`�� (gsDraw2DCircle)�ŗ��p���Ă���)
	for (int i=0; i<360; i++)
	{
		g_Sinf[i] = sinf( D3DXToRadian(i) );
		g_Cosf[i] = cosf( D3DXToRadian(i) );
	}
}



//---------------------------------------------------------------------
//	���b�Z�[�W�\��
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
//	Direct3D�̏�����
//---------------------------------------------------------------------
void gsInitD3D( HWND hWnd, bool WindowMode )
{
	HRESULT		rc;		// ���^�[���R�[�h

    // Direct3D �I�u�W���N�g����
    g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

    // �\���̂̐ݒ�
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferCount  = 1;
	
	D3DDISPLAYMODE d3ddm;
    g_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

	// �E�B���h�E���[�h���ǂ��� �ɂ��p�����|�^��ς���
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
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;	// vsync ��҂�
//	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	// �R�c�p
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	///////////////////////////////////////////////////////////////////////
	// Direct3D �f�o�C�X����

	// �`��:HAL,  ���_����:HARDWARE �Ő���
	rc =	g_pD3D->CreateDevice(  D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
								   D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice );
	if ( SUCCEEDED(rc) )
			gsDebugPrintf( "��gsInitD3D : Direct3D �f�o�C�X �� �`��:HAL ���_����:HARDWARE �Ő���\n" );

	// ��L�����s�Ȃ�C�`��:HAL�C���_����:SOFTWARE
	if ( FAILED( rc ) )
	{
		rc = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
								   D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice );
		if ( SUCCEEDED(rc) )
			gsDebugPrintf( "��gsInitD3D : Direct3D �f�o�C�X �� �`��:HAL ���_����:SOFTWARE �Ő���\n" );
	}

	// ��L�����s�Ȃ�C�`��:REF�C���_����:HARDWARE
	if ( FAILED( rc ) )
	{
		rc = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
								   D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice );
		if ( SUCCEEDED(rc) )
			gsDebugPrintf( "��gsInitD3D : Direct3D �f�o�C�X �� �`��:REF ���_����:HARDWARE �Ő���\n" );
	}

	// ��L�����s�Ȃ�C�`��:REF�C���_����:SOFTWARE
	if ( FAILED( rc ) )
	{
		rc = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
								   D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice );
		if ( SUCCEEDED(rc) )
			gsDebugPrintf( "��gsInitD3D : Direct3D �f�o�C�X �� �`��:REF ���_����:SOFTWARE �Ő���\n" );
	}

	// ���C�e�B���O���[�h�� OFF �ɂ���
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	// �W���I�ȐF�̐ݒ�
	g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
	g_pd3dDevice->SetRenderState( D3DRS_BLENDOP,	D3DBLENDOP_ADD );
	g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,	D3DBLEND_SRCALPHA );
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,	D3DBLEND_INVSRCALPHA );

	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,	 D3DTOP_MODULATE);
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE	);	// 1�߂̈������e�N�X�`���Ƃ���
	g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE	);	// 2�߂̈������ԃf�B�t���[�Y�F�Ƃ���

	// Z�o�b�t�@���I���ɂ���
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	// �f�o�C�X�̐��\������Ă���
	g_pd3dDevice->GetDeviceCaps( &g_d3dcaps );
}


//---------------------------------------------------------------------
// �g�p�����I�u�W�F�N�g�̉��
//---------------------------------------------------------------------
void gsCleanup()
{
    GS_SAFE_RELEASE( g_pd3dDevice );	// Direct3D �f�o�C�X
    GS_SAFE_RELEASE( g_pD3D	);			// Direct3D
}


//---------------------------------------------------------------------
//	�����_�����O�i�`��j�ƃQ�[�������Ăяo��
//---------------------------------------------------------------------
void gsRender()
{
    // �o�b�N�o�b�t�@�Ƃy�o�b�t�@�����ŃN���A
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

    // �V�[���J�n
    g_pd3dDevice->BeginScene();

	// �W���C�p�b�h�����X�V
	Update_JoyPadInfo();

	if (gMsgMode==0)
	{
		// �Q�[�����[�v���Ăяo��(���[�U�[����`)
		GameLoop();
	}
	else
	{
		// ���b�Z�[�W�\��
		gsDrawText(10,10,gMsgStr);
	}

	// �V�[���I��
    g_pd3dDevice->EndScene();

    // �o�b�N�o�b�t�@���f�B�X�v���C�ɕ\��
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}


//=====================================================================
//	���ʏ���
//=====================================================================

//---------------------------------------------------------------------
//	���L�[�̏�Ԏ擾
//		int gsKeyState( UINT vk );
//
//		���� [in]	vk	: ���ׂ�L�[�̉��z�L�[�R�[�h ( �͈� 0 �` 255 )
//
//		�߂�l		GSKS_RELEASE	: ������Ă���	= 0
//					GSKS_DOWN		: ��������		= 1
//					GSKS_PRESS		: �������ςȂ�	= 2
//					GSKS_UP			: ����������	= 3
//---------------------------------------------------------------------
int gsKeyState( UINT vk )
{
	// ���z�L�[�R�[�h���@0�`255 �͈̔͊O�Ȃ�, GSKC_RELEASE ��Ԃ�
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

	return GSKS_RELEASE;	// (�N���肦�Ȃ�)
}


//---------------------------------------------------------------------
//	���L�[�̏�Ԃ��X�V����
//		static	void _gsKeyStateUpdate();
//
//		����	�Ȃ�
//		�߂�l	�Ȃ�
//
//		���)	�L�[��Ԃ��X�V����. �ȉ��̃o�b�t�@���X�V����D
//				static	BYTE	_KeyBuffer[2][256];
//				static	int		_KeyBuffNo = 0;
//---------------------------------------------------------------------
static	void _gsKeyStateUpdate()
{
	_KeyBuffNo = 1 - _KeyBuffNo;
	GetKeyboardState( _KeyBuffer[_KeyBuffNo] );
}

//---------------------------------------------------------------------
//	���e�N�X�`����ǂݍ���
//		void gsLoadTexture(gsTexture *texture,  char *str, UINT colorKey)
//
//		���� [out]	texture		: �e�N�X�`�����Ǘ�����ϐ��ւ̃|�C���^
//		���� [in]	str			: �e�N�X�`���̃t�@�C����
//		���� [in]	colorKey	: ���߂�����F (0xaarrggbb)
//
//		�߂�l	�Ȃ�
//---------------------------------------------------------------------
void gsLoadTexture(gsTexture *pTexture,  char *str, gsColor colorKey)
{
	// �e�N�X�`�������łɊ��蓖�Ă��Ă���Ȃ�C�������
	// ���[�J���ϐ��̏ꍇ�CNULL ���ݒ肳��Ă��Ȃ��\������ ���댯�I
	//if ( *texture != NULL )
	//{
	//	D3ReleaseTexture( *texture );
	//	*texture = NULL;
	//	OutputDebugString( "�ȑO�̃e�N�X�`�����������\n" );
	//}

	//	D3DXGetImageInfoFromFile �֐��ŁC�t�@�C�����̉摜�𑜓x�𓾂邱�Ƃ��ł���D
	//	���̂��Ƃɂ��C�摜�T�C�Y�� 2�ׂ̂���ł���K�v���Ȃ��Ȃ�D
	//	���_��̂���C�摜�̓ǂݍ��݂��\�ƂȂ�D

	// �e�N�X�`���̓ǂݍ���
	if ( FAILED( D3DXCreateTextureFromFileEx(
		g_pd3dDevice,				// Direct3D �f�o�C�X
		str,						// �t�@�C����
		D3DX_DEFAULT, D3DX_DEFAULT,	// �����������e�N�X�`���̕��ƍ���
		1,							// �~�b�v���x���̐�
		0,							// �e�N�X�`���̎g�p���@
		D3DFMT_UNKNOWN,				// �e�N�X�`���t�H�[�}�b�g
		D3DPOOL_MANAGED,			// �e�N�X�`���̃������Ǘ����@
		D3DX_FILTER_NONE,			// �C���[�W���t�B���^�����O������@
		D3DX_DEFAULT,				// �~�b�v�}�b�v���x�����t�B���^�����O������@
		colorKey,					// ���߂���F�A�i0:�J���[�L�[�𖳌��Ƃ���j
		0,							// �t�@�C�����f�[�^�̎擾 (0:�K�v�Ȃ�)
		0,							// �p���b�g��� (0:�K�v�Ȃ�)
		pTexture)))					// �e�N�X�`���p�|�C���^�ւ̃|�C���^
	{
		MessageBox(NULL, "�e�N�X�`���t�@�C��������܂���\n�I�����܂�", str, MB_OK);
		PostQuitMessage(0);
	}	
}

//---------------------------------------------------------------------
//	���e�N�X�`�����������
//		void D3ReleaseTexture(gsTexture texture);
//		
//		���� [in]	texture	: �������e�N�X�`��
//		�߂�l		�Ȃ�
//---------------------------------------------------------------------
void	gsReleaseTexture(gsTexture texture)
{
	GS_SAFE_RELEASE( texture );
}


//---------------------------------------------------------------------
//	���W���I�ȐF�̍����̐ݒ�
//		void D3SetNormalColor(void);
//
//		����		�Ȃ�
//		�߂�l		�Ȃ�
//---------------------------------------------------------------------
void	gsSetNormalColor()
{
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,	D3DBLEND_INVSRCALPHA );
}

//---------------------------------------------------------------------
//	���Z�I�ȐF�̍����̐ݒ�i�����}�[�N�Ȃǁj
//---------------------------------------------------------------------
void	gsSetAddColor()
{
	g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND,	D3DBLEND_ONE );
}


//=====================================================================
//	2D����
//=====================================================================

//---------------------------------------------------------------------
//	��2D��ʂ̃N���A
//		void	gsDraw2DClear (gsColor color);
//
//		���� [in]	color	: �N���A����F
//
//		�߂�l		�Ȃ�
//	
//		����j	Z �o�b�t�@���N���A����邱�Ƃɒ��ӂ��ꂽ��
//---------------------------------------------------------------------
void	gsDraw2DClear(gsColor color)
{

    // �o�b�N�o�b�t�@�Ƃy�o�b�t�@��ŃN���A
    g_pd3dDevice->Clear(	0, NULL, 
							D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
							color, 1.0f, 0 );
}

//---------------------------------------------------------------------
//	��2D�摜�̕`��
//		void gsDraw2D(gsTexture texture, int sx, int sy,
//								gsColor cr= GSARGB(255,255,255,255) );
//
//		���� [in]	texture : �e�N�X�`��
//		���� [in]	sx, sy	: �\���ʒu(�X�N���[�����W)
//					�� �摜�̍���̃s�N�Z���� (x, y)�ɑΉ��Â�����
//		���� [in]	cr		: ���_�J���[
//					�� �f�t�H���g�l GSARGB(255,255,255,255)
//
//		�߂�l		�Ȃ�
//---------------------------------------------------------------------
void	gsDraw2D(gsTexture texture, int sx, int sy, gsColor cr)
{
	// �e�N�X�`���̃T�C�Y�擾�p
	D3DSURFACE_DESC	sd;
	float			xs;
	float			ys;

	// �^�ϊ�
	float fx = (float)sx;
	float fy = (float)sy;

	// �G�̑傫���̎擾
	texture->GetLevelDesc(0, &sd);
	xs = (float)sd.Width;
	ys = (float)sd.Height;

	// ���_�f�[�^�̏���
	gsTLVertex vertices[] =
	{
		//	    ( x,	 y,		z )	    rhw	  ���_�J���[	�e�N�X�`�����W
		{ gsVec3( fx,    fy,    0.0f ), 1.0f, cr,			gsVec2(0.0f, 0.0f) },
		{ gsVec3( fx+xs, fy,    0.0f ), 1.0f, cr,			gsVec2(1.0f, 0.0f) },
		{ gsVec3( fx,    fy+ys, 0.0f ), 1.0f, cr,			gsVec2(0.0f, 1.0f) },
		{ gsVec3( fx+xs, fy+ys, 0.0f ), 1.0f, cr,			gsVec2(1.0f, 1.0f) },
	};

	// ���e�����o��̂Œ��~	2011.5.3
	// �摜��K�m�ɕ`�悷�邽�߂̃X�N���[�����W�̕␳	2009.12.21
	//for (int i=0; i<4; i++)
	//{
	//	vertices[i].pos.x -= 0.5f;
	//	vertices[i].pos.y -= 0.5f;
	//}

	// �`��
	gsSetZBufferOff();	// Z �o�b�t�@�ւ̏������݂͂��Ȃ�
	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̃^�C�v
		2,							// �v���~�e�B�u�̐�
		vertices,					// ���_�f�[�^�ւ̃|�C���^
		sizeof(gsTLVertex) );		// �e���_�f�[�^�ւ̃X�g���C�h(�o�C�g�P��)
	gsSetZBufferOn();	// Z �o�b�t�@�ւ̏������݂�����
}

//---------------------------------------------------------------------------------------
//	�� �G�̕`��
//		void	gsDraw2DPartEx(gsTexture texture, int sx, int sy, int sw, int sh,
//							int tx, int ty, int tw, int th, float angle, gsColor cr );
//
//		���� [in]	texture : �e�N�X�`��
//		���� [in]	sx, sy	: �\���ʒu(�X�N���[�����W)
//		���� [in]	sw, sh	: �e�N�X�`���̏c���̃T�C�Y
//						�� 0�̂Ƃ��͉摜�̃T�C�Y
//		���� [in]	tx, ty	: �؂���e�N�X�`�������̍���̍��W
//		���� [in]	tw, th	: �؂���e�N�X�`���̉����ƍ���
//		���� [in]	color	: ���_�J���[
//		���� [in]	angle	: ��]�p�A���W�A��						
//
//		�߂�l		�Ȃ�
//---------------------------------------------------------------------------------------
void	gsDraw2DPartEx(gsTexture texture, int sx, int sy, int sw, int sh, 
					   int tx, int ty, int tw, int th, float angle, gsColor cr)
{
	float			sw2, sh2;
	D3DSURFACE_DESC	sd;
	float xs, ys;
	float nx1, ny1, nx2, ny2;
	int i;

	// �e�N�X�`���̃T�C�Y�̎擾
	texture->GetLevelDesc(0, &sd);
	xs = (float)sd.Width;
	ys = (float)sd.Height;

	// ���_�f�[�^�̍쐬
	gsTLVertex vertices[4];

	// ��������z�̐ݒ�
	for ( i =0; i < 4; i++ )
	{
		vertices[i].rhw		= 1.0f;
		vertices[i].color	= cr;
		vertices[i].pos.z	= 0.0f;
	}

	// �G�̑傫���̎擾
	if ( sw == 0 )
	{
		sw = tw;
	}
	if ( sh == 0 )
	{
		sh = th;
	}

	// �g��E�k���Ɖ�]����
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

	// ���e�����o��̂Œ��~	2011.5.3
	// �摜��K�m�ɕ`�悷�邽�߂̃X�N���[�����W�̕␳	2009.12.21
	//for (i=0; i<4; i++)
	//{
	//	vertices[i].pos.x -= 0.5f;
	//	vertices[i].pos.y -= 0.5f;
	//}

	// �e�N�X�`�����W�̐ݒ�
	nx1 = (float) tx	   / xs;
	ny1 = (float) ty	   / ys;
	nx2 = (float)(tx + tw) / xs;
	ny2 = (float)(ty + th) / ys;

	vertices[0].uv = gsVec2(nx1, ny1);
	vertices[1].uv = gsVec2(nx2, ny1);
	vertices[2].uv = gsVec2(nx1, ny2);
	vertices[3].uv = gsVec2(nx2, ny2);

	// �`��
	gsSetZBufferOff();	// Z �o�b�t�@�ւ̏������݂͂��Ȃ�	2009.07.23 �ǉ�

	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̃^�C�v
		2,								// �v���~�e�B�u�̐�
		vertices,						// ���_�f�[�^�ւ̃|�C���^
		sizeof(gsTLVertex) );		// �e���_�f�[�^�ւ̃X�g���C�h�i�o�C�g�P�ʁj

	gsSetZBufferOn();	// Z �o�b�t�@�ւ̏������݂�����		2009.07.23 �ǉ�
}

//---------------------------------------------------------------------
//	�� �G�̕`��
//		void gsDraw2D(gsTexture texture, int sx, int sy,
//							int tx, int ty, int tw, int th,
//							gsColor cr= GSARGB(255,255,255,255) );
//
//		���� [in]	texture : �e�N�X�`��
//		���� [in]	sx, sy	: �\���ʒu(�X�N���[�����W)
//						�� �摜�̍���̃s�N�Z���� (x, y)�ɑΉ��Â�����
//		���� [in]	tx, ty	: �؂���e�N�X�`�������̍���̍��W
//		���� [in]	tw, th	: �؂���e�N�X�`���̉����ƍ���
//		���� [in]	cr		: ���_�J���[
//						�� �f�t�H���g�l GSARGB(255,255,255,255)
//
//		�߂�l		�Ȃ�
//---------------------------------------------------------------------
void	gsDraw2DPart(gsTexture texture, int sx, int sy,
					 int tx, int ty, int tw, int th, gsColor cr )
{
	D3DSURFACE_DESC	sd;
	float xs, ys;
	float nx1, ny1, nx2, ny2;
	int i;

	// �e�N�X�`���̃T�C�Y�̎擾
	texture->GetLevelDesc(0, &sd);
	xs = (float)sd.Width;
	ys = (float)sd.Height;

	// ���_�f�[�^�̍쐬
	gsTLVertex vertices[4];

	// ��������z�̐ݒ�
	for ( i =0; i < 4; i++ )
	{
		vertices[i].rhw		= 1.0f;
		vertices[i].color	= cr;
		vertices[i].pos.z	= 0.0f;
	}
	
	// �`��ʒu�̐ݒ�
	vertices[0].pos.x = (float)sx;			vertices[0].pos.y = (float)sy;
	vertices[1].pos.x = (float)sx + tw;		vertices[1].pos.y = (float)sy;
	vertices[2].pos.x = (float)sx;			vertices[2].pos.y = (float)sy + th;
	vertices[3].pos.x = (float)sx + tw;		vertices[3].pos.y = (float)sy + th;

	// ���e�����o��̂Œ��~	2011.5.3
	// �摜��K�m�ɕ`�悷�邽�߂̃X�N���[�����W�̕␳	2009.12.21
	//for (i=0; i<4; i++)
	//{
	//	vertices[i].pos.x -= 0.5f;
	//	vertices[i].pos.y -= 0.5f;
	//}

	// �e�N�X�`�����W�̐ݒ�
	nx1 = (float) tx	   / xs;
	ny1 = (float) ty	   / ys;
	nx2 = (float)(tx + tw) / xs;
	ny2 = (float)(ty + th) / ys;

	vertices[0].uv = gsVec2(nx1, ny1);
	vertices[1].uv = gsVec2(nx2, ny1);
	vertices[2].uv = gsVec2(nx1, ny2);
	vertices[3].uv = gsVec2(nx2, ny2);

	// �`��
	gsSetZBufferOff();	// Z �o�b�t�@�ւ̏������݂͂��Ȃ�	2009.07.23 �ǉ�

	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̃^�C�v
		2,								// �v���~�e�B�u�̐�
		vertices,						// ���_�f�[�^�ւ̃|�C���^
		sizeof(gsTLVertex) );		// �e���_�f�[�^�ւ̃X�g���C�h�i�o�C�g�P�ʁj

	gsSetZBufferOn();	// Z �o�b�t�@�ւ̏������݂�����		2009.07.23 �ǉ�
}


//---------------------------------------------------------------------
//	���e�N�X�`���̕��i�s�N�Z���j���擾����
//		int	 gsGetTextureWidth (gsTexture Texture);
//
//		���� [in]	texture : ���ׂ�e�N�X�`��
//		�߂�l		����Ԃ�
//					�� texture ������(=NULL)�Ȃ�A0��Ԃ�
//---------------------------------------------------------------------
int	 gsGetTextureWidth (gsTexture texture)
{
	D3DSURFACE_DESC	sd;
	int				size;

	if ( texture )
	{
		// �e�N�X�`���̃T�C�Y�̎擾
		texture->GetLevelDesc(0, &sd);
		size = (int)sd.Width;

		return size;
	}

	return 0;
}


//---------------------------------------------------------------------
//	���e�N�X�`���̍����i�s�N�Z���j���擾����
//		int	 gsGetTextureHeight(gsTexture texture);
//
//		���� [in]	texture : ���ׂ�e�N�X�`��
//		�߂�l		������Ԃ�
//					�� texture ������(=NULL)�Ȃ�A0��Ԃ�
//---------------------------------------------------------------------
int	 gsGetTextureHeight(gsTexture texture)
{
	D3DSURFACE_DESC	sd;
	int				size;

	if ( texture )
	{
		// �e�N�X�`���̃T�C�Y�̎擾
		texture->GetLevelDesc(0, &sd);
		size = (int)sd.Height;

		return size;
	}

	return 0;
}

//---------------------------------------------------------------------
//	�� �w�肳�ꂽ 2�_�Ԃ����� ������`�悷��
//		void	gsDraw2DLine( int x1, int y1, int x2, int y2, gsColor color);
//
//		���� [in]	x1, y1	: �����̎n�_���W (�X�N���[�����W)
//		���� [in]	x2, y2	: �����̏I�_���W (�X�N���[�����W)
//		���� [in]	color	: �����̐F
//		�߂�l		�Ȃ�
//---------------------------------------------------------------------
void	gsDraw2DLine( int x1, int y1, int x2, int y2, gsColor color)
{
	//	���_�f�[�^�̍쐬
	gsTLVertex	vertices[2] = {
		//			( x,		y,		z  )	rhw		���_�F	�e�N�X�`�����W
		{ gsVec3((float)x1, (float)y1, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
		{ gsVec3((float)x2, (float)y2, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
	};

	gsSetZBufferOff();	// Z �o�b�t�@�ւ̏������݂͂��Ȃ�
	g_pd3dDevice->SetTexture( 0, NULL );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_LINELIST,			// �v���~�e�B�u�̃^�C�v
		1,						// �v���~�e�B�u�̐�
		vertices,				// ���_�f�[�^�ւ̃|�C���^
		sizeof(gsTLVertex) );	// �e���_�f�[�^�ւ̃X�g���C�h�i�o�C�g�P�ʁj
	gsSetZBufferOn();	// Z �o�b�t�@�ւ̏������݂�����
}

//---------------------------------------------------------------------
//	�� �w�肳�ꂽ 2�_��Ίp���Ƃ��� �����`��`�悷��
//		void	gsDraw2DRectangle(
//					int x1, int y1, int x2, int y2,
//					gsColor color, bool bFillMode = false );
//
//		���� [in]	x1, y1		: �����̎n�_���W (�X�N���[�����W)
//		���� [in]	x2, y2		: �����̏I�_���W (�X�N���[�����W)
//		���� [in]	color		: �����̐F
//		���� [in]	bFillMode	: �h��Ԃ����[�h
//									true:�h��Ԃ� false:�h��Ԃ��Ȃ�
//		�߂�l		�Ȃ�
//---------------------------------------------------------------------
void	gsDraw2DRectangle(int x1, int y1, int x2, int y2, gsColor color, bool bFillMode)
{
	//	���_�f�[�^�̍쐬
	gsTLVertex	vertices[5] = {
		//			( x,		y,		z  )	rhw		���_�F	�e�N�X�`�����W
		{ gsVec3((float)x1, (float)y1, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
		{ gsVec3((float)x2, (float)y1, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
		{ gsVec3((float)x2, (float)y2, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
		{ gsVec3((float)x1, (float)y2, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
		{ gsVec3((float)x1, (float)y1, 0.0f),	1.0f,	color,	gsVec2(0.0f, 0.0f) },
	};

	gsSetZBufferOff();	// Z �o�b�t�@�ւ̏������݂͂��Ȃ�
	g_pd3dDevice->SetTexture( 0, NULL );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );

	if ( bFillMode )
		g_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, vertices, sizeof(gsTLVertex) );
	else
		g_pd3dDevice->DrawPrimitiveUP( D3DPT_LINESTRIP,	  4, vertices, sizeof(gsTLVertex) );

	gsSetZBufferOn();	// Z �o�b�t�@�ւ̏������݂�����
}

//---------------------------------------------------------------------
//	�� �~��`�悷�� (�� n �p�` �̃|���S����)
//		void	gsDraw2DCircle(int cx, int cy, int r,
//								  gsColor color, bool bFillMode = false);
//
//		���� [in]	cx, cy		: �~�̒��S�n�_���W (�X�N���[�����W)
//		���� [in]	r			: �~�̔��a (�s�N�Z��)
//		���� [in]	color		: ���̐F
//		���� [in]	bFillMode	: �h��Ԃ����[�h
//									true:�h��Ԃ� false:�h��Ԃ��Ȃ�
//		�߂�l		�Ȃ�
//---------------------------------------------------------------------
void	gsDraw2DCircle(int cx, int cy, int r,  gsColor color, bool bFillMode)
{
	//	���_�f�[�^�̍쐬
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

	// 360�p�` �̕`��
	gsSetZBufferOff();	// Z �o�b�t�@�ւ̏������݂͂��Ȃ�
	g_pd3dDevice->SetTexture( 0, NULL );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );

	if ( bFillMode )
		g_pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 360, &v[0], sizeof(gsTLVertex) );
	else
		g_pd3dDevice->DrawPrimitiveUP( D3DPT_LINESTRIP,	  360, &v[1], sizeof(gsTLVertex) );

	gsSetZBufferOn();	// Z �o�b�t�@�ւ̏������݂�����
}


//=====================================================================
// �����t�H���g����
//=====================================================================

// �t�H���g�֌W�̃O���[�o���ϐ�
static		LPD3DXFONT		g_pD3DXFont;		// D3DX�t�H���g
static		int				g_nFontSize;		// �t�H���g�T�C�Y
static		char			g_szFontName[32];	// �t�H���g��

//---------------------------------------------------------------------
// �t�H���g�̏�����
//---------------------------------------------------------------------
void gsInitFont(void)
{
	// 16�s�N�Z���̍����C�f�t�H���g�t�H���g�̐ݒ�
	gsSetFont( 16, "�l�r �S�V�b�N" );
}


//---------------------------------------------------------------------
// ���f�t�H���g�t�H���g�̃T�C�Y�ƃt�H���g�̐ݒ�
//		void gsSetFont(int size, char *szFontName = "�l�r �S�V�b�N" );
//
//	���� [in]	size		: �����̃T�C�Y (�s�N�Z���P��)
//	���� [in]	szFontName	: �t�H���g��
//
//	�߂�l		�Ȃ�
//
//	�� �t�H���g�����ȗ������ "�l�r �S�V�b�N" ���C�I�������
//---------------------------------------------------------------------
void gsSetFont(int size, char *szFontName )
{
	// �t�H���g�T�C�Y, �t�H���g�����擾�ł���悤�ɂƂ��Ă����D
	g_nFontSize = size;
	strcpy( g_szFontName, szFontName );

	// �t�H���g�̉��
	GS_SAFE_RELEASE( g_pD3DXFont );

	//	D3DX�t�H���g�쐬
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
//	��2D�摜�̕`��
//		void gsDraw2DEx(gsTexture texture, int sx, int sy,int sw, int sh,
//								gsColor cr= GSARGB(255,255,255,255) );
//
//		���� [in]	texture : �e�N�X�`��
//		���� [in]	sx, sy	: �\���ʒu(�X�N���[�����W)
//					�� �摜�̍���̃s�N�Z���� (x, y)�ɑΉ��Â�����
//		���� [in]	sw, sh	: �e�N�X�`���̏c���̃T�C�Y
//		���� [in]	cr		: ���_�J���[
//					�� �f�t�H���g�l GSARGB(255,255,255,255)
//
//		�߂�l		�Ȃ�
//---------------------------------------------------------------------
void	gsDraw2DEx(gsTexture texture, int sx, int sy, int sw, int sh, gsColor cr)
{
	float			xs;
	float			ys;

	// �^�ϊ�
	float fx = (float)sx;
	float fy = (float)sy;

	// �w�肳�ꂽ�T�C�Y���g�p
	xs = (float)sw;
	ys = (float)sh;

	// ���_�f�[�^�̏���
	gsTLVertex vertices[] =
	{
		//	    ( x,	 y,		z )	    rhw	  ���_�J���[	�e�N�X�`�����W
		{ gsVec3( fx,    fy,    0.0f ), 1.0f, cr,			gsVec2(0.0f, 0.0f) },
		{ gsVec3( fx+xs, fy,    0.0f ), 1.0f, cr,			gsVec2(1.0f, 0.0f) },
		{ gsVec3( fx,    fy+ys, 0.0f ), 1.0f, cr,			gsVec2(0.0f, 1.0f) },
		{ gsVec3( fx+xs, fy+ys, 0.0f ), 1.0f, cr,			gsVec2(1.0f, 1.0f) },
	};

	// ���e�����o��̂Œ��~	2011.5.3
	// �摜��K�m�ɕ`�悷�邽�߂̃X�N���[�����W�̕␳	2009.12.21
//	for (int i=0; i<4; i++)
//	{
//		vertices[i].pos.x -= 0.5f;
//		vertices[i].pos.y -= 0.5f;
//	}

	// �`��
	gsSetZBufferOff();	// Z �o�b�t�@�ւ̏������݂͂��Ȃ�
	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( FVF_TLVERTEX );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,		// �v���~�e�B�u�̃^�C�v
		2,							// �v���~�e�B�u�̐�
		vertices,					// ���_�f�[�^�ւ̃|�C���^
		sizeof(gsTLVertex) );		// �e���_�f�[�^�ւ̃X�g���C�h(�o�C�g�P��)
	gsSetZBufferOn();	// Z �o�b�t�@�ւ̏������݂�����
}



//---------------------------------------------------------------------
// �t�H���g�̉��
//---------------------------------------------------------------------
void gsReleaseFont(void)
{
	GS_SAFE_RELEASE( g_pD3DXFont );
}


//---------------------------------------------------------------------
// �e�L�X�g�i���́j�̕`��
//---------------------------------------------------------------------
void gsDrawText( int x, int y, char *str )
{
	gsDrawPrintf( x, y, GSRGB(255,255,255), str );
}

//---------------------------------------------------------------------
// �����̕`��
//---------------------------------------------------------------------
void gsDrawNum( int x, int y, int a )
{
	gsDrawPrintf( x, y, GSRGB(255,255,255), "%d", a );	
}

//---------------------------------------------------------------------
//	���o�̓t�H�[�}�b�g�w��\�ȕ�����̕`��	// 2009.06.07 �ǉ�
//	�@���\���ʒu�C�����F�̎w�肠��D�ϐ��̒l��\�����邱�Ƃ��ł���D
//
//		��@��)
//			bool gsDrawPrintf(int x, int y, gsColor color, char *szFormat, ...);
//
//		���@��)	x, y		: �\���ʒu
//				color		: ������̐F
//				szFormat	: �o�͏���
//				...			: �ϐ��̕���
//
//		�߂�l)	�������ꂽ������(�I�[�� null �����͊܂܂�܂���)
//				(�G���[��:���̒l)
//---------------------------------------------------------------------
int	gsDrawPrintf(int x, int y, gsColor color, char *szFormat, ...)
{
	char	szText[1024];	// �`�敶����
	RECT	rect;			// ��`	
	int		nLength;		// ������

	// ������̐���
	va_list		va;

	va_start( va, szFormat );
	nLength = vsprintf( szText, szFormat, va);
	va_end( va );

	// ������̕`��
	SetRect( &rect, x, y, GS_WINDOW_WIDTH, GS_WINDOW_HEIGHT );
	g_pD3DXFont->DrawText( NULL, szText, -1, &rect, DT_LEFT, color );

	return nLength;
}


//---------------------------------------------------------------------
//	���o�̓t�H�[�}�b�g�w��\�ȕ�����̕`��	// 2009.07.23 �ǉ�
//	�@���\���ʒu�C�����F�̎w�肠��D�ϐ��̒l��\�����邱�Ƃ��ł���D
//	�@���܂��C�t�H���g�T�C�Y�ɂ��C�K���ȑ傫���̉e��`�悵�Ă���C�ړI�̕������`�悷��D
//
//		��@��)
//			bool gsDrawPrintfShadow(int x, int y, gsColor color, char *szFormat, ...);
//
//		���@��)	x, y		: �\���ʒu
//				color		: ������̐F
//				szFormat	: �o�͏���
//				...			: �ϐ��̕���
//
//		�߂�l)	�������ꂽ������(�I�[�� null �����͊܂܂�܂���)
//				(�G���[��:���̒l)
//---------------------------------------------------------------------
int	gsDrawPrintfShadow(int x, int y, gsColor color, char *szFormat, ...)
{
	char		szText[1024];	// �`�敶����
	RECT		rect;			// ��`	
	int			nLength;		// ������
	gsColor		cShadow;		// �e�̐F

	// �e�̐F�̎Z�o
//	cShadow = ~(color & 0x00ffffff) | 0xff000000;
	cShadow = 0xff000000;

	// ������̐���
	va_list		va;

	va_start( va, szFormat );
	nLength = vsprintf( szText, szFormat, va);
	va_end( va );

	// ������̕`��
	SetRect( &rect, x + g_nFontSize/16, y + g_nFontSize/16, GS_WINDOW_WIDTH, GS_WINDOW_HEIGHT );
	g_pD3DXFont->DrawText( NULL, szText, -1, &rect, DT_LEFT, cShadow );

	SetRect( &rect, x, y, GS_WINDOW_WIDTH, GS_WINDOW_HEIGHT );
	g_pD3DXFont->DrawText( NULL, szText, -1, &rect, DT_LEFT, color	 );

	return nLength;
}


//=====================================================================
//	�R�c����
//=====================================================================

// �R�c�̃J�X�^�����_�f�[�^�̍\����		�� �ύX�K
struct CUSTOMVERTEX3D
{
    FLOAT x, y, z;		// ���_�̍��W
    DWORD color;        // ���_�̐F
    FLOAT tu, tv;   	// �e�N�X�`�����W
};

// �R�c�̂e�u�e��`
#define D3DFVF_CUSTOMVERTEX3D (D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//---------------------------------------------------------------------
// �J�����ʒu�̐ݒ�
// �n�ʂƐ����ɗ��A�ڐ��͂x���ŉ�]����
//---------------------------------------------------------------------
void gsSetCamera(float x, float y, float z,float dir)
{

	// �J�����̍��W�ݒ�
	D3DXVECTOR3 vEyePt( x, y, z );

	// �J�����̌����̐ݒ�
	D3DXVECTOR3 vLookatPt( x+cos(dir), y, z+sin(dir) );

	// �J�����̓��̐ݒ�i��ɓ��͏�����j
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );

	// �J�����̍s��ϊ���ݒ肷��
	D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

	// ����p�A�O��̃N���b�s���O���w�肷��
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 200.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}

//---------------------------------------------------------------------
// �J�����O���[�h���I�t�ɐݒ�
// �J�����O���[�h�i�|���S���̗��ʂ�\�����Ȃ����[�h�j���I�t�ɂ���B
// ����ɂ�藠�ʂ��\�������B
//---------------------------------------------------------------------
void gsSetCullOff()
{
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
}

//---------------------------------------------------------------------
// �J�����O���[�h�������̃I���ɐݒ�
// ����ɂ��E���̕\�ʂ̂ݕ\�������B
//---------------------------------------------------------------------
void gsSetCullOn()
{
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
}

//---------------------------------------------------------------------
// ���C�g���I���ɐݒ�
// �@���̂��郂�f���Ɍ��𓖂Ăĕ\������
//---------------------------------------------------------------------
void gsSetLightOn()
{
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}

//---------------------------------------------------------------------
// ���C�g���I�t�ɐݒ�
// �@���̂Ȃ��|���S�����e�N�X�`���̐F�ŕ\������
//---------------------------------------------------------------------
void gsSetLightOff()
{
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
}

//---------------------------------------------------------------------
// ���C�g�̐ݒ�
// x y z ���̕����@�i�����̈ʒu�ł͂Ȃ��A���̐i�ޕ������w��j
// color rgb�Ō��̐F�Ƌ������w��
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

    // �w�肵���ݒ肵���A���r�G���g�J���[���Z�b�g����
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, color );
}


//---------------------------------------------------------------------
// z�o�b�t�@���I���ɂ���
// �ʏ�̕\���́A���̃��[�h
//---------------------------------------------------------------------
void gsSetZBufferOn()
{
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
}

//---------------------------------------------------------------------
// z�o�b�t�@���I�t�ɂ���
// �ʏ�̕\���́A���̃��[�h
//---------------------------------------------------------------------
void gsSetZBufferOff()
{
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
}


//---------------------------------------------------------------------
// �s��ϊ��̐ݒ�
// �w�x�y�̈ʒu�Ƃx���ŉ�]���w��
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
// �s��ϊ��̐ݒ�
// �w�x�y�̈ʒu�Ƃx���ŉ�]���w��
// �g��ϊ����s��
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
//�@�S�p�|���S���̕\���A�n�ʗp
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

	// �`��
	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX3D );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̃^�C�v
		2,								// �v���~�e�B�u�̐�
		vertices,						// ���_�f�[�^�ւ̃|�C���^
		sizeof(CUSTOMVERTEX3D) );		// �e���_�f�[�^�ւ̃X�g���C�h�i�o�C�g�P�ʁj

}

//---------------------------------------------------------------------
//�@�S�p�|���S���̕\���A�����Ă��镨��
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

	// �`��
	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX3D );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̃^�C�v
		2,								// �v���~�e�B�u�̐�
		vertices,						// ���_�f�[�^�ւ̃|�C���^
		sizeof(CUSTOMVERTEX3D) );		// �e���_�f�[�^�ւ̃X�g���C�h�i�o�C�g�P�ʁj
}

//---------------------------------------------------------------------
//�@����ȂS�p�|���S���̕\���A�G�t�F�N�g�\��
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

	// �`��
	g_pd3dDevice->SetTexture( 0, texture );
    g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX3D );
	g_pd3dDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̃^�C�v
		2,								// �v���~�e�B�u�̐�
		vertices,						// ���_�f�[�^�ւ̃|�C���^
		sizeof(CUSTOMVERTEX3D) );		// �e���_�f�[�^�ւ̃X�g���C�h�i�o�C�g�P�ʁj
}



//=============================================================================
//	X ���f���֘A
//=============================================================================

//=====================================================================
//	gsCAllocateHierarchy �N���X
//	---------------------------
//	X File �̊K�w�\������́C���̏��𐶐����邽�߂ɗ��p�����N���X�D
//	���p�҂́CID3DXAllocateHierarchy �N���X��h���������N���X��
//	�쐬����K�v������D
//=====================================================================
class gsCAllocateHierarchy : public ID3DXAllocateHierarchy
{
public:
	///////////////////////////////////////////////////////////////////
	// ���\�b�h

	// �t���[���̐������ɌĂ΂�郁�\�b�h
	STDMETHOD(CreateFrame)(THIS_
		LPCSTR						Name, 
		LPD3DXFRAME*				ppNewFrame);

	// ���b�V���R���e�i�̐������ɌĂ΂�郁�\�b�h
    STDMETHOD(CreateMeshContainer)(THIS_ 
        LPCSTR						Name, 
        CONST D3DXMESHDATA*			pMeshData, 
        CONST D3DXMATERIAL*			pMaterials, 
        CONST D3DXEFFECTINSTANCE*	pEffectInstances, 
        DWORD						NumMaterials, 
        CONST DWORD*				pAdjacency, 
        LPD3DXSKININFO				pSkinInfo, 
        LPD3DXMESHCONTAINER*		ppNewMeshContainer);

	// �t���[���̍폜���ɌĂ΂�郁�\�b�h
	STDMETHOD(DestroyFrame)(THIS_
		LPD3DXFRAME					pFrameToFree); 

	// ���b�V���R���e�i�̍폜���ɌĂ΂�郁�\�b�h
	STDMETHOD(DestroyMeshContainer)(THIS_ 
		LPD3DXMESHCONTAINER			pMeshContainerToFree); 


	//////////////////////////////////////////////////////////////////////
	// �R���X�g���N�^
	gsCAllocateHierarchy(){}
};

// �K�w�\���t���̃��b�V���𑀍삷��ۂɗ��p����I�u�W�F�N�g
gsCAllocateHierarchy	AllocHierarchy;


//=====================================================================
//	gsCAllocateHierarchy::CreateFrame
//	---------------------------------
//	�t���[���������ɌĂ΂�郁�\�b�h
//		[in]	Name		: �t���[����
//		[out]	ppNewFrame	: �������ꂽ�t���[���I�u�W�F�N�g
//=====================================================================
HRESULT gsCAllocateHierarchy::CreateFrame(
	LPCTSTR		Name,
	LPD3DXFRAME	*ppNewFrame)
{
	gsFrame	*pTmpFrame = NULL;	
	HRESULT	rc;			// ���^�[���R�[�h

	*ppNewFrame = NULL;

	// �t���[���I�u�W�F�N�g�̐���
	pTmpFrame = new gsFrame;
	if ( pTmpFrame == NULL ) 
	{
		rc = E_OUTOFMEMORY;
		goto e_Exit;
	}

	// �t���[�����̕ۑ�
	pTmpFrame->Name = new TCHAR[lstrlen(Name) + 1];
	if ( pTmpFrame->Name == NULL)
	{
		rc = E_OUTOFMEMORY;
		goto e_Exit;
	}
	lstrcpy(pTmpFrame->Name, Name);
	gsDebugPrintf("CreateFrame:Name[%s]\n", Name);	// Debug


	// �t���[���I�u�W�F�N�g�̏����l�̐ݒ�
	D3DXMatrixIdentity(&pTmpFrame->TransformationMatrix);
	D3DXMatrixIdentity(&pTmpFrame->CombinedTransformMatrix);
	
	pTmpFrame->pMeshContainer	= NULL;	// ���b�V���R���e�i
	pTmpFrame->pFrameSibling	= NULL;	// �Z��t���[��
	pTmpFrame->pFrameFirstChild	= NULL;	// �q�t���[��
	
	// �t���[���I�u�W�F�N�g�̃|�C���^�̊i�[
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
//	���b�V���R���e�i�������ɌĂ΂�郁�\�b�h
//		[in]	Name				: ���b�V���R���e�i�� 
//		[in]	pMeshData			: ���b�V���f�[�^
//		[in]	pMaterials			: �}�e���A�����
//		[in]	pEffectInstances	: �G�t�F�N�g�C���X�^���X(?)
//		[in]	NumMaterials		: �}�e���A����
//		[in]	pAdjacency			: �אڐ����
//		[in]	pSkinInfo			: �X�L�����
//		[out]	ppNewMeshContainer	: �������ꂽ���b�V���R���e�i
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
	
	gsMeshContainer*	pTmpMeshContainer = NULL;	// ���b�V���R���e�i
	LPD3DXMESH			pMesh	= NULL;

	UINT	nFaces;		// �t�F�C�X��
	UINT	nBones;		// �{�[����

	UINT	iMaterial;
    UINT	iBone;

	HRESULT	rc;			// ���^�[���R�[�h

    LPDIRECT3DDEVICE9 pDevice = NULL;


	// �����ݒ�
	*ppNewMeshContainer = NULL;

	// �ʏ탁�b�V���̂݃T�|�[�g
	//(�v���O���b�V�u���b�V���C�p�b�`���b�V���͖��Ή�)
	if ( pMeshData->Type != D3DXMESHTYPE_MESH)
	{
		rc = E_FAIL;
		goto e_Exit;
	}

	// �R�[�h�̉ǐ������߂邽��
	pMesh = pMeshData->pMesh;


 
	// �V�K�Ƀ��b�V���R���e�i�𐶐�����
	pTmpMeshContainer = new gsMeshContainer;
	if ( pTmpMeshContainer == NULL )
	{
		rc =  E_OUTOFMEMORY;
		goto e_Exit;
	}
	ZeroMemory(pTmpMeshContainer, sizeof(gsMeshContainer));

	// ���b�V���R���e�i���̕ۑ�
	gsDebugPrintf("CreateMeshContainer:Name[%s]\n", Name);	// Debug
	pTmpMeshContainer->Name = new TCHAR[lstrlen(Name) + 1];
	if ( !pTmpMeshContainer->Name )
	{
		rc =  E_OUTOFMEMORY;
		goto e_Exit;
	}
	lstrcpy(pTmpMeshContainer->Name, Name);


	pMesh->GetDevice(&pDevice);


	// ���b�V���f�[�^�̐ݒ�
	// �����b�V���f�[�^�ɖ@����񂪑��݂��Ȃ��ꍇ�ɂ́C�����������ւ���D

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
	// �}�e���A�����C�אڐ����C�e�N�X�`�����̐ݒ�

	nFaces = pMesh->GetNumFaces();	// �t�F�C�X���̎擾

	// �K�v�ȃ������̊m��
	pTmpMeshContainer->NumMaterials	= max(1, NumMaterials);
	pTmpMeshContainer->pMaterials	= new D3DXMATERIAL[pTmpMeshContainer->NumMaterials];
	pTmpMeshContainer->ppTextures	= new gsTexture[pTmpMeshContainer->NumMaterials];
	pTmpMeshContainer->pAdjacency	= new DWORD[nFaces*3];
	
	// �������G���[�̃`�F�b�N
	if ( (pTmpMeshContainer->pMaterials == NULL) ||
		 (pTmpMeshContainer->ppTextures == NULL) ||
		 (pTmpMeshContainer->pAdjacency == NULL)	)
	{
		rc = E_OUTOFMEMORY;
		goto e_Exit;
	}

	// �אڐ����̐ݒ�
	memcpy(pTmpMeshContainer->pAdjacency, pAdjacency, sizeof(DWORD) * nFaces*3);

	// �e�N�X�`�����̏�����
	ZeroMemory(pTmpMeshContainer->ppTextures, sizeof(gsTexture) * pTmpMeshContainer->NumMaterials);

	// X File ���Ƀ}�e���A����񂪑��݂���ꍇ
	if ( NumMaterials > 0 )
	{
		// �}�e���A�����̐ݒ�
		memcpy(pTmpMeshContainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL) * NumMaterials);

		// �e�N�X�`�����̐ݒ�i�e�N�X�`���t�@�C���̓ǂݍ��݂Ɛݒ�j
		for ( iMaterial = 0;  iMaterial < NumMaterials;  iMaterial++ )
		{
			// �e�N�X�`���̃t�@�C���������݂��C���C�t�@�C��������łȂ��Ȃ�
			if ( pTmpMeshContainer->pMaterials[iMaterial].pTextureFilename != NULL &&
				 lstrlen(pTmpMeshContainer->pMaterials[iMaterial].pTextureFilename) > 0 )
			{
				// �t�@�C�����̎�荞��
				TCHAR strTexturePath[MAX_PATH];
				lstrcpy(strTexturePath, pTmpMeshContainer->pMaterials[iMaterial].pTextureFilename);

				// �e�N�X�`���̓ǂݍ��݂Ɛݒ�
				// ���G���[���ł������͒��f���Ȃ��悤�ɂ��Ă���
				if ( FAILED(D3DXCreateTextureFromFile(
					pDevice,
//					g_pd3dDevice,
					strTexturePath,
					&pTmpMeshContainer->ppTextures[iMaterial])))
				{
					gsDebugPrintf("��CreateMeshContainer : �e�N�X�`��[%s]�̓ǂݍ��݃G���[\n", strTexturePath );
					pTmpMeshContainer->ppTextures[iMaterial] = NULL;
				}
				pTmpMeshContainer->pMaterials[iMaterial].pTextureFilename = NULL;
			}
		}
	}
	else	// �}�e���A����񂪑��݂��Ȃ��ꍇ �� �f�t�H���g�l����������
	{
		pTmpMeshContainer->pMaterials[0].pTextureFilename = NULL;
		ZeroMemory(&pTmpMeshContainer->pMaterials[0].MatD3D, sizeof(D3DMATERIAL9));

																//	  r     g     b     a
		pTmpMeshContainer->pMaterials[0].MatD3D.Diffuse  = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pTmpMeshContainer->pMaterials[0].MatD3D.Specular = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	}

	// �X�L����񂪑��݂���ꍇ
	if ( pSkinInfo != NULL )
	{
		// �X�L�����̐ݒ�
		pTmpMeshContainer->pSkinInfo = pSkinInfo;
		pSkinInfo->AddRef();

		pTmpMeshContainer->pOrigMesh = pMesh;
        pMesh->AddRef();

		// �{�[���ϊ��s��p�̈�̊m��
		nBones = pSkinInfo->GetNumBones();
		pTmpMeshContainer->pBoneOffsetMatrices = new D3DXMATRIX[nBones];
		if ( pTmpMeshContainer->pBoneOffsetMatrices == NULL )
		{
			rc = E_OUTOFMEMORY;
			goto e_Exit;
		}

		// �X�L����񂩂�C�{�[���̃I�t�Z�b�g�s������o���Ă����D
		// (��ŁC���x���ǂݍ��ޕK�v���Ȃ��悤�ɂ��邽��)
		for ( iBone = 0; iBone < nBones; iBone++ )
		{
			pTmpMeshContainer->pBoneOffsetMatrices[iBone] =
				*(pTmpMeshContainer->pSkinInfo->GetBoneOffsetMatrix(iBone));
		}

		GS_SAFE_RELEASE( pTmpMeshContainer->MeshData.pMesh );
		GS_SAFE_RELEASE( pTmpMeshContainer->pBoneBuffer    );

		// ���_�u�����h�ɗ��p���邽�߂� ���b�V���f�[�^�ɕϊ�����
		rc = pTmpMeshContainer->pSkinInfo->ConvertToBlendedMesh(
				pTmpMeshContainer->pOrigMesh,			// ���b�V��
				NULL,									 
				pTmpMeshContainer->pAdjacency,			// �אڐ����
				NULL, NULL, NULL, 
				&pTmpMeshContainer->NumInfl,			// �e�����󂯂�{�[���̍ő吔
				&pTmpMeshContainer->NumBones,			// �{�[����
				&pTmpMeshContainer->pBoneBuffer,		// �{�[���f�[�^��Ɨp
				&pTmpMeshContainer->MeshData.pMesh	);	// �V�������b�V��

		if (FAILED(rc))
			goto e_Exit;
    }

	// ���������������D��Ɨp�̃��b�V���R���e�i�̃|�C���^��ݒ肷��D
	*ppNewMeshContainer = pTmpMeshContainer;
	pTmpMeshContainer = NULL;

	rc = S_OK;

e_Exit:
    GS_SAFE_RELEASE(pDevice);

	// �������C�G���[�����������Ƃ��C��Ɨp�ɍ쐬�������b�V���R���e�i���������D
	if( pTmpMeshContainer != NULL )
	{
		DestroyMeshContainer(pTmpMeshContainer);
	}

	return	rc;
}


//=====================================================================
//	gsCAllocateHierarchy::DestroyFrame
//	----------------------------------
//	�t���[���폜���ɌĂ΂�郁�\�b�h
//	D3DXFrameDestroy �֐��́C�ċA�I�ɌZ��t���[���C�q�t���[�����폜����D
//	�e�X�̃t���[�����폜����Ƃ��ɁC���̊֐����Ă΂��D
//		[in]	pFrameToFree	: �������t���[�� 
//=====================================================================
HRESULT gsCAllocateHierarchy::DestroyFrame(
	LPD3DXFRAME pFrameToFree )
{
	gsDebugPrintf( "�� DestroyFrame [%s]\n", pFrameToFree->Name );
	GS_SAFE_DELETE_ARRAY(pFrameToFree->Name);	// �t���[�����̉��
	GS_SAFE_DELETE(pFrameToFree);				// �t���[���̉��

	return	S_OK;
}


//=====================================================================
//	gsCAllocateHierarchy::DestroyMeshContainer
//	------------------------------------------
//	���b�V���R���e�i�폜���ɌĂ΂�郁�\�b�h
//		[in]	pMeshContainerBase	: ������郁�b�V���R���e�i
//=====================================================================
HRESULT gsCAllocateHierarchy::DestroyMeshContainer(
	LPD3DXMESHCONTAINER pMeshContainerBase )
{
	gsMeshContainer *pMeshContainer = (gsMeshContainer*)pMeshContainerBase;
	UINT	iMaterial;

	GS_SAFE_DELETE_ARRAY( pMeshContainer->Name );					// ���b�V���R���e�i���̉��
	GS_SAFE_DELETE_ARRAY( pMeshContainer->pAdjacency );			// �אڐ����̉��

	for ( UINT i=0; i<pMeshContainer->NumMaterials; i++)		// �}�e���A�����̉��
		GS_SAFE_DELETE_ARRAY( pMeshContainer->pMaterials->pTextureFilename );
	GS_SAFE_DELETE_ARRAY( pMeshContainer->pMaterials );			

	GS_SAFE_DELETE_ARRAY( pMeshContainer->pBoneOffsetMatrices );	// �{�[���I�t�Z�b�g�s��̉��
	
	// �e�N�X�`���̉��
	if( pMeshContainer->ppTextures != NULL )
	{
		for(iMaterial = 0;  iMaterial < pMeshContainer->NumMaterials;  iMaterial++)
		{
			GS_SAFE_RELEASE( pMeshContainer->ppTextures[iMaterial] );
		}
	}
	GS_SAFE_DELETE_ARRAY( pMeshContainer->ppTextures );			// �e�N�X�`���z��̉��

	// �{�[�����܂ރ��b�V�����̉��
    GS_SAFE_DELETE_ARRAY( pMeshContainer->ppBoneMatrixPtrs );		// �{�[���ϊ��s��Q�̉�� 
    GS_SAFE_RELEASE( pMeshContainer->pBoneBuffer );				// �{�[�������s��o�b�t�@�̉��
    GS_SAFE_RELEASE( pMeshContainer->pOrigMesh );					// �I���W�i�����b�V���f�[�^�̉��
	GS_SAFE_RELEASE( pMeshContainer->MeshData.pMesh );				// ���b�V���f�[�^�̉��
    GS_SAFE_RELEASE( pMeshContainer->pSkinInfo );					// �X�L�����̉��

	// ���b�V���R���e�i�̉��
	GS_SAFE_DELETE( pMeshContainer );							

	return	S_OK;
}

//---------------------------------------------------------------------
//	X ���f���ǂݍ���	��A�j���[�V������
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
		gsDebugPrintf("�� D3LoadXA : X File �����݂��Ȃ�[%s]\n", pXFileName);

		MessageBox(NULL, "�w�t�@�C��������܂���\n�I�����܂�", pXFileName, MB_OK);

		PostQuitMessage(0);

		return E_FAIL;
	}
	

	D3DXMATERIAL* d3dxMaterials =
				 (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

    m->pMeshMaterials = new D3DMATERIAL9[m->dwNumMaterials];

    m->pMeshTextures  = new gsTexture[m->dwNumMaterials];
    for( DWORD i=0; i<m->dwNumMaterials; i++ )
    {
        // �}�e���A���̃R�s�[
        m->pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        m->pMeshMaterials[i].Ambient = m->pMeshMaterials[i].Diffuse;
        m->pMeshTextures[i] = NULL;

        if( d3dxMaterials[i].pTextureFilename != NULL && 
            lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
        {
			// �e�N�X�`���̓ǂݍ��݂Ɛݒ�
			// ���G���[���ł������͒��f���Ȃ��悤�ɂ��Ă���
			if( FAILED( D3DXCreateTextureFromFile( 
						g_pd3dDevice, d3dxMaterials[i].pTextureFilename, &m->pMeshTextures[i] ) ) )
			{
				gsDebugPrintf("��D3LoadX : �e�N�X�`��[%s]�̓ǂݍ��݃G���[\n",
													d3dxMaterials[i].pTextureFilename );
			}
        }
    }

	// �K�؂ȏ��ԂɃ��b�V���f�[�^���\�[�g���āC�����ɕ`�悳���悤�ɂ���
	m->pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT,NULL,NULL,NULL,NULL);

	// �}�e���A���o�b�t�@�̉��
	GS_SAFE_RELEASE( pD3DXMtrlBuffer );

	return S_OK;
}



//=====================================================================
//	D3LoadXA
//	--------
//	�K�w�\�������������b�V���̓ǂݍ���
//	�A�j���[�V�������̓ǂݍ��݂ɂ��Ή����Ă���
//		[out]	pMesh		: ��������郁�b�V��
//		[in]	pXFileName	: X �t�@�C����
//=====================================================================
HRESULT	gsLoadXA( gsMesh* pMesh, char* pXFileName )
{
	// �K�w�\���t���̃��b�V���𑀍삷��ۂɗ��p����I�u�W�F�N�g
//	gsCAllocateHierarchy	AllocHierarchy;

//	LPD3DXFRAME	pFrameRoot;
	HRESULT	rc;

	// �K�w�\���������� X File �̓ǂݍ���
	rc = D3DXLoadMeshHierarchyFromX( 
			pXFileName,					// X �t�@�C����
			D3DXMESH_MANAGED,			// ���b�V���̍쐬�I�v�V����
										//	D3DXMESH_VB_MANAGED | D3DXMESH_IB_MANAGED 
			g_pd3dDevice,				// Direct3D Device
			&AllocHierarchy,			// �K�w�\���𐶐�����C���^�[�t�F�C�X
			NULL,						// ���[�U�[�ŗL�f�[�^�͗��p���Ȃ�(NULL)

			&pMesh->pFrameRoot,			// ���[�h�����t���[���K�w�ւ̃|�C���^
			&pMesh->pAnimController );	// �A�j���[�V�����R���g���[���ւ̃|�C���^

	if( FAILED( rc ) )
	{
		gsDebugPrintf("�� D3LoadXA : X File �����݂��Ȃ�[%s]\n", pXFileName);
		MessageBox(NULL, "�w�t�@�C��������܂���\n�I�����܂�", pXFileName, MB_OK);

		PostQuitMessage(0);

		return	E_FAIL;
	}

	// �{�[���ϊ��s��̐����Ɛݒ�
	_gsInitBoneMatrics(pMesh->pFrameRoot, pMesh->pFrameRoot);

	return	S_OK;
}


//=====================================================================
//	_gsInitBoneMatrics
//	------------------
//	�{�[���ϊ��s����C�ċA�I�ɐ������C�ݒ肷��
//		[in]	pFrame	: �{�[���ϊ��s���ݒ肷��t���[��
//=====================================================================
static	HRESULT	_gsInitBoneMatrics(LPD3DXFRAME pFrameRoot, LPD3DXFRAME pFrame)
{
    HRESULT hr;

	// �t���[���̃|�C���^���L���Ȃ�C�{�[���ϊ��s��𐶐��C�ݒ肷��
    if (pFrame->pMeshContainer != NULL)
    {
        hr = _gsInitBoneMatricsOnMesh(pFrameRoot, pFrame->pMeshContainer);
        if (FAILED(hr))
            return hr;
    }

	// �Z��t���[��������Ȃ�C�Z��t���[�����̃t���[������������
    if (pFrame->pFrameSibling != NULL)
    {
        hr = _gsInitBoneMatrics(pFrameRoot, pFrame->pFrameSibling);
        if (FAILED(hr))
            return hr;
    }

	// �q�t���[��������Ȃ�C�q�t���[�����̃t���[������������
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
//	�{�[���ϊ��s��𐶐����C���b�V���R���e�i�ɐݒ肷��
//		[in]	pFrameRoot			: ���̃t���[�����N�_�Ƃ���
//									  �Ώۃt���[����{��
//		[in]	pMeshContinerBase	: �K�p���郁�b�V���R���e�i
//=====================================================================
static	HRESULT	_gsInitBoneMatricsOnMesh(
			LPD3DXFRAME pFrameRoot, LPD3DXMESHCONTAINER pMeshContainerBase)
{
	gsFrame *pFrame;
	UINT	nBones;		// �{�[����
	UINT	iBone;

	// �h�����������b�V���R���e�i�ɁC���N���X�̃{�[���ϊ��s���ݒ肷��
	gsMeshContainer *pMeshContainer = (gsMeshContainer*)pMeshContainerBase;

	// �X�L�����b�V���ł���΁C�{�[���ϊ��s���ݒ肷��
	if ( pMeshContainer->pSkinInfo )
	{
		nBones = pMeshContainer->pSkinInfo->GetNumBones();

		pMeshContainer->ppBoneMatrixPtrs = new D3DXMATRIX*[nBones];
		if (pMeshContainer->ppBoneMatrixPtrs == NULL)
			return E_OUTOFMEMORY;

		for (iBone = 0;  iBone < nBones;  iBone++)
		{
			gsDebugPrintf( "��_gsInitBoneMatricsOnMesh : �{�[����[%s]\n", pMeshContainer->pSkinInfo->GetBoneName(iBone) );

			pFrame = (gsFrame*)D3DXFrameFind( pFrameRoot, pMeshContainer->pSkinInfo->GetBoneName(iBone) );

			if (pFrame == NULL)
				return E_FAIL;

			pMeshContainer->ppBoneMatrixPtrs[iBone] = &pFrame->CombinedTransformMatrix;
		}
	}

	return S_OK;
}


//---------------------------------------------------------------------
//	X ���f�����	���K�w�\���̂Ȃ����b�V���p
//---------------------------------------------------------------------
HRESULT	gsReleaseX( gsMesh* pReleaseMesh )
{
	// �}�e���A�����̉��
	GS_SAFE_DELETE_ARRAY( pReleaseMesh->pMeshMaterials );		// �}�e���A�����̉��

	// �e�N�X�`���̉��
    if( pReleaseMesh->pMeshTextures )
    {
        for( UINT i = 0;  i < pReleaseMesh->dwNumMaterials;  i++ )
        {
            GS_SAFE_RELEASE( pReleaseMesh->pMeshTextures[i] );	// �e�N�X�`���C���^�[�t�F�C�X�̉��
        }
        GS_SAFE_DELETE_ARRAY( pReleaseMesh->pMeshTextures );	// �e�N�X�`���z��̉��
    }

	// ���b�V���̉��
	GS_SAFE_RELEASE( pReleaseMesh->pMesh );

	return	S_OK;
}


//---------------------------------------------------------------------
//	X ���f�����	���K�w�\���̂��郁�b�V���p�i�A�j���[�V�������܂ށj
//---------------------------------------------------------------------
HRESULT	D3ReleaseXA( gsMesh* pReleaseMesh )
{
	if( pReleaseMesh->pFrameRoot != NULL )
	{
//		gsCAllocateHierarchy AllocHierarchy;	// �K�w�\���t���b�V������

		D3DXFrameDestroy( pReleaseMesh->pFrameRoot, &AllocHierarchy );

		pReleaseMesh->pFrameRoot = NULL;
	}

	GS_SAFE_RELEASE(pReleaseMesh->pAnimController);
	

	return	S_OK;
}


//---------------------------------------------------------------------
// x���f���`��		���K�w�\���̂Ȃ����b�V���p
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
// x���f���`��		���K�w�\���̂��郁�b�V���p
//---------------------------------------------------------------------
void gsDrawXA( gsMesh *m, float x, float y, float z, float t, double animePastTime )
{
	LPD3DXANIMATIONSET	pAnimSet;
	m->pAnimController->GetAnimationSet(0, &pAnimSet);

	gsSetMatrices( x, y, z, t );

	D3DXMATRIXA16 matWorld;
	g_pd3dDevice->GetTransform( D3DTS_WORLD, &matWorld );

	m->pAnimController->AdvanceTime( animePastTime, NULL );

	// �{�[���̍����s����X�V����
	_gsUpdateBoneMatrices( m->pFrameRoot, &matWorld );

	// �t���[���S�̂�`�悷��
	_gsDrawFrame( m->pFrameRoot );						
}


//=====================================================================
//	_gsUpdateBoneMatrices
//	---------------------
//	�{�[���̍����s����Z�o�C�ݒ肷��
//		[in]	pFrameBase		: ���ڂ��Ă���t���[��
//		[in]	pParentMatrix	: �e�̕ϊ��s��
//=====================================================================
static	void	_gsUpdateBoneMatrices(LPD3DXFRAME pFrameBase, LPD3DXMATRIX pParentMatrix)
{
	// �{�[���̍����s��𗘗p���邽�߁C�h���N���X�̃|�C���^�Ƃ��ė��p���� 
	gsFrame *pFrame = (gsFrame*)pFrameBase;

	///////////////////////////////////////////////////////////////////
	// �{�[���̍����s��𐶐�����
	
	// �e�̕ϊ��s����g���āC���݂̃t���[���̍����s����Z�o����
	if(pParentMatrix != NULL)
	{
		pFrame->CombinedTransformMatrix = pFrame->TransformationMatrix * *pParentMatrix;
	}
	// �e���Ȃ���΁CX File ���� ���̍s��������s��Ƃ���
	else
	{
		pFrame->CombinedTransformMatrix = pFrame->TransformationMatrix;
	}

	// �Z��t���[��������Ȃ�C�e�̕ϊ��s��������Ƃ��ēn��
	// �Z��t���[���̃{�[���ϊ��s����Z�o������
	if(pFrame->pFrameSibling != NULL)
	{
		_gsUpdateBoneMatrices(pFrame->pFrameSibling, pParentMatrix);
	}

	// �q�t���[��������Ȃ�C���݂̃t���[���̍����s��������Ƃ��ēn��
	// �q�t���[���̃{�[���ϊ��s����Z�o������
	if(pFrame->pFrameFirstChild != NULL)
	{
		_gsUpdateBoneMatrices(pFrame->pFrameFirstChild, &pFrame->CombinedTransformMatrix);
	}
}


//=====================================================================
//	_gsDrawFrame
//	------------
//	�t���[���̏������ɁC�`�悷��
//		[in]	pFrame	: ���ڂ��Ă���t���[��
//=====================================================================
static	void	_gsDrawFrame( LPD3DXFRAME pFrame )
{
	// ���b�V���R���e�i
	LPD3DXMESHCONTAINER pMeshContainer;

	// �t���[���ɑΉ��Â����Ă��郁�b�V���R���e�i�����o��
	pMeshContainer = pFrame->pMeshContainer;

	// ���b�V���R���e�i�� ���X�g�\���ƂȂ��Ă���̂�
	// ���������ǂ�Ȃ���C�`�悵�Ă���
	while ( pMeshContainer != NULL )
	{
		// ���b�V���R���e�i�����ɕ`�悷��
		_gsDrawMeshContainer( pMeshContainer, pFrame );

		// ���̃��b�V���R���e�i�Ɉڂ�
		pMeshContainer = pMeshContainer->pNextMeshContainer;
	}

	// �Z��t���[�������݂���Ȃ�C�����`�悷��
	if ( pFrame->pFrameSibling != NULL )
	{
		_gsDrawFrame( pFrame->pFrameSibling );
	}

	// �q�t���[�������݂���Ȃ�C�����`�悷��
	if ( pFrame->pFrameFirstChild != NULL )
	{
		_gsDrawFrame( pFrame->pFrameFirstChild );
	}
}


//=====================================================================
//	_gsDrawMeshContainer
//	--------------------
//	���b�V���R���e�i�̓��e�����ɕ`�悷��
//		[in]	pMeshContainerBase	: �`�悷�郁�b�V���R���e�i
//		[in]	pFrameBase			: �����s������o���t���[��
//=====================================================================
static	void	_gsDrawMeshContainer(
		LPD3DXMESHCONTAINER	pMeshContainerBase,
		LPD3DXFRAME			pFrameBase )
{
	// �`��Ώۂ̃��b�V���R���e�i�ƃt���[��
	gsMeshContainer*	pMeshContainer	= (gsMeshContainer*)pMeshContainerBase;
	gsFrame*			pFrame			= (gsFrame*)pFrameBase;

	// �{�[���̍����ɗ��p����
    LPD3DXBONECOMBINATION	pBoneComb;
	UINT					AttribIdPrev;
	D3DXMATRIXA16			matTmp;
	D3DXMATRIXA16			matOffset;
	D3DXMATRIXA16			matBoneInfl;

	// �X�L����񂪂���Ȃ�C�{�[���̏d�݂𔽉f�����邽��
	// �e���_�ɓK�p���鍇���s����Z�o���Ă���`�悷��
	if ( pMeshContainer->pSkinInfo )
	{
		AttribIdPrev = UNUSED32; 
		pBoneComb = reinterpret_cast<LPD3DXBONECOMBINATION>
						(pMeshContainer->pBoneBuffer->GetBufferPointer());

		// �����O���[�v���Ƃɕ`����s��
		for (UINT iAttrib = 0; iAttrib < pMeshContainer->NumBones; iAttrib++)
		{
			// �����O���[�v���̍ő�{�[�����𒲂ׂ�
			UINT NumBlend = 0;
			for ( UINT i = 0;  i < pMeshContainer->NumInfl;  i++ )
			{
				if ( pBoneComb[iAttrib].BoneId[i] != UINT_MAX )
				{
					NumBlend = i;
				}
			}
	
			// ���_�u�����h�������C�n�[�h�E�F�A�Ŏ��s�\�Ȃ�`�悷��
			if( g_d3dcaps.MaxVertexBlendMatrices >= NumBlend + 1 )
			{
				// �{�[���̃I�t�Z�b�g�s��Ƃ𔽉f���Ă���{�[�������[���h�ϊ��s��ɐݒ肵�܂��B
				for ( UINT i = 0;  i < pMeshContainer->NumInfl;  i++ )
				{
					UINT iMatrixIndex = pBoneComb[iAttrib].BoneId[i];
					if (iMatrixIndex != UINT_MAX)
					{
						matOffset	= pMeshContainer->pBoneOffsetMatrices[iMatrixIndex];
						matBoneInfl = *(pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]);

						// �s��̍���
						matTmp =  matOffset * matBoneInfl;

						// ���[���h�ϊ��s��̐ݒ�
						g_pd3dDevice->SetTransform( D3DTS_WORLDMATRIX( i ), &matTmp );
					}
				}

				// �`�����(�����_�[�X�e�[�g)�̐ݒ�
				g_pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND, NumBlend );

				// �}�e���A���ƃe�N�X�`���̓K�p
				if ((AttribIdPrev != pBoneComb[iAttrib].AttribId) || (AttribIdPrev == UNUSED32))
				{
					g_pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[pBoneComb[iAttrib].AttribId].MatD3D );
					g_pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[pBoneComb[iAttrib].AttribId] );
					AttribIdPrev = pBoneComb[iAttrib].AttribId;
				}

				// ���b�V���̕`��
				pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
			}
		}

		// �`�����(�����_�[�X�e�[�g)�̕��A
		g_pd3dDevice->SetRenderState( D3DRS_VERTEXBLEND, 0 );
	}

	// �X�L����񂪑��݂��Ȃ��Ȃ�C�P�ɕ`�悷��
	else
	{
		// ���[���h�ϊ��s��̐ݒ�
		g_pd3dDevice->SetTransform( D3DTS_WORLD, &pFrame->CombinedTransformMatrix );

		// �}�e���A���O���[�v�ɕ����ĕ`�悷��
		for ( UINT iMaterial=0;  iMaterial < pMeshContainer->NumMaterials;  iMaterial++ )
		{
			// �}�e���A���̐ݒ�
			g_pd3dDevice->SetMaterial( &pMeshContainer->pMaterials[iMaterial].MatD3D );

			// �e�N�X�`���̐ݒ�
			g_pd3dDevice->SetTexture( 0, pMeshContainer->ppTextures[iMaterial] );

			// ���b�V���̕`��
			pMeshContainer->MeshData.pMesh->DrawSubset(iMaterial);
		}
	}
}


//=============================================================================
// DirectInput�֘A
//=============================================================================

// �W���C�p�b�h���擾 (�W���C�p�b�hNo, �擾�������L�[���)
bool gsJoyCheck( int Num, int State )
{
	bool bNowStat = g_sysJoy.m_InpState[1][Num] & State ? true : false;

	return bNowStat;
}


// �W���C�p�b�h���擾 (�W���C�p�b�hNo, �擾�������L�[���)
int gsGetJoyPadState( int Num, int State )
{

	bool bOldStat = g_sysJoy.m_InpState[0][Num] & State ? true : false;
	bool bNowStat = g_sysJoy.m_InpState[1][Num] & State ? true : false;


	if ( !bOldStat && !bNowStat ) return GSKS_RELEASE;  // ������Ă���
	if ( !bOldStat &&  bNowStat ) return GSKS_DOWN;	    // ��������
	if (  bOldStat &&  bNowStat ) return GSKS_PRESS;	// �������ςȂ�
	if (  bOldStat && !bNowStat ) return GSKS_UP;		// ����������

	return GSKS_RELEASE;	// (�N���肦�Ȃ�)
}


// �W���C�p�b�h�̏�����
bool InitJoyPad( void )
{
	int      i;
	HRESULT  hr;



	for( i=0 ; i<16 ; i++ )g_sysJoy.m_pDIDJoy[i] = NULL;

	// �W���C�p�b�h���g�p�ł���ő吔��ݒ�
	int JoystickMax = joyGetNumDevs();

	// ���ʂ͂P�U��
	if( JoystickMax >= 16 ) 
		JoystickMax = 16;

	// �ڑ�����Ă���W���C�p�b�h�����N���A
	g_JoystickCount = 0;

	// DirectInput8�I�u�W�F�N�g���쐬����Ă��邩�H
	if( g_sysJoy.m_pDInp == NULL ){
		// DirectInput8�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create( g_hInst, DIRECTINPUT_VERSION, 
								IID_IDirectInput8, (void**)&g_sysJoy.m_pDInp, NULL); 
		if (FAILED(hr)) 
		{
			MessageBox( NULL, "DirectInput8�I�u�W�F�N�g�쐬���s", "Error", MB_OK | MB_ICONSTOP );
			return false;
		}
	}

	// �f�o�C�X��񋓂��č쐬
	hr = g_sysJoy.m_pDInp->EnumDevices(DI8DEVCLASS_GAMECTRL,
									 EnumJoyPadsCallback,
									 NULL,
									 DIEDFL_ATTACHEDONLY);

	if(FAILED(hr) || (g_sysJoy.m_pDIDJoy[0] == NULL))
	{
		// �W���C�p�b�h�Ȃ��Ȃ�
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
		// �f�[�^�`����ݒ�
		hr = g_sysJoy.m_pDIDJoy[i]->SetDataFormat(&c_dfDIJoystick2);

		if (FAILED(hr))
		{
			MessageBox( NULL, "�W���C�p�b�h�p�f�[�^�t�H�[�}�b�g�ݒ莸�s", "Error", MB_OK | MB_ICONSTOP );
			return false;
		}

		// �R�[���o�b�N�֐����g���Ċe���̃��[�h��ݒ�
		g_NowNum = i;

		hr = g_sysJoy.m_pDIDJoy[i]->EnumObjects(EnumAxesCallback, g_hWnd, DIDFT_ALL);

		if (FAILED(hr))
		{
			MessageBox( NULL, "�����[�h�ݒ莸�s", "Error", MB_OK | MB_ICONSTOP );
			return false;
		}

		// �����[�h��ݒ�i��Βl���[�h�ɐݒ�B�f�t�H���g�Ȃ̂ŕK�������ݒ�͕K�v�Ȃ��j
		DIPROPDWORD diprop;

		diprop.diph.dwSize			= sizeof(diprop); 
		diprop.diph.dwHeaderSize	= sizeof(diprop.diph); 
		diprop.diph.dwObj			= 0;
		diprop.diph.dwHow			= DIPH_DEVICE;
		diprop.dwData				= DIPROPAXISMODE_ABS;
	//	diprop.dwData				= DIPROPAXISMODE_REL;	// ���Βl���[�h�̏ꍇ
		hr = g_sysJoy.m_pDIDJoy[i]->SetProperty(DIPROP_AXISMODE, &diprop.diph);

		if (FAILED(hr))
		{
			MessageBox( NULL, "�����[�h�̐ݒ�Ɏ��s�I", "Error", MB_OK | MB_ICONSTOP );
			return false;
		}

		// �o�b�t�@�����O�E�f�[�^���擾���邽�߁A�o�b�t�@�E�T�C�Y��ݒ�
		diprop.dwData = DIDEVICE_BUFFERSIZE;

		hr = g_sysJoy.m_pDIDJoy[i]->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph);

		if (FAILED(hr))
		{
			MessageBox( NULL, "�o�b�t�@�T�C�Y�̐ݒ�Ɏ��s�I", "Error", MB_OK | MB_ICONSTOP );
			return false;
		}

		// �W���C�p�b�h�̓��͐���J�n
		g_sysJoy.m_pDIDJoy[i]->Acquire();
	}

	return true;
}


// �W���C�p�b�h�񋓊֐�
BOOL CALLBACK EnumJoyPadsCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext)
{
	HRESULT hr;


	// �񋓂��ꂽ�W���C�p�b�h�ւ̃C���^�[�t�F�C�X���擾����
	hr = g_sysJoy.m_pDInp->CreateDevice(pdidInstance->guidInstance, &g_sysJoy.m_pDIDJoy[g_JoystickCount], NULL);

	if (FAILED(hr)) return DIENUM_CONTINUE;

	// �W���C�p�b�h�̔\�͂𒲂ׂ�
	g_sysJoy.m_diDevCaps.dwSize = sizeof(DIDEVCAPS);

	hr = g_sysJoy.m_pDIDJoy[g_JoystickCount]->GetCapabilities(&g_sysJoy.m_diDevCaps);

	if (FAILED(hr))
	{
		// �W���C�p�b�h�\�͂̎擾�Ɏ��s
		g_sysJoy.m_pDIDJoy[g_JoystickCount]->Release();
		return DIENUM_CONTINUE;
	}

	return ( ++g_JoystickCount == g_JoystickMax ) ? ( DIENUM_STOP ) : ( DIENUM_CONTINUE );
}


// �W���C�p�b�h�̎���񋓂���֐�
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{

	HRESULT hr;
	int     i = g_NowNum;


	// ���̒l�͈̔͂�ݒ�i-1000�`1000�j
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


// �W���C�p�b�h�̏�Ԑ���
void Update_JoyPadInfo(void)
{
	int			 i;
	HRESULT		 hr;
	DIJOYSTATE2  dijs;	// ���݂̃W���C�p�b�h�̏��



	// 1���[�v�O�̓��͏���ޔ� (�����n�߂����o���邽��)
	memcpy(&g_sysJoy.m_InpState[0], &g_sysJoy.m_InpState[1], sizeof(int)*16);


	// ���͏�񏉊���
	for( i=0 ; i<16 ; i++ ){
		g_sysJoy.m_InpState[1][i] = 0;
	}

	for( i=0 ; i<g_JoystickCount ; i++ ){
		// �W���C�p�b�h�ڑ��H
		if (g_sysJoy.m_pDIDJoy[i] != NULL)
		{
			// �f�o�C�X����f�[�^���|�[�����O
			if (FAILED(hr = g_sysJoy.m_pDIDJoy[i]->Poll()))
			{
				hr = g_sysJoy.m_pDIDJoy[i]->Acquire();
				while(hr == DIERR_INPUTLOST)
				{
					// �W���C�p�b�h�̓��͐���J�n
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


			// �W���C�p�b�h���͏��Z�b�g
			if ( dijs.rgdwPOV[0] == 0)      g_sysJoy.m_InpState[1][i] |= KEY_UP;		// ��  (�\���L�[)
			if ( dijs.rgdwPOV[0] == 4500)   g_sysJoy.m_InpState[1][i] |= KEY_RIGHTUP;	// �E��(�\���L�[)
			if ( dijs.rgdwPOV[0] == 9000)   g_sysJoy.m_InpState[1][i] |= KEY_RIGHT;		// �E  (�\���L�[)
			if ( dijs.rgdwPOV[0] == 13500)  g_sysJoy.m_InpState[1][i] |= KEY_RIGHTDOWN; // �E��(�\���L�[)
			if ( dijs.rgdwPOV[0] == 18000)  g_sysJoy.m_InpState[1][i] |= KEY_DOWN;		// ��  (�\���L�[)
			if ( dijs.rgdwPOV[0] == 22500)  g_sysJoy.m_InpState[1][i] |= KEY_LEFTDOWN;	// ����(�\���L�[)
			if ( dijs.rgdwPOV[0] == 27000)  g_sysJoy.m_InpState[1][i] |= KEY_LEFT;		// ��  (�\���L�[)
			if ( dijs.rgdwPOV[0] == 31500)  g_sysJoy.m_InpState[1][i] |= KEY_LEFTUP;	// ����(�\���L�[)

			if ( dijs.lY < -500)			g_sysJoy.m_InpState[1][i] |= JOYPAD_UP;		// ��(�W���C�p�b�h)
			if ( dijs.lY >  500)			g_sysJoy.m_InpState[1][i] |= JOYPAD_DOWN;	// ��(�W���C�p�b�h)
			if ( dijs.lX < -500)			g_sysJoy.m_InpState[1][i] |= JOYPAD_LEFT;	// ��(�W���C�p�b�h)
			if ( dijs.lX >  500)			g_sysJoy.m_InpState[1][i] |= JOYPAD_RIGHT;	// �E(�W���C�p�b�h)

			if ( dijs.rgbButtons[0])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON1;	// �{�^���P
			if ( dijs.rgbButtons[1])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON2;	// �{�^���Q
			if ( dijs.rgbButtons[2])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON3;	// �{�^���R
			if ( dijs.rgbButtons[3])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON4;	// �{�^���S
			if ( dijs.rgbButtons[4])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON5;	// �{�^���T
			if ( dijs.rgbButtons[5])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON6;	// �{�^���U
			if ( dijs.rgbButtons[6])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON7;	// �{�^���V
			if ( dijs.rgbButtons[7])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON8;	// �{�^���W
			if ( dijs.rgbButtons[8])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON9;	// �{�^���X
			if ( dijs.rgbButtons[9])		g_sysJoy.m_InpState[1][i] |= JOYPAD_BUTTON10;	// �{�^���P�O
		}
	}
}


//=============================================================================
//	�T�E���h�֌W
//=============================================================================

//=================================================================
// �@�\�FDirectSound������
// �����F�Ȃ�
// �Ԃ�l�F����true�A���sfalse
//=================================================================
bool InitDirectSound()
{
	HRESULT   hr;


	//=================================================
	// DirectSound����
	//=================================================
	hr = DirectSoundCreate8(NULL, &g_lpDirectSound, NULL);
	if FAILED( hr ) return false;


	// �������x���̐ݒ�
	// (�������x���Ƃ͑��̃A�v���P�[�V�����Ɠ����f�o�C�X�𓯎����p����Ƃ��̗D��x)
	// (��2�����ɂ�DSSCL_PRIORITY(�W�����������n�[�h�E�F�A�ɋ߂��������s����)�̑���
	// DSSCL_NORMAL(�v���C�}���o�b�t�@���f�t�H���g�ݒ�Ŏg��)�A
	// DSSCL_WRITEPRIMARY(�v���C�}���o�b�t�@�ɃA�N�Z�X�ł��邪�Z�J���_���o�b�t�@�g�p�s��)������B)
	hr = g_lpDirectSound->SetCooperativeLevel( g_hWnd, DSSCL_PRIORITY );

	if FAILED( hr )
	{
		hr = g_lpDirectSound->SetCooperativeLevel( g_hWnd, DSSCL_NORMAL );
		if FAILED( hr ) return false;
	}


	//=================================================
	// �v���C�}���T�E���h�o�b�t�@����
	//=================================================
//	DSBUFFERDESC desc = { sizeof(DSBUFFERDESC) };

//	LPDIRECTSOUNDBUFFER pSBPrimary = NULL;
	DSBUFFERDESC dsbdesk;
	memset(&dsbdesk, 0, sizeof(DSBUFFERDESC));
	dsbdesk.dwSize = sizeof(DSBUFFERDESC);
	dsbdesk.dwFlags = DSBCAPS_PRIMARYBUFFER		// �v���C�}���o�b�t�@�����
						| DSBCAPS_CTRLVOLUME	// �{�����[���̕ύX��L���ɂ���
					    | DSBCAPS_CTRLPAN;		// �p����L���ɂ���

	// �v���C�}���T�E���h�o�b�t�@�̍쐬
	g_lpDirectSound->CreateSoundBuffer(&dsbdesk, &g_lpPrimaryBuffer, NULL);

	// �v���C�}���o�b�t�@�̃t�H�[�}�b�g���w��
	WAVEFORMATEX wfx;

	memset(&wfx, 0, sizeof(wfx)); 
	wfx.wFormatTag = WAVE_FORMAT_PCM; // PCM�`��
	wfx.nChannels = 2;				  // �`�����l��(�X�e���I)
	wfx.nSamplesPerSec = 44100;		  // �T���v�����O���[�g(44.1kHz)
	wfx.wBitsPerSample = 16;		  // �ʎq���r�b�g(16bit)
	wfx.nBlockAlign = 4;			  // 1�T���v�����O������̃o�C�g��(16bit�~2ch)
	wfx.nAvgBytesPerSec = 176400;	  // 1�b������̃o�C�g��(16bit�~2ch�~44100Hz)

	g_lpPrimaryBuffer->SetFormat(&wfx);


	if FAILED( hr ) return false;

	return true;
}



//---------------------------------------------------------------------
//	���T�E���h��ǂݍ���
//		void gsLoadSound(gsSound *sound,  char *str )
//
//		���� [out]	sound		: �T�E���h���Ǘ�����ϐ��ւ̃|�C���^
//		���� [in]	str			: �T�E���h�̃t�@�C����
//
//		�߂�l	�Ȃ�
//---------------------------------------------------------------------
void gsLoadSound( gsSound *sound, char *str )
{
	char *str2;
	int err;

	err = 0;
	str2 = str;
	while ( *str2 != '\0')
	{
		// �g���q��wav�����ׂ�
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

	// wav�`���łȂ��ꍇ�i���̖��߂�wav�̂ݑΉ��j
	if ( err == 0 )
	{
		MessageBox( NULL, "�T�E���h�t�@�C����wav�`���ł͂���܂���\n�I�����܂�", str, MB_OK );
		PostQuitMessage(0);
	}

	*sound = LoadWave(str);

	// ���[�h���s
	if ( *sound == NULL )
	{
		MessageBox( NULL, "�T�E���h�t�@�C��������܂���\n�I�����܂�", str, MB_OK );
		PostQuitMessage(0);
	}
}

//---------------------------------------------------------------------
//	���T�E���h���������
//		void gsReleaseSound( gsSound sound )
//
//		���� [out]	sound		: �T�E���h���Ǘ�����ϐ�
//
//		�߂�l	�Ȃ�
//---------------------------------------------------------------------
void gsReleaseSound( gsSound sound )
{
	GS_SAFE_RELEASE( sound );
}


//---------------------------------------------------------------------
//	���T�E���h���v���C����
//		void gsPlaySound( gsSound sound )
//
//		�����@�Ȃ�
//
//		�߂�l	�Ȃ�
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
//	���T�E���h���~�߂�
//		void gsStopSound( gsSound sound )
//
//		�����@�Ȃ�
//
//		�߂�l	�Ȃ�
//---------------------------------------------------------------------
void gsStopSound( gsSound sound)
{
	sound->Stop();
}


//=================================================================
// �@�\�F�������
// �����F�Ȃ�
// �Ԃ�l�F�Ȃ�
//=================================================================
void ReleaseDirectSound( void )
{
	if ( g_lpPrimaryBuffer != NULL ) g_lpPrimaryBuffer->Release();
	if ( g_lpDirectSound   != NULL ) g_lpDirectSound->Release();
}


//=================================================================
// �@�\�F�Z�J���_���o�b�t�@���쐬����Wave�t�@�C����ǂݍ���
// �����Fwav�t�@�C����
// �Ԃ�l�F�g�`�f�[�^��ǂݍ��񂾃T�E���h�o�b�t�@�|�C���^
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
	// Wave�t�@�C���t�H�[�}�b�g���ƃf�[�^�T�C�Y���擾
	//=====================================================
	szWavData = GetWaveData( file, &lpWavData, &wf );
	if ( szWavData == 0 ) goto EXIT;

	//=====================================================
	// DirectSoundBuffer�ݒ�
	//=====================================================
	desc.dwFlags       = DSBCAPS_LOCDEFER;
	desc.dwBufferBytes = szWavData;
	desc.lpwfxFormat   = &wf;

	//=====================================================
	// DirectSoundBuffer����
	//=====================================================
	hr = g_lpDirectSound->CreateSoundBuffer( &desc, &lpTempBuff, NULL );
	if FAILED( hr ) goto EXIT;

	//=====================================================
	// DirectSoundBuffer ���� DirectSoundBuffer8�C���^�t�F�[�X�̎擾
	//=====================================================
	hr = lpTempBuff->QueryInterface( IID_IDirectSoundBuffer8, (void **)&lpBuffer );
	lpTempBuff->Release();

	if FAILED( hr ) goto EXIT;


	//=====================================================
	// �o�b�t�@���b�N
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

	// �T�E���h�f�[�^�ǂݍ���
	memcpy( lpSoundData1, lpWavData, szWavData );

	// ���b�N����
	lpBuffer->Unlock( lpSoundData1, size1, lpSoundData2, size2 );

	result = lpBuffer;

// �I��
EXIT:
	if ( lpWavData != NULL ) delete [] lpWavData;

	return result;
}


//=================================================================
// �@�\  �FWave�f�[�^�ǂݍ���
// ����  �F�t�@�C�����A�g�`�i�[�|�C���^�AWave�w�b�_
// �Ԃ�l�F�g�`�f�[�^�T�C�Y
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
	// �t�@�C���I�[�v��
	//--------------------------------------------------------
	fp = fopen( file, "rb" );
	if ( fp == NULL ) goto EXIT;

	//--------------------------------------------------------
	// "RIFF"�̕�����
	//--------------------------------------------------------
	fread( Chunk, sizeof(char), 4, fp );
	if ( strcmp( "RIFF", Chunk ) ) goto EXIT;

	//--------------------------------------------------------
	// RIFF�f�[�^�T�C�Y
	//--------------------------------------------------------
	fread( &RiffDataSize, sizeof(long), 1, fp );

	//--------------------------------------------------------
	// "WAVE"�̕�����
	//--------------------------------------------------------
	fread( Chunk, sizeof(char), 4, fp );
	if ( strcmp( "WAVE", Chunk ) ) goto EXIT;

	//========================================================
	// Foramt �`�����N
	//========================================================
	// "fmt "�̕�����
	fread( Chunk, sizeof(char), 4, fp );
	if ( strcmp( "fmt ", Chunk ) ) goto EXIT;

	//--------------------------------------------------------
	// fmt�f�[�^�T�C�Y
	//--------------------------------------------------------
	fread( &fmtDataSize, sizeof(long), 1, fp );

	//--------------------------------------------------------
	// �t�H�[�}�b�g���擾
	//--------------------------------------------------------
	FormatSize = sizeof(WAVEFORMATEX);
	fread( lpwf, FormatSize, 1, fp );

	// PCM�̎��ͥ��
	if ( lpwf->wFormatTag == 1 )
	{
		// �ǉ��f�[�^�͂���܂���
		lpwf->cbSize = 0;
	}

	fseek( fp, fmtDataSize-sizeof(WAVEFORMATEX), SEEK_CUR );

	//========================================================
	// Data�`�����N����
	//========================================================
	while ( true )
	{
		// �`�����N�`�F�b�N
		fread( Chunk, sizeof(char), 4, fp );
		// ��t�@�C���H
		if ( feof( fp ) ) goto EXIT;
		// �f�[�^�`�����N�H
		if ( strcmp( "data", Chunk ) == 0 )
		{
			break;
		}
		else
		{
			// �f�[�^�`�����N�Ŗ�����Ύ��̃`�����N��
			DWORD size;

			fread( &size, sizeof(DWORD), 1, fp );
			fseek( fp, size, SEEK_CUR );
		}
	}

	// �f�[�^�`�����N�̃T�C�Y���擾
	fread( &DataSize, sizeof(long), 1, fp );

	// �f�[�^�{�̂��擾
	*lpData = new BYTE [ DataSize ];
	fread( *lpData, sizeof(BYTE), DataSize, fp );

	result = DataSize;

	// �I��
EXIT:
	if ( fp != NULL ) fclose( fp );

	return result;
}

/*

�l�b�h���g�p�����T�E���h�A���݂͖��g�p

// �T�E���h���I�[�v������
bool	gsSoundOpen(gsSound *pSound, char *szFileName)
{
	// �t�@�C�����̑ޔ�p
	char *pName;

	// �p�����[�^�̐ݒ�
	pSound->m_OpenParam.dwCallback		= 0;
	pSound->m_OpenParam.lpstrDeviceType = 0;

	// �t�@�C�����̑ޔ�
	pName = new char[lstrlen(szFileName)+1];
	lstrcpy(pName, szFileName);
	pSound->m_OpenParam.lpstrElementName = pName;
	
	// �t�@�C���I�[�v��
	MCIERROR mcirc;
	char strErr[1024];

	mcirc = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&pSound->m_OpenParam);

	if (mcirc)
	{	
		mciGetErrorString(mcirc , strErr , 1024);
		gsDebugPrintf("�I�[�v���G���[[%s]\n", strErr);
	}

	return	true;
}

// �T�E���h���N���[�Y����
bool	gsSoundClose(gsSound *pSound)
{
	mciSendCommand(pSound->m_OpenParam.wDeviceID, MCI_CLOSE, 0, 0);
	delete [] pSound->m_OpenParam.lpstrElementName;

	pSound->m_OpenParam.lpstrElementName = 0;

	return	true;
}

// �T�E���h���ŏ�����Đ�����
bool	gsSoundPlay(gsSound *pSound)
{
	static MCI_PLAY_PARMS mpp;
	MCIERROR mcirc;
	char strErr[1024];

	mcirc = mciSendCommand(pSound->m_OpenParam.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START,	0);
	if (mcirc)
	{	
		mciGetErrorString(mcirc , strErr , 1024);
		gsDebugPrintf("�V�[�N�G���[[%s]\n", strErr);
	}
	mcirc = mciSendCommand(pSound->m_OpenParam.wDeviceID, MCI_PLAY, 0, (DWORD_PTR)&mpp);
	if (mcirc)
	{	
		mciGetErrorString(mcirc , strErr , 1024);
		gsDebugPrintf("�Đ��G���[[%s]\n", strErr);
	}

	return	true;
}

// �T�E���h�̒�~
bool	gsSoundStop(gsSound *pSound)
{
	mciSendCommand(pSound->m_OpenParam.wDeviceID, MCI_STOP, 0, 0);

	return	true;
}

// �T�E���h���~�܂��Ă��邩�ǂ������e�X�g����
bool	gsSoundisStopped(gsSound *pSound)
{
	MCI_STATUS_PARMS mciStatus;

	mciStatus.dwItem = MCI_STATUS_MODE;
	mciSendCommand(pSound->m_OpenParam.wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&mciStatus);

	return (mciStatus.dwReturn != MCI_MODE_PLAY);
}
*/

//=====================================================================
//	FPS �\������
//=====================================================================

int gFPS1,gFPS2;
int gFPSTime1,gFPSTime2;

//---------------------------------------------------------------------
// FPS������
// �ŏ��ɌĂяo��
//---------------------------------------------------------------------
void gsInitFPS(void)
{
	gFPS1=0; gFPS2=0;
	gFPSTime1=0;	gFPSTime2=0;
}

//---------------------------------------------------------------------
// FPS����
// �P���[�v�ɂP��Ăяo��
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
// FPS�\��
//---------------------------------------------------------------------
void gsDrawFPS( int x, int y )
{
	gsDrawNum( x, y, gFPS2);
}


//---------------------------------------------------------------------------------------
//	���f�o�b�O�p������̃A�E�g�v�b�g�E�B���h�E�ւ̏o��
//		�f�o�b�O�ɗp����֐��B�ϐ��̒l��\�����邱�Ƃ��ł���B
//
//		int		gsDebugPrintf(char *szFormat, ...);
//
//		���� [in]		szFormat	: �\���t�H�[�}�b�g
//			 [in]		...			: �O�ȏ�̈����̎w��
//				
//		�߂�l			�o�͕�����
//
//		���\���ł���ő啶�����́AGS_MAX_DEBUG_STRING �ł���B
//		���f�o�b�O���̂ݕ\�������B
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
//	���G���[���b�Z�[�W�̃A�E�g�v�b�g�E�B���h�E�ւ̕\��
//		�G���[�R�[�h�ɑΉ������G���[���b�Z�[�W���A�E�g�v�b�g�E�B���h�E�ɕ\������D
//
//		void	gsErrorMsg(LPCSTR szPreMessage, HRESULT hErrorCode);
//
//		���� [in]	szPreMessage	: �G���[���Ȃǂ�����������
//		���� [in]	hErrorCode		: �G���[�R�[�h
//
//		�߂�l		�Ȃ�
//---------------------------------------------------------------------------------------
void	gsErrorMsg(LPCSTR szPreMessage, HRESULT hErrorCode)
{
	gsDebugPrintf("%s[%s]\n", szPreMessage, DXGetErrorString(hErrorCode));
}

void ShowConsole()//�� �f�o�b�O�p�錾(�폜��)
{
	/*�R���\�[���E�B���h�E���쐬*/
	AllocConsole();
	freopen(
		"CONIN$",						//�V�����t�@�C���̃p�X
		"r",							//�A�N�Z�X���̎��
		stdin							//FILE�\���̂ւ̃|�C���^
		);
	freopen(
		"CONOUT$",
		"w",
		stdout
		);
}