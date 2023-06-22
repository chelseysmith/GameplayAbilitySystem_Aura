// Copyright Taffy Team


#include "Character/AuraEnemy.h"

#include "Aura/Aura.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	if (Weapon)
	{
		Weapon->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}
}

void AAuraEnemy::HighlightActor()
{
	ToggleHighlight(true);
}

void AAuraEnemy::UnHighlightActor()
{
	ToggleHighlight(false);
}

void AAuraEnemy::ToggleHighlight(bool bIsEnabled)
{
	GetMesh()->SetRenderCustomDepth(bIsEnabled);
	if (Weapon)
	{
		Weapon->SetRenderCustomDepth(bIsEnabled);
	}
}
