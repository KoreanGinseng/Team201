/**
 * @file Atack_BAT.h
 * @brief �啂̍U��
 * @author �吼�i��
 * @date �X�V���i10/29�j
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