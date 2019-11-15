/**
 * @file Atack_TESTBOS2.h
 * @brief �e�X�g�{�X2�̍U��
 * @author �吼�i��
 * @date �X�V���i11/15�j
 */

#pragma once
#include	"_Onishi/EnemyAtack.h"
#include	"EnemyShot.h"
#include	"AimBullet.h"
#include	"BounceBullet.h"
#include	"ReflectBullet.h"
#include	"RayBullet.h"
#define ShotCount	2

class CAtack_TESTBOS2 :public CEnemyAtack {
private:
	float	m_fAtackTimer;
	float	m_fCooltime;
	float	m_ScaleMagnification;
	CEnemyShot* m_ShotReflectArry;
	CRectangle				m_SrcRect;
	CTexture	m_Texture;
	float	m_Radian;
	CRayBullet	m_RayBullet;
	//CEnemyShot*	m_ShotBounceArry;
public:
	CAtack_TESTBOS2();
	~CAtack_TESTBOS2();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};
