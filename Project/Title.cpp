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

	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {

		m_bEnd = true;
		m_NextSceneNo = SCENENO_GAME;

	}
	
}

//�`��
void CTitle::Render()
{

	RenderDebug();

}

//�f�o�b�O�`��
void CTitle::RenderDebug()
{

	CGraphicsUtilities::RenderString(0, 100, "�^�C�g��");

}

//���
void CTitle::Release()
{

}