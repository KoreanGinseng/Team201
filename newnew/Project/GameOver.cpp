/*****************************************************************
 *	@file			GameOver.cpp
 *	@brief			�Q�[���I�[�o�[�V�[������
 *	@author			����D�R
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"GameOver.h"

/*****************************************************************
 * @fn
 * �����Ȃ��R���X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
CGameOver::CGameOver() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * �����Ȃ��f�X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
CGameOver::~CGameOver() {
	Release();
}

/*****************************************************************
 * @fn
 * �K�v�ȑf�ނ̓ǂݍ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
bool CGameOver::Load() {

	//�V�[���G�t�F�N�g�X�^�[�g
	m_pEffect = NEW CEffectFade();
	m_pEffect->In(10);

	return TRUE;
}

/*****************************************************************
 * @fn
 * ������
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGameOver::Initialize() {
	//�J�ڐ�̏�����
	m_NextSceneNo = SCENENO_GAMEOVER;
}

/*****************************************************************
 * @fn
 * �X�V
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGameOver::Update() {

	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_NextSceneNo = SCENENO_GAME;
	}

	UpdateDebug();

}

/*****************************************************************
 * @fn
 * �`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGameOver::Render() {

	RenderDebug();
}
 void CGameOver::RenderUI()
 {
 }
/*****************************************************************
* @fn
* �f�o�b�O�X�V
* @param �Ȃ�
* @return �Ȃ�
*****************************************************************/
void CGameOver::UpdateDebug() {

	if (g_pInput->IsKeyPush(MOFKEY_Q)) {
		m_NextSceneNo = SCENENO_GAME;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_pEffect->IsStart()) {
		m_pEffect->Out(10);
	}
	else if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {

	}
	if (m_pEffect->IsEnd() && m_pEffect->IsStart()) {

		m_NextSceneNo = SCENENO_RANKING;
	}
}
/*****************************************************************
 * @fn
 * �f�o�b�O�`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGameOver::RenderDebug() {

	CGraphicsUtilities::RenderString(0, 100, "�Q�[���I�[�o�[");

}

/*****************************************************************
 * @fn
 * ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGameOver::Release() {
	if (m_pEffect) {

		delete m_pEffect;

		m_pEffect = nullptr;
	}

}