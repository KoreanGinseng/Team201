#include "AimShot.h"



CAimShot::CAimShot(void) :
CShot()
{
	m_TexScale = 1.0f;
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
	//m_Spd = Vector2(12, 12);
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
	m_pTexture->RenderScaleRotate(m_Pos.x - scroll.x, m_Pos.y - scroll.y, m_TexScale, m_RotateRad - MOF_ToRadian(180));
#ifdef _DEBUG
	if (gbDebug)
	{
		CRectangle rect = GetRect();
		CGraphicsUtilities::RenderRect(rect - scroll, MOF_COLOR_BLUE);
	}
#endif
}

CRectangle CAimShot::GetRect(void)
{
	return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_pTexture->GetWidth() * m_TexScale, m_Pos.y + m_pTexture->GetHeight() * m_TexScale);
}

float CAimShot::GetRad(void) const
{
	return m_RotateRad;
}

float CAimShot::GetScale(void) const
{
	return m_TexScale;
}

void CAimShot::SetScale(const float & s)
{
	m_TexScale = s;
}

void CAimShot::SetSpd(const Vector2 & spd)
{
	m_Spd = spd;
}
