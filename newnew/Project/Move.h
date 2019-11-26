#pragma once
#include	"Mof.h"
#include	"GameDefine.h"

class CMove
{
protected:
	Vector2	m_Move;
	Vector2	m_Spd;
	int		m_MotionNo;
	bool	m_bReverse;
public:
	CMove();
	~CMove();
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	int  GetMotionNo(void) const { return m_MotionNo; }
	Vector2 GetMove(void) const { return m_Move; }
	Vector2 GetSpd(void) const { return m_Spd; }
	void SetMove(const Vector2& move) { m_Move = move; }
	void SetSpd(const Vector2& spd) { m_Spd = spd; }
	bool GetReverse(void) const { return m_bReverse; }
	void MoveReverse(void);
};

