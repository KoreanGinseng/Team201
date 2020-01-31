#include "EnemyBoss3.h"



CEnemyBoss3::CEnemyBoss3(void) :
	CEnemy()
{
	m_EnemyType = ENEMY_BOSS_3;
}


CEnemyBoss3::~CEnemyBoss3(void)
{
}

void CEnemyBoss3::CreateMotion(const char * pName)
{
	CCharacter::CreateMotion("AnimEneBoss3.bin");
}

void CEnemyBoss3::Initialize(void)
{
	std::string texName = g_pAnimManager->GetAnimation("AnimEneBoss3.bin")->GetTextureName();
	m_pTexture = g_pTextureManager->GetTexture(texName);
	m_HandPos1 = m_Pos;
	m_HandPos2 = m_Pos + Vector2(-100, 50);
	m_pHandTexture1 = g_pTextureManager->GetTexture("Boss3_Hand.png");
	m_pHandTexture2 = g_pTextureManager->GetTexture("Boss3Hand2.png");
	m_MovePos1 = m_MovePos2 = Vector2(0, 0);
	m_bMoveHand = false;
	m_pBossTexture = g_pTextureManager->GetTexture("Boss3_HONTAI.png");
	m_bBossChange = false;
}

void CEnemyBoss3::Update(void)
{
	if (!m_bBossChange)
	{
		CCordinate::SetPlayerCntrl(true);

		return;
	}
	CCordinate::SetPlayerCntrl(false);

	if (!m_bMoveHand)
	{
		m_MovePos2.y -= 0.2f;
		if (m_MovePos2.y < -2.0f)
		{
			m_bMoveHand = true;
		}
	}
	else
	{
		m_MovePos2.y += 0.2f;
		if (m_MovePos2.y > 2.0f)
		{
			m_bMoveHand = false;
		}
	}

	m_Motion.AddTimer(CUtilities::GetFrameSecond());
#ifdef _DEBUG
	if (g_pInput->IsKeyPush(MOFKEY_NUMPAD4))
	{
		m_bDead = true;
	}
#endif // _DEBUG
}

void CEnemyBoss3::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();


	if (!m_bBossChange)
	{
		m_pBossTexture->RenderScale(1024, 708, 0.32f);
		return;
	}

	//m_pHandTexture1->RenderScale(m_HandPos1.x - scroll.x, m_HandPos1.y - scroll.y, 1.5f);
	m_pHandTexture2->RenderScale(m_HandPos2.x - scroll.x, m_HandPos2.y - scroll.y + m_MovePos2.y, 1.5f);

	m_pTexture->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 1.2f, m_Motion.GetSrcRect());
}
