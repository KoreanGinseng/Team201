#include "SavePosint.h"



CSavePosint::CSavePosint(void) :
CTargetObj()
{
	m_bSelectTarget = false;
}


CSavePosint::~CSavePosint()
{
}

void CSavePosint::Update(void)
{
	if (m_Pos.x < CCordinate::GetPlayerPos().x)
	{
		CCordinate::SetSavePoint(m_Pos);
	}
}
