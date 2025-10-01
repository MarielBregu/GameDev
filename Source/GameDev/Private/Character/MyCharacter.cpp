// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "InputBufferComponent.h"


AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	InputBuffer = CreateDefaultSubobject<UInputBufferComponent>(TEXT("InputBuffer"));

}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



