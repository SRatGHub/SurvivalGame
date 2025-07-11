// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Cam"));

	//Initial setup of the camera component

	//Attaching Camera to Skeletal Mesh and Head bone
	PlayerCamComp->SetupAttachment(GetMesh(), "head");

	//Share Rotation with Controller
	PlayerCamComp->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Bindings for the Controller Inputs
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyPlayer::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AMyPlayer::AddControllerYawInput);
	PlayerInputComponent->BindAction("JumpEvent", IE_Pressed, this, &AMyPlayer::StartJump);
	PlayerInputComponent->BindAction("JumpEvent", IE_Released, this, &AMyPlayer::StopJump);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyPlayer::FindObject);
}


void AMyPlayer::StartJump()
{//The player jumps when the button is pressed
	bPressedJump = true;
}

void AMyPlayer::StopJump()
{//The player doesn't jump when the button isn't pressed
	bPressedJump = false;
}

void AMyPlayer::FindObject()
{
}

void AMyPlayer::MoveForward(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, axisValue);
}

void AMyPlayer::MoveRight(float axisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, axisValue);
}

