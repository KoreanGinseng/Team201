#include "MoveFloat.h"



CMoveFloat::CMoveFloat() :
CMove()
{
}


CMoveFloat::~CMoveFloat()
{
}

void CMoveFloat::Initialize(void)
{
	m_Spd.x = 5.0f;
}

void CMoveFloat::Update(void)
{
	m_Move.x = m_Spd.x;
}
