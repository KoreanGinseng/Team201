#pragma once
#include	"EnemyAtack.h"

class CAtack_TERESA :public CEnemyAtack {
private:
public:
	CAtack_TERESA();
	~CAtack_TERESA();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};
