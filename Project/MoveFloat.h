#pragma once
#include "Move.h"
class CMoveFloat :
	public CMove
{
public:
	CMoveFloat();
	~CMoveFloat();
	void Initialize(void) override;
	void Update(void) override;
};

