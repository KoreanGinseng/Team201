#include		"PendulumLine.h"

CPendulumLine::CPendulumLine() : CEmpty() {

	m_Aliment = RENDERTYPE_ROTATION;
	 deg = 1;
	 m_Rote = MOF_ToRadian(90);
}

CPendulumLine::~CPendulumLine() {


}

void CPendulumLine::Initialize(void)
{ 

}

bool CPendulumLine::Load(void)
{
	RectLoad("RectTree.txt");
	return true;
}

void CPendulumLine::Update(const bool & me)
{
	

	m_Rote += MOF_ToRadian(deg);
	int d = MOF_ToDegree(m_Rote);
	if ( d > 90||d<-90)
	{
		deg *= -1;
	}

}

Vector2 CPendulumLine::GetRectCenter() {

	float y = 192;
	float ang = m_Rote;
	float ca = cos(ang);
	float sa = sin(ang);
	float ax = -sa * y;
	float ay = ca * y;

	return Vector2(ax + m_pPos->x,ay + m_pPos->y);

}
