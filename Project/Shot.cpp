#include "Shot.h"

CDynamicArray<CShot*> CShot::m_ShotLists;

CShot::CShot(void) :
CSubstance(),
m_bShot(false)
{
	m_bSelectTarget = false;
	m_ShotLists.Add(this);
	m_SubType = SUB_ENE;
	m_OffsetWait = 180;
}


CShot::~CShot(void)
{
	for (int i = 0; i < m_ShotLists.GetArrayCount(); i++)
	{
		m_ShotLists[i] = nullptr;
	}
	m_ShotLists.Release();
}

bool CShot::IsShot(void) const
{
	return m_bShot;
}

void CShot::SetShot(const bool & b)
{
	m_bShot = b;
}

void CShot::CollisionPlayer(const Vector2& over)
{
	m_Move.x += over.x * 10.0f;
	//m_Pos.x += over.x;
}

bool CShot::OverValue(CRectangle rect, Vector2 & over)
{
	CRectangle r = GetRect();
	if (!r.CollisionRect(rect))
	{
		return false;
	}
	//CRectangle trect = r;
	//trect.Expansion(-6, 0);
	//if (trect.CollisionRect(rect))
	//{
	//	float h = r.Bottom - rect.Top;
	//	over.y -= h;
	//	r.Top -= h;
	//	r.Bottom -= h;
	//}
	//CRectangle lrect = r;
	//lrect.Expansion(0, -6);
	//if (lrect.CollisionRect(rect))
	//{
	//	float w = rect.Right - r.Left;
	//	over.x += w;
	//	r.Left += w;
	//	r.Right += w;
	//}
	over.x += rect.Right - r.Left;
	return true;
}

CDynamicArray<CShot*>* CShot::GetShotLists(void)
{
	return &m_ShotLists;
}
