// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MyCharacter.h"
//#include "Data/ComboAttackData.h"
#include "Components/InputBufferComponent.h"


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


bool AMyCharacter::GetDataTableRow_ComboAttack(const FString& Sequence, FComboAttackData& OutRow) const
{
	if (!ComboTable) return false;

	//Creazione di RowName di tipo FName(Variabile) a partire dal *di sequence quindi il valore al suo interno
	//che sara la sequence messa su un input da Bp
	const FName RowName(*Sequence);

	/*CAssegno il valore a FComboAttackData a partire dal *di Row
	ComboTable e il puntatore alla nostra DataTable Su BP
	-> singifica acceddi al membro tramite puntatore quindi ComboTable accede a FComboAttackData
	Quindi dovra fare il FindRow ovvero leggere la riga ti tipo <ComboAttackData>
	quindi FComboAttackData si crea a partire dal *Row che e = a FindRow dentro il FindRow di <FComboAttackData>
	 cerca se esiste RownName(Sequence) all interno di FComboAttackData
	 */
	if (const FComboAttackData* Row = ComboTable->FindRow<FComboAttackData>(RowName, TEXT("ComboLookup")))
	{
		// Copia il contenuto della riga trovata nell'out param "OutRow".
		OutRow = *Row;
		// true = Row Found (in BP: Branch su Return Value → ramo True)
		return true;      
	}
	// false = Row Not Found.
	return false;          
}



