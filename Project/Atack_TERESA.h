/**
 * @file Atack_TERESA.h
 * @brief �e���T�̍U��
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include	"_Onishi/EnemyAtack.h"

class CAtack_TERESA :public CEnemyAtack {
private:
public:
	CAtack_TERESA();
	~CAtack_TERESA();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};