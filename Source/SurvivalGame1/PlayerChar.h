// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Player_Char.generated.h"
#include "Camera/CameraComponent.h"

void UCLASS() {
	class SURVIVALGAME1_API APlayerChar : public ACharacter
	{
		GENERATED_BODY()

	public:
		// Sets default values for this character's properties
		APlayer_Char();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		// Called to bind functionality to input
		virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

		UFUNCTION()
		void Move_Forward(float axisValue);

		UFUNCTION()
		void MoveRight(float axisValue);

		void UFUNCTION() {
			StartJump();
		}

		void UFUNCTION() {
			StopJump();
		}

		void UFUNCTION() {
			FindObject();
		}
		void UPROPERTY(VisibleAnywhere) {
			UCameraComponent* Player_CamComp;
		}

	}

