/**
 * @file Enemy_TESTBOS3.h
 * @brief テストボス3
 * @author 大西永遠
 * @date 更新日（11/19）
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
