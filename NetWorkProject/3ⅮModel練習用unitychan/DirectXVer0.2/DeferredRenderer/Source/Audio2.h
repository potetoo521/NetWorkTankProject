//=============================================================================
//
// �T�E���h���� [XAudio2.h]
//
//=============================================================================

#ifndef _XAUDIO2_H_
#define _XAUDIO2_H_
//#include <d3d10.h>
#include <xaudio2.h>

// �T�E���h�t�@�C��
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// �T���v��BGM
	//SOUND_LABEL_SE000,			// �T���v��SE
	//SOUND_LABEL_SE001,			// �T���v��SE0
	//SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(void);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void PauseSound(SOUND_LABEL label);
#endif
