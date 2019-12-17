#include		"PendulumLine.h"

CPendulumLine::CPendulumLine() : CEmpty() {
	m_Aliment = RENDERTYPE_ROTATION;
	deg = 90;
	m_Rote = MOF_ToRadian(deg);
	m_CosSpd = 0.05f;
	m_CosTime = 0;
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

	bool a = false, b = false;
void CPendulumLine::Update(const bool & me)
{	
	////U‚èq‚ÌŒvZ
	////d—Í‰Á‘¬“x1ƒGƒlƒ‹ƒM[

	////‰Á‘¬‚·‚é
	//deg += LineSpd * 10.1f;
	////”½“]‚·‚é
	//if (deg < 0 && LineSpd < 0)
	//{
	//	LineSpd *= -1;
	//	a = true;
	//}
	//if (deg < -90 && b)
	//{
	//	b = true;
	//}
	//if (deg > 0 && LineSpd > 0 && b)
	//{
	//	LineSpd *= -1;
	//	b = false;
	//	a = false;
	//}
	//MOF_PRINTLOG("%.f\n", deg);

	////LineSpd += 0.1;
	////if (LineSpd > 1)
	////{
	////	LineSpd = 1;
	////}
	////deg += LineSpd;
	//
	////d(U‚èq‚ÌŠp“x)‚ª90“x‚É‚È‚é‚Æ”½“]‚·‚é

	////if (deg > 90|| deg < -90)
	////{
	////	deg *= -1;
	////	LineSpd *= -1;
	////}
	//m_Rote = MOF_ToRadian(deg);

	m_CosTime+= m_CosSpd;
	float c = cos(m_CosTime);
	m_Rote = MOF_ToRadian(80) * c;//copysignf((c * c), c);
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
