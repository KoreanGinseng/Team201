/*****************************************************************
 *	@file			Kimura.cpp
 *	@brief			キムラシーン実装
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"Kimura.h"


/*****************************************************************
 * @fn
 * 引数なしコンストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CKimura::CKimura() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * 引数なしデストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CKimura::~CKimura() {
	Release();
}

/*****************************************************************
 * @fn
 * 必要な素材の読み込み
 * @param なし
 * @return なし
 *****************************************************************/
void CKimura::Load() {

	m_BackTexture.Load("TestKimura.png");

}

/*****************************************************************
 * @fn
 * 初期化
 * @param なし
 * @return なし
 *****************************************************************/
void CKimura::Initialize() {


	Load();

	m_bEnd = false;

	m_NowScene = /*SCENENO_GAME*/6;
	m_NextScene = /*SCENENO_GAME*/6;

	m_Effect = { 255,0,0 };

	m_Player.Load();

	m_Player.Initialize();

}

/*****************************************************************
 * @fn
 * 更新
 * @param なし
 * @return なし
 *****************************************************************/
void CKimura::Update() {

	EffectUpdate(EFFECTNO_1);

	if (g_pInput->GetGamePadCount()) {

		if (g_pGamePad->IsKeyPush(GAMEKEY_B)) {

			m_NowScene = 8;

		}
	}

	m_Player.Update();

}

/*****************************************************************
 * @fn
 * 描画
 * @param なし
 * @return なし
 *****************************************************************/
void CKimura::Render() {

	m_BackTexture.Render(0, 0, MOF_ARGB(m_Effect.Alpha, 255, 255, 255));

	EffectRender(EFFECTNO_1);

	m_Player.Render();

	RenderDebug();
}

/*****************************************************************
 * @fn
 * デバッグ描画
 * @param なし
 * @return なし
 *****************************************************************/
void CKimura::RenderDebug() {

	CGraphicsUtilities::RenderString(0, 0, MOF_XRGB(255,0,0),"KimuraScene Bボタンで画面遷移");

}

/*****************************************************************
 * @fn
 * 解放
 * @param なし
 * @return なし
 *****************************************************************/
void CKimura::Release() {

	m_Player.Release();

}