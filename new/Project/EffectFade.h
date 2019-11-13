#pragma once
#include "SceneEffectBase.h"
class CEffectFade :
	public CSceneEffectBase
{
public:
	CEffectFade();
	~CEffectFade();

	bool Out(const int& spd);
	bool In(const int& spd);
	bool Render(void);
};

