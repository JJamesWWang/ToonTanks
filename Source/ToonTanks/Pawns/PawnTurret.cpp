// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnTurret.h"

#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

APawnTurret::APawnTurret()
{
}

void APawnTurret::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);
}

void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive() || GetDistanceToPlayer() > FireRange)
	{
		return;
	}
	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	// If Player is null or is Dead, return
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
	{
		return;
	}

	if (GetDistanceToPlayer() <= FireRange)
	{
		Fire();
	}
}

float APawnTurret::GetDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}
