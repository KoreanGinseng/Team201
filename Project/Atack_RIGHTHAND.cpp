/**
 * @file Atack_RIGHTHAND.cpp
 * @brief　右手の攻撃
 * @author 大西永遠
 * @date 更新日（12/3）
 */

#include	"Atack_RIGHTHAND.h"

CAtack_RIGHTHAND::CAtack_RIGHTHAND() :
	CEnemyAtack()
	/*m_Limit(false)*/{

}
CAtack_RIGHTHAND::~CAtack_RIGHTHAND() {

}
void CAtack_RIGHTHAND::Initialize() {
	
}
void CAtack_RIGHTHAND::Initialize(float posX, float posY) {
	//m_Limit = false;
	//m_Impact.Initialize();
	//m_Impact.Fire(posX,posY);
	//m_fAtackPosX = posX;
	//m_fAtackPosY = posY;
}

void CAtack_RIGHTHAND::Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {

}

//bool CAtack_RIGHTHAND::UpdateWave() {
//	if (!m_Limit) {
//		return;
//	}
//	m_Impact.Update();
//}

void CAtack_RIGHTHAND::Render() {
	//if (!m_Limit) {
	//	return;
	//}
	//m_Impact.Render();
}
void CAtack_RIGHTHAND::Release() {

}