#include "EnemyBoss.h"
#include "Boss1Shot.h"


CEnemyBoss::CEnemyBoss(void) :
CEnemy()
{
	m_Scale = 1.7f;
	m_EnemyType = ENEMY_BOSS_1;
	m_bSelectTarget = false;
	m_HP = 2;
}


CEnemyBoss::~CEnemyBoss(void)
{
}

void CEnemyBoss::Initialize(void)
{
	CEnemy::Initialize();
	m_HP = 2;
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
	if (m_DamageWait % 2 != 1)
	{
		m_pTexture->RenderScale(screenPos.x, screenPos.y, m_Scale, r);
	}
	
	Vector2 scroll = CCamera2D::GetSScroll();
	
	for (int i = 0; i < m_BoundShotArray.GetArrayCount(); i++)
	{
		Vector2 sp = ScreenTransration(scroll, m_BoundShotArray[i]->GetPos());
		m_BoundShotArray[i]->Render(sp);
	}
#ifdef _DEBUG
	if (gbDebug)
	{
		if (g_pInput->IsKeyPush(MOFKEY_4))
		{
			m_bDead = true;
		}
		//CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
		//CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
		for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
		{
			CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
				screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
			CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
		}
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

CDynamicArray<CShot*>* CEnemyBoss::GetAnimShotArray(void)
{
	return &m_AnimShotArray;
}

CDynamicArray<CShot*>* CEnemyBoss::GetBoundShotArray(void)
{
	return &m_BoundShotArray;
}

void CEnemyBoss::Move(void)
{
	if (m_Motion.GetMotionNo() != 2)
	{
		if (m_BoundShotArray.GetArrayCount() < 1)
		{
			m_Motion.ChangeMotion(1);
			if (!m_bCameraMove)
			{
				m_BoundShotArray.Add(NEW CBoss1Shot1());
				m_BoundShotArray[0]->Initialize();
				m_BoundShotArray[0]->Fire(m_Pos);
			}
		}
		else if(!m_BoundShotArray[0]->IsShot())
		{
			m_Motion.ChangeMotion(1);
			m_BoundShotArray[0]->Initialize();
			m_BoundShotArray[0]->Fire(m_Pos);
		}
	}

	for (int i = 0; i < m_BoundShotArray.GetArrayCount(); i++)
	{
		m_BoundShotArray[i]->Update();
	}
	if (m_Motion.GetMotionNo() == 1 && m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(0);
	}
	if (m_Motion.GetMotionNo() == 2 && m_Motion.IsEndMotion())
	{
		m_bDead = true;
	}
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
}

void CEnemyBoss::Animation(void)
{
	//m_Motion.AddTimer(CUtilities::GetFrameSecond());
}

bool CEnemyBoss::Dmg(const int & dmg)
{
	if (m_DamageWait > 0)
	{
		return false;
	}
	m_HP -= dmg;
	m_DamageWait = 60;
	if (m_HP < 0)
	{
		m_Motion.ChangeMotion(2);
	}

	g_pSoundManager->PlaySE("Dmg.mp3");
	return true;
}


