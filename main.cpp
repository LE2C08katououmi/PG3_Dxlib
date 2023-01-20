#include "DxLib.h"
#include <stdio.h>

int CheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	int L1 = x1;      // 左
	int R1 = x1 + w1; // 右(左+横幅)
	int L2 = x2;      // 左
	int R2 = x2 + w2; // 右(左+横幅)

	if (R1 < L2) return 0;
	if (R2 < L1) return 0;

	int U1 = y1;      // 上
	int D1 = y1 + h1; // 下(上+縦幅)
	int U2 = y2;      // 上
	int D2 = y2 + h2; // 下(上+縦幅)

	if (D1 < U2) return 0;
	if (D2 < U1) return 0;

	// それ以外の場合は当たっている
	return 1;
}

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "LE2C_08_カトウ_オウミ: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 600;

// ウィンドウ縦幅
const int WIN_HEIGHT = 600;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// ウィンドウモードに設定
	ChangeWindowMode(TRUE);

	// ウィンドウサイズを手動では変更させず、
	// かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// タイトルを変更
	SetMainWindowText(TITLE);

	// 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// 画面サイズを設定(解像度との比率で設定)
	SetWindowSizeExtendRate(1.0);

	// 画面の背景色を設定する
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlibの初期化
	if (DxLib_Init() == -1) { return -1; }

	// (ダブルバッファ)描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画像などのリソースデータの変数宣言と読み込み


	// ゲームループで使う変数の宣言
	int boxX1 = 0;
	int boxY1 = 180;

	int boxX2 = 360;
	int boxY2 = 0;

	int switchX = 0;
	int switchY = 480;

	int switchBoxX = 240;
	int switchBoxY = 60;

	int switchBoxX2 = 540;
	int switchBoxY2 = 60;

	int num = 0;
	int hit = 0;

	int block = LoadGraph("block.png");
	const int BLOCK_SIZE = 30;

	int map1[20][20] = {
		0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,1,1,0,0,1,3,3,1,1,1,1,1,1,1,1,3,3,
		0,0,1,1,1,0,0,1,3,3,1,1,1,1,1,1,1,1,3,3,
		0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,4,4,0,0,
		0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,4,4,0,0,
		0,0,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1,1,0,0,
		0,0,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1,1,0,0,
		0,0,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1,1,0,0,
		0,0,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1,1,0,0,
		0,0,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1,1,0,0,
		0,0,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,0,0,1,1,5,5,1,1,1,1,0,0,
		2,2,0,0,0,0,0,0,0,0,1,1,5,5,1,1,1,1,0,0,
		2,2,0,0,0,0,0,0,0,0,1,1,6,6,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,0,0,1,1,6,6,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,
	};

	int map2[20][20] = {
		0,0,0,7,7,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,
0,0,0,7,7,0,0,0,0,0,1,1,0,0,0,0,0,2,2,0,
0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,2,2,0,
0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,
0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,
1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,1,3,3,3,1,1,1,1,0,0,0,0,0,0,
0,0,0,1,1,1,1,3,3,3,1,1,1,1,7,7,1,1,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,1,7,7,1,1,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
1,4,4,0,0,1,1,0,0,0,5,5,0,0,0,0,0,0,0,0,
1,4,4,0,0,1,1,0,0,0,5,5,0,0,0,0,0,0,0,0,
1,0,0,0,0,5,5,0,0,0,1,1,0,0,0,0,1,1,0,0,
1,0,0,0,0,5,5,0,0,0,1,1,0,0,0,0,1,1,0,0,
1,0,0,0,0,5,5,0,0,0,1,1,0,0,0,0,1,1,0,0,
1,6,6,0,0,5,5,0,0,0,1,1,0,0,0,0,1,1,0,0,
1,6,6,0,0,5,5,0,0,0,1,1,0,0,0,0,1,1,0,0,
	};

	// 最新のキーボード情報用
	char keys[256] = { 0 };

	// 1ループ(フレーム)前のキーボード情報
	char oldkeys[256] = { 0 };

	// ゲームループ
	while (true) {
		// 最新のキーボード情報だったものは1フレーム前のキーボード情報として保存
		// 最新のキーボード情報を取得
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		GetHitKeyStateAll(keys);

		// 画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		// 更新処理
		switch (num)
		{
			case 0:

				if (boxX1 <= -60 || boxY1 <= -60)
				{
					boxX1 = 0;
					boxY1 = 180;
					boxX2 = 360;
					boxY2 = 0;
				}

				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					num = 1;
				}

				break;

			case 1:

				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					num = 2;
				}

				break;

			case 2:

				if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
				{
					num = 0;
				}

				break;
		}

		if (keys[KEY_INPUT_W] == 1)
		{
			boxY1 -= 10;
			boxY2 -= 10;
		}

		if (keys[KEY_INPUT_A] == 1)
		{
			boxX1 -= 10;
			boxX2 -= 10;
		}

		if (keys[KEY_INPUT_S] == 1)
		{
			boxY1 += 10;
			boxY2 += 10;
		}

		if (keys[KEY_INPUT_D] == 1)
		{
			boxX1 += 10;
			boxX2 += 10;
		}

		hit = CheckHit(switchX, switchY, 60, 60, boxX1, boxY1, 60, 60);

		// 描画処理
		DrawBox(boxX1, boxY1, boxX1 + 60, boxY1 + 60, GetColor(255, 255, 255), true);
		DrawBox(boxX2, boxY2, boxX2 + 60, boxY2 + 60, GetColor(255, 255, 255), true);

		DrawBox(switchX, switchY, switchX + 60, switchY + 60, GetColor(255, 255, 100), true);

		if (hit == 0) 
		{
			DrawBox(switchBoxX, switchBoxY, switchBoxX + 60, switchBoxY + 60, GetColor(255, 255, 0), true);
			DrawBox(switchBoxX2, switchBoxY2, switchBoxX2 + 60, switchBoxY2 + 60, GetColor(255, 255, 0), true);
		}

		if (num == 0)
		{
			for (int j = 0; j < 20; j++)
			{
				for (int i = 0; i < 20; i++)
				{
					if (map1[j][i] == 1)
					{
						DrawGraph(i * BLOCK_SIZE, j * BLOCK_SIZE, block, true);
					}
				}
			}
		}

		if (num == 1)
		{
			for (int j = 0; j < 20; j++)
			{
				for (int i = 0; i < 20; i++)
				{
					if (map2[j][i] == 1)
					{
						DrawGraph(i * BLOCK_SIZE, j * BLOCK_SIZE, block, true);
					}
				}
			}
		}

		//---------  ここまでにプログラムを記述  ---------//
		// (ダブルバッファ)裏面
		ScreenFlip();

		// 20ミリ秒待機(疑似60FPS)
		WaitTimer(20);

		// Windowsシステムからくる情報を処理する
		if (ProcessMessage() == -1) {
			break;
		}

		// ESCキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dxライブラリ終了処理
	DxLib_End();

	// 正常終了
	return 0;
}
