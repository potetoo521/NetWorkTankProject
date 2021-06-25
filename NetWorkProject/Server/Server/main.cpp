//マルチスレッドTCP通信
//サーバー
//Dxライブラリ使用
#pragma once
#include "main.h"
#include <thread>
#include <iostream>
#include <list>
#include <memory>

//std::list<Data*>datalist;
list<unique_ptr<Base>>datalist;//全てのActorが格納される

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	//windowモード切替
	ChangeWindowMode(TRUE);
	//windowサイズ
	SetGraphMode(WIDTH, HEIGHT, 32);
	//バックグラウンド処理の許可
	SetAlwaysRunFlag(TRUE);
	//多重起動の許可
	SetDoubleStartValidFlag(TRUE);

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) return -1;

	//windowの名前
	SetWindowText("サーバー");

	//バックバッファを使用
	SetDrawScreen(DX_SCREEN_BACK);

	//送受信データ処理用
	char StrBuf[256] = { "NULL" };

	//プレイヤーデータ
	Player* p_data[MAX];


	for (int i = 0; i < MAX; i++) p_data[i] = new Player();

	//送信用データ
	SendData* Send_Data = new SendData();//全てのプレイヤー情報が入る

	//ネットワーク関係
	IPDATA IP;
	int Port = 26;
	int NetHandle[4] = { 0 };

	//////////////////////////////////////////////////

	//接続待機状態にする
	PreparationListenNetWork(Port);

	//サブスレッド
	thread* player[MAX];
	/*
	for (int i = 0; i < MAX; i++)
	{
		player[i] = new thread([&]() {

			IPDATA ip{ 0,0,0,0 };//IPアドレス
			int DataLength = -1;//受信データの大きさ取得用
			int p1_NetHandle = -1;//ネットワークハンドル
			char StrBuf[256]{ "null" };//送受信データ用

			//初回接続処理
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				p1_NetHandle = GetNewAcceptNetWork();//ネットワークハンドル取得
				if (p1_NetHandle != -1) {
					NetHandle[i] = p1_NetHandle;
					break;
				}
			}

			//サブスレッドのメインループ
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				DataLength = GetNetWorkDataLength(p1_NetHandle);
				if (DataLength != 0) {
					//受信データをStrBufに取得
					NetWorkRecv(p1_NetHandle, StrBuf, DataLength);
					//接続してきたマシンのIPアドレスを取得
					GetNetWorkIP(p1_NetHandle, &ip);

					//IPアドレスから初回の接続か確認
					if (p_data[i]->ip.d1 == ip.d1 && p_data[i]->ip.d2 == ip.d2 &&
						p_data[i]->ip.d3 == ip.d3 && p_data[i]->ip.d4 == ip.d4
						) {

						//二回目以降の接続s
						SendData player;//移動ベクトル
						MousePos mop{ 0,0 };   //mouse位置
						bool mou_l;//左クリックの状態

						//受信データを変換
						memcpy_s(&player, sizeof(SendData), StrBuf, sizeof(SendData));
						
						//移動処理
						p_data[i]->pos.x += player.data->pos.x;
						p_data[i]->pos.y += player.data->pos.y;
						/*
						//マウス左クリックされているか
						if (mou_l==true)
						{
							p_data[0]->moupos.x = mop.x;
							p_data[0]->moupos.y = mop.y;


						}


						//弾丸発射処理---
						if (mou_l) {//mouse左クリックされたとき真

							//Playerの位置を取得
							float p_x = p_data[0]->pos.x;
							float p_y = p_data[0]->pos.y;


							//弾丸スポーン処理
							auto a = (unique_ptr<Base>)new BulletData();
							datalist.push_back(move(a));

						}
						//当たり判定
						for (auto i = datalist.begin(); i != datalist.end(); i++) {
							if ((*i)->ID == 1) {
								Pos e_pos = ((BulletData*)(*i).get())->pos;
								if (1) {

									;
								}
							}
						}

						//HPの残存処理

						//送信データの更新
						Send_Data->data[i].pos.x = p_data[i]->pos.x;
						Send_Data->data[i].pos.y = p_data[i]->pos.y;
						//送信データの更新
						Send_Data->data[i].moupos.x = p_data[i]->moupos.x;
						Send_Data->data[i].moupos.y = p_data[i]->moupos.y;



					}
					else {
						//初回の接続
						//IPと名前を登録
						p_data[i]->ip = ip;
						p_data[i]->ID = 0;
						memcpy_s(p_data[i]->name, sizeof(p_data[i]->name),
							StrBuf, sizeof(p_data[i]->name));
						//送信データの更新
						strcpy_s(Send_Data->data[i].name, sizeof(p_data[i]->name), p_data[i]->name);

						Send_Data->data[i].pos = p_data[i]->pos;//位置

						Send_Data->data[i].ip = p_data[i]->ip;//IP

						Send_Data->data[i].ID = p_data[i]->ID;//ID

						//データを送信
						NetWorkSend(p1_NetHandle, Send_Data, sizeof(SendData));
					}
				}
			}
			}
		);

*/

	struct DataBox { //送受信用構造体(テスト)
		Pos pos;
		Vec vec;
		MousePos mou_p;
		bool bullet_f;
	};


		//p_data[0]==PlayerData
	thread* p1 = new thread([&]()
		{
			IPDATA ip{ 0,0,0,0 };//IPアドレス
			int DataLength = -1;//受信データの大きさ取得用
			int p1_NetHandle = -1;//ネットワークハンドル
			char StrBuf[256]{ "null" };//送受信データ用

			//初回接続処理
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				p1_NetHandle = GetNewAcceptNetWork();//ネットワークハンドル取得
				if (p1_NetHandle != -1) {
					NetHandle[0] = p1_NetHandle;
					break;
				}
			}

			//サブスレッドのメインループ
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				DataLength = GetNetWorkDataLength(p1_NetHandle);
				if (DataLength != 0) {
					//受信データをStrBufに取得
					NetWorkRecv(p1_NetHandle, StrBuf, DataLength);
					//接続してきたマシンのIPアドレスを取得
					GetNetWorkIP(p1_NetHandle, &ip);

					//IPアドレスから初回の接続か確認
					if (p_data[0]->ip.d1 == ip.d1 && p_data[0]->ip.d2 == ip.d2 &&
						p_data[0]->ip.d3 == ip.d3 && p_data[0]->ip.d4 == ip.d4
						) {

						//二回目以降の接続
						DataBox databox{0};//使用するデータを格納用

						//受信データを変換
						memcpy_s(&databox, sizeof(DataBox), StrBuf, sizeof(DataBox));

						//移動処理
						p_data[0]->pos.x += databox.vec.x;
						p_data[0]->pos.y += databox.vec.y;

						if (databox.bullet_f==true)
						{
							p_data[0]->moupos.x = databox.mou_p.x;
							p_data[0]->moupos.y = databox.mou_p.y;
						}
						/*
						//マウス左クリックされているか
						if (mou_l==true)
						{
							p_data[0]->moupos.x = mop.x;
							p_data[0]->moupos.y = mop.y;


						}


						//弾丸発射処理---
						if (mou_l) {//mouse左クリックされたとき真

							//Playerの位置を取得
							float p_x = p_data[0]->pos.x;
							float p_y = p_data[0]->pos.y;


							//弾丸スポーン処理
							auto a = (unique_ptr<Base>)new BulletData();
							datalist.push_back(move(a));

						}
						//当たり判定
						for (auto i = datalist.begin(); i != datalist.end(); i++) {
							if ((*i)->ID == 1) {
								Pos e_pos = ((BulletData*)(*i).get())->pos;
								if (1) {

									;
								}
							}
						}*/

						//HPの残存処理






						//送信データの更新
						Send_Data->data[0].pos.x = p_data[0]->pos.x;
						Send_Data->data[0].pos.y = p_data[0]->pos.y;
						//送信データの更新
						Send_Data->data[0].moupos.x = p_data[0]->moupos.x;
						Send_Data->data[0].moupos.y = p_data[0]->moupos.y;



					}
					else {
						//初回の接続
						//IPと名前を登録
						p_data[0]->ip = ip;
						p_data[0]->ID = 0;
						memcpy_s(p_data[0]->name, sizeof(p_data[0]->name),
							StrBuf, sizeof(p_data[0]->name));
						//送信データの更新
						strcpy_s(Send_Data->data[0].name, sizeof(p_data[0]->name), p_data[0]->name);

						Send_Data->data[0].pos = p_data[0]->pos;//位置

						Send_Data->data[0].ip = p_data[0]->ip;//IP

						Send_Data->data[0].ID = p_data[0]->ID;//ID

						//データを送信
						NetWorkSend(p1_NetHandle, Send_Data, sizeof(SendData));
					}
				}
			}
		}
	);

	//p_data[1]
	thread* p2 = new thread([&]()
		{
			IPDATA ip{ 0,0,0,0 };//IPアドレス
			int DataLength = -1;//受信データの大きさ取得用
			int p2_NetHandle = -1;//ネットワークハンドル
			char StrBuf[256]{ "null" };//送受信データ用

			//初回接続処理
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				p2_NetHandle = GetNewAcceptNetWork();//ネットワークハンドル取得
				if (p2_NetHandle != -1) {
					NetHandle[1] = p2_NetHandle;
					break;
				}
			}

			//サブスレッドのメインループ
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				DataLength = GetNetWorkDataLength(p2_NetHandle);
				if (DataLength != 0) {
					//受信データをStrBufに取得
					NetWorkRecv(p2_NetHandle, StrBuf, DataLength);
					//接続してきたマシンのIPアドレスを取得
					GetNetWorkIP(p2_NetHandle, &ip);

					//IPアドレスから初回の接続か確認
					if (p_data[1]->ip.d1 == ip.d1 && p_data[1]->ip.d2 == ip.d2 &&
						p_data[1]->ip.d3 == ip.d3 && p_data[1]->ip.d4 == ip.d4
						) {
						//二回目以降の接続
						Vec v{ 0.0f,0.0f };
						//受信データを変換
						memcpy_s(&v, sizeof(Vec), StrBuf, sizeof(Vec));
						//移動処理
						p_data[1]->pos.x += v.x;
						p_data[1]->pos.y += v.y;

						//送信データの更新
						Send_Data->data[1].pos.x = p_data[1]->pos.x;
						Send_Data->data[1].pos.y = p_data[1]->pos.y;

					}
					else {
						//初回の接続
						//IPと名前を登録
						p_data[1]->ip = ip;
						p_data[1]->ID = 1;
						memcpy_s(p_data[1]->name, sizeof(p_data[1]->name),
							StrBuf, sizeof(p_data[1]->name));
						//送信データの更新
						strcpy_s(Send_Data->data[1].name, sizeof(p_data[1]->name), p_data[1]->name);
						Send_Data->data[1].pos = p_data[1]->pos;//位置
						Send_Data->data[1].ip = p_data[1]->ip;//IP
						Send_Data->data[1].ID = p_data[1]->ID;

						//データを送信
						NetWorkSend(p2_NetHandle, Send_Data, sizeof(SendData));
					}
				}
			}
		}
	);

	//p_da1ta[2]
	thread* p3 = new thread([&]() {});
	//p_data[3]
	thread* p4 = new thread([&]() {});

	//メインループ(サーバー管理画面)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//画面クリア

		//起動端末のIPアドレス
		GetMyIPAddress(&IP, 1, NULL);

		//切断状況をチェック
		int LostHandle = GetLostNetWork();

		for (int i = 0; i < MAX; i++) {

			//データを送信
			if (NetHandle[i] != -1) {
				NetWorkSend(NetHandle[i], Send_Data, sizeof(SendData));
			}

			//切断したプレイヤーを初期化
			if (LostHandle == NetHandle[i]) {
				NetHandle[i] = 0;
				//データの初期化
				p_data[i]->Data_Init();
			}
		}

		//-------------------状況表示--------------------------------
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"PCのIPアドレス:%d.%d.%d.%d 接続ポート:%d",
			IP.d1,
			IP.d2,
			IP.d3,
			IP.d4,
			Port
		);

		for (int i = 0; i < MAX; i++)
		{
			//プレイヤー状況表示
			DrawFormatString(0, i * 48 + 32, GetColor(255, 255, 255),
				"スレッド%d IP:%d.%d.%d.%d  name=%8s  x=%f:y=%f \n mou_x=%f;mou_y=%f",
				p_data[i]->ID,
				p_data[i]->ip.d1,
				p_data[i]->ip.d2,
				p_data[i]->ip.d3,
				p_data[i]->ip.d4,
				p_data[i]->name,
				p_data[i]->pos.x,
				p_data[i]->pos.y,
				p_data[i]->moupos.x,
				p_data[i]->moupos.y
			);
		}

		ScreenFlip();//画面更新
		if ((ProcessMessage() == -1))break;
	}
		p1->join();
		p2->join();
		p3->join();
		p4->join();
		delete p1;
		delete p2;
		delete p3;
		delete p4;

		DxLib_End();
		return 0;
}









