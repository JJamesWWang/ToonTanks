// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"
#include "ToonTanks/GameModes/TankGameModeBase.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = DefaultHealth;
	GameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(
	AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage == 0 || Health <= 0)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.f, DefaultHealth);
	UE_LOG(LogTemp, Warning, TEXT("%s took damage; health remaining: %f"), *GetOwner()->GetName(), Health);
	if (Health <= 0.f)
	{
		if (GameMode)
		{
			GameMode->ActorDied(GetOwner());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Health component has no reference to the GameMode."));
		}
	}
}
