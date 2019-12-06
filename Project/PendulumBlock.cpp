#include		"PendulumBlock.h"

CPendulumBlock::CPendulumBlock() : CEmpty() {


}

CPendulumBlock::~CPendulumBlock() {


}

void CPendulumBlock::Initialize(void)
{
}

bool CPendulumBlock::Load(void)
{
	RectLoad("RectTree.txt");
	return true;
}

void CPendulumBlock::Update(const bool & me)
{



}
