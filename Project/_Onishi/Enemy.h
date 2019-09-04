#pragma once
#include	"Mof.h"

#define EnemySpeed 2
#define Timer 5
#define GRAVITY 0.4f


class CEnemy {
private:
	bool m_bEnd;
	bool m_bRevers;
	float m_bXpos;
	float m_bYpos;
	float m_bTimer;
	float m_bMoveX;
	float m_bMoveY;
public:
	CEnemy();
	~CEnemy();
	void Initialize(void);
	void Update(float Xpos, float Ypos, bool pRevers,int Type);
	void KUpdate(void);
	void NUpdate(void);
	void TUpdate(float Xpos, float Ypos, bool pRevers);
	void CollisionStage(float ox, float oy, int Type);
	void Render(void);

	float GetXpos(void) { return m_bXpos; };
	float GetYpos(void) { return m_bYpos; };

};
