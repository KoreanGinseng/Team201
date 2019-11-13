/**
 * @file Atack_NOKONOKO.ｈ
 * @brief ノコノコの攻撃
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#pragma once
#include	"EnemyAtack.h"

class CAtack_NOKONOKO :public CEnemyAtack {
private:
public:
	CAtack_NOKONOKO();
	~CAtack_NOKONOKO();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};
