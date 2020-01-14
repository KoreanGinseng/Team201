#include "Heal.h"



CHeal::CHeal(void)
{
	m_bSelectTarget = false;
}


CHeal::~CHeal(void)
{
}

void CHeal::Update(void)
{
	if (--m_CoolTime < 0)
	{
		m_CoolTime = 0;
	}
}

bool CHeal::OverValue(CRectangle rect, Vector2 & out)
{
	if (GetRect().CollisionRect(rect) && m_CoolTime == 0)
	{
		m_CoolTime = 600;
		return true;
	}
	return false;
}
