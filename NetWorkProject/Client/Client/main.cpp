//マルチスレッドTCP通信　クライアント側
//Dxライブラリ使用
#pragma once
#include "character.h"

//#include "character.h"
#include <memory>
//リスト
std::list<unique_ptr<Base>>datalist;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdLine, _In_ int nShowCmd) 
{
	//windowモードの切り替え
	ChangeWindowMode(TRUE);
	//windowサイズ
	SetGraphMode((int)WIDTH, (int)HEIGHT, 32);
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

	//char image_str[MAX][256];//画像読み込み


	//画像の読み込み
	for (int i = 0; i < MAX; i++)
	{
		img[0] = LoadGraph("image/maid.png");
		img[1] = LoadGraph("image/Bullet.jpg");
	}
	
	//送受信データ処理用
	char StrBuf[256] = { "null" };//256バイトまで


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
	Player* my_Data = new Player(0.0f, 0.0f, name);
	auto add = (unique_ptr<Base>) my_Data;
	datalist.emplace_back(move(add));//リストに追加

	//データ送信用データ
	Player* databox = new Player();

	//全てのプレイヤーデータ(自身を含む)
	SendData* Player_ALL = new SendData();

	//Player* PlayerChar[MAX];//プレイヤーデータ編集用
	//for (int i = 0; i < MAX; i++)//テスト
	//{
	//	PlayerChar[i] = new Player();//プレイヤーデータ作成
	//	auto addAll = (unique_ptr<Base>) PlayerChar[i];//全てのプレイヤーデータをリストに追加
	//	datalist.emplace_back(move(addAll));//リストに追加
	//}
	//
	//
	
	//初回接続(サーバーへ接続）
	NetHandel = ConnectNetWork(IP, Port);//入力したIPと設定したポートを使用

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

			memcpy_s(Player_ALL, sizeof(SendData), StrBuf, sizeof(SendData));//データを受け取る変換

			DrawString(0, 16, "接続完了。何かキーを押してください。",
													GetColor(255, 255, 255));
			ScreenFlip();
			WaitKey();
			break;
		}
		else 
		{
			//接続中
			DrawString(0, 0, "接続確立中・・・", GetColor(255, 255, 255));
		}
		ScreenFlip();
	}

	struct DataBox { //送受信用構造体(テスト)
		Pos pos{ 0.0f,0.0f };    //位置
		Vec vec{ 0.0f,0.0f };    //移動ベクトル
		Pos moupos{ 0, 0 };        //mouseの位置
		Vec mouvec{ 0,0 };       //mouseベクトル
		GraphSize gr_size{ 0,0 };//画像サイズ

	};

	//メインループ(Escキーで終了)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//画面クリア


		//受信データがあるかチェック
		if (GetNetWorkDataLength(NetHandel) != 0) {
			//データを受信した場合
			NetWorkRecv(NetHandel, StrBuf, sizeof(SendData));
			//プレイヤー全体データの更新
			memcpy_s(Player_ALL, sizeof(SendData), StrBuf, sizeof(SendData));//データを受け取る

		}
		else
		{

			//データを受信していない場合
		    databox->vec    = my_Data->vec;  //移動 Vec情報 8

			//弾丸の作成した情報を送るときはベクトルと位置情報、IDがあれば別クライアント側で作成できる
			databox->mouvec = my_Data->mouvec; //mousevec Vec情報 8

			my_Data->mouvec = { 0.0f,0.0f };//ベクトルを初期化

			//データ送信
			NetWorkSend(NetHandel, &databox, sizeof(SendData)); //CharacterData送信
	
		}

		DrawFormatString(0, 256, GetColor(255, 255, 255),
			"mouse_x:%f         mouse_y:%f"    "pos_x:%f          pos_y:%f",
			my_Data->moupos.x,
			my_Data->moupos.y,
			my_Data->pos.x,
			my_Data->pos.y
		);


		//リストのメソッドを実行
		for (auto i = datalist.begin(); i != datalist.end(); i++) {

			(*i)->Action(datalist);//全てのオブジェクトのAction処理
	
			Player* data = ((Player*)(*i).get());//プレイヤーデータ

			if (IsVariable(data->mouvec))//ベクトルが存在するか
			{
				//受信データを元に各プレイヤーのベクトルと位置を参照し弾丸作成(Test)
				Bullet* bullet = new Bullet(data->pos.x, data->pos.y, data->mouvec.x, data->mouvec.y, data->ID);//位置と方向ベクトル
				auto add = (unique_ptr<Bullet>) bullet;
				datalist.emplace_back(move(add));//リストにbulletを追加
			}
				
		}

		for (auto i = datalist.begin(); i != datalist.end(); i++) {

			(*i)->Draw();//全てのオブジェクトの描画処理
	
		}

		//リストから要素を削除(IDが-999の時に削除)
		for (auto i = datalist.begin(); i != datalist.end(); i++)
		{
			if ((*i)->ID == DESTROY_ID)//IDが-999ならdelete
			{
				//リストから削除
				i = datalist.erase(i);
				break;
			}
		}

		/*
		//描画
		//Player_ALLを使って画面の更新
		for (int i = 0; i < MAX; i++) {
			if (Player_ALL->player[i].ID != -1) {//プレイヤーのIDが使用可能か

				//Action実行
				if (IsVariable(Player_ALL->player[i].mouvec))//値が入っているか判定
				{
					Player data = Player_ALL->player[i];//playerDataを仮保存

					//受信データを元に各プレイヤーのベクトルと位置を参照し弾丸作成(Test)
					Bullet* bullet = new Bullet(data.pos.x, data.pos.y, data.mouvec.x, data.mouvec.y, data.ID);//位置と方向ベクトル
					auto add = (unique_ptr<Bullet>) bullet;
					datalist.emplace_back(move(add));//リストにbulletを追加
					
				}
				
				//キャラ
				DrawGraphF(Player_ALL->player[i].pos.x,
					Player_ALL->player[i].pos.y,
					img[i],
					TRUE
				);
				//名前
				DrawStringF(Player_ALL->player[i].pos.x,
					Player_ALL->player[i].pos.y,
					Player_ALL->player[i].name,
					GetColor(255, 255, 255)
				);
			}
		}

		//DrawGraphF(0.0f, 0.0f, img[Player_ALL->data->ID], TRUE);//ID表示
*/	
	

		ScreenFlip();//画面更新

		//例外処理発生でループを抜ける
		if (ProcessMessage() == -1)break;
	}

	DxLib_End();//Dxライブラリの解放
	return 0;
}




