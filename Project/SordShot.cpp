#include "SordShot.h"



CSordShot::CSordShot(void) :
CShot()
{
	m_bSelectTarget = true;
}


CSordShot::~CSordShot(void)
{
}

void CSordShot::Fire(const Vector2 & startPos)
{
	m_Pos = startPos;
	for (int i = -2; i < 3; i++)
	{
		m_WarpPos[i + 2] = m_Pos + Vector2(100 * i, 0);
	}
	m_bShot = true;
	m_No = CUtilities::Random(5);
	m_Pos = m_WarpPos[m_No];
	m_Move = Vector2(0, 0);
}

void CSordShot::Initialize(void)
{
	m_pTexture = g_pTextureManager->GetTexture("Boss_Sord.png");
	m_bShot = false;
	m_No = 0;
	m_OffsetWait = 120;
	m_WaitCount = m_OffsetWait;
}

void CSordShot::Update(void)
{
	if (m_bAnimStop)
	{
		m_WaitCount--;
		if (m_WaitCount < 0)
		{
			m_bAnimStop = false;
			m_SubStatus = SUBSTATUS_NOMAL;
			m_WaitCount = m_OffsetWait;
		}
		return;
	}

	m_WarpTime--;
	if (m_WarpTime < 0)
	{
		m_WarpTime = m_OffsetWarpTime;
		int no = m_No;
		while (no == m_No)
		{
			m_No = CUtilities::Random(5);
		}
		m_Pos.x = m_WarpPos[m_No].x;
	}

	m_Move.y += GRAVITY;

	m_Pos += m_Move;

	if (IsStageOver())
	{
		m_bShot = false;
	}
}

void CSordShot::Render(const Vector2 & screenPos)
{
	if (!m_bShot)
	{
		return;
	}
	Vector2 scroll = CCamera2D::GetSScroll();
	m_pTexture->RenderScale(m_Pos.x - scroll.x, m_Pos.y - scroll.y, 0.5f);
	if (m_bTarget)
	{
		CGraphicsUtilities::RenderRect(GetRect() - scroll, MOF_COLOR_GREEN);
	}
#ifdef _DEBUG
	if (gbDebug)
	{
		CGraphicsUtilities::RenderRect(GetRect() - scroll, MOF_COLOR_BLUE);
	}
#endif // _DEBUG

}

void CSordShot::SetWorpTime(const int & time)
{
	m_OffsetWarpTime = time;
}

CRectangle CSordShot::GetRect(void)
{
	return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_pTexture->GetWidth() * 0.5f, m_Pos.y + m_pTexture->GetHeight() * 0.5f);
}
