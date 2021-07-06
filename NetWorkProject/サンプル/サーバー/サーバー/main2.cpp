#include "main.h"
#include "chara.h"
#include "net.h"//mainとcharaの後に読み込み
#include <thread>
#include <iostream>

//サーバー
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

	SetWindowText("サーバー:ポート26");

	//管理用プレイヤーデータ
	Player_Data p;

	//送信データ
	SEND_SERVER_DATA s_send;

	//ネットワーク関係
	IPDATA IP;
	int port = 26;//使用ポート


	//接続待機状態にする
	PreparationListenNetWork(port);

	//サブスレッドNo1
	thread* p1 = new thread([&]() {
		int DataLenght = -1;//受信データのサイズ用
		unsigned char scene = CONNECTING;

		//初回接続待機
		while (scene==CONNECTING) {
			if (CheckHitKey(KEY_INPUT_ESCAPE)) scene = -1;

			p.NetHandle[T1] = GetNewAcceptNetWork();
			if (p.NetHandle[T1] != -1) {
				char ID[4];
				sprintf_s(ID, "%d", T1);
				NetWorkSend(p.NetHandle[T1], &ID, sizeof(ID));//IDを送信
				GetNetWorkIP(p.NetHandle[T1], &p.IP[T1]);//IPアドレス取得
				p.flg[T1] = 1;//フラグを更新
				scene = ONLINE;
				break;
			}
			if (ProcessMessage() == -1)break;
		}

		//サブメインループ
		while (scene==ONLINE) {
			if (CheckHitKey(KEY_INPUT_ESCAPE) || p.NetHandle[T1] == -1) scene = -1;

			DataLenght = GetNetWorkDataLength(p.NetHandle[T1]);//データ受信の有無
			if (DataLenght != 0) {
				char str[256] = { "null" };//受信データ保存用
				SEND_CLIENT_DATA c_send;//クライアントからの送信データ
				//データ受信処理
				NetWorkRecv(p.NetHandle[T1], str, sizeof(SEND_CLIENT_DATA));
				memcpy_s(&c_send, sizeof(SEND_CLIENT_DATA), str, sizeof(SEND_CLIENT_DATA));

				//送信データの更新

				//プレイヤーデータの更新
				p.p_data[T1].pos = c_send.pos[T1];				//位置情報更新

				//弾丸との当たり判定実装
				




				//弾の処理
				//弾の移動ベクトルがゼロじゃ無い場合
				if (c_send.m_vec.x != 0.0f || c_send.m_vec.y != 0.0f) {
					//送信する弾の移動ベクトルの情報を更新
					p.tama_vec[T1] = c_send.m_vec;
				}
			}
			if (ProcessMessage() == -1) break;
		}
	});
	
	thread* p2 = new thread([&]() {
		int DataLenght = -1;//受信データのサイズ用
		unsigned char scene = CONNECTING;

		//初回接続待機
		while (scene==CONNECTING) {
			if (CheckHitKey(KEY_INPUT_ESCAPE)) scene = -1;

			p.NetHandle[T2] = GetNewAcceptNetWork();
			if (p.NetHandle[T2] != -1) {
				char ID[4];
				sprintf_s(ID, "%d", T2);
				NetWorkSend(p.NetHandle[T2], &ID, sizeof(ID));//IDを送信
				GetNetWorkIP(p.NetHandle[T2], &p.IP[T2]);//IPアドレス取得
				p.flg[T2] = 1;//フラグを更新
				scene = ONLINE;
				break;
			}
			if (ProcessMessage() == -1)break;
		}

		//サブメインループ
		while (scene==ONLINE) {
			if (CheckHitKey(KEY_INPUT_ESCAPE) || p.NetHandle[T2] == -1) scene = -1;

			DataLenght = GetNetWorkDataLength(p.NetHandle[T2]);//データ受信の有無
			if (DataLenght != 0) {
				char str[256] = { "null" };//受信データ保存用
				SEND_CLIENT_DATA c_send;//クライアントからの送信データ
				//データ受信処理
				NetWorkRecv(p.NetHandle[T2], str, sizeof(SEND_CLIENT_DATA));
				memcpy_s(&c_send, sizeof(SEND_CLIENT_DATA), str, sizeof(SEND_CLIENT_DATA));

				//プレイヤーデータの更新
				//位置情報更新
				p.p_data[T2].pos = c_send.pos[T2];

				//送信データの更新
				//弾の移動ベクトルの処理
				//弾の移動ベクトルがゼロじゃ無い場合
				if (c_send.m_vec.x != 0.0f || c_send.m_vec.y != 0.0f) {
					//送信する弾の移動ベクトルの情報を更新
					p.tama_vec[T2] = c_send.m_vec;
				}
			}
			if (ProcessMessage() == -1) break;
		}
	});

	//メインループ
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		//起動端末のIPアドレス
		GetMyIPAddress(&IP, 1, NULL);

		//状況
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"PCのIPアドレス:%d.%d.%d.%d  接続ポート %d size:%d",
			IP.d1,
			IP.d2,
			IP.d3,
			IP.d4,
			port,
			sizeof(Player_Data)
		);

		//プレイヤー
		for (int i = 0; i < MAX; i++) {
			DrawFormatString(0, i * 16 + 32, GetColor(255, 255, 255),
				"NetHandle:%d IPアドレス:%d.%d.%d.%d　x=%4f,y=%4f flg=%d ",
				p.NetHandle[i],
				p.IP[i].d1,
				p.IP[i].d2,
				p.IP[i].d3,
				p.IP[i].d4,
				p.p_data[i].pos.x,
				p.p_data[i].pos.y,
				p.flg[i]
			);
		}

		//切断した場合
		int LostHandle = GetLostNetWork();
		//切断したプレイヤーのデータを初期化
		for (int i = 0; i < MAX; i++) {
			if (LostHandle == p.NetHandle[i]) {
				p.NetHandle[i] = -1;
				p.IP[i] = { 0,0,0,0 };
				p.p_data[i].pos = { -1.0f,-1.0f };
				p.flg[i] = -1;
			}
		}

		//データの送信
		for (int i = 0; i < MAX; i++) {
			if (p.NetHandle[i] != -1) {
				NetWorkSend(p.NetHandle[i], &p, sizeof(Player_Data));
			}
		}

		//弾の移動ベクトルを初期化
		for (int i = 0; i < MAX; i++) {
			p.tama_vec[i] = { 0.0f,0.0f };
		}

		ScreenFlip();
		if (ProcessMessage() == -1)break;
	}
	p1->join();
	p2->join();
	delete p1;
	delete p2;

	DxLib_End();
	return 0;
}