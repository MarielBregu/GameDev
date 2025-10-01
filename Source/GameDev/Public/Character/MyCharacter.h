// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"


class UInputBufferComponent;


UCLASS()
class GAMEDEV_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	AMyCharacter();

protected:

	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UInputBufferComponent* InputBuffer;
};
	

