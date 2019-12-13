/**
 * @file BounceBllet.h
 * @brief 跳弾
 * @author 大西永遠
 * @date 更新日（10/29）
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
