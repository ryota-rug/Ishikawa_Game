#include "Select_Data.h"


namespace
{
	SelectState::SELECT eSelect;
	SelectState::STAGE eStage;
}



SelectState::SELECT SelectState::GetSelect()
{
	return eSelect;
}

void SelectState::SetSelect(SelectState::SELECT select)
{
	eSelect = select;
}

SelectState::STAGE SelectState::GetStage()
{
	return eStage;
}

void SelectState::SetStage(SelectState::STAGE stage)
{
	eStage = stage;
}
