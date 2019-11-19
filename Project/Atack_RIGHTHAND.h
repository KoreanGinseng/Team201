/**
 * @file Atack_RIGHTHAND.h
 * @brief �E��̍U��
 * @author �吼�i��
 * @date �X�V���i11/19�j
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