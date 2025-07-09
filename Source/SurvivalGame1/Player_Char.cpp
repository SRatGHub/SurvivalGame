// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_Char.h"

// Sets default values
APlayer_Char::APlayer_Char()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam"));

	PlayerCamComp->SetupAttachment(GetMesh(), "head");

	PlayerCamComp->bUsePawnControlRotation = true;
	


}

// Called when the game starts or when spawned
void APlayer_Char::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayer_Char::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayer_Char::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move_Forward", this, &APlayer_Char::Move_Forward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayer_Char::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayer_Char::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APlayer_Char::AddControllerYawInput);
	PlayerInputComponent->BindAxis("JumpEvent", IE_Pressed, this, &APlayer_Char::StartJump);
	PlayerInputComponent->BindAxis("JumpEvent", IE_Released, this, &APlayer_Char::StopJump);
}

void APlayer_Char::Move_Forward(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axisValue);
}

void APlayer_Char::StartJump()
{
	bPressedJump = true;
}
void APlayer_Char::StopJump()
{
	bPressJump = false;
}
void APlayer_Char::FindObject()
{

}
void APlayer_Char::MoveRight(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, axisValue);
}

