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

	gpXGpad = new CXGamePad();
	XGAMEPADCREATEINFO xc;
	g_pGamePad->Create(&xc);

	gpScene = new CGame();

	gpLoading = new CLoading();
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

	if (!gpLoading->IsEnd())
	{
		return TRUE;
	}
	
	gpScene->EffectFrame();

	gpScene->Update();

	if (gpScene->IsEnd())
	{
		int n = gpScene->GetNextSceneNo();
		gpScene->Release();
		NewPointerRelease(gpScene);
		NewPointerRelease(gpLoading);
		switch (n)
		{
		case SCENENO_GAME:
			gpScene = new CGame();
			break;
		case SCENENO_TITLE:
			gpScene = new CTitle();
			break;
		case SCENENO_GAMECLEAR:
			gpScene = new CGameClear();
			break;
		case SCENENO_GAMEOVER:
			gpScene = new CGameOver();
			break;
		case SCENENO_RANKING:
			gpScene = new CRanking();
			break;
		default:
			break;
		}
		gpLoading = new CLoading();
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

	if (!gpLoading->IsEnd())
	{
		//描画の終了
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

	g_pGamePad->Release();
	NewPointerRelease(gpXGpad);
	gpScene->Release();
	NewPointerRelease(gpScene);
	gpLoading->Release();
	NewPointerRelease(gpLoading);

	return TRUE;
}