/**
 * @file Enemy_Atack.cpp
 * @brief �G�l�~�[�̍U��
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include	"Mof.h"
#include	"../EnemyDefine.h"

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
	bool m_bShow;

private:

public:
	CEnemyAtack();
	virtual ~CEnemyAtack();
	virtual void Initialize()=0;
	virtual void Update(float EnemyPosX,float EnemyPosY,bool EnemyRevers, float PlayerPosX, float PlayerPosY)=0;

	virtual void Render()=0;
	virtual void Release() = 0;

};
