#pragma once
#include	"Mof.h"
#include	"GameDefine.h"
#include	"SceneBase.h"
#include	"EffectManager.h"

class CLoading : public CThread
{
private:
	bool	m_bEnd;
	CSceneBase*	m_pScene;
public:
public:
	CLoading(void);
	~CLoading(void);
	void Run(void);
	void Render(void);
	bool IsEnd(void) const { return m_bEnd; }
	void SetScene(CSceneBase* ps) { m_pScene = ps; }
private:
	void Load(void);
	void Initialize(void);
};
