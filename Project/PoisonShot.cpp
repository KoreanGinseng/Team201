#include "PoisonShot.h"



CPoisonShot::CPoisonShot(void)
{
}


CPoisonShot::~CPoisonShot(void)
{
}

void CPoisonShot::Initialize(void)
{
	CAnimationData* pData = CAnimationManager::GetAnimation("Effect_Poison.bin");
	std::string texName = pData->GetTextureName();
	SpriteAnimationCreate* pAnim = pData->GetAnim();
	m_Motion.Create(pAnim, pData->GetAnimCount());
	//m_pTexture = CTextureManager::GetTexture(texName);
	m_pTexture = CTextureManager::GetTexture("Poison_Shot.png");
}

void CPoisonShot::Update(void)
{
	if (!m_bShot)
	{
		return;
	}
	m_Move.y += GRAVITY;
	m_Pos += m_Move;
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	if (m_Motion.IsEndMotion())
	{
		m_bShot = false;
	}
}

void CPoisonShot::Render(const Vector2 & screenPos)
{
	if (!m_bShot)
	{
		return;
	}
	//CSubstance::Render(screenPos);
	Vector2 scroll = CCamera2D::GetSScroll();
	m_pTexture->RenderScaleRotate(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 0.3f, MOF_ToRadian(0));
}

void CPoisonShot::Fire(const Vector2 & startPos)
{
	m_Pos = startPos;
	m_Motion.SetTime(0);
	m_Move = Vector2(-3, -6);
	m_bShot = true;
}
