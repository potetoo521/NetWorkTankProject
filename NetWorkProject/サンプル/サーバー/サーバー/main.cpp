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

	//管理用プレイヤーデータ（構造体）
	Player_Data p;
	for (int i = 0; i < MAX; i++) {
		p.p_data[i] = new Player();
	}

	//プレイヤーの位置情報
	Player_Point all_p_pos;
	for (int i = 0; i < MAX; i++) {
		all_p_pos.pos[i].x = 0.0f;
		all_p_pos.pos[i].y = 0.0f;
	}

	//ネットワーク関係
	IPDATA IP;
	int port = 26;//使用ポート
	
	//接続待機状態にする
	PreparationListenNetWork(port);

	//サブスレッドNo1
	thread* p1 = new thread([&]() {
		IPDATA ip{ 0 };
		int DataLength = -1;
		char StrBuf[512]{ "null" };//送受信データ用
		SEND_CLIENT_DATA scData;
		
		//初回接続待機
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
			//GetNewAcceptNetWork()で接続の有無を確認
			p.NetHandle[T1] = GetNewAcceptNetWork();
			if( p.NetHandle[T1] != -1 ){
				char text[sizeof(int)];
				sprintf_s(text, "%d", T1);
				NetWorkSend(p.NetHandle[T1], &text, sizeof(int));//IDの送信
				GetNetWorkIP(p.NetHandle[T1], &p.IP[T1]);//IPアドレス取得
				all_p_pos.flg[T1] = { 1 };
				break;
			}
			if (ProcessMessage() == -1)break;
		}

		//サブメインループ
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
			if (p.NetHandle[T1] != -1) {
				DataLength = GetNetWorkDataLength(p.NetHandle[T1]);
				if (DataLength != 0) {
					char str[256] = { "null" };
					//データ受信
					NetWorkRecv(p.NetHandle[T1], str, sizeof(SEND_CLIENT_DATA));
					memcpy_s(&scData, sizeof(SEND_CLIENT_DATA), str, sizeof(SEND_CLIENT_DATA));
					//プレイヤーの位置更新
					p.p_data[T1]->pos.x = p.p_data[T1]->pos.x + scData.p_vec.x;
					p.p_data[T1]->pos.y = p.p_data[T1]->pos.y + scData.p_vec.y;

					//位置情報
					all_p_pos.pos[T1].x = p.p_data[T1]->pos.x;
					all_p_pos.pos[T1].y = p.p_data[T1]->pos.y;
					//弾移動ベクトル
					all_p_pos.m_vec[T1].x = scData.m_vec.x;
					all_p_pos.m_vec[T1].x = scData.m_vec.x;
				}

				//データの送信
				if (CheckHitKey(KEY_INPUT_SPACE)) {
					NetWorkSend(p.NetHandle[T1], &all_p_pos, sizeof(Player_Point));
				}
			}
			if (ProcessMessage() == -1)break;
		}
	});

	/*
	thread* p2 = new thread([&]() {
		IPDATA ip{ 0 };
		int DataLength = -1;
		char StrBuf[512]{ "null" };//送受信データ用
		SEND_CLIENT_DATA scData;

		//初回接続待機
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
			//GetNewAcceptNetWork()で接続の有無を確認
			p.NetHandle[T2] = GetNewAcceptNetWork();
			if( p.NetHandle[T2] != -1 ){
				char text[sizeof(int)];
				sprintf_s(text, "%d", T2);
				NetWorkSend(p.NetHandle[T2], &text, sizeof(int));//IDの送信
				GetNetWorkIP(p.NetHandle[T2], &p.IP[T1]);//IPアドレス取得
				break;
			}
			if (ProcessMessage() == -1)break;
		}

		//サブメインループ
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
			if (p.NetHandle[T2] != -1) {
				DataLength = GetNetWorkDataLength(p.NetHandle[T2]);
				if (DataLength != 0) {
					char str[256] = { "null" };
					//データ受信
					NetWorkRecv(p.NetHandle[T2], str, sizeof(SEND_CLIENT_DATA));
					memcpy_s(&scData, sizeof(SEND_CLIENT_DATA), str, sizeof(SEND_CLIENT_DATA));
					//プレイヤーの位置更新
					p.p_data[T2]->pos.x = p.p_data[T2]->pos.x + scData.p_vec.x;
					p.p_data[T2]->pos.y = p.p_data[T2]->pos.y + scData.p_vec.y;

					//位置情報
					all_p_pos.pos[T2].x = p.p_data[T2]->pos.x;
					all_p_pos.pos[T2].y = p.p_data[T2]->pos.y;
					//弾移動ベクトル
					all_p_pos.m_vec[T2].x = scData.m_vec.x;
					all_p_pos.m_vec[T2].x = scData.m_vec.x;
				}

				//データの送信
				if (CheckHitKey(KEY_INPUT_SPACE)) {
					NetWorkSend(p.NetHandle[T2], &all_p_pos, sizeof(Player_Point));
				}
			}
			if (ProcessMessage() == -1)break;
		}
	});
	*/

	//メインループ
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		//起動端末のIPアドレス
		GetMyIPAddress(&IP, 1, NULL);

		//状況
		DrawFormatString(0,0,GetColor(255,255,255),
			"PCのIPアドレス:%d.%d.%d.%d  接続ポート %d",
			IP.d1,
			IP.d2,
			IP.d3,
			IP.d4,
			port
		);

		for (int i = 0; i < MAX; i++) {
			DrawFormatString(0, i * 16 + 32, GetColor(255, 255, 255),
				"NetHandle:%d IPアドレス:%d.%d.%d.%d　x=%4f,y=%4f",
				p.NetHandle[i],
				p.IP[i].d1,
				p.IP[i].d2,
				p.IP[i].d3,
				p.IP[i].d4,
				p.p_data[i]->pos.x,
				p.p_data[i]->pos.y
				);
		}

		//切断した場合の処理
		int LostHandle = GetLostNetWork();
		for (int i = 0; i < MAX; i++) {
			//データの送信
			if (p.NetHandle[i] != -1) {
				//ネットワークハンドルがあれば、データを送信
				NetWorkSend(p.NetHandle[i], &all_p_pos, sizeof(Player_Point));
			}

			//切断したプレイヤーのデータを初期化
			if (LostHandle == p.NetHandle[i]) {
				p.NetHandle[i] = -1;
				p.IP->d1 = 0;
				p.IP->d2 = 0;
				p.IP->d3 = 0;
				p.IP->d4 = 0;
				p.p_data[i]->Init();
			}
		}

		ScreenFlip();
		if (ProcessMessage() == -1)break;
	}
	p1->join();
	//p2->join();
	delete p1;
	//delete p2;

	DxLib_End();
	return 0;
}