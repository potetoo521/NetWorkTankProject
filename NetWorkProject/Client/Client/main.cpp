//マルチスレッドTCP通信　クライアント側
//Dxライブラリ使用
#pragma once
#include "main.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdLine, _In_ int nShowCmd) 
{
	//windowモードの切り替え
	ChangeWindowMode(TRUE);
	//windowサイズ
	SetGraphMode(WIDTH, HEIGHT, 32);
	//バックグラウンド処理の許可
	SetAlwaysRunFlag(TRUE);
	//多重起動の許可
	SetDoubleStartValidFlag(TRUE);
	//Dxライブラリの初期化
	if (DxLib_Init() == -1) return -1;//失敗したらプログラム終了

	//バックバッファを使う設定
	SetDrawScreen(DX_SCREEN_BACK);
	//winodowの名前
	SetWindowText("クライアント");

	int img[MAX];

	char image_str[MAX][256];//画像読み込み


	//画像の読み込み
	for (int i = 0; i < MAX; i++)
	{
		img[0] = LoadGraph("image/maid.png");
		img[1] = LoadGraph("image/koiking.png");
		img[2] = LoadGraph("image/koiking.png");
		img[3] = LoadGraph("image/hitogage.png");

	}
	
	//送受信データ処理用
	char StrBuf[256] = { "null" };//256バイトまで

	//全てのプレイヤーデータ
	SendData* Player_ALL = new SendData();

	//通信関係
	IPDATA IP;
	//通信用のハンドル
	int NetHandel;
	//ポート
	int Port = 26;
	//通信先のIPアドレスの設定
	IP = IP_set();

	//プレイヤデータ作成
	//名前の入力
	char name[8] = "null";
	ClearDrawScreen();//画面クリア
	DrawString(0, 0, "名前を入力　小文字8文字/全角4文字まで",
		GetColor(255, 255, 255));
	KeyInputString(0, 16, 10, name, FALSE);

	//初回送信データの作成
	Data* my_Data = new Data(0.0f, 0.0f, name);

	//初回接続(サーバーへ接続）
	NetHandel = ConnectNetWork(IP, Port);//入力したIPと設定したポートを使用


	struct MousePos {
		int mouse_x, mouse_y;


	};

	MousePos mop{ 0,0 };


	//接続するまで待機
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//画面クリア

		if (NetHandel != -1) {
			//接続完了
			//サーバーにデータを送信(名前だけ送信)
			NetWorkSend(NetHandel, &my_Data->name, sizeof(my_Data->name));
			//サーバーからの応答待機
			while (!ProcessMessage()) {
				//送受信データを調べる
				if (GetNetWorkDataLength(NetHandel) != 0) break;
			}
			//受信データを変換
			//受信データをメモリからStrBufにコピーして、SendDataに変換
			NetWorkRecv(NetHandel, StrBuf, sizeof(SendData));//コピー
			memcpy_s(Player_ALL, sizeof(SendData), StrBuf, sizeof(SendData));//変換

			DrawString(0, 16, "接続完了。何かキーを押してください。",
													GetColor(255, 255, 255));
			ScreenFlip();
			WaitKey();
			break;
		}
		else {
			//接続中
			DrawString(0, 0, "接続確立中・・・", GetColor(255, 255, 255));
		}
		ScreenFlip();
	}

	//メインループ(Escキーで終了)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//画面クリア

		bool net_Receive = false;

		//受信データがあるかチェック
		if (GetNetWorkDataLength(NetHandel) != 0) {
			//データを受信した場合
			NetWorkRecv(NetHandel, StrBuf, sizeof(SendData));
			//プレイヤー全体データの更新
			memcpy_s(Player_ALL, sizeof(SendData), StrBuf, sizeof(SendData));
			net_Receive = true;
		}

		//Pos mop{ 0.0f,0.0f };
		if(net_Receive==false)
		{
			//データを受信していない場合
			//移動処理
			Vec v{ 0.0f,0.0f };
			if (CheckHitKey(KEY_INPUT_UP)) v.y = -4.0f;
			if (CheckHitKey(KEY_INPUT_DOWN)) v.y = 4.0f;
			if (CheckHitKey(KEY_INPUT_LEFT)) v.x = -4.0f;
			if (CheckHitKey(KEY_INPUT_RIGHT)) v.x = 4.0f;
			//入力があった場合にデータを送信
			if (v.x != 0.0f || v.y != 0.0f) {
				//データ送信
				NetWorkSend(NetHandel, &v, sizeof(Vec));
			}

		
			//弾丸発射目標取得処理
			if (GetMouseInput()&MOUSE_INPUT_LEFT) {
				//押された時
			
				//mouseカーソルの位置をセット
				GetMousePoint(&mop.mouse_x,&mop.mouse_y);


				//データ送信
				NetWorkSend(NetHandel, &mop, sizeof(Pos));

			}
			else {
				//押されていない
			}

		}

		DrawFormatString(0, 16, GetColor(255, 255, 255),
			"mouse_x:%d          mouse_y:%d",
			mop.mouse_x,
			mop.mouse_y
		);


		//描画
		//Player_ALLを使って画面の更新
		for (int i = 0; i < MAX; i++) {
			if (Player_ALL->data[i].ID != -1) {
				//キャラ
				DrawGraphF(Player_ALL->data[i].pos.x,
					Player_ALL->data[i].pos.y,
					img[i],
					TRUE
				);
				//名前
				DrawStringF(Player_ALL->data[i].pos.x,
					Player_ALL->data[i].pos.y,
					Player_ALL->data[i].name,
					GetColor(255, 255, 255)
				);
			}


		}
		DrawGraphF(0.0f, 0.0f, img[Player_ALL->data->ID], TRUE);
	
	

		ScreenFlip();//画面更新

		//例外処理発生でループを抜ける
		if (ProcessMessage() == -1)break;
	}

	DxLib_End();//Dxライブラリの解放
	return 0;
}