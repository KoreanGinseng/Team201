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

//! GLOBAL
bool		g_bDebug = true;		//! �f�o�b�O�\���t���O

int			FPS = 60;

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

	SCENENO_FUJIWARA,
	SCENENO_INOUE,
	SCENENO_ONISHI,
	SCENENO_KIMURA,
};