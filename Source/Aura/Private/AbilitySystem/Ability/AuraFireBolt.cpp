// Copyright Taffy Team


#include "AbilitySystem/Ability/AuraFireBolt.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n"

			// Level
			"<Small>Level: </>"
			"<Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </>"
			"<ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </>"
			"<Cooldown>%.1f</>\n\n"

			// Description and Damage
			"<Default>Launches a bolt of fire, exploding on impact and dealing </>"
			"<Damage>%d</>"
			"<Default> damage with a chance to burn</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	else
	{
		return FString::Printf(TEXT(
			// Title
			"<Title>FIRE BOLT</>\n"

			// Level
			"<Small>Level: </>"
			"<Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </>"
			"<ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </>"
			"<Cooldown>%.1f</>\n\n"

			// Description and Damage
			"<Default>Launches </><Time>%d</><Default> bolts of fire, exploding on impact and dealing </>"
			"<Damage>%d</>"
			"<Default> damage with a chance to burn</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	
	return FString::Printf(TEXT(
			// Title
			"<Title>NEXT LEVEL</>\n"

			// Level
			"<Small>Level: </>"
			"<Level>%d</>\n"
			// ManaCost
			"<Small>ManaCost: </>"
			"<ManaCost>%.1f</>\n"
			// Cooldown
			"<Small>Cooldown: </>"
			"<Cooldown>%.1f</>\n\n"

			// Description and Damage
			"<Default>Launches </><Time>%d</><Default> bolts of fire, exploding on impact and dealing </>"
			"<Damage>%d</>"
			"<Default> damage with a chance to burn</>"),

			// Values
			Level,
			ManaCost,
			Cooldown,
			FMath::Min(Level, NumProjectiles),
			ScaledDamage);
}