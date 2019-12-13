/**
 * @file CloningSword.h
 * @brief ���g���錕
 * @author �吼�i��
 * @date �X�V���i11/19�j
 */

#pragma once
#include "EnemyShot.h"
#include "EnemyDefine.h"
#define ENDTIME 3

class CCloningSword :public CEnemyShot {
private:
	float m_EndTime;
public:
	CCloningSword();
	~CCloningSword();
	void Initialize();
	void Fire(float px, float py, float sx, float sy, float pPosx, float pPosy);
	void CloningFire(float px, float py, float sx, float sy, float pPosx, float pPosy,float rd,float ddx,float ddy);
	bool Update();
	void Render();
	void Release();
	void CollisionStage(float ox, float oy);

};
