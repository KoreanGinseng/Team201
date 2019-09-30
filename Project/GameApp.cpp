/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//! INCLUDE
#include	"GameApp.h"

//! SCENE
#include	"Game/Game.h"
#include	"GameClear/GameClear.h"
#include	"GameOver/GameOver.h"
#include	"Title/Title.h"
#include	"_Inoue/Inoue.h"
#include	"_Fujiwara/Fujiwara.h"
#include	"_Kimura/Kimura.h"
#include	"_Onishi/Onishi.h"
#include	"Ranking/Ranking.h"

//! GLOBAL
bool				g_bDebug = true;	//! �f�o�b�O�\���t���O
CSceneBase*			g_pScene = nullptr;	//! �V�[���i�[�|�C���^


class CLoading : public CThread {
public:
	bool bEnd = false;
	void Run(void)
	{
		Sleep(10000);
		bEnd = true;
		return;
	}
};
CLoading a;
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//�J�n�V�[��
	g_pScene = new CGame();			//�Q�[���V�[������X�^�[�g(�f�o�b�N�p)
	//g_pScene = new CTitle();		//�^�C�g���V�[������X�^�[�g


	//�ǂݍ��݃J�����g�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectoryA("Resource");

	//�V�[���̓ǂݍ���
	g_pScene->Load();
	//�V�[���̏�����
	g_pScene->Initialize();

	//FPS�̐ݒ�
	if (!CUtilities::SetFPS(GAMEFPS)) 
	{
		return FALSE;
	}
	a.Start("Loading");
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();

	//�V�[���̍X�V
	g_pScene->Update();

	//���̃V�[���ɍs���Ƃ�
	if (g_pScene->IsEnd()) 
	{
		//���̃V�[�����擾
		int change = g_pScene->GetNextScene();
		//�Â��V�[�����폜
		delete g_pScene;
		//�V�����V�[�����擾
		switch (change) 
		{
		case SCENENO_TITLE:
			g_pScene = new CTitle();
			break;
		case SCENENO_GAME:
			g_pScene = new CGame();
			break;
		case SCENENO_GAMECLEAR:
			g_pScene = new CGameClear();
			break;
		case SCENENO_GAMEOVER:
			g_pScene = new CGameOver();
			break;
		case SCENENO_RANKING:
			g_pScene = new CRanking();
			break;
		case SCENENO_FUJIWARA:
			g_pScene = new CFujiwara();
			break;
		case SCENENO_INOUE:
			g_pScene = new CInoue();
			break;
		case SCENENO_KIMURA:
			g_pScene = new CKimura();
			break;
		case SCENENO_ONISHI:
			g_pScene = new COnishi();
			break;
		}
		//�V�����V�[���̓ǂݍ��݂Ə�����
		g_pScene->Load();
		g_pScene->Initialize();
	}

	//F1�L�[�Ńf�o�b�O�t���O�̐؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_F1)) 
	{
		g_bDebug = !g_bDebug;
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	//�V�[���̕`��
	g_pScene->Render();

	if (a.bEnd)
	{
		CGraphicsUtilities::RenderString(0, 0, "LoadEnd");
	}
	else
	{
		CGraphicsUtilities::RenderString(0, 0, "Load...");
	}
	//�f�o�b�O�\��
	if (g_bDebug) 
	{
		//�V�[���̃f�o�b�O�`��
		g_pScene->RenderDebug();
		//FPS�̕\��
		CGraphicsUtilities::RenderString(DEBUGPOSX_FPS, DEBUGPOSY_FPS, "%d", CUtilities::GetFPS());
	}
	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void){
	//�V�[���̉��
	g_pScene->Release();

	//�V�[���̍폜
	if (g_pScene) 
	{
		delete g_pScene;
		//�폜�����|�C���^�ɂ�0������
		g_pScene = NULL;
	}

	return TRUE;
}