/*****************************************************************
 *	@file			GameDefine.h
 *	@brief			ゲームの定義ファイル
 *	@author			井上颯騎
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

 //INCLUDE
#include	"Mof.h"
#include	"ResourceManager.h"
#include	"Coordinate.h"


//USING
using CTexturePtr = std::shared_ptr<CTexture>;
using RectArray = CDynamicArray<CRectangle>;

#include	"AnimationData.h"
#include	"TimeManager.h"

//DEFINE

#define		GAMEFPS			60		//! ゲームに設定されているFPSの値

#define		STAGE_COUNT		4		//! ゲームステージ数
#define		START_STAGE		0		//! ゲーム開始ステージ番号

#define		GRAVITY			0.3f	//! ゲーム内重力
#define		GRAVITYMAX		20.0f	//! ゲーム内重力

#define		PLAYER_MAXHP			6
#define		PLAYER_MAXSTOCK			3
#define		PLAYER_MAXSPEED			8
#define		PLAYER_SPEED			0.3f
#define		PLAYER_MAXSKILLRANGE	512.0f
#define		PLAYER_JUMPPOW			-11.0f

//#define		g_pAnimManager		CResourceManager<CAnimationData>::GetInstance()
//#define		g_pSoundManager		CResourceManager<CSoundBuffer>::GetInstance()
//#define		g_pTextureManager	CResourceManager<CTexture>::GetInstance()
#include	"AnimationManager.h"
#include	"SoundManager.h"
#include	"TextureManager.h"
#include	"EffectManager.h"
#define		g_pAnimManager		CAnimationManager::GetAnimation()
#define		g_pTextureManager	CTextureManager::GetTexture()
#define		g_pSoundManager		CSoundManager::GetSound()
#define		g_pEffectManager	CEffectManager::GetEffect()

extern bool					gbDebug;

constexpr	char			picture[] = "picture";
constexpr	char			anim[] = "anim";

constexpr	char*	FileName[] = {
	//TEXTURE
	"player.png",
	"ene_Mash2.png",
	"ene_MashPoison.png",
	"ene_Bat.png",
	"ene_Oct.png",
	"ene_Hand.png",
	"ene_Bat.png",
	"ene_Boss1.png",
	"enemy08.png",
	"enemy09.png",

	"Item01.png",
	"Item02.png",
	"Item03.png",
	"Item04.png",
	"Item05.png",
	"Item06.png",
	"Item07.png",
	"Item08.png",
	"Rope.png",
	"Tree01.png",

	"Bridge.png",
	"SavePoint.png",
	"CameraPoint.png",
	"Object_Pole.png",
	"Obj07.png",
	"Obj08.png",

	"bg1.png",
	"bg2.png",
	"bg3.png",
	"空.png",
	"cloud01.png",
	"cloud02.png",
	"cloud03.png",
	"mapchip1.png",
	"mapchip2.png",
	"mapchip3.png",
	"Font.png",
	"bomc.png",

	//ANIMATION
	"PlayerAnim001.bin",
	"AnimEneMash.bin",
	"AnimEneMashPoison.bin",
	"AnimEneBat.bin",
	"AnimEneOct.bin",
	"AnimEneHand.bin",
	"AnimEneBat.bin",
	"AnimEneBoss1.bin",
	"EnemyAnim08.bin",
	"EnemyAnim09.bin",
	"ItemAnim01.bin",
	"ItemAnim02.bin",
	"ItemAnim03.bin",
	"ItemAnim04.bin",
	"ItemAnim05.bin",
	"ItemAnim06.bin",
	"ItemAnim07.bin",
	"ItemAnim08.bin",
	"Rope.bin",
	"Tree01.bin",
	"Bridge.bin",
	"SavePoint.bin",
	"CameraPoint.bin",
	"Object_Pole01.bin",
	"Hummer.bin",
	"Door.bin",
	"Object_Tresure.bin",
	"suitti.bin",
	"Renga.bin",
	"Object_Floor01.bin",
	"Object_Floor04.bin",
	"HEAL.bin",

	//EFFECT
	"Effect_Explosion.bin",

	//SOUNDSE
	"TestJump.mp3",

	//SOUNDBGM
	"TestStageBGM.mp3",

	//RECT
	"RectRope.txt",
	"RectTree.txt",
	"RectBridge.txt",
	"RectSavePoint.txt",
	"RectCameraPoint.txt",
	"RectPole.txt",
	"RectHummer.txt",
	"RectDoor.txt",
	"RectTresure.txt",
	"RectPushSwitch.txt",
	"RectRenga.txt",
	"RectMoveFloor1.txt",
	"RectMoveFloor4.txt",
	"RectHeal.txt",
};

//ENUM
typedef enum tag_WAY {
	WAY_X,
	WAY_Y,
}WAY;

enum tag_ANIMMOTION {
	MOTION_WAIT,
	MOTION_MOVE,
	MOTION_JUMP,
	MOTION_ATTACK,
	MOTION_ATTACK2,
	MOTION_ATTACK3,
	MOTION_ATTACK4,
	MOTION_BREAK,
	MOTION_CLEAN,
	MOTION_DELETE,
};

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
	TEXTURE_ENEMY_9,
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
	TEXTURE_MAP_BACK1,
	TEXTURE_MAP_BACK2,
	TEXTURE_MAP_BACK3,
	TEXTURE_MAP_SORA,
	TEXTURE_MAP_BACKCHIP_1,
	TEXTURE_MAP_BACKCHIP_2,
	TEXTURE_MAP_BACKCHIP_3,
	TEXTURE_MAP_CHIP1,
	TEXTURE_MAP_CHIP2,
	TEXTURE_MAP_CHIP3,
	TEXTURE_FONT,
	TEXTURE_EFFECT_EXPROSION,

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
	ANIMATION_ENEMY_9,
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
	ANIMATION_OBJ_9,
	ANIMATION_OBJ_10,
	ANIMATION_OBJ_11,
	ANIMATION_OBJ_12,
	ANIMATION_OBJ_13,
	ANIMATION_OBJ_14,

	ANIMATION_COUNT,
}ANIMATIONDATA;

typedef enum tag_EFFECRDATA {
	EFFECTDATA_EXPROSION = ANIMATION_COUNT,

	EFFECTDATA_COUNT,
}EFFECTDATA;

/*****************************************************************
 * @enum tag_SOUNDDATA
 * サウンドファイルの列挙
 *****************************************************************/
typedef enum tag_SOUNDSEDATA {
	SOUND_SE_JUMP = EFFECTDATA_COUNT,

	SOUND_SE_COUNT,
}SOUNDSEDATA;

typedef enum tag_SOUNDBGMDATA {
	SOUND_BGM_STAGE1 = SOUND_SE_COUNT,

	SOUND_BGM_COUNT,
}SOUNDBGMDATA;

enum tag_RECTDATA {
	RECT_OBJ_1 = SOUND_BGM_COUNT,
	RECT_OBJ_2,
	RECT_OBJ_3,
	RECT_OBJ_4,
	RECT_OBJ_5,
	RECT_OBJ_6,
	RECT_OBJ_7,
	RECT_OBJ_8,
	RECT_OBJ_9,
	RECT_OBJ_10,
	RECT_OBJ_11,

	RECT_OBJ_12,
	RECT_OBJ_13,
	
	RECT_OBJ_14,

	RECT_OBJ_COUNT,
};

/*エフェクトの種類*/
enum tag_EFFECTTYPE {

	EFFECT_EXPROSION,

	EFFECT_TYPECOUNT,

};

/*****************************************************************
 * @enum tag_ENEMY
 * 敵の列挙
 *****************************************************************/
enum tag_ENEMY
{
	ENEMY_MASH,
	ENEMY_POISUNMASH,
	ENEMY_BAT,
	ENEMY_OCT,
	ENEMY_HAND,
	ENEMY_FLOATING,
	ENEMY_BOSS_1,
	ENEMY_BOSS_2,
	ENEMY_BOSS_3,
};

/*****************************************************************
 * @enum tag_OBJECT
 * オブジェクトの列挙
 *****************************************************************/
enum tag_OBJECT
{
	OBJECT_ROPE,
	OBJECT_TREE01,
	OBJECT_BRIDGE,
	OBJECT_SAVEPOINT,
	OBJECT_CAMERACNTRL,
	OBJECT_POLE,
	OBJECT_HAMMER,
	OBJECT_DOOR,
	OBJECT_TRESURE,
	OBJECT_PUSHSWITCH,
	OBJECT_RENGA,

	OBJECT_MOVEFLOOR1,
	OBJECT_MOVEFLOOR2,
	OBJECT_MOVEFLOOR3,
	OBJECT_MOVEFLOOR4,
	OBJECT_MOVEFLOOR5,
	OBJECT_MOVEFLOOR6,

	OBJECT_HEAL,
};

enum tag_RENDERTYPE
{
	RENDER_BACKBACK,
	RENDER_BACKSTAGE,
};

enum tag_SUBTYPE
{
	SUB_ENE,
	SUB_OBJ,
	SUB_ITEM,
	SUB_SHOT,
};

enum tag_SUBSTATUS
{
	SUBSTATUS_BACK,
	SUBSTATUS_NOMAL,
	SUBSTATUS_TRIP,
	SUBSTATUS_STOP,
};

enum tag_CAMERADATA {
	CAMERA_MOVE_BRIDGE,
	CAMERA_MOVE_BOSS,
};

struct CameraCntrlData {
	Vector2	targetPos;
	int		second;
};

extern CXGamePad*			gpXGpad;

#define		g_pGamePad		gpXGpad