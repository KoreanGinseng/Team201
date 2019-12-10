/**
 * @file Atack_TESTBOS3.h
 * @brief �e�X�g�{�X3�̍U��
 * @author �吼�i��
 * @date �X�V���i12/3�j
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

	//�{�X�̌`��
	int		m_Form;
	//�{�X�̊e�`�Ԃ̍U���p�^�[����
	const	int		m_Ptn[4] = { 2,3,3,5 };
	//�{�X�̍U���p�^�[��
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

	//�{�X�̑S�̓���
	void BossBehavior(void);
	//�{�X�̌`�Ԃ��Ƃ̓���
	void Form1Ptn(void);
	void Form2Ptn(void);
	void Form3Ptn(void);
	void Form4Ptn(void);
	//�@���ׂ��S�`��
	bool CrushHand(void);
	//���_��f��1.4�`��
	bool AcidBless();
	//���g���錕�̍U��2.4�`��
	bool ShadowSwordAttack(void);
	//�@�����ďՌ��g2.4�`��
	bool CrushWave(void);
	//�u�Ԉړ����錕3�`��
	bool TeleportSword(void);
	//�u�Ԉړ�����G3.4�`��
	bool TeleportEnemy(void);
	
};
