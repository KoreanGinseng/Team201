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
	float m_EnemySpeed;
	CEnemyAtack	m_bAtack;
	CSpriteMotionController m_Motion;
	CRectangle				m_SrcRect;
	CTexture	m_Texture;
public:
	CEnemyMove();
	~CEnemyMove();
	void Initialize(int Type);
	void Update(float Xpos, float Ypos,int Type);
	void KUpdate(float Xpos,float Ypos);
	void NUpdate(void);
	void TUpdate(float Xpos, float Ypos);
	void BUpdate(float Xpos, float Ypos);
	void KOUpdate(void);
	void CollisionStage(float ox, float oy, int Type);
	void Render(float Xpos, float Ypos,int Type);

	float GetXpos(void) { return m_bXpos; };
	float GetYpos(void) { return m_bYpos; };

};
