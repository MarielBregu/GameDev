#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "Types/AttackTypes.h"
#include "Data/ComboAttackData.h"
#include "DamageComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAMEDEV_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Costruttore
	UDamageComponent();

	/** Calcola il danno finale combinando ComboData, Stance e AttackType */
	UFUNCTION(BlueprintCallable, Category="Damage")
	float ComputeFinalDamage(const FComboAttackData& ComboData, const FGameplayTag& CurrentStance);

protected:

	/** Danni base per tipo di attacco (Light, Slam, ecc.) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage|Base")
	TMap<EAttackType, float> AttackTypeBaseDamages;

	/** Danni bonus per stance (Normal, Fire, Dragon, ecc.) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage|Base")
	TMap<FGameplayTag, float> StanceBaseDamages;


private:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category="Damage|Debug", meta=(AllowPrivateAccess="true"))
	float LastComputedDamage = 0.f;

};
