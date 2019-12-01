/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"SceneBase.h"
#include	"Loading.h"
#include	"Game.h"
#include	"Title.h"
#include	"GameClear.h"
#include	"GameOver.h"
#include	"Ranking.h"

CSceneBase*			gpScene = nullptr;
CLoading*			gpLoading = nullptr;

CXGamePad*			gpXGpad = nullptr;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	CUtilities::SetCurrentDirectory("Resource");

	if (!CUtilities::SetFPS(GAMEFPS))
	{
		return FALSE;
	}

	gpXGpad = NEW CXGamePad();
	XGAMEPADCREATEINFO xc;
	xc.No = 0;
	g_pGamePad->Create(&xc);

	gpScene = NEW CGame();

	gpLoading = NEW CLoading();
	gpLoading->SetStartUp(TRUE);
	gpLoading->SetScene(gpScene);
	gpLoading->Start("Loading");

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();
	g_pGamePad->RefreshKey();

	if (!gpLoading->IsSceneStart())
	{
		if (gpLoading->IsEnd())
		{
			if (g_pInput->IsKeyPush(MOFKEY_A) || g_pInput->IsKeyPush(MOFKEY_RETURN) || g_pGamePad->IsKeyPush(XINPUT_A))
			{
				gpLoading->SceneStart();
			}
		}
		return TRUE;
	}
	
	gpScene->EffectFrame();

	gpScene->Update();

	if (gpScene->IsEnd())
	{
		bool loadPush = true;
		int n = gpScene->GetNextSceneNo();
		gpScene->Release();
		NewPointerRelease(gpScene);
		NewPointerRelease(gpLoading);
		switch (n)
		{
		case SCENENO_GAME:
			loadPush = false;
			gpScene = NEW CGame();
			break;
		case SCENENO_TITLE:
			gpScene = NEW CTitle();
			break;
		case SCENENO_GAMECLEAR:
			gpScene = NEW CGameClear();
			break;
		case SCENENO_GAMEOVER:
			gpScene = NEW CGameOver();
			break;
		case SCENENO_RANKING:
			gpScene = NEW CRanking();
			break;
		default:
			break;
		}
		gpLoading = NEW CLoading();
		gpLoading->SetStartUp(loadPush);
		gpLoading->SetScene(gpScene);
		gpLoading->Start("Loading");
	}

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	if (!gpLoading->IsSceneStart())
	{
		//描画の終了
		gpLoading->Render();
		g_pGraphics->RenderEnd();
		return TRUE;
	}

	gpScene->Render();
	gpScene->RenderUI();
	gpScene->EffectRender();

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void){
	gpLoading->Join();
	g_pGamePad->Release();
	NewPointerRelease(gpXGpad);
	gpScene->Release();
	NewPointerRelease(gpScene);
	gpLoading->Release();
	NewPointerRelease(gpLoading);
	g_pEffectManager->Release();
	g_pSoundManager->Release();
	g_pTextureManager->Release();
	g_pAnimManager->Release();
	g_pTimeManager->Release();
	g_pScore->Release();
	return TRUE;
}