/*****************************************************************
 *	@file			GameDefine.h
 *	@brief			ゲームの定義ファイル
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

 //INCLUDE
#include	"Mof.h"
#include	"_Inoue/ResourceManager.h"
#include	"SoundManager.h"
#include	"Coordinate.h"


//USING
using CTexturePtr = std::shared_ptr<CTexture>;
using CMotionPtr = std::shared_ptr<CSpriteMotionController>;

#include	"_Inoue/AnimationData.h"

//DEFINE

#define		GAMEFPS			60		//! ゲームに設定されているFPSの値

#define		STAGE_COUNT		3		//! ゲームステージ数
#define		START_STAGE		0		//! ゲーム開始ステージ番号

#define		GRAVITY			0.3f	//! ゲーム内重力

#define		PLAYER_MAXHP			10
#define		PLAYER_MAXSTOCK			3
#define		PLAYER_MAXSPEED			8
#define		PLAYER_SPEED			0.3f
#define		PLAYER_MAXSKILLRANGE	512.0f
#define		PLAYER_JUMPPOW			-10.0f
#define		PLAYER_HIGHJUMPPOW		-15.0f

#define		g_pAnimManager		CResourceManager<CAnimationData>::GetInstance()
#define		g_pTextureManager	CResourceManager<CTexture>::GetInstance()
#define		g_pSoundManager		CResourceManager<CSoundBuffer>::GetInstance()


constexpr	char*	FileName[] = {
	"playerAnim.bin",
	"",
	"",
	"",
	"",
	".png",
	"",
	"",
	"",
	".mp3",
	"",
};

//STRUCT


//ENUM
typedef enum tag_WAY {
	WAY_X,
	WAY_Y,
}WAY;

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

/*****************************************************************
 * @enum tag_TEXTUREDATA
 * テクスチャファイルの列挙
 *****************************************************************/
typedef enum tag_TEXTUREDATA {
	TEXTURE_PLAYER,
	TEXTURE_ENEMY_1,
	TEXTURE_ENEMY_2,
	TEXTURE_ENEMY_3,
	TEXTURE_ENEMY_4,
	TEXTURE_ENEMY_5,
	TEXTURE_ENEMY_6,
	TEXTURE_ENEMY_7,
	TEXTURE_ENEMY_8,
	TEXTURE_ITEM_1,
	TEXTURE_ITEM_2,
	TEXTURE_ITEM_3,
	TEXTURE_ITEM_4,
	TEXTURE_ITEM_5,
	TEXTURE_ITEM_6,
	TEXTURE_ITEM_7,
	TEXTURE_ITEM_8,
	TEXTURE_OBJ_1,
	TEXTURE_OBJ_2,
	TEXTURE_OBJ_3,
	TEXTURE_OBJ_4,
	TEXTURE_OBJ_5,
	TEXTURE_OBJ_6,
	TEXTURE_OBJ_7,
	TEXTURE_OBJ_8,
	TEXTURE_ENEMY_ATTACK,
	TEXTURE_MAP_BACK,
	TEXTURE_MAP_BACKCHIP_1,
	TEXTURE_MAP_BACKCHIP_2,
	TEXTURE_MAP_CHIP,
	TEXTURE_FONT,

	TEXTURE_COUNT,
}TEXTUREDATA;

/*****************************************************************
 * @enum tag_ANIMATIONDATA
 * アニメーションファイルの列挙
 *****************************************************************/
typedef enum tag_ANIMATIONDATA {
	ANIMATION_PLAYER = TEXTURE_COUNT,
	ANIMATION_ENEMY_1,
	ANIMATION_ENEMY_2,
	ANIMATION_ENEMY_3,
	ANIMATION_ENEMY_4,
	ANIMATION_ENEMY_5,
	ANIMATION_ENEMY_6,
	ANIMATION_ENEMY_7,
	ANIMATION_ENEMY_8,
	ANIMATION_ITEM_1,
	ANIMATION_ITEM_2,
	ANIMATION_ITEM_3,
	ANIMATION_ITEM_4,
	ANIMATION_ITEM_5,
	ANIMATION_ITEM_6,
	ANIMATION_ITEM_7,
	ANIMATION_ITEM_8,
	ANIMATION_OBJ_1,
	ANIMATION_OBJ_2,
	ANIMATION_OBJ_3,
	ANIMATION_OBJ_4,
	ANIMATION_OBJ_5,
	ANIMATION_OBJ_6,
	ANIMATION_OBJ_7,
	ANIMATION_OBJ_8,

	ANIMATION_COUNT,
}ANIMATIONDATA;






/*****************************************************************
 * @enum tag_ENEMY
 * 敵の列挙
 *****************************************************************/
enum tag_ENEMY
{
	ENEMY_KURIBO,
	ENEMY_NOKONOKO,
	ENEMY_TERESA,
	ENEMY_BAT,
	ENEMY_KOTEIHOUDAI,
};