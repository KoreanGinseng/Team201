#pragma once
#include "EnemyShot.h"
#include "EnemyDefine.h"

class CAimBullet :public CEnemyShot {
private:
public:
	CAimBullet();
	~CAimBullet();
	void Initialize();
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	void Update();
	void Render();
	void CollisionStage(float ox, float oy) {};
};
