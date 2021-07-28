//=============================================================================
//
// 入力処理 [input.h]
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);

bool GetKeyboardPress(int key);  // GetAsyncKeystateとほぼ同じ、プレス状態を取得する
bool GetKeyboardTrigger(int key);  // 現在のフレームでキーが押されたか、その瞬間が分かる
bool GetKeyboardRepeat(int key);  // リピート＝カーソルの動き
bool GetKeyboardRelease(int key);  // リリース＝キーが離された瞬間を取れる

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