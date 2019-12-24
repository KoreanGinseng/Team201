#include "CameraCntrl.h"



CCameraCntrl::CCameraCntrl(void) :
CTargetObj(),
m_bCntrl(false)
{
	m_bSelectTarget = false;
}

CCameraCntrl::~CCameraCntrl(void)
{
}

void CCameraCntrl::Update(void)
{
	if (m_bCntrl)
	{
		return;
	}

	if (m_Pos.x < CCordinate::GetPlayerPos().x)
	{
		m_bCntrl = true;
	}
}
