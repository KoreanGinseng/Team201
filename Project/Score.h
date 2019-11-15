#pragma once

class CScore {

private:

	int		m_Score;
	int		m_Skill;
	int		m_Damage;

	static CScore*	m_pInstance;

	CScore(void) { m_Score = 0,m_Skill = 0,m_Damage = 0; }
	~CScore(void) = default;
public:

	static	CScore*		GetInstance(void) {

		if (m_pInstance == nullptr) {

			m_pInstance = new CScore();

		}

		return m_pInstance;

	}
	void		Release(void) {

		if (m_pInstance) {

			delete m_pInstance;
			m_pInstance = nullptr;

		}

	}
	void		TotalScore(int score) { m_Score = score * 100; }
	void		AddSkillCount(void) { m_Skill++; }
	void		AddDamageCount(void) { m_Damage++; }
	int			GetScore(void) { return m_Score - (m_Skill*100) - (m_Damage*500); }
};

#define		g_pScore		CScore::GetInstance()
