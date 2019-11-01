#pragma once
#include	"EnemyAtack.h"

class CAtack_KURIBO :public CEnemyAtack {
private:
public:
	CAtack_KURIBO();
	~CAtack_KURIBO();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};
