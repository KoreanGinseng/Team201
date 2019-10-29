/*
 * @file Atack_KURIBO.h
 * @brief �N���{�[�̍U��
 * @author �吼�i��
 * @date �X�V���i10/29�j
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
