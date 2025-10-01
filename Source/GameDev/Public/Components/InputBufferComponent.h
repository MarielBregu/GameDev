#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "InputBufferComponent.generated.h"



//Dichiarazione Evento/Delegato
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComboAttempt, const FString&, Sequence);

UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class GAMEDEV_API UInputBufferComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInputBufferComponent();

	UFUNCTION(BlueprintCallable, Category="Combat|Input Buffer")
	void AddInputToBuffer(const FString& InputAction);

	UFUNCTION(BlueprintCallable, Category="Combat|Input Buffer")
	void SetIsAttacking(bool bInIsAttacking) { bIsAttacking = bInIsAttacking; }

	UFUNCTION(BlueprintCallable, Category="Combat|Input Buffer")
	void ResetSequence();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Input Buffer")
	bool bIsAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat|Input Buffer")
	FString BufferedInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat|Input Buffer")
	bool bBufferedInputPending = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Combat|Input Buffer")
	FString InputSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Input Buffer", meta=(ClampMin="1"))
	int32 MaxBufferSize = 4;

	UPROPERTY(BlueprintAssignable, Category="Combat|Input Buffer")
	FOnComboAttempt OnComboAttempt;

private:
	void TryConsumeIfReady();
};
