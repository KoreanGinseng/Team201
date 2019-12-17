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
	m_Move = Vector2(CUtilities::Random(1, 3), 0);
}

void CBackChip::Update(void)
{
	m_Pos -= m_Move / 5.0f;
}

void CBackChip::RenderBackBack(const Vector2 & screenPos)
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = CStage::GetStageRect().Right;
	int hn = CStage::GetStageRect().Bottom;
	for (float y = ((int)-screenPos.y / 4 % hn) - hn; y < sch; y += hn) {
		for (float x = ((int)-screenPos.x / 4 % wn) - wn; x < scw; x += wn) {
			m_pTexture->Render(x + m_Pos.x, y);
		}
	}
}

void CBackChip::RenderBackStage(const Vector2 & screenPos)
{
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = CStage::GetStageRect().Right;
	int hn = CStage::GetStageRect().Bottom;
	for (float y = ((int)-screenPos.y / 4 % hn) - hn; y < sch; y += hn) {
		for (float x = ((int)-screenPos.x / 4 % wn) - wn; x < scw; x += wn) {
			m_pTexture->Render(x + m_Pos.x, y);
		}
	}
}
