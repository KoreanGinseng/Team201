#include "MoveFloor.h"



CMoveFloor::CMoveFloor(void)
{
}


CMoveFloor::~CMoveFloor(void)
{
}

void CMoveFloor::Initialize(void)
{
	switch (m_SubStatus)
	{
	case SUBSTATUS_BACK:
	{
		m_BackPos = m_Pos.y;
		m_NomalPos = m_Pos.y + 200;
		m_TripPos = m_Pos.y + 400;
		break;
	}
	case SUBSTATUS_NOMAL:
	{
		m_BackPos = m_Pos.y - 200;
		m_NomalPos = m_Pos.y;
		m_TripPos = m_Pos.y + 200;
		break;
	}
	case SUBSTATUS_TRIP:
	{
		m_BackPos = m_Pos.y - 400;
		m_NomalPos = m_Pos.y - 200;
		m_TripPos = m_Pos.y;
		break;
	}
	}
	m_PrevSubStatus = m_SubStatus;
	m_bChange = false;
	char* file[] = {
		"Object_Floor01.png",
		"Object_Floor02.png",
		"Object_Floor03.png",
		"Object_Floor04.png",
		"Object_Floor05.png",
		"Object_Floor06.png",
	};
	m_pTexture = g_pTextureManager->GetTexture(file[3 * m_RectType + m_ColorType]);
}

void CMoveFloor::Update(void)
{
	if (m_PrevSubStatus != m_SubStatus)
	{
		m_bChange = true;
		m_PrevSubStatus = m_SubStatus;
	}
	if (m_bChange)
	{
		switch (m_SubStatus)
		{
		case SUBSTATUS_BACK:
		{
			if (m_Pos.y != m_BackPos)
			{
				m_Pos.y--;
			}
			else
			{
				m_bChange = false;
			}
			break;
		}
		case SUBSTATUS_NOMAL:
		{
			if (m_Pos.y != m_NomalPos)
			{
				if (m_Pos.y - m_NomalPos < 0)
				{
					m_Pos.y++;
				}
				else if (m_Pos.y - m_NomalPos > 0)
				{
					m_Pos.y--;
				}
			}
			else
			{
				m_bChange = false;
			}
			break;
		}
		case SUBSTATUS_TRIP:
		{
			if (m_Pos.y != m_TripPos)
			{
				m_Pos.y++;
			}
			else
			{
				m_bChange = false;
			}
			break;
		}
		}
	}
}

void CMoveFloor::SetColorType(const int & t)
{
	m_ColorType = t;
}

void CMoveFloor::SetRectType(const int & t)
{
	m_RectType = t;
}
