/**
 * @file Enemy_TESTBOS2.cpp
 * @brief �e�X�g�{�X2
 * @author �吼�i��
 * @date �X�V���i11/5�j
 */

#pragma once
#include	"_Onishi/EnemyMove.h"

class CEnemy_TESTBOS2 :public CEnemyMove {
private:
	int m_HP;
public:
	CEnemy_TESTBOS2();
	~CEnemy_TESTBOS2();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};

