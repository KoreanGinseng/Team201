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
CSceneBase() {
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
	for (int i = 0; i < STAGE_COUNT; i++) {
		m_Stage[i].Load(g_StageFileName[i]);
	}
	m_Player.Load();
}

/*****************************************************************
 * @fn
 * ������
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGame::Initialize() {
	m_StageNo = 0;
	for (int i = 0; i < STAGE_COUNT; i++) {
		m_Stage[i].Initialize();
	}
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

	Vector2 o;
	if (m_Stage[m_StageNo].Collision(m_Player.GetRect(), o))
	{
		m_Player.CollisionStage(o);
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
		m_StageNo++;
		if (m_StageNo >= STAGE_COUNT) {
			m_StageNo = 0;
		}
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
}

/*****************************************************************
 * @fn
 * �f�o�b�O�`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGame::RenderDebug() {

}

/*****************************************************************
 * @fn
 * ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGame::Release() {
	for (int i = 0; i < STAGE_COUNT; i++)
	{
		m_Stage[i].Release();
	}
	m_Player.Release();
}