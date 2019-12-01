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
			"ENEMOVESTAGE.txt",
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
	m_pTargetObjArray(),
	m_pMapObjArray()
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
	return TRUE;
}

//������
void CGame::Initialize()
{
	//�J�ڐ�̏�����
	m_NextSceneNo = SCENENO_GAME;

	//�X�e�[�W�̏�����
	m_Stage[m_StageNo].Initialize(&m_pEnemyArray, &m_pItemArray, &m_pTargetObjArray, &m_pMapObjArray, &m_pBackChipArray);

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

	//�v���C���[�̍X�V
	m_Player.Update();
	

	//�G�̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		if (!m_pEnemyArray[i]->IsShow() || m_pEnemyArray[i]->IsDead())
		{
			continue;
		}
		//m_pEnemyArray[i]->Update(m_Player.GetPos());
		m_pEnemyArray[i]->Update();
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

	//�����蔻��
	Collosion();

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

	//�w�i�`�b�v��BACKBACK�`��
	for (int i = 0; i < m_Stage[m_StageNo].GetBackChipCount(); i++)
	{
		if (m_pBackChipArray[i]->GetRenderType() == RENDER_BACKBACK)
		{
			m_pBackChipArray[i]->RenderBackBack(m_MainCamera.GetScroll());
		}
	}

	//�X�e�[�W��BACK�`��
	m_Stage[m_StageNo].RenderBack(m_MainCamera.GetScroll());


	//�w�i�`�b�v��BACKSTAGE�`��
	for (int i = 0; i < m_Stage[m_StageNo].GetBackChipCount(); i++)
	{
		if (m_pBackChipArray[i]->GetRenderType() == RENDER_BACKSTAGE)
		{
			m_pBackChipArray[i]->RenderBackStage(m_MainCamera.GetScroll());
		}
	}

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
	//�}�b�v�I�u�W�F�N�g�̉��
	m_pMapObjArray.Release();
	//�w�i�p�[�c�̉��
	m_pBackChipArray.Release();
	m_Player.Release();
}



void CGame::Collosion(void)
{
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

	//�G�Ƃ̓����蔻��
	//�G�̐��������[�v
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
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
			if (m_Stage[m_StageNo].OverValue(m_pEnemyArray[i]->GetRectArray(j), over))
			{
				//���܂��Ă��邾�����ɖ߂�
				m_pEnemyArray[i]->CollisionStage(over);
			}

			//���܂�l�̒l�����Z�b�g
			over = Vector2(0, 0);

			//�v���C���[�Ƃ̖��܂�����߂�
			if (m_pEnemyArray[i]->OverValue(m_Player.GetRect(), over))
			{
				//�G���X�L���Ŏ~�܂��Ă���Ȃ疄�܂�l�����߂�
				if (m_pEnemyArray[i]->IsSkill())
				{
					m_Player.CollisionStage(over);
				}
				//�~�܂��ĂȂ��Ȃ�v���C���[�Ƀ_���[�W
				else
				{
					m_Player.Dmg(*m_pEnemyArray[i]);
				}
			}

			//���܂�l�̒l�����Z�b�g
			over = Vector2(0, 0);

			//���̓G�Ƃ̖��܂�����߂�
			for (int k = 0; k < m_Stage[m_StageNo].GetEnemyCount(); k++)
			{
				if (k == i)
				{
					continue;
				}
				for (int l = 0; l < m_pEnemyArray[k]->GetRectArray().GetArrayCount(); l++)
				{
					if (m_pEnemyArray[i]->OverValue(m_pEnemyArray[k]->GetRectArray(l), over))
					{
						//���܂��Ă��邾�����ɖ߂�
						m_pEnemyArray[k]->CollisionStage(over);
						m_pEnemyArray[i]->Reverse(-over);
					}
				}
			}
		}
	}

	//�A�C�e���Ƃ̓����蔻��
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
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

	//�I�u�W�F�N�g�Ƃ̓����蔻��
	//�I�u�W�F�N�g�̐����������蔻�������
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		//��\���Ȃ�X�L�b�v
		if (!m_pTargetObjArray[i]->IsShow())
		{
			continue;
		}
		//���܂�l�����Z�b�g
		over = Vector2(0, 0);

		//�v���C���[�Ƃ̓����蔻��
		if (m_pTargetObjArray[i]->OverValue(m_Player.GetRect(), over))
		{
			//�Ԃ������I�u�W�F�N�g�����[�v�̏ꍇ
			if (m_pTargetObjArray[i]->GetObjType() == OBJECT_ROPE)
			{
				//�o���悤�ɂ���
				m_Player.SetClime(true);
			}
			//���[�v�ȊO�̏ꍇ
			else
			{
				//�ʏ�̓����ɂ���
				m_Player.SetClime(false);
				//���܂�l�����߂�
				m_Player.CollisionStage(over);
			}
		}

		//�G�̐��������[�v
		for (int j = 0; j < m_Stage[m_StageNo].GetEnemyCount(); j++)
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
					m_pEnemyArray[j]->CollisionStage(over);
				}
			}
		}
	}
}