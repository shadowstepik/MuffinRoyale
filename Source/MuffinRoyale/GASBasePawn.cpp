// Fill out your copyright notice in the Description page of Project Settings.


#include "GASBasePawn.h"
#include "GameplayAbilitySpec.h"

// Sets default values
AGASBasePawn::AGASBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UGASAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UGASAttributeSet>(TEXT("AttributeSetBase"));

	NetUpdateFrequency = 100.0f;
}

int32 AGASBasePawn::GetAbilityLevel(EGASAbilityInputID AbilityID) const
{
	return 1;
}

UGASAttributeSet* AGASBasePawn::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

float AGASBasePawn::GetSugar() const
{
	return AttributeSetBase->GetSugar();
}

// Called when the game starts or when spawned
void AGASBasePawn::BeginPlay()
{
	Super::BeginPlay();

	AddPawnAbilities();
	InitializeAttributes();
	AddStartupEffects();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (AbilitySystemComponent)
	{
		// Attribute change callbacks
		SugarChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetSugarAttribute()).AddUObject(this, &AGASBasePawn::SugarChanged);

	}

}

void AGASBasePawn::AddPawnAbilities()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->PawnAblilitiesGiven)
	{
		return;
	}

	for (TSubclassOf<UGASGameplayAbility>& StartupAbility : PawnAbilities)
	{
		/*AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility, 1, 0, this));*/
	}

	AbilitySystemComponent->PawnAblilitiesGiven = true;
}

void AGASBasePawn::InitializeAttributes()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

void AGASBasePawn::AddStartupEffects()
{
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent || AbilitySystemComponent->StartupEffectsApplied)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}

	AbilitySystemComponent->StartupEffectsApplied = true;
}

void AGASBasePawn::SugarChanged(const FOnAttributeChangeData& Data)
{
	return;
}

// Called every frame
void AGASBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
//void AGASBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}
