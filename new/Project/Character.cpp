#include "Character.h"



CCharacter::CCharacter()
{
}


CCharacter::~CCharacter()
{
}

void CCharacter::Initialize(void)
{
	m_MvCntrl.Initialize();
	m_Anim.Initialize();
}

void CCharacter::Update(void)
{
	m_MvCntrl.Update();
	m_Anim.Update();
}

void CCharacter::Render(const Vector2& screenPos)
{
	m_pTexture->Render(screenPos.x, screenPos.y, GetSrcRect());
}

void CCharacter::Release(void)
{
	m_MvCntrl.Remove();
	m_Anim.Release();
}

void CCharacter::CollisionStage(const Vector2 & over)
{
	m_Pos += over;
}
