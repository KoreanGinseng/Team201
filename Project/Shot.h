#pragma once
#include	"GameDefine.h"
#include	"Substance.h"

class CShot : public CSubstance
{
private:
protected:

public:
	CShot();
	virtual ~CShot();
	virtual void Fire(const Vector2& startPos) = 0;
};

