/**
 * @file Atack_KOTEIHOUDAI.h
 * @brief �Œ�C��̍U��
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include	"EnemyAtack.h"
#include	"EnemyDefine.h"
#include	"EnemyShot.h"
#include	"AimBullet.h"

class CAtack_KOTEIHOUDAI :public CEnemyAtack {
private:
	
	float	m_fAtackTimer;
	float	m_fCooltime;
	float	m_PlayerPlaceX;
	float	m_PlayerPlaceY;
	
	CAimBullet* m_AimBullet;
	CEnemyShot*	m_ShotArry[ENEMYSHOT_COUNT];
	//CBounceBullet* m_BounceBullet;
public:
	CAtack_KOTEIHOUDAI();
	~CAtack_KOTEIHOUDAI();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};