#pragma once
#include	"EnemyAtack.h"
#include	"EnemyShot.h"

class CAtack_TESTBOS :public CEnemyAtack {
private:
	float	m_fAtackTimer;
	float	m_fCooltime;
	CEnemyShot* m_ShotAimArry[ENEMYSHOT_COUNT];
	CEnemyShot*	m_ShotBounceArry;
public:
	CAtack_TESTBOS();
	~CAtack_TESTBOS();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};
