// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFullnessChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

UENUM(BlueprintType)
enum class E_UnitState : uint8
{
	None		UMETA(DisplayName = "None"),
	Alive		UMETA(DisplayName = "Alive"),
	Dead		UMETA(DisplayName = "Dead"),
	Attacking	UMETA(DisplayName = "Attacking"),
	Walk		UMETA(DisplayName = "Walk")
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), DisplayName = "StateComponent", Blueprintable)
class MUFFINROYALE_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStateComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)const;

	UPROPERTY(BlueprintAssignable)
		FOnFullnessChanged OnFullnessChangedDelegate;

	UPROPERTY(BlueprintAssignable)
		FOnDead OnDeadDelegate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated)
		E_UnitState MyUnitState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing = OnRep_Fullness)
		float Fullness;

	UFUNCTION(BlueprintCallable)
		void OnRep_Fullness();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing = OnRep_MaxFullness)
		float MaxFullness;

	UFUNCTION(BlueprintCallable)
		void OnRep_MaxFullness();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ConstMaxFullness;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float StartFullness;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage;

	UFUNCTION(BlueprintCallable)
		void AddFullness(float Value);

	UFUNCTION(BlueprintCallable)
		void RemoveFullness(float Value);

	UFUNCTION(BlueprintCallable)
		void AddMaxFullness(float Value);

	UFUNCTION(BlueprintCallable)
		void RemoveMaxFullness(float Value);

	UFUNCTION(BlueprintCallable)
		void Dead();

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};