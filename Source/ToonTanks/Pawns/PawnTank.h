// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"

#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 *
 */
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

public:
	APawnTank();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool GetIsPlayerAlive();
	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.f;

	FVector MoveDirection;
	FQuat RotationDirection;
	APlayerController* PlayerController = nullptr;

	bool bIsPlayerAlive = true;

	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);

	void Move();
	void Rotate();
};
