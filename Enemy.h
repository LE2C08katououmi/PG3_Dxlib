#pragma once
class Enemy
{
protected:
public:
	static int enemyCount;
	Enemy() { enemyCount++; }
	~Enemy() { enemyCount--; }
};