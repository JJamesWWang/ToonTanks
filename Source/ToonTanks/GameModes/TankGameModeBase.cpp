// Fill out your copyright notice in the Description page of Project Settings.

#include "TankGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void ATankGameModeBase::HandleGameStart()
{
	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));
	GameStart();
	if (PlayerController)
	{
		PlayerController->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate =
			FTimerDelegate::CreateUObject(PlayerController, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), Turrets);
	return Turrets.Num();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);
		if (PlayerController)
		{
			PlayerController->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		if (--TargetTurrets <= 0)
		{
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	GameOver(PlayerWon);
}
