#include "Enemy.h"



CEnemy::CEnemy()
	: CSubstance()
{

}


CEnemy::~CEnemy()
{
	Release();
}

void CEnemy::Update(void)
{
	m_MvCntrl.Update();
	m_Anim.Update();
	
	m_Pos += m_MvCntrl.GetMove();
}

void CEnemy::CollisionStage(const Vector2 & over)
{
	m_Pos += over;
	if (m_MvCntrl.GetMove().x < 0)
	{
		if (over.x > 0)
		{
			m_MvCntrl.MoveReverse();
		}
	}
	else if (m_MvCntrl.GetMove().x > 0)
	{
		if (over.x < 0)
		{
			m_MvCntrl.MoveReverse();
		}
	}

	if (m_MvCntrl.GetMove().y > 0)
	{
		if (over.y < 0)
		{
			m_MvCntrl.SetMove(Vector2(m_MvCntrl.GetMove().x, 0));
		}
	}
}
