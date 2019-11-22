/**
 * @file Atack_TESTBOS3.h
 * @brief テストボス3の攻撃
 * @author 大西永遠
 * @date 更新日（11/19）
 */

#pragma once
#include	"_Onishi/EnemyAtack.h"
#include	"EnemyShot.h"
#include	"_Onishi/EnemyMove.h"
#include	"_Onishi/Enemy_KURIBO.h"
#include	"CloningSword.h"
#include	"TeleportationSword.h"
#include	<random>
#define ShotCount	2
#define TLeTime 0.2f


class CAtack_TESTBOS3 :public CEnemyAtack {
private:
	float	m_fAtackTimer;
	float	m_fCooltime;
	float	m_ScaleMagnification;
	CEnemyShot* m_ShotArry[CloningCount];
	CRectangle				m_SrcRect;
	CTexture	m_Texture;
	float	m_Radian;
	CEnemy_KURIBO m_KURIBO;
	int m_EneCount;
	int m_SwordCount;
	int m_TleCount;
	float	m_TleTime;
	int	m_Counting;
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
