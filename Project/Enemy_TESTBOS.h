/**
 * @file Enemy_TESTBOS.cpp
 * @brief �e�X�g�{�X
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#pragma once
#include	"_Onishi/EnemyMove.h"

class CEnemy_TESTBOS:public CEnemyMove {
private:
	int m_HP;
public:
	CEnemy_TESTBOS();
	~CEnemy_TESTBOS();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};
