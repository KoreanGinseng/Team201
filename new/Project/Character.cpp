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

	m_Anim.Update();
}

void CCharacter::Render(const Vector2& screenPos)
{
}

void CCharacter::Release(void)
{
}
