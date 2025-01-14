#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

UENUM(BlueprintType)
enum class EInteractionType : uint8 {
	CrosshairUI UMETA(DisplayName = "Crosshair UI"),
	PressToInspect UMETA(DisplayName = "Press to Inspect")
};

class ACharacter;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIInteractable : public UInterface {
	GENERATED_BODY()
};

/**
 * 
 */
class MEGA_API IIInteractable {
	GENERATED_BODY()

public:
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Interact(ACharacter* Character);

	// New function to get interaction type
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	EInteractionType GetInteractionType() const;

};


