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
	case MOVE_PLAYER:
		move = NEW CMovePlayer();
		break;
	case MOVE_ENE_KINOKO:
	case MOVE_ENE_DOKU:
		move = NEW CMoveMash();
		break;
	case MOVE_ENE_BAT:
		move = NEW CMoveBat();
		break;
	case MOVE_ENE_TAKO:
		break;
	case MOVE_BC_01:
	case MOVE_BC_02:
	case MOVE_BC_03:
		move = NEW CMoveBackChip();
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
