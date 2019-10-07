/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
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
#include	"SoundManager.h"
#include	"Loading.h"

//GLOBAL
CSceneBase*		gpScene = nullptr;
CLoading		gLoading;

#ifdef _DEBUG
bool			gbDebug = false;
#endif // _DEBUG


/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	CUtilities::SetCurrentDirectory("Resource");
	
	gpScene = new CTitle();			//タイトルから開始

#ifdef _DEBUG
	gpScene = new CGame();			//ゲームシーンから開始(デバッグ用)
#endif // _DEBUG

	/*gLoading.SetLoad(gpScene->Load);
	gLoading.SetInit(gpScene->Initialize);*/
	gLoading.SetScene(gpScene);
	gLoading.Start("Loading");

	//FPSの設定
	if (!CUtilities::SetFPS(GAMEFPS))
	{
		return FALSE;
	}
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

	if (!gLoading.IsEnd())
	{
		return TRUE;
	}

	//シーンの更新
	gpScene->Update();

	//シーン切り替え
	if (gpScene->IsEnd())
	{
		//次のシーン番号取得
		int nextScene = gpScene->GetNextSceneNo();
		
		//古いシーンを解放
		gpScene->Release();
		delete gpScene;
		
		//次のシーンを生成
		switch (nextScene)
		{
		case SCENENO_TITLE:
			gpScene = new CTitle();
			break;
		case SCENENO_GAME:
			gpScene = new CGame();
			break;
		case SCENENO_GAMEOVER:
			gpScene = new CTitle();
			break;
		case SCENENO_GAMECLEAR:
			gpScene = new CGame();
			break;
		case SCENENO_RANKING:
			gpScene = new CGame();
			break;
		case SCENENO_FUJIWARA:
			gpScene = new CTitle();
			break;
		case SCENENO_INOUE:
			gpScene = new CGame();
			break;
		case SCENENO_KIMURA:
			gpScene = new CTitle();
			break;
		case SCENENO_ONISHI:
			gpScene = new CGame();
			break;
		}
		//別スレッドでやりたい。(LOADING)
		{
			gLoading.Start("Loading");
		}
	}

#ifdef _DEBUG
	//F1キーでデバッグ表示の切り替え
	if (g_pInput->IsKeyPush(MOFKEY_F1))
	{
		gbDebug = !gbDebug;
	}
#endif // _DEBUG

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
	g_pGraphics->ClearTarget(0.0f,0.0f,0.0f,0.0f,1.0f,0);

	if (!gLoading.IsEnd())
	{
		CGraphicsUtilities::RenderString(0, 0, "LOADING");
		//描画の終了
		g_pGraphics->RenderEnd();
		return TRUE;
	}
	else
	{
		CGraphicsUtilities::RenderString(0, 0, "LOADEND");
	}

	//シーンの描画
	gpScene->Render();

#ifdef _DEBUG
	//デバッグの描画
	if (gbDebug)
	{
		gpScene->RenderDebug();
	}
#endif // _DEBUG

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
	
	//シーンの解放
	gpScene->Release();
	delete gpScene;
	gpScene = NULL;

	//g_pResouseManager->Release();
	g_pSoundManager->Release();
	g_pEffectManager->Release();
	g_pTextureManager->Release();
	g_pAnimManager->Release();
	return TRUE;
}