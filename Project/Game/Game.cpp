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

	Vector2 o;
	if (m_Stage[m_StageNo].Collision(m_Player.GetRect(), o))
	{
		m_Player.CollisionStage(o);
	}

	Vector2 centerPos = m_Player.GetPos()
		- Vector2(g_pGraphics->GetTargetWidth() / 2,
				  g_pGraphics->GetTargetHeight() / 2 + 180) + m_Player.GetMove2();

	if (centerPos != m_MainCamera.GetScroll())
	{
		Vector2 d = centerPos - m_MainCamera.GetScroll();
		d /= PLAYER_MAXSPEED;
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
	
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
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