#include "Enemy.h"
#include "DxLib.h"

void (Enemy::* Enemy::spFuncTable[])() = {
	&Enemy::Access,
	&Enemy::Attack,
	&Enemy::Pullout,
};

void Enemy::Access()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�ߐ�", true);
}

void Enemy::Attack()
{
	DrawFormatString(0, 25, GetColor(255, 255, 255), "�ˌ�", true);
}

void Enemy::Pullout()
{
	DrawFormatString(0, 50, GetColor(255, 255, 255), "�P��", true);
}

void Enemy::Action()
{
	for (int i = 0; i < 3; i++) 
	{
		(this->*spFuncTable[i])();
	}
}
