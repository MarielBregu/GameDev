// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Data/ComboAttackData.h"
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


	// Assegna dall’editor la tua DT_ComboAttack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	UDataTable* ComboTable = nullptr;

	
	//Sarebbe il get data table row del Bp
	//
	UFUNCTION(BlueprintCallable, Category="Combat|Combo")
	bool GetDataTableRow_ComboAttack(const FString& Sequence, FComboAttackData& OutRow) const; 



public:
	
	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UInputBufferComponent* InputBuffer;
};
	

