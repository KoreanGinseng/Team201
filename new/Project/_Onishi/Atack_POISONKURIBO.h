/*
 * @file Atack_POISONKURIBO.h
 * @brief �ŃN���{�[�̍U��
 * @author �吼�i��
 * @date �X�V���i11/1�j
 */

#pragma once
#include	"EnemyAtack.h"
#include	"Mof.h"
#include	"EnemyShot.h"
#include	"PoisonBullet.h"
#include	"EnemyDefine.h"

class CAtack_POISONKURIBO :public CEnemyAtack {
private:
	CEnemyShot* m_Shot;
public:
	CAtack_POISONKURIBO();
	~CAtack_POISONKURIBO();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};

