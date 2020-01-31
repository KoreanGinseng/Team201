#include "Treasure.h"



CTreasure::CTreasure(void) :
CTargetObj()
{
	m_bKey = false;
}


CTreasure::~CTreasure(void)
{
}

void CTreasure::Render(const Vector2 & screenPos)
{
	if (!m_bShow)
	{
		return;
	}
	CRectangle r = GetSrcRect();
	if (!m_bReverse)
	{
		r.Left = GetSrcRect().Right;
		r.Right = GetSrcRect().Left;
	}
	m_pTexture->Render(screenPos.x, screenPos.y, r);

	Vector2 scroll = CCamera2D::GetSScroll();

#ifdef _DEBUG
	if (gbDebug)
	{
		CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
		CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
		for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
		{
			CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
				screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
			CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
		}
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 60, "SubStatus : %d", m_SubStatus);
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 90, "SubType   : %d", m_SubType);
	}
#endif // _DEBUG

	CRectangle sRect = GetRect();
	if (m_bTarget)
	{
		CGraphicsUtilities::RenderRect(sRect.Left - scroll.x, sRect.Top - scroll.y, sRect.Right - scroll.x, sRect.Bottom - scroll.y, MOF_COLOR_GREEN);
	}

	if (!m_bKey && m_Motion.GetMotionNo() == 2)
	{
		g_pTextureManager->GetTexture("Key.png")->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 0.3f);
	}
}

void CTreasure::RenderCircle(const Vector2 & screenPos)
{
}

bool CTreasure::OverValue(CRectangle rect, Vector2 & out)
{
	bool re = false;
	if (m_bKey)
	{
		return re;
	}
	CRectangle rec(m_Pos.x, m_Pos.y, m_Pos.x + m_Motion.GetSrcRect().GetWidth(), m_Pos.y + m_Motion.GetSrcRect().GetHeight());
	if (rec.CollisionRect(rect) && m_Motion.GetMotionNo() == 2)
	{
		m_bKey = true;
		CCordinate::SetKey(true);
	}
	return re;
}

CRectangle CTreasure::GetRect(void)
{
	
	return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_Motion.GetSrcRect().GetWidth(), m_Pos.y + m_Motion.GetSrcRect().GetHeight());
}
