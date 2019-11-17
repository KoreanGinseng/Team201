#include "MoveController.h"



CMoveController::CMoveController()
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
