/**
 * @file Atack_TESTBOS3.cpp
 * @brief �e�X�g�{�X3�̍U��
 * @author �吼�i��
 * @date �X�V���i11/22�j
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
	//���g���錕
	/*for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i] = new CCloningSword();
		m_ShotArry[i]->Initialize();

	}*/

	//�u�Ԉړ����錕
	for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i] = new CTeleportationSword();
		m_ShotArry[i]->Initialize();

	}
	m_TleCount = 0;

	//���g����G
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
	//X���W�̍U���͈�
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

	////���g�G
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

	////�u�Ԉړ�
	//if (m_ShotArry[m_TleCount]->GetTleEnd()) {
	//	return;
	//}
	//m_TleTime -= 1 * CUtilities::GetFrameSecond();
	//if (m_TleTime <= 0) {
	//	m_TleCount = rand() % 5;
	//	m_TleTime = TLeTime;
	//}

	//�E��
	if (!m_Hand.GetMoveFlag()) {
		m_Hand.Initialize();
		m_Hand.Start(PlayerPosX);
	}
	m_Hand.Update(PlayerPosX, PlayerPosY);
	m_Hand.CollisionStage();
}
void CAtack_TESTBOS3::Render() {

	//���g��
	/*for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i]->Render();

	}*/
	
	//�E��
	m_Hand.Render(m_fAtackPosX,m_fAtackPosY);

	//�u�Ԉړ�
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