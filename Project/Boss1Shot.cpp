#include "Boss1Shot.h"



CBoss1Shot1::CBoss1Shot1(void) :
CShot()
{
	m_bSelectTarget = true;
	m_ShotType = SHOT_BOUND;
}


CBoss1Shot1::~CBoss1Shot1(void)
{
}

void CBoss1Shot1::Initialize(void)
{
	CAnimationData* pData = CAnimationManager::GetAnimation("Explosion_A.bin");
	m_TexName = pData->GetTextureName();
	SpriteAnimationCreate* pAnim = pData->GetAnim();
	m_Motion.Create(pAnim, pData->GetAnimCount());
	//m_pTexture = CTextureManager::GetTexture(texName);
	m_pTexture = CTextureManager::GetTexture("Boss1Shot.png");
	m_Bound = 0;
}

void CBoss1Shot1::Update(void)
{
	if (!m_bAnimStop)
	{
		m_Move.y += GRAVITY;
		m_Move.x += 0.005f;
	}

	m_Pos += m_Move;
	
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
	
	if (m_Bound > 0)
	{
		if (!m_bAnimStop)
		{
			m_Motion.AddTimer(CUtilities::GetFrameSecond());
		}
		if (m_Motion.IsEndMotion())
		{
			m_bShot = false;
		}
	}
}

void CBoss1Shot1::Render(const Vector2 & screenPos)
{
	Vector2 scroll = CCamera2D::GetSScroll();
	if (m_Bound > 0)
	{
		CTexturePtr pt = g_pTextureManager->GetTexture(m_TexName);
		float sx = (m_Motion.GetSrcRect().GetWidth() - m_pTexture->GetWidth()) * 1.5f;
		float sy = (m_Motion.GetSrcRect().GetHeight() - m_pTexture->GetHeight());
		pt->Render(m_ExPos.x - scroll.x - sx, m_ExPos.y - scroll.y - sy, m_Motion.GetSrcRect());
	}
	else
	{
		m_pTexture->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 0.5f);
	}
}

void CBoss1Shot1::Fire(const Vector2 & pos)
{
	m_Pos = pos;
	m_Move = Vector2(-5, -6);
	m_bShot = true;
}

void CBoss1Shot1::CollisionPlayer(const Vector2 & over)
{
	CShot::CollisionPlayer(over);
	m_WaitCount = 0;
}

void CBoss1Shot1::CollisionStage(const Vector2 & over)
{
	m_Pos += over;
	if (over.y < 0 && m_Move.y > 0)
	{
		m_Move.y = -6 + m_Bound++;

		m_ExPos = m_Pos;
	}
}

CRectangle CBoss1Shot1::GetRect(void)
{
	return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_pTexture->GetWidth() * 0.5f, m_Pos.y + m_pTexture->GetHeight() * 0.5f);
}
