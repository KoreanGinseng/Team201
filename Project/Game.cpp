/*****************************************************************
 *	@file			Game.cpp
 *	@brief			�Q�[���V�[���N���X
 *	@author			����D�R
 *	@date			2019/09/29
 *****************************************************************/

// INCLUDE
#include "Game.h"

char*		g_StageFileName[STAGE_COUNT] = {
			"testMap1-1.txt",
			"testMap1-1.txt",
			"testMap1-1.txt",
};

//�R���X�g���N�^
CGame::CGame() :
CSceneBase(),
m_StageNo(START_STAGE),
m_bPoase(false)
{
}

//�f�X�g���N�^
CGame::~CGame()
{
}

//�ǂݍ���
bool CGame::Load()
{
	if (!m_Stage[m_StageNo].Load(g_StageFileName[m_StageNo]))
	{
		return FALSE;
	}
	//�G�������m��
	m_EnemyArray = new CEnemy[m_Stage[m_StageNo].GetEnemyCount()];
	//�A�C�e���������m��
	m_ItemArray = new CItem[m_Stage[m_StageNo].GetItemCount()];
	//�I�u�W�F�N�g�������m��
	m_pObjArray = new CObject[m_Stage[m_StageNo].GetObjectCount()];
	return TRUE;
}

//������
void CGame::Initialize()
{
	m_Stage[m_StageNo].Initialize(m_EnemyArray, m_ItemArray, m_pObjArray);
	m_Player.Initialize();
	g_pTimeManager->Reset();
}

//�X�V
void CGame::Update()
{
	//F4�L�[�Ń|�[�Y
	if (g_pInput->IsKeyPush(MOFKEY_F4)) {
		m_bPoase = !m_bPoase;
	}

	// ESCAPE�L�[�ŏI��
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
		PostQuitMessage(0);
	}

	//�|�[�Y���Ȃ�|�[�Y��ʂ̍X�V�݂̂���
	if (m_bPoase) {

		return;
	}

	//�v���C���[�̍X�V
	m_Player.Update();

	Vector2 o(0, 0);
	//�v���C���[�ƃX�e�[�W�̓����蔻��
	if (m_Stage[m_StageNo].Collision(m_Player.GetRect(), o))
	{
		m_Player.CollisionStage(o);
	}

	//�G�̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].Update(m_Player.GetPos());
		//�����蔻��
		Vector2 eo(0, 0);
		if (m_Stage[m_StageNo].Collision(m_EnemyArray[i].GetRect(), eo))
		{
			m_EnemyArray[i].CollisionStage(eo);
		}
	}
	//�A�C�e���̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		//�����蔻��
		Vector2 io(0, 0);
		if (m_Stage[m_StageNo].Collision(m_ItemArray[i].GetRect(), io))
		{
			m_ItemArray[i].CollisionStage(io);
		}
	}
	//�I�u�W�F�N�g�̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		if (!m_pObjArray[i].GetShow())
		{
			continue;
		}
		m_pObjArray[i].Update();
		//�����蔻��
		Vector2 oo(0, 0);
		if (m_Stage[m_StageNo].Collision(m_pObjArray[i].GetRect(), oo))
		{
			m_pObjArray[i].CollisionStage(oo);
		}
	}

	//�J�����̍X�V
	Vector2 centerPos = m_Player.GetPos() - Vector2(g_pGraphics->GetTargetWidth() / 2, 180) + (m_Player.GetSpd() + Vector2(0.1f, 0.1f));
	m_MainCamera.Update(centerPos, m_Player.GetRect(), m_Stage[m_StageNo].GetStageRect());

	//�X�e�[�W�̍X�V
	m_Stage[m_StageNo].Update();


	// O�L�[�ŃX�e�[�W�ύX
	if (g_pInput->IsKeyPush(MOFKEY_O)) {
		Release();
		if (++m_StageNo >= STAGE_COUNT) {
			m_StageNo = 0;
		}
		Load();
		Initialize();
	}

	//�Q�[�����Ԃ����Z
	g_pTimeManager->Tick();
}

//�`��
void CGame::Render()
{
	//�X�e�[�W�̕`��
	m_Stage[m_StageNo].Render(m_MainCamera.GetScroll());

	//�v���C���[�̕`��
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.Render(screenPos);

	//�G�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_EnemyArray[i].GetPos());
		m_EnemyArray[i].Render(screenPos);
	}
	//�A�C�e���̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_ItemArray[i].GetPos());
		m_ItemArray[i].Render(screenPos);
	}
	//�I�u�W�F�N�g�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pObjArray[i].GetPos());
		m_pObjArray[i].Render(screenPos);
	}

	//�|�[�Y���Ȃ�|�[�Y��ʂ̕`��
	if (m_bPoase)
	{
		//�Q�[����ʂ��D�F�ɂȂ���
		CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(128, 128, 128, 128));
	}
}

//�f�o�b�O�`��
void CGame::RenderDebug()
{
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.RenderDebug(screenPos);
	String(1600, 0, 128, g_pTimeManager->GetNowTime());
	CGraphicsUtilities::RenderString(0, 30, "%.1f,%.1f", m_MainCamera.GetScroll().x, m_MainCamera.GetScroll().y);
}

//���
void CGame::Release()
{
	m_Stage[m_StageNo].Release();

	//�G�̉��
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//�A�C�e���̉��
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	//�I�u�W�F�N�g�̊J��
	if (m_pObjArray)
	{
		delete[] m_pObjArray;
		m_pObjArray = NULL;
	}
	m_Player.Release();
}