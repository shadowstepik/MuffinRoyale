// Fill out your copyright notice in the Description page of Project Settings.


#include "StateComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UStateComponent::UStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


void UStateComponent::OnRep_Fullness()
{
	OnFullnessChangedDelegate.Broadcast();
}

void UStateComponent::OnRep_MaxFullness()
{
	OnFullnessChangedDelegate.Broadcast();
}

void UStateComponent::AddFullness(float Value)
{
	Fullness = Fullness + Value;
	if (GetOwnerRole() == ROLE_Authority)
	{
		OnRep_Fullness();
	}
}

void UStateComponent::RemoveFullness(float Value)
{
	Fullness = Fullness - Value;
	if (GetOwnerRole() == ROLE_Authority)
	{
		OnRep_Fullness();
	}
}

void UStateComponent::AddMaxFullness(float Value)
{
	MaxFullness = MaxFullness + Value;
	if (GetOwnerRole() == ROLE_Authority)
	{
		OnRep_Fullness();
	}

}

void UStateComponent::RemoveMaxFullness(float Value)
{
	MaxFullness = MaxFullness - Value;
	if (GetOwnerRole() == ROLE_Authority)
	{
		OnRep_Fullness();
	}

}

void UStateComponent::Dead()
{
	OnDeadDelegate.Broadcast();
}

// Called when the game starts
void UStateComponent::BeginPlay()
{
	Super::BeginPlay();
	UActorComponent::SetIsReplicated(true);
	MyUnitState = E_UnitState::Alive;
	MaxFullness = ConstMaxFullness;
	Fullness = StartFullness;
	// ...

}


// Called every frame
void UStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStateComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStateComponent, Fullness);
	DOREPLIFETIME(UStateComponent, MaxFullness);
	DOREPLIFETIME(UStateComponent, MyUnitState);

};
