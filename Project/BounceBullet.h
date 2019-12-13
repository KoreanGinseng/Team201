/**
 * @file BounceBllet.h
 * @brief ���e
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include	"EnemyShot.h"
#include	"EnemyDefine.h"
#define	Jumping_Power	-10
#define	Bounce_Times	2
#define ExplosionTime	3
#define Bounce_Factor	0.8f
class CBounceBullet :public CEnemyShot {
private:
	int m_BounceTimes;
	float m_ExplosionTime;
public:
	CBounceBullet();
	~CBounceBullet();
	void Initialize();
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	bool Update();
	void Render();
	void Release();
	void CollisionStage(float ox, float oy);
};
