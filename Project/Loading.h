#pragma once
#include	"Mof.h"
#include	"EffectManager.h"
#include	"ResourceManager.h"
#include	"SoundManager.h"
#include	"TimeManager.h"

typedef bool(*BOOLPOINTER)(void);
typedef void(*VOIDPOINTER)(void);

class CLoading : public CThread
{
private:
	bool	m_bEnd;
	bool    (*pload)();
	void    (*pinit)();
	void Load(void);
	void Initialize(void);

public:
	CLoading(void);
	~CLoading(void);
	void Run(void);
	bool IsEnd(void) const { return m_bEnd; }
	void SetLoad(BOOLPOINTER pl) { pload = pl; }
	void SetInit(VOIDPOINTER pi) { pinit = pi; }
};

