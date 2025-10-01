#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Animation/AnimMontage.h"
#include "Types/AttackTypes.h"
#include "ComboAttackData.generated.h"

USTRUCT(BlueprintType)

struct FComboAttackData : public FTableRowBase

{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	 TSoftObjectPtr<UAnimMontage> Montage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAttackType AttackType = EAttackType::Normal;
	
};
