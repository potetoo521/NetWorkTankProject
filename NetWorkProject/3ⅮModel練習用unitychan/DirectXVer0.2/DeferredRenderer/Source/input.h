//=============================================================================
//
// ���͏��� [input.h]
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

bool GetKeyboardPress(int key);  // GetAsyncKeystate�Ƃقړ����A�v���X��Ԃ��擾����
bool GetKeyboardTrigger(int key);  // ���݂̃t���[���ŃL�[�������ꂽ���A���̏u�Ԃ�������
bool GetKeyboardRepeat(int key);  // ���s�[�g���J�[�\���̓���
bool GetKeyboardRelease(int key);  // �����[�X���L�[�������ꂽ�u�Ԃ�����

bool GetMouseLeftPress(void);
bool GetMouseLeftTrigger(void);
bool GetMouseRightPress(void);
bool GetMouseRightTrigger(void);
bool GetMouseCenterPress(void);
bool GetMouseCenterTrigger(void);
long GetMouseAxisX(void);
long GetMouseAxisY(void);
long GetMouseAxisZ(void);
long GetMouseX(void);
long GetMouseY(void);

#endif