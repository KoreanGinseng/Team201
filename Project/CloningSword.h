/**
 * @file CloningSword.h
 * @brief ���g���錕
 * @author �吼�i��
 * @date �X�V���i11/19�j
 */

#pragma once
#include "EnemyShot.h"
#include "EnemyDefine.h"

class CCloningSword :public CEnemyShot {
private:
public:
	CCloningSword();
	~CCloningSword();
	void Initialize();
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	void CloningFire(float px, float py, float sx, float sy, float pPosx, float pPosy,float rd,float ddx,float ddy);
	void Update();
	void Render();
	void Release();
	void CollisionStage(float ox, float oy);

};
