/*****************************************************************
 *	@file			Game.cpp
 *	@brief			ゲームシーンクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/

// INCLUDE
#include "Game.h"

int CGame::m_StageNo = START_STAGE;

const char*		g_StageFileName[STAGE_COUNT] = {
			"TestStage1-1.txt",
			"Stage1-1.txt",
			"Stage1-1.txt",
			"Stage1-1.txt",
};

//コンストラクタ
CGame::CGame() :
	CSceneBase(),
	m_bPoase(false),
	m_pEnemyArray(nullptr),
	m_pItemArray(nullptr),
	m_pObjArray(nullptr)
{
}

//デストラクタ
CGame::~CGame()
{
}

//読み込み
bool CGame::Load()
{
	//シーンエフェクトスタート
	m_pEffect = new CEffectFade();
	m_pEffect->In(10);

	if (!m_Stage[m_StageNo].Load(g_StageFileName[m_StageNo]))
	{
		return FALSE;
	}
	//敵メモリ確保
	m_pEnemyArray = new CEnemy[m_Stage[m_StageNo].GetEnemyCount()];
	//アイテムメモリ確保
	m_pItemArray = new CItem[m_Stage[m_StageNo].GetItemCount()];
	//オブジェクトメモリ確保
	m_pObjArray = new CObject[m_Stage[m_StageNo].GetObjectCount()];
	return TRUE;
}

void CGame::SaveLoad() {

	//セーブポイントに値が入っている場合セットする
	if (gSavePos.x&&gSavePos.y) {

		m_Player.SetPos(gSavePos);

	}

}

//初期化
void CGame::Initialize()
{
	//終了フラグの初期化
	m_bEnd = false;
	//遷移先の初期化
	m_NextSceneNo = SCENENO_GAME;
	m_Stage[m_StageNo].Initialize(m_pEnemyArray, m_pItemArray, m_pObjArray);
	m_Player.Initialize();
	//セーブポイントの座標をロードする
	SaveLoad();
	g_pTimeManager->Reset();
}

//更新
void CGame::Update()
{

	//
	if (ReNum::GetInstance().GetReNumber() < 0 && !m_bEnd)
	{
		m_bEnd = true;
		m_pEffect->Out(10);
		m_NextSceneNo = SCENENO_GAMEOVER;
	}

	UpdateDebug();

	//F4キーでポーズ
	if (g_pInput->IsKeyPush(MOFKEY_F4))
	{
		m_bPoase = !m_bPoase;
	}

	// ESCAPEキーで終了
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
	{
		PostQuitMessage(0);
	}

	//ポーズ中ならポーズ画面の更新のみする
	if (m_bPoase)
	{
		return;
	}


	//プレイヤーがスキル発動時の場合、
	if (m_Player.IsTrigger())
	{
		m_Player.SkillColision(m_pEnemyArray, m_Stage[m_StageNo].GetEnemyCount(), m_pObjArray, m_Stage[m_StageNo].GetObjectCount());
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
		if (!m_pEnemyArray[i].GetShow())
		{
			continue;
		}
		m_pEnemyArray[i].Update(m_Player.GetPos());
		//当たり判定
		Vector2 eo(0, 0);
		if (m_Stage[m_StageNo].Collision(m_pEnemyArray[i].GetRect(), eo))
		{
			m_pEnemyArray[i].CollisionStage(eo);
		}
		if (m_pEnemyArray[i].Collision(m_Player.GetRect(), o))
		{
			if (m_pEnemyArray[i].IsSkill())
			{
				m_Player.CollisionStage(o);
			}
			else
			{
				m_Player.Dmg(m_pEnemyArray[i]);
			}
		}
	}
	//アイテムの更新
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		if (!m_pItemArray[i].GetShow())
		{
			continue;
		}
		m_pItemArray[i].Update();
		//当たり判定
		Vector2 io(0, 0);
		if (m_Stage[m_StageNo].Collision(m_pItemArray[i].GetRect(), io))
		{
			m_pItemArray[i].CollisionStage(io);
		}
	}
	//オブジェクトの更新
	bool clime = false;
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		//非表示かつ出現していなかったら処理を飛ばす
		if (!m_pObjArray[i].GetShow()&&!m_pObjArray[i].IsAppearance())
		{
			continue;
		}
		m_pObjArray[i].Update();
		//当たり判定
		Vector2 oo(0, 0);
		if (m_Stage[m_StageNo].Collision(m_pObjArray[i].GetRect(), oo))
		{
			//m_pObjArray[i].CollisionStage(oo);
		}
		//プレイヤーとの当たり判定
		oo = Vector2(0, 0);
		if (m_pObjArray[i].Collision(m_Player.GetRect(), oo))
		{
			if (m_pObjArray[i].GetType() == OBJECT_ROPE)
			{
				clime = true;
				break;
			}
			else
			{
				clime = false;
				m_Player.CollisionStage(oo);
			}
		}
		for (int j = 0; j < m_Stage[m_StageNo].GetEnemyCount(); j++)
		{
			oo = Vector2(0, 0);
			if (m_pObjArray[i].Collision(m_pEnemyArray[j].GetRect(), oo))
			{
				if (m_pObjArray[i].GetType() == OBJECT_ROPE)
				{
					continue;
				}
				else
				{
					m_pEnemyArray[j].CollisionStage(oo);
				}
			}
		}
	}
	m_Player.SetClime(clime);

	//オブジェクトの出現
	ObjectAppearance();

	//プレイヤーの座標を保存する
	PlayerSave();

	//カメラの更新
	Vector2 centerPos = m_Player.GetPos() - Vector2(g_pGraphics->GetTargetWidth() / 2, 180) + (m_Player.GetSpd() + Vector2(0.1f, 0.1f));
	m_MainCamera.Update(centerPos, m_Player.GetRect(), m_Stage[m_StageNo].GetStageRect());

	//ステージの更新
	m_Stage[m_StageNo].Update();

	//ゲーム時間を加算
	g_pTimeManager->Tick();
}

//描画
void CGame::Render()
{

	//goriosi
	g_pTextureManager->GetResource("空.png")->Render(0, 0);

	//ステージの描画
	m_Stage[m_StageNo].Render(m_MainCamera.GetScroll());

	//プレイヤーの描画
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.Render(screenPos);

	//敵の描画
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pEnemyArray[i].GetPos());
		m_pEnemyArray[i].Render(screenPos);
	}
	//アイテムの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pItemArray[i].GetPos());
		m_pItemArray[i].Render(screenPos);
	}
	//オブジェクトの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		//オブジェクトが出現していない場合、描画しない
		if (!m_pObjArray[i].IsAppearance()) {

			continue;
		}

		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pObjArray[i].GetPos());
		m_pObjArray[i].Render(screenPos);
	}

	//
	m_UI.Render(m_Player.GetHp());

	//ポーズ中ならポーズ画面の描画
	if (m_bPoase)
	{
		//ゲーム画面が灰色になるやつ
		CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(128, 128, 128, 128));
	}
}

void CGame::UpdateDebug() {


	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd) {

		g_pScore->TotalScore((int)g_pTimeManager->GetNowTime());
		m_bEnd = true;
		m_pEffect->Out(10);
		m_SceneNo = SCENENO_GAMEOVER;


	}
	else if (g_pInput->IsKeyPush(MOFKEY_L)) {

		m_bEnd = true;

		m_pEffect->Out(10);

		m_SceneNo = SCENENO_GAMECLEAR;

	}
	if (m_pEffect->IsEnd() && m_bEnd&&m_SceneNo!=-1) {

		m_NextSceneNo = m_SceneNo;

	}
}

//オブジェクトの出現
void CGame::ObjectAppearance() {

	Vector2 screen = Vector2(g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight());

	for (int i = 0; i < m_Stage->GetObjectCount(); i++) {

		//出現フラグが立っている場合、飛ばす
		if (m_pObjArray[i].IsAppearance()) {

			continue;

		}

		//画面内に入ったら出現フラグを立てる
		if (m_pObjArray[i].GetPos().x - m_MainCamera.GetScroll().x < g_pGraphics->GetTargetWidth()&&
			m_pObjArray[i].GetPos().y - m_MainCamera.GetScroll().y < g_pGraphics->GetTargetHeight()) {

			m_pObjArray[i].SetAppearance(true);

		}

	}

}

void CGame::PlayerSave() {

	for (int i = 0; i < m_Stage->GetObjectCount(); i++) {

		//出現していないかつセーブオブジェクトではない場合、飛ばす
		if (!m_pObjArray[i].IsAppearance()||m_pObjArray[i].GetType()!=OBJECT_SAVE) {

			continue;

		}

		//すでに通過済みの場合、飛ばす
		if (m_pObjArray[i].IsSave()) {

			continue;

		}

		//プレイヤーがセーブポイントに達したとき、セーブポイントの座標を保存する
		if (m_Player.GetPos().x > m_pObjArray[i].GetPos().x) {

			gSavePos = m_pObjArray[i].GetPos();
			m_pObjArray[i].SetSave(true);

		}

	}

}
//デバッグ描画
void CGame::RenderDebug()
{
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.RenderDebug(screenPos);
	//敵の描画
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pEnemyArray[i].GetPos());
		m_pEnemyArray[i].RenderDebug(screenPos);
	}
	//オブジェクトの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pObjArray[i].GetPos());
		m_pObjArray[i].RenderDebug(screenPos);
		CGraphicsUtilities::RenderString(i * 30, 0, "%d", m_pObjArray[i].IsAppearance());
	}
	String(1600, 0, 128, g_pTimeManager->GetNowTime());
	//CGraphicsUtilities::RenderString(0, 30, "%.1f,%.1f", m_MainCamera.GetScroll().x, m_MainCamera.GetScroll().y);
}

//解放
void CGame::Release()
{
	if (m_pEffect) {

		delete m_pEffect;

		m_pEffect = nullptr;
	}
	m_Stage[m_StageNo].Release();

	//敵の解放
	if (m_pEnemyArray != nullptr)
	{
		delete[] m_pEnemyArray;
		m_pEnemyArray = NULL;
	}
	//アイテムの解放
	if (m_pItemArray != nullptr)
	{
		delete[] m_pItemArray;
		m_pItemArray = NULL;
	}
	//オブジェクトの開放
	if (m_pObjArray != nullptr)
	{
		delete[] m_pObjArray;
		m_pObjArray = NULL;
	}
	m_Player.Release();

}