#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"              // Necessario per usare FGameplayTag
#include "InputTagBufferComponent.generated.h"

// ============================================================================
// Delegato che il componente emette quando la sequenza cambia/va consumata.
// Notifica una chiave FString già pronta per la tua DataTable
// (es: "Input.Attack.Light|Input.Attack.Heavy").
// ============================================================================
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagSequence, const FString&, Sequence);

/**
 * Componente SEPARATO che bufferizza input come FGameplayTag.
 * - Se non stai attaccando: gli input vengono aggiunti subito alla sequenza.
 * - Se stai attaccando (bIsAttacking = true): l’input viene messo "in pending".
 *   Quando torni a false, il pending viene consumato e aggiunto alla sequenza.
 * Ogni volta che la sequenza è valida e non supera il limite, emette OnTagSequence
 * con una chiave "TagA|TagB|TagC" compatibile con la tua DataTable.
 */
UCLASS(ClassGroup=(Combat), meta=(BlueprintSpawnableComponent))
class GAMEDEV_API UInputTagBufferComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UInputTagBufferComponent();

    // ------------------------------------------------------------------------
    // Aggiunge un input (GameplayTag) al buffer.
    // - Se bIsAttacking è true, l’input viene messo "in sospeso" (pending).
    // - Se bIsAttacking è false, viene aggiunto alla sequenza e si notifica.
    // ------------------------------------------------------------------------
    UFUNCTION(BlueprintCallable, Category="Combat|Input Tag Buffer")
    void AddInputTagToBuffer(const FGameplayTag& InputTag);

    // ------------------------------------------------------------------------
    // Imposta lo stato "sto attaccando / non sto attaccando".
    // Quando si passa da TRUE -> FALSE, se c’è un input pending lo consuma e
    // lo aggiunge alla sequenza, poi prova a notificare.
    // ------------------------------------------------------------------------
    UFUNCTION(BlueprintCallable, Category="Combat|Input Tag Buffer")
    void SetIsAttacking(bool bInIsAttacking);

    // ------------------------------------------------------------------------
    // Reset completo del buffer:
    // - Svuota la sequenza di tag
    // - Annulla eventuale input pending
    // ------------------------------------------------------------------------
    UFUNCTION(BlueprintCallable, Category="Combat|Input Tag Buffer")
    void ResetSequence();

public:
    // ------------------------ STATO / CONFIGURAZIONE -------------------------

    // True = sto eseguendo un attacco (gli input vanno in pending)
    // False = posso accumulare direttamente gli input nella sequenza
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Input Tag Buffer")
    bool bIsAttacking = false;

    // Ultimo input ricevuto mentre stavo attaccando (pending)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat|Input Tag Buffer")
    FGameplayTag BufferedInputTag;

    // Esiste un input pending valido?
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat|Input Tag Buffer")
    bool bBufferedInputPending = false;

    // Sequenza corrente di input, espressa come array di GameplayTag
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Combat|Input Tag Buffer")
    TArray<FGameplayTag> InputSequenceTags;

    // Lunghezza massima della sequenza (in numero di input, non caratteri).
    // Se superata, la sequenza viene svuotata (comportamento come il tuo originale).
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat|Input Tag Buffer", meta=(ClampMin="1"))
    int32 MaxBufferSize = 4;

    // Evento emesso quando la sequenza è pronta da interpretare.
    // Ricevi già la chiave pronta per la DataTable (TagA|TagB|TagC).
    UPROPERTY(BlueprintAssignable, Category="Combat|Input Tag Buffer")
    FOnTagSequence OnComboAttempt;

private:
    // ------------------------------------------------------------------------
    // Converte l’array di tag in una chiave "TagA|TagB|TagC".
    // Esempio: [Input.Attack.Light, Input.Attack.Heavy] -> "Input.Attack.Light|Input.Attack.Heavy"
    // ------------------------------------------------------------------------
    static FString MakeKeyFromTags(const TArray<FGameplayTag>& Tags);

    // ------------------------------------------------------------------------
    // Applica la logica "soglia" e notifica:
    // - Se la sequenza supera MaxBufferSize -> svuota (reset soft).
    // - Altrimenti costruisce la chiave e chiama OnTagSequence.
    // ------------------------------------------------------------------------
    void TryConsumeIfReady();
};
