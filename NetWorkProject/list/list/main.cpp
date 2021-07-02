//リスト列
//DxLibrary使用
#pragma once
#include "main.h"
#include "character.h"
//#include <memory>//メモリ解放に必要


//ユニークポインタを使ったリスト
list<unique_ptr<Base>>base;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	//windowモード切り替え
	ChangeWindowMode(TRUE);
	//windowサイズ
	SetGraphMode(WIDTH, HEIGHT, 32,FPS);

	//DxLibraryの初期化
	if (DxLib_Init() == -1)return -1;

	//windowの名前
	SetWindowText("サンプルGame");

	//バックバッファを使用
	SetDrawScreen(DX_SCREEN_BACK);

	//リストへプレイヤーを追加
	auto a = (unique_ptr<Base>)new Player();
	base.emplace_back(move(a));
	
	//auto a = (Base*)new Player();
	//base.push_back(a);


	//メインループ
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//画面クリア

		//リストのメソッドを実行
		for (auto i = base.begin(); i != base.end(); i++)
			(*i)->Action(base);//各オブジェクトの処理
		
		for (auto i = base.begin(); i != base.end(); i++)
			(*i)->Draw();//各オブジェクトの描画処理

		//オブジェクトの削除
		for (auto i = base.begin(); i != base.end(); i++) {
			if (((Base*)(*i).get())->ID == Destroy_ID)
			{
				i = base.erase(i);   //削除
				if (i == base.end())break;//リスト最後尾まで確認
			}
		}

		//リストから要素を削除(IDが-999の時に削除)
		//for (auto i = base.begin(); i !=base.end() ; i++)
		//{
		//	if ((*i)->ID == -999)
		//	{
		//		//リストから削除
		//		delete(*i);
		//		i = base.erase(i);
		//		break;
		//	}
		//}

		//for (auto i = base.begin(); i != base.end(); i++)
		//{
		//	i = base.erase(i);
		//	break;
		//}

		ScreenFlip();//画面更新
		//例外処理
		if (ProcessMessage() == -1)break;


	}

	DxLib_End();

	return 0;
}

