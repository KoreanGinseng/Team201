#include "Tree01.h"



CTree01::CTree01() :
CTargetObj()
{
	m_Type = OBJECT_TREE01;
}


CTree01::~CTree01()
{
}

bool CTree01::OverValue(CRectangle rec, Vector2 & out)
{
	if (m_SubStatus == SUBSTATUS_TRIP)
	{
		return false;
	}
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
