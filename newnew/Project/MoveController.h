#pragma once
#include	"GameDefine.h"
#include	"Move.h"
#include	"Anim.h"

class CMoveController
{
private:
	CMove*	m_pMove;
public:
	CMoveController();
	~CMoveController();
	void Initialize(void);
	void Update(void);
	template< typename T >
	bool Create( T * p )
	{
		T* move = T();
		if (!move)
		{
			return false;
		}
		*move = *p;
		NewPointerRelease(m_pMove);
		m_pMove = move;
	}
	Vector2 GetMove(void) const { return m_pMove->GetMove(); }
	int GetMotionNo(void) const { return m_pMove->GetMotionNo(); }
	CMove*  GetInstance(void) { return m_pMove; }
	void SetMove(const float& x, const float& y) { SetMove(Vector2(x, y)); }
	void SetMove(const Vector2& move) { m_pMove->SetMove(move); }
	void Remove(void) { NewPointerRelease(m_pMove); }
};

