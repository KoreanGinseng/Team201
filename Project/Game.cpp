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
			"TestMap1226.txt",
			"TEISHUTSUYOU.txt",
			"ENEMOVESTAGE2.txt",
			"Stage1-a.txt",
};

CTexture tex;
//コンストラクタ
CGame::CGame() :
CSceneBase(),
m_bPoase(false),
m_pEnemyArray(),
m_pItemArray(),
m_pTargetObjArray(),
m_pMapObjArray(),
m_bClear(false)
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
	m_pEnemyArray.ReSize(m_Stage[m_StageNo].GetEnemyCount());
	for (int i = 0; i < m_pEnemyArray.GetArrayCount(); i++)
	{
		m_pEnemyArray.SetData(NEW CEnemy(), i);
	}
	//アイテムメモリ確保
	m_pItemArray.ReSize(m_Stage[m_StageNo].GetItemCount());
	for (int i = 0; i < m_pItemArray.GetArrayCount(); i++)
	{
		m_pItemArray.SetData(NEW CItem(), i);
	}
	//オブジェクトメモリ確保
	m_pTargetObjArray.ReSize(m_Stage[m_StageNo].GetObjectCount());
	for (int i = 0; i < m_pTargetObjArray.GetArrayCount(); i++)
	{
		m_pTargetObjArray.SetData(NEW CTargetObj(), i);
	}
	//マップオブジェクトメモリ確保
	m_pMapObjArray.ReSize(m_Stage[m_StageNo].GetMapObjCount());
	for (int i = 0; i < m_pMapObjArray.GetArrayCount(); i++)
	{
		m_pMapObjArray.SetData(NEW CMapObj(), i);
	}
	//背景チップメモリ確保
	m_pBackChipArray.ReSize(m_Stage[m_StageNo].GetBackChipCount());
	for (int i = 0; i < m_pBackChipArray.GetArrayCount(); i++)
	{
		m_pBackChipArray.SetData(NEW CBackChip(), i);
	}

	if (!tex.CreateTarget(g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), PixelFormat::PIXELFORMAT_R8G8B8A8_UNORM, BufferAccess::BUFFERACCESS_GPUREADWRITE))
	{
		return FALSE;
	}
	return TRUE;
}

//初期化
void CGame::Initialize()
{
	//遷移先の初期化
	m_NextSceneNo = SCENENO_GAME;

	//プレイヤーの初期化
	m_Player.Initialize();

	//ステージの初期化
	m_Stage[m_StageNo].Initialize(&m_pEnemyArray, &m_pItemArray, &m_pTargetObjArray, &m_pMapObjArray, &m_pBackChipArray);

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

	//プレイヤーの更新
	m_Player.Update();
	

	//敵の更新
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		m_pEnemyArray[i]->Update();
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
	
	//オブジェクトの更新
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		if (!m_pTargetObjArray[i]->IsShow())
		{
			continue;
		}
		m_pTargetObjArray[i]->Update();
	}

	//マップオブジェクトの更新
	for (int i = 0; i < m_Stage[m_StageNo].GetMapObjCount(); i++)
	{
		if (!m_pMapObjArray[i]->IsShow())
		{
			continue;
		}
		m_pMapObjArray[i]->Update();
	}

	//マップオブジェクトの更新
	for (int i = 0; i < m_Stage[m_StageNo].GetBackChipCount(); i++)
	{
		if (!m_pBackChipArray[i]->IsShow())
		{
			continue;
		}
		m_pBackChipArray[i]->Update();
	}

	m_Player.SetCntrl(true);
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		if (m_pTargetObjArray[i]->GetObjType() != OBJECT_CAMERACNTRL)
		{
			continue;
		}
		if (!static_cast<CCameraCntrl*>(m_pTargetObjArray[i])->IsCntrl() || static_cast<CCameraCntrl*>(m_pTargetObjArray[i])->IsEndCntrl())
		{
			continue;
		}
		m_Player.SetCntrl(false);
		m_MainCamera.Move(static_cast<CCameraCntrl*>(m_pTargetObjArray[i])->GetMoveType());
		static_cast<CCameraCntrl*>(m_pTargetObjArray[i])->SetEnd(!m_MainCamera.IsStart());
	}
	CCordinate::SetCameraCntrl(m_MainCamera.IsStart());
	if (m_MainCamera.IsBoss())
	{
		CCordinate::SetBossFlag(true);
		m_MainCamera.SetScrollX(m_Stage[m_StageNo].GetStageRect().Right - g_pGraphics->GetTargetWidth());
	}


	//当たり判定
	Collosion();

	//カメラの更新
	Vector2 centerPos = m_Player.GetPos() - Vector2(g_pGraphics->GetTargetWidth() / 2, 180) + (Vector2(PLAYER_SPEED, PLAYER_JUMPPOW) + Vector2(0.1f, 0.1f));
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
	g_pTextureManager->GetTexture("空.png")->Render(0, 0);

	//背景チップのBACKBACK描画
	for (int i = 0; i < m_Stage[m_StageNo].GetBackChipCount(); i++)
	{
		if (m_pBackChipArray[i]->GetRenderType() == RENDER_BACKBACK)
		{
			m_pBackChipArray[i]->RenderBackBack(m_MainCamera.GetScroll());
		}
	}

	//背景チップのBACKSTAGE描画
	for (int i = 0; i < m_Stage[m_StageNo].GetBackChipCount(); i++)
	{
		if (m_pBackChipArray[i]->GetRenderType() == RENDER_BACKSTAGE)
		{
			m_pBackChipArray[i]->RenderBackStage(m_MainCamera.GetScroll());
		}
	}

	//ステージのBACK描画
	m_Stage[m_StageNo].RenderBack(m_MainCamera.GetScroll());

	//マップオブジェクトの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetMapObjCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pMapObjArray[i]->GetPos());
		m_pMapObjArray[i]->Render(screenPos);
	}

	//オブジェクトの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pTargetObjArray[i]->GetPos());
		m_pTargetObjArray[i]->Render(screenPos);
	}

	//ステージのCHIP描画
	m_Stage[m_StageNo].RenderChip(m_MainCamera.GetScroll());

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
	//Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	//m_Player.RenderDebug(screenPos);
	
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
	//マップオブジェクトの解放
	m_pMapObjArray.Release();
	//背景パーツの解放
	m_pBackChipArray.Release();
	m_Player.Release();
}



void CGame::Collosion(void)
{
#pragma region プレイヤーが当たる側
	//プレイヤーがスキル発動時の場合、
	if (m_Player.IsTrigger())
	{
		//m_Player.SkillColision(m_pEnemyArray, m_Stage[m_StageNo].GetEnemyCount(), m_pObjArray, m_Stage[m_StageNo].GetObjectCount());
		m_Player.TargetSelect(&m_pEnemyArray, &m_pTargetObjArray, &m_pItemArray);
	}

	//埋まり値用
	Vector2 over(0, 0);
	//プレイヤーとステージの当たり判定
	if (m_Stage[m_StageNo].OverValue(m_Player.GetRect(), over))
	{
		//埋まっている値だけ元に戻す
		m_Player.CollisionStage(over);
	}
#pragma endregion

#pragma region 敵が当たる側
	//敵との当たり判定
	//敵の数だけループ
	//for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	for (int i = 0; i < m_pEnemyArray.GetArrayCount(); i++)
	{
		//非表示か死亡の場合スキップ
		if (!m_pEnemyArray[i]->IsShow() || m_pEnemyArray[i]->IsDead())
		{
			continue;
		}

		//一体の矩形の数だけループ
		for (int j = 0; j < m_pEnemyArray[i]->GetSrcRectArray().GetArrayCount(); j++)
		{
			//埋まり値の値をリセット
			over = Vector2(0, 0);

			//ステージと埋まりを求める
			if (m_pEnemyArray[i]->IsCollisionFlag() && m_Stage[m_StageNo].OverValue(m_pEnemyArray[i]->GetRectArray(j), over))
			{
				//埋まっているだけ元に戻す
				m_pEnemyArray[i]->CollisionStage(over);
			}

			//埋まり値の値をリセット
			over = Vector2(0, 0);

			//プレイヤーとの埋まりを求める
			if (m_pEnemyArray[i]->OverValue(m_Player.GetRect(), over))
			{
				//敵がスキルで止まっているなら埋まり値だけ戻す
				if (m_pEnemyArray[i]->GetStatus() == SUBSTATUS_STOP)
				{
					m_Player.CollisionStage(over);
				}
				//止まってないならプレイヤーにダメージ
				else
				{
					if (m_pEnemyArray[i]->GetEnemyType() == ENEMY_HAND)
					{
						m_pEnemyArray[i]->KnockBack(m_Player.GetRect(), m_Player.GetDamageWait());
					}
					m_Player.Dmg(*m_pEnemyArray[i]);
				}
			}

			//埋まり値の値をリセット
			over = Vector2(0, 0);

			//他の敵との埋まりを求める
			//for (int k = 0; k < m_Stage[m_StageNo].GetEnemyCount(); k++)
			for (int k = 0; k < m_pEnemyArray.GetArrayCount(); k++)
			{
				if (k == i)
				{
					continue;
				}
				for (int l = 0; l < m_pEnemyArray[k]->GetRectArray().GetArrayCount(); l++)
				{
					if (m_pEnemyArray[i]->IsCollisionFlag() && m_pEnemyArray[k]->IsCollisionFlag() && m_pEnemyArray[i]->OverValue(m_pEnemyArray[k]->GetRectArray(l), over))
					{
						//埋まっているだけ元に戻す
						if (m_pEnemyArray[k]->GetEnemyType() == ENEMY_BOSS_1 || m_pEnemyArray[k]->GetEnemyType() == ENEMY_BOSS_3)
						{
							continue;
						}
						m_pEnemyArray[k]->CollisionStage(over);
						m_pEnemyArray[i]->Reverse(-over);
					}
				}
			}
		}
	}
#pragma endregion

#pragma region アイテムが当たる側
	//アイテムとの当たり判定
	//for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	for (int i = 0; i < m_pItemArray.GetArrayCount(); i++)
	{
		//非表示ならスキップ
		if (!m_pItemArray[i]->IsShow())
		{
			continue;
		}

		//１アイテムの矩形の数だけループ
		for (int j = 0; j < m_pItemArray[i]->GetSrcRectArray().GetArrayCount(); j++)
		{
			//埋まり値のリセット
			over = Vector2(0, 0);

			//ステージとの埋まり値を求める
			if (m_Stage[m_StageNo].OverValue(m_pItemArray[i]->GetRectArray(j), over))
			{
				//埋まっているだけ戻す
				m_pItemArray[i]->CollisionStage(over);
			}
		}
	}
#pragma endregion

#pragma region オブジェクトが当たる側
	//オブジェクトとの当たり判定
	//オブジェクトの数だけ当たり判定をする
	//for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	for (int i = 0; i < m_pTargetObjArray.GetArrayCount(); i++)
	{
		//非表示ならスキップ
		if (!m_pTargetObjArray[i]->IsShow())
		{
			continue;
		}
		//埋まり値をリセット
		over = Vector2(0, 0);
	
		//プレイヤーとの当たり判定
		m_Player.SetClime(false);
		if (m_pTargetObjArray[i]->OverValue(m_Player.GetRect(), over))
		{
			//ぶつかったオブジェクトがロープの場合
			if (m_pTargetObjArray[i]->GetObjType() == OBJECT_ROPE && m_pTargetObjArray[i]->GetStatus() == SUBSTATUS_NOMAL)
			{
				//登れるようにする
				m_Player.SetClime(true);
				break;
			}
			//ロープ以外の場合
			else
			{
				//通常の動きにする
				//スキルが使われている状態なら当たり判定を行わない
				if (!m_pTargetObjArray[i]->GetStatus())
				{
					//埋まり値だけ戻す
					m_Player.CollisionStage(over);
				}
			}
		}

		//敵の数だけループ
		for (int j = 0; j < m_pEnemyArray.GetArrayCount(); j++)
		{
			//埋まり値をリセット
			over = Vector2(0, 0);
			
			//敵との埋まり値を求める
			if (m_pTargetObjArray[i]->OverValue(m_pEnemyArray[j]->GetRect(), over))
			{
				//ロープなら当たり判定をしない
				if (m_pTargetObjArray[i]->GetObjType() == OBJECT_ROPE)
				{
					//continue;
				}
				//それ以外埋まり値だけ戻す
				else
				{
					//スキルが使われている状態なら当たり判定を行わない
					if (!m_pTargetObjArray[i]->GetStatus())
					{
						m_pEnemyArray[j]->CollisionStage(over);
					}
				}
			}
		}
	}
#pragma endregion
}
