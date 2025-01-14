#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "InteractableComponent.generated.h"

class UUserWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MEGA_API UInteractableComponent : public UActorComponent {
	GENERATED_BODY()
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UInteractableComponent();
	
	void PrimaryInteract(ACharacter* Character); // call this from input

protected:
	virtual void BeginPlay() override;
	
	void TraceUnderCursor();

	void Interact(AActor* InFocus, ACharacter* Character);

	void ShowCrosshairUI(AActor* InFocus);

	UPROPERTY()
	AActor* LastFocusActor;

	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float InteractDistance = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float InteractRadius = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel = ECC_WorldDynamic;
	

};
