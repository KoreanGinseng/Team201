#pragma once
#include "Substance.h"
class CItem :
	public CSubstance
{
public:
	CItem();
	~CItem();
	virtual void Initialize(void) override {}
	virtual void Update(void) override {}
};

