/**
 * @file Atack_RIGHTHAND.h
 * @brief 右手の攻撃
 * @author 大西永遠
 * @date 更新日（11/19）
 */

#pragma once
#include	"_Onishi/EnemyAtack.h"

class CAtack_RIGHTHAND :public CEnemyAtack {
private:
public:
	CAtack_RIGHTHAND();
	~CAtack_RIGHTHAND();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};