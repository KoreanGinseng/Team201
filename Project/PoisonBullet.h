/**
 * @file PoisonBllet.h
 * @brief 毒弾
 * @author 大西永遠
 * @date 更新日（11/1）
 */

#pragma once
#include	"EnemyShot.h"
#include	"EnemyDefine.h"

class CPoisonBullet :public CEnemyShot {
private:
	
	int m_BounceTimes;
	float m_PoisonTime;
public:
	CPoisonBullet();
	~CPoisonBullet();
	void Initialize();
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	bool Update();
	void Render();
	void Release();
	void CollisionStage(float ox, float oy);
};
