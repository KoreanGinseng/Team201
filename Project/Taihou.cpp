#include "Taihou.h"



CTaihou::CTaihou(void) :
	CEnemy()
{

	m_Radian = 0.0f;
	m_bCollision = false;
}


CTaihou::~CTaihou(void)
{
}

void CTaihou::Initialize(void)
{
	m_AimShot.SetTexture(g_pTextureManager->GetTexture("TaihouTama.png"));
	m_AimShot.SetSpd(Vector2(10, 10));
	m_AimShot.SetScale(0.4f);
	m_OffsetShotWait = 180;
	m_bShow = false;
	m_bDead = false;
	m_pTexture = g_pTextureManager->GetTexture("TAIHOU.png");
}

void CTaihou::Update(void)
{
	if (CCamera2D::GetSScroll().x + g_pGraphics->GetTargetWidth() > m_Pos.x)
	{
		m_bShow = true;
	}
	if (!m_bShow)
	{
		return;
	}
	if (m_ShotWait-- < 0)
	{
		m_ShotWait = m_OffsetShotWait;
		if (!m_AimShot.IsShot())
		{
			Vector2 pos = m_Pos;
			pos += m_HontaiRect.GetCenter() * 0.2f - Vector2(50, 30);
			m_AimShot.Fire(pos);
		}
	}
	if (m_AimShot.IsShot())
	{
		m_AimShot.Update();
	}
}

void CTaihou::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();

	if (m_AimShot.IsShot())
	{
		m_AimShot.Render(Vector2());
	}
	/*float x = m_pTexture->GetWidth() * 0.5f;
	float y = m_pTexture->GetHeight() * 0.5f;*/
	Vector2 center(m_Pos.x + 64, m_Pos.y + 64);
	Vector2 d = Vector2(
		CCordinate::GetPlayerPos().x + 192 * 0.5f,
		CCordinate::GetPlayerPos().y + 192 * 0.5f)
		- m_Pos;
	m_Radian = atan2f(d.y, d.x);
	m_pTexture->RenderScaleRotate(center.x - scroll.x, center.y - scroll.y, 0.2f, m_Radian - MOF_ToRadian(25), m_TutuRect);
	m_pTexture->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 0.2f, m_HontaiRect);
#ifdef _DEBUG
	if (gbDebug)
	{
		CGraphicsUtilities::RenderRect(GetRect() - scroll, MOF_COLOR_BLUE);
	}
#endif // _DEBUG

}

void CTaihou::RenderCircle(const Vector2 & screenPos)
{
}

void CTaihou::CreateMotion(const char * pName)
{
	CAnimationData* pData = g_pAnimManager->GetAnimation("AnimEneTaihou.bin");
	int c = pData->GetAnimCount();
	m_Motion.Create(pData->GetAnim(), c);
	m_HontaiRect = m_Motion.GetSrcRect();
	m_Motion.ChangeMotion(1);
	m_TutuRect = m_Motion.GetSrcRect();
}

CRectangle CTaihou::GetRect(void)
{
	return CRectangle(m_Pos.x , m_Pos.y, m_Pos.x + m_HontaiRect.GetWidth() * 0.2f, m_Pos.y + m_HontaiRect.GetHeight() * 0.2f);
}
