/**
 * @file EnemyDefine.h
 * @brief “G‚Ì‚Ü‚Æ‚ß
 * @author ‘å¼‰i‰“
 * @date XV“úi11/15j
 */

#pragma once

#pragma region “G‚Ìí—Ş

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

#pragma region “G‚Ì“®‚« 
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
//“G‚Ì‹ßÚUŒ‚”ÍˆÍ
#define Proximity_AtackX 50	
#define Proximity_AtackY 50
//“G‚Ì‹ßÚUŒ‚‚ÌˆÊ’u
#define Atack_Position 50
//“G‚Ì”¼Œa
#define EnemyRadius 10
#pragma endregion

#pragma region “G‚ÌUŒ‚
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
//”š”­ˆÊ’u
#define Exp_Pos 100
#pragma endregion

#pragma region “G‚Ì’e
enum  BULLET
{
	AIM_BULLET,
	BOUNCE_BULLET,
	POISON_BULLET,
	REFLECT_BULLET,
};

//BounceBullet

//#define GRAVITY 0.4f

//“G‚Ì’e‚Ì‘å‚«‚³
#define BulletRadius 5


//’e‚ğÁ‚·ŠÔ
#define EraseTime 4
#pragma endregion

//d—Í‚ÌÅ‘å’l
#define GravityMax	20 

#pragma region ƒfƒoƒbƒN‚Ì“–‚½‚è”»’è‚Ì”ÍˆÍ
//‰E’[
#define Collision_Right 800
//¶’[
#define Collision_Left 200
//‰º
#define Collision_Down 600
#pragma endregion

#pragma region •ªg
#define	CloningCount	5
#define CloningDistance	70
#pragma endregion

#pragma region ƒ{ƒX‚ÌUŒ‚
enum tag_BOS3
{
	PUNCH,
	ACID,
	SCSWORD,
	SHOCKWAVE,
	TLSWORD,
	SCENEMY,
};
#pragma endregion

#pragma region d—Í‚ÌÅ‘å’l
#pragma endregion