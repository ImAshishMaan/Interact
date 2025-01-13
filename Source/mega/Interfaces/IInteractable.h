#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType)
class UIInteractable : public UInterface {
	GENERATED_BODY()
};

/**
 * 
 */
class MEGA_API IIInteractable {
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	void Interact();
public:
};
