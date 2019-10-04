#pragma once
#include	"EnemyMove.h"

class CENEMY_TERESA :public CEnemyMove {
private:
public:
	CENEMY_TERESA();
	~CENEMY_TERESA();
	void Initialize();
	void Update(float Xpos, float Ypos);
};