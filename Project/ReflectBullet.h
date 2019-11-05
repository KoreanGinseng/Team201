/**
 * @file ReflectBullet.h
 * @brief ���˒e
 * @author �吼�i��
 * @date �X�V���i11/5�j
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
