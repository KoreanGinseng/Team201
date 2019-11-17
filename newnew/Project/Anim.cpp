#include	"Anim.h"

void CAnim::Initialize(void)
{
	m_pAnim = nullptr;
}

void CAnim::Update(void)
{
	if (!m_pAnim)
	{
		return;
	}
	m_pAnim->AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_pAnim->GetSrcRect();
}

void CAnim::Create(const char * pName)
{
	int c = g_pAnimManager->GetResource(pName)->GetAnimCount();
	NewPointerRelease(m_pAnim);
	m_pAnim = new CSpriteMotionController();
	m_pAnim->Create(g_pAnimManager->GetResource(pName)->GetAnim(), c);
}
