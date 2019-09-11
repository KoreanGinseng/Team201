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
			"testMap7-7.txt",
			"testMap7-7.txt",
			"testMap7-7.txt",
};

/*****************************************************************
 * @fn
 * 引数なしコンストラクタ
 * @param なし
 * @return なし
 *****************************************************************/
CGame::CGame() :
CSceneBase(),
m_StageNo(0){
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
	m_Stage[m_StageNo].Load(g_StageFileName[m_StageNo]);
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage[m_StageNo].GetEnemyCount()];
	//アイテムメモリ確保
	m_ItemArray = new CItem[m_Stage[m_StageNo].GetItemCount()];
	//オブジェクトメモリ確保
	m_pObjArray = new CObject[m_Stage[m_StageNo].GetObjectCount()];
	m_Player.Load();
}

/*****************************************************************
 * @fn
 * 初期化
 * @param なし
 * @return なし
 *****************************************************************/
void CGame::Initialize() {
	m_Stage[m_StageNo].Initialize(m_EnemyArray, m_ItemArray, m_pObjArray);
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

	Vector2 o(0, 0);
	if (m_Stage[m_StageNo].Collision(m_Player.GetRect(), o))
	{
		m_Player.CollisionStage(o);
	}

	//敵の更新
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update();
		Vector2 eo(0, 0);
		if (m_Stage[m_StageNo].Collision(m_EnemyArray[i].GetRect(), eo))
		{
			m_EnemyArray[i].CollisionStage(eo);
		}
	}
	//アイテムの更新
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		Vector2 io(0, 0);
		if (m_Stage[m_StageNo].Collision(m_ItemArray[i].GetRect(), io))
		{
			m_ItemArray[i].CollisionStage(io);
		}
	}
	//オブジェクトの更新
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		if (!m_pObjArray[i].GetShow())
		{
			continue;
		}
		m_pObjArray[i].Update();
	}

	Vector2 centerPos = m_Player.GetPos() - Vector2(g_pGraphics->GetTargetWidth() / 2, 0) + m_Player.GetMove2();

	if (centerPos != m_MainCamera.GetScroll())
	{
		Vector2 d = centerPos - m_MainCamera.GetScroll();
		d.x /= PLAYER_MAXSPEED;
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
		if ((m_MainCamera.GetCameraRect().Bottom < m_Stage[m_StageNo].GetStageRect().Bottom && screenPos.y > 580) ||
			(m_Stage[m_StageNo].GetStageRect().Top < m_MainCamera.GetCameraRect().Top && screenPos.y < 180))
		{
			d.y /= PLAYER_MAXSPEED;
		}
		else
		{
			d.y = 0;
		}
		if (m_Stage[m_StageNo].GetStageRect().Bottom < m_MainCamera.GetCameraRect().Bottom)
		{
			m_MainCamera.SetScrollY(m_Stage[m_StageNo].GetStageRect().Bottom - g_pGraphics->GetTargetHeight());
			d.y = 0;
		}
		if (m_Stage[m_StageNo].GetStageRect().Top > m_MainCamera.GetCameraRect().Top)
		{
			m_MainCamera.SetScrollY(0);
			d.y = 0;
		}
		
		m_MainCamera.AddScroll(d);
	}

	m_Stage[m_StageNo].Update();

	// Oキーでステージ変更
	if (g_pInput->IsKeyPush(MOFKEY_O)) {
		Release();
		if (++m_StageNo >= STAGE_COUNT) {
			m_StageNo = 0;
		}
		Load();
		Initialize();
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

	//敵の描画
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_EnemyArray[i].GetPos());
		m_EnemyArray[i].Render(screenPos);
	}
	//アイテムの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_ItemArray[i].GetPos());
		m_ItemArray[i].Render(screenPos);
	}
	//オブジェクトの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pObjArray[i].GetPos());
		m_pObjArray[i].Render(screenPos);
	}

	CGraphicsUtilities::RenderString(0, 30, "%.1f,%.1f", m_MainCamera.GetScroll().x, m_MainCamera.GetScroll().y);
}

/*****************************************************************
 * @fn
 * デバッグ描画
 * @param なし
 * @return なし
 *****************************************************************/
void CGame::RenderDebug() {
	m_Stage[m_StageNo].RenderDebug(m_MainCamera.GetScroll());

	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.RenderDebug();

	//敵の描画
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_EnemyArray[i].GetPos());
		m_EnemyArray[i].RenderDebug(screenPos);
	}
	//アイテムの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_ItemArray[i].GetPos());
		m_ItemArray[i].RenderDebug(screenPos);
	}
	//オブジェクトの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pObjArray[i].GetPos());
		m_pObjArray[i].RenderDebug(screenPos);
	}
}

/*****************************************************************
 * @fn
 * 解放
 * @param なし
 * @return なし
 *****************************************************************/
void CGame::Release() {

	m_Stage[m_StageNo].Release();
	
	//敵の解放
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//アイテムの解放
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//オブジェクトの開放
	if (m_pObjArray)
	{
		delete[] m_pObjArray;
		m_pObjArray = NULL;
	}
	m_Player.Release();
}