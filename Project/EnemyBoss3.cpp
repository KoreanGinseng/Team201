#include "EnemyBoss3.h"



void CEnemyBoss3::AttackReset(void)
{
	m_AttackNo = 0;
	for (auto& itr : m_AttackList)
	{
		itr = -1;
	}
	while (m_AttackNo != 3)
	{
		m_AttackList[m_AttackNo] = CUtilities::Random(3);
		bool search = false;
		for (int i = 0; i < 3; i++)
		{
			if (i == m_AttackNo)
			{
				continue;
			}
			if (m_AttackList[i] == m_AttackList[m_AttackNo])
			{
				search = true;
				break;
			}
		}
		if (!search)
		{
			m_AttackNo++;
		}
	}
	m_AttackNo = 0;
}

void CEnemyBoss3::Attack(void)
{
	switch (m_AttackList[m_AttackNo])
	{
	case 0:
	{

	}
	case 1:
	{

	}
	case 2:
	{

	}
	}

	if (m_bBossAttack)
	{
		m_AttackNo++;
		if (m_AttackNo >= 3)
		{
			AttackReset();
		}
	}
}

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
	m_HP = 3;
	m_bShow = true;
	m_bDead = false;
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
	m_StartTime = 120;
	m_ChangeTime = 30;
	m_FlashAlpha = 0;
	CCordinate::SetBossFlash(&m_FlashAlpha);

	m_SrcRectArray.Add(CRectangle(450, 360, 1000, 700));
	m_SrcRectArray.Add(CRectangle(250, 700, 1000, 1000));

	AttackReset();
	
	m_bBossAttack = false;

	//DEBUG
	m_bBossChange = true;

}

void CEnemyBoss3::Update(void)
{
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

	if (!m_bBossChange || (m_bBossChange && m_FlashAlpha > 0))
	{
		CCordinate::SetPlayerCntrl(true);
		if (m_StartTime-- <= 0)
		{
			m_StartTime = 0;
			if (m_ChangeTime > 0)
			{
				m_FlashAlpha += 3;
				if (m_FlashAlpha >= 255)
				{
					m_FlashAlpha = 255;
					m_bBossChange = true;
					m_ChangeTime--;
				}
			}
			else
			{
				m_FlashAlpha -= 3;
				if (m_FlashAlpha < 0)
				{
					m_FlashAlpha = 0;
				}
			}
		}
		return;
	}
	CCordinate::SetPlayerCntrl(false);

	Attack();

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
	if (m_DamageWait % 2 != 0)
	{
		return;
	}

	Vector2 scroll = CCamera2D::GetSScroll();


	if (!m_bBossChange)
	{
		m_pBossTexture->RenderScale(1024, 708, 0.32f);
		return;
	}

	//m_pHandTexture1->RenderScale(m_HandPos1.x - scroll.x, m_HandPos1.y - scroll.y, 1.5f);
	m_pHandTexture2->RenderScale(m_HandPos2.x - scroll.x, m_HandPos2.y - scroll.y + m_MovePos2.y, 1.5f);

	m_pTexture->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 1.2f, m_Motion.GetSrcRect());
#ifdef _DEBUG
	if (gbDebug)
	{
		for (int i = 0; i < m_SrcRectArray.GetArrayCount(); i++)
		{
			CRectangle rect = m_SrcRectArray[i];
			CGraphicsUtilities::RenderRect(rect + m_Pos - scroll, MOF_COLOR_BLUE);
		}
	}
#endif // _DEBUG
}

void CEnemyBoss3::RenderCircle(const Vector2 & screenPos)
{
}

CRectangle CEnemyBoss3::GetRect(void)
{
	CRectangle rect(m_Pos.x, m_Pos.y, m_Pos.x + m_Motion.GetSrcRect().GetWidth() * 1.2f, m_Pos.y + m_Motion.GetSrcRect().GetHeight() * 1.2f);
	return rect;
}

CRectangle CEnemyBoss3::GetSrcAddRect(void)
{
	CRectangle rect(350, 50, 700, 360);
	return rect;
}
