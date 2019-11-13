/**
 * @file Atack_BAT.h
 * @brief 蝙蝠の攻撃
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#pragma once
#include	"EnemyAtack.h"

class CAtack_BAT :public CEnemyAtack {
private:
public:
	CAtack_BAT();
	~CAtack_BAT();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};