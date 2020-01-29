/*****************************************************************
 *	@file			GameClear.cpp
 *	@brief			�Q�[���N���A�V�[������
 *	@author			����D�R
 *	@date			2019/07/29
 *****************************************************************/

//! INCLUDE
#include	"GameClear.h"

/*****************************************************************
 * @fn
 * �����Ȃ��R���X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
CGameClear::CGameClear() :
CSceneBase() {
}

/*****************************************************************
 * @fn
 * �����Ȃ��f�X�g���N�^
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
CGameClear::~CGameClear() {
	Release();
}

/*****************************************************************
 * @fn
 * �K�v�ȑf�ނ̓ǂݍ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
bool CGameClear::Load() {

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
void CGameClear::Initialize() {

	//�J�ڐ�̏�����
	m_NextSceneNo = SCENENO_GAMECLEAR;


}

/*****************************************************************
 * @fn
 * �X�V
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGameClear::Update() {

	UpdateDebug();

}

/*****************************************************************
* @fn
* �f�o�b�O�X�V
* @param �Ȃ�
* @return �Ȃ�
*****************************************************************/
void CGameClear::UpdateDebug() {

	//if (g_pInput->IsKeyPush(MOFKEY_Q)) {
	//	m_NextSceneNo = SCENENO_GAME;
	//}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_pEffect->IsStart()) {
		m_pEffect->Out(10);
		m_NextSceneNo = SCENENO_TITLE;

		g_pSoundManager->PlaySE("Enter.mp3");
	}
	//else if (g_pInput->IsKeyPush(MOFKEY_SPACE)) {

	//}
	//if (m_pEffect->IsEnd() && m_pEffect->IsStart()) {
	//}
}
/*****************************************************************
 * @fn
 * �`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGameClear::Render() {

	RenderDebug();
	g_pTextureManager->GetTexture("arigatou.png")->Render(0, 0);
}

 void CGameClear::RenderUI()
 {
	 String((g_pGraphics->GetTargetWidth() - 64 * 12) * 0.5f - 64, 740 - 32, 64, "PRESS RETURN");
	 String((g_pGraphics->GetTargetWidth() - 64 * 13) * 0.5f - 64, 840 - 32, 64, "BACK TO TITLE");
 }

/*****************************************************************
 * @fn
 * �f�o�b�O�`��
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGameClear::RenderDebug() {

	//CGraphicsUtilities::RenderString(0, 100, "�Q�[���N���A");
}

/*****************************************************************
 * @fn
 * ���
 * @param �Ȃ�
 * @return �Ȃ�
 *****************************************************************/
void CGameClear::Release() {
	if (m_pEffect) {

		delete m_pEffect;

		m_pEffect = nullptr;
	}

}