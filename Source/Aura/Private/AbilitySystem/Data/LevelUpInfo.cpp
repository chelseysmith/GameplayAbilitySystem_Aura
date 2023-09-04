// Copyright Taffy Team


#include "AbilitySystem/Data/LevelUpInfo.h"

FAuraLevelUpInfo ULevelUpInfo::FindLevelUpInfoForExperience(int32 Experience)
{
	int32 Index = 0;
	for (const FAuraLevelUpInfo& LevelUpInfo : LevelUpInformation)
	{
		if (Experience >= LevelUpInfo.LevelUpRequirement)
		{
			Index++;
		}
		else break;
	}
	return LevelUpInformation[Index];
}

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		if (LevelUpInformation.Num() - 1 <= Level) return Level;

		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			Level++;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}
