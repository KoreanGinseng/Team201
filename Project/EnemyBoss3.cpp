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
}

void CEnemyBoss3::Update(void)
{
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
	m_pTexture->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 1.2f, m_Motion.GetSrcRect());
}
