/**
 * @file Enemy_KURIBIO.h
 * @brief クリボー
 * @author 大西永遠
 * @date 更新日（11/22）
 */

#pragma once
#include	"EnemyMove.h"
#include	"../EnemyDefine.h"
#define	ENDTIME 3

class CEnemy_KURIBO :public CEnemyMove {
private:
	CEnemyAtack*	m_Atack;
	float m_PosX[CloningCount];
	float m_PosY[CloningCount];
	float m_EndTime;
public:
	CEnemy_KURIBO();
	~CEnemy_KURIBO();
	void Initialize();
	void ClonInitialize(int cnt);
	void Update(float Xpos, float Ypos);
	bool ClonUpdate(int i);
	void CollisionStage(int i);
	void Render(float Xpos, float Ypos);
	void ClonRender(int i);
	void Release();
	bool GetShow() { return m_bEnd; }
	void SetShow(bool bs) { m_bEnd = bs; }
};