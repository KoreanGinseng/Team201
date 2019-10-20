#include	"Camera2D.h"

CCamera2D::CCamera2D() :
	m_Pos(Vector2(0,0)) {
}

void CCamera2D::Update(const Vector2& centerPos, const CRectangle& prec, const CRectangle& srec)
{
	CRectangle rect = GetRect();
	if (centerPos != m_Pos)
	{
		Vector2 d = centerPos - m_Pos;
		Vector2 pPos = Vector2(prec.Left, prec.Top);
		Vector2 screenPos = ScreenTransration(m_Pos, pPos);
		if ((rect.Right < srec.Right && screenPos.x > g_pGraphics->GetTargetWidth() / 2) ||
			(srec.Left < rect.Left && screenPos.x < g_pGraphics->GetTargetWidth() / 2))
		{
			d.x /= PLAYER_MAXSPEED;
		}
		else
		{
			d.x = 0;
		}
		if (srec.Right < rect.Right)
		{
			m_Pos.x = srec.Right - g_pGraphics->GetTargetWidth();
			d.x = 0;
		}
		if (srec.Left > rect.Left)
		{
			m_Pos.x = 0;
			d.x = 0;
		}
		if ((rect.Bottom < srec.Bottom && screenPos.y > 180) ||
			(srec.Top < rect.Top && screenPos.y < 180))
		{
			d.y /= PLAYER_MAXSPEED;
		}
		else
		{
			d.y = 0;
		}
		if (srec.Bottom < rect.Bottom)
		{
			m_Pos.y = srec.Bottom - g_pGraphics->GetTargetHeight();
			d.y = 0;
		}
		if (srec.Top > rect.Top)
		{
			m_Pos.y = 0;
			d.y = 0;
		}
		m_Pos += d;
	}
	if (m_Pos.x < 0)
	{
		m_Pos.x = 0;
	}
	if (m_Pos.y < 0)
	{
		m_Pos.y = 0;
	}
}