/*****************************************************************
 *	@file			Game.cpp
 *	@brief			ゲームシーンクラス
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/

 // INCLUDE
#include "Game.h"

const char*		g_StageFileName[STAGE_COUNT] = {
	//"Stage-R-2-test.txt",
	"EnemyTestStage.txt",
	"Stage-R-1-test.txt",
	//"Stage-R-2-test2.txt",
	"Stage-R-3-test.txt",
	"Stage-R-4-test.txt",
	//"Stage-R-2.txt",
	//"Stage-R-1.txt",
	//"TEISHUTSUYOU.txt",
	//"TestMap1226.txt",
	//"ENEMOVESTAGE2.txt",
};

//コンストラクタ
CGame::CGame() :
	CSceneBase(),
	m_bPoase(false),
	m_pEnemyArray(),
	m_pItemArray(),
	m_pTargetObjArray(),
	m_pMapObjArray(),
	m_bClear(false),
	m_StageNo(0),
	m_CAlpha(0)
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
	g_pSoundManager->LoadBGM("Stage1_BGM.mp3");
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

	const char* BgmFile[] = {
		"Stage1_BGM.mp3",
		"Stage2_BGM.mp3",
		"Stage3_BGM.mp3",
		"Stage4_BGM.mp3",
	};
	g_pSoundManager->StopBGM();
	g_pSoundManager->SetVolumeBGM("Stage1_BGM.mp3", 0.7f);
	g_pSoundManager->PlayBGM(BgmFile[m_StageNo]);

	m_MainCamera.Initialize();

	CCordinate::SetBossFlag(false);
	CCordinate::SetKey(false);
	m_CAlpha = 0;
}

//更新
void CGame::Update()
{

	CCordinate::SetBack(false);
	CCordinate::SetSkip(false);
	CCordinate::SetStop(false);

	//ゲームオーバーへ
	if (m_Player.IsDead() && !IsStart())
	{
		m_pEffect->Out(10);
		m_NextSceneNo = SCENENO_GAMEOVER;
		g_pSoundManager->GetSoundBGM("Stage1_BGM.mp3")->Stop();
	}

	//デバッグ用
	//UpdateDebug();


	//F4キーでポーズ
	if (g_pInput->IsKeyPush(MOFKEY_F4))
	{
		m_bPoase = !m_bPoase;

		g_pSoundManager->PlaySE("Enter.mp3");
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
		m_pEnemyArray[i]->SetCameraMove(m_MainCamera.IsStart());
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
		if (m_StageNo == 0)
		{
			if (!g_pSoundManager->GetSoundBGM("Boss1_BGM.mp3")->IsPlay())
			{
				g_pSoundManager->StopBGM();
				g_pSoundManager->PlayBGM("Boss1_BGM.mp3");
			}
		}
		if (m_StageNo == 1)
		{
			if (!g_pSoundManager->GetSoundBGM("Boss2_BGM.mp3")->IsPlay())
			{
				g_pSoundManager->StopBGM();
				g_pSoundManager->PlayBGM("Boss2_BGM.mp3");
			}
		}
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

	for (int i = 0; i < m_pEnemyArray.GetArrayCount(); i++)
	{
		CEnemy* ene = m_pEnemyArray[i];
		if (!ene->IsBoss())
		{
			continue;
		}
		if (ene->IsDead())
		{
			if (m_StageNo == 3)
			{
				if (!m_bClear)
				{
					g_pSoundManager->StopBGM();
					g_pSoundManager->PlayBGM("Clear_BGM.mp3");
				}
				m_bClear = true;
			}
			else
			{
				m_pEffect->Out(10);
				m_NextSceneNo = SCENENO_GAME;
				g_pSoundManager->GetSoundBGM("Stage1_BGM.mp3")->Stop();
			}
		}
	}

}

//描画
void CGame::Render(void)
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
	//プレイヤーの描画
	screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.RenderCircle(screenPos);

	//敵の描画
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pEnemyArray[i]->GetPos());
		m_pEnemyArray[i]->RenderCircle(screenPos);
	}

	//アイテムの描画
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pItemArray[i]->GetPos());
		m_pItemArray[i]->RenderCircle(screenPos);
	}
}

void CGame::RenderUI(void)
{
	String(g_pGraphics->GetTargetWidth() - 64 * 2 - 64 * 7, 0, 64, "TIME:");
	String(g_pGraphics->GetTargetWidth() - 64 * 2, 0, 64, g_pTimeManager->GetNowTime());
	CTexturePtr pt = g_pTextureManager->GetTexture("UI_HP.png");
	pt->RenderScale(0.0f, g_pGraphics->GetTargetHeight() - pt->GetHeight() * 0.4f + 100, 0.4f);
	CTexturePtr pt2 = g_pTextureManager->GetTexture("UI_SKILL.png");
	pt2->RenderScale(g_pGraphics->GetTargetWidth() - pt2->GetWidth() * 0.4f, g_pGraphics->GetTargetHeight() - pt2->GetHeight() * 0.4f + 100, 0.4f);

	if (CCordinate::IsBackUI())
	{
		g_pTextureManager->GetTexture("Skill_UI_Back.png")->RenderScale(1570, 917, 0.4f);
	}
	if (CCordinate::IsSkipUI())
	{
		g_pTextureManager->GetTexture("Skill_UI_Skip.png")->RenderScale(1686, 917, 0.4f);
	}
	if (CCordinate::IsStopUI())
	{
		g_pTextureManager->GetTexture("Skill_UI_Stop.png")->RenderScale(1626, 917, 0.4f);
	}

	int hp = m_Player.GetHp();
	CTexturePtr pt3 = g_pTextureManager->GetTexture("HP_H.png");
	CTexturePtr pt4 = g_pTextureManager->GetTexture("HP.png");
	for (int i = 1; i <= hp; i++)
	{
		if (i % 2 == 0)
		{
			pt4->RenderScale(0 + 35 * i - 100, 800, 0.4f);
		}
		else
		{
			pt3->RenderScale(0 + 35 * (i + 1) - 5 - 100, 800, 0.4f);
		}
	}
	String(0, 0, 32, "A :JUMP", m_Player.IsJump() ? MOF_XRGB(128, 128, 128) : MOF_COLOR_WHITE);
	if (m_Player.IsTrigger())
	{
		if (!m_Player.IsEne())
		{
			String(0, 32, 32, "X :BACK", m_Player.IsObjBack() ? MOF_XRGB(128, 128, 128) : MOF_COLOR_WHITE);
			String(0, 64, 32, "Y :STOP", MOF_XRGB(128, 128, 128));
			String(0, 96, 32, "B :TRIP", m_Player.IsObjTrip() ? MOF_XRGB(128, 128, 128) : MOF_COLOR_WHITE);
		}
		else
		{
			String(0, 32, 32, "X :BACK", MOF_XRGB(128, 128, 128));
			String(0, 64, 32, "Y :STOP", !m_Player.IsEne() ? MOF_XRGB(128, 128, 128) : MOF_COLOR_WHITE);
			String(0, 96, 32, "B :TRIP", MOF_XRGB(128, 128, 128));
		}
	}
	else
	{
		String(0, 32, 32, "X :BACK", MOF_XRGB(128, 128, 128));
		String(0, 64, 32, "Y :STOP", MOF_XRGB(128, 128, 128));
		String(0, 96, 32, "B :TRIP", MOF_XRGB(128, 128, 128));
	}
	String(0, 128, 32, "LT:SKILL", m_Player.IsTrigger() ? MOF_XRGB(128, 128, 128) : MOF_COLOR_WHITE);

	String(320, 0, 32, "F4:PAUSE");
	String(320, 32, 32, "LB:PREV");
	String(320, 64, 32, "RB:NEXT");
	if (m_bClear)
	{
		int alp = m_CAlpha++;
		if (alp > 255)
		{
			alp = 255;
		}
		if (m_CAlpha > 30 + 255)
		{
			m_pEffect->Out(10);
			m_NextSceneNo = SCENENO_GAME;
		}
		CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB( alp, 255, 255, 255));
		//g_pTextureManager->GetTexture("fin.png")->Render(0, 0, MOF_ARGB(alp, 255, 255, 255));
	}


	//ポーズ中ならポーズ画面の描画
	if (m_bPoase)
	{
		//ゲーム画面が灰色になるやつ
		CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(128, 128, 128, 128));
		String((g_pGraphics->GetTargetWidth() - 64 * 5) * 0.5f - 64, 340 - 32, 64, "PAUSE");
	}
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
void CGame::SetStageNo(const int & no)
{
	m_StageNo = no;
}
//デバッグ描画
void CGame::RenderDebug()
{
}

//解放
void CGame::Release(void)
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

	for (int i = 0; i < CShot::GetShotLists()->GetArrayCount(); i++)
	{
		if (!CShot::GetShotLists()->GetData(i)->IsShot())
		{
			continue;
		}
		over = Vector2(0, 0);
		//if (m_Player.OverValue(CShot::GetShotLists()->GetData(i)->GetRect(), over))
		if (CShot::GetShotLists()->GetData(i)->OverValue(m_Player.GetRect(), over))
		{
			if (CShot::GetShotLists()->GetData(i)->GetStatus() == SUBSTATUS_STOP)
			{
				CShot::GetShotLists()->GetData(i)->CollisionPlayer(over);
			}
			else
			{
				m_Player.Dmg(1);
			}
		}
	}
#pragma endregion

#pragma region 敵が当たる側
	//敵との当たり判定
	//敵の数だけループ
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

				if (m_pEnemyArray[i]->GetEnemyType() == ENEMY_BOSS_1)
				{
					CEnemyBoss* pe = static_cast<CEnemyBoss*>(m_pEnemyArray[i]);
					if (pe->GetBoundShotArray()->GetArrayCount() > 0)
					{
						Vector2 shotOver(0, 0);
						if (m_Stage[m_StageNo].OverValue(pe->GetBoundShotArray()->GetData(0)->GetRect(), shotOver))
						{
							pe->GetBoundShotArray()->GetData(0)->CollisionStage(shotOver);
						}
					}
					for (int sc = 0; sc < CShot::GetShotLists()->GetArrayCount(); sc++)
					{
						if (CShot::GetShotLists()->GetData(sc)->GetShotType() != SHOT_BOUND)
						{
							continue;
						}
						if (pe->GetRectArray(j).CollisionRect(CShot::GetShotLists()->GetData(sc)->GetRect()))
						{
							pe->Dmg(1);
							CShot::GetShotLists()->GetData(sc)->SetShot(false);
							Vector2 effectPos = pe->GetPos() - CCamera2D::GetSScroll();
							effectPos.y -= 90;
							effectPos.x -= 30;
							g_pEffectManager->Start("Explosion_B.bin", effectPos);
						}
					}
				}
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
			for (int k = 0; k < m_pEnemyArray.GetArrayCount(); k++)
			{
				if (k == i)
				{
					continue;
				}
				if (m_pEnemyArray[i]->IsDead() || m_pEnemyArray[k]->IsDead())
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

		if (m_pEnemyArray[i]->GetEnemyType() == ENEMY_BOSS_2)
		{
			CEnemyBoss2* pe = static_cast<CEnemyBoss2*>(m_pEnemyArray[i]);
			for (int sc = 0; sc < CShot::GetShotLists()->GetArrayCount(); sc++)
			{
				if (CShot::GetShotLists()->GetData(sc)->GetShotType() != SHOT_RAY)
				{
					continue;
				}
				CDynamicArray<CCircle>* prc = static_cast<CRayShot*>(CShot::GetShotLists()->GetData(sc))->GetShotCircle();
				for (int rc = 0; rc < prc->GetArrayCount(); rc++)
				{
					CCircle prcc = prc->GetData(rc);
					pe->CollisionRayShot(prcc);
				}
			}
		}
	}
#pragma endregion

#pragma region アイテムが当たる側
	//アイテムとの当たり判定
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
			if (m_pTargetObjArray[i]->GetObjType() == OBJECT_DOOR && CCordinate::IsKey())
			{
				static_cast<CDoor*>(m_pTargetObjArray[i])->OpenTheDoor();
				g_pSoundManager->PlaySE("Door.mp3");
				m_NextSceneNo = SCENENO_GAME;
				m_pEffect->Out(10);
			}
			//ぶつかったオブジェクトがロープの場合
			if (m_pTargetObjArray[i]->GetObjType() == OBJECT_ROPE && m_pTargetObjArray[i]->GetStatus() == SUBSTATUS_BACK)
			{
				//登れるようにする
				m_Player.SetClime(true);
				break;
			}
			else if (m_pTargetObjArray[i]->GetObjType() == OBJECT_HEAL)
			{
				m_Player.Heal(1);
			}
			//ロープ以外の場合
			else
			{
				//通常の動きにする
				//スキルが使われている状態なら当たり判定を行わない
				//埋まり値だけ戻す
				m_Player.CollisionStage(over);
			}
		}

		//SHOT
		if (m_pTargetObjArray[i]->GetObjType() >= OBJECT_MOVEFLOOR1 && m_pTargetObjArray[i]->GetObjType() <= OBJECT_MOVEFLOOR6)
		{
			for (int sc = 0; sc < CShot::GetShotLists()->GetArrayCount(); sc++)
			{
				if (CShot::GetShotLists()->GetData(sc)->GetShotType() != SHOT_RAY)
				{
					continue;
				}
				CRayShot* prs = static_cast<CRayShot*>(CShot::GetShotLists()->GetData(sc));
				CDynamicArray<CCircle>* prc = prs->GetShotCircle();
				for (int rc = 0; rc < prc->GetArrayCount(); rc++)
				{
					if (prs->IsRef())
					{
						if (rc < prs->GetTempCount())
						{
							continue;
						}
					}
					CCircle prcc = prc->GetData(rc);
					if (CollisionRectCircle(m_pTargetObjArray[i]->GetRect(), prcc))
					{
						static_cast<CRayShot*>(CShot::GetShotLists()->GetData(sc))->Refrect(Vector2(prcc.x, prcc.y));
					}
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
					////スキルが使われている状態なら当たり判定を行わない
					m_pEnemyArray[j]->CollisionStage(over);
				}
			}
		}
	}
#pragma endregion
}
