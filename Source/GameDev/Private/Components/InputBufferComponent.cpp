#include "Components/InputBufferComponent.h"

UInputBufferComponent::UInputBufferComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


//Funzione Add input to buffer da Input action "E il valore che assegni ai IA_Attack vari"

void UInputBufferComponent::AddInputToBuffer(const FString& InputAction)
{
	// Se sto attaccando, bufferizzo l'input e segnalo pending
	if (bIsAttacking)
	{
		BufferedInput         = InputAction;
		bBufferedInputPending = true;
		return;
	}

	//Breanch False
	// Altrimenti accumulo nella sequenza
	// Sarebbe L'append oovvero  tra A "Input sequence" e B "InputAction", essendo che la sequence e vuota torna
	// il valore del input action
	
		InputSequence += InputAction;
		// Controllo soglia
		TryConsumeIfReady();
}

void UInputBufferComponent::TryConsumeIfReady()
{
	// Condition del tuo Branch in BP: LEN > MaxBufferSize
	if (InputSequence.Len() > MaxBufferSize)          
	{
		InputSequence.Empty();                        
		return;                                      
	}
	else                                             
	{
		// Passo la sequenza InputSequence Dentro OncomboAttempt(Seqeunce)
		OnComboAttempt.Broadcast(InputSequence);
	}
}

void UInputBufferComponent::ResetSequence()
{
	InputSequence.Empty();
}