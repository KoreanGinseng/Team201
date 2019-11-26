/**
 * @file Enemy_RIGHTHAND.h
 * @brief �E��
 * @author �吼�i��
 * @date �X�V���i11/19�j
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
};
