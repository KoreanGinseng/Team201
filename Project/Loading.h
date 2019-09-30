#pragma once
#include	"Mof.h"
#include	"EffectManager.h"
#include	"ResourceManager.h"
#include	"SoundManager.h"
#include	"TimeManager.h"

class CLoading : public CThread
{
private:
	bool	m_bEnd;

	void Load(void);
	void Initialize(void);

public:
	CLoading(void);
	~CLoading(void);
	void Run(void);
	bool IsEnd(void) const { return m_bEnd; }
};

