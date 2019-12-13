/**
 * @file AimBullet.h
 * @brief 狙撃
 * @author 大西永遠
 * @date 更新日（10/29）
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
