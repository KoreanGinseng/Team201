/*
 * @file Atack_POISONKURIBO.h
 * @brief 毒クリボーの攻撃
 * @author 大西永遠
 * @date 更新日（11/1）
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

