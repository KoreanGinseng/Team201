/*****************************************************************
 *	@file			Title.cpp
 *	@brief			�^�C�g���V�[���N���X
 *	@author			����D�R
 *	@date			2019/09/29
 *****************************************************************/

 // INCLUDE
#include "Title.h"


//�R���X�g���N�^
CTitle::CTitle() :
	CSceneBase()
{
}

//�f�X�g���N�^
CTitle::~CTitle()
{
}

//�ǂݍ���
bool CTitle::Load()
{

	//�V�[���G�t�F�N�g�X�^�[�g
	m_pEffect = new CEffectFade();
	m_pEffect->In(10);

	return TRUE;
}

//������
void CTitle::Initialize()
{
	//�I���t���O�̏�����
	m_bEnd = false;
	//�J�ڐ�̏�����
	m_NextSceneNo = SCENENO_TITLE;


}

//�X�V
void CTitle::Update()
{
	if (g_pInput->IsKeyPush(MOFKEY_RETURN))
	{
		m_bEnd = true;
		m_NextSceneNo = SCENENO_GAME;
		ReNum::GetInstance().SetReNum();
	}

	UpdateDebug();
	
}

//�`��
void CTitle::Render()
{

	RenderDebug();

}

void CTitle::UpdateDebug() {

	if (g_pInput->IsKeyPush(MOFKEY_Q)) {

		m_bEnd = true;
		m_NextSceneNo = SCENENO_GAME;
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {

		m_bEnd = true;
		m_pEffect->Out(10);

	}

	if (m_pEffect->IsEnd() && m_bEnd) {

		m_NextSceneNo = SCENENO_GAME;
	}

}

//�f�o�b�O�`��
void CTitle::RenderDebug()
{

	CGraphicsUtilities::RenderString(0, 100, "�^�C�g��");

}

//���
void CTitle::Release()
{
	if (m_pEffect) {

		delete m_pEffect;

		m_pEffect = nullptr;

	}

}