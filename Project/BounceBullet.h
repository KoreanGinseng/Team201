#pragma once
#include	"EnemyShot.h"
#include	"EnemyDefine.h"

class CBounceBullet :public CEnemyShot {
private:
	int m_BounceTimes;
	float m_ExplosionTime;
public:
	CBounceBullet();
	~CBounceBullet();
	void Initialize();
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	void Update();
	void Render();
	void Release();
	void CollisionStage(float ox, float oy);
};
