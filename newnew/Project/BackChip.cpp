#include "BackChip.h"



CBackChip::CBackChip()
{
	m_bShow = true;
}


CBackChip::~CBackChip()
{
}

void CBackChip::RenderBackBack(const Vector2 & screenPos)
{
	m_pTexture->Render(screenPos.x, screenPos.y);
}

void CBackChip::RenderBackStage(const Vector2 & screenPos)
{
	m_pTexture->Render(screenPos.x, screenPos.y);
}
