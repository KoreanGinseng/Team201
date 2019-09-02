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

#define		STAGE_COUNT		3		//! ゲームステージ数


#define		PLAYER_WIDTH	60
#define		PLAYER_HEIGHT	64
#define		PLAYER_MAXHP	100
#define		PLAYER_MAXLIFE	3
#define		PLAYER_MAXSPEED	8
#define		PLAYER_GRAVITY	0.3f
#define		GRAVITY			0.3f

//! GLOBAL
extern bool		g_bDebug;			//! デバッグ表示フラグ

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
	SCENENO_RANKING,

	SCENENO_FUJIWARA,
	SCENENO_INOUE,
	SCENENO_ONISHI,
	SCENENO_KIMURA,
};