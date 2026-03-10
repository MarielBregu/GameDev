// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/DamageComponent.h"
#include "Data/ComboAttackData.h"
#include "GameplayTagContainer.h"
#include "MyCharacter.generated.h"

class UInputBufferComponent;
class UInputTagBufferComponent; 

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
	UFUNCTION(BlueprintCallable, Category="Combat|Combo")
	bool GetDataTableRow_ComboAttack(const FString& Sequence, FComboAttackData& OutRow) const; 

	UFUNCTION(BlueprintPure, Category="Combat|Stance")
	FGameplayTag MakeStancedInputTag(const FGameplayTag& BaseInputTag) const;


public:
	
	virtual void Tick(float DeltaTime) override;


	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Stance")
	FGameplayTag CurrentStance;



	

	
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UInputBufferComponent* InputBuffer;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UInputTagBufferComponent* InputTagBuffer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta=(AllowPrivateAccess="true"))
	UDamageComponent* DamageComponent;




};
	

