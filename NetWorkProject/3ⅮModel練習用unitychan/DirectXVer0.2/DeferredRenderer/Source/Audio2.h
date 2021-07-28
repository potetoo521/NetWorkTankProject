//=============================================================================
//
// サウンド処理 [XAudio2.h]
//
//=============================================================================

#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_
//#include <d3d10.h>
#include <xaudio2.h>

// サウンドファイル
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// サンプルBGM
	//SOUND_LABEL_SE000,			// サンプルSE
	//SOUND_LABEL_SE001,			// サンプルSE0
	//SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(void);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void PauseSound(SOUND_LABEL label);
#endif
