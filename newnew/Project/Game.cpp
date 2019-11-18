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
			"Stage1-1.txt",
			"Stage1-1.txt",
			"Stage1-1.txt",
			"Stage1-1.txt",
};

//コンストラクタ
CGame::CGame() :
	CSceneBase(),
	m_bPoase(false),
	m_pEnemyArray(),
	m_pItemArray(),
	m_pTargetObjArray()
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
	m_pEffect = NEW CEffectFade();
	m_pEffect->In(10);

	if (!m_Stage[m_StageNo].Load(g_StageFileName[m_StageNo]))
	{
		return FALSE;
	}
	//敵メモリ確保
	CEnemy* tmp_e = NEW CEnemy;
	m_pEnemyArray.SetArray(&tmp_e, m_Stage[m_StageNo].GetEnemyCount());
	delete tmp_e;
	//アイテムメモリ確保
	CItem* tmp_i = NEW CItem;
	m_pItemArray.SetArray(&tmp_i, m_Stage[m_StageNo].GetItemCount());
	delete tmp_i;
	//オブジェクトメモリ確保
	CTargetObj* tmp_t = NEW CTargetObj;
	m_pTargetObjArray.SetArray(&tmp_t, m_Stage[m_StageNo].GetObjectCount());
	delete tmp_t;

	return TRUE;
}

//初期化
void CGame::Initialize()
{
	//遷移先の初期化
	m_NextSceneNo = SCENENO_GAME;

	//ステージの初期化
	m_Stage[m_StageNo].Initialize(&m_pEnemyArray, &m_pItemArray, &m_pTargetObjArray);

	//プレイヤーの初期化
	m_Player.Initialize();
	//ゲーム開始時間リセット
	g_pTimeManager->Reset();
}

//更新
void CGame::Update()
{

	//ゲームオーバーへ
	if (m_Player.IsDead() && !IsStart())
	{
		m_pEffect->Out(10);
		m_NextSceneNo = SCENENO_GAMEOVER;
	}

	//デバッグ用
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
		//m_Player.SkillColision(m_pEnemyArray, m_Stage[m_StageNo].GetEnemyCount(), m_pObjArray, m_Stage[m_StageNo].GetObjectCount());
		m_Player.TargetSelect(&m_pEnemyArray, &m_pTargetObjArray, &m_pItemArray);
	}

	//プレイヤーの更新
	m_Player.Update();

	Vector2 o(0, 0);
	//プレイヤーとステージの当たり判定
	if (m_Stage[m_StageNo].OverValue(m_Player.GetRect(), o))
	{
		m_Player.CollisionStage(o);
	}

	//敵の更新
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		if (!m_pEnemyArray[i]->IsShow() || !m_pEnemyArray[i]->IsDead())
		{
			continue;
		}
		//m_pEnemyArray[i]->Update(m_Player.GetPos());
		m_pEnemyArray[i]->Update();
	}

	//当たり判定
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		if (!m_pEnemyArray[i]->IsShow() || !m_pEnemyArray[i]->IsDead())
		{
			continue;
		}
		Vector2 eo(0, 0);
		for (int j = 0; i < m_pEnemyArray[i]->GetSrcRectArray().GetArrayCount(); j++)
		{
			if (m_Stage[m_StageNo].OverValue(m_pEnemyArray[i]->GetRectArray(j), eo))
			{
				m_pEnemyArray[i]->CollisionStage(eo);
			}
			if (m_pEnemyArray[i]->OverValue(m_Player.GetRectArray(i), o))
			{
				if (m_pEnemyArray[i]->IsSkill())
				{
					m_Player.CollisionStage(o);
				}
				else
				{
					m_Player.Dmg(*m_pEnemyArray[i]);
				}
			}
		}
	}

	//アイテムの更新
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		if (!m_pItemArray[i]->IsShow())
		{
			continue;
		}
		m_pItemArray[i]->Update();
	}
	//当たり判定
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		for (int j = 0; j < m_pItemArray[i]->GetSrcRectArray().GetArrayCount(); j++)
		{
			Vector2 io(0, 0);
			if (m_Stage[m_StageNo].OverValue(m_pItemArray[i]->GetRectArray(j), io))
			{
				if (!m_pItemArray[i]->IsShow())
				{
					continue;
				}
				m_pItemArray[i]->CollisionStage(io);
			}
		}
	}
	//オブジェクトの更新
	bool clime = false;
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		if (!m_pTargetObjArray[i]->IsShow())
		{
			continue;
		}
		m_pTargetObjArray[i]->Update();
	}

	//当たり判定
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		if (!m_pTargetObjArray[i]->IsShow())
		{
			continue;
		}
		Vector2 oo(0, 0);
		//プレイヤーとの当たり判定
		oo = Vector2(0, 0);
		if (m_pTargetObjArray[i]->OverValue(m_Player.GetRect(), oo))
		{
			if (m_pTargetObjArray[i]->GetObjType() == OBJECT_ROPE)
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
			if (m_pTargetObjArray[i]->OverValue(m_pEnemyArray[j]->GetRect(), oo))
			{
				if (m_pTargetObjArray[i]->GetObjType() == OBJECT_ROPE)
				{
					continue;
				}
				else
				{
					m_pEnemyArray[j]->CollisionStage(oo);
				}
			}
		}
	}
	m_Player.SetClime(clime);

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
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pEnemyArray[i]->GetPos());
		m_pEnemyArray[i]->Render(screenPos);
	}
	//アイテムの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pItemArray[i]->GetPos());
		m_pItemArray[i]->Render(screenPos);
	}
	//オブジェクトの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pTargetObjArray[i]->GetPos());
		m_pTargetObjArray[i]->Render(screenPos);
	}

	//ポーズ中ならポーズ画面の描画
	if (m_bPoase)
	{
		//ゲーム画面が灰色になるやつ
		CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(128, 128, 128, 128));
	}
}

void CGame::RenderUI(void)
{
	String(1600, 0, 128, g_pTimeManager->GetNowTime());
}

void CGame::UpdateDebug() {

	

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !IsStart()) {
		g_pScore->TotalScore(g_pTimeManager->GetNowTime());
		m_pEffect->Out(10);
		m_NextSceneNo = SCENENO_GAMEOVER;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_L) && !IsStart()) {
		m_pEffect->Out(10);
		m_NextSceneNo = SCENENO_GAMECLEAR;
	}
}
//デバッグ描画
void CGame::RenderDebug()
{
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.RenderDebug(screenPos);
	
	//CGraphicsUtilities::RenderString(0, 30, "%.1f,%.1f", m_MainCamera.GetScroll().x, m_MainCamera.GetScroll().y);
}

//解放
void CGame::Release()
{
	NewPointerRelease(m_pEffect);
	m_Stage[m_StageNo].Release();

	//敵の解放
	m_pEnemyArray.Release();
	//アイテムの解放
	m_pItemArray.Release();
	//オブジェクトの開放
	m_pTargetObjArray.Release();

	m_Player.Release();
}