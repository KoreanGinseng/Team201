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
			"testaaa3.txt",
			"testaaa2.txt",
			"testaaa5.txt",
			"testaaa4.txt",
};

//�R���X�g���N�^
CGame::CGame() :
	CSceneBase(),
	m_bPoase(false),
	m_pEnemyArray(nullptr),
	m_pItemArray(nullptr),
	m_pObjArray(nullptr)
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
	m_pEffect = new CEffectFade();
	m_pEffect->In(10);

	if (!m_Stage[m_StageNo].Load(g_StageFileName[m_StageNo]))
	{
		return FALSE;
	}
	//�G�������m��
	m_pEnemyArray = new CEnemy[m_Stage[m_StageNo].GetEnemyCount()];
	//�A�C�e���������m��
	m_pItemArray = new CItem[m_Stage[m_StageNo].GetItemCount()];
	//�I�u�W�F�N�g�������m��
	m_pObjArray = new CObject[m_Stage[m_StageNo].GetObjectCount()];
	return TRUE;
}

//������
void CGame::Initialize()
{
	//�I���t���O�̏�����
	m_bEnd = false;
	//�J�ڐ�̏�����
	m_NextSceneNo = SCENENO_GAME;
	m_Stage[m_StageNo].Initialize(m_pEnemyArray, m_pItemArray, m_pObjArray);
	m_Player.Initialize();
	g_pTimeManager->Reset();
}

//�X�V
void CGame::Update()
{

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
		m_Player.SkillColision(m_pEnemyArray, m_Stage[m_StageNo].GetEnemyCount(), m_pObjArray, m_Stage[m_StageNo].GetObjectCount());
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
		if (!m_pEnemyArray[i].GetShow())
		{
			continue;
		}
		m_pEnemyArray[i].Update(m_Player.GetPos());
		//�����蔻��
		Vector2 eo(0, 0);
		if (m_Stage[m_StageNo].Collision(m_pEnemyArray[i].GetRect(), eo))
		{
			m_pEnemyArray[i].CollisionStage(eo);
		}
		if (m_pEnemyArray[i].Collision(m_Player.GetRect(), o))
		{
			m_Player.CollisionStage(o);
		}
	}
	//�A�C�e���̍X�V
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		if (!m_pItemArray[i].GetShow())
		{
			continue;
		}
		m_pItemArray[i].Update();
		//�����蔻��
		Vector2 io(0, 0);
		if (m_Stage[m_StageNo].Collision(m_pItemArray[i].GetRect(), io))
		{
			m_pItemArray[i].CollisionStage(io);
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
			//m_pObjArray[i].CollisionStage(oo);
		}
		//�v���C���[�Ƃ̓����蔻��
		bool clime = false;
		oo = Vector2(0, 0);
		if (m_pObjArray[i].Collision(m_Player.GetRect(), oo))
		{
			if (m_pObjArray[i].GetType() == OBJECT_ROPE)
			{
				clime = true;
			}
			else
			{
				m_Player.CollisionStage(oo);
			}
		}
		m_Player.SetClime(clime);
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
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pEnemyArray[i].GetPos());
		m_pEnemyArray[i].Render(screenPos);
	}
	//�A�C�e���̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pItemArray[i].GetPos());
		m_pItemArray[i].Render(screenPos);
	}
	//�I�u�W�F�N�g�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pObjArray[i].GetPos());
		m_pObjArray[i].Render(screenPos);
	}

	//UI���艟��
	CTexturePtr ui1 = g_pTextureManager->GetResource("UI01.png");
	int y = g_pGraphics->GetTargetHeight() - ui1->GetHeight();
	ui1->Render(0, y - 64);
	CTexturePtr ui2 = g_pTextureManager->GetResource("UI02.png");
	int y2 = g_pGraphics->GetTargetHeight() - ui2->GetHeight();
	int x2 = g_pGraphics->GetTargetWidth() - ui2->GetWidth();
	ui2->Render(x2, y2 - 64);


	//�|�[�Y���Ȃ�|�[�Y��ʂ̕`��
	if (m_bPoase)
	{
		//�Q�[����ʂ��D�F�ɂȂ���
		CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(128, 128, 128, 128));
	}
}

void CGame::UpdateDebug() {

	

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd) {

		m_bEnd = true;
		m_pEffect->Out(10);
		m_SceneNo = SCENENO_GAMEOVER;


	}
	else if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {

		m_bEnd = true;

		m_pEffect->Out(10);

		m_SceneNo = SCENENO_GAMECLEAR;

	}
	if (m_pEffect->IsEnd() && m_bEnd&&m_SceneNo!=-1) {

		m_NextSceneNo = m_SceneNo;

	}
}
//�f�o�b�O�`��
void CGame::RenderDebug()
{
	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.RenderDebug(screenPos);
	//�G�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pEnemyArray[i].GetPos());
		m_pEnemyArray[i].RenderDebug(screenPos);
	}
	//�I�u�W�F�N�g�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pObjArray[i].GetPos());
		m_pObjArray[i].RenderDebug(screenPos);
	}
	String(1600, 0, 128, g_pTimeManager->GetNowTime());
	//CGraphicsUtilities::RenderString(0, 30, "%.1f,%.1f", m_MainCamera.GetScroll().x, m_MainCamera.GetScroll().y);
}

//���
void CGame::Release()
{
	if (m_pEffect) {

		delete m_pEffect;

		m_pEffect = nullptr;
	}
	m_Stage[m_StageNo].Release();

	//�G�̉��
	if (m_pEnemyArray != nullptr)
	{
		delete[] m_pEnemyArray;
		m_pEnemyArray = NULL;
	}
	//�A�C�e���̉��
	if (m_pItemArray != nullptr)
	{
		delete[] m_pItemArray;
		m_pItemArray = NULL;
	}
	//�I�u�W�F�N�g�̊J��
	if (m_pObjArray != nullptr)
	{
		delete[] m_pObjArray;
		m_pObjArray = NULL;
	}
	m_Player.Release();
}