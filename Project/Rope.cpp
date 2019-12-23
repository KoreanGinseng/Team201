#include "Rope.h"



CRope::CRope() :
CTargetObj()
{
	m_Type = OBJECT_ROPE;
}


CRope::~CRope()
{
}

void CRope::Initialize(void)
{
	CTargetObj::Initialize();
	m_Pos.y += 32;
}

bool CRope::OverValue(CRectangle rec, Vector2 & out)
{
	if (GetRectArray(0).CollisionRect(rec))
	{
		return true;
	}
	return false;
}
