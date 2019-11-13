/**
 * @file Enemy_Atack.cpp
 * @brief �G�l�~�[�̍U��
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include	"../GameDefine.h"
#include	"EnemyDefine.h"

#define Atacktime 3


enum ENEMYATACK {
	ATACK_KURIBO,
	ATACK_NOKONOKO,
	ATACK_TERESA,
	ATACK_BAT,
	ATACK_KOTEIHOUDAI,
};

class CEnemyAtack {
protected:
	float m_fAtackPosX;
	float m_fAtackPosY;
	float m_fTime;
	bool m_bShow;
public:
	CEnemyAtack();
	virtual ~CEnemyAtack();
	virtual void Initialize(void) = 0;
	virtual void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) = 0;
	virtual void Render(void) = 0;
	virtual void Release() = 0;

};

#include	"Atack_BAT.h"
#include	"Atack_KOTEIHOUDAI.h"
#include	"Atack_KURIBO.h"
#include	"Atack_NOKONOKO.h"
#include	"Atack_TERESA.h"
#include	"Atack_TESTBOS.h"