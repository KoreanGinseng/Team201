#include "TargetObj.h"



CTargetObj::CTargetObj() :
CSubstance()
{
}


CTargetObj::~CTargetObj()
{
	Release();
}

void CTargetObj::Initialize(void)
{
	m_bReverse = true;
}

void CTargetObj::Update(void)
{

}

void CTargetObj::SetStatus(const int & n)
{
	if (n == 1)
	{
		m_SubStatus = 0;
	}
	else
	{
		m_SubStatus = 1;
	}
	m_Motion.ChangeMotion(m_SubStatus);
}

bool CTargetObj::OverValue(CRectangle rec, Vector2 & out)
{
	return false;
}
