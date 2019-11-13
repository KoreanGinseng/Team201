#pragma once

class CMove
{
public:
	CMove();
	~CMove();
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual int  GetMotion(void) = 0;
};

