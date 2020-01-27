#include "RayShot.h"



CRayShot::CRayShot(void) :
	CShot()
{
	m_ShotType = SHOT_RAY;
}


CRayShot::~CRayShot(void)
{
	m_pTexture = nullptr;
}

void CRayShot::Fire(const Vector2 & startPos)
{
	m_bShot = true;
	m_Pos = startPos;
	m_RefrectPos[0] = m_Pos;
	Vector2 d = Vector2(
		CCordinate::GetPlayerPos().x + 192 * 0.5f,
		CCordinate::GetPlayerPos().y + 192 * 0.5f)
		- m_Pos;
	float fd = sqrtf(d.x * d.x + d.y * d.y);
	Vector2 dd = d / fd;
	m_Spd = Vector2(12, 12);
	m_Move = dd * m_Spd;
	m_RefrectRad[0] = atan2f(d.y, d.x);
	m_Timer = 180;
	m_bReverse = false;
}

void CRayShot::Initialize(void)
{
	m_bShot = false;
	m_pTexture = g_pTextureManager->GetTexture("RayShot2.png");
	for (auto& itr : m_RefrectPos)
	{
		itr = Vector2(0, 0);
	}
}

void CRayShot::Update(void)
{
	m_Pos += m_Move;
	if (m_Pos.x < CCamera2D::GetSScroll().x || m_Timer-- < 0)
	{
		m_bShot = false;
	}
}

void CRayShot::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();
	CRectangle rect(0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight());
	if (m_bReverse)
	{
		float tmp = rect.Left;
		rect.Left = rect.Right;
		rect.Right = tmp;
	}
	m_pTexture->RenderScaleRotate(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 0.5f, 1.0f, m_RefrectRad[0], rect);
#ifdef _DEBUG
	if (gbDebug)
	{
		CCircle cir = GetShotCircle();
		CGraphicsUtilities::RenderFillCircle(cir.x - scroll.x, cir.y - scroll.y, cir.r, MOF_COLOR_BLUE);
	}
#endif
}

CCircle CRayShot::GetShotCircle(void) const
{
	Vector2 pos = Vector2(
		m_Pos.x + m_pTexture->GetWidth() * cosf(m_RefrectRad[0]) * 0.5f/* + m_bReverse ? m_pTexture->GetWidth() * cosf(m_RefrectRad[0]) : 0*/,
		m_Pos.y + m_pTexture->GetWidth() * 0.5f * sinf(m_RefrectRad[0]) - m_pTexture->GetHeight() * 0.5f
	);
	return CCircle(pos, m_pTexture->GetHeight() * 0.5f);
}

void CRayShot::Refrect(void)
{
	m_Move.x *= -1;
	m_RefrectRad[0] += MOF_ToRadian(180) - m_RefrectRad[0];
}

void CRayShot::FireStop(void)
{
	m_bShot = false;
	m_bReverse = true;
}
