#include "MoveController.h"



CMoveController::CMoveController()
{
}


CMoveController::~CMoveController()
{
}

void CMoveController::Initialize(void)
{
	for (int i = 0; i < m_MoveArray.GetArrayCount(); i++)
	{
		m_MoveArray[i]->Initialize();
	}
	m_Anim.Initialize();
}

void CMoveController::Update(void)
{
	for (int i = 0; i < m_MoveArray.GetArrayCount(); i++)
	{
		m_MoveArray[i]->Update();
	}
	m_Anim.Update();
}
