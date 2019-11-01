#pragma once
#include	"EnemyAtack.h"

class CAtack_BAT :public CEnemyAtack {
private:
public:
	CAtack_BAT();
	~CAtack_BAT();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};