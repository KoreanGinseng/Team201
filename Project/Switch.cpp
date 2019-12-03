#include "Switch.h"



CSwitch::CSwitch()
{
}


CSwitch::~CSwitch()
{
}

void CSwitch::Initialize(void)
{
	m_bswitch = false;
}

bool CSwitch::Load(void)
{
	return false;
}

void CSwitch::Update(const bool &me)
{

}

void CSwitch::SetSwitch(bool b)
{
	m_bswitch = b;
}