#pragma once
#include	"EnemyMove.h"

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
