#pragma once
#include "Move.h"

class CMoveBat :
	public CMove
{
private:
	float	m_TurnPosLeft;
	float	m_TurnPosRight;
	bool	m_bFind;
public:
	CMoveBat();
	~CMoveBat();
	void Initialize(void) override;
	void Update(void) override;
};

