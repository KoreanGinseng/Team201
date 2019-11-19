/**
 * @file CloningSword.h
 * @brief 分身する剣
 * @author 大西永遠
 * @date 更新日（11/19）
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
