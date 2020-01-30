#include "Taihou.h"



CTaihou::CTaihou(void) :
CEnemy()
{

	m_Radian = 0.0f;

}


CTaihou::~CTaihou(void)
{
}

void CTaihou::Initialize(void)
{
	m_AimShot.SetTexture(g_pTextureManager->GetTexture("TaihouTama.png"));
	m_AimShot.SetSpd(Vector2(10, 10));
	m_AimShot.SetScale(0.4f);
}

void CTaihou::Update(void)
{
}

void CTaihou::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();
	
	/*float x = m_pTexture->GetWidth() * 0.5f;
	float y = m_pTexture->GetHeight() * 0.5f;*/
	Vector2 center(m_Pos.x + 64, m_Pos.y + 64);
	Vector2 d = Vector2(
		CCordinate::GetPlayerPos().x + 192 * 0.5f,
		CCordinate::GetPlayerPos().y + 192 * 0.5f)
		- m_Pos;
	m_Radian = atan2f(d.y, d.x);
	m_pTexture->RenderScaleRotate(center.x - scroll.x, center.y - scroll.y, 0.2f,m_Radian - MOF_ToRadian(25), m_TutuRect);
	m_pTexture->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 0.2f, m_HontaiRect);
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
