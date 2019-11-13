#include	"Anim.h"

void CAnim::Initialize(void)
{

}

void CAnim::Update(void)
{
	m_Anim.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Anim.GetSrcRect();
}

void CAnim::Create(const char * pName)
{
	int c = g_pAnimManager->GetResource(pName)->GetAnimCount();
	m_Anim.Create(g_pAnimManager->GetResource(pName)->GetAnim(), c);
}
