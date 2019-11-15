/*****************************************************************
 *	@file			GameDefine.h
 *	@brief			�Q�[���̒�`�t�@�C��
 *	@author			����D�R
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

#define		GAMEFPS			60		//! �Q�[���ɐݒ肳��Ă���FPS�̒l

#define		STAGE_COUNT		4		//! �Q�[���X�e�[�W��
#define		START_STAGE		0		//! �Q�[���J�n�X�e�[�W�ԍ�

#define		GRAVITY			0.3f	//! �Q�[�����d��

#define		PLAYER_MAXHP			2
#define		PLAYER_MAXSTOCK			3
#define		PLAYER_MAXSPEED			8
#define		PLAYER_SPEED			0.3f
#define		PLAYER_MAXSKILLRANGE	512.0f
#define		PLAYER_JUMPPOW			-10.0f
#define		PLAYER_HIGHJUMPPOW		-15.0f

#define		g_pAnimManager		CResourceManager<CAnimationData>::GetInstance()
#define		g_pTextureManager	CResourceManager<CTexture>::GetInstance()
#define		g_pSoundManager		CResourceManager<CSoundBuffer>::GetInstance()

constexpr	char			picture[] = "picture";
constexpr	char			anim[] = "anim";

constexpr	char*	AnimName[] = {
	//��{
	"�ҋ@",
	"�ړ�",
	"�W�����v",
	"�U��",
	"�U��2",
	"�U��3",
	"�U��4",
	//�I�u�W�F�N�g
	"���Ă���",
	"�����Ă���",
	"������",
};

constexpr	char*	FileName[] = {
	//TEXTURE
	"player3.png",
	"EnemyKinoko.png",
	"EnemyDoku.png",
	"EnemyBat.png",
	"enemy04.png",
	"enemy05.png",
	"enemy06.png",
	"enemy07.png",
	"enemy08.png",
	"Item01.png",
	"Item02.png",
	"Item03.png",
	"Item04.png",
	"Item05.png",
	"Item06.png",
	"Item07.png",
	"Item08.png",
	"obj_rope03.png",
	"Obj_Tree01.png",
	"obj_bridge03.png",
	"Obj04.png",
	"Obj05.png",
	"Obj06.png",
	"Obj07.png",
	"Obj08.png",
	"bg.png",
	"bgChip01.png",
	"bgChip02.png",
	"MapChip02.png",
	"sumple_imvisible.png",
	//ANIMATION
	"playerAnim.bin",
	"EnemyKinokoAnim.bin",
	"EnemyDokuAnim.bin",
	"EnemyBatAnim.bin",
	"EnemyAnim01.bin",
	"OctAnim.bin",
	"EnemyAnim06.bin",
	"EnemyAnim07.bin",
	"EnemyAnim08.bin",
	"ItemAnim01.bin",
	"ItemAnim02.bin",
	"ItemAnim03.bin",
	"ItemAnim04.bin",
	"ItemAnim05.bin",
	"ItemAnim06.bin",
	"ItemAnim07.bin",
	"ItemAnim08.bin",
	"RopeAnim.bin",
	"obj_treeanim01.bin",
	"BridgeAnim.bin",
	"ObjAnim04.bin",
	"ObjAnim05.bin",
	"ObjAnim06.bin",
	"ObjAnim07.bin",
	"ObjAnim08.bin",
	//SOUND
	"TestJump.mp3",
	"TestStageBGM.mp3",
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
 * �V�[���ԍ��̗�
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
 * �e�N�X�`���t�@�C���̗�
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
	TEXTURE_MAP_BACK,
	TEXTURE_MAP_BACKCHIP_1,
	TEXTURE_MAP_BACKCHIP_2,
	TEXTURE_MAP_CHIP,
	TEXTURE_FONT,

	TEXTURE_COUNT,
}TEXTUREDATA;

/*****************************************************************
 * @enum tag_ANIMATIONDATA
 * �A�j���[�V�����t�@�C���̗�
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
 * @enum tag_SOUNDDATA
 * �T�E���h�t�@�C���̗�
 *****************************************************************/
typedef enum tag_SOUNDDATA {
	SOUND_JUMP = ANIMATION_COUNT,
	SOUND_STAGEBGM,

	SOUND_COUNT,
}SOUNDDATA;




/*****************************************************************
 * @enum tag_ENEMY
 * �G�̗�
 *****************************************************************/
enum tag_ENEMY
{
	ENEMY_KURIBO,
	ENEMY_NOKONOKO,
	ENEMY_BAT,
	ENEMY_TERESA,
	ENEMY_KOTEIHOUDAI,
	ENEMY_TESTBOS,
	ENEMY_FLOATING,
	ENEMY_POISONKURIBO,
	ENEMY_TESTBOS2,
};

/*****************************************************************
 * @enum tag_OBJECT
 * �I�u�W�F�N�g�̗�
 *****************************************************************/
enum tag_OBJECT
{
	OBJECT_ROPE,
	OBJECT_BRIDGE,
	OBJECT_TREE01,
};


extern CXGamePad*			gpXGpad;

#define		g_pGamePad		gpXGpad

#include <crtdbg.h>
#define	  NEW					new
#ifdef _DEBUG
#define   NEW                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif