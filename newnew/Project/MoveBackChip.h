#pragma once
#include "Move.h"
class CMoveBackChip :
	public CMove
{
public:
	CMoveBackChip();
	~CMoveBackChip();
	void Initialize(void) override;
	void Update(void) override;
};

