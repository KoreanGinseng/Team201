#include "Heal.h"



CHeal::CHeal(void) :
CTargetObj()
{
	m_bSelectTarget = false;
	m_Type = OBJECT_HEAL;
	m_CoolTime = 0;
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
		m_CoolTime = 60;
		return true;
	}
	return false;
}

void CHeal::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();
	if (m_CoolTime != 0)
	{
		m_pTexture->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 0.4f, m_Motion.GetSrcRect(), MOF_XRGB(128, 128, 128));
		return;
	}
	m_pTexture->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 0.4f, m_Motion.GetSrcRect());
#ifdef _DEBUG
	if (gbDebug)
	{
		CGraphicsUtilities::RenderRect(GetRect() - scroll, MOF_COLOR_BLUE);
	}
#endif
}

void CHeal::RenderCircle(const Vector2 & screenPos)
{
}

CRectangle CHeal::GetRect(void)
{
	return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_Motion.GetSrcRect().GetWidth() * 0.4f, m_Pos.y + m_Motion.GetSrcRect().GetHeight() * 0.4f);
}
