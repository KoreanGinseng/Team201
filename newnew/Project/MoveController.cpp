#include "MoveController.h"



CMoveController::CMoveController() :
m_pMove(nullptr)
{
	m_pMove = nullptr;
}


CMoveController::~CMoveController()
{
}

void CMoveController::Initialize(void)
{
	if (m_pMove)
	{
		m_pMove->Initialize();
	}
}

void CMoveController::Update(void)
{
	if (m_pMove)
	{
		m_pMove->Update();
	}
}

bool CMoveController::Create(const int & no)
{
	CMove* move = nullptr;
	switch (no)
	{
	case 0:
		move = NEW CMovePlayer();
		break;
	default:
		break;
	}
	if (!move)
	{
		return false;
	}
	NewPointerRelease(m_pMove);
	m_pMove = move;
	return true;
}
