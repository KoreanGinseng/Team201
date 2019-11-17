/*****************************************************************
 *	@file			SceneBase.h
 *	@brief			�V�[���x�[�X�N���X
 *	@author			����D�R
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

// INCLUDE
#include	"Mof.h"
#include	"SceneEffectBase.h"

class CSceneBase
{
protected:
	int  m_NextSceneNo;
	CSceneEffectBase* m_pEffect;
public:
	CSceneBase() {}
	virtual ~CSceneBase() {}
	bool	EffectFrame(void) { return m_pEffect->Frame(); }
	bool	EffectRender(void) { return m_pEffect->Render(); }
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void RenderUI() = 0;
	virtual void RenderDebug() = 0;
	virtual void Release() = 0;
	virtual int GetSceneName(void) = 0;

	bool IsStart(void) const { return m_pEffect->IsStart(); }
	bool IsEnd(void) const { return m_pEffect->IsEnd(); }
	int  GetNextSceneNo(void) const { return m_NextSceneNo; }
};

