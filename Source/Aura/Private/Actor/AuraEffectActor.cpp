// Copyright Taffy Team


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
//#include "Components/SphereComponent.h"

AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));

	// Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	// SetRootComponent(Mesh);
	//
	// Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	// Sphere->SetupAttachment(GetRootComponent());
	// Sphere->SetSphereRadius(250.f);
	// Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();

	// Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraEffectActor::OnBeginOverlap);
	// Sphere->OnComponentEndOverlap.AddDynamic(this, &AAuraEffectActor::OnEndOverlap);
}

// void AAuraEffectActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	if (InstantGameplayEffectClass)
// 	{
// 		ApplyEffectToTarget(OtherActor, InstantGameplayEffectClass);
// 	}
// 	
// 	if (DurationGameplayEffectClass)
// 	{
// 		ApplyEffectToTarget(OtherActor, DurationGameplayEffectClass);
// 	}
//
// 	if (InfiniteGameplayEffectClass)
// 	{
// 		ApplyEffectToTarget(OtherActor, InfiniteGameplayEffectClass);
// 	}
// 	
// 	Destroy();
// }
//
// void AAuraEffectActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// }

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	
	if (TargetASC == nullptr) return;
	check(GameplayEffectClass);

	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle =
		TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);
	
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle =
		TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	const bool bIsInfinite =
		EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	
	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle, TargetASC);
	}
}

void AAuraEffectActor::OnBeginOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		for (FActiveGameplayEffectHandle& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}
