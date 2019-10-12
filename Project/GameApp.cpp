/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"GameDefine.h"
#include	"SceneBase.h"
#include	"Game.h"
#include	"Title.h"
#include	"GameClear.h"
#include	"GameOver.h"
#include	"Ranking.h"
#include	"_Fujiwara/Fujiwara.h"
#include	"_Inoue/Inoue.h"
#include	"_Kimura/Kimura.h"
#include	"_Onishi/Onishi.h"
#include	"GameDefine.h"
#include	"EffectManager.h"
//#include	"SoundManager.h"
#include	"Loading.h"

//GLOBAL
CSceneBase*		gpScene = nullptr;
CLoading*		gpLoading = nullptr;

#ifdef _DEBUG
bool			gbDebug = false;
#endif // _DEBUG


/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	CUtilities::SetCurrentDirectory("Resource");
	
	//gpScene = new CTitle();			//�^�C�g������J�n
	//gpScene = new CGame();
#ifdef _DEBUG
	gpScene = new CGame();			//�Q�[���V�[������J�n(�f�o�b�O�p)
#endif // _DEBUG

	/*gLoading.SetLoad(gpScene->Load);
	gLoading.SetInit(gpScene->Initialize);*/
	if (gpLoading == nullptr)
	{
		gpLoading = new CLoading();
	}
	gpLoading->SetScene(gpScene);
	gpLoading->Start("Loading");

	//FPS�̐ݒ�
	if (!CUtilities::SetFPS(GAMEFPS))
	{
		return FALSE;
	}
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

	if (!gpLoading->IsEnd())
	{
		return TRUE;
	}

	//�V�[���̍X�V
	gpScene->Update();

	//�V�[���؂�ւ�
	if (gpScene->IsEnd())
	{
		//���̃V�[���ԍ��擾
		int nextScene = gpScene->GetNextSceneNo();
		
		//�Â��V�[�������
		gpScene->Release();
		delete gpScene;
		
		//���̃V�[���𐶐�
		switch (nextScene)
		{
		case SCENENO_TITLE:
			gpScene = new CTitle();
			break;
		case SCENENO_GAME:
			gpScene = new CGame();
			break;
		case SCENENO_GAMEOVER:
			gpScene = new CGameOver();
			break;
		case SCENENO_GAMECLEAR:
			gpScene = new CGameClear();
			break;
		case SCENENO_RANKING:
			gpScene = new CRanking();
			break;
		case SCENENO_FUJIWARA:
			gpScene = new CFujiwara();
			break;
		case SCENENO_INOUE:
			gpScene = new CInoue();
			break;
		case SCENENO_KIMURA:
			gpScene = new CKimura();
			break;
		case SCENENO_ONISHI:
			gpScene = new COnishi();
			break;
		}
		//�ʃX���b�h�ł�肽���B(LOADING)
		{
			gpLoading->Release();
			delete gpLoading;
			gpLoading = new CLoading();
			gpLoading->SetScene(gpScene);
			gpLoading->Start("Loading");
		}
	}

	// O�L�[�ŃX�e�[�W�ύX
	if (gpScene->GetSceneName() == SCENENO_GAME && g_pInput->IsKeyPush(MOFKEY_O))
	{
		gpScene->Release();
		delete gpScene;
		CGame::NextStage();
		gpScene = new CGame();
		gpLoading->Release();
		delete gpLoading;
		gpLoading = new CLoading();
		gpLoading->SetScene(gpScene);
		gpLoading->Start("Loading");
	}

#ifdef _DEBUG
	//F1�L�[�Ńf�o�b�O�\���̐؂�ւ�
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		gbDebug = !gbDebug;
	}
#endif // _DEBUG

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
	g_pGraphics->ClearTarget(0.0f,0.0f,0.0f,0.0f,1.0f,0);

	if (!gpLoading->IsEnd())
	{
		CGraphicsUtilities::RenderString(0, 0, "LOADING");
		//�`��̏I��
		g_pGraphics->RenderEnd();
		return TRUE;
	}
	else
	{
		CGraphicsUtilities::RenderString(0, 0, "LOADEND");
	}

	//�V�[���̕`��
	gpScene->Render();

#ifdef _DEBUG
	//�f�o�b�O�̕`��
	if (gbDebug)
	{
		gpScene->RenderDebug();
	}
#endif // _DEBUG

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
	gpScene->Release();
	delete gpScene;
	gpScene = NULL;
	gpLoading->Release();
	delete gpLoading;
	gpLoading = nullptr;

	//g_pResouseManager->Release();
	g_pSoundManager->Release();
	g_pEffectManager->Release();
	g_pTextureManager->Release();
	g_pAnimManager->Release();
	g_pTimeManager->Release();
	return TRUE;
}