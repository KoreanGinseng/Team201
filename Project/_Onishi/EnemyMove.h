#pragma once
#include	"Mof.h"

#define EnemySpeed 2
#define Timer 5
#define AtackTimer 5
#define CoolTime 5
#define GRAVITY 0.4f

enum ENEMY
{
	ENEMY_KURIBO,
	ENEMY_NOKONOKO,
	ENEMY_TERESA,
	ENEMY_BAT,
	ENEMY_KOTEIHOUDAI,
};

class CEnemyMove {
private:
	bool m_bEnd;
	bool m_bRevers;
	float m_bXpos;
	float m_bYpos;
	float m_bTimer;
	float m_bAtackTimer;
	float m_bCooltime;
	float m_bMoveX;
	float m_bMoveY;
public:
	CEnemyMove();
	~CEnemyMove();
	void Initialize(void);
	void Update(float Xpos, float Ypos, bool pRevers,int Type);
	void KUpdate(void);
	void NUpdate(void);
	void TUpdate(float Xpos, float Ypos, bool pRevers);
	void BUpdate(float Xpos, float Ypos);
	void KOUpdate(void);
	void CollisionStage(float ox, float oy, int Type);
	void Render(float Xpos, float Ypos,int Type);

	float GetXpos(void) { return m_bXpos; };
	float GetYpos(void) { return m_bYpos; };

};
