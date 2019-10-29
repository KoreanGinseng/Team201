/**
 * @file Enemy_KURIBIO.h
 * @brief �N���{�[
 * @author �吼�i��
 * @date �X�V���i10/29�j
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