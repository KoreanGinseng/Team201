#include "EnemyHand.h"



CEnemyHand::CEnemyHand() :
CEnemy()
{
	m_EnemyType = ENEMY_HAND;
	m_bGravity = false;
	m_bCollision = false;
	m_bFind = false;
	m_bGhost = false;
	m_bReverse = false;
	m_Spd = Vector2(3, 3);
	m_DamageWait = 100;
	m_OffsetWait = 180;
}


CEnemyHand::~CEnemyHand()
{
}

void CEnemyHand::Move(void)
{
	if (CCordinate::GetPlayerPos().x > m_Pos.x && !m_bFind)
	{
		m_DamageWait = 0;
		m_bFind = true;
		m_bGhost = true;
	}
	if (!m_bFind)
	{
		return;
	}
	Vector2 d = m_Pos - CCordinate::GetPlayerPos();
	float c = sqrt(d.x * d.x + d.y * d.y);
	m_Move = -((d / c) * m_Spd);
}

void CEnemyHand::Render(const Vector2 & screenPos)
{
	if (!m_bShow || !m_bGhost)
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

#ifdef _DEBUG
	Vector2 scroll = CCamera2D::GetSScroll();
	CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
	CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
	for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
	{
		CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
			screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
	}
#endif // _DEBUG
}

void CEnemyHand::RenderCircle(const Vector2 & screenPos)
{
	if (!m_bShow || !m_bGhost)
	{
		return;
	}
	CRectangle r = GetSrcRect();
	if (!m_bReverse)
	{
		r.Left = GetSrcRect().Right;
		r.Right = GetSrcRect().Left;
	}
	m_pTexture->Render(screenPos.x, screenPos.y, r, MOF_ARGB(128, 255, 255, 255));
}
