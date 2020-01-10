#include "BackChip.h"



CBackChip::CBackChip()
{
	m_bShow = true;
	m_bReverse = true;
}


CBackChip::~CBackChip()
{
	Release();
}

void CBackChip::Initialize(void)
{
	m_StartPos = m_Pos;
	m_Move = Vector2(CUtilities::Random(10, 30), 0);
}

void CBackChip::Update(void)
{
	m_Pos -= m_Move / 5.0f;
	if (m_Pos.x + m_pTexture->GetWidth() < 0)
	{
		m_Pos.x = CStage::GetStageRect().Right;
	}
}

void CBackChip::RenderBackBack(const Vector2 & screenPos)
{
	//int scw = g_pGraphics->GetTargetWidth();
	//int sch = g_pGraphics->GetTargetHeight();
	//int wn = CStage::GetStageRect().Right;
	//int hn = CStage::GetStageRect().Bottom;
	Vector2 scroll = CCamera2D::GetSScroll();
	scroll /= 4;
	//for (float y = ((int)-scroll.y / 4 % hn) - hn; y < sch; y += hn) {
	//	for (float x = ((int)-scroll.x / 4 % wn) - wn; x < scw; x += wn) {
			m_pTexture->Render(m_Pos.x - scroll.x, m_Pos.y - scroll.y);
	//	}
	//}
}

void CBackChip::RenderBackStage(const Vector2 & screenPos)
{
	//int scw = g_pGraphics->GetTargetWidth();
	//int sch = g_pGraphics->GetTargetHeight();
	//int wn = CStage::GetStageRect().Right;
	//int hn = CStage::GetStageRect().Bottom;
	Vector2 scroll = CCamera2D::GetSScroll();
	scroll /= 4;
	//for (float y = ((int)-scroll.y / 4 % hn) - hn; y < sch; y += hn) {
	//	for (float x = ((int)-scroll.x / 4 % wn) - wn; x < scw; x += wn) {
			m_pTexture->Render(m_Pos.x - scroll.x, m_Pos.y - scroll.y);
	//	}
	//}
}
