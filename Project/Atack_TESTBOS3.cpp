/**
 * @file Atack_TESTBOS3.cpp
 * @brief �e�X�g�{�X3�̍U��
 * @author �吼�i��
 * @date �X�V���i11/19�j
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
	for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i] = new CCloningSword();
		m_ShotArry[i]->Initialize();

	}

	//���g����G
	for (m_Count = 0; m_Count < CloningCount;m_Count++) {
		m_KURIBO.ClonInitialize(m_Count);
	}
	m_Count = 0;
	//m_Texture.Load("Hp.png");
	m_ScaleMagnification = 0;
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

				for (int i = 0; i < CloningCount; i++) {
					/*if (m_ShotArry->GetShow()) {
						continue;
					}*/



					m_ShotArry[i]->Initialize();
					if (i==2) {
						m_ShotArry[i]->Fire(EnemyPosX, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY);
					}
					else
					{
						m_ShotArry[i]->CloningFire(EnemyPosX + i * CloningDistance - CloningDistance*2, EnemyPosY, BulletSpeed, BulletSpeed, PlayerPosX, PlayerPosY,rd,ddx,ddy);
					}


					
				}
				m_ShotArry[rnd]->SetFrag(true);

				m_fAtackPosX = EnemyPosX;
				m_fAtackPosY = EnemyPosY;
			}
		}

		m_bShow = true;

	}
	for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i]->Update();
	}
	m_KURIBO.ClonUpdate(m_Count); 
	m_KURIBO.CollisionStage(m_Count);
	m_Count++;
	if (m_Count==CloningCount) {
		m_Count = 0;
	}
}
void CAtack_TESTBOS3::Render() {
	for (int i = 0; i < CloningCount; i++) {
		m_ShotArry[i]->Render();

	}

	m_KURIBO.ClonRender(m_Count);

	//m_Texture.RenderScaleRotate(m_fAtackPosX,m_fAtackPosY,m_ScaleMagnification,1.0f, MOF_ToRadian(30));

}
void CAtack_TESTBOS3::Release() {
	for (int i = 0; i < CloningCount; i++) {
		if (m_ShotArry) {
			m_ShotArry[i]->Release();
			delete[] m_ShotArry[i];
			m_ShotArry[i] = NULL;
		}
	}
	//m_Texture.Release();

}