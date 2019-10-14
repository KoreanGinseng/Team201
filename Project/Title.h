/*****************************************************************
 *	@file			Title.h
 *	@brief			�^�C�g���V�[���N���X
 *	@author			����D�R
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

