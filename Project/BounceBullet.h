#pragma once
#include	"EnemyShot.h"
#include	"EnemyDefine.h"

class CBounceBullet :public CEnemyShot {
private:
	int m_BounceTimes;
public:
	CBounceBullet();
	~CBounceBullet();
	void Initialize();
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	void Update();
	void Render();
	void CollisionStage(float ox, float oy);
};