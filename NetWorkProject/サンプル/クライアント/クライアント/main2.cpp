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

	//ネットワーク関係
	IPDATA IP;//IPアドレス
	int NetHandle;//ネットワークハンドル
	int port = 26;//ポート

	//IPアドレスセット
	//IP = IP_set();
	IP.d1 = 172;
	IP.d2 = 17;
	IP.d3 = 80;
	IP.d4 = 103;

	//サーバーで管理しているID(スレッドNo）
	int server_ID{ -1 };

	//シーン
	unsigned char scene = CONNECTING;

	//プレイヤーデータ
	Player_Data p;

	//プレイヤーオブジェクトの生成
	Player* player = new Player(0.0f, 0.0f);
	//マウスカーソル
	Mouse* mouse = new Mouse();

	//接続
	NetHandle = ConnectNetWork(IP, port);

	//接続
	while (scene==CONNECTING){
		if (CheckHitKey(KEY_INPUT_ESCAPE)) scene=-1;

		ClearDrawScreen();//画面クリア
		//接続待機
		DrawString(0, 0, "接続中",GetColor(255, 255, 255));
		if (NetHandle != -1) {
			//データが送られてきた場合
			if (GetNetWorkDataLength(NetHandle) != 0) {
				char str[4] = "";
				//データの受信処理
				if (NetWorkRecv(NetHandle, str, sizeof(4)) != -1){ 
					//登録IDの取得
					server_ID = atoi(str);
					p.flg[server_ID] = 1;//管理データのフラグを更新
					scene = ONLINE;//シーンをオンラインに切換			
				}
			}
		}
		else {
			//接続が失敗した場合の処理
			DrawString(0, 16, "接続失敗", GetColor(255, 255, 255));
			WaitKey();
			scene = -1;
		}
		ScreenFlip();
	}

	NetWorkRecvBufferClear(NetHandle);//受信データバッファをクリア

	

	//メインループ
	while (scene == ONLINE) {
		if (CheckHitKey(KEY_INPUT_ESCAPE)) scene = -1;

		ClearDrawScreen();
		int d_length = GetNetWorkDataLength(NetHandle);

		//データを受信した場合
		if (d_length >= sizeof(Player_Data)) {
			Player_Data r_recv;//受信データ保存用
			char str[sizeof(Player_Data)] = " ";
			NetWorkRecv(NetHandle, str, sizeof(Player_Data));
			memcpy_s(&r_recv, sizeof(Player_Data), str, sizeof(Player_Data));

			for (int i = 0; i < MAX; i++) {
				//自分以外のIDを検索
				if (server_ID != i) {

					//現在の管理フラグが-1で、受信したデータが-1じゃ無い場合
					//新規で接続があった事になる
					if (p.flg[i] == -1 && r_recv.flg[i] != -1) {
						//新規接続があった場合
						//他のプレイヤーを追加と作成
						bace.emplace_back((unique_ptr<Bace>)new AnyPlayer(r_recv.flg[i]));
						p.flg[i] = r_recv.flg[i];//フラグを更新
					}

					//他のプレイヤーの座標を更新
					if (p.flg[i] != -1) {
						for (auto a = bace.begin(); a != bace.end(); a++) {//リスト
							if ((*a)->ID == p.flg[i]) {

								//同じIDの座標を更新
								((AnyPlayer*)(*a).get())->pos = r_recv.p_data[i].pos;
								//((AnyPlayer*)(*a).get())->FLAG = r_recv.p_data[i].hit_flag;//ヒットフラグ更新
								
								//((Player*)(*a).get())->FLAG = r_recv.p_data[i].hit_flag;

								//攻撃処理
								//もし、攻撃ベクトルが0.0f以外だったら弾を生成してその方向に飛ばす
								if (r_recv.b_data[i].bullet_vec.x != 0.0f || r_recv.b_data[i].bullet_vec.y != 0.0f) {

									//弾をlistに追加
									bace.emplace_back((unique_ptr<Bace>)new Bullet(r_recv.b_data[i].bullet_vec.x, r_recv.b_data[i].bullet_vec.y,
										r_recv.p_data[i].pos.x, r_recv.p_data[i].pos.y, r_recv.p_data[i].ID));
								}
							}
						}
					}
				}
				//プレイヤー管理データの座標更新
				p.p_data[i].pos = r_recv.p_data[i].pos;
			}
		}

		//プレイヤーとマウス(攻撃）に動きがあったらデータを送信
		if (mouse->Action(bace, player->pos.x, player->pos.y,player->ID) || player->Action(bace)) {
			//送信データの作成
			SEND_CLIENT_DATA send;
			send.pos[server_ID] = player->pos;//位置情報
			send.m_vec = mouse->b_v;//弾の移動ベクトル
			NetWorkSend(NetHandle, &send, sizeof(send));//データ送信
		}

		//-----------------------------
		//for (auto i = bace.begin(); i != bace.end(); i++){ 
		// 
		//	if (((Bullet*)(*i).get())->ID == p.p_data->ID);
		// 
		// NetWorkSend(NetHandle,&send,sizeof(send));//データ送信
        //      	}
		//ヒット判定があった弾丸のIDと発射プレイヤーID

		
		


		//-----------------------------
		

		//リストのAction処理
		for (auto i = bace.begin(); i != bace.end(); i++) (*i)->Action(bace);

		//リストから不要オブジェクトを削除
		for (auto i = bace.begin(); i != bace.end(); i++) {
			if ((*i)->FLAG == false) {
				i = bace.erase(i);
				break;
			}
		}

		//listの描画
		for (auto i = bace.begin(); i != bace.end(); i++)  (*i)->Draw();
		//プレイヤー
		player->Draw();
		//マウス
		mouse->Draw();

		//サーバーのID  ネットハンドル  受信データサイズ
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"ID=%d NetHandle:%d DataLength=%d",
			server_ID,
			NetHandle,
			GetNetWorkDataLength(NetHandle)
		);

		//プレイヤー
		for (int i = 0; i < MAX; i++) {
			DrawFormatString(0, i * 16 + 32, GetColor(255, 255, 255),
				"IPアドレス:%d.%d.%d.%d　x=%4f,y=%4f  flg=%d",
				p.IP[i].d1,
				p.IP[i].d2,
				p.IP[i].d3,
				p.IP[i].d4,
				p.p_data[i].pos.x,
				p.p_data[i].pos.y,
				p.flg[i]
			);
		}

		ScreenFlip();
		if (ProcessMessage() == -1) break;
	}

	//ネットワークの切断
	CloseNetWork(NetHandle);

	DxLib_End();

	return 0;
}