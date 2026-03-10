#include "Components/DamageComponent.h"
#include "GameplayTagContainer.h"


UDamageComponent::UDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	// Inizializza alcuni valori di default (puoi modificarli in editor)
	AttackTypeBaseDamages.Add(EAttackType::Normal, 15.f);
	AttackTypeBaseDamages.Add(EAttackType::Slash, 30.f);
	AttackTypeBaseDamages.Add(EAttackType::Slam, 50.f);
	AttackTypeBaseDamages.Add(EAttackType::Finisher, 20.f);

	// Creazione tag stance base
	const FGameplayTag NormalTag = FGameplayTag::RequestGameplayTag(FName("Stance.Normal"));
	const FGameplayTag FireTag   = FGameplayTag::RequestGameplayTag(FName("Stance.Fire"));
	const FGameplayTag WindTag   = FGameplayTag::RequestGameplayTag(FName("Stance.Wind"));

	StanceBaseDamages.Add(NormalTag, 10.f);
	StanceBaseDamages.Add(FireTag, 15.f);
	StanceBaseDamages.Add(WindTag, 10.f);
}


float UDamageComponent::ComputeFinalDamage(const FComboAttackData& ComboData, const FGameplayTag& CurrentStance)
{

	//Calcola il danno totale:
	//se vuoi puoi sommare anche ComboData.BaseDamage
	float FinalDamage = ComboData.Damage;

	//Bonus Tipo Attacco
	if (const float* AttackBonus = AttackTypeBaseDamages.Find(ComboData.AttackType))
	{
		FinalDamage += *AttackBonus;
	}

	//bonus Stance
	if (const float* StanceBonus = StanceBaseDamages.Find(CurrentStance))
	{
		FinalDamage += *StanceBonus;
	}

	//Salva per uso in blueprint
	LastComputedDamage = FinalDamage;

	return FinalDamage;	
}