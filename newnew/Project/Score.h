#pragma once

class CScore {

private:

	int		m_Score;
	int		m_Skill;
	int		m_Damage;

	static CScore*	m_pInstance;

	CScore(void) { m_Score = 0; }
	~CScore(void) = default;
public:

	static	CScore*		GetInstance(void) {

		if (m_pInstance == nullptr) {

			m_pInstance = NEW CScore();

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
	int			GetScore(void) { return m_Score - m_Skill - m_Damage; }
};

#define		g_pScore		CScore::GetInstance()
