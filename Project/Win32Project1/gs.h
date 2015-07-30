//=====================================================================
//	�b�� 3D �w�Z���C�u���� �w�b�_�[�t�@�C��
//
//	�t�@�C����	�y gs.h �z	Ver 2.3
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

#ifndef	__GS_H
#define	__GS_H

//---------------------------------------------------------------------
//	�� �R���p�C���C�����J�ւ̎w��
//---------------------------------------------------------------------

//	���[�j���O(�x��)�G���[�\���}��
#pragma warning(disable:4996)	// sprintf, strcpy �Ȃǂ̎g�p���̌x���G���[
#pragma warning(disable:4819)	// �����R�[�h�y�[�W�Ɋւ���x���G���[

// �g�p��������}���`�o�C�g�R�[�h(SJIS)���p�ɂ���
#ifdef UNICODE		// UNICODE������
	#undef UNICODE
	#undef _UNICODE
#endif

#ifndef _MBCS		// SJIS�g�p
	#define _MBCS
#endif

//	���C�u�����̎Q�Ǝw��
#pragma comment(lib, "d3d9.lib"	)			// Direct3D ���C�u����
#ifdef _DEBUG
	#pragma comment(lib, "d3dx9d.lib" )		// Direct3D Extension ���C�u����
#else										//  Debug   �o�[�W������
	#pragma comment(lib, "d3dx9.lib"  )		//  Release �o�[�W����������
#endif

#pragma comment(lib, "dsound.lib") 
#pragma comment(lib, "dinput8.lib" )		// DirectInput
#pragma comment(lib, "dxguid.lib"  )		// Guid
#pragma comment(lib, "winmm.lib"   )		// �}���`���f�B�A
#pragma comment(lib, "dxerr.lib"  )			// DirectX �G���[�������[�e�B���e�B


//---------------------------------------------------------------------
//	�� �C���N���[�h
//---------------------------------------------------------------------
#include <windows.h>		// Windows API
#include <d3d9.h>			// Direct3D
#include <d3dx9.h>			// Direct3D Extension�iDirectX �g���j
#define  DIRECTINPUT_VERSION 0x0800
#include <dinput.h>			// DirectInput
#include <dsound.h>
#include <dxerr.h>			// DirectX �G���[�������[�e�B���e�B
#include <mmsystem.h>		// timeGetTime
#include <cstdlib>			// srand, rand


//---------------------------------------------------------------------
//	�� �}�N��
//---------------------------------------------------------------------

// ��
#define		GSPI				D3DX_PI

// �����֌W	(������ XorShift �A���S���Y���ɕύX�\��)
#define		gsRandomize()		srand((unsigned)timeGetTime())
#define		gsRandom(n)			(int)( ((long)rand() * (n))/ (RAND_MAX+1) )

// �J���[
#define		GSRGB(r,g,b)		D3DCOLOR_XRGB((r),(g),(b))
#define		GSARGB(a,r,g,b)		D3DCOLOR_ARGB((a),(r),(g),(b))

// �L�[������Ԃ̎擾
#define		gsKeyCheck(vk)		(gsKeyState(vk) == GSKS_PRESS)

// �E�B���h�E�T�C�Y
#define		GS_WINDOW_WIDTH		64 * 16
#define		GS_WINDOW_HEIGHT		64 * 9

// �A�v���P�[�V�����̋����I��
#define		gsQuitApplication()		PostQuitMessage(0)

// ����������p�}�N��
#ifndef		GS_SAFE_RELEASE
	#define GS_SAFE_RELEASE(p)		{ if(p) { (p)->Release(); (p) = NULL; } }
#endif
#ifndef		GS_SAFE_DELETE
	#define GS_SAFE_DELETE(p)		{ if(p) { delete (p);     (p) = NULL; } }
#endif
#ifndef		GS_SAFE_DELETE_ARRAY
	#define	GS_SAFE_DELETE_ARRAY(p)	{ if(p) { delete [] (p);  (p) = NULL; } }
#endif

// �f�o�b�O������\��
#define		GS_MAX_DEBUG_STRING		256			// �f�o�b�N������ő啶����
#define		GS_NOT_USE_PARAM(x)		(x) = (x)	// ���g�p�����̌x���G���[�𖳎�������



//---------------------------------------------------------------------
//	�� �^�錾
//---------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////
// �e�N�X�`���[
typedef		LPDIRECT3DTEXTURE9	gsTexture;

///////////////////////////////////////////////////////////////////////
//	�x�N�g��
typedef		D3DXVECTOR2			gsVec2;
typedef		D3DXVECTOR3			gsVec3;

///////////////////////////////////////////////////////////////////////
//	�J���[
typedef		D3DCOLOR			gsColor;

//---------------------------------------------------------------------
//	�� ���_�t�H�[�}�b�g
//---------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////
//	�g�����X�t�H�[���ς݁C���C�e�B���O�ς� ���_�t�H�[�}�b�g
#define	FVF_TLVERTEX	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

struct gsTLVertex
{
    gsVec3		pos;		// �ʒu(2D���W) (x, y, z)
    float		rhw;		// 1/w
	gsColor		color;		// ���_�J���[(�f�B�t���[�Y�F)
    gsVec2		uv;			// �e�N�X�`���[���W (u, v)
};

///////////////////////////////////////////////////////////////////////
//	���C�e�B���O�ς� ���_�t�H�[�}�b�g
#define	FVF_LVERTEX		( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

struct gsLVertex
{
    gsVec3		pos;		// �ʒu (x, y, z)
	gsColor		color;		// ���_�J���[(�f�B�t���[�Y�F)
    gsVec2		uv;			// �e�N�X�`���[���W (u, v)
};

///////////////////////////////////////////////////////////////////////
//	���_�t�H�[�}�b�g
#define	FVF_VERTEX		( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )

struct gsVertex
{
    gsVec3		pos;		// �ʒu (x, y, z)
	gsVec3		normal;		// �@���x�N�g��
    gsVec2		uv;			// �e�N�X�`���[���W (u, v)
};


//---------------------------------------------------------------------
//	�� enum�^
//---------------------------------------------------------------------
// �L�[�̏��
enum	_GSKS
{
	GSKS_RELEASE	= 0,	// ������Ă���
	GSKS_DOWN		= 1,	// ��������
	GSKS_PRESS		= 2,	// �������ςȂ�	
	GSKS_UP			= 3,	// ����������
};


//---------------------------------------------------------------------
//	���֐��v���g�^�C�v�錾
//---------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////
// ���C���V�X�e���ŗL�̊֐�
INT		WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT );
LRESULT	WINAPI gsMsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
void	gsInitD3D( HWND hWnd, bool WindowMode );


///////////////////////////////////////////////////////////////////////
// ���ʋ@�\�̊֐�
void	gsLoadTexture(gsTexture *pTexture,  char *str, gsColor colorKey);
void	gsReleaseTexture(gsTexture texture);
void	gsCleanup();
void	gsRender();

void	gsSetNormalColor(void);
void	gsSetAddColor(void);


///////////////////////////////////////////////////////////////////////
// 2D �֌W�̊֐�
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
// ��{�}�`�̕`��

// ����
void	gsDraw2DLine	 (int x1, int y1, int x2, int y2, gsColor color);

// �����`
void	gsDraw2DRectangle(int x1, int y1, int x2, int y2, gsColor color,
													bool bFillMode = false);

// �~
void	gsDraw2DCircle	 (int cx, int cy, int r,  gsColor color, 
													bool bFillMode = false);	


///////////////////////////////////////////////////////////////////////
// �t�H���g�֌W
void	gsInitFont();
void	gsReleaseFont();
void	gsDrawText( int x, int y, char *str );
void	gsDrawNum ( int x, int y, int a );

void	gsSetFont(int size, char *szFontName = "�l�r �S�V�b�N" );	
int		gsDrawPrintf	  (int x, int y, gsColor color, char *szFormat, ...);
int		gsDrawPrintfShadow(int x, int y, gsColor color, char *szFormat, ...);


///////////////////////////////////////////////////////////////////////
//	�L�[�̉�����Ԃ𒲂ׂ�֐�
int		gsKeyState(UINT vk);


// �}�E�X�̈ʒu�Ɋ֌W����֐� <������>
//int	gsGetMouseX(void);
//int	gsGetMouseY(void);
//void	gsSetMouseX(int posx);
//void	gsSetMouseY(int posy);


///////////////////////////////////////////////////////////////////////
// 3D �֌W�̊֐�
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
//	�t���[���\���� 
//	�������ϊ��s����v�Z����Ƃ��ɕ֗��Ȃ悤�Ɋg�����Ă���
struct gsFrame : public D3DXFRAME
{
	// �e�t���[���ɓK�p���鍇���ςݕϊ��s��
	D3DXMATRIXA16	CombinedTransformMatrix;
};


///////////////////////////////////////////////////////////////////////
//	���b�V���R���e�i�\����
//	X File ���� ���܂��܂ȃf�[�^��ێ����邽�߂̍\����
//	�������̃e�N�X�`���𗘗p�ł���悤�Ɋg��
//	���X�L�����b�V����������悤�Ɋg��
struct gsMeshContainer : public D3DXMESHCONTAINER
{
	///////////////////////////////////////////////////////////////////
	// �e�N�X�`��
	gsTexture	*ppTextures;

	///////////////////////////////////////////////////////////////////
	// �X�L�����
	LPD3DXMESH				pOrigMesh;				// �I���W�i���̃��b�V�����

	LPD3DXATTRIBUTERANGE	pAttributeTable;		// �����e�[�u��

	DWORD					NumInfl;				// �e�����󂯂�{�[���̍ő吔
	DWORD					NumBones;				// �{�[����

	D3DXMATRIX*				pBoneOffsetMatrices;	// �{�[���̃I�t�Z�b�g�s��

	LPD3DXBUFFER			pBoneBuffer;			// �{�[���f�[�^��Ɨp
	D3DXMATRIX**			ppBoneMatrixPtrs;

	DWORD					NumPaletteEntries;		// �p���b�g�G���g����

	// �\�t�g�E�F�A�őΉ�����ꍇ�ɗ��p�����(��������)
	bool					UseSoftwareVP;
	DWORD					iAttributeSW;
};


///////////////////////////////////////////////////////////////////////
//	gsMesh �^
struct gsMesh
{
	// �A�j���[�V�������Ȃ����b�V���̏ꍇ�Ɏg�p
	LPD3DXMESH		pMesh;				// ���b�V��
	D3DMATERIAL9*	pMeshMaterials;		// �}�e���A�����
	gsTexture*		pMeshTextures;		// �e�N�X�`�����
	DWORD			dwNumMaterials;		// �}�e���A���̐�

	// �A�j���[�V�������郁�b�V���̏ꍇ�Ɏg�p
	LPD3DXFRAME					pFrameRoot;
	LPD3DXANIMATIONCONTROLLER	pAnimController;

	// �R���X�g���N�^
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

// �K�w�\���̂Ȃ����b�V���ŗ��p����֐�
HRESULT	gsLoadX   ( gsMesh *m, char *pXFileName );
void	gsDrawX   ( gsMesh *m, float x, float y, float z, float t );
HRESULT	gsReleaseX( gsMesh* pReleaseMesh );

// �K�w�\���̂��郁�b�V���ŗ��p����֐�
HRESULT	gsLoadXA   ( gsMesh* pMesh, char* pXFileName );
void	gsDrawXA   ( gsMesh *m, float x, float y, float z, float t, double animePastTime );
HRESULT	gsReleaseXA( gsMesh *pReleaseMesh );

///////////////////////////////////////////////////////////////////////
//	�T�E���h�֌W
//	�������Đ�(MIDI������)������ꍇ�ɂ́Calias(�ʖ�)������΂���

//	gsSound �^
//struct	gsSound
//{
//	MCI_OPEN_PARMS	m_OpenParam;
//
//	// �R���X�g���N�^
//	gsSound()
//	{
//		m_OpenParam.wDeviceID		 = 0;
//		m_OpenParam.lpstrDeviceType	 = 0;
//		m_OpenParam.lpstrAlias		 = 0;
//		m_OpenParam.lpstrElementName = 0;
//		m_OpenParam.dwCallback		 = 0;
//	}
//};

//	�T�E���h����֐�
//bool	gsSoundOpen		(gsSound *pSound, char *szFileName);
//bool	gsSoundClose	(gsSound *pSound);
//bool	gsSoundPlay		(gsSound *pSound);
//bool	gsSoundStop		(gsSound *pSound);
//bool	gsSoundisStopped(gsSound *pSound);



///////////////////////////////////////////////////////////////////////
// �e�o�r����
void	gsInitFPS(void);
void	gsSetFPS(void);
void	gsDrawFPS(int x, int y);

///////////////////////////////////////////////////////////////////////
// �f�o�b�O�p������̕\��
int		gsDebugPrintf(char *szFormat, ...);
void	gsErrorMsg(LPCSTR szPreMessage, HRESULT hErrorCode);

void	gsMessage(char str[]);



// ��DirectInput�p

// �p�b�h������Ԃ̎擾
#define		gsJoyPadCheck(vk1, vk2)		(gsGetJoyPadState( vk1, vk2 ) == GSKS_PRESS)

int gsGetJoyPadState( int , int );	// �W���C�p�b�h���擾

// �W���C�p�b�h���͎��ʗp�萔
#define JOYPAD_UP		(1 << 9)					// ��(�W���C�p�b�h)
#define JOYPAD_DOWN		(1 << 10)					// ��(�W���C�p�b�h)
#define JOYPAD_LEFT		(1 << 11)					// ��(�W���C�p�b�h)
#define JOYPAD_RIGHT	(1 << 12)					// �E(�W���C�p�b�h)

// �{�^��������񎯕ʗp�萔
#define JOYPAD_BUTTON1		(1 << 13)					// �{�^�� 1
#define JOYPAD_BUTTON2		(1 << 14)					// �{�^�� 2
#define JOYPAD_BUTTON3		(1 << 15)					// �{�^�� 3
#define JOYPAD_BUTTON4		(1 << 16)					// �{�^�� 4
#define JOYPAD_BUTTON5		(1 << 17)					// �{�^�� 5
#define JOYPAD_BUTTON6		(1 << 18)					// �{�^�� 6
#define JOYPAD_BUTTON7		(1 << 19)					// �{�^�� 7
#define JOYPAD_BUTTON8		(1 << 20)					// �{�^�� 8
#define JOYPAD_BUTTON9		(1 << 21)					// �{�^�� 9
#define JOYPAD_BUTTON10		(1 << 22)					// �{�^��10


// �����p

// ���̓��X�g
#define DIDEVICE_BUFFERSIZE	100						// �f�o�C�X�ɐݒ肷��o�b�t�@�E�T�C�Y
#define KEY_BUFFRSIZE 256

// �\���L�[���͎��ʗp�萔
#define KEY_UP			(1 << 1)					// ��(�\���L�[)
#define KEY_DOWN		(1 << 2)					// ��(�\���L�[)
#define KEY_LEFT		(1 << 3)					// ��(�\���L�[)
#define KEY_RIGHT		(1 << 4)					// �E(�\���L�[)
#define KEY_RIGHTUP		(1 << 5)					// �E��(�\���L�[)
#define KEY_RIGHTDOWN	(1 << 6)					// �E��(�\���L�[)
#define KEY_LEFTDOWN	(1 << 7)					// ����(�\���L�[)
#define KEY_LEFTUP		(1 << 8)					// ����(�\���L�[)

// �W���C�p�b�h�ݒ�\����
typedef struct __INPUT{
	LPDIRECTINPUT8       m_pDInp;					// Directinput
	LPDIRECTINPUTDEVICE8 m_pDIDKey;					// DirectInput�f�o�C�X�i�L�[�{�[�h�p�j
	LPDIRECTINPUTDEVICE8 m_pDIDJoy[16];				// DirectInput�f�o�C�X�i�W���C�p�b�h�p�j
	DIDEVCAPS			 m_diDevCaps;				// �W���C�p�b�h�̔\��
	BYTE				 m_KeyState[KEY_BUFFRSIZE];	// �L�[�{�[�h���
	int					 m_InpState[2][16];			// ���݂̓��͏��
}SYSINPUT;

extern SYSINPUT          g_sysJoy;
extern int				 g_JoyPadCount;
extern int				 g_JoyPadMax;
extern int				 g_NowNum;

// �R�[���o�b�N
BOOL CALLBACK EnumJoyPadsCallback(const DIDEVICEINSTANCE* pdidInstance, VOID* pContext);
BOOL CALLBACK EnumAxesCallback(LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

bool gsJoyCheck( int Num, int State );
bool InitJoyPad();		// �W���C�p�b�h�̏�����
void Update_JoyPadInfo();	// �W���C�p�b�h�̏�Ԑ���
void CheckPad_ParallelTranslation();	// �L�[�{�[�h��p�b�h�̓��͏�񂩂畽�s�ړ��s����쐬
void CheckPad_Rotation();	// �L�[�{�[�h��p�b�h�̓��͏�񂩂��]�s����쐬
bool CheckPad_Reset();	// �p�b�h�̍��W���Z�b�g���������擾




// DirectSound�֘A
#define  LOOP_ON    1    // �g�`�f�[�^�����[�v�Đ�����
#define  LOOP_OFF   0    // �g�`�f�[�^�����[�v�Đ����Ȃ��@
typedef		LPDIRECTSOUNDBUFFER8	gsSound;

void gsLoadSound( gsSound *sound, char *str );
void gsReleaseSound( gsSound sound );
void gsPlaySound( gsSound sound, int loop_flag);
void gsStopSound( gsSound sound);


// �����p�֐�
bool InitDirectSound();
gsSound LoadWave( char *file );
DWORD GetWaveData( char *file, LPBYTE *lpData, WAVEFORMATEX *lpwf );

#endif		// __GS_H
