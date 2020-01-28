#include "Door.h"



CDoor::CDoor(void) :
CTargetObj()
{
	m_bSelectTarget = false;
	m_Type = OBJECT_DOOR;
}


CDoor::~CDoor(void)
{
}

void CDoor::OpenTheDoor(void)
{
	m_Motion.ChangeMotion(1);
}

bool CDoor::OverValue(CRectangle rect, Vector2 & out)
{
	CRectangle rec(m_Pos.x, m_Pos.y, m_Pos.x + m_Motion.GetSrcRect().GetWidth(), m_Pos.y + m_Motion.GetSrcRect().GetHeight());
	if (rec.CollisionRect(rect))
	{
		return true;
	}
	return false;
}
