/*****************************************************************
 *	@file			Onishi.h
 *	@brief			�I�I�j�V�V�[���N���X
 *	@author			����D�R
 *	@date			2019/07/29
 *****************************************************************/
#pragma once

 //! INCLUDE
#include	"../SceneBase.h"
#include	"EnemyMove.h"
#include	"Enemy_KURIBO.h"
#include	"Enemy_NOKONOKO.h"
#include	"Enemy_TERESA.h"
#include	"Enemy_BAT.h"
#include	"Enemy_KOTEIHOUDAI.h"
#include	"../Enemy_TESTBOS.h"
#include	"../Enemy_FLOATING.h"
#include	"../Enemy_POISONKURIBO.h"
#include	"../Enemy_TESTBOS2.h"
#include	"../Enemy_TESTBOS3.h"
#include	"../Atack_KURIBO.h"
#include	"../Atack_NOKONOKO.h"
#include	"../Atack_TERESA.h"
#include	"../Atack_BAT.h"
#include	"../Atack_KOTEIHOUDAI.h"
#include	"../Atack_TESTBOS.h"
#include	"../Atack_POISONKURIBO.h"
#include	"../Atack_TESTBOS2.h"
#include	"../Atack_TESTBOS3.h"
#define		spead 20
 /*****************************************************************
  *	@brief			�I�I�j�V�V�[���N���X
  *	@author			����D�R
  *****************************************************************/
class COnishi : public CSceneBase {
private:
	bool poase;
	float time;
	float Xpos;
	float Ypos;
	float MXpos;
	float MYpos;
	bool atack;
	bool h;
	float getxpos;
	float getypos;
	float getx;
	float gety;
	bool Revers;
	int gEnemytype;
	CEnemyMove* gEnemy;
	CEnemy_KURIBO*	gKURIBO;
	CENEMY_NOKONOKO*	gNOKONOKO;
	CENEMY_TERESA*	gTERESA;
	CENEMY_BAT*	gBAT;
	CENEMY_KOTEIHOUDAI*	gKOTEIHOUDAI;
	CEnemy_TESTBOS* gTESTBOS;
	CENEMY_FLOATING* gFLOATING;
	CEnemy_POISONKURIBO* gPOISONKURIBO;
	CEnemy_TESTBOS* gTESTBOS2;
	CEnemyAtack* gAtack;
	CAtack_KURIBO* gAtack_KURIBO;
	CAtack_TESTBOS* gAtack_TESTBOS;
	CAtack_TESTBOS* gAtack_TESTBOS2;
	
public:
	/*****************************************************************
	 * @fn
	 * �����Ȃ��R���X�g���N�^
	 * @param �Ȃ�
	 * @return �Ȃ�
	 *****************************************************************/
	COnishi();

	/*****************************************************************
	 * @fn
	 * �����Ȃ��f�X�g���N�^
	 * @param �Ȃ�
	 * @return �Ȃ�
	 *****************************************************************/
	~COnishi();

	/*****************************************************************
	 * @fn
	 * �K�v�ȑf�ނ̓ǂݍ���
	 * @param �Ȃ�
	 * @return �Ȃ�
	 *****************************************************************/
	void Load();

	/*****************************************************************
	 * @fn
	 * ������
	 * @param �Ȃ�
	 * @return �Ȃ�
	 *****************************************************************/
	void Initialize();

	/*****************************************************************
	 * @fn
	 * �X�V
	 * @param �Ȃ�
	 * @return �Ȃ�
	 *****************************************************************/
	void Update();

	/*****************************************************************
	 * @fn
	 * �`��
	 * @param �Ȃ�
	 * @return �Ȃ�
	 *****************************************************************/
	void Render();

	/*****************************************************************
	 * @fn
	 * �f�o�b�O�`��
	 * @param �Ȃ�
	 * @return �Ȃ�
	 *****************************************************************/
	void RenderDebug();

	/*****************************************************************
	 * @fn
	 * ���
	 * @param �Ȃ�
	 * @return �Ȃ�
	 *****************************************************************/
	void Release();
};