#include		"Pendulum.h"

CPendulum::CPendulum() : CEmpty() {


}

CPendulum::~CPendulum() {


}

void CPendulum::Initialize(void)
{
}

bool CPendulum::Load(void)
{
	RectLoad("RectTree.txt");
	return true;
}

void CPendulum::Update(const bool & me)
{

}
