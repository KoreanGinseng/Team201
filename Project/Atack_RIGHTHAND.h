/**
 * @file Atack_RIGHTHAND.h
 * @brief 右手の攻撃
 * @author 大西永遠
 * @date 更新日（12/3）
 */

#pragma once
#include	"_Onishi/EnemyAtack.h"
#include	"ImpactBullet.h"

class CAtack_RIGHTHAND :public CEnemyAtack {
private:
	bool m_Limit;
	CImpactBullet m_Impact;
public:
	CAtack_RIGHTHAND();
	~CAtack_RIGHTHAND();
	void Initialize();
	void Initialize(float posX, float posY);
	void Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY);
	void Update();
	void Render();
	void Release();
	bool SetLimit(bool bs) { return m_Limit = bs; }
};