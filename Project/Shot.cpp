#include "Shot.h"



CShot::CShot(void) :
CSubstance(),
m_bShot(false)
{
	m_bSelectTarget = false;
}


CShot::~CShot(void)
{
}

bool CShot::IsShot(void) const
{
	return m_bShot;
}

void CShot::SetShot(const bool & b)
{
	m_bShot = b;
}
