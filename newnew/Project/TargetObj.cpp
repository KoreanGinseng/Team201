#include "TargetObj.h"



CTargetObj::CTargetObj()
{
}


CTargetObj::~CTargetObj()
{
	Release();
}

void CTargetObj::Initialize(void)
{
	CCharacter::Initialize();
	m_bShow = true;
}
