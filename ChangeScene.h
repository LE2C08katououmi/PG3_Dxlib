#pragma once

class SceneManger {
private:
	SceneManger();
	~SceneManger();
public:
	SceneManger(const SceneManger& obj) = delete;
	SceneManger& operator=(const SceneManger& obj) = delete;
	static SceneManger* GetInstance();
	void ChangeScene(int scene);
};