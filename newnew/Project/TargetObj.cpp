#include "TargetObj.h"



CTargetObj::CTargetObj()
{
}


CTargetObj::~CTargetObj()
{
	Release();
}

void CTargetObj::Initialize(void)
{
	CCharacter::Initialize();
	m_bShow = true;
}

void CTargetObj::Update(void)
{
	if (m_bSkill)
	{
		m_Anim.Update();
		if (m_Anim.IsEndMotion())
		{
			if (m_Anim.GetMotionNo() == 0)
			{
				m_Anim.ChangeAnim(1);
			}
			else
			{
				m_Anim.ChangeAnim(0);
			}
			m_bSkill = false;
		}
	}
}

bool CTargetObj::OverValue(CRectangle rec, Vector2 & out)
{
	switch (m_Type)
	{
	case OBJECT_ROPE:
		return CollisionRope(rec);
		break;
	case OBJECT_TREE01:
		return CollisionTree(rec, out);
		break;
	case OBJECT_BRIDGE:
		return CollisionBridge(rec, out);
	default:
		break;
	}
	return false;
}

bool CTargetObj::CollisionRope(CRectangle rec)
{
	if (GetRectArray(0).CollisionRect(rec))
	{
		return true;
	}
	return false;
}

bool CTargetObj::CollisionTree(CRectangle rec, Vector2 & out)
{

	return false;
}

bool CTargetObj::CollisionBridge(CRectangle rec, Vector2 & out)
{

	return false;
}
