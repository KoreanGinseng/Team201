/**
 * @file EnemyDefine.h
 * @brief 敵のまとめ
 * @author 大西永遠
 * @date 更新日（11/15）
 */

#pragma once

#pragma region 敵の種類

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

#pragma region 敵の動き 
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
//敵の近接攻撃範囲
#define Proximity_AtackX 50	
#define Proximity_AtackY 50
//敵の近接攻撃の位置
#define Atack_Position 50
//敵の半径
#define EnemyRadius 10
#pragma endregion

#pragma region 敵の攻撃
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
//爆発位置
#define Exp_Pos 100
#pragma endregion

#pragma region 敵の弾
enum  BULLET
{
	AIM_BULLET,
	BOUNCE_BULLET,
	POISON_BULLET,
	REFLECT_BULLET,
};

//BounceBullet

//#define GRAVITY 0.4f

//敵の弾の大きさ
#define BulletRadius 5


//弾を消す時間
#define EraseTime 4
#pragma endregion

//重力の最大値
#define GravityMax	20 

#pragma region デバックの当たり判定の範囲
//右端
#define Collision_Right 800
//左端
#define Collision_Left 200
//下
#define Collision_Down 600
#pragma endregion

#pragma region 分身
#define	CloningCount	5
#define CloningDistance	70
#pragma endregion

#pragma region 重力の最大値
#pragma endregion

#pragma region 重力の最大値
#pragma endregion