#pragma once

#include	"../SceneBase.h"
//#include	"../Project/GameDefine.h"
#include	"GamePad.h"

class CTestEffectScene : public CSceneBase{

private:
public:
	CTestEffectScene();
	~CTestEffectScene();
	void	Load(void);
	void	Initialize(void);
	void	Update(void);
	void	Render(void);
	void	RenderDebug(void);
	void	Release(void);
};