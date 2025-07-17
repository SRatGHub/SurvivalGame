// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Resources_M.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "MyPlayer.generated.h"



UCLASS()
class SURVIVALGAME2_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void MoveForward(float axisValue);
	UFUNCTION()
		void MoveRight(float axisValue);
	UFUNCTION()
		void StartJump();
	UFUNCTION()
		void StopJump();
	UFUNCTION()
		void FindObject();
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* PlayerCamComp;
	
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Health = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Hunger = 100.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
		float Stamina = 100.0f;
	UFUNCTION(BlueprintCallable)
		void SetHealth(float amount);
	UFUNCTION(BlueprintCallable)
		void SetHunger(float amount);
	UFUNCTION()
		void DecreaseStats();
	UFUNCTION(BlueprintCallable)
		void SetStamina(float amount);


	UPROPERTY(EditAnywhere, Category = "Resources")
		int Wood;
	UPROPERTY(EditAnywhere, Category = "Resources")
		int Stone;
	UPROPERTY(EditAnywhere, Category = "Resources")
		int Berry;
	UPROPERTY(EditAnywhere, Category = "Resources")
		TArray<FString> ResourcesNameArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resources")
		TArray<int> ResourcesArray;

	UFUNCTION()
		void GiveResource(float amount, FString resourceType);

	UPROPERTY(EditAnywhere, Category = "HitMarker")
	UMaterialInterface* hitdecal;
};
