#include "ChangeScene.h"
#include "DxLib.h"
#include <stdio.h>

SceneManger::SceneManger() {}
SceneManger::~SceneManger() {}

SceneManger* SceneManger::GetInstance()
{
	static SceneManger instance;

	return &instance;
}

void SceneManger::ChangeScene(int sceneNo)
{
	if (sceneNo == 0) {
		DrawBox(0, 0, 600, 400, GetColor(255, 255, 255), true);
	}

	if (sceneNo == 1) {
		DrawBox(0, 0, 600, 400, GetColor(255, 0, 255), true);
	}

	if (sceneNo == 2) {
		DrawBox(0, 0, 600, 400, GetColor(255, 255, 0), true);
	}

	if (sceneNo == 3) {
		DrawBox(0, 0, 600, 400, GetColor(0, 255, 255), true);
	}
}