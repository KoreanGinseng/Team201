/**
 * @file Enemy_Atack.cpp
 * @brief �G�l�~�[�̍U��
 * @author �吼�i��
 * @date �X�V���i10/29�j
 */

#include "EnemyAtack.h"
#include "mof.h"

CEnemyAtack::CEnemyAtack() :
	m_fAtackPosX(0.0f),
	m_fAtackPosY(0.0f),
	m_fTime(0),
	m_bShow(false) {
}

CEnemyAtack::~CEnemyAtack() {
}
/**
 * @brief	������
 * @return ����
 */
void CEnemyAtack::Initialize() {

}
/**
 * @brief	�N���{�[�X�V
 * @param (EposX) �G�l�~�[��X���W
 * @param (EposY) �G�l�~�[��Y���W
 * @param (ERevers) �G�l�~�[�̕���
 * @return ����
 */
void CEnemyAtack::Update(float EemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {
	
}
/**
 * @brief	�`��
 * @return ����
 */
void CEnemyAtack::Render() {

}