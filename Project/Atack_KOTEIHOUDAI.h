#pragma once
#include	"_Onishi/EnemyAtack.h"

class CAtack_KOTEIHOUDAI :public CEnemyAtack {
private:
public:
	CAtack_KOTEIHOUDAI();
	~CAtack_KOTEIHOUDAI();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
};