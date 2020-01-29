#include "AimShot.h"



CAimShot::CAimShot(void) :
CShot()
{
}


CAimShot::~CAimShot(void)
{
}

void CAimShot::Fire(const Vector2 & startPos)
{
	m_bShot = true;
	m_Pos = startPos;
	Vector2 d = Vector2(
		CCordinate::GetPlayerPos().x + 192 * 0.5f,
		CCordinate::GetPlayerPos().y + 192 * 0.5f)
		- m_Pos;
	float fd = sqrtf(d.x * d.x + d.y * d.y);
	Vector2 dd = d / fd;
	m_Spd = Vector2(12, 12);
	m_Move = dd * m_Spd;
	m_RotateRad = atan2f(d.y, d.x);
}

void CAimShot::Initialize(void)
{
	m_bShot = false;
}

void CAimShot::Update(void)
{
	if (!m_bShot)
	{
		return;
	}
	m_Pos += m_Move;
}

void CAimShot::Render(const Vector2 & screenPos)
{
	if (!m_bShot)
	{
		return;
	}
	Vector2 scroll = CCamera2D::GetSScroll();
	m_pTexture->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 0.5f);
}

CRectangle CAimShot::GetRect(void)
{
	return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_pTexture->GetWidth(), m_Pos.y + m_pTexture->GetHeight());
}
