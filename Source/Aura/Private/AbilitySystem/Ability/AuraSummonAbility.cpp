// Copyright Taffy Team


#include "AbilitySystem/Ability/AuraSummonAbility.h"

#include "NavigationSystem.h"
#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();

	const float DeltaSpread = SpawnSpread / NumMinions;
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	
	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i + DeltaSpread / 2.f, FVector::UpVector);
		const FVector ChosenSpawnLocation = Location + Direction * FMath::FRandRange(MinSpawnDistance, MaxSpawnDistance);

		FNavLocation NavLocation;
		if (UWorld* World = GetWorld())
		{
			UNavigationSystemV1* NavigationSystemV1 = UNavigationSystemV1::GetCurrent(World);
			if (NavigationSystemV1->ProjectPointToNavigation(ChosenSpawnLocation, NavLocation))
			{
				SpawnLocations.Add(NavLocation.Location);
			}
			//else i--; This could cause a lock if the entire Angle was unable to spawn an enemy. Look into this in the future.
		}
	}

	const FVector RightOfSpread = Forward.RotateAngleAxis(SpawnSpread / 2.f, FVector::UpVector);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + RightOfSpread * MaxSpawnDistance, 4.f, FLinearColor::Green, 5.f);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location, Location + LeftOfSpread * MaxSpawnDistance, 4.f, FLinearColor::Red, 5.f);
	
	return SpawnLocations;	
}
