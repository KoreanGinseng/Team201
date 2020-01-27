#include "CameraCntrl.h"



CCameraCntrl::CCameraCntrl(void) :
CTargetObj(),
m_bCntrl(false),
m_bEndCntrl(false)
{
	m_Type = OBJECT_CAMERACNTRL;
	m_bSelectTarget = false;
}

CCameraCntrl::~CCameraCntrl(void)
{
}

void CCameraCntrl::Initialize(void)
{
	if (m_SubStatus == 0)
	{
		m_MoveType = CAMERA_MOVE_BOSS;
	}
	else
	{
		m_MoveType = CAMERA_MOVE_BRIDGE;
	}
	m_bCntrl = false;
	m_bEndCntrl = false;
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

void CCameraCntrl::Render(const Vector2 & screenPos)
{
}
