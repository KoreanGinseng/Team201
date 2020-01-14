#include "Boss1Shot.h"



CBoss1Shot1::CBoss1Shot1(void)
{
}


CBoss1Shot1::~CBoss1Shot1(void)
{
}

void CBoss1Shot1::Initialize(void)
{
	CAnimationData* pData = CAnimationManager::GetAnimation("Effect_Poison.bin");
	std::string texName = pData->GetTextureName();
	SpriteAnimationCreate* pAnim = pData->GetAnim();
	m_Motion.Create(pAnim, pData->GetAnimCount());
	m_pTexture = CTextureManager::GetTexture(texName);
	m_Bound = 0;
}

void CBoss1Shot1::Update(void)
{
	m_Move.y += GRAVITY;
	m_Pos += m_Move;
}

void CBoss1Shot1::Fire(const Vector2 & pos)
{
	m_Pos = pos;
	m_Move = Vector2(-5, -8);
	m_bShot = true;
}

void CBoss1Shot1::CollisionStage(const Vector2 & over)
{
	if (over.y < 0 && m_Move.y > 0)
	{
		m_Move.y = -6 + m_Bound++;
	}
}
