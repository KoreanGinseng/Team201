#pragma once
#include	"_Onishi/EnemyAtack.h"

class CAtack_NOKONOKO :public CEnemyAtack {
private:
public:
	CAtack_NOKONOKO();
	~CAtack_NOKONOKO();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};
