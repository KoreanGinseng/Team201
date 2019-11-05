/**
 * @file Enemy_TESTBOS2.cpp
 * @brief テストボス2
 * @author 大西永遠
 * @date 更新日（11/5）
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

