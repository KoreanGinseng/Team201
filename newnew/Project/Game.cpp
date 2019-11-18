/*****************************************************************
 *	@file			Game.cpp
 *	@brief			�Q�[���V�[���N���X
 *	@author			����D�R
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

//�R���X�g���N�^
CGame::CGame() :
	CSceneBase(),
	m_bPoase(false),
	m_pEnemyArray(),
	m_pItemArray(),
	m_pTargetObjArray()
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
	CEnemy* tmp_e = NEW CEnemy;
	m_pEnemyArray.SetArray(&tmp_e, m_Stage[m_StageNo].GetEnemyCount());
	delete tmp_e;
	//�A�C�e���������m��
	CItem* tmp_i = NEW CItem;
	m_pItemArray.SetArray(&tmp_i, m_Stage[m_StageNo].GetItemCount());
	delete tmp_i;
	//�I�u�W�F�N�g�������m��
	CTargetObj* tmp_t = NEW CTargetObj;
	m_pTargetObjArray.SetArray(&tmp_t, m_Stage[m_StageNo].GetObjectCount());
	delete tmp_t;

	return TRUE;
}

//������
void CGame::Initialize()
{
	//�J�ڐ�̏�����
	m_NextSceneNo = SCENENO_GAME;

	//�X�e�[�W�̏�����
	m_Stage[m_StageNo].Initialize(&m_pEnemyArray, &m_pItemArray, &m_pTargetObjArray);

	//�v���C���[�̏�����
	m_Player.Initialize();
	//�Q�[���J�n���ԃ��Z�b�g
	g_pTimeManager->Reset();
}

//�X�V
void CGame::Update()
{

	//�Q�[���I�[�o�[��
	if (m_Player.IsDead() && !IsStart())
	{
		m_pEffect->Out(10);
		m_NextSceneNo = SCENENO_GAMEOVER;
	}

	//�f�o�b�O�p
	UpdateDebug();

	//F4�L�[�Ń|�[�Y
	if (g_pInput->IsKeyPush(MOFKEY_F4))
	{
		m_bPoase = !m_bPoase;
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


	//�v���C���[���X�L���������̏ꍇ�A
	if (m_Player.IsTrigger())
	{
		//m_Player.SkillColision(m_pEnemyArray, m_Stage[m_StageNo].GetEnemyCount(), m_pObjArray, m_Stage[m_StageNo].GetObjectCount());
		m_Player.TargetSelect(&m_pEnemyArray, &m_pTargetObjArray, &m_pItemArray);
	}

	//�v���C���[�̍X�V
	m_Player.Update();

	Vector2 o(0, 0);
	//�v���C���[�ƃX�e�[�W�̓����蔻��
	if (m_Stage[m_StageNo].OverValue(m_Player.GetRect(), o))
	{
		m_Player.CollisionStage(o);
	}

	//�G�̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		if (!m_pEnemyArray[i]->IsShow() || !m_pEnemyArray[i]->IsDead())
		{
			continue;
		}
		//m_pEnemyArray[i]->Update(m_Player.GetPos());
		m_pEnemyArray[i]->Update();
	}

	//�����蔻��
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

	//�A�C�e���̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		if (!m_pItemArray[i]->IsShow())
		{
			continue;
		}
		m_pItemArray[i]->Update();
	}
	//�����蔻��
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
	//�I�u�W�F�N�g�̍X�V
	bool clime = false;
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		if (!m_pTargetObjArray[i]->IsShow())
		{
			continue;
		}
		m_pTargetObjArray[i]->Update();
	}

	//�����蔻��
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		if (!m_pTargetObjArray[i]->IsShow())
		{
			continue;
		}
		Vector2 oo(0, 0);
		//�v���C���[�Ƃ̓����蔻��
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

	//�J�����̍X�V
	Vector2 centerPos = m_Player.GetPos() - Vector2(g_pGraphics->GetTargetWidth() / 2, 180) + (m_Player.GetSpd() + Vector2(0.1f, 0.1f));
	m_MainCamera.Update(centerPos, m_Player.GetRect(), m_Stage[m_StageNo].GetStageRect());

	//�X�e�[�W�̍X�V
	m_Stage[m_StageNo].Update();

	//�Q�[�����Ԃ����Z
	g_pTimeManager->Tick();
}

//�`��
void CGame::Render()
{

	//goriosi
	g_pTextureManager->GetResource("��.png")->Render(0, 0);

	//�X�e�[�W�̕`��
	m_Stage[m_StageNo].Render(m_MainCamera.GetScroll());

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
	//�I�u�W�F�N�g�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pTargetObjArray[i]->GetPos());
		m_pTargetObjArray[i]->Render(screenPos);
	}

	//�|�[�Y���Ȃ�|�[�Y��ʂ̕`��
	if (m_bPoase)
	{
		//�Q�[����ʂ��D�F�ɂȂ���
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
//�f�o�b�O�`��
void CGame::RenderDebug()
{
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.RenderDebug(screenPos);
	
	//CGraphicsUtilities::RenderString(0, 30, "%.1f,%.1f", m_MainCamera.GetScroll().x, m_MainCamera.GetScroll().y);
}

//���
void CGame::Release()
{
	NewPointerRelease(m_pEffect);
	m_Stage[m_StageNo].Release();

	//�G�̉��
	m_pEnemyArray.Release();
	//�A�C�e���̉��
	m_pItemArray.Release();
	//�I�u�W�F�N�g�̊J��
	m_pTargetObjArray.Release();

	m_Player.Release();
}