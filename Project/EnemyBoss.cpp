#include "EnemyBoss.h"



CEnemyBoss::CEnemyBoss(void) :
CEnemy()
{
	m_Scale = 1.7f;
	m_EnemyType = ENEMY_BOSS_1;
	m_bSelectTarget = false;
}


CEnemyBoss::~CEnemyBoss(void)
{
}

void CEnemyBoss::Render(const Vector2 & screenPos)
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
	m_pTexture->RenderScale(screenPos.x, screenPos.y, m_Scale, r);

#ifdef _DEBUG
	if (g_pInput->IsKeyPush(MOFKEY_4))
	{
		m_bDead = true;
	}
	Vector2 scroll = CCamera2D::GetSScroll();
	//CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
	//CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
	for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
	{
		CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
			screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
	}
#endif // _DEBUG
}

void CEnemyBoss::RenderCircle(const Vector2 & screenPos)
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
	m_pTexture->RenderScale(screenPos.x, screenPos.y, m_Scale, r, MOF_ARGB(128, 255, 255, 255));
}

CRectangle CEnemyBoss::GetSrcAddRect(void)
{
	CRectangle rec(0, 0, GetSrcRect().GetWidth() * m_Scale, GetSrcRect().GetHeight() * m_Scale);
	rec.Left += 200;
	rec.Bottom -= 100;
	return rec;
}


