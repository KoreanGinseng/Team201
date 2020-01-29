#include	"Substance.h"

CSubstance::CSubstance(void) :
CCharacter()
{
	m_SubType = -1;
	m_SubStatus = SUBSTATUS_NOMAL;
	m_bTarget = false;
	m_bSelectTarget = true;
	m_bAnimStop = false;
}

void CSubstance::Stop(void)
{
	if (m_SubType == SUB_ENE)
	{
		m_SubStatus = SUBSTATUS_STOP;
		m_bAnimStop = true;
		m_Move = Vector2(0, 0);
		m_WaitCount = m_OffsetWait;
		std::string texName = g_pAnimManager->GetAnimation("Effect_Stop.bin")->GetTextureName();
		g_pEffectManager->Start("Effect_Stop.bin", m_Pos - CCamera2D::GetSScroll() - Vector2(600 * 0.5f, 500 * 0.5f));
		CCordinate::SetStop(true);
		g_pSoundManager->GetSoundSE("SkillActivate.mp3")->Play();
	}
}

void CSubstance::Back(void)
{
	if (m_SubType != SUB_ENE && m_SubStatus != SUBSTATUS_BACK)
	{
		if (m_SubStatus == SUBSTATUS_NOMAL)
		{
			m_SubStatus = SUBSTATUS_BACK;
			g_pSoundManager->GetSoundSE("SkillActivate.mp3")->Play();
		}
		else
		{
			m_SubStatus = SUBSTATUS_NOMAL;
			g_pSoundManager->GetSoundSE("SkillActivate.mp3")->Play();
		}
		m_Motion.ChangeMotion(m_SubStatus);

		std::string texName = g_pAnimManager->GetAnimation("Effect_back.bin")->GetTextureName();
		g_pEffectManager->Start("Effect_Back.bin", m_Pos - CCamera2D::GetSScroll() - Vector2(600 * 0.5f, 500 * 0.5f));
		CCordinate::SetBack(true);
	}
}
void CSubstance::Trip(void)
{
	if (m_SubType != SUB_ENE && m_SubStatus != SUBSTATUS_TRIP)
	{
		if (m_SubStatus == SUBSTATUS_NOMAL)
		{
			m_SubStatus = SUBSTATUS_TRIP;
			g_pSoundManager->GetSoundSE("SkillActivate.mp3")->Play();
		}
		else
		{
			m_SubStatus = SUBSTATUS_NOMAL;
			g_pSoundManager->GetSoundSE("SkillActivate.mp3")->Play();
		}
		m_Motion.ChangeMotion(m_SubStatus);

		std::string texName = g_pAnimManager->GetAnimation("Effect_Skip.bin")->GetTextureName();
		g_pEffectManager->Start("Effect_Skip.bin", m_Pos - CCamera2D::GetSScroll() - Vector2(600 * 0.5f, 500 * 0.5f));
		CCordinate::SetSkip(true);
	}
}

void CSubstance::Render(const Vector2 & screenPos)
{
	if (!m_bShow)
	{
		return;
	}
	CRectangle r = GetSrcRect();
	if (!m_bReverse)
	{
		r.Left = GetSrcRect().Right;
		r.Right = GetSrcRect().Left;
	}
	m_pTexture->Render(screenPos.x, screenPos.y, r);

	Vector2 scroll = CCamera2D::GetSScroll();

#ifdef _DEBUG
	if (gbDebug)
	{
		CRectangle rec(-scroll.x + GetRect().Left, -scroll.y + GetRect().Top, -scroll.x + GetRect().Right, -scroll.y + GetRect().Bottom);
		CGraphicsUtilities::RenderRect(rec, MOF_COLOR_RED);
		for (int i = 0; i < GetRectArray().GetArrayCount(); i++)
		{
			CGraphicsUtilities::RenderRect(screenPos.x + m_SrcRectArray[i].Left, screenPos.y + m_SrcRectArray[i].Top,
				screenPos.x + m_SrcRectArray[i].Right, screenPos.y + m_SrcRectArray[i].Bottom, MOF_COLOR_BLUE);
			CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 30, "%.1f , %.1f", m_Pos.x, m_Pos.y);
		}
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 60, "SubStatus : %d", m_SubStatus);
		CGraphicsUtilities::RenderString(screenPos.x, screenPos.y - 90, "SubType   : %d", m_SubType);
	}
#endif // _DEBUG

	CRectangle sRect = GetRect();
	if (m_bTarget)
	{
		CGraphicsUtilities::RenderRect(sRect.Left - scroll.x, sRect.Top - scroll.y, sRect.Right - scroll.x, sRect.Bottom - scroll.y, MOF_COLOR_GREEN);
	}
}
