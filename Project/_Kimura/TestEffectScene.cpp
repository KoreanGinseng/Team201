#include		"TestEffectScene.h"

CTestEffectScene::CTestEffectScene() : CSceneBase() {



}

CTestEffectScene::~CTestEffectScene() {


}

void CTestEffectScene::Load() {

	m_BackTexture.Load("TestEffectScene.jpg");

}

void CTestEffectScene::Initialize() {
	Load();

	m_bEnd = false;
	m_NowScene = /*SCENENO_GAME*/8;
	m_NextScene = /*SCENENO_GAME*/8;

	m_Effect = { 0,0,0 };

}

void CTestEffectScene::Update() {

	EffectUpdate(EFFECTNO_2);

	if (g_pInput->GetGamePadCount()) {

		if (g_pGamePad->IsKeyPush(GAMEKEY_B)) {

			m_NowScene = 7;

		}
	}

}

void CTestEffectScene::Render() {

	m_BackTexture.Render(0, 0);

	EffectRender(EFFECTNO_2);

	RenderDebug();


}

void CTestEffectScene::RenderDebug() {

	CGraphicsUtilities::RenderString(0, 0,MOF_XRGB(0,255,0),"TestEffectScene Bƒ{ƒ^ƒ“‚Å‰æ–Ê‘JˆÚ");

}

void CTestEffectScene::Release() {

	m_BackTexture.Release();

}
