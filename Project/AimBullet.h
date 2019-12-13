/**
 * @file AimBullet.h
 * @brief �_��
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

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
	bool Update();
	void Render();
	void Release();
	void CollisionStage(float ox, float oy) {};

};
