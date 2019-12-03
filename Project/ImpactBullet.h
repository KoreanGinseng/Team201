/**
 * @file ImpactBullet.h
 * @brief 衝撃
 * @author 大西永遠
 * @date 更新日（12/3）
 */

#pragma once
#include "EnemyShot.h"
#include "EnemyDefine.h"

class CImpactBullet :public CEnemyShot {
private:
public:
	CImpactBullet();
	~CImpactBullet();
	void Initialize();
	//void Initialize(float posX,float posY);
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	void Fire(float px, float py);
	void Update();
	void Render();
	void Release();
	void CollisionStage(float ox, float oy) {};

};
