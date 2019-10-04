#pragma once
#include	"Mof.h"
#include	"EnemyAtack.h"

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

enum BAT_ANIM
{
	BAT_MOVE,
	BAT_DOWN,
	BAT_ANIMCOUNT,
};

class CEnemyMove {
protected:
	bool m_bEnd;
	bool m_bRevers;
	float m_fXpos;
	float m_fYpos;
	float m_fMoveX;
	float m_fMoveY;
	float m_fEnemySpeed;

private:
	
	float m_fAtackTimer;
	float m_fCooltime;
	//CEnemyAtack	m_Atack;
	CRectangle	m_SrcRect;
public:
	CEnemyMove();
	virtual	~CEnemyMove();
	virtual void Initialize() = 0;
	virtual void Update(float Xpos, float Ypos) = 0;
	virtual void Render(float Xpos, float Ypos) = 0;
	virtual void Release()=0;
	void CollisionStage(float ox, float oy, int Type);
	float GetXpos(void) { return m_fXpos; };
	float GetYpos(void) { return m_fYpos; };
};








