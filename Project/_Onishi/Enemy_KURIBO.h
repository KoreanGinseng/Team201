/**
 * @file Enemy_KURIBIO.h
 * @brief クリボー
 * @author 大西永遠
 * @date 更新日（10/29）
 */

#pragma once
#include	"EnemyMove.h"

class CEnemy_KURIBO :public CEnemyMove {
private:
	CEnemyAtack*	m_Atack;
public:
	CEnemy_KURIBO();
	~CEnemy_KURIBO();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};