/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
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
bool				g_bDebug = true;	//! デバッグ表示フラグ
CSceneBase*			g_pScene = nullptr;	//! シーン格納ポインタ


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
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//開始シーン
	g_pScene = new CGame();			//ゲームシーンからスタート(デバック用)
	//g_pScene = new CTitle();		//タイトルシーンからスタート


	//読み込みカレントディレクトリの設定
	CUtilities::SetCurrentDirectoryA("Resource");

	//シーンの読み込み
	g_pScene->Load();
	//シーンの初期化
	g_pScene->Initialize();

	//FPSの設定
	if (!CUtilities::SetFPS(GAMEFPS)) 
	{
		return FALSE;
	}
	a.Start("Loading");
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

	//シーンの更新
	g_pScene->Update();

	//次のシーンに行くとき
	if (g_pScene->IsEnd()) 
	{
		//次のシーンを取得
		int change = g_pScene->GetNextScene();
		//古いシーンを削除
		delete g_pScene;
		//新しいシーンを取得
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
		//新しいシーンの読み込みと初期化
		g_pScene->Load();
		g_pScene->Initialize();
	}

	//F1キーでデバッグフラグの切り替え
	if (g_pInput->IsKeyPush(MOFKEY_F1)) 
	{
		g_bDebug = !g_bDebug;
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

	//シーンの描画
	g_pScene->Render();

	if (a.bEnd)
	{
		CGraphicsUtilities::RenderString(0, 0, "LoadEnd");
	}
	else
	{
		CGraphicsUtilities::RenderString(0, 0, "Load...");
	}
	//デバッグ表示
	if (g_bDebug) 
	{
		//シーンのデバッグ描画
		g_pScene->RenderDebug();
		//FPSの表示
		CGraphicsUtilities::RenderString(DEBUGPOSX_FPS, DEBUGPOSY_FPS, "%d", CUtilities::GetFPS());
	}
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
	g_pScene->Release();

	//シーンの削除
	if (g_pScene) 
	{
		delete g_pScene;
		//削除したポインタには0を入れる
		g_pScene = NULL;
	}

	return TRUE;
}