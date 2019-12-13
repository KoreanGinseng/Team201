/**
 * @file PoisonBllet.h
 * @brief �Œe
 * @author �吼�i��
 * @date �X�V���i11/1�j
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
