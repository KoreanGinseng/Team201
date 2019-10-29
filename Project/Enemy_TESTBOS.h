/**
 * @file Enemy_TESTBOS.cpp
 * @brief テストボス
 * @author 大西永遠
 * @date 更新日（10/29）
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
