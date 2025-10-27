#include "Components/InputTagBufferComponent.h"

// Costruttore: disattiva il Tick perché la logica è tutta event-driven (input/notifiche)
UInputTagBufferComponent::UInputTagBufferComponent() 
{
    PrimaryComponentTick.bCanEverTick = false;
}

// -----------------------------------------------------------------------------
// MakeKeyFromTags
// Scorre la sequenza di tag e crea una FString unica separata da pipe 
// da usare come RowName nella tua DataTable (compatibile con il tuo codice).
// -----------------------------------------------------------------------------
FString UInputTagBufferComponent::MakeKeyFromTags(const TArray<FGameplayTag>& Tags)
{
    FString Out;
    for (int32 i = 0; i < Tags.Num(); ++i)
    {
        if (i > 0) Out += TEXT("|");               // separatore tra un input e l'altro
        Out += Tags[i].ToString();                 // es: "Input.Attack.Light"
    }
    return Out;
}

// -----------------------------------------------------------------------------
// AddInputTagToBuffer
// - Se il tag non è valido → esce.
// - Se sto attaccando → salva questo input come "pending" (non modifica la sequenza).
// - Se NON sto attaccando → aggiunge subito alla sequenza e notifica TryConsumeIfReady.
// -----------------------------------------------------------------------------
void UInputTagBufferComponent::AddInputTagToBuffer(const FGameplayTag& InputTag)
{
    if (!InputTag.IsValid())                      // evita tag non registrati o vuoti
        return;

    if (bIsAttacking)
    {
        // Sto eseguendo un attacco: non accodo subito, ma tengo in sospeso
        BufferedInputTag      = InputTag;
        bBufferedInputPending = true;
        return;
    }

    // Non sto attaccando: posso accodare direttamente
    InputSequenceTags.Add(InputTag);

    // Applica la logica di soglia + notifica
    TryConsumeIfReady();
}

// -----------------------------------------------------------------------------
// TryConsumeIfReady
// - Se la lunghezza della sequenza supera MaxBufferSize → la svuota e basta.
// - Altrimenti costruisce la chiave "TagA|TagB|TagC" e la emette con OnTagSequence.
//   (Da BP userai questa chiave per fare FindRow nella DataTable, come già facevi.)
// -----------------------------------------------------------------------------
void UInputTagBufferComponent::TryConsumeIfReady()
{
    if (InputSequenceTags.Num() > MaxBufferSize)
    {
        // Overflow: reset soft della sequenza (comportamento equivalente al tuo)
        InputSequenceTags.Empty();
        return;
    }

    // Sequenza valida: notifica verso BP la chiave da usare per la DataTable
    const FString Key = MakeKeyFromTags(InputSequenceTags);
    OnComboAttempt.Broadcast(Key);}

// -----------------------------------------------------------------------------
// ResetSequence
// Svuota completamente lo stato del componente lato runtime:
// - cancella la sequenza
// - pulisce il pending (se c'era)
// -----------------------------------------------------------------------------
void UInputTagBufferComponent::ResetSequence()
{
    InputSequenceTags.Empty();
    bBufferedInputPending = false;
    BufferedInputTag = FGameplayTag();            // invalida il tag pending
}

// -----------------------------------------------------------------------------
// SetIsAttacking
// Imposta lo stato attuale (attacco in corso / no).
// Se sto passando da TRUE -> FALSE e avevo un input pending,
// lo consumo subito (lo aggiungo alla sequenza) e provo a notificare.
// -----------------------------------------------------------------------------
void UInputTagBufferComponent::SetIsAttacking(bool bInIsAttacking)
{
    const bool bWasAttacking = bIsAttacking;
    bIsAttacking = bInIsAttacking;

    // Transizione da "attaccando" a "non attaccando"
    if (bWasAttacking && !bIsAttacking && bBufferedInputPending)
    {
        // Consumo il pending: lo aggiungo alla sequenza
        bBufferedInputPending = false;

        if (BufferedInputTag.IsValid())
        {
            InputSequenceTags.Add(BufferedInputTag);
            BufferedInputTag = FGameplayTag();    // pulizia del pending
            TryConsumeIfReady();                  // applica soglia + notifica
        }
    }
}
