// Fill out your copyright notice in the Description page of Project Settings.


#include "Resources_M.h"

// Sets default values
AResources_M::AResources_M()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ResourceNameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Render"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = Mesh;

	ResourceNameText->SetupAttachment(Mesh);


}

// Called when the game starts or when spawned
void AResources_M::BeginPlay()
{
	Super::BeginPlay();

	tempText = tempText.FromString(resourceName);

	ResourceNameText->SetText(tempText);
	
}

// Called every frame
void AResources_M::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

