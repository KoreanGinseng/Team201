/*
 * @file Atack_KURIBO.h
 * @brief クリボーの攻撃
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#pragma once
#include	"_Onishi/EnemyAtack.h"
#include	"Mof.h"

class CAtack_KURIBO :public CEnemyAtack {
private:
public:
	CAtack_KURIBO();
	~CAtack_KURIBO();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};
