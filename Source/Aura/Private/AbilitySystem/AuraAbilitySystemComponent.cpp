// Copyright Taffy Team


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AuraGameplayTags.h"

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);

	/*const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	GameplayTags.Attributes_Secondary_Armor.ToString();*/
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer TagContainer;
	GameplayEffectSpec.GetAllAssetTags(TagContainer);

	if (TagContainer.Num() > 0)
	{
		EffectAssetTags.Broadcast(TagContainer);
	}
	
	for (const FGameplayTag& Tag: TagContainer)
	{
		//TODO: Broadcast the tag to the Widget Controller
		
	}
}
