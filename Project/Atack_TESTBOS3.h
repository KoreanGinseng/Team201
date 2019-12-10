/**
 * @file Atack_TESTBOS3.h
 * @brief テストボス3の攻撃
 * @author 大西永遠
 * @date 更新日（12/3）
 */

#pragma once
#include	"_Onishi/EnemyAtack.h"
#include	"EnemyShot.h"
#include	"_Onishi/EnemyMove.h"
#include	"_Onishi/Enemy_KURIBO.h"
#include	"CloningSword.h"
#include	"TeleportationSword.h"
#include	<random>
#include	"Enemy_RIGHTHAND.h"
#include	"Atack_RIGHTHAND.h"

#define ShotCount	2

typedef struct 
{

	Vector2		enemyPos;
	Vector2		playerPos;

}TESTBOSS_INFO;

class CAtack_TESTBOS3 :public CEnemyAtack {
private:

	TESTBOSS_INFO	m_TestInfo;

	float	m_fAtackTimer;
	float	m_fCooltime;
	float	m_ScaleMagnification;

	//ボスの形態
	int		m_Form;
	//ボスの各形態の攻撃パターン数
	const	int		m_Ptn[4] = { 2,3,3,5 };
	//ボスの攻撃パターン
	CDynamicArray<int>		m_AttackPtn;

	CEnemyShot* m_ShotArry;
	CEnemyShot* m_ClonArry[CloningCount];
	CRectangle				m_SrcRect;
	CTexture	m_Texture;
	float	m_Radian;
	CEnemy_KURIBO m_KURIBO;
	int m_EneCount;
	int m_SwordCount;

	int	m_Counting;
	CEnemy_RIGHTHAND m_Hand;
	CAtack_RIGHTHAND m_AtackHand;
	//CRayBullet	m_RayBullet;
	//CEnemyShot*	m_ShotBounceArry;
public:
	CAtack_TESTBOS3();
	~CAtack_TESTBOS3();
	void Initialize();
	void PtnInitialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
	void TLSwordUpdate(float EnemyPosX, float EnemyPosY, float PlayerPosX, float PlayerPosY);
	void ClonSwordUpdate(float EnemyPosX, float EnemyPosY, float PlayerPosX, float PlayerPosY);

	//ボスの全体動作
	void BossBehavior(void);
	//ボスの形態ごとの動作
	void Form1Ptn(void);
	void Form2Ptn(void);
	void Form3Ptn(void);
	void Form4Ptn(void);
	//叩き潰す全形態
	bool CrushHand(void);
	//強酸を吐く1.4形態
	bool AcidBless();
	//分身する剣の攻撃2.4形態
	bool ShadowSwordAttack(void);
	//叩きつけて衝撃波2.4形態
	bool CrushWave(void);
	//瞬間移動する剣3形態
	bool TeleportSword(void);
	//瞬間移動する敵3.4形態
	bool TeleportEnemy(void);
	
};
