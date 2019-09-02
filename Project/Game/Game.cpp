/*****************************************************************
 *	@file			Game.cpp
 *	@brief			�Q�[���V�[������
 *	@author			����D�R
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"Game.h"
#include	"../Coordinate.h"

char*		g_StageFileName[STAGE_COUNT] = {
			"testMap.txt",
			"testMap2-2.txt",
			"testMap3.txt",
};

/*****************************************************************
 * @fn
 * �����Ȃ��R���X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
CGame::CGame() :
CSceneBase(),
m_StageNo(0){
}

/*****************************************************************
 * @fn
 * �����Ȃ��f�X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
CGame::~CGame() {
	Release();
}

/*****************************************************************
 * @fn
 * �K�v�ȑf�ނ̓ǂݍ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGame::Load() {
	m_Stage[m_StageNo].Load(g_StageFileName[m_StageNo]);
	//�G�������m��
	m_EnemyArray = new CEnemy[m_Stage[m_StageNo].GetEnemyCount()];
	//�A�C�e���������m��
	m_ItemArray = new CItem[m_Stage[m_StageNo].GetItemCount()];
	//�I�u�W�F�N�g�������m��
	m_pObjArray = new CObject[m_Stage[m_StageNo].GetObjectCount()];
	m_Player.Load();
}

/*****************************************************************
 * @fn
 * ������
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGame::Initialize() {
	m_Stage[m_StageNo].Initialize(m_EnemyArray, m_ItemArray, m_pObjArray);
	m_Player.Initialize();
}

/*****************************************************************
 * @fn
 * �X�V
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGame::Update() {

	m_Player.Update();

	Vector2 o(0, 0);
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
		m_EnemyArray[i].Update();
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
	}

	Vector2 centerPos = m_Player.GetPos()
		- Vector2(g_pGraphics->GetTargetWidth() / 2,
				  g_pGraphics->GetTargetHeight() / 2 + 180) + m_Player.GetMove2();

	if (centerPos != m_MainCamera.GetScroll())
	{
		Vector2 d = centerPos - m_MainCamera.GetScroll();
		d /= PLAYER_MAXSPEED;
		m_MainCamera.AddScroll(d);
	}

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

	// �X�y�[�X�L�[�Ńt���X�N���[���ɕϊ�
	if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {
		g_pGraphics->ChangeScreenMode();
	}

	// ESCAPE�L�[�ŏI��
	if (g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
		PostQuitMessage(0);
	}
}

/*****************************************************************
 * @fn
 * �`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGame::Render() {
	m_Stage[m_StageNo].Render(m_MainCamera.GetScroll());
	
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
}

/*****************************************************************
 * @fn
 * �f�o�b�O�`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGame::RenderDebug() {
	m_Stage[m_StageNo].RenderDebug(m_MainCamera.GetScroll());

	Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_Player.GetPos());
	m_Player.RenderDebug();

	//�G�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetEnemyCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_EnemyArray[i].GetPos());
		m_EnemyArray[i].RenderDebug(screenPos);
	}
	//�A�C�e���̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetItemCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_ItemArray[i].GetPos());
		m_ItemArray[i].RenderDebug(screenPos);
	}
	//�I�u�W�F�N�g�̕`��
	for (int i = 0; i < m_Stage[m_StageNo].GetObjectCount(); i++)
	{
		Vector2 screenPos = ScreenTransration(m_MainCamera.GetScroll(), m_pObjArray[i].GetPos());
		m_pObjArray[i].RenderDebug(screenPos);
	}
}

/*****************************************************************
 * @fn
 * ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGame::Release() {

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