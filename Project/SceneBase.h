/*****************************************************************
 *	@file			SceneBase.h
 *	@brief			シーンベースクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

// INCLUDE
#include	"Mof.h"

class CSceneBase
{
protected:
	bool m_bEnd;
	int  m_NextSceneNo;
public:
	CSceneBase();
	virtual ~CSceneBase();
	virtual bool Load() = 0;
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void RenderDebug() = 0;
	virtual void Release() = 0;
	virtual int GetSceneName(void) = 0;

	bool IsEnd() { return m_bEnd; }
	int  GetNextSceneNo() { return m_NextSceneNo; }
};

