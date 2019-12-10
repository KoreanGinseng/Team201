/**
 * @file TeleportationSword.h
 * @brief 瞬間移動剣
 * @author 大西永遠
 * @date 更新日（11/22）
 */

#pragma once
#include "EnemyShot.h"
#include "EnemyDefine.h"
#define STOPTIME 4
#define TLeTime 0.5f

class CTeleportationSword :public CEnemyShot {
private:
	
	float m_PosX[CloningCount];
	float m_PosY[CloningCount];
	float	m_TleTime;
	int m_TleCount;
public:
	CTeleportationSword();
	~CTeleportationSword();
	void Initialize();
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	void CloningFire(float px, float py, float sx, float sy, float pPosx, float pPosy, float rd, float ddx, float ddy);
	void Update();
	void Render();
	void Release();
	void CollisionStage(float ox, float oy);

};
