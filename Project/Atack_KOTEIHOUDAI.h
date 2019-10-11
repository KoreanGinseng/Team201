#pragma once
#include	"_Onishi/EnemyAtack.h"
#include	"EnemyDefine.h"

class CAtack_KOTEIHOUDAI :public CEnemyAtack {
private:
	float	m_Radian;
	float	m_fAtackTimer;
	float	m_fCooltime;
	float	m_PlayerPlaceX;
	float	m_PlayerPlaceY;
	float ddx;
	float ddy;
public:
	CAtack_KOTEIHOUDAI();
	~CAtack_KOTEIHOUDAI();
	void Initialize();
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Render();
	void Release();
};