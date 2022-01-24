// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MuffinRoyale/MuffinRoyale.h"
#include "AbilitySystemInterface.h"
#include <GameplayEffectTypes.h>
#include "MuffinRoyale/GASAbilitySystemComponent.h"
#include "MuffinRoyale/GASAttributeSet.h"
#include "GameFramework/Pawn.h"
#include "Abilities/GameplayAbility.h"
#include "GASBasePawn.generated.h"

UCLASS()
class MUFFINROYALE_API AGASBasePawn : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGASBasePawn();

	//virtual void RemovePawnAbilities();

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	class UGASAttributeSet* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetSugar() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGASGameplayAbility>> PawnAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
		TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Gameplay")
		UGASAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Gameplay")
		UGASAttributeSet* AttributeSetBase = nullptr;

	UFUNCTION(BlueprintCallable)
		virtual int32 GetAbilityLevel(EGASAbilityInputID AbilityID) const;


	virtual void SugarChanged(const FOnAttributeChangeData& Data);

	FDelegateHandle SugarChangedDelegateHandle;

	virtual void AddPawnAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	/*virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;*/

};
