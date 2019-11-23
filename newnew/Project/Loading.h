#pragma once
#include	"Mof.h"
#include	"GameDefine.h"
#include	"SceneBase.h"
#include	"EffectManager.h"

class CLoading : public CThread
{
private:
	bool	m_bEnd;
	bool	m_bStart;
	int		m_Count;
	int		m_CountMax;
	CString m_Message;
	CSceneBase*	m_pScene;
	bool	m_bStartUp;
public:
public:
	CLoading(void);
	~CLoading(void);
	void Run(void);
	void Render(void);
	void SceneStart(void) { m_bStart = true; }
	bool IsEnd(void) const { return m_bEnd; }
	bool IsSceneStart(void) const { return m_bStart; }
	void SetScene(CSceneBase* ps) { m_pScene = ps; }
	void SetStartUp(const bool& b) { m_bStartUp = b; }
private:
	void Load(void);
	void Initialize(void);
};

