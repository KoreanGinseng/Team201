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


#define		PLAYER_WIDTH	60
#define		PLAYER_HEIGHT	64
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