/*****************************************************************
 *	@file			GameDefine.h
 *	@brief			�Q�[���̒�`�t�@�C��
 *	@author			����D�R
 *	@date			2019/09/29
 *****************************************************************/
#pragma once

 //INCLUDE
#include	"Mof.h"

//DEFINE
#define		GAMEFPS			60		//! �Q�[���ɐݒ肳��Ă���FPS�̒l

#define		STAGE_COUNT		3		//! �Q�[���X�e�[�W��
#define		START_STAGE		0		//! �Q�[���J�n�X�e�[�W�ԍ�

#define		GRAVITY			0.3f	//! �Q�[�����d��

//ENUM
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