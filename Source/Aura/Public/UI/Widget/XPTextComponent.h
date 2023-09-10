// Copyright Taffy Team

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "XPTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UXPTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetXPText(int32 XP);
	
};
