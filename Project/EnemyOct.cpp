#include "EnemyOct.h"



CEnemyOct::CEnemyOct(void) :
CEnemy()
{
	m_EnemyType = ENEMY_OCT;
	m_OffsetWait = 120;
	m_bCollision = true;
}


CEnemyOct::~CEnemyOct(void)
{
}

void CEnemyOct::Initialize(void)
{
	m_bDead = false;
	m_bShow = true;
	m_AimShot.SetTexture(g_pTextureManager->GetTexture("Oct_Shot.png"));
	CAnimationData* pData = g_pAnimManager->GetAnimation("Effect_Beem.bin");
	int c = pData->GetAnimCount();
	m_ShotMotion.Create(pData->GetAnim(), c);
	m_pShotTexture = g_pTextureManager->GetTexture(pData->GetTextureName());
	m_AimShot.SetScale(0.2f);
	m_AimShot.SetSpd(Vector2(16, 16));
	m_bShotEffect = false;
}

void CEnemyOct::Update(void)
{

	if (m_bShotEffect)
	{
		m_ShotMotion.AddTimer(CUtilities::GetFrameSecond() * 2.0f);
	}
	if (m_AimShot.IsShot())
	{
		m_AimShot.Update();
	}

	if (m_bAnimStop)
	{
		m_WaitCount--;
		if (m_WaitCount < 0)
		{
			m_WaitCount = m_OffsetWait;
			m_bAnimStop = false;
		}
		return;
	}

	if (m_bGravity)
	{
		m_Move.y += GRAVITY;
		if (m_Move.y > GRAVITYMAX)
		{
			m_Move.y = GRAVITYMAX;
		}
	}
	if (CCordinate::GetPlayerPos().x < m_Pos.x && CCordinate::GetPlayerPos().x > m_Pos.x - 128 * 6)
	{
		if (!m_AimShot.IsShot() && m_Motion.GetMotionNo() == 0)
		{
			m_Motion.ChangeMotion(1);
		}
	}
	if (m_Motion.GetMotionNo() == 1 && m_Motion.GetFrameNo() >= 12 && !m_AimShot.IsShot())
	{
		m_ShotMotion.SetTime(0);
		m_bShotEffect = true;
	}

	if (m_Motion.GetMotionNo() == 1 && m_Motion.GetFrameNo() >= 14 && !m_AimShot.IsShot())
	{
		Vector2 pos = m_Pos + Vector2(-10, 60);
		m_AimShot.Fire(pos);
	}
	if (m_Motion.GetMotionNo() == 1 && m_Motion.IsEndMotion())
	{
		m_Motion.ChangeMotion(0);
	}
	if(m_AimShot.IsShot())
	{
		if (m_AimShot.IsStageOver())
		{
			m_AimShot.SetShot(false);
		}
	}

	m_Pos += m_Move;

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
}

void CEnemyOct::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();
	if (m_AimShot.IsShot())
	{
		m_AimShot.Render(Vector2());
	}
	m_pTexture->Render(m_Pos.x - scroll.x, m_Pos.y - scroll.y, m_Motion.GetSrcRect());
	if (!m_ShotMotion.IsEndMotion())
	{
		m_pShotTexture->RenderScale(m_Pos.x - scroll.x - 130, m_Pos.y - scroll.y - 40, 0.5f, m_ShotMotion.GetSrcRect());
	}
#ifdef _DEBUG
	if (gbDebug)
	{
		CRectangle rect = GetRect();
		CGraphicsUtilities::RenderRect(rect - scroll, MOF_COLOR_BLUE);
	}
#endif
}

CRectangle CEnemyOct::GetRect(void)
{
	CRectangle rect(m_Pos.x, m_Pos.y, m_Pos.x + m_Motion.GetSrcRect().GetWidth(), m_Pos.y + m_Motion.GetSrcRect().GetHeight());
	rect.Expansion(-10, -30);
	return rect;
}

CRectangle CEnemyOct::GetSrcAddRect(void)
{
	CRectangle rect(0, 0, m_Motion.GetSrcRect().GetWidth(), m_Motion.GetSrcRect().GetHeight());
	rect.Expansion(-10, -30);
	return rect;
}
