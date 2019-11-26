/**
 * @file Atack_TESTBOS3.cpp
 * @brief テストボス3の攻撃
 * @author 大西永遠
 * @date 更新日（11/22）
 */

#include	"Atack_TESTBOS3.h"


CAtack_TESTBOS3::CAtack_TESTBOS3() :
	CEnemyAtack() {

}
CAtack_TESTBOS3::~CAtack_TESTBOS3() {

}
void CAtack_TESTBOS3::Initialize() {
	m_bShow = false;
	m_fAtackTimer = 0;
	m_fCooltime = 0;
	//分身する剣
	/*for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i] = new CCloningSword();
		m_ShotArry[i]->Initialize();

	}*/

	//瞬間移動する剣
	for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i] = new CTeleportationSword();
		m_ShotArry[i]->Initialize();

	}
	m_TleCount = 0;

	//分身する敵
	for (m_EneCount = 0; m_EneCount < CloningCount;m_EneCount++) {
		m_KURIBO.ClonInitialize(m_EneCount);
	}
	m_EneCount = 0;

	//m_Texture.Load("Hp.png");
	m_ScaleMagnification = 0;
	m_TleTime = TLeTime;

	m_Counting = 1;
}

void CAtack_TESTBOS3::Update(float EnemyPosX, float EnemyPosY, bool EnemyRevers, float PlayerPosX, float PlayerPosY) {
	//X座標の攻撃範囲
	if (EnemyPosX - BosAtackRange < PlayerPosX&&EnemyPosX + BosAtackRange > PlayerPosX) {
		if (m_fAtackTimer >= 0 && m_fCooltime <= 0) {
			m_fAtackTimer -= 1 * CUtilities::GetFrameSecond();
			if (m_fAtackTimer < 0) {
				m_fCooltime = CoolTime;
				m_bShow = false;
			}
		}
		if (m_fCooltime >= 0 && m_fAtackTimer <= 0) {
			m_fCooltime -= 1 * CUtilities::GetFrameSecond();
			if (m_fCooltime < 0) {
				m_fAtackTimer = AtackTimer;
				float rd = m_ShotArry[2]->GetRadian(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);
				float ddx = m_ShotArry[2]->Getddx(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);
				float ddy = m_ShotArry[2]->Getddy(EnemyPosX, EnemyPosY, PlayerPosX, PlayerPosY);

				int rnd = rand() % 5;

				//for (int i = 0; i < CloningCount; i++) {
				//	/*if (m_ShotArry->GetShow()) {
				//		continue;
				//	}*/



				//	m_ShotArry[i]->Initialize();
				//	if (i==2) {
				//		m_ShotArry[i]->Fire(EnemyPosX, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY);
				//	}
				//	else
				//	{
				//		m_ShotArry[i]->CloningFire(EnemyPosX + i * CloningDistance - CloningDistance*2, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY,rd,ddx,ddy);
				//	}


				//	
				//}
				//m_ShotArry[rnd]->SetFrag(true);


				m_fAtackPosX = EnemyPosX;
				m_fAtackPosY = EnemyPosY;
			}
		}

		m_bShow = true;

	}


	//for (int i = 0; i < CloningCount; i++) {
	//	m_ShotArry[i]->Update();
	//}

	////分身敵
	//m_KURIBO.ClonUpdate(m_EneCount); 
	//m_KURIBO.CollisionStage(m_EneCount);

	//m_EneCount++;
	//if (m_EneCount==CloningCount) {
	//	m_EneCount = 0;
	//}

	///*m_EneCount += m_Counting;
	//if (m_EneCount == CloningCount) {
	//	m_Counting = -1 ;
	//	m_EneCount == CloningCount - 1;
	//}
	//else if (m_EneCount == 0) {
	//	m_Counting = 1 ;
	//}*/

	////瞬間移動
	//if (m_ShotArry[m_TleCount]->GetTleEnd()) {
	//	return;
	//}
	//m_TleTime -= 1 * CUtilities::GetFrameSecond();
	//if (m_TleTime <= 0) {
	//	m_TleCount = rand() % 5;
	//	m_TleTime = TLeTime;
	//}

	//右手
	if (!m_Hand.GetMoveFlag()) {
		m_Hand.Initialize();
		m_Hand.Start(PlayerPosX);
	}
	m_Hand.Update(PlayerPosX, PlayerPosY);
	m_Hand.CollisionStage();
}
void CAtack_TESTBOS3::Render() {

	//分身剣
	/*for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i]->Render();

	}*/
	
	//右手
	m_Hand.Render(m_fAtackPosX,m_fAtackPosY);

	//瞬間移動
	m_ShotArry[m_TleCount]->Render();

	m_KURIBO.ClonRender(m_EneCount);

}
void CAtack_TESTBOS3::Release() {
	for (int i = 0; i < CloningCount; i++) {
		if (m_ShotArry) {
			m_ShotArry[i]->Release();
			delete[] m_ShotArry[i];
			m_ShotArry[i] = NULL;
		}
	}
	

}