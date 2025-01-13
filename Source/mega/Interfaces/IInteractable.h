#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

class UStaticMesh;
class AMegaCharacter;

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
	void Interact(APawn* InstigatorPawn);

	/*UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Inspect(AMegaCharacter* Character, UStaticMesh* StaticMesh);*/
};

