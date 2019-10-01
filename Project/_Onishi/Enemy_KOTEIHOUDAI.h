#pragma once
#include	"EnemyMove.h"
class CENEMY_KOTEIHOUDAI :public CEnemyMove {
private:
	float m_fAtackTimer;
	float m_fCooltime;
public:
	CENEMY_KOTEIHOUDAI();
	~CENEMY_KOTEIHOUDAI();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};

