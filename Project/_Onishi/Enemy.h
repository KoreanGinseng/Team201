#pragma once
#include	"Mof.h"

#define EnemySpeed 2
#define Timer 5


class CEnemy {
private:
	bool m_bEnd;
	bool m_bRevers;
	float m_bXpos;
	float m_bYpos;
	float m_bTimer;
public:
	CEnemy();
	~CEnemy();
	void Initialize(void);
	void KUpdate(void);
	void NUpdate(void);
	void TUpdate(float Xpos, float Ypos, bool pRevers);
	void Render(void);

};
