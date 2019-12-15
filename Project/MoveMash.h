#pragma once
#include "Move.h"
#include "EnemyDefine.h"

class CMoveMash :
	public CMove
{
private:

public:
	CMoveMash();
	~CMoveMash();
	void Initialize(void) override;
	void Update(void) override;
};

