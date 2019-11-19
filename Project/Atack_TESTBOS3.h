/**
 * @file Atack_TESTBOS3.h
 * @brief �e�X�g�{�X3�̍U��
 * @author �吼�i��
 * @date �X�V���i11/19�j
 */

#pragma once
#include	"_Onishi/EnemyAtack.h"
#include	"EnemyShot.h"

#include	"CloningSword.h"
#include	<random>
#define ShotCount	2

class CAtack_TESTBOS3 :public CEnemyAtack {
private:
	float	m_fAtackTimer;
	float	m_fCooltime;
	float	m_ScaleMagnification;
	CEnemyShot* m_ShotArry[CloningCount];
	CRectangle				m_SrcRect;
	CTexture	m_Texture;
	float	m_Radian;
	//CRayBullet	m_RayBullet;
	//CEnemyShot*	m_ShotBounceArry;
public:
	CAtack_TESTBOS3();
	~CAtack_TESTBOS3();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};
