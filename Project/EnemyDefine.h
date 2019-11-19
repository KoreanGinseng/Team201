/**
 * @file EnemyDefine.h
 * @brief �G�̂܂Ƃ�
 * @author �吼�i��
 * @date �X�V���i11/15�j
 */

#pragma once

#pragma region �G�̎��

//EnemyMove.h
enum ENEMY
{
	ENEMY_KURIBO,
	ENEMY_NOKONOKO,
	ENEMY_TERESA,
	ENEMY_BAT,
	ENEMY_KOTEIHOUDAI,
	ENEMY_TESTBOS,
	ENEMY_FLOATING,
	ENEMY_POISONKURIBO,
	ENEMY_TESTBOS2,
	ENEMY_RIGHTHAND,
	ENEMY_TESTBOS3
};

//ENEMY_FLOATING.cpp


#pragma endregion

#pragma region �G�̓��� 
enum BAT_ANIM
{
	BAT_MOVE,
	BAT_DOWN,
	BAT_ANIMCOUNT,
};

#define EnemySpeed 2
#define Timer 5
#define AtackTimer 1
#define CoolTime 1
#define GRAVITY 0.4f
//CMovie;
//LPMovie
//�G�̋ߐڍU���͈�
#define Proximity_AtackX 50	
#define Proximity_AtackY 50
//�G�̋ߐڍU���̈ʒu
#define Atack_Position 50
//�G�̔��a
#define EnemyRadius 10
#pragma endregion

#pragma region �G�̍U��
//EnemyAtack
#define Atacktime 3

//Atack_KOTEIHOUDAI
#define		PI	3.14159
#define		BulletSpeed	8
#define		ENEMYSHOT_COUNT	5

//Atack_TESTBOS.cpp
#define BosBulletSpeed 5
#define BosAtackRange	600

//Atack_POISONKURIBO
#define AtackRangeX	200
#define AtackRangeY	100
#define PoisonTime 0.5f
#define PoisonBulletSpeedX 10
#define PoisonBulletSpeedY 0
//�����ʒu
#define Exp_Pos 100
#pragma endregion

#pragma region �G�̒e
enum  BULLET
{
	AIM_BULLET,
	BOUNCE_BULLET,
	POISON_BULLET,
	REFLECT_BULLET,
};

//BounceBullet

//#define GRAVITY 0.4f

//�G�̒e�̑傫��
#define BulletRadius 5


//�e����������
#define EraseTime 4
#pragma endregion

//�d�͂̍ő�l
#define GravityMax	20 

#pragma region �f�o�b�N�̓����蔻��͈̔�
//�E�[
#define Collision_Right 800
//���[
#define Collision_Left 200
//��
#define Collision_Down 600
#pragma endregion

#pragma region ���g
#define	CloningCount	5
#define CloningDistance	70
#pragma endregion

#pragma region �d�͂̍ő�l
#pragma endregion

#pragma region �d�͂̍ő�l
#pragma endregion