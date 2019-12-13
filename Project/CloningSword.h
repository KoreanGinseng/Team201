/**
 * @file CloningSword.h
 * @brief 分身する剣
 * @author 大西永遠
 * @date 更新日（11/19）
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
