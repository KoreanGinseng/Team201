#pragma once
#include "Move.h"
class CMoveHand :
	public CMove
{
private:
	bool	m_bFind;
public:
	CMoveHand();
	~CMoveHand();
	void Initialize(void) override;
	void Update(void) override;
};

