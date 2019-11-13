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
	void Remove(void) { NewPointerRelease(m_pMove); }
};

