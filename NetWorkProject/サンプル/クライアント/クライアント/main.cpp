#pragma once
#include "main.h"
#include "chara.h"
#include "mouse.h"
#include "net.h"
#include <thread>
#include <iostream>

//リスト(弾用）
list<unique_ptr<Bace>> bace;

//クライアント用プログラム(TCP/IP)
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	//windowモード切替
	ChangeWindowMode(TRUE);
	//windowサイズ
	SetGraphMode(800, 600, 32);
	//バックグラウンド処理の許可
	SetAlwaysRunFlag(TRUE);
	//多重起動の許可
	SetDoubleStartValidFlag(TRUE);

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) return -1;

	//バックバッファを使う設定
	SetDrawScreen(DX_SCREEN_BACK);
	SetWindowText("クライアント:ポート27");

	//プレイヤーオブジェクトの生成
	Player* player[MAX];
	for (int i = 0; i < MAX; i++) {
		player[i]= new Player();
	}
	//マウスカーソル
	Mouse* mouse = new Mouse();

	//他のプレイヤー
	Player_Data o_p;
	for (int i = 0; i < MAX; i++) {
		o_p.p_data[i] = new Player();
	}

	//プレイヤーの位置情報
	Player_Point all_p_pos;
	for (int i = 0; i < MAX; i++) {
		all_p_pos.pos[i].x = 0.0f;
		all_p_pos.pos[i].y = 0.0f;
	}

	//ネットワーク関係
	IPDATA IP;//IPアドレス
	int NetHandle;//ネットワークハンドル
	int port = 26;//ポート

	//IPアドレスセット
	IP = IP_set();

	//サーバーで管理しているID(スレッドNo）
	int server_ID{ -1 };

	//接続処理
	NetHandle = ConnectNetWork(IP, port);


	//初回接続
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//画面クリア
		if (NetHandle != -1) {
			//接続完了
			//サーバーからの応答待機
			while (!ProcessMessage()) {
				//送受信データを調べる
				if (GetNetWorkDataLength(NetHandle) != 0) {
					char str[] = "null";
					//データの受信
					NetWorkRecv(NetHandle, str, sizeof(server_ID));
					//登録IDの取得
					server_ID=atoi(str);
					player[server_ID] = new Player(100.0f,100.0f);
					break;
				}
			}
			DrawString(0, 16, "接続完了。何かキーを押してください。",
				GetColor(255, 255, 255));
			ScreenFlip();
			WaitKey();
			break;
		}
		else {
			//接続中
			DrawString(0, 0, "接続失敗", GetColor(255, 255, 255));
			ScreenFlip();
			WaitKey();
			break;
		}
	}

	//メインループ
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		
		//データを受信した場合
		if (GetNetWorkDataLength(NetHandle) != 0) {
			char str[256] = { "null" };//データ受信用バッファ

			Player_Point send_all_p_pos;//受信データ一時保存用

			NetWorkRecv(NetHandle, str, sizeof(Player_Point));
			memcpy_s(&send_all_p_pos, sizeof(Player_Point), str, sizeof(Player_Point));

			//他のプレイヤーの処理
			for (int i = 0; i < MAX; i++) {
				//IDと配列の添え字を見て、自分以外のオブジェクトを処理
				if (i != server_ID) {
					//他プレイヤーの新規接続
					if (send_all_p_pos.flg[i] != all_p_pos.flg[i]) {
						//他プレイヤーの作成
						player[i] = new Player(0, 0);
						//フラグ更新
						all_p_pos.flg[i] = send_all_p_pos.flg[i];
					}
					player[i]->pos.x = all_p_pos.pos[i].x;
					player[i]->pos.y = all_p_pos.pos[i].y;
				}
			}
			//NetWorkRecv(NetHandle, str, sizeof(Player_Data));
			//memcpy_s(&o_p, sizeof(Player_Data), str, sizeof(Player_Data));
		}

		//処理
		for (auto i = bace.begin(); i != bace.end(); i++)
			(*i)->Action(bace);//リストの処理（弾）

		//プレイヤーとマウスの処理 動きがあったらデータを送信
		//player[server_ID]->Action(bace);
		if (mouse->Action(bace, player[server_ID]->pos.x, player[server_ID]->pos.y) || player[server_ID]->Action(bace)){
			//送信データの作成
			SEND_CLIENT_DATA send;
			send.p_vec = player[server_ID]->vec;
			send.m_vec = mouse->b_v;
			NetWorkSend(NetHandle, &send, sizeof(send));
		}
	

		//描画
		//弾
		for (auto i = bace.begin(); i != bace.end(); i++)  (*i)->Draw();

		//プレイヤー
		player[server_ID]->Draw();

		//マウスカーソル
		mouse->Draw();

		//リストから不要オブジェクトを削除（弾）
		for (auto i = bace.begin(); i != bace.end(); i++) {
			if ((*i)->ID == -1) {
				i = bace.erase(i);
				break;
			}
		}

		//ネットハンドル
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"NetHandle:%d",
			NetHandle
		);

		for (int i = 0; i < MAX; i++) {
			DrawFormatString(0, i * 16 + 32, GetColor(255, 255, 255),
				"x=%4f,y=%4f\nvx=%4f,vy=%4fA",
				all_p_pos.pos[i].x,
				all_p_pos.pos[i].y
			);
		}
		/*
		for (int i = 0; i < MAX; i++) {
			DrawFormatString(0,i*16+32,GetColor(255,255,255),
				"NetHandle:%d IPアドレス:%d.%d.%d.%d　x=%4f,y=%4f",
				o_p.NetHandle[i],
				o_p.IP[i].d1,
				o_p.IP[i].d2,
				o_p.IP[i].d3,
				o_p.IP[i].d4,
				o_p.p_data[i]->pos.x,
				o_p.p_data[i]->pos.y
			);
		}
		*/
		ScreenFlip();
		if (ProcessMessage() == -1) break;
	}

	//ネットワークの切断
	CloseNetWork(NetHandle);

	DxLib_End();

	return 0;
}