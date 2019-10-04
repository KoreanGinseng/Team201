#pragma once
#include	"EnemyMove.h"

class CENEMY_BAT :public CEnemyMove {
private:
	enum BAT_ANIM
	{
		BAT_MOVE,
		BAT_DOWN,
		BAT_ANIMCOUNT,
	};
public:
	CENEMY_BAT();
	~CENEMY_BAT();
	void Initialize();
	void Update(float Xpos, float Ypos);
};
