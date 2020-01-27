#include "EnemyBoss2.h"



CEnemyBoss2::CEnemyBoss2(void) :
CEnemy()
{
	m_EnemyType = ENEMY_BOSS_2;
	m_bSelectTarget = false;
}


CEnemyBoss2::~CEnemyBoss2(void)
{
}

void CEnemyBoss2::CreateMotion(const char * pName)
{
	SpriteAnimationCreate* pAnim = g_pAnimManager->GetAnimation("_Boss2_H.bin")->GetAnim();
	int c = g_pAnimManager->GetAnimation("_Boss2_H.bin")->GetAnimCount();
	m_BodyMotion[BODY_HEAD].Create(pAnim, c);
	pAnim = g_pAnimManager->GetAnimation("_Boss2_D.bin")->GetAnim();
	c = g_pAnimManager->GetAnimation("_Boss2_D.bin")->GetAnimCount();
	m_BodyMotion[BODY_BODY].Create(pAnim, c);
	pAnim = g_pAnimManager->GetAnimation("_Boss2_U.bin")->GetAnim();
	c = g_pAnimManager->GetAnimation("_Boss2_U.bin")->GetAnimCount();
	m_BodyMotion[BODY_DOWN].Create(pAnim, c);
	pAnim = g_pAnimManager->GetAnimation("_Boss2_End.bin")->GetAnim();
	c = g_pAnimManager->GetAnimation("_Boss2_End.bin")->GetAnimCount();
	m_DeadMotion.Create(pAnim, c);
}

void CEnemyBoss2::SetTexture(const CTexturePtr & pt)
{
	m_pBodyTexture[BODY_HEAD] = g_pTextureManager->GetTexture("_Boss2_H.png");
	m_pBodyTexture[BODY_BODY] = g_pTextureManager->GetTexture("_Boss2_D.png");
	m_pBodyTexture[BODY_DOWN] = g_pTextureManager->GetTexture("_Boss2_U.png");
	m_pBodyTexture[BODY_COUNT + BODY_HEAD] = g_pTextureManager->GetTexture("_Boss2_H_D.png");
	m_pBodyTexture[BODY_COUNT + BODY_BODY] = g_pTextureManager->GetTexture("_Boss2_D_D.png");
	m_pBodyTexture[BODY_COUNT + BODY_DOWN] = g_pTextureManager->GetTexture("_Boss2_U_D.png");
	m_pDeadTexture = g_pTextureManager->GetTexture("_Boss2_END.png");
}

void CEnemyBoss2::Initialize(void)
{
	for (auto& itr : m_bBodyDead)
	{
		itr = false;
	}
	m_BodyPos[BODY_HEAD] = m_Pos - Vector2(0,200);
	m_BodyPos[BODY_BODY] = m_Pos - Vector2(0, 200) + Vector2(0, 5) * 1.8f;
	m_BodyPos[BODY_DOWN] = m_Pos - Vector2(0, 200) + Vector2(0, 100) * 1.8f;
	m_bDeadM = false;
}

void CEnemyBoss2::Update(void)
{
	for (auto& itr : m_BodyMotion)
	{
		itr.AddTimer(CUtilities::GetFrameSecond());
	}
	if (m_bBodyDead[BODY_DOWN] && m_bBodyDead[BODY_BODY] && m_bBodyDead[BODY_HEAD])
	{
		m_bDeadM = true;
	}
	if (m_bDeadM)
	{
		m_DeadMotion.AddTimer(CUtilities::GetFrameSecond());
		for (auto& itr : m_BodyPos)
		{
			itr += Vector2(0, 3);
		}
		if (m_DeadMotion.IsEndMotion() && m_DeadMotion.GetMotionNo() == 1)
		{
			m_bDead = true;
		}
		if (m_DeadMotion.IsEndMotion() && m_DeadMotion.GetMotionNo() == 0)
		{
			m_DeadMotion.ChangeMotion(1);
		}
	}
#ifdef _DEBUG
	if (g_pInput->IsKeyPush(MOFKEY_NUMPAD7))
	{
		m_bBodyDead[BODY_DOWN] = true;
	}
	if (g_pInput->IsKeyPush(MOFKEY_NUMPAD8))
	{
		m_bBodyDead[BODY_BODY] = true;
	}
	if (g_pInput->IsKeyPush(MOFKEY_NUMPAD9))
	{
		m_bBodyDead[BODY_HEAD] = true;
	}
#endif // _DEBUG

}

void CEnemyBoss2::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();
	if (!m_bDeadM)
	{
		(m_bBodyDead[BODY_DOWN] ? m_pBodyTexture[BODY_COUNT + BODY_DOWN] : m_pBodyTexture[BODY_DOWN])
			->RenderScale(m_BodyPos[BODY_DOWN].x - scroll.x, m_BodyPos[BODY_DOWN].y - scroll.y, 1.8f, m_BodyMotion[BODY_DOWN].GetSrcRect());
		(m_bBodyDead[BODY_BODY] ? m_pBodyTexture[BODY_COUNT + BODY_BODY] : m_pBodyTexture[BODY_BODY])
			->RenderScale(m_BodyPos[BODY_BODY].x - scroll.x, m_BodyPos[BODY_BODY].y - scroll.y, 1.8f, m_BodyMotion[BODY_BODY].GetSrcRect());
		(m_bBodyDead[BODY_HEAD] ? m_pBodyTexture[BODY_COUNT + BODY_HEAD] : m_pBodyTexture[BODY_HEAD])
			->RenderScale(m_BodyPos[BODY_HEAD].x - scroll.x, m_BodyPos[BODY_HEAD].y - scroll.y, 1.8f, m_BodyMotion[BODY_HEAD].GetSrcRect());
	}
	else
	{
		m_pDeadTexture->RenderScale(m_BodyPos[BODY_HEAD].x - scroll.x - 100, m_BodyPos[BODY_HEAD].y - scroll.y, 1.8f, m_DeadMotion.GetSrcRect());
	}
}

void CEnemyBoss2::RenderCircle(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();
	if (!m_bDeadM)
	{
		(m_bBodyDead[BODY_DOWN] ? m_pBodyTexture[BODY_COUNT + BODY_DOWN] : m_pBodyTexture[BODY_DOWN])
			->RenderScale(m_BodyPos[BODY_DOWN].x - scroll.x, m_BodyPos[BODY_DOWN].y - scroll.y, 1.8f, m_BodyMotion[BODY_DOWN].GetSrcRect(), MOF_ARGB(128, 255, 255, 255));
		(m_bBodyDead[BODY_BODY] ? m_pBodyTexture[BODY_COUNT + BODY_BODY] : m_pBodyTexture[BODY_BODY])
			->RenderScale(m_BodyPos[BODY_BODY].x - scroll.x, m_BodyPos[BODY_BODY].y - scroll.y, 1.8f, m_BodyMotion[BODY_BODY].GetSrcRect(), MOF_ARGB(128, 255, 255, 255));
		(m_bBodyDead[BODY_HEAD] ? m_pBodyTexture[BODY_COUNT + BODY_HEAD] : m_pBodyTexture[BODY_HEAD])
			->RenderScale(m_BodyPos[BODY_HEAD].x - scroll.x, m_BodyPos[BODY_HEAD].y - scroll.y, 1.8f, m_BodyMotion[BODY_HEAD].GetSrcRect(), MOF_ARGB(128, 255, 255, 255));
	}
	else
	{
		m_pDeadTexture->RenderScale(m_BodyPos[BODY_HEAD].x - scroll.x - 100, m_BodyPos[BODY_HEAD].y - scroll.y, 1.8f, m_DeadMotion.GetSrcRect(), MOF_ARGB(128, 255, 255, 255));
	}
}

void CEnemyBoss2::Release(void)
{
	m_pDeadTexture = nullptr;
	m_DeadMotion.Release();
	for (auto& itr : m_pBodyTexture)
	{
		itr = nullptr;
	}
	for (auto& itr : m_BodyMotion)
	{
		itr.Release();
	}
}
