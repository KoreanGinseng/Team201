/**
 * @file ImpactBullet.h
 * @brief �Ռ�
 * @author �吼�i��
 * @date �X�V���i12/3�j
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
