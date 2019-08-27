/*****************************************************************
 *	@file			Game.cpp
 *	@brief			ゲームシーン実装
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"Game.h"
#include	"../Coordinate.h"

char*		g_StageFileName[STAGE_COUNT] = {
			"testMap.txt",
			"testMap2-2.txt",
			"testMap3.txt",
};

/*****************************************************************
 * @fn
 * 引数なしコンストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CGame::CGame() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * 引数なしデストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CGame::~CGame() {
	Release();
}

/*****************************************************************
 * @fn
 * 必要な素材の読み込み
 * @param なし
 * @return なし
 *****************************************************************/
void CGame::Load() {
	for (int i = 0; i < STAGE_COUNT; i++) {
		m_Stage[i].Load(g_StageFileName[i]);
	}
	m_Player.Load();
}

/*****************************************************************
 * @fn
 * 初期化
 * @param なし
 * @return なし
 *****************************************************************/
void CGame::Initialize() {
	m_StageNo = 0;
	for (int i = 0; i < STAGE_COUNT; i++) {
		m_Stage[i].Initialize();
	}
	m_Player.Initialize();
}

/*****************************************************************
 * @fn
 * 更新
 * @param なし
 * @return なし
 *****************************************************************/
void CGame::Update() {

	m_Player.Update();

	if (m_Player.GetPos() != m_MainCamera.GetScroll())
	{
		Vector2 d = m_Player.GetPos() - m_MainCamera.GetScroll();
		d /= PLAYER_MAXSPEED * 0.5;
		m_MainCamera.AddScroll(d);
	}

	m_Stage[m_StageNo].Update();

	// Oキーでステージ変更
	if (g_pInput->IsKeyPush(MOFKEY_O)) {
		m_StageNo++;
		if (m_StageNo >= STAGE_COUNT) {
			m_StageNo = 0;
		}
	}

	// スペースキーでフルスクリーンに変換
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		g_pGraphics->ChangeScreenMode();
	}

	// ESCAPEキーで終了
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
		PostQuitMessage(0);
	}
}

/*****************************************************************
 * @fn
 * 描画
 * @param なし
 * @return なし
 *****************************************************************/
void CGame::Render() {
	m_Stage[m_StageNo].Render(m_MainCamera.GetScroll());
	
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), Vector2(m_Player.GetPos().x, -m_Player.GetPos().y));
	m_Player.Render(screenPos);
}

/*****************************************************************
 * @fn
 * デバッグ描画
 * @param なし
 * @return なし
 *****************************************************************/
void CGame::RenderDebug() {

}

/*****************************************************************
 * @fn
 * 解放
 * @param なし
 * @return なし
 *****************************************************************/
void CGame::Release() {
	for (int i = 0; i < STAGE_COUNT; i++)
	{
		m_Stage[i].Release();
	}
	m_Player.Release();
}