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
	~CTitle() override;
	bool Load() override;
	void Initialize() override;
	void Update() override;
	void Render() override;
	void RenderUI() override;
	void RenderDebug() override;
	void Release() override;

	void UpdateDebug();

	int GetSceneName(void) { return SCENENO_TITLE; }
};

