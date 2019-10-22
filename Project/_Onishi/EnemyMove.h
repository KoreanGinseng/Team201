#pragma once
#include	"Mof.h"
#include	"../GameDefine.h"
#include	"EnemyAtack.h"

#define Timer 5
#define AtackTimer 5
#define CoolTime 5

class CEnemyMove {
protected:
	float		m_fXpos;
	float		m_fYpos;
	float		m_fMoveX;
	float		m_fMoveY;
	float		m_fEnemySpeed;
	bool		m_bAttack;
	bool		m_bReverse;
	CRectangle	m_SrcRect;
	CSpriteMotionController	m_Motion;
private:
	
	float m_fAtackTimer;
	float m_fCooltime;
public:
	CEnemyMove();
	virtual	~CEnemyMove();
	virtual void Initialize() = 0;
	virtual void Update(float Xpos, float Ypos) = 0;
	void	Animation(void);
	Vector2	GetSpd(void) const { return Vector2(m_fMoveX, m_fMoveY); }
	Vector2	GetPos(void) const { return Vector2(m_fXpos, m_fYpos); }
	void	SetPos(const Vector2& pos) { m_fXpos = pos.x; m_fYpos = pos.y; }
	CRectangle	GetSrcRect(void) const { return m_SrcRect; }
	virtual CRectangle	GetRect(void) const = 0;
	void ResetSpd(const WAY& w) { ((w == WAY_X) ? m_fMoveX : m_fMoveY) = 0; }
	void Reverse(void) { m_fMoveX *= -1; m_bReverse = !m_bReverse; }
	void SetReverse(bool flag) { m_bReverse = flag; }
	bool GetAttack(void) const { return m_bAttack; }
	bool GetReverce(void) const { return m_bReverse; }
	void Release(void) { m_Motion.Release(); }
};








