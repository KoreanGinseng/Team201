/*****************************************************************
 *	@file			SceneBase.h
 *	@brief			シーンベースクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

// INCLUDE
#include	"Mof.h"
#include	"EffectFade.h"

class CSceneBase
{
protected:
	bool m_bEnd;
	int  m_NextSceneNo;
	int	 m_SceneNo;
	CSceneEffectBase* m_pEffect;
public:
	CSceneBase();
	virtual ~CSceneBase();
	bool	EffectFrame(void) { return m_pEffect->Frame(); }
	bool	EffectRender(void) { return m_pEffect->Render(); }
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void RenderDebug() = 0;
	virtual void Release() = 0;
	virtual int GetSceneName(void) = 0;

	bool IsEnd(void) const { return m_bEnd; }
	bool IsSceneEnd(void) const { return m_pEffect->IsEnd(); }
	int  GetNextSceneNo(void) const { return m_NextSceneNo; }
};

