#include "BackChip.h"



CBackChip::CBackChip()
{
	m_bShow = true;
}


CBackChip::~CBackChip()
{
	Release();
}

void CBackChip::Initialize(void)
{
	m_MvCntrl.Initialize();
	m_Anim.Initialize();
	m_StartPos = m_Pos;
	m_MvCntrl.SetSpd(0, 0);
	m_MvCntrl.SetSpd(CUtilities::Random(1, 3), 0);
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
