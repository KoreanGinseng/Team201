/**
 * @file Enemy_TESTBOS3.h
 * @brief �e�X�g�{�X3
 * @author �吼�i��
 * @date �X�V���i11/19�j
 */

#pragma once
#include	"_Onishi/EnemyMove.h"

class CEnemy_TESTBOS3 :public CEnemyMove {
private:
	int m_HP;
public:
	CEnemy_TESTBOS3();
	~CEnemy_TESTBOS3();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};
