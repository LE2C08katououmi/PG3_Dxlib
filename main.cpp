#include "DxLib.h"
#include <stdio.h>

int CheckHit(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	int L1 = x1;      // ��
	int R1 = x1 + w1; // �E(��+����)
	int L2 = x2;      // ��
	int R2 = x2 + w2; // �E(��+����)

	if (R1 < L2) return 0;
	if (R2 < L1) return 0;

	int U1 = y1;      // ��
	int D1 = y1 + h1; // ��(��+�c��)
	int U2 = y2;      // ��
	int D2 = y2 + h2; // ��(��+�c��)

	if (D1 < U2) return 0;
	if (D2 < U1) return 0;

	// ����ȊO�̏ꍇ�͓������Ă���
	return 1;
}

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2C_08_�J�g�E_�I�E�~: �^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 600;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾
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

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		// �ŐV�̃L�[�{�[�h�����擾
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
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

		// �`�揈��
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

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
