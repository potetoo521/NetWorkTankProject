#include "main.h"

IPDATA IP_set() {
	IPDATA ip;

	while (1) {
		ClearDrawScreen();

		DrawString(0, 0, "ＩＰ入力", GetColor(255, 255, 255));
		ip.d1 = KeyInputNumber(0, 16, 255, 0, FALSE);
		ip.d2 = KeyInputNumber(0, 16, 255, 0, FALSE);
		ip.d3 = KeyInputNumber(0, 16, 255, 0, FALSE);
		ip.d4 = KeyInputNumber(0, 16, 255, 0, FALSE);
		DrawFormatString(0, 16, GetColor(255, 0, 0),
			"IP: %d:%d:%d:%d",
			ip.d1,
			ip.d2,
			ip.d3,
			ip.d4
		);

		DrawString(0, 32, "これで良いですか？", GetColor(255, 255, 255));
		DrawString(0, 48, "0...いいえ 1...はい\n>>", GetColor(255, 255, 255));
		if (KeyInputNumber(16, 64, 1, 0, FALSE)) break;

	}
	return ip;
}

//モードセレクト
int SelectMode() {
	int mode;

	while (1) {
		ClearDrawScreen();

		DrawString(0, 0, "モードの選択  0:サーバー  1:クライアント", GetColor(255, 255, 255));
		mode = KeyInputNumber(0, 16, 1, 0, FALSE);
		if (mode == 0) {
			DrawString(0, 32, "サーバー", GetColor(255, 0, 0));
		}
		else {
			DrawString(0, 32, "クライアント", GetColor(255, 255, 255));
		}
		DrawString(0, 64, "これで良いですか？", GetColor(255, 255, 255));
		DrawString(0, 80, "0...いいえ 1...はい \n>>", GetColor(255, 255, 255));
		if (KeyInputNumber(16, 96, 1, 0, FALSE)) break;

	}
	return mode;
}
