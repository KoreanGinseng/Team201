#include	"Camera2D.h"
#include	"Coordinate.h"

Vector2 CCamera2D::m_sPos = Vector2();

CCamera2D::CCamera2D() :
m_Pos(Vector2(0,0)),
m_bStart(false),
m_StartPos(),
m_bCenter(false),
m_KeepCount(0),
m_bBoss(false)
{
	CCordinate::SetMainCameraPos(&m_Pos);
}

void CCamera2D::Update(const Vector2& centerPos, const CRectangle& prec, const CRectangle& srec)
{
	m_sPos = m_Pos;
	if (m_bStart || m_bBoss)
	{
		return;
	}
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

	m_Pos.x = (int)m_Pos.x;
	m_Pos.y = (int)m_Pos.y;
}

void CCamera2D::Move(const int & type)
{
	switch (type)
	{
	case CAMERA_MOVE_BRIDGE:
		{
			if (!m_bStart)
			{
				m_bStart = true;
				m_StartPos = m_Pos;
			}
			if (!m_bCenter)
			{
				m_Pos.x += 3;
				if (m_Pos.x - m_StartPos.x > 850)
				{
					m_bCenter = true;
				}
			}
			else
			{
				//m_Pos.x -= 4;
				m_KeepCount++;
				//if (m_Pos.x - m_StartPos.x < 0)
				if (m_KeepCount > 30)
				{
					m_bCenter = false;
					m_bStart = false;
				}
			}
		}
		break;
	case CAMERA_MOVE_BOSS:
		{
			if (!m_bStart)
			{
				m_bStart = true;
				m_StartPos = m_Pos;
			}
			if (!m_bCenter)
			{
				m_Pos.x += 5;
				if (m_Pos.x - m_StartPos.x > 870)
				{
					m_bCenter = true;
				}
			}
			else
			{
				m_KeepCount++;
				if (m_KeepCount > 120)
				{
					m_bBoss = true;
					m_bCenter = false;
					m_bStart = false;
				}
			}
		}
		break;
	default:
		break;
	}
}
