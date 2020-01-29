#include "EnemyMash.h"



CEnemyMash::CEnemyMash() :
	CEnemy(),
	m_bDmg(false),
	m_DmgScale(Vector2(1, 1))
{
	m_EnemyType = ENEMY_MASH;
	m_Spd.x = -2.0f;
	m_OffsetWait = 300;
}


CEnemyMash::~CEnemyMash()
{
}

void CEnemyMash::Update(void)
{
	if (m_bAnimStop)
	{
		m_WaitCount--;
		if (m_WaitCount < 0)
		{
			m_WaitCount = 0;
			m_bAnimStop = false;
			m_SubStatus = SUBSTATUS_NOMAL;
		}
	}
	if (m_bDead)
	{
		return;
	}
	if (!m_bShow)
	{
		if (CCordinate::GetMainCameraRect().Right > m_Pos.x)
		{
			m_bShow = true;
		}
		return;
	}

	if (m_bDmg)
	{
		m_Move = Vector2(0, 0);
		m_DmgScale.x += 0.1f;
		m_DmgScale.y -= 0.05f;
		if (m_DmgScale.y < 0)
		{
			m_DmgScale.y = 0;
			m_bDead = true;
			m_bSelectTarget = false;
		}
		return;
	}

	if (!m_bAnimStop)
	{
		Move();
	}
	if (CCordinate::IsCameraCntrl())
	{
		m_Move.x = 0;
		if (!m_bGravity)
		{
			m_Move.y = 0;
		}
	}

	if (m_bGravity)
	{
		m_Move.y += m_Spd.y;
		if (m_Move.y > GRAVITYMAX)
		{
			m_Move.y += GRAVITYMAX;
		}
	}

	m_Pos += m_Move;

	if (!m_bAnimStop)
	{
		Animation();
	}

	if (IsStageOver())
	{
		m_bDead = true;
		m_bShow = false;
	}
	if (m_Move.x < 0)
	{
		m_bReverse = true;
	}
	else if (m_Move.x > 0)
	{
		m_bReverse = false;
	}

	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
}

void CEnemyMash::Render(const Vector2 & screenPos)
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

	if (m_bDmg)
	{
		m_pTexture->RenderScale(screenPos.x + r.GetWidth() / 2, screenPos.y + r.GetHeight(), m_DmgScale.x, m_DmgScale.y, r, TEXTUREALIGNMENT_BOTTOMCENTER);
		//m_pTexture->RenderScale(screenPos.x + r.GetWidth() / 2, screenPos.y + r.GetHeight() / 2, m_DmgScale.x, m_DmgScale.y, r, TEXTUREALIGNMENT_CENTERCENTER);
	}
	else
	{
		m_pTexture->Render(screenPos.x, screenPos.y, r);
	}

#ifdef _DEBUG
	if (gbDebug)
	{
		Vector2 scroll = CCamera2D::GetSScroll();
		CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
		CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
		for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
		{
			CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
				screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
			CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
		}
	}
#endif // _DEBUG
}

void CEnemyMash::RenderCircle(const Vector2 & screenPos)
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
	if (m_bDmg)
	{
		m_pTexture->RenderScale(screenPos.x + r.GetWidth() / 2, screenPos.y + r.GetHeight(), m_DmgScale.x, m_DmgScale.y, r, MOF_ARGB(128, 255, 255, 255), TEXTUREALIGNMENT_BOTTOMCENTER);
		//m_pTexture->RenderScale(screenPos.x + r.GetWidth() / 2, screenPos.y + r.GetHeight() / 2, m_DmgScale.x, m_DmgScale.y, r, TEXTUREALIGNMENT_CENTERCENTER);
	}
	else
	{
		m_pTexture->Render(screenPos.x, screenPos.y, r, MOF_ARGB(128, 255, 255, 255));
	}
}

void CEnemyMash::Move(void)
{
	m_Move.x += m_Spd.x;

	m_Move.x = MOF_CLIPING(m_Move.x, -MASH_MAXSPD, MASH_MAXSPD);
}

void CEnemyMash::Animation(void)
{
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
}

bool CEnemyMash::Dmg(const int & dmg)
{
	m_HP -= dmg;
	if (m_HP <= 0)
	{
		m_HP = 0;
		m_bDmg = true;
	}
	g_pSoundManager->PlaySE("Dmg.mp3");
	return true;
}

CRectangle CEnemyMash::GetRect(void)
{
	CRectangle rec = CCharacter::GetRect();
	rec.Expansion(-30, -10);
	return rec;
}

CRectangle CEnemyMash::GetSrcAddRect(void)
{
	CRectangle rect(0, 0, GetSrcRect().GetWidth(), GetSrcRect().GetHeight());
	rect.Expansion(-30, -10);
	return rect;
}
