#include		"PendulumLine.h"

CPendulumLine::CPendulumLine() : CEmpty() {


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
	
}
