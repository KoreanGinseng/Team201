/*****************************************************************
 *	@file			Game.cpp
 *	@brief			�Q�[���V�[���N���X
 *	@author			����D�R
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

//�R���X�g���N�^
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

//�f�X�g���N�^
CGame::~CGame()
{
}

//�ǂݍ���
bool CGame::Load()
{
	//�V�[���G�t�F�N�g�X�^�[�g
	m_pEffect = NEW CEffectFade();
	m_pEffect->In(10);

	if (!m_Stage[m_StageNo].Load(g_StageFileName[m_StageNo]))
	{
		return FALSE;
	}
	//�G�������m��
	m_pEnemyArray.ReSize(m_Stage[m_StageNo].GetEnemyCount());
	for (int i = 0; i < m_pEnemyArray.GetArrayCount(); i++)
	{
		m_pEnemyArray.SetData(NEW CEnemy(), i);
	}
	//�A�C�e���������m��
	m_pItemArray.ReSize(m_Stage[m_StageNo].GetItemCount());
	for (int i = 0; i < m_pItemArray.GetArrayCount(); i++)
	{
		m_pItemArray.SetData(NEW CItem(), i);
	}
	//�I�u�W�F�N�g�������m��
	m_pTargetObjArray.ReSize(m_Stage[m_StageNo].GetObjectCount());
	for (int i = 0; i < m_pTargetObjArray.GetArrayCount(); i++)
	{
		m_pTargetObjArray.SetData(NEW CTargetObj(), i);
	}
	//�}�b�v�I�u�W�F�N�g�������m��
	m_pMapObjArray.ReSize(m_Stage[m_StageNo].GetMapObjCount());
	for (int i = 0; i < m_pMapObjArray.GetArrayCount(); i++)
	{
		m_pMapObjArray.SetData(NEW CMapObj(), i);
	}
	//�w�i�`�b�v�������m��
	m_pBackChipArray.ReSize(m_Stage[m_StageNo].GetBackChipCount());
	for (int i = 0; i < m_pBackChipArray.GetArrayCount(); i++)
	{
		m_pBackChipArray.SetData(NEW CBackChip(), i);
	}
	g_pSoundManager->LoadBGM("Stage1_BGM.mp3");
	return TRUE;
}

//������
void CGame::Initialize()
{
	//�J�ڐ�̏�����
	m_NextSceneNo = SCENENO_GAME;

	//�v���C���[�̏�����
	m_Player.Initialize();

	//�X�e�[�W�̏�����
	m_Stage[m_StageNo].Initialize(&m_pEnemyArray, &m_pItemArray, &m_pTargetObjArray, &m_pMapObjArray, &m_pBackChipArray);

	//�Q�[���J�n���ԃ��Z�b�g
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

//�X�V
void CGame::Update()
{

	CCordinate::SetBack(false);
	CCordinate::SetSkip(false);
	CCordinate::SetStop(false);

	//�Q�[���I�[�o�[��
	if (m_Player.IsDead() && !IsStart())
	{
		m_pEffect->Out(10);
		m_NextSceneNo = SCENENO_GAMEOVER;
		g_pSoundManager->GetSoundBGM("Stage1_BGM.mp3")->Stop();
	}

	//�f�o�b�O�p
	//UpdateDebug();


	//F4�L�[�Ń|�[�Y
	if (g_pInput->IsKeyPush(MOFKEY_F4))
	{
		m_bPoase = !m_bPoase;

		g_pSoundManager->PlaySE("Enter.mp3");
	}

	// ESCAPE�L�[�ŏI��
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE))
	{
		PostQuitMessage(0);
	}

	//�|�[�Y���Ȃ�|�[�Y��ʂ̍X�V�݂̂���
	if (m_bPoase)
	{
		return;
	}

	//�v���C���[�̍X�V
	m_Player.Update();


	//�G�̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		m_pEnemyArray[i]->Update();
		m_pEnemyArray[i]->SetCameraMove(m_MainCamera.IsStart());
	}

	//�A�C�e���̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		if (!m_pItemArray[i]->IsShow())
		{
			continue;
		}
		m_pItemArray[i]->Update();
	}

	//�I�u�W�F�N�g�̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		if (!m_pTargetObjArray[i]->IsShow())
		{
			continue;
		}
		m_pTargetObjArray[i]->Update();
	}

	//�}�b�v�I�u�W�F�N�g�̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetMapObjCount(); i++)
	{
		if (!m_pMapObjArray[i]->IsShow())
		{
			continue;
		}
		m_pMapObjArray[i]->Update();
	}

	//�}�b�v�I�u�W�F�N�g�̍X�V
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

	//�����蔻��
	Collosion();

	//�J�����̍X�V
	Vector2 centerPos = m_Player.GetPos() - Vector2(g_pGraphics->GetTargetWidth() / 2, 180) + (Vector2(PLAYER_SPEED, PLAYER_JUMPPOW) + Vector2(0.1f, 0.1f));
	m_MainCamera.Update(centerPos, m_Player.GetRect(), m_Stage[m_StageNo].GetStageRect());

	//�X�e�[�W�̍X�V
	m_Stage[m_StageNo].Update();

	//�Q�[�����Ԃ����Z
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

//�`��
void CGame::Render(void)
{
	//goriosi
	g_pTextureManager->GetTexture("��.png")->Render(0, 0);

	//�w�i�`�b�v��BACKBACK�`��
	for (int i = 0; i < m_Stage[m_StageNo].GetBackChipCount(); i++)
	{
		if (m_pBackChipArray[i]->GetRenderType() == RENDER_BACKBACK)
		{
			m_pBackChipArray[i]->RenderBackBack(m_MainCamera.GetScroll());
		}
	}

	//�w�i�`�b�v��BACKSTAGE�`��
	for (int i = 0; i < m_Stage[m_StageNo].GetBackChipCount(); i++)
	{
		if (m_pBackChipArray[i]->GetRenderType() == RENDER_BACKSTAGE)
		{
			m_pBackChipArray[i]->RenderBackStage(m_MainCamera.GetScroll());
		}
	}

	//�X�e�[�W��BACK�`��
	m_Stage[m_StageNo].RenderBack(m_MainCamera.GetScroll());

	//�}�b�v�I�u�W�F�N�g�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetMapObjCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pMapObjArray[i]->GetPos());
		m_pMapObjArray[i]->Render(screenPos);
	}

	//�I�u�W�F�N�g�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pTargetObjArray[i]->GetPos());
		m_pTargetObjArray[i]->Render(screenPos);
	}

	//�X�e�[�W��CHIP�`��
	m_Stage[m_StageNo].RenderChip(m_MainCamera.GetScroll());

	//�v���C���[�̕`��
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.Render(screenPos);

	//�G�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pEnemyArray[i]->GetPos());
		m_pEnemyArray[i]->Render(screenPos);
	}

	//�A�C�e���̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pItemArray[i]->GetPos());
		m_pItemArray[i]->Render(screenPos);
	}
	//�v���C���[�̕`��
	screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.RenderCircle(screenPos);

	//�G�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pEnemyArray[i]->GetPos());
		m_pEnemyArray[i]->RenderCircle(screenPos);
	}

	//�A�C�e���̕`��
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


	//�|�[�Y���Ȃ�|�[�Y��ʂ̕`��
	if (m_bPoase)
	{
		//�Q�[����ʂ��D�F�ɂȂ���
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
//�f�o�b�O�`��
void CGame::RenderDebug()
{
}

//���
void CGame::Release(void)
{
	NewPointerRelease(m_pEffect);
	m_Stage[m_StageNo].Release();

	//�G�̉��
	m_pEnemyArray.Release();
	//�A�C�e���̉��
	m_pItemArray.Release();
	//�I�u�W�F�N�g�̊J��
	m_pTargetObjArray.Release();
	//�}�b�v�I�u�W�F�N�g�̉��
	m_pMapObjArray.Release();
	//�w�i�p�[�c�̉��
	m_pBackChipArray.Release();
	m_Player.Release();
}



void CGame::Collosion(void)
{
#pragma region �v���C���[�������鑤
	//�v���C���[���X�L���������̏ꍇ�A
	if (m_Player.IsTrigger())
	{
		//m_Player.SkillColision(m_pEnemyArray, m_Stage[m_StageNo].GetEnemyCount(), m_pObjArray, m_Stage[m_StageNo].GetObjectCount());
		m_Player.TargetSelect(&m_pEnemyArray, &m_pTargetObjArray, &m_pItemArray);
	}

	//���܂�l�p
	Vector2 over(0, 0);
	//�v���C���[�ƃX�e�[�W�̓����蔻��
	if (m_Stage[m_StageNo].OverValue(m_Player.GetRect(), over))
	{
		//���܂��Ă���l�������ɖ߂�
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

#pragma region �G�������鑤
	//�G�Ƃ̓����蔻��
	//�G�̐��������[�v
	for (int i = 0; i < m_pEnemyArray.GetArrayCount(); i++)
	{
		//��\�������S�̏ꍇ�X�L�b�v
		if (!m_pEnemyArray[i]->IsShow() || m_pEnemyArray[i]->IsDead())
		{
			continue;
		}

		//��̂̋�`�̐��������[�v
		for (int j = 0; j < m_pEnemyArray[i]->GetSrcRectArray().GetArrayCount(); j++)
		{
			//���܂�l�̒l�����Z�b�g
			over = Vector2(0, 0);

			//�X�e�[�W�Ɩ��܂�����߂�
			if (m_pEnemyArray[i]->IsCollisionFlag() && m_Stage[m_StageNo].OverValue(m_pEnemyArray[i]->GetRectArray(j), over))
			{
				//���܂��Ă��邾�����ɖ߂�
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


			//���܂�l�̒l�����Z�b�g
			over = Vector2(0, 0);

			//�v���C���[�Ƃ̖��܂�����߂�
			if (m_pEnemyArray[i]->OverValue(m_Player.GetRect(), over))
			{
				//�G���X�L���Ŏ~�܂��Ă���Ȃ疄�܂�l�����߂�
				if (m_pEnemyArray[i]->GetStatus() == SUBSTATUS_STOP)
				{
					m_Player.CollisionStage(over);
				}
				//�~�܂��ĂȂ��Ȃ�v���C���[�Ƀ_���[�W
				else
				{
					if (m_pEnemyArray[i]->GetEnemyType() == ENEMY_HAND)
					{
						m_pEnemyArray[i]->KnockBack(m_Player.GetRect(), m_Player.GetDamageWait());
					}
					m_Player.Dmg(*m_pEnemyArray[i]);
				}
			}

			//���܂�l�̒l�����Z�b�g
			over = Vector2(0, 0);

			//���̓G�Ƃ̖��܂�����߂�
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
						//���܂��Ă��邾�����ɖ߂�
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

#pragma region �A�C�e���������鑤
	//�A�C�e���Ƃ̓����蔻��
	for (int i = 0; i < m_pItemArray.GetArrayCount(); i++)
	{
		//��\���Ȃ�X�L�b�v
		if (!m_pItemArray[i]->IsShow())
		{
			continue;
		}

		//�P�A�C�e���̋�`�̐��������[�v
		for (int j = 0; j < m_pItemArray[i]->GetSrcRectArray().GetArrayCount(); j++)
		{
			//���܂�l�̃��Z�b�g
			over = Vector2(0, 0);

			//�X�e�[�W�Ƃ̖��܂�l�����߂�
			if (m_Stage[m_StageNo].OverValue(m_pItemArray[i]->GetRectArray(j), over))
			{
				//���܂��Ă��邾���߂�
				m_pItemArray[i]->CollisionStage(over);
			}
		}
	}
#pragma endregion

#pragma region �I�u�W�F�N�g�������鑤
	//�I�u�W�F�N�g�Ƃ̓����蔻��
	//�I�u�W�F�N�g�̐����������蔻�������
	for (int i = 0; i < m_pTargetObjArray.GetArrayCount(); i++)
	{
		//��\���Ȃ�X�L�b�v
		if (!m_pTargetObjArray[i]->IsShow())
		{
			continue;
		}
		//���܂�l�����Z�b�g
		over = Vector2(0, 0);

		//�v���C���[�Ƃ̓����蔻��
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
			//�Ԃ������I�u�W�F�N�g�����[�v�̏ꍇ
			if (m_pTargetObjArray[i]->GetObjType() == OBJECT_ROPE && m_pTargetObjArray[i]->GetStatus() == SUBSTATUS_BACK)
			{
				//�o���悤�ɂ���
				m_Player.SetClime(true);
				break;
			}
			else if (m_pTargetObjArray[i]->GetObjType() == OBJECT_HEAL)
			{
				m_Player.Heal(1);
			}
			//���[�v�ȊO�̏ꍇ
			else
			{
				//�ʏ�̓����ɂ���
				//�X�L�����g���Ă����ԂȂ瓖���蔻����s��Ȃ�
				//���܂�l�����߂�
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

		//�G�̐��������[�v
		for (int j = 0; j < m_pEnemyArray.GetArrayCount(); j++)
		{
			//���܂�l�����Z�b�g
			over = Vector2(0, 0);

			//�G�Ƃ̖��܂�l�����߂�
			if (m_pTargetObjArray[i]->OverValue(m_pEnemyArray[j]->GetRect(), over))
			{
				//���[�v�Ȃ瓖���蔻������Ȃ�
				if (m_pTargetObjArray[i]->GetObjType() == OBJECT_ROPE)
				{
					//continue;
				}
				//����ȊO���܂�l�����߂�
				else
				{
					////�X�L�����g���Ă����ԂȂ瓖���蔻����s��Ȃ�
					m_pEnemyArray[j]->CollisionStage(over);
				}
			}
		}
	}
#pragma endregion
}
