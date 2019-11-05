/**
 * @file ReflectBullet.h
 * @brief 反射弾
 * @author 大西永遠
 * @date 更新日（11/5）
 */

#pragma once
#include "EnemyShot.h"
#include "EnemyDefine.h"

class CReflectBullet :public CEnemyShot {
private:
	int m_BounceTimes;
public:
	CReflectBullet();
	~CReflectBullet();
	void Initialize();
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	void Update();
	void Render();
	void Release();
	void CollisionStage(float ox, float oy);

};
