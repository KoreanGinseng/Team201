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
	m_bReverse = true;
	m_bShow = true;
}

void CTargetObj::Update(void)
{
	/*if (m_bSkill)
	{
		m_Anim.Update();
		if (m_Motion.IsEndMotion())
		{
			if (m_Motion.GetMotionNo() == 0)
			{
				m_Motion.ChangeMotion(1);
			}
			else
			{
				m_Motion.ChangeMotion(0);
			}
			m_bSkill = false;
		}
	}*/
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
	bool re = false;
	CRectangle r = rec;
	CRectangle myRec = GetRectArray(2);
	//BOTTOM
	CRectangle brec = r;
	brec.Top = brec.Bottom - 1;
	//brec.Expansion(-6, 0);
	if (myRec.CollisionRect(brec))
	{
		out.y += myRec.Top - brec.Bottom;
		r.Top += myRec.Top - brec.Bottom;
		r.Bottom += myRec.Top - brec.Bottom;
		re = true;
	}
	myRec = GetRectArray(1);
	//LEFT
	CRectangle lrec = r;
	lrec.Right = r.Left + 1;
	if (myRec.CollisionRect(lrec))
	{
		out.x += myRec.Right - lrec.Left;
		r.Left += myRec.Right - lrec.Left;
		r.Right += myRec.Right - lrec.Left;
		re = true;
	}
	//RIGHT
	CRectangle rrec = r;
	rrec.Left = r.Right - 1;
	if (myRec.CollisionRect(rrec))
	{
		out.x += myRec.Left - rrec.Right;
		r.Left += myRec.Right - rrec.Left;
		r.Right += myRec.Right - rrec.Left;
		re = true;
	}
	return re;
}

bool CTargetObj::CollisionBridge(CRectangle rec, Vector2 & out)
{
	bool re = false;
	CRectangle r = rec;
	CRectangle myRec = GetRectArray(0);
	float sp = 0.1f;
	CRectangle brec = r;
	brec.Top = r.Bottom - 1;
	if (myRec.CollisionRect(brec))
	{
		re = true;
		sp = (myRec.Right - r.Left) / myRec.GetWidth();
		if (sp < 0)
		{
			sp = 0.1f;
		}
		else if (sp > 1.0f)
		{
			sp = 1.0f;
		}
		float cTop = myRec.Bottom - myRec.GetHeight() * sp;
		if (brec.Bottom < cTop)
		{
			return re;
		}
		out.y += cTop - brec.Bottom;
		r.Top += cTop - brec.Bottom;
		r.Bottom += cTop - brec.Bottom;
	}
	myRec = GetRectArray(2);
	brec = r;
	brec.Top = r.Bottom - 1;
	if (myRec.CollisionRect(brec))
	{
		sp = (r.Right - myRec.Left) / myRec.GetWidth();
		if (sp < 0)
		{
			sp = 0.1f;
		}
		else if (sp > 1)
		{
			sp = 1.0f;
		}
		float cTop = myRec.Bottom - myRec.GetHeight() * sp;
		out.y += cTop - r.Bottom;
		r.Top += cTop - brec.Bottom;
		r.Bottom += cTop - brec.Bottom;
		re = true;
	}
	myRec = GetRectArray(1);
	brec = r;
	brec.Top = r.Bottom - 1;
	if (myRec.CollisionRect(brec))
	{
		out.y -= myRec.GetHeight() - (myRec.Bottom - r.Bottom);
		r.Top += myRec.Top - brec.Bottom;
		r.Bottom += myRec.Top - brec.Bottom;
		re = true;
	}
	return re;
}
