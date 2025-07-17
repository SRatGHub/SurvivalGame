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

	ResourcesArray.SetNum(3);
	ResourcesNameArray.Add(TEXT("Wood"));
	ResourcesNameArray.Add(TEXT("Stone"));
	ResourcesNameArray.Add(TEXT("Berry"));

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle StartTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(StartTimerHandle, this, &AMyPlayer::DecreaseStats, 2.0f, true);
	
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
	FHitResult HitResult;
	FVector StartLocation = PlayerCamComp->GetComponentLocation();
	FVector Direction = PlayerCamComp->GetForwardVector() * 800.0f;
	FVector EndLocation = StartLocation + Direction;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnFaceIndex = true;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams))
	{
		AResources_M* HitResource = Cast<AResources_M>(HitResult.GetActor());

		if (Stamina > 5.0f)
		{



			if (HitResource)
			{
				FString hitName = HitResource->resourceName;
				int resourceValue = HitResource->resourceAmount;

				HitResource->totalResource = HitResource->totalResource - resourceValue;

				if (HitResource->totalResource > resourceValue)
				{
					GiveResource(resourceValue, hitName);

					check(GEngine != nullptr);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Collected"));

					UGameplayStatics::SpawnDecalAtLocation(GetWorld(), hitdecal, FVector(10.0f, 10.0f, 10.0f), HitResult.Location, FRotator(-90, 0, 0), 2.0f);

					SetStamina(-5.0f);
				}
				else
				{
					HitResource->Destroy();
					check(GEngine != nullptr);
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Resource Depleted"));
				}
			}
		}
	}
}

void AMyPlayer::SetHealth(float amount)
{
	if (Health + amount < 100)
	{
		Health = Health + amount;
	}
}

void AMyPlayer::SetHunger(float amount)
{
	if (Hunger + amount < 100) {
		Hunger = Hunger + amount;
	}
}

void AMyPlayer::DecreaseStats()
{
	if (Hunger > 0)
	{
		SetHunger(-1.0f);
	}
	
	SetStamina(10.0f);

	if (Hunger <=0)
	{
		SetHealth(-3.0f);
	}
}

void AMyPlayer::SetStamina(float amount)
{
	if (Stamina + amount < 100)
	{
		Stamina = Stamina + amount;
	}
}

void AMyPlayer::GiveResource(float amount, FString resourceType)
{
	if (resourceType == "Wood")
	{
		ResourcesArray[0] = ResourcesArray[0] + amount;
	}
	if (resourceType == "Stone")
	{
		ResourcesArray[1] = ResourcesArray[1] + amount;
	}
	if (resourceType == "Berry")
	{
		ResourcesArray[2] = ResourcesArray[2] + amount;
	}
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

