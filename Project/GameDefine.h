/*****************************************************************
 *	@file			GameDefine.h
 *	@brief			ゲームの定義ファイル
 *	@author			井上颯騎
 *	@date			2019/07/29
 *****************************************************************/
#pragma once
//! INCLUDE
#include	"Mof.h"

//! DEFINE
#define		GAMEFPS			60		//! ゲームに設定されているFPSの値

//! GLOBAL
bool		g_bDebug = true;		//! デバッグ表示フラグ

//! デバック表示位置定義
#define		DEBUGPOSX_FPS		g_pGraphics->GetTargetWidth() - 30	//! FPS表示位置X
#define		DEBUGPOSY_FPS		10									//! FPS表示位置Y

/*****************************************************************
 * @enum tag_SCENENO
 * シーン番号の列挙
 *****************************************************************/
enum tag_SCENENO {
	SCENENO_TITLE,
	SCENENO_GAME,
	SCENENO_GAMECLEAR,
	SCENENO_GAMEOVER,

	SCENENO_FUJIWARA,
	SCENENO_INOUE,
	SCENENO_ONISHI,
	SCENENO_KIMURA,
	SCENENO_TEST,
};