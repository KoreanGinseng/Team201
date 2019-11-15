#include "BackChip.h"




BackChip::BackChip()
{
}


BackChip::~BackChip()
{
}

bool BackChip::Load()
{
	return true;
}

void BackChip::Initialize(Vector2 pos, int type)
{
	m_Type = type;
	SetPos(pos);
	m_bShow = true;
}

void BackChip::Update()
{
	m_Pos.x -=2;
}

void BackChip::Render(Vector2 pos)
{
	m_pTexture->Render(pos.x, pos.y);
}

void BackChip::RenderDebug()
{
}

void BackChip::Release()
{
}

bool BackChip::GetShow()
{
	return m_bShow;
}
void BackChip::SetPos(Vector2 p)
{
	m_Pos = p;
}

