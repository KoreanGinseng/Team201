#pragma once

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
};

enum tag_ATTACK {
	EATTACK_BYTE,
	EATTACK_POISON,
	EATTACK_BULLET,
	EATTACK_BULLETAIM,
};


	#define EnemySpeed 2
	#define Timer 5
	#define AtackTimer 1
	#define CoolTime 1
	#define GRAVITY 0.4f

//EnemyAtack
	#define Atacktime 3

//Atack_KOTEIHOUDAI
	#define		PI	3.14159
	#define		BulletSpeed	8
	#define		ENEMYSHOT_COUNT	50

//BounceBullet
	#define	Jumping_Power	-10
	#define	Bounce_Times	2
	#define ExplosionTime	3
	//#define GRAVITY 0.4f

//Atack_TESTBOS.cpp
#define BosBulletSpeed 5
#define BosAtackRange	600

//ENEMY_FLOATING.cpp
#define	CrawlRange	100
#define CrawlRangeCenter 50
