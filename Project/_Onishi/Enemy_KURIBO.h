#pragma once
#include	"EnemyMove.h"

class CEnemy_KURIBO :public CEnemyMove {
private:
public:
	CEnemy_KURIBO();
	~CEnemy_KURIBO();
	void Initialize();
	void Update(float Xpos, float Ypos);
};