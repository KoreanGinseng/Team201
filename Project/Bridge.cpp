#include "Bridge.h"



CBridge::CBridge() :
CTargetObj()
{
	m_Type = OBJECT_BRIDGE;
}


CBridge::~CBridge()
{
}

bool CBridge::OverValue(CRectangle rec, Vector2 & out)
{
	if (m_SubStatus != SUBSTATUS_NOMAL)
	{
		return false;
	}
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
		if (brec.Bottom < cTop)
		{
			return re;
		}
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
