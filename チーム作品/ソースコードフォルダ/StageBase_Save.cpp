#include "StageBase.h"

SaveData* Stage_Base::GetSaveData()
{
	return m_pNowSaveFile;
}

void Stage_Base::SetSaveData(SaveData *SaveData)
{
	m_pNowSaveFile = SaveData;
}