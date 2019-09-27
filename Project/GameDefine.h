/*****************************************************************
 *	@file			GameDefine.h
 *	@brief			�Q�[���̒�`�t�@�C��
 *	@author			����D�R
 *	@date			2019/07/29
 *****************************************************************/
#pragma once
//! INCLUDE
#include	"Mof.h"

//! DEFINE
#define		GAMEFPS			60		//! �Q�[���ɐݒ肳��Ă���FPS�̒l

#define		STAGE_COUNT		3		//! �Q�[���X�e�[�W��
#define		START_STAGE		0		//! �Q�[���J�n�X�e�[�W�ԍ�


#define		PLAYER_WIDTH	192
#define		PLAYER_HEIGHT	192
#define		PLAYER_MAXHP	100
#define		PLAYER_MAXLIFE	3
#define		PLAYER_MAXSPEED	8
#define		PLAYER_GRAVITY	0.3f
#define		GRAVITY			0.3f

//! GLOBAL
extern bool		g_bDebug;			//! �f�o�b�O�\���t���O

//! �f�o�b�N�\���ʒu��`
#define		DEBUGPOSX_FPS		g_pGraphics->GetTargetWidth() - 30	//! FPS�\���ʒuX
#define		DEBUGPOSY_FPS		10									//! FPS�\���ʒuY

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
	TEXTURE_OBJ_1,
	TEXTURE_OBJ_2,
	TEXTURE_OBJ_3,
	TEXTURE_OBJ_4,
	TEXTURE_ENEMY_ATTACK,
	TEXTURE_MAP_BACK,
	TEXTURE_MAP_BACKCHIP_1,
	TEXTURE_MAP_BACKCHIP_2,
	TEXTURE_MAP_CHIP,

	TEXTURE_COUNT,
}TEXTUREDATA;

/*****************************************************************
 * @enum tag_ANIMATIONDATA
 * �A�j���[�V�����t�@�C���̗�
 *****************************************************************/
typedef enum tag_ANIMATIONDATA {
	ANIMATION_PLAYER,
	ANIMATION_ENEMY_1,
	ANIMATION_ENEMY_2,
	ANIMATION_ENEMY_3,
	ANIMATION_OBJ_1,
	ANIMATION_OBJ_2,
	ANIMATION_OBJ_3,
	ANIMATION_OBJ_4,

	ANIMATION_COUNT,
}ANIMATIONDATA;