#include "Pole.h"



CPole::CPole(void) :
CTargetObj()
{
	m_Type = OBJECT_POLE;
	m_bReverse = true;
}


CPole::~CPole(void)
{
}

void CPole::Initialize(void)
{
}

bool CPole::OverValue(CRectangle rec, Vector2 & out)
{
	bool re = false;
	if (m_SubStatus == SUBSTATUS_TRIP)
	{
		return re;
	}
	CRectangle rect = GetRectArray().GetData(0);
	CRectangle prec = rec;
	if (!rect.CollisionRect(prec))
	{
		return re;
	}
	CRectangle br = prec;
	br.Expansion(-6, 0);
	br.Top = br.Bottom - 1;
	if (rect.CollisionRect(br))
	{
		re = true;
		float result = br.Bottom - rect.Top;
		out.y -= result;
		prec.Top -= result;
		prec.Bottom -= result;
	}
	CRectangle rr = prec;
	rr.Expansion(0, -6);
	rr.Left = rr.Right - 1;
	CRectangle lr = prec;
	lr.Expansion(0, -6);
	lr.Right = lr.Left + 1;
	if (rect.CollisionRect(rr))
	{
		re = true;
		float result = rr.Right - rect.Left;
		out.x -= result;
		prec.Left -= result;
		prec.Right -= result;
	}
	if (rect.CollisionRect(lr))
	{
		re = true;
		float result = rect.Right - lr.Left;
		out.x += result;
		prec.Left += result;
		prec.Right += result;
	}
	return re;
}