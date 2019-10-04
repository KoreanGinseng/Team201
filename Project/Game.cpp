/*****************************************************************
 *	@file			Game.cpp
 *	@brief			ゲームシーンクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/

// INCLUDE
#include "Game.h"

char*		g_StageFileName[STAGE_COUNT] = {
			"testMap1-1.txt",
			"testMap1-1.txt",
			"testMap1-1.txt",
};

//コンストラクタ
CGame::CGame() :
CSceneBase(),
m_StageNo(START_STAGE),
m_bPoase(false)
{
}

//デストラクタ
CGame::~CGame()
{
}

//読み込み
bool CGame::Load()
{
	if (!m_Stage[m_StageNo].Load(g_StageFileName[m_StageNo]))
	{
		return FALSE;
	}
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage[m_StageNo].GetEnemyCount()];
	//アイテムメモリ確保
	m_ItemArray = new CItem[m_Stage[m_StageNo].GetItemCount()];
	//オブジェクトメモリ確保
	m_pObjArray = new CObject[m_Stage[m_StageNo].GetObjectCount()];
	return TRUE;
}

//初期化
void CGame::Initialize()
{
	m_Stage[m_StageNo].Initialize(m_EnemyArray, m_ItemArray, m_pObjArray);
	m_Player.Initialize();
	g_pTimeManager->Reset();
}

//更新
void CGame::Update()
{
	//F4キーでポーズ
	if (g_pInput->IsKeyPush(MOFKEY_F4)) {
		m_bPoase = !m_bPoase;
	}

	// ESCAPEキーで終了
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
		PostQuitMessage(0);
	}

	//ポーズ中ならポーズ画面の更新のみする
	if (m_bPoase) {

		return;
	}

	//プレイヤーの更新
	m_Player.Update();

	Vector2 o(0, 0);
	//プレイヤーとステージの当たり判定
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
		m_EnemyArray[i].Update(m_Player.GetPos());
		//当たり判定
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
		//当たり判定
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
		//当たり判定
		Vector2 oo(0, 0);
		if (m_Stage[m_StageNo].Collision(m_pObjArray[i].GetRect(), oo))
		{
			m_pObjArray[i].CollisionStage(oo);
		}
	}

	//カメラの更新
	Vector2 centerPos = m_Player.GetPos() - Vector2(g_pGraphics->GetTargetWidth() / 2, 180) + (m_Player.GetSpd() + Vector2(0.1f, 0.1f));
	m_MainCamera.Update(centerPos, m_Player.GetRect(), m_Stage[m_StageNo].GetStageRect());

	//ステージの更新
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

	//ゲーム時間を加算
	g_pTimeManager->Tick();
}

//描画
void CGame::Render()
{
	//ステージの描画
	m_Stage[m_StageNo].Render(m_MainCamera.GetScroll());

	//プレイヤーの描画
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

	//ポーズ中ならポーズ画面の描画
	if (m_bPoase)
	{
		//ゲーム画面が灰色になるやつ
		CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(128, 128, 128, 128));
	}
}

//デバッグ描画
void CGame::RenderDebug()
{
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.RenderDebug(screenPos);
	String(1600, 0, 128, g_pTimeManager->GetNowTime());
	CGraphicsUtilities::RenderString(0, 30, "%.1f,%.1f", m_MainCamera.GetScroll().x, m_MainCamera.GetScroll().y);
}

//解放
void CGame::Release()
{
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