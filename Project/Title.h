/*****************************************************************
 *	@file			Title.h
 *	@brief			タイトルシーンクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

 // INCLUDE
#include "SceneBase.h"
#include	"GameDefine.h"

class CTitle :
	public CSceneBase
{
private:

public:
	CTitle();
	~CTitle();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release();
	int GetSceneName(void) { return SCENENO_TITLE; }
};

