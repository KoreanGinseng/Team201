#pragma once
#include	"EnemyMove.h"

class CENEMY_NOKONOKO :public CEnemyMove {
private:
	float m_fTimer;
public:
	CENEMY_NOKONOKO();
	~CENEMY_NOKONOKO();
	void Initialize();
	void Update(float Xpos, float Ypos);
	void Render(float Xpos, float Ypos);
	void Release();
};
