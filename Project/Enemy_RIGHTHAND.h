/**
 * @file Enemy_RIGHTHAND.h
 * @brief 右手
 * @author 大西永遠
 * @date 更新日（11/19）
 */

#pragma once
#include "_Onishi/EnemyMove.h"
#define	MAXTOP 200.0f
#define AIMTIME 2

class CEnemy_RIGHTHAND :public CEnemyMove {
private:
	float PlayPosX;
	float m_InitialPositionX;
	float m_InitialPositionY;
	float m_AimTime;
	bool m_MoveEndFlag;
	bool m_Limit;
	bool m_Fire;
public:
	CEnemy_RIGHTHAND();
	~CEnemy_RIGHTHAND();
	void Initialize();
	void Start(float PlayerPosX);
	void Start(float InitialPositionX, float InitialPositionY);
	void Update(float Xpos, float Ypos);
	void CollisionStage();
	void Render(float Xpos, float Ypos);
	void Release();
	bool SetLimit(bool bs) { return m_Limit = bs; }
	bool GetFire() { return m_Fire; };
	bool SetFire(bool bs) { return m_Fire = bs; };
	float GetPosX() { return m_fXpos; };
	float GetPosY() { return m_fYpos; };
};
